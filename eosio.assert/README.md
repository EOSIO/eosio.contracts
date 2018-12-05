## Installation

* Load either `eosio.bios` or `eosio.system` into the `eosio` account. Requires release 1.3.x or later.
* Reload all `eosio.*` ABIs so eosio.bios or eosio.system can record their hash
* Load `eosio.assert` into the `eosio.assert` account
  * Do **not** make eosio.assert privileged
* Use `eosio.assert`'s `setchain` action to initialize the contract. Requires `eosio` authorization.

## Maintaining manifests (app owners)

* Use `add.manifest` and `del.manifest`
* The manifest id is the hash over the serialized form of these fields from the manifest:
  * `account`: the account which owns the app
  * `domain`: the domain the app is hosted on
  * `appmeta`: see the manifest spec
  * `whitelist`
    * Array of (contract, action) that the manifest allows
    * An empty contract or action indicates a wildcard match

## Using require (wallets)

* Add the `require` action to the transaction
  * `chain_params_hash`: This identifies the chain. It's a hash over the serialized form of:
    * `chain_id`
    * `chain_name`
    * `icon`
  * `manifest_id`: Identifies a manifest registered by `add.manifest`
  * `actions`: All actions in the transaction. Don't include the `require` action in this array.
  * `abi_hashes`: To fill this field:
    * Create a sorted set of contracts that appear in `actions`. Remove duplicates.
    * For each contract, append that contract's ABI hash to `abi_hashes`.
    * Hash the ABIs in the on-chain (raw) form. Don't hash the ABIs in JSON form.
* `require` runs the following checks:
  * `chain_params_hash` must match the hash of the chain data registered with `setchain`
  * `manifest_id` exists
  * The manifest's whitelist permits all provided actions
  * Contracts have matching ABI hashes
* If any check fails, then the transaction will fall
