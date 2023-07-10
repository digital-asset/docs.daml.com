.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _explicit-contract-disclosure:

Explicit Contract Disclosure (Experimental)
###########################################

In Daml, you must specify upfront who can view data. To change who can see the data, you would typically need to rewrite the asset with a new annotation. Canton 2.7 introduces explicit contract disclosure as a feature that allows you to seamlessly delegate contract read rights to a non-stakeholder using off-ledger data distribution. This supports efficient, scalable data sharing on the ledger. 

Here are some use cases that illustrate how you might benefit from explicit contract disclosure:

- You want to provide proof of the price data for a stock transaction. Instead of subscribing to price updates and potentially being inundated with thousands of price updates every minute, you could put the price data on a separate ledger that has a Web 2.0 API. You can then use that API to feed only the current price back into the ledger once.
- You need to distribute software updates for an app. In an open network, that could mean shipping the update to millions of users. Instead, you can run automations centrally and use data from the user to build a transaction.

Toggle the ``explicit-disclosure-unsafe`` flag in the participant configuration as shown below
to use disclosed contracts in command submission by means of explicit contract disclosure.

.. note::  This feature is **experimental** and **must not** be used in production environments.

::

    participants {
        participant {
            ledger-api.explicit-disclosure-unsafe = true
        }
    }

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

.. note:: Only contracts created starting with Canton 2.6 can be shared as disclosed contracts.
  Prior to this version, contracts' **CreatedEvent** does not have ``ContractMetadata`` populated
  and cannot be used as disclosed contracts.

.. _submitter-disclosed-contract:

Attaching a disclosed contract to a command submission
------------------------------------------------------

A disclosed contract can be attached as part of the ``Command``'s :ref:`disclosed_contracts <com.daml.ledger.api.v1.Commands.disclosed_contracts>`
and requires the following fields (see :ref:`DisclosedContract <com.daml.ledger.api.v1.DisclosedContract>` for content details) to be populated from
the original `CreatedEvent` (see above):

- **template_id** - The contract's template id.
- **contract_id** - The contract id.
- **arguments** - The contract's create arguments. This field is a protobuf ``oneof``
  and it allows either passing the contract's create arguments typed (as ``create_arguments``)
  or as a byte array (as ``create_arguments_blob``).
  Generally, clients should use the ``create_arguments_blob`` for convenience since they can be received as such
  from the stakeholder off-ledger (see above).
- **metadata** - The contract metadata. This field can be populated as received from the stakeholder (see below).

Trading the stock with explicit disclosure
-------------------------------------------------

In the example above, **Buyer** does not have visibility over the ``stockCid``, ``priceQuotationCid`` and ``offerCid`` contracts,
so **Buyer** must provide them as disclosed contracts in the command submission exercising ``Offer_Accept``. To
do so, the contracts' stakeholders must fetch them from the ledger and make them available to the **Buyer**.

.. note:: Daml Script support for explicit disclosure is currently not implemented.
  The last steps of the example are modeled using raw gRPC queries.

The contracts' stakeholders issue fetch queries to the Ledger API for retrieving
the associated contract payloads. For simplicity in the example, all parties reside on participant ``participant``
with the Ledger API running on port ``5031``.

