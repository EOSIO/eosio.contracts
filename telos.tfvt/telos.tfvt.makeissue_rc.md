## Action - `{{ telos.tfvt.makeissue }}`

This human-language contract for the `telos.tfvt` action `makeissue()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

_**holder**_ - the account making the issue.

_**info_url**_ - the info link for the campaign.

_**issue_name**_ - the name of the issue as an account name.

_**transaction**_ - the transaction to send if the issue proposal passes.

### Intent

The intention of the authors and the invoker of this contract is to create a proposal on Trail Service that is votable on by TFVT holders. It shall have no other effect.

### Contract Text

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to create an issue proposal called, {{issue_name}} with a link to further information here: {{info_url}}. If this issue is passed by a vote of the TFVT holders, then {{issue_name}} will receive the following transaction: {{transaction}} in accordance with the Telos Foundation Charter.
