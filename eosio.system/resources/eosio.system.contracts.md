<h1 class="contract">regproducer</h1>

## Description

This human-language contract for the `eosio.system` action `regproducer()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

[Telos “regproducer” - Chinese language](https://web.ipfs.telosfoundation.io/QmfBsDyyfjcmjJB66jB6k547itK9EkbVD95Xhqp7MxBmpJ) 

[Telos "regproducer" - Korean language](https://web.ipfs.telosfoundation.io/QmbobxTH2xrMJnqKfKwd3wtv8LtvFeUcD5mxb3NAebuQyq)  

### Parameters

_**producer**_ is the name of the block producer account executing this contract.

_**producer_key**_ is the public key to be used in signing all blocks produced by the block producer executing this contract.

### 1. Intent of Action  -  `{{ regproducer }}`

The intent of the `{{ regproducer }}` action is to register an account as a block producer candidate, to enumerate the obligations and rules of block producer candidacy and operation, and to inform producers about the penalties and penalty process for violation of these rules and obligations.

### 2. Nomination

I, {{ producer }}, hereby nominate myself for consideration as an elected block producer. This nomination includes the express agreement to all terms of this human-language contract by the block producer candidate entity and all of its owners.

### 3. Disclosure of Producer Key

If {{ producer }} is selected to produce blocks by the “eosio” contract, I will sign blocks with {{ producer_key }} and I hereby attest that I will keep this key secret and secure. If I suspect my key has been compromised, I will call this contract again with a new secure key.

### 4. Disclosure of Entity and Server Information

I, {{ producer }}, acknowledge that I have disclosed accurate information about my block producer entity and server location(s). Server location data is accurate to within two degrees of latitude and longitude. The country of domicile of my ownership entity, expressed as a 2-letter ISO code is {{ entity_domicile_country }}. The location(s) or my block producer server(s) is {{ location_name }}, location country, expressed as a 2-letter ISO code is {{ server_location_country }}. The location of my block producer server(s), expressed as latitude and longitude is {{ server_location_latitude }}, {{ server_location_longitude }}.

### 5. Penalty Enforcement via “enforcebprules” Contract

I, {{ producer }}, acknowledge that if I fail to fulfill the obligations or violate the rules set forth in this contract, that the other block producers shall impose upon me the penalties enumerated for the corresponding violation. The vehicle for this enforcement shall be the “enforcebprules” contract which may be executed by any block producer to allege a violation of the rules and present evidence of the violation. The “enforcebprules” contract shall alert me if I am accused of a violation and I will have a maximum of 50,000 blocks (approximately seven hours) to post a rebuttal to the evidence presented against me prior to other block producers voting. If a 2/3+1 majority of elected block producers votes that they are convinced the infraction did occur, then the associated penalty shall be imposed.

### 6. Obligation to Enforce Block Producer Rules

I, {{ producer }}, acknowledge that at any time I serve as a block producer, I shall enforce the rules and associated penalties set forth in this human-language contract when another block producer reports evidence of an alleged violation in the form of executing the “enforcebprules” contract. When “enforcebprules” is executed by any block producer, I have the obligation to assess all evidence presented both by the accuser and the accused and vote whether the evidence persuades me that the alleged infraction has occurred. I shall, within 100,000 blocks (approximately 14 hours) of the contract being first executed in the case, cast a definitive yes or no vote via the “enforcebprules” contract as to whether I am convinced the violation occurred. Failure to vote within 100,000 blocks shall place me in violation of the block producer minimum requirements until either I vote, or the “enforcebprules” contract is enacted by a majority of 2/3+1 of all block producers. If I discover evidence of a violation of this human-language contract by another block producer, I am obligated to execute the “enforcebprules” contract and provide evidence of the alleged violation as quickly as I may fully investigate and collect evidence.

### 7. Resignation and Removal for Inability to Perform Obligations

If {{ producer }} is unable to perform obligations under this human-language contract I will resign my position by resubmitting this contract with the null producer key. If {{ producer }} fails to resign when unable to perform said obligations, {{ producer }} shall be removed by automated contract or by actions of the remaining block producers. {{ producer }} may be removed at any time when it fails to produce 15% or more of its assigned blocks in a rotation of the block producer scheduling routine, or when 1/3–1 block producers are failing to produce blocks on the current schedule and {{ producer }} is the block producer with the highest number of missed blocks or the lowest percentage of Member votes among the group of block producers that is failing to produce blocks.

### 8. Objectively Valid and Invalid Blocks

I, {{ producer }}, acknowledge that a block is “objectively valid” if it conforms to the deterministic blockchain rules in force at the time of its creation, and is “objectively invalid” if it fails to conform to those rules.

### 9. Signing of Messages with Producer Key

I, {{ producer }}, hereby agree to only use {{producer_key}} to sign messages under the following scenarios: proposing an objectively valid block at the time appointed by the block scheduling algorithm, pre-confirming a block produced by another producer in the schedule when I find said block objectively valid, confirming a block for which {{ producer }} has received 2/3+1 pre-confirmation messages from other producers. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 16,000,000 blocks (approximately 90 days) on first offence or 63,000,000 blocks (approximately 365 days) on second or subsequent offenses. I may also be liable for liabilities due to this action.

### 10. Acceptance of Liability and Damages

I, {{ producer }}, hereby accept liability for any and all provable damages that result from my: signing two different block proposals with the same timestamp with {{producer_key}}, signing two different block proposals with the same block number with {{producer_key}}, signing any block proposal which builds off of an objectively invalid block, signing a pre-confirmation for an objectively invalid block, signing a confirmation for a block for which I do not possess pre-confirmation messages from 2/3+1 other producers. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 16,000,000 blocks (approximately 90 days) on first offence or 63,000,000 blocks (approximately 365 days) on second or subsequent offenses. I may also be liable for damages due to this action.

### 11. Malicious Collusion

I, {{ producer }}, hereby agree that double-signing for a timestamp or block number in concert with 2 or more other producers shall automatically be deemed malicious and subject to a fine equal to the past year of compensation received, and other damages. An exception may be made if {{ producer }} can demonstrate that the double-signing occurred due to a bug in the reference software; the burden of proof is on {{ producer }}. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 63,000,000 blocks (approximately 365 days) on first offence or 315,000,000 blocks (approximately 5 years) on second or subsequent offenses.

### 12. Interference with Block Producer Election Process

I, {{ producer }}, hereby agree not to interfere with the producer election process. I agree to process all producer election transactions that occur in blocks I create, to sign all objectively valid blocks I create that contain election transactions, and to sign all pre-confirmations and confirmations necessary to facilitate transfer of control to the next set of producers as determined by the system contract. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for shall be cause for my disqualification from all service as a block producer for 16,000,000 blocks (approximately 90 days) on first offence or 63,000,000 blocks (approximately 365 days) on second or subsequent offenses.

### 13. Adherence to Block Producer Minimum Requirements

I, {{ producer }}, hereby acknowledge that violation of the Telos Block Producer Minimum Requirements shall be cause for disqualification from service of {{ producer }} as a block producer until {{ producer }} is once again in compliance. Compliance shall be monitored and enforced by smart contract, oracle, other objective, or disinterested party as the network developers shall initially designate on network launch or subsequently amend. The current Telos Block Producer Minimum Requirements shall be recorded on chain at a publicly disclosed address.

### 14. Authentication of Network Peers

The community agrees to allow {{ producer }} to authenticate peers as necessary to prevent abuse and denial of service attacks; however, {{ producer }} agrees not to discriminate against non-abusive peers. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 5,000,000 blocks (approximately 29 days) on first offence or 32,000,000 block (approximately 180 days) on second or subsequent offenses.

### 15. Fair Dealing in Processing Transactions

I, {{ producer }}, agree to process transactions on a first-in, first-out, best-effort basis and to honestly bill transactions for measured execution time. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 5,000,000 blocks (approximately 29 days) on first offence or 32,000,000 block (approximately 180 days) on second or subsequent offenses.

### 16. No Reordering Transactions to Profit

I, {{ producer }}, agree not to manipulate the contents of blocks in order to derive profit from the order in which transactions are included in the hash of the block that is produced. Apparent intentional violation of the preceding, as judged by a 2/3+1 majority of all block producers,shall be cause for my disqualification from all service as a block producer for 16,000,000 blocks (approximately 90 days) on first offence or 63,000,000 blocks (approximately 365 days) on second or subsequent offenses.

### 17. Ownership

I, {{ producer }}, hereby agree to disclose and attest under penalty of perjury all ultimate beneficial owners of my ownership entity who own more than 5% and all direct shareholders. When required by the Telos Block Producer Minimum Requirements, I shall also provide an identity verification hash from an accepted third-party identity verification service along with the name of that service. All owners of my ownership entity are listed herein:{{owner{name}, (percentage}, (idprovider}, {idhash}}. I will not misrepresent ownership or the penalty status of any owners in an attempt to evade penalties. No owner is currently under penalty for violating the human language terms of the “regproducer” contract. Misrepresentation includes misspelling or using an alternate writing of the same person or entity’s name, listing the name of an entity owned or controlled by more than 5% of a listed owner, or by listing the name of any person or entity who is not the true beneficial owner or their fiduciary. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 16,000,000 blocks (approximately 90 days) on first offence or 63,000,000 blocks (approximately 365 days) on second or subsequent offenses.

### 18. Ownership of More than One Block Producer

I, {{ producer }}, acknowledge that no entity, whether an individual, corporation, nonprofit, or decentralized organization, shall own any interest in more than one block producer candidate at any time. For the purpose of this paragraph, spouses, parents, children and siblings of an owner shall be considered the same as the owner. Any block producer with any owner currently under penalty by the “enforcebprules” contract is disqualified for the entire term of the penalty.

### 19. Producing Blocks on Schedule

I, {{ producer }}, agree not to produce blocks before my scheduled time unless I have received all blocks produced by the prior producer. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 5,000,000 blocks (approximately 29 days) on first offence or 32,000,000 block (approximately 180 days) on second or subsequent offenses.

### 20. Producing Blocks on Accurate Time

I, {{ producer }}, agree not to publish blocks with timestamps more than 500ms in the past or future unless the prior block is more than 75% full by either CPU or network bandwidth metrics. Apparent intentional or negligent violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 5,000,000 blocks (approximately 29 days) on first offence or 32,000,000 block (approximately 180 days) on second or subsequent offenses.

### 21. Setting Accurate RAM Supply

I, {{ producer }}, agree not to set the RAM supply to more RAM than my block producing nodes can currently support. Apparent intentional violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer for 5,000,000 blocks (approximately 29 days) on first offence or 32,000,000 block (approximately 180 days) on second or subsequent offenses.

### 22. Voter-confusing Block Producer Names

I, {{ producer }}, agree not to register a block producer name intended or deemed likely to create confusion among Telos voters as to their identity compared to other Telos block producers. Priority of names will be granted to the block producer candidate who first registered on the Telos network or Telos pre-launch testnet. Until the Telos network has been activated for six months, the same priority will be granted to block producer candidates who registered a block producer name during the first 30 days of the original EOS mainnet. Violation of the preceding, as judged by a majority of 2/3+1 of all block producers, shall be cause for my disqualification from all service as a block producer until a new block producer name is registered. There shall be no further penalty for this violation.

### 23. Amending “regproducer” Human-language Contract

I, {{ producer }}, acknowledge that the terms of this human-language contract may be amended from time to time by Telos owners voting on the “ratifyamend” contract as described in the Telos Network Operating Agreement. If I do not consent to the new terms of the amended human-language contract, I must remove my block producer candidate from service. Remaining registered as a block producer more than 180,000 blocks (approximately 25 hours) after this human-language contract is amended indicates my acceptance of the new version.

### 24. Definitions

The term “block producer” shall be deemed to mean one of the up to 21 block producer candidates actually validating transactions on the Telos network, including any non-elected block producer candidate serving the validating function due to the failure of another block producer, or rotation schemes intended to aid network health, or any other reason. The term “second or subsequent offences” shall refer to violations of any offence described within the same paragraph of this human-language contract, but not to offences described in different paragraphs. A second or subsequence offence shall only apply if a majority of 2/3+1 block producers voted to impose a penalty on a previous alleged offence. A majority of “2/3+1” shall mean a number greater than or equal to 2/3rds of the total number plus one additional. For clarity, when the total is 21 block producers, a 2/3+1 majority would require the votes of 15 block producers. A “human-language contract” means the portion of a smart contract that is written in a human language such as English or Korean as opposed to a computer language such as C++, with the goal of clearly expressing the intent of the transaction between the user executing the contract and the person or entity that controls it. An “accepted third-party verification service” means a service or entity providing identification verification as a cryptographic hashed value that is listed on a list maintained on-chain by the Telos Block Producers and amended by a vote of 2/3+1 Block Producers. The “‘regproducer’ contract” means any Telos system contract or contracts that is designed to nominate an entity as a block producer candidate, whether or not the contract is actually named “regproducer”. The “‘enforcebprules’ contract” means any Telos system contract or contracts that is designed to enforce the Block Producer Minimum Requirements or “regproducer” contract, whether or not the contract is actually named “enforcebprules”. The “‘ratifyamend’ contract” means any Telos system contract or contracts that is designed to allow Telos Members to ratify or amend any of the Telos Governance Documents, whether or not the contract is actually named “ratifyamend”. The terms “‘eosio’ contract” and “system contract” mean the core operating system contract or contracts of the Telos EOSIO system, whether or not the contract is actually named “eosio”.