::

  # Needs to be extracted via package lookup
  packageId="436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d"

  # Needs to be extracted via party lookup
  buyerId="Buyer::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"
  stockExchangeId="StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"
  sellerId="Seller::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"

  # StockExchange fetches the Stock contract referenced by stockCid from the ledger by querying the Ledger API
  # (here we are using the GetTransactions query)
  grpcurl -plaintext -d '{"ledgerId":"participant","begin":{"absolute":"0000000000000000"},"end":{"boundary":"LEDGER_END"},"filter":{"filters_by_party":{"'"$stockExchangeId"'":{"inclusive":{"template_ids":[{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Stock"}]}}}},"verbose":true}' localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions
  # Result: {"transactions":[{"transaction_id":"1220073a3db0e42b536791ed24689ec587276de2cad79887e466c380c26ffda7baf1","command_id":"e1cbb1b7-277c-4126-bde7-13b3cb158b36","effective_at":"2023-04-05T09:11:29.062939Z","events":[{"created":{"event_id":"#1220073a3db0e42b536791ed24689ec587276de2cad79887e466c380c26ffda7baf1:0","contract_id":"00406f5cfbe495a21d576fbc4971e5d12c1ec5de972439ca0c054bbe54883de2a9ca01122064de6a454a83ce3ac4535ac9df550b21b90b9524fee6210af213fccf0ac4acca","template_id":{"package_id":"436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d","module_name":"StockExchange","entity_name":"Stock"},"create_arguments":{"record_id":{"package_id":"436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d","module_name":"StockExchange","entity_name":"Stock"},"fields":[{"label":"issuer","value":{"party":"StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"}},{"label":"owner","value":{"party":"Seller::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"}},{"label":"stockName","value":{"text":"Daml"}}]},"witness_parties":["StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"agreement_text":"","signatories":["StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"observers":["Seller::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"metadata":{"created_at":"2023-04-05T09:11:29.062939Z","driver_metadata":"CiYKJAgBEiA5hhYAzLWLGx4dr6MO0r1xoD/AAu/Xe6H56hCOzDqOlQ=="}}}],"offset":"00000000000000000d"}]}

  # As above, StockExchange fetches the PriceQuotation referenced by priceQuotationCid
  grpcurl -plaintext -d '{"ledgerId":"participant","begin":{"absolute":"0000000000000000"},"end":{"boundary":"LEDGER_END"},"filter":{"filters_by_party":{"'"$stockExchangeId"'":{"inclusive":{"template_ids":[{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"PriceQuotation"}]}}}},"verbose":true}' localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions
  # Result: {"transactions":[{"transaction_id":"1220ecf0113498df1e9a4fd9aeed82b877b71cb0a8d57fdaca188294dfdeeada5eac","command_id":"433e9786-df09-4243-ad70-1d27fee05031","effective_at":"2023-04-05T09:11:29.257808Z","events":[{"created":{"event_id":"#1220ecf0113498df1e9a4fd9aeed82b877b71cb0a8d57fdaca188294dfdeeada5eac:0","contract_id":"00e0be88a38c25bc0b3b35acd6f46de92584becf99009cb512a71727fb928c90fdca01122080169e053bd955dc5e29efeeb500fd28182546e1306e7ca968eca48c5fd1bc19","template_id":{"package_id":"436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d","module_name":"StockExchange","entity_name":"PriceQuotation"},"create_arguments":{"record_id":{"package_id":"436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d","module_name":"StockExchange","entity_name":"PriceQuotation"},"fields":[{"label":"issuer","value":{"party":"StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"}},{"label":"stockName","value":{"text":"Daml"}},{"label":"value","value":{"int64":"3"}}]},"witness_parties":["StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"agreement_text":"","signatories":["StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"metadata":{"created_at":"2023-04-05T09:11:29.257808Z","driver_metadata":"CiYKJAgBEiBsywnjtj+a0Px6A2LwSV2MrOxE9QyJDM0VpgPAEGamqg=="}}}],"offset":"00000000000000000f"}]}

  # As above, Seller fetches the Offer referenced by offerCid
  grpcurl -plaintext -d '{"ledgerId":"participant","begin":{"absolute":"0000000000000000"},"end":{"boundary":"LEDGER_END"},"filter":{"filters_by_party":{"'"$sellerId"'":{"inclusive":{"template_ids":[{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Offer"}]}}}},"verbose":true}' localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions
  # Result: {"transactions":[{"transaction_id":"1220af12e338e39694374f8e7fc992a9361dfbe942705bdcfb29e56f5c6668713bb3","command_id":"aecbac54-5166-450c-868d-3ee912e7073c","effective_at":"2023-04-05T09:11:29.158305Z","events":[{"created":{"event_id":"#1220af12e338e39694374f8e7fc992a9361dfbe942705bdcfb29e56f5c6668713bb3:0","contract_id":"00b8355cf81045ad6212e6168380dd9ca4b7dbe9b7f0b53c595bdc0b9e60ec6789ca011220249c851ca8927e761d2fdba628f1508c6e2a3bb9fa64164f5c297aae023bfdd3","template_id":{"package_id":"436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d","module_name":"StockExchange","entity_name":"Offer"},"create_arguments":{"record_id":{"package_id":"436c13be1424a16fb69a3dda4983b94f1965ac12c66d8a6d879ad3027ea4782d","module_name":"StockExchange","entity_name":"Offer"},"fields":[{"label":"seller","value":{"party":"Seller::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"}},{"label":"quotationProducer","value":{"party":"StockExchange::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"}},{"label":"offeredAssetCid","value":{"contract_id":"00406f5cfbe495a21d576fbc4971e5d12c1ec5de972439ca0c054bbe54883de2a9ca01122064de6a454a83ce3ac4535ac9df550b21b90b9524fee6210af213fccf0ac4acca"}}]},"witness_parties":["Seller::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"agreement_text":"","signatories":["Seller::122001002fb09c069a0f4e7badf9cb1a6d7dd9097fbdb653e1278193aa5f36b9c6b3"],"metadata":{"created_at":"2023-04-05T09:11:29.158305Z","driver_metadata":"CiYKJAgBEiBNiC/8U069Zpc7gOt3YGmmdk+TGWEZRsNukLYri+64Sg=="}}}],"offset":"00000000000000000e"}]}

