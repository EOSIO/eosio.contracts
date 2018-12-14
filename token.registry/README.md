# TIP-5 Interface and Sample Implementation Walkthrough

This walkthrough follows the design pattern outlined in `token.registry.hpp` and implemented in `token.registry.cpp`. In addition, this pattern was made to be extensible. Plugins that offer extended functionality are available in the `include` folder.

### Actions

* `mint()` Mint is called to create tokens, thereby introducing new tokens into circulation.
  
* `transfer()` Transfer is called to send tokens from one account to another.

* `allot()` Allot is called to make an allotment to another account.

* `unallot()` Unallot is called to cancel an allotment and return the remaining allotted tokens to the sender's wallet.

* `claimallot()` ClaimAllot is called by the intended recipient to collect an allotment.

    An important feature to note is that allotments can be claimed in increments or all at once; the choice is entirely at the discretion of the recipient.

    For example, Account A makes an allotment of 5.00 TEST tokens for Account B. Account B can then call claimallot() to retrieve any number of the allotted tokens up to the allotted amount. Account B calls claimallot() and retrieves 3.50 TEST tokens, which are then deposited into Account B's entry on the balances table. Later, Account B makes a second call to claimallot() and retrieves 1.00 TEST tokens, leaving 0.50 TEST in the allotment. Later, Account A calls unallot() and chooses to reclaim 0.25 TEST, moving those funds back into their wallet. Finally, Account B retrieves the remaining 0.25 TEST tokens, and the ram allocated for the allotment is returned to the sender.

* `createwallet()` CreateWallet is called to create a zero-balance entry in the balances table so the user can receive tokens freely.

    While it is not strictly necessary to have a function such as createwallet, it's needed in order to avoid having ram "leaks" plague contract users. A ram "leak" occurs when an account uses some of it's own ram to store data for another account, and while it's a relatively small amount of ram (at least in the TIP-5 implementation), it has the potential to add up and result in a significant drain of resources.
    
    For example, Account A wants to transfer 1.00 TEST token to Account B, but Account B doesn't have a wallet created on the TEST token contract (in other words, Account B doesn't own any TEST token, not even an amount of zero). If Account A were to transfer the TEST token anyway, it would need to first pay ram out of it's own pocket to cover the cost of creating the balance entry before emplacing the transfer (this is disabled in the TIP-5 implementation by design). While it is possible to give the ram back to Account A through making a subsequent table modification and passing Account B as the ram payer, it is much better (and cleaner) practice to enforce users to pay for their own ram requirements outright.

* `deletewallet()` DeleteWallet is called to delete a zero-balance entry in the balances table.

    It is critical to ensure a wallet entry is only deleted if it has a balance of exactly zero. Deleting wallets with balances in them is the equivalent of burning those tokens and not removing them from the maximum supply. Future TIP-5 extentions will introduce token burning features that account for this as well as a variable max supply.

### Tables and Structs

The TIP-5 standard uses three tables to store information about token balances, token allotments, and global token settings.

* `balances_table` The balances table is used to store the native token balances of each user on the contract.

    The balances_table typedef is defined in the interface, allowing developers to instantiate the table with any code or scope as needed. The balances table stores `balance` structs, indexed by the `owner` member.

    * `owner` is the account that owns the token balance.
    * `tokens` is the native asset, where `tokens.amount` is the quantity held.

* `allotments_table` The allotments_table is a table separate from balances that allows users to make allotments to a desired recipient. The recipient can then collect their allotment at any time, provided the user who made the allotment has not reclaimed it.

    The allotments_table typedef is defined in the interface, allowing developers to instantiate the table with any code or scope as needed. The allotments table stores `allotment` structs, indexed by the `recipient` member. The allotments table also has a secondary index, `sender`.

    * `recipient` is the account that is intended to receive the allotment.
    * `sender` is the account that made the allotment.
    * `tokens` is the asset allotted, where `tokens.amount` is the quantity allotted.

* `_config` The _config instance of the `config_singleton` typedef is a global singleton that is instantiated and set automatically by the constructor and destructor, respectively. 

    The _config singleton holds all information about the native token managed by the contract. This information can be set by creating a `config` struct with the desired configuration and then setting that struct into the singleton at contract destruction. This design pattern allows the `config` struct to be modified at will during execution, and then the final state will be saved automatically when the destructor is called. See the constructor and destructor implementation for an example.

    * `publisher` is the account that owns the token contract and has the authority to mint new tokens.
    * `token_name` is the human-readable name of the native token.
    * `max_supply` is the maximum number of tokens that can be in circulation at any given time.
    * `supply` is the amount of tokens currently in circulation.

### Teclos Example Commands

*Replace positionals such as contract-name, account-name, and your-auth with the appropriate identifiers for your environment.*

* `teclos get table contract-name account-name balances`
  
    Returns the balance of the account name.

* `teclos get table contract-name account-name allotments`

    Returns all allotments made by the account name.

* `teclos get table contract-name contract-name config`

    Returns the configuration of the token contract.

* `teclos push action contract-name transfer '{"sender": "account-name", "recipient": "account-name", "tokens": "5.00 TEST"}' -p your-auth`

    Executes a transfer of the native asset to the recipient.

* `teclos push action contract-name allot '{"sender": "account-name", "recipient": "account-name", "tokens": "5.00 TEST"}' -p your-auth`

    Makes an allotment for the recipient from the sender.

* `teclos push action contract-name claimallot '{"sender": "account-name", "recipient": "account-name", "tokens": "5.00 TEST"}' -p your-auth`

    Claims an allotment made for the recipient.