## Smart Contract - `{{ telos.tfvt }}`

This human-language contract for the `{{ telos.tfvt }}` smart contract is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Intent

This smart contract was designed to be used in managing voting functions for the Telos Foundation, including creating and closing issues to be voted which end in some form of transaction if sucessful, and creating leaderboard-type elections for Telos Foundation board members. This smart contract is intended to manage nominating an accountholder to stand for election, creating the election, adding and removing candidates prior to the start of voting, and to close out the election when voting has concluded. Finally, this smart contract is intended to allow a multi-sig group of Telos Foundation board members whose numbers satisfy the `major` permission of the `tf` account to remove a current board member from office. It shall have no other effect.


### Actions and Inputs

This smart contract has eight actions: `nominate()`, `makeissue()`, `closeissue()`, `makeelection()`, `addcand()`, `removecand()`, `endelection()` and `removemember()`. 

#### Action: `nominate()` 

Purpose: To nominate an accountholder to stand for election as a Telos Foundation board member.

Input | Input Type | Description
------|------------|------------
_**nominee**_ | name | The account name of the account-holder being nominated
_**nominator**_ | name | The account name of the account-holder who is nominating. This account must contain a TFVT or TFBOARD token.

#### Action: `makeissue()`

Purpose: To create a proposal on Trail Service that is votable on by TFVT holders.

Input | Input Type | Description
------|------------|------------
_**holder**_ | name | The account making the issue.
_**info_url**_ | string | The account name of the account-holder who is nominating. This account must contain a TFVT or TFBOARD token.
_**issue_name**_ | name | The account name of the account-holder being nominated
_**transaction**_ | transaction | The account name of the account-holder who is nominating. This account must contain a TFVT or TFBOARD token.

#### Action: `closeissue()`

Purpose: To close an issue created through the `makeissue()` action, after voting has ended. 

Input | Input Type | Description
------|------------|------------
_**holder**_ | name | The account calling to close the issue.
_**proposer**_ | name | The name of the account that proposed the issue.

#### Action: `makeelection()`

Purpose: To create a leaderboard-type election on the Trail Service to elect Telos Foundation board members through TFVT voting.

Input | Input Type | Description
------|------------|------------
_**holder**_ | name | The account making the leaderboard-type election.
_**info_url**_ | string | The info link for the campaign.

#### Action: `addcand()`

Purpose: To add a nominee to the list of candidates on an existing leaderboard-type election in the Trail Service, prior to the start of voting.

Input | Input Type | Description
------|------------|------------
_**candidate**_ | name | The account making the issue.
_**info_link**_ | string | The  link to the nominee's campaign information.

#### Action: `removecand()`

Purpose: To remove a nominee from the list of candidates on an existing leaderboard-type election in the Trail Service, prior to the start of voting.

Input | Input Type | Description
------|------------|------------
_**candidate**_ | name | The name of the account for the nominee being removed from the election.

#### Action: `endelection()`

Purpose: To end a completed leaderboard-type election that was created by the `makeelection()` action, finalizing election results, resolving any ties and launching a runoff election for seats that still remain open.

Input | Input Type | Description
------|------------|------------
_**holder**_ | name | The name of the account invoking `endelection()`.

#### Action: `removemember()`

Purpose: To allow a multi-sig group of Telos Foundation board members whose numbers satisfy the `major` permission of the `tf` account to remove a current board member from office.

Input | Input Type | Description
------|------------|------------
_**member_to_remove**_ | name | The account name of the board member to remove.

### Contract Text

I attest that I am the owner or authorized user of this account {{signer}}, and that I intend to manage voting functions for the Telos Foundation, including creating and closing issues to be voted which end in some form of transaction if sucessful, and creating leaderboard-type elections for Telos Foundation board members, or to manage nominating an accountholder to stand for election, creating the election, adding and removing candidates prior to the start of voting, and to close out the election when voting has concluded, or to allow a multi-sig group of Telos Foundation board members whose numbers satisfy the `major` permission of the `tf` account to remove a current board member from office. All in accordance with the Telos Foundation Charter.
