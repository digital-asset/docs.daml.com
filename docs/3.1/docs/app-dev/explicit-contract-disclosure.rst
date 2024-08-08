.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _explicit-contract-disclosure:

Explicit Contract Disclosure
####################################

In Daml, you must specify up front who can view data using `stakeholder <https://docs.daml.com/concepts/glossary.html#stakeholder>`_ annotations in template definitions.
To change who can see the data, you would typically need to recreate a contract with a template that computes different stakeholder parties.

Explicit contract disclosure allows you to delegate contract read rights to non-stakeholders using off-ledger data distribution.
This supports efficient, scalable data sharing on the ledger.

.. note::  Explicit disclosure is activated by default.
    To deactivate it, configure ``participants.participant.ledger-api.enable-explicit-disclosure = false``.

Here are some use cases that illustrate how you might benefit from explicit contract disclosure:

- You want to provide proof of the price data for a stock transaction. Instead of subscribing to price updates and potentially being inundated with thousands of price updates every minute, you could serve the price data through a traditional Web 2.0 API. You can then use that API to feed only the current price back into the ledger at the time of use. You still get the same validation and security, but reduce the amount of data being transferred manyfold.
- You want to run an open market on ledger. Rather than making all bids and asks explicitly visible to all marketplace users, you serve market data though standard Web 2.0 APIs. At the point of use, the available bids and asks are fed back into the transactions to get the same activeness and correctness guarantees that would be provided had they been shared though the observer mechanism.

Contract Read Delegation
------------------------

Contract read delegation allows a party to acquire read rights during
command submission over a contract of which it is neither a stakeholder nor an informee.

As an example application where read delegation could be used,
consider a simplified trade between two parties.
In this example, party **Seller** owns a unit of Digital Asset ``Stock`` issued by the **StockExchange** party.
As the issuer of the stock, **StockExchange** also publishes the stock's ``PriceQuotation`` as public data,
which can be used for settling trades at the correct market value. The **Seller** announces an offer
to sell its stock publicly by creating an ``Offer`` contract that can be exercised by anyone who
can pay the correct market value in terms of ``IOU`` units.

On the other side, party **Buyer** owns an ``IOU`` with 10 monetary units, which it wants to
use to acquire **Seller**'s stock.

The Daml templates used to model the above-mentioned trade are outlined below.

::

    module StockExchange where

    import Daml.Script
    import DA.Assert
    import DA.Action

    template IOU
      with
        issuer: Party
        owner: Party
        value: Int
      where
        signatory issuer
        observer owner

        choice IOU_Transfer: ()
          with
            target: Party
            amount: Int
          controller owner
          do
            -- Check that the transferred amount is not higher than the current IOU value
            assert (value >= amount)
            create this with issuer = issuer, owner = target, value = amount
            -- No need to create a new IOU for owner if the full value is transferred
            if value == amount then pure ()
            else void $ create this with issuer = issuer, owner = owner, value = value - amount
            pure ()

    template Stock
      with
        issuer: Party
        owner: Party
        stockName: Text
      where
        signatory issuer
        observer owner

        choice Stock_Transfer: ()
          with
            newOwner: Party
          controller owner
          do
            create this with owner = newOwner
            pure ()

    -- Expresses the current market value of a stock issued by the issuer.
    -- Not modelled in this example: the issuer ensures that only one `PriceQuotation`
    -- is active at a time for a specific `stockName`.
    template PriceQuotation
      with
        issuer: Party
        stockName: Text
        value: Int
      where
        signatory issuer

        -- Helper choice to allow the controller to fetch this contract without being a stakeholder.
        -- By fetching this contract, the controller (i.e. `fetcher`) proves
        -- that this contract is active and represents the current market value for this stock.
        nonconsuming choice PriceQuotation_Fetch: PriceQuotation
          with fetcher: Party
          controller fetcher
          do pure this

    template Offer
      with
        seller: Party
        quotationProducer: Party
        offeredAssetCid: ContractId Stock
      where
        signatory seller

        choice Offer_Accept: ()
          with
            priceQuotationCid: ContractId PriceQuotation
            buyer: Party
            buyerIou: ContractId IOU
          controller buyer
          do
            priceQuotation <- exercise
              priceQuotationCid PriceQuotation_Fetch with
                fetcher = buyer
            asset <- fetch offeredAssetCid

            -- Assert the quotation issuer and asset name
            priceQuotation.issuer === quotationProducer
            priceQuotation.stockName === asset.stockName

            _ <- exercise
              offeredAssetCid Stock_Transfer with
                newOwner = buyer

            -- Purchase the stock at the currently published fair price.
            _ <- exercise
              buyerIou IOU_Transfer with target = seller, amount = priceQuotation.value
            pure ()

