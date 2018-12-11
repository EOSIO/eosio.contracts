## Action - `{{ telos.tfvt.closeissue }}`

This human-language contract for the `telos.tfvt` action `closeissue()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

_**holder**_ - the account calling to close the issue.

_**proposer**_ - the name of the account that proposed the issue.

### Intent

The intention of the authors and the invoker of this contract is to close an issue created through the `makeissue()` action, after voting has ended. It shall have no other effect.

### Contract Text

I attest that I am the owner or authorized user of this account {{holder}} and that I intend to close an issue created by the account: {{proposer}}, for which voting has ended, in accordance with the Telos Foundation Charter.
