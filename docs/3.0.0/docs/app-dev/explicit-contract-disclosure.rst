.. Copyright (c) 2023 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

.. _explicit-contract-disclosure:

Explicit Contract Disclosure (Beta)
###########################################

In Daml, you must specify up front who can view data using `stakeholder <https://docs.daml.com/concepts/glossary.html#stakeholder>`_ annotations in template definitions.
To change who can see the data, you would typically need to recreate a contract with a template that computes different stakeholder parties.

Explicit contract disclosure (available in Canton 2.8.0 as a `Beta feature <https://docs.daml.com/support/status-definitions.html#early-access-features>`_) allows you to delegate contract read rights to non-stakeholders using off-ledger data distribution.
This supports efficient, scalable data sharing on the ledger.

.. note::  Explicit disclosure is activated by default.
    To deactivate it, configure ``participants.participant.ledger-api.enable-explicit-disclosure = false``.

Here are some use cases that illustrate how you might benefit from explicit contract disclosure:

- You want to provide proof of the price data for a stock transaction. Instead of subscribing to price updates and potentially being inundated with thousands of price updates every minute, you could serve the price data though a traditional Web 2.0 API. You can then use that API to feed only the current price back into the ledger at the time of use. You still get the same validation and security, but reduce the amount of data being transferred manyfold.
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

.. note:: Daml Script support for explicit disclosure is currently not implemented.
  The last steps of the example are modeled using raw gRPC queries.
  For a complete example using a high-level client API, see the
  `Java Bindings StockExchange example project <https://github.com/digital-asset/ex-java-bindings/blob/f474ae83976b0ad197e2fabfce9842fb9b3de907/StockExchange/README.rst>`_.

The contracts' stakeholders issue fetch queries to the Ledger API (each to their own participant) for retrieving
the associated contract payloads.

This example uses the following Canton participant node topology:

- ``stockExchangeParticipant`` hosts party with display name ``StockExchange`` and exposes Ledger API on port ``5011``
- ``bankParticipant`` hosts party with display name ``Bank`` and exposes Ledger API on port ``5021``
- ``buyerParticipant`` hosts party with display name ``Buyer`` and exposes Ledger API on port ``5031``
- ``sellerParticipant`` hosts party with display name ``Seller`` and exposes Ledger API on port ``5041``

::

  # Needs to be extracted via package lookup
  packageId="b861bd5ab83cca1dec91c67fe80717846dc0759b21798370b93e1b149c67e717"

  # Needs to be extracted via party lookup
  buyerId="Buyer::12208af4736f4bb2b6608d50a5e800a3cd469a1a7b74c951eb8e0c74faf2ed711c58"
  stockExchangeId="StockExchange::1220b387de01b7daa112c6f397e28ccb95215bbb3c6d818793638e48c27b52bf2e26"
  sellerId="Seller::1220d163325bde4266110f54c5dbcc91281adfc41b0e80a63f0af7857694be627300"

  # StockExchange fetches the Stock contract referenced by stockCid from the ledger by querying the Ledger API
  # (here we are using the GetTransactions query)
  stockQuery=$(cat <<EOF
  {
    "ledgerId": "stockExchangeParticipant",
    "begin": {
      "absolute": "0000000000000000"
    },
    "end": {
      "boundary": "LEDGER_END"
    },
    "filter": {
      "filters_by_party": {
        "$stockExchangeId": {
          "inclusive": {
            "template_filters": [
              {
                "template_id": {
                  "package_id": "$packageId",
                  "module_name": "StockExchange",
                  "entity_name": "Stock"
                },
                "include_created_event_blob": true
              }
            ]
          }
        }
      }
    }
  }
  EOF
  )

  stockTransactions=$(grpcurl -plaintext -d $stockQuery localhost:5011 com.daml.ledger.api.v1.TransactionService/GetTransactions)

  # As above, StockExchange fetches the PriceQuotation referenced by priceQuotationCid
  priceQuotationQuery=$(cat <<EOF
  {
    "ledgerId": "stockExchangeParticipant",
    "begin": {
      "absolute": "0000000000000000"
    },
    "end": {
      "boundary": "LEDGER_END"
    },
    "filter": {
      "filters_by_party": {
        "$stockExchangeId": {
          "inclusive": {
            "template_filters": [
              {
                "template_id": {
                  "package_id": "$packageId",
                  "module_name": "StockExchange",
                  "entity_name": "PriceQuotation"
                },
                "include_created_event_blob": true
              }
            ]
          }
        }
      }
    }
  }
  EOF
  )

  priceQuotationTransactions=$(grpcurl -plaintext -d $priceQuotationQuery localhost:5011 com.daml.ledger.api.v1.TransactionService/GetTransactions)

  # As above, Seller fetches the Offer referenced by offerCid
  offerQuery=$(cat <<EOF
  {
    "ledgerId": "sellerParticipant",
    "begin": {
      "absolute": "0000000000000000"
    },
    "end": {
      "boundary": "LEDGER_END"
    },
    "filter": {
      "filters_by_party": {
        "$sellerId": {
          "inclusive": {
            "template_filters": [
              {
                "template_id": {
                  "package_id": "$packageId",
                  "module_name": "StockExchange",
                  "entity_name": "Offer"
                },
                "include_created_event_blob": true
              }
            ]
          }
        }
      }
    }
  }
  EOF
  )

  offerTransactions=$(grpcurl -plaintext -d $offerQuery localhost:5041 com.daml.ledger.api.v1.TransactionService/GetTransactions)

  # As above, Buyer fetches the IOU
  iouQuery=$(cat <<EOF
  {
    "ledgerId": "buyerParticipant",
    "begin": {
      "absolute": "0000000000000000"
    },
    "end": {
      "boundary": "LEDGER_END"
    },
    "filter": {
      "filters_by_party": {
        "$buyerId": {
          "inclusive": {
            "template_filters": [
              {
                "template_id": {
                  "package_id": "$packageId",
                  "module_name": "StockExchange",
                  "entity_name": "IOU"
                },
                "include_created_event_blob": false
              }
            ]
          }
        }
      }
    }
  }
  EOF
  )

  iouTransactions=$(grpcurl -plaintext -d $iouQuery localhost:5031 com.daml.ledger.api.v1.TransactionService/GetTransactions)

