# Trail Service User/Developer Guide

Trail offers a comprehensive suite of blockchain-based voting services available to any prospective voter or contract developer.

Developers can easily interface with Trail by including the `trail.voting.hpp` plugin in their contracts. The following sections outline how users and developers can leverage Trail's voting systems to run nearly any type of election or ballot, while being confident in the accuracy and transparency of every vote cast. 

Additionally, Trail was developed to withstand every known method of fraudulent voting (and even some new ones that only happen on the blockchain). Trail has a 3-tiered approach to combating voter fraud, which is explained in further detail farther down this document.

## Ballot Lifecycle

Building a ballot on Trail is very simple and gives great flexibility to the developer to build their ballots in any structure they desire. An example ballot and voting contract will be used throughout this guide, and is recommended as an established model for Trail interface best practices. The following steps should be seen as general guidelines, and do not necessarily have to happen in order:

### Understanding Trail's Role

Trail was designed to allow maximum flexibility for smart contract developers, while at the same time consolidating many of the boilerplate functions of voting contracts into a single service. 

This paradigm means contract writers can leave the "counting parts" up to Trail and instead focus on what they want their ballot results to mean. Through cross-contract table lookup, any contract can view the results of a ballot or election and then have their contracts make decisions based on those results.

Trail ballots and elections are also stored indefinitely, allowing lookup throughout the entire history of the service. 

### 1. Setting Up Your Contract (Optional)

While setting up an external contract is not required to utilize Trail's services, it is required if developers want to **contractually** act on ballot results. If you aren't interested in having a separate contract and just want to run a ballot, then proceed to number 2.

For our contract example, we will be making a simple document updater where updates are voted on by the community. The basic interface looks like this:

* `createdoc(string doc_title, vector<string> paragraphs)`

    The createdoc action will create a new document, retrievable by a document id. The text of the document is stored as a series of strings, where the vector key is mapped to the paragraph number.

* `makeproposal(uint64_t doc_id, string new_paragraph)`

    The makeproposal action stores the new paragraph retrievable by a proposal id, after first making sure the associated document exists. No vote counts are stored for this proposal (remember, that's Trail's job).

* `linkballot(uint64_t prop_id, uint64_t ballot_id)`

    The linkballot action will link a proposal to an existing ballot in Trail. The proposal object has a field `ballot_id` which this action updates with the associated ballot id. This step isn't strictly necessary, but is a nice way to have a quick reference of which ballots your proposals are targeting.

* `closeballot(uint64_t prop_id)`

    The closeballot action is important for performing custom logic on ballot results, and simply sends an inline action to Trail's `closevote()` action upon completion. The `status` field of the ballot allows ballot closers the ability to assign any meaning to status codes they desire. For example, a voting contract could interpret a status code of `7` to mean `REFUNDED`. However, status codes `0`, `1`, and `2` are reserved for meaning `OPEN`, `PASS`, and `FAIL`, respectively.

### 2. Ballot Registration

Ballot regisration allows any user or developer to create a public ballot that can be voted on by any registered voter. 

* `regballot(name publisher, symbol voting_symbol, uint32_t begin_time, uint32_t end_time, string info_url)`

    The regballot action will register a new ballot with attributes reflecting the given parameters.

    `publisher` is the account publishing the ballot. Only this account will be able to modify and close the ballot.

    `voting_symbol` is the symbol to be used for counting votes. This is typically TLOS.

    `begin_time` and `end_time` are the beginning and end time of the ballot  measured in seconds. Any vote for the ballot can be cast between these two times (inclusive). The current time in seconds can be retrieved from Trail's `environment` singleton, however this value only updates when Trail receives an action so this value may be off depending on when it was last modified. Simply querying for this value will not update it.

    `info_url` is critical to ensuring voters are able to know exactly waht they are voting on when they cast their votes. This parameter can simply be a url to a webpage (or even better, an IPFS hash) that explains what the ballot is for, and should provide sufficient information for voters to make an informed decision. Since some ballots will host this information on their own smart contract, this can simply be a pointer to that information as well. However, in order to ensure knowledgable voting, this field should never be left blank. Without providing a link to this information, any malicious actor could launch a misinformation campaign to confuse potential voters. Don't let malicious users hijack your ballot!

* `unregballot(name publisher, uint64_t ballot_id)`

    The unregballot action removes a ballot from the blockchain. This action can only be performed before a ballot opens for voting. Ballots cannot be unregistered after voting has begun.

    `publisher` is the account that published the ballot. Only this account can unregister the ballot.

    `ballot_id` is the ballot ID of the ballot to unregister.

### 3. Running A Ballot 

After ballot setup is complete, the only thing left to do is wait for the ballot to open and begin receiving votes. Votes cast on the ballot are live, so it is very easy to see the state of the ballot as votes roll in. There are also a few additional features available for ballot runners that want to operate a more complex campaign. This feature set will grow with the development of Trail and as more complex versions of ballots are introduced to the system.

* `nextcycle(name publisher, uint64_t ballot_id, uint32_t new_begin_time, uint32_t new_end_time)`

    The nextcycle action is used to manage voting campaigns that operate in stages. Calling nextcycle will reset the ballot with new begin and end times, as well as reset the vote counts.

    `publisher` is the account that published the ballot. Only this account is authorized to call nextcycle.

    `ballot_id` is the ballot ID of the ballot to recycle.

    `new_begin_time` and `new_end_time` are the new beginning and end times of the new cycle. The time format is the same as registering the ballot initially.

### 4. Closing A Ballot

After a ballot has reached it's end time, it will automatically stop accepting votes. The final tally can be seen by querying the `ballots` table with the relevent ballot ID.

* `closevote(name publisher, uint64_t ballot_id, uint8_t pass)`

    The closevote action is how ballot publishers close out a ballot and render a decision based on the results.

    `publisher` is the publisher of the ballot. Only this account can close the ballot.

    `ballot_id` is the ballot ID of the ballot to close.

    `pass` is the resultant ballot status after reaching a verdict on the votes. This number can represent any end state desired, but `0`, `1`, and `2` are reserved for `OPEN`, `PASS`, and `FAIL` respectively.

## Voter 

* `mirrorstake()` 

    `mirrorstake` is the fundamental 

* `castvote`


* `deloldvotes`



### Voter Registration

All users on the Telos Blockchain Network can register their accounts and receive a VoterID card that's valid for any Ballot or Election running on Trail. 

* `regvoter()`

    Calling the regvoter action will assign a Voter ID to the given `member` account and save it to the voters table. 

* `unregvoter()`

    The unregvoter() action will remove the `voter` from the voters table. 

### Getting and Casting Votes
