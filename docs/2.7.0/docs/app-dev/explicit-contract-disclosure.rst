.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _explicit-contract-disclosure:

Explicit Contract Disclosure (Experimental)
###########################################

Canton 2.7 introduces explicit contract disclosure as a feature
that allows you to seamlessly delegate contract read rights to a non-stakeholder using off-ledger data distribution.

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

  -- StockExchange fetches the Stock contract referenced by stockCid from the ledger by querying the Ledger API
  -- (here we are using the GetTransactions query)
  grpcurl -plaintext -d '{"ledgerId":"participant","begin":{"absolute":"0000000000000000"},"end":{"boundary":"LEDGER_END"},"filter":{"filtersByParty":{"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa":{"inclusive":{"templateIds":[{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Stock"}]}}}},"verbose":true}' localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions
  -- Result: {"transactions":[{"transaction_id":"122042e84ef22a53b5142caa87b1781f9ac5a722afecdab22bac14e96f7c08cc72a6","command_id":"65d892e8-01f5-4f08-930c-6947a74b9c97","effective_at":"2023-03-22T19:18:46.750406Z","events":[{"created":{"event_id":"#122042e84ef22a53b5142caa87b1781f9ac5a722afecdab22bac14e96f7c08cc72a6:0","contract_id":"00b58bf53c8460d597173323436d340943e81a8a1f29f34b032a5938a9ce0a1e64ca0112203ea53a05196b6bdeda8a0db13db0fa15b4858fa4efcd97348a40b2c2b3bb1fa6","template_id":{"package_id":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","module_name":"StockExchange","entity_name":"Stock"},"create_arguments":{"record_id":{"package_id":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","module_name":"StockExchange","entity_name":"Stock"},"fields":[{"label":"issuer","value":{"party":"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"owner","value":{"party":"Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"stockName","value":{"text":"Daml"}}]},"witness_parties":["StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"agreement_text":"","signatories":["StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"observers":["Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"metadata":{"created_at":"2023-03-22T19:18:46.750406Z","driver_metadata":"CiYKJAgBEiA766TiHrw+qL6JW+0ze65RTfIFFFLrh09VpCOdjXs/2g=="}}}],"offset":"00000000000000000d"}]}

  -- As above, StockExchange fetches the PriceQuotation referenced by priceQuotationCid
  grpcurl -plaintext -d '{"ledgerId":"participant","begin":{"absolute":"0000000000000000"},"end":{"boundary":"LEDGER_END"},"filter":{"filtersByParty":{"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa":{"inclusive":{"templateIds":[{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"PriceQuotation"}]}}}},"verbose":true}' localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions
  -- Result: {"transactions":[{"transaction_id":"12201195375e18bd12570a4506a1d211e213620229466e8372690043a9db4ea5aa13","command_id":"69d9b10d-0227-4703-9c35-739cec273f31","effective_at":"2023-03-22T19:18:46.927082Z","events":[{"created":{"event_id":"#12201195375e18bd12570a4506a1d211e213620229466e8372690043a9db4ea5aa13:0","contract_id":"00958d90de435166c63a70884d36700d49f05c8e58644afa772021171edd782e17ca0112208d3b314f70bf390728f66eb52349389aaccdfa6d7073b1a0d68ae1631961a919","template_id":{"package_id":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","module_name":"StockExchange","entity_name":"PriceQuotation"},"create_arguments":{"record_id":{"package_id":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","module_name":"StockExchange","entity_name":"PriceQuotation"},"fields":[{"label":"issuer","value":{"party":"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"stockName","value":{"text":"Daml"}},{"label":"value","value":{"int64":"3"}}]},"witness_parties":["StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"agreement_text":"","signatories":["StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"metadata":{"created_at":"2023-03-22T19:18:46.927082Z","driver_metadata":"CiYKJAgBEiDOv6D+wdEKAJbkn5mpXkKJucdJ/M/SpuZO9A+EGOYDzw=="}}}],"offset":"00000000000000000f"}]}

  -- As above, Seller fetches the Offer referenced by offerCid
  grpcurl -plaintext -d '{"ledgerId":"participant","begin":{"absolute":"0000000000000000"},"end":{"boundary":"LEDGER_END"},"filter":{"filtersByParty":{"Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa":{"inclusive":{"templateIds":[{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Offer"}]}}}},"verbose":true}' localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions
  -- Result: {"transactions":[{"transaction_id":"1220e17dec28e3277933917513fb92e80a1ef0c5b9645b017527e3cc00723d4da1b7","command_id":"0b255a2c-db13-4d6e-8ab4-a7b20a0b261d","effective_at":"2023-03-22T19:18:46.838466Z","events":[{"created":{"event_id":"#1220e17dec28e3277933917513fb92e80a1ef0c5b9645b017527e3cc00723d4da1b7:0","contract_id":"00368651c0f69fc69cea6e9f69293e41ec9da5edd9ecf4c71fe6689027a62595d5ca011220580ab01aec0c0e2b2f171556087224aaa60f793100bec923f881352d1812a767","template_id":{"package_id":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","module_name":"StockExchange","entity_name":"Offer"},"create_arguments":{"record_id":{"package_id":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","module_name":"StockExchange","entity_name":"Offer"},"fields":[{"label":"seller","value":{"party":"Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"quotationProducer","value":{"party":"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"offeredAssetCid","value":{"contract_id":"00b58bf53c8460d597173323436d340943e81a8a1f29f34b032a5938a9ce0a1e64ca0112203ea53a05196b6bdeda8a0db13db0fa15b4858fa4efcd97348a40b2c2b3bb1fa6"}}]},"witness_parties":["Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"agreement_text":"","signatories":["Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"],"metadata":{"created_at":"2023-03-22T19:18:46.838466Z","driver_metadata":"CiYKJAgBEiDO65v0iPOxiiBxvMCUge/ddRaK3NfWt9TuqNpRrMXNzA=="}}}],"offset":"00000000000000000e"}]}

**Buyer** receives these contracts from the stakeholders and adapts them to disclosed contracts (as described in :ref:`the previous section <submitter-disclosed-contract>`)
in a command submission that executes ``Offer_Accept`` on the ``offerCid``. The resulting gRPC command submission, which succeeds, is
shown below.

::

  -- Buyer exercises Offer_Accept on offerCid with populating the Command.disclosed_contracts field
  -- with the data previously shared off-ledger for offerCid, stockCid and priceQuotationCid
  grpcurl -plaintext -d '{"commands":{"ledgerId":"participant","workflowId":"ExplicitDisclosureWorkflow","applicationId":"ExplicitDisclosure","commandId":"ExplicitDisclosure-command","party":"Buyer::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa","commands":[{"exercise":{"templateId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Offer"},"contractId":"00368651c0f69fc69cea6e9f69293e41ec9da5edd9ecf4c71fe6689027a62595d5ca011220580ab01aec0c0e2b2f171556087224aaa60f793100bec923f881352d1812a767","choice":"Offer_Accept","choiceArgument":{"record":{"recordId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Offer_Accept"},"fields":[{"label":"priceQuotationCid","value":{"contractId":"00958d90de435166c63a70884d36700d49f05c8e58644afa772021171edd782e17ca0112208d3b314f70bf390728f66eb52349389aaccdfa6d7073b1a0d68ae1631961a919"}},{"label":"buyer","value":{"party":"Buyer::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"buyerIou","value":{"contractId":"009008413016cc8e53dd69164df4b7dbc3b57ca541d1176b7324d1fa2ca2e23aa6ca0112200c592da4825f68b6a1978e579115b0f7baf9fa414923c0e62c95b793a767ef16"}}]}}}}],"submissionId":"ExplicitDisclosure-submission","disclosedContracts":[{"templateId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Stock"},"contractId":"00b58bf53c8460d597173323436d340943e81a8a1f29f34b032a5938a9ce0a1e64ca0112203ea53a05196b6bdeda8a0db13db0fa15b4858fa4efcd97348a40b2c2b3bb1fa6","createArguments":{"recordId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Stock"},"fields":[{"label":"issuer","value":{"party":"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"owner","value":{"party":"Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"stockName","value":{"text":"Daml"}}]},"metadata":{"createdAt":"2023-03-22T19:18:46.750406Z","driverMetadata":"CiYKJAgBEiA766TiHrw+qL6JW+0ze65RTfIFFFLrh09VpCOdjXs/2g=="}},{"templateId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Offer"},"contractId":"00368651c0f69fc69cea6e9f69293e41ec9da5edd9ecf4c71fe6689027a62595d5ca011220580ab01aec0c0e2b2f171556087224aaa60f793100bec923f881352d1812a767","createArguments":{"recordId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"Offer"},"fields":[{"label":"seller","value":{"party":"Seller::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"quotationProducer","value":{"party":"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"offeredAssetCid","value":{"contractId":"00b58bf53c8460d597173323436d340943e81a8a1f29f34b032a5938a9ce0a1e64ca0112203ea53a05196b6bdeda8a0db13db0fa15b4858fa4efcd97348a40b2c2b3bb1fa6"}}]},"metadata":{"createdAt":"2023-03-22T19:18:46.838466Z","driverMetadata":"CiYKJAgBEiDO65v0iPOxiiBxvMCUge/ddRaK3NfWt9TuqNpRrMXNzA=="}},{"templateId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"PriceQuotation"},"contractId":"00958d90de435166c63a70884d36700d49f05c8e58644afa772021171edd782e17ca0112208d3b314f70bf390728f66eb52349389aaccdfa6d7073b1a0d68ae1631961a919","createArguments":{"recordId":{"packageId":"5811603b1342a2a791fd69aff08d710f67bf652f3e7129dd51f69bc01bb30f19","moduleName":"StockExchange","entityName":"PriceQuotation"},"fields":[{"label":"issuer","value":{"party":"StockExchange::12206edc46b86d9ea5f75407fa04720ea005f253ca736fb047a8c25839edf2fbb8fa"}},{"label":"stockName","value":{"text":"Daml"}},{"label":"value","value":{"int64":"3"}}]},"metadata":{"createdAt":"2023-03-22T19:18:46.927082Z","driverMetadata":"CiYKJAgBEiDOv6D+wdEKAJbkn5mpXkKJucdJ/M/SpuZO9A+EGOYDzw=="}}]}}' localhost:5031 com.daml.ledger.api.v1.CommandService/SubmitAndWait
