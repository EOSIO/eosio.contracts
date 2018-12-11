<h1 class ="contract">addcand</h1>
This human-language contract for the `telos.tfvt` action `addcand()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **candidate** (name of the account for the nominee being added to the election)

* **info_link** (a link to the nominee's campaign information)

### Intent

The intention of the authors and the invoker of this contract is to add a nominee to the list of candidates on an existing leaderboard-type election in Trail, prior to the start of voting. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to add the candidate who owns the account {{candidate}} to a leaderboard-type election with a campaign information page at this link: {{info_link}}, in accordance with the Telos Foundation Charter.

<h1 class ="contract">closeissue</h1>
This human-language contract for the `telos.tfvt` action `closeissue()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **holder** (account calling to close the issue)

* **proposer** (name of the account that proposed the issue)

### Intent

The intention of the authors and the invoker of this contract is to close an issue created through the `makeissue()` action, after voting has ended. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to close an issue created by the account: {{proposer}}, for which voting has ended, in accordance with the Telos Foundation Charter.

<h1 class ="contract">endelection</h1>
This human-language contract for the `telos.tfvt` action `endelection()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **holder** (name of the account invoking `endelection()`)

### Intent

The intention of the authors and the invoker of this contract is to end a completed leaderboard-type election that was created by the `makeelection()` action, finalizing election results, resolving any ties and launching a runoff election for seats that still remain open. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to  end a completed leaderboard-type election, finalizing its results and launching a runoff election if there are unresolved seats remaining open, in accordance with the Telos Foundation Charter.

<h1 class ="contract">makeelection</h1>
This human-language contract for the `telos.tfvt` action `makeelection()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **holder** (account making the leaderboard-type election)

* **info_url** (info link for the campaign)

### Intent

The intention of the authors and the invoker of this contract is to create a leaderboard-type election on the Trail Service to elect Telos Foundation board members through TFVT voting. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to  create a leaderboard-type election with a link to campaign information here: {{info_url}} on the Trail Service to elect Telos Foundation board members through TFVT voting, in accordance with the Telos Foundation Charter.

<h1 class ="contract">makeissue</h1>
This human-language contract for the `telos.tfvt` action `makeissue()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **holder** (account making the issue)

* **info_url** (info link for the campaign)

* **issue_name** (name of the issue as an account name)

* **transaction** (transaction to send if the issue proposal passes) 

### Intent

The intention of the authors and the invoker of this contract is to create a proposal on Trail Service that is votable on by TFVT holders. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to create an issue proposal called, {{issue_name}} with a link to further information here: {{info_url}}. If this issue is passed by a vote of the TFVT holders, then {{issue_name}} will receive the following transaction: {{transaction}} in accordance with the Telos Foundation Charter.

<h1 class ="contract">nominate</h1>
This human-language contract for the `telos.tfvt` action `nominate()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **nominee** (account name of the account-holder being nominated)

* **nominator** (account name of the account-holder who is nominating -  account must contain a TFVT or TFBOARD token)

### Intent

The intention of the authors and the invoker of this contract is to nominate an accountholder to stand for election as a Telos Foundation board member. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{nominator}} and that I intend to nominate the owner of the account: {{nominee}} to stand for election as a Telos Foundation board member in accordance with the Telos Foundation Charter.

<h1 class ="contract">removecand</h1>
This human-language contract for the `telos.tfvt` action `removecand()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **candidate** (name of the account for the nominee being removed from the election)

### Intent

The intention of the authors and the invoker of this contract is to remove a nominee from the list of candidates on an existing leaderboard-type election in the Trail Service, prior to the start of voting. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to  remove the candidate who owns the account {{candidate}} from a leaderboard-type election, in accordance with the Telos Foundation Charter.

<h1 class ="contract">removemembe</h1>
This human-language contract for the `telos.tfvt` action `removemember()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

* **member_to_remove** (account name of the board member to remove)

### Intent

The intention of the authors and the invoker of this contract is to allow a multi-sig group of Telos Foundation board members whose numbers satisfy the `major` permission of the `tf` account to remove a current board member from office. It shall have no other effect.

### Body

I attest that I am the owner or authorized user of this account {{signer}}, and that I intend to  remove from office the Telos Foundation board member represented by the account {{member_to_remove}} and terminate all voting powers thereof, in accordance with the Telos Foundation Charter.
