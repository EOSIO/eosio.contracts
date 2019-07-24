## Introducing eosio.system contract

The `eosio.system` contract is another smart contract that Block.one provides an implementation for as a sample system contract.  It is a version of `eosio.bios` only this time it is not minimalist, it contains more elaborated structures, classes, methods, and actions needed for an EOSIO based blockchain core functionality:
- Users can stake tokens for CPU and Network bandwidth, and then vote for producers or delegate their vote to a proxy.
- Producers can register in order to be voted for, and can claim per-block and per-vote rewards.
- Users can buy and sell RAM at a market-determined price.
- Users can bid on premium names.
- A resource exchange system, named REX, allows token holders to lend their tokens, and users to rent CPU and NET resources in return for a market-determined fee.

The actions implemented and publicly exposed by the `eosio.system` system contract are presented in the table below. Just like the `eosio.bios` sample contract there are a few actions which are not implemented at the contract level (`newaccount`, `updateauth`, `deleteauth`, `linkauth`, `unlinkauth`, `canceldelay`, `onerror`, `setabi`, `setcode`), they are just declared in the contract so they will show in the contract's ABI and users will be able to push those actions to the chain via the account holding the 'eosio.system' contract, but the implementation is at the EOSIO core level. They are referred to as EOSIO native actions.

|Action name|Action description|
|---|---|
|newaccount|Called after a new account is created. This code enforces resource-limits rules for new accounts as well as new account naming conventions.|
|updateauth|Updates the permission for an account.|
|deleteauth|Delete permission for an account.|
|linkauth|Assigns a specific action from a contract to a permission you have created.|
|unlinkauth|Assigns a specific action from a contract to a permission you have created.|
|canceldelay|Allows for cancellation of a deferred transaction.|
|onerror|Called every time an error occurs while a transaction was processed.|
|setabi|Allows for updates of the contract ABI of an account.|
|setcode|Allows for updates of the contract code of an account.|
|init|Initializes the system contract for a version and a symbol.|
|setram|Set the ram supply.|
|setramrate|Set the ram increase rate.|
|setparams|Set the blockchain parameters.|
|setpriv|Set privilege status for an account (turn it on/off).|
|setalimits|Set the resource limits of an account.|
|setacctram|Set the RAM limits of an account.|
|setacctnet|Set the NET limits of an account.|
|setacctcpu|Set the CPU limits of an account.|
|rmvproducer|Deactivates a producer by name, if not found asserts.|
|updtrevision|Updates the current revision.|
|bidname|Allows an account to place a bid for a name.|
|bidrefund|Allows an account to get back the amount it bid so far on a name.|
|deposit|Deposits core tokens to user REX fund.|
|withdraw|Withdraws core tokens from user REX fund.|
|buyrex|Buys REX in exchange for tokens taken out of user's REX fund by transferring core tokens from user REX fund and converting them to REX stake.|
|unstaketorex|Use staked core tokens to buy REX.|
|sellrex|Sells REX in exchange for core tokens by converting REX stake back into core tokens at current exchange rate.|
|cnclrexorder|Cancels unfilled REX sell order by owner if one exists.|
|rentcpu|Use payment to rent as many SYS tokens as possible as determined by market price and stake them for CPU for the benefit of receiver, after 30 days the rented core delegation of CPU will expire.|
|rentnet|Use payment to rent as many SYS tokens as possible as determined by market price and stake them for NET for the benefit of receiver, after 30 days the rented core delegation of NET will expire.|
|fundcpuloan|Transfers tokens from REX fund to the fund of a specific CPU loan in order to be used for loan renewal at expiry.|
|fundnetloan|Transfers tokens from REX fund to the fund of a specific NET loan in order to be used for loan renewal at expiry.|
|defcpuloan|Withdraws tokens from the fund of a specific CPU loan and adds them to the REX fund.|
|defnetloan|Withdraws tokens from the fund of a specific NET loan and adds them to the REX fund.|
|updaterex|Updates REX owner vote weight to current value of held REX tokens.|
|consolidate|Consolidates REX maturity buckets into one bucket that cannot be sold before 4 days.|
|mvtosavings|Moves a specified amount of REX to savings bucket.|
|mvfrsavings|Moves a specified amount of REX from savings bucket.|
|rexexec|Processes max CPU loans, max NET loans, and max queued sellrex orders. Action does not execute anything related to a specific user.|
|closerex|Deletes owner records from REX tables and frees used RAM. Owner must not have an outstanding REX balance.|
|buyrambytes|Increases receiver's ram in quantity of bytes provided.|
|buyram|Increases receiver's ram quota based upon current price and quantity of tokens provided.|
|sellram|Reduces quota my bytes and then performs an inline transfer of tokens to receiver based upon the average purchase price of the original quota.|
|delegatebw|Stakes SYS from the balance of one account for the benefit of another.|
|undelegatebw|Decreases the total tokens delegated by one account to another account and/or frees the memory associated with the delegation if there is nothing left to delegate.|
|refund|This action is called after the delegation-period to claim all pending unstaked tokens belonging to owner.|
|regproducer|Register producer action, indicates that a particular account wishes to become a producer.|
|unregprod|Deactivate the block producer with specified account.|
|voteproducer|Votes for a set of producers. This action updates the list of producers voted for, for given voter account.|
|regproxy|Set specified account as proxy.|
|onblock|This special action is triggered when a block is applied by the given producer and cannot be generated from any other source.|
|claimrewards|Claim block producing and vote rewards for block producer identified by an account.|
