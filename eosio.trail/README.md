# Trail Walkthrough

Trail offers a comprehensive suite of blockchain-based contract services.

## Voting and Ballot/Voter Registration

All users on the Telos Blockchain Network can register their account and receive a VoterID card that can be used in any Ballot or Election running on Trail. Developers can easily integrate with Trail by including the `traildef.voting.hpp` plugin in their contracts.

### Voting Actions

* `regvoter()`

    Calling regvoter will affiliate the given account_name with the given token symbol. Any user with an account_name may call regvoter, thereby allowing the given user to vote on any proposal or in any election powered by Trail.

* `unregvoter()`

    Calling unregvoter will remove the voter registration from the voters table. Since the user pays a small amount of RAM to register, calling unregvoter will reclaim the RAM spent on the registration.

* `regballot()`

    RegBallot is called to register a voting contract. After calling regballot, Trail will automatically begin tracking votes on any open proposal/election made by the contract.

* `unregballot()`

    Unregballot is called to remove a registered voting contract from the table. This will also cause Trail to stop propagating votes for the unregistered contract.

## Token Registration

Developers and organizations can author new and independent token contracts and then register their contract through Trail.

* `regtoken()`
* `unregtoken()`

## Trail Definitions

## Teclos Example Commands