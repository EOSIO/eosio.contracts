## Action - `{{ telos.tfvt.removemember }}`

This human-language contract for the `telos.tfvt` action `removemember()` is legally binding and can be used in the event of a dispute. Disputes shall be settled through arbitration by Telos Elected Arbitrators as described in the Telos Blockchain Network Operating Agreement and the Telos Blockchain Network Arbitration Rules and Procedures.

### Parameters

_**member_to_remove**_ - the account name of the board member to remove.

### Intent

The intention of the authors and the invoker of this contract is to allow a multi-sig group of Telos Foundation board members whose numbers satisfy the `major` permission of the `tf` account to remove a current board member from office. It shall have no other effect.

### Contract Text

I attest that I am the owner or authorized user of this account {{signer}}, and that I intend to  remove from office the Telos Foundation board member represented by the account {{member_to_remove}} and terminate all voting powers thereof, in accordance with the Telos Foundation Charter.
