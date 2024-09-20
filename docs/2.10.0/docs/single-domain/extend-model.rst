.. Copyright (c) 2024 Digital Asset (Switzerland) GmbH and/or its affiliates. All rights reserved.
.. SPDX-License-Identifier: Apache-2.0

Extend the Model
================

Extend the single domain quick start, beginning with the model. Daml choices determine how the backend API endpoints are written, which in turn guide the development of the frontend UI elements and event listeners.

Begin with an open terminal in the project's root directory. If you use `Visual Studio <https://code.visualstudio.com/docs/languages/java>`_, enter ``daml studio`` to open the text editor.

.. code-block:: bash

   daml-app-template ~ % daml studio

.. note::
   ``daml studio`` should automatically install the `Daml Studio <https://docs.daml.com/daml/daml-studio.html>`_ extension in Visual Studio. The extension assists Daml app development. You can double-check that the extension is installed by opening the extension menu and searching for 'Daml studio'.

   .. image:: images/daml-studio-extension.png

.. note::
   Intellij also supports Daml development.

The Daml Template
-----------------

Daml templates model business workflows. They enforce rules regarding the creation and management of contracts. Templates define a contract type, which can be instantiated and managed on the Daml ledger. 

Templates specify: 

- fields and data types that define the contract payload information upon creation
- `signatory <https://docs.daml.com/concepts/ledger-model/ledger-integrity.html#signatories-agreements-and-maintainers>`_, whose authorization is required for the creation of the contract
- choices, which are actions that a `controller <https://docs.daml.com/daml-finance/reference/code-documentation/daml-finance-rst/Daml-Finance-Account-Account.html#module-daml-finance-account-account-19369#v:controllers>`_ can take on a contract

**Create a RejectedTransferOffer Template**

1. Find 'Model.daml' in /app/daml/src/main/daml/Com/Daml/App/Template/. 

   .. image:: images/daml-model-file-tree.png
      :width: 250px

2. Find the template 'TransferOffer' in Model.daml.

3. Write a new RejectedTransferOffer template directly above the currently existing template TransferOffer. The new template is a composite of the TransferOffer template that extends the ability for providers, senders, and receivers to reject a transfer offer with a reason. 

   .. code-block:: daml
      :linenos:
      :lineno-start: 167

         template RejectedTransferOffer
         with
            transferOffer : TransferOffer
            rejectionReason : Text
         where
            signatory transferOffer.provider, transferOffer.sender, transferOffer.receiver

            ensure rejectionReason /= ""

            key (transferOffer.provider, transferOffer.sender, transferOffer.receiver, transferOffer.trackingId) : (Party, Party, Party, Text)
            maintainer key._1

   The template takes a transfer offer and a rejection reason, a non-empty string, requires a transfer offer with a provider, sender, and receiver, and creates an identifier key for each rejection. 

   ``signatory transferOffer.provider…`` uses dot notation to maintain a direct link to the original offer. This format ensures that the Parties are identified consistently across related contracts.

   ``maintainer key._1`` indicates that the provider is responsible for maintaining the contract. 

4. Create a new RejectWithReason choice within the TransferOffer template:

   .. code-block:: daml
      :linenos:
      :lineno-start: 218

         choice RejectWithReason : (ContractId RejectedTransferOffer, ContractId Transferable.I)
         with
            reason : Text
         controller receiver
         do
            now <- getTime
            assertMsg "The transfer offer has expired and cannot be rejected" (now < expiresAt)
            rejectedOfferCid <- create RejectedTransferOffer with
               transferOffer = this
               rejectionReason = reason
            unlockedCid <- unlockAndRemoveObservers (S.fromList [provider, sender]) receiver lockedTransferableCid
            return (rejectedOfferCid, unlockedCid)

   This choice takes a reason for the rejection, and ensures that the receiver controls the choice and that the transfer offer contract has not expired. When the choice is exercised a new "RejectedTransferOffer" contract is created that subsequently unlocks the assets that were to be transferred, and removes the provider and sender as observers. This choice contains a handful of interesting Daml-specific items:

   - ``controller receiver`` specifies that only the receiver of the transfer offer can exercise this choice.
   - ``now <- getTime`` fetches the current time on the ledger. 

     .. note::
        In a dev environment without an active ledger, the `getTime <https://docs.daml.com/concepts/time.html>`_ function returns the epoch time, January 1, 1970. This happens because the ledger is not active and cannot fetch the system time. In a Daml application deployed to an active ledger, getTime fetches the current ledger time, which reflects the time that the ledger itself is using.

   - ``assertMsg`` `asserts <https://docs.daml.com/daml/stdlib/Prelude.html#function-da-internal-assert-assertmsg-31545>`_ the current time is less than the time of the expiresAt value. The assertion fails and the transaction is aborted if the value of now is later than or equal to the time value of expiresAt.
   - ``unlockAndRemoveObservers`` removes the receiver. When the receiver rejects the offer they are no longer a stakeholder in the transaction and have no need to observe the contract. The function call also unlocks the credits reserved for the transaction.

At this point, the extension features a new template, RejectedTransferOffer, that allows for a rejection reason. It also implements a new choice, RejectWithReason within the TransferOffer template, which takes a reason and creates the RejectedTransferOffer contract. 

Canton needs to be stopped and the caches cleared to ensure the model rebuilds properly. 

1. Quit and restart the terminals to terminate the processes. 

2. Navigate to the project's root directory, then run the stop-canton script to clean the Docker containers:

   .. code-block:: bash

      ./scripts/stop-canton.sh

   .. image:: images/terminal-stop-daml-script.png

3. Clear Gradle's cache:

   .. code-block:: bash

      ./gradlew clean

   .. image:: images/terminal-gradlew-clean.png

4. Clear the frontend servers:

   .. code-block:: bash

      ./gradlew :app:frontend:clean

   .. image:: images/terminal-gradlew-frontend-clean.png

5. Rebuild the DAR files:

   .. code-block:: bash

      ./gradlew :app:daml:assemble

   If the choices have been added correctly, the DARs should update with the new choices in the TransferOffer template.

   .. image:: images/terminal-gradlew-daml-assemble.png

You have implemented the new RejectedTransferOffer template and RejectWithReason choice in Model.daml. This extension allows users greater control over their transfer offers. The next step integrates the new choices into the backend API to interact with the Daml ledger.