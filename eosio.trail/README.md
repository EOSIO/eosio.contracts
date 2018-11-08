# Trail Service User Guide

Trail offers a comprehensive suite of blockchain-based voting services available to any prospective voter or contract developer.

Developers can easily integrate with Trail by including the `trail.voting.hpp` plugin in their contracts.

## Voter Registration

All users on the Telos Blockchain Network can register their account and receive a VoterID card that can be used in any Ballot or Election running on Trail. 

* `regvoter()`

    Calling regvoter() will assign a Voter ID to the `member` account and save it to the voters table. 

* `unregvoter()`

    The unregvoter() action will remove the `voter` from the voters table. 

## Ballot Registration

* `regballot()`

    The regballot() action will register a new ballot to the `ballots` table.

    * 

* `unregballot()`

    

* `mirrorstake` 



* `castvote`



* `nextcycle`



* `deloldvotes`



* `closevote`



## Token Registration

Developers and organizations can author new and independent token contracts and then register the token contract through Trail.

* `regtoken()`



* `unregtoken()`



## Trail Definitions