The following snippet of :ref:`Daml Script <daml-script>` models the setup of the trade between the parties.

::

      let stockName = "Daml"

      stockCid <- submit stockExchange do
        createCmd Stock with
          issuer = stockExchange
          owner = seller
          stockName = stockName

      offerCid <- submit seller do
        createCmd Offer with
          seller = seller
          quotationProducer = stockExchange
          offeredAssetCid = stockCid

      priceQuotationCid <- submit stockExchange do
        createCmd PriceQuotation with
          issuer = stockExchange
          stockName = stockName
          value = 3

      buyerIouCid <- submit bank do
        createCmd IOU with
          issuer = bank
          owner = buyer
          value = 10

Settling the trade on-ledger implies that **Buyer** exercises ``Offer_Accept``
on the ``offerCid`` contract.
But how can **Buyer** exercise a choice on a contract
on which it is neither a stakeholder nor a prior informee?
The same question applies to **Buyer**'s visibility over the
``stockCid`` and ``priceQuotationCid`` contracts.

If **Buyer** plainly exercises the choice as shown in the snippet below,
the submission will fail with an error citing missing visibility rights over the involved contracts.

::

      -- Command fails with missing visibility over the contracts for buyer
      _ <- submit buyer do
        exerciseCmd offerCid Offer_Accept with priceQuotationCid = priceQuotationCid, buyer = buyer, buyerIou = buyerIouCid


Read delegation using explicit contract disclosure
``````````````````````````````````````````````````

With the introduction of explicit contract disclosure, **Buyer** can accept the offer from **Seller**
without having seen the involved contracts on the ledger. This is possible if the contracts' stakeholders
decide to :ref:`disclose <stakeholder-contract-share>` their contracts to any party desiring to execute such a trade.
**Buyer** can attach the disclosed contracts to the command submission
that is exercising ``Offer_Accept`` on **Seller**'s ``offerCid``, thus bypassing the visibility restriction
over the contracts.

.. note:: The Ledger API uses the disclosed contracts attached to command submissions
  for resolving contract and key activeness lookups during command interpretation.
  This means that usage of a disclosed contract effectively bypasses the visibility restriction
  of the submitting party over the respective contract.
  However, the authorization restrictions of the Daml model still apply:
  the submitted command still needs to be well authorized. The actors
  need to be properly authorized to execute the action,
  as described in :ref:`Privacy Through Authorization <da-model-privacy-authorization>`.

.. _stakeholder-contract-share:

How do stakeholders disclose contracts to submitters?
-----------------------------------------------------

The disclosed contract's details can be fetched by the contract's stakeholder from the contract's
associated :ref:`CreatedEvent <com.daml.ledger.api.v1.CreatedEvent>`,
which can be read from the Ledger API via the active contracts and transactions queries
(see :ref:`Reading from the ledger <reading-from-the-ledger>`).

The stakeholder can then share the disclosed contract details to the submitter off-ledger (outside of Daml)
by conventional means, such as HTTPS, SFTP, or e-mail. A :ref:`DisclosedContract <com.daml.ledger.api.v1.DisclosedContract>` can
be constructed from the fields of the same name from the original contract's ``CreatedEvent``.

.. note::
  The ``created_event_blob`` field in ``CreatedEvent`` (used to construct the :ref:`DisclosedContract <com.daml.ledger.api.v1.DisclosedContract>`)
  is populated **only** on demand for ``GetTransactions``, ``GetTransactionTrees``, and ``GetActiveContracts`` streams.
  To learn more, see :ref:`configuring transaction filters <transaction-filter>`.

