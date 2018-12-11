<h1 class="contract">regcand</h1>
This human-language contract for the `eosio.arbitration` action `regcand` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **candidate** (account name of the candidate applying for an arbitrator position)

* **creds_ipfs_url** (ipfs hash link to the candidate's credentials)

### Intent

The intent of the {{regcand}} action is to register an account as an arbitrator candidate, to enumerate the obligations and rules of arbitrator candidacy and service, and to inform arbitrators about the penalties and penalty process for violation of these rules and obligations.

### 2. Nomination

I, {{candidate}}, hereby nominate myself for consideration as an Elected Arbitrator. This nomination includes the express agreement to all human-language terms of this contract by the arbitrator candidate entity and all of its owners. I attest that all disclosures I make as part of this nomination contract are true and that no important details have been omitted.

### 3. Disclosure of Arbitrator

If I, {{candidate}}, am selected to arbitrate a Case by the voter contract, I will sign messages with {{arbitrator_key}} and I hereby attest that I will keep this key secret and secure. If I suspect my key has been compromised, I will call this contract again with a new secure key.

### 4. Penalty Enforcement via Arbitration Tribunal

I, {{candidate}}, acknowledge that if I or a Judge within my entity fail to fulfill the obligations or violate the rules set forth in this contract, that arbitrator and/or said Judge may receive the penalties enumerated for the corresponding violation. The vehicle for this enforcement shall be an arbitration tribunal in which arbitrator and/or said Judge is named as the Respondent. If a majority of the judges of arbitration determine that the infraction did occur, then the associated penalty shall be imposed.

### 5. No Other Role

I, {{candidate}}, agree that I, and any owners, if {{arbitrator}} is an entity, shall not seek to serve in another role of trust on the Telos Blockchain Network such as block producer candidate or core developer during the time that I am a candidate for arbitrator. Violation of the preceding by any Judge, as judged by an arbitration tribunal, shall be cause for the disqualification of said Judge from all service as a judge of arbitration for 365 days on first offence or 3 years on second or subsequent offenses.

### 6. Resignation and Removal for Inability to Perform Obligations

If I, {{candidate}}, am unable to perform obligations under the human-language terms of this contract I will resign my position by executing the ‘unregarb’ action.

### 7. Recusal

Any time I, {{candidate}}, detect a conflict of interest, a family, personal, or business relationship with one or more party(s) of an arbitration, I shall recuse myself from service in that Case by using the recusal action of the ‘arbitration’ contract. I shall also recuse myself from a Case any time I receive attempts of undue influence regarding that Case from a terrestrial government or other entity that may have power over me. I shall not recuse myself from service for any other reason and shall endeavor to bring each Case to a just and timely resolution. Violation of the preceding by any Judge, as judged by an arbitration tribunal, shall be cause for the disqualification of said Judge from all service as a judge of arbitration for 365 days on first offence or 3 years on second or subsequent offenses.

### 8. Impartiality

I, {{candidate}}, agree to remain impartial and to conduct arbitration fairly and according to the documented practices of the selected rules of arbitration. I will seek to be consistent with precedents in similar Cases so as to apply a consistent application of the arbitration process. Violation of the preceding by any Judge, as judged by an arbitration tribunal, shall be cause for the disqualification of said Judge from all service as a judge of arbitration for 365 days on first offence or 3 years on second or subsequent offenses.

### 9. Ownership

I, {{candidate}}, attest under penalty of perjury that I hereby disclose all owners of my ownership entity and all shareholders who own more than 5%. When required by the Arbitrator Minimum Requirements, I shall also provide an identity verification hash from an accepted third-party identity verification service along with the name of that service. All owners of my ownership entity are listed herein: {owner{name}, (percentage}, (idprovider}, {idhash}}. No owner is currently under penalty for violating the human language terms of the regarbitrator contract. Violation of the preceding by Arbitrator, as judged by an arbitration tribunal, shall be cause for the disqualification of said Arbitrator and all associated Judges from all service as an arbitrator or judge of arbitration for 180 days on first offence or 2 years on second or subsequent offenses.

### 10. Arbitrator Personnel

I, {{candidate}}, attest that I, each registered arbitrator personnel listed herein meets the minimum requirements for a Telos Arbitrator Candidate and is proficient in the language or languages indicated. When required by the Arbitrator minimum requirements, I shall also provide an identity verification hash from an accepted third-party identity verification service along with the name of that service. All personnel of my ownership entity who shall serve as Arbitrators are listed herein: {personnel{name}, {(language}}, (idprovider}, {idhash}}. And no Judge is currently under penalty for violating the human language terms of the regarbitrator contract.  Violation of the preceding by Arbitrator, as judged by an arbitration tribunal, shall be cause for the disqualification of said Arbitrator and all associated Judges from all service as an arbitrator or judge of arbitration for 180 days on first offence or 2 years on second or subsequent offenses.

### 11. Amending Human-language Terms of ‘regarb’ Contract

I acknowledge that the human-language terms of this contract may be amended from time to time by TLOS owners voting on the ‘ratifyamend’ contract as described in the Telos Blockchain Network Operating Agreement. If I do not consent to the new terms of the amended human-language contract, I must remove myself from service as an arbitrator candidate. Remaining registered as an arbitrator candidate more than 180,000 blocks (approximately 24 hours) after the human-language terms are amended indicates my acceptance of the amended version.

### 12. Definitions

The term “Arbitrator” means an individual or entity such as an arbitration firm serving or seeking to serve in the role of a Judge, as defined below, of arbitration on the Telos Blockchain Network. The term “Judge” means an individual person within the Arbitrator entity who serves the role of a judge of arbitration. The “human-language terms” of a contract means the portion of a smart contract that is written in a human language such as English or Korean as opposed to a computer language such as C++, with the goal of clearly expressing the intent of the transaction between the user executing the contract and the person or entity that controls it. The term “second or subsequent offences” shall refer to violations of any offence described within the same paragraph of this contact’s human-language terms, but not to offences described in different paragraphs. A second or subsequent offence shall only apply if an arbitration tribunal imposed a penalty on a previous alleged offence.

<h1 class="contract">unregcand</h1>
This human-language contract for the `eosio.arbitration` action `unregcand` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **candidate** (account to be unregistered)

### Intent

The intention of the authors and the invoker of this contract is to the candidate's previously registered arbitrator application. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{candidate}} and that I intend to remove my previously registered application to serve as an arbitrator on Telos.

<h1 class="contract">initelection</h1>
This human-language contract for the `eosio.arbitration` action `initelection` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **signer** (account name of the signer - _implied parameter_)

### Intent

The intention of the authors and the invoker of this contract is to register a leaderboard-type election of arbitrator candidates by sending an inline action to the `regballot()` action on Trail. This will initialize the election with the proper values needed to hold an arbitrator election. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to initialize a new arbitrator election.


<h1 class="contract">candaddlead</h1>
This human-language contract for the `eosio.arbitration` action `candaddlead` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **candidate** (name of the account being added)

* **creds_ipfs_url** (url link to the candidate's credentials)

* **signer** (account name of the signer - _implied parameter_)

### Intent

The intention of the authors and the invoker of this contract is to add a single registered arbitrator candidate to a leaderboard-type election of arbitrator candidates prior to the start of voting. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to add the registered arbitrator candidate: {{candidate}} with credentials stored at {{creds_ipfs_url}} to the current arbitrator election.

<h1 class="contract">candrmvlead</h1>
This human-language contract for the `eosio.arbitration` action `candrmvlead` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

** **candidate** (name of the account being removed)

* **signer** (account name of the signer - _implied parameter_)

### Intent

The intention of the authors and the invoker of this contract is to remove a single registered arbitrator candidate from a leaderboard-type election of arbitrator candidates prior to the start of voting. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}} and that I intend to remove the registered arbitrator candidate: {{candidate}} from the current arbitrator election.

<h1 class="contract">endelection</h1>
This human-language contract for the `eosio.arbitration` action `endelection` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **candidate** (account calling the endelection action)

### Intent

The intention of the authors and the invoker of this contract is to end an arbitrator election that is no longer open for voting and finalize its results. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{candidate}} and that I intend to end an arbitrator election that is no longer open for voting so that its results may be finalized.