**Buyer** receives these contracts from the stakeholders and adapts them to disclosed contracts (as described in :ref:`the previous section <submitter-disclosed-contract>`)
in a command submission that executes ``Offer_Accept`` on the ``offerCid``. The resulting gRPC command submission, which succeeds, is
shown below.

::

  # Extracted from the transaction lookup query results from above
  stockCid=$(echo "$stockTransactions" | jq -r '.transactions[0].events[0].created.contract_id')
  priceQuotationCid=$(echo "$priceQuotationTransactions" | jq -r '.transactions[0].events[0].created.contract_id')
  offerCid=$(echo "$offerTransactions" | jq -r '.transactions[0].events[0].created.contract_id')

  # The contract id of Buyer's IOU
  buyerIouCid=$(echo $iouTransactions | jq -r '.transactions[0].events[0].created.contract_id')

  stockCreatedEventBlob=$(echo "$stockTransactions" | jq -r '.transactions[0].events[0].created.created_event_blob')
  priceQuotationCreatedEventBlob=$(echo "$priceQuotationTransactions" | jq -r '.transactions[0].events[0].created.created_event_blob')
  offerCreatedEventBlob=$(echo "$offerTransactions" | jq -r '.transactions[0].events[0].created.created_event_blob')

  # Buyer exercises Offer_Accept on offerCid with populating the Command.disclosed_contracts field
  # with the data previously shared off-ledger for offerCid, stockCid and priceQuotationCid contracts
  exerciseOfferTransferCommand=$(cat <<EOF
  {
    "commands": {
      "ledger_id": "buyerParticipant",
      "workflow_id": "ExplicitDisclosureWorkflow",
      "application_id": "ExplicitDisclosure",
      "command_id": "ExplicitDisclosure-command",
      "party": "$buyerId",
      "commands": [
        {
          "exercise": {
            "template_id": {
              "package_id": "$packageId",
              "module_name": "StockExchange",
              "entity_name": "Offer"
            },
            "contract_id": "$offerCid",
            "choice": "Offer_Accept",
            "choice_argument": {
              "record": {
                "record_id": {
                  "package_id": "$packageId",
                  "module_name": "StockExchange",
                  "entity_name": "Offer_Accept"
                },
                "fields": [
                  {
                    "label": "priceQuotationCid",
                    "value": {
                      "contract_id": "$priceQuotationCid"
                    }
                  },
                  {
                    "label": "buyer",
                    "value": {
                      "party": "$buyerId"
                    }
                  },
                  {
                    "label": "buyerIou",
                    "value": {
                      "contract_id": "$buyerIouCid"
                    }
                  }
                ]
              }
            }
          }
        }
      ],
      "submission_id": "ExplicitDisclosure-submission",
      "disclosed_contracts": [
        {
          "template_id": {
            "package_id": "$packageId",
            "module_name": "StockExchange",
            "entity_name": "Stock"
          },
          "contract_id": "$stockCid",
          "created_event_blob": "$stockCreatedEventBlob"
        },
        {
          "template_id": {
            "package_id": "$packageId",
            "module_name": "StockExchange",
            "entity_name": "Offer"
          },
          "contract_id": "$offerCid",
          "created_event_blob": "$offerCreatedEventBlob"
        },
        {
          "template_id": {
            "package_id": "$packageId",
            "module_name": "StockExchange",
            "entity_name": "PriceQuotation"
          },
          "contract_id": "$priceQuotationCid",
          "created_event_blob": "$priceQuotationCreatedEventBlob"
        }
      ]
    }
  }
  EOF
  )

  grpcurl -plaintext -d $exerciseOfferTransferCommand localhost:5031 com.daml.ledger.api.v1.CommandService/SubmitAndWait