.. _submitter-disclosed-contract:

Attaching a disclosed contract to a command submission
------------------------------------------------------

A disclosed contract can be attached as part of the ``Command``'s :ref:`disclosed_contracts <com.daml.ledger.api.v1.Commands.disclosed_contracts>`
and requires the following fields (see :ref:`DisclosedContract <com.daml.ledger.api.v1.DisclosedContract>` for content details) to be populated from
the original `CreatedEvent` (see above):

- **template_id** - The contract's template id.
- **contract_id** - The contract id.
- **created_event_blob** - The contract's representation as an opaque blob encoding.

.. note:: Only contracts created starting with Canton 2.8 can be shared as disclosed contracts.
  In earlier versions, the **CreatedEvent** does not have the required populated `created_event_blob` field
  and cannot be used as disclosed contracts.

Trading the stock with explicit disclosure
------------------------------------------

In the example above, **Buyer** does not have visibility over the ``stockCid``, ``priceQuotationCid`` and ``offerCid`` contracts,
so **Buyer** must provide them as disclosed contracts in the command submission exercising ``Offer_Accept``. To
do so, the contracts' stakeholders must fetch them from the ledger and make them available to the **Buyer**.

Then, the **Buyer** attaches the disclosed contract payloads to the command submission that accepts the offer.

These last two steps are executed using the new Daml Script functions supporting explicit disclosure: `queryDisclosure` and `submitWithDisclosures`.

::

       disclosedStock <- fromSome <$> queryDisclosure stockExchange stockCid
       disclosedOffer <- fromSome <$> queryDisclosure seller offerCid
       disclosedPriceQuotation <- fromSome <$> queryDisclosure stockExchange priceQuotationCid

       _ <- submitWithDisclosures buyer [disclosedStock, disclosedOffer, disclosedPriceQuotation] do
         exerciseCmd offerCid Offer_Accept with priceQuotationCid = priceQuotationCid, buyer = buyer, buyerIou = buyerIouCid


.. note:: For an example using Java bindings for client applications, see the
  `Java Bindings StockExchange example project <https://github.com/digital-asset/ex-java-bindings/blob/f474ae83976b0ad197e2fabfce9842fb9b3de907/StockExchange/README.rst>`_.

Safeguards
------------------------------------------
Explicit Contract Disclosure usage should always be accompanied by on-ledger contracts. This ensures that workflows executed based on the disclosed contract's contents conform to on-ledger agreements between the stakeholders (or trusted parties) involved.

In the above example, ``IOU`` contracts between *Buyer* and *Issuer* (a trusted party on the ledger) ensure that the exercising of the ``Offer_Accept`` choice using disclosed contract results in a contractually agreed-upon outcome.

This works by performing several safety checks in the ``IOU_Transfer`` choice within the ``IOU`` contract, which is called from the ``Offer_Accept`` choice.

The ``IOU`` contract provides several safeguards in the ``Offer_Accept`` workflow:

- *Buyer* exercising the ``Offer_Accept`` choice is defined on the ``IOU`` agreement.
- Creation of an IOU with the same amount for the *Seller* happens atomically with a deduction of the same amount from the *Buyer'* IOU.
- *Buyer* cannot be deducted and *Seller* cannot receive more than the stipulated value on the ``IOU`` contract.

By ensuring the *Buyer* party expected to execute the ``Offer_Accept`` choice, a trusted *Issuer* party and required terms of execution are clearly defined on an trusted on-ledger ``IOU`` contract with a trusted *Issuer* party as a signatory, the *Seller* can disclose the ``Offer`` contract and the **Buyer** can execute the ``Offer_Accept`` choice on the disclosed ``Offer`` contract knowing workflow safety is ensured.

If disclosed contracts contain malicious data or are maliciously executed on, the safeguards prevent unexpected outcomes.

Generic variants of the discussed safeguards should be implemented when utilizing explicitly disclosed contracts to ensure workflow safety.
