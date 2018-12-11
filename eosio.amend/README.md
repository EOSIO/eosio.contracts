# RatifyAmend Core Contract

The RatifyAmend contract stores and manages the core governance documents for Telos. Updates to these governance documents are proposed, evaluated, and applied/rejected through this contract.

## Contract Usage

* `insertdoc(string title, vector<string> clauses)`

    The insertdoc action will add a new document to the `documents` table.

    `title` is the title of the document.

    `clauses` is a list of clauses that make up the document. Ideally, each clause would be it's own IPFS hash.

* `makeproposal(string sub_title, uint64_t doc_id, uint8_t new_clause_num, string new_ipfs_url, name proposer)`

    The makeproposal action will make a new proposal and call `regballot()` on Trail with the given values. This will also store the "metadata" of the proposal on this contract.

    `sub_title` is the title of the submission.

    `doc_id` is the document id for which the proposal will update.

    `new_clause_num` is the new clause number to update.

    `new_ipfs_url` is the link to the new clause text.

    `proposer` is the proposer of the submission.

* `addclause(uint64_t sub_id, uint8_t new_clause_num, string new_ipfs_url)`

    The addclause action will add a new clause to a currently existing submission.

    `sub_id` is the submission id of the submission for which to add the clause.

    `new_clause_num` is the clause number to update.

    `new_ipfs_url` is the link to the new clause text.

* `openvoting(uint64_t sub_id)`

    The openvoting action will open a submission up for voting.

    `sub_id` is the submission id for which to open voting.

* `cancelsub(uint64_t sub_id)`

    The cancelsub action will cancel a pending submission.

    `sub_id` is the submission to cancel.

* `closeprop(uint64_t sub_id)`

    The closeprop action will close an proposal.

    `sub_id` is the submission to close.

* `getdeposit(name owner)`

    The getdeposit action will return an unspent deposit for an account held on RatifyAmend.

    `owner` is the name of the account for which to get the deposit.

* `setenv(config new_environment)`

    The setenv action sets the contract environment.

    `new_environment` is the new environment to set.