**Buyer** receives these contracts from the stakeholders and adapts them to disclosed contracts (as described in :ref:`the previous section <submitter-disclosed-contract>`)
in a command submission that executes ``Offer_Accept`` on the ``offerCid``. The resulting gRPC command submission, which succeeds, is
shown below.

::

  # Extracted from the transaction lookup query results from above
  offerCid="00b8355cf81045ad6212e6168380dd9ca4b7dbe9b7f0b53c595bdc0b9e60ec6789ca011220249c851ca8927e761d2fdba628f1508c6e2a3bb9fa64164f5c297aae023bfdd3"
  priceQuotationCid="00e0be88a38c25bc0b3b35acd6f46de92584becf99009cb512a71727fb928c90fdca01122080169e053bd955dc5e29efeeb500fd28182546e1306e7ca968eca48c5fd1bc19"
  stockCid="00406f5cfbe495a21d576fbc4971e5d12c1ec5de972439ca0c054bbe54883de2a9ca01122064de6a454a83ce3ac4535ac9df550b21b90b9524fee6210af213fccf0ac4acca"

  # The contract id of Buyer's IOU (for conciseness, not shown in this example but can be extracted by the Buyer from the getTransactions queries as above)
  buyerIouCid="00cd7d7b27f1b323bb55c2b0adf2aac76657079741adf6dc98a5d977338e3c92eeca011220649fd780478bb1d2159639fa6df276c0214c672609252c4db601ade0c67605fb"

  stockContractCreatedAt="2023-04-05T09:11:29.062939Z"
  stockContractDriverMetadata="CiYKJAgBEiA5hhYAzLWLGx4dr6MO0r1xoD/AAu/Xe6H56hCOzDqOlQ=="

  offerContractCreatedAt="2023-04-05T09:11:29.158305Z"
  offerContractDriverMetadata="CiYKJAgBEiBNiC/8U069Zpc7gOt3YGmmdk+TGWEZRsNukLYri+64Sg=="

  priceQuotationContractCreatedAt="2023-04-05T09:11:29.257808Z"
  priceQuotationContractDriverMetadata="CiYKJAgBEiBsywnjtj+a0Px6A2LwSV2MrOxE9QyJDM0VpgPAEGamqg=="

  # Buyer exercises Offer_Accept on offerCid with populating the Command.disclosed_contracts field
  # with the data previously shared off-ledger for offerCid, stockCid and priceQuotationCid contracts
  grpcurl -plaintext -d '{"commands":{"ledger_id":"participant","workflow_id":"ExplicitDisclosureWorkflow","application_id":"ExplicitDisclosure","command_id":"ExplicitDisclosure-command","party":"'"$buyerId"'","commands":[{"exercise":{"template_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Offer"},"contract_id":"'"$offerCid"'","choice":"Offer_Accept","choice_argument":{"record":{"record_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Offer_Accept"},"fields":[{"label":"priceQuotationCid","value":{"contract_id":"'"$priceQuotationCid"'"}},{"label":"buyer","value":{"party":"'"$buyerId"'"}},{"label":"buyerIou","value":{"contract_id":"'"$buyerIouCid"'"}}]}}}}],"submission_id":"ExplicitDisclosure-submission","disclosed_contracts":[{"template_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Stock"},"contract_id":"'"$stockCid"'","create_arguments":{"record_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Stock"},"fields":[{"label":"issuer","value":{"party":"'"$stockExchangeId"'"}},{"label":"owner","value":{"party":"'"$sellerId"'"}},{"label":"stockName","value":{"text":"Daml"}}]},"metadata":{"created_at":"'"$stockContractCreatedAt"'","driver_metadata":"'"$stockContractDriverMetadata"'"}},{"template_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Offer"},"contract_id":"'"$offerCid"'","create_arguments":{"record_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"Offer"},"fields":[{"label":"seller","value":{"party":"'"$sellerId"'"}},{"label":"quotationProducer","value":{"party":"'"$stockExchangeId"'"}},{"label":"offeredAssetCid","value":{"contract_id":"'"$stockCid"'"}}]},"metadata":{"created_at":"'"$offerContractCreatedAt"'","driver_metadata":"'"$offerContractDriverMetadata"'"}},{"template_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"PriceQuotation"},"contract_id":"'"$priceQuotationCid"'","create_arguments":{"record_id":{"package_id":"'"$packageId"'","module_name":"StockExchange","entity_name":"PriceQuotation"},"fields":[{"label":"issuer","value":{"party":"'"$stockExchangeId"'"}},{"label":"stockName","value":{"text":"Daml"}},{"label":"value","value":{"int64":"3"}}]},"metadata":{"created_at":"'"$priceQuotationContractCreatedAt"'","driver_metadata":"'"$priceQuotationContractDriverMetadata"'"}}]}}' localhost:5031 com.daml.ledger.api.v1.CommandService/SubmitAndWait
