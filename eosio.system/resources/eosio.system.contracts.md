<h1 class="contract">clnproposal</h1>

## Description

This action is used to clear the RAM being used to store all information related to
{{ proposal_name }}. All associated votes must be cleared before {{ proposal_name }}
can be cleared from the RAM of {{ proposer }}.

This action can be called by any user, requiring no authorization.

This action can only be called 72 hours after {{ expires_at }} has been reached.
{{ expires_at }} is set at the moment that {{ proposal_name }} is created, and can
only be updated by {{ proposer }}. This will allow time to compute a tally of all
associated votes before it can be cleared.

The user who calls `clnproposal` will pay the CPU and NET bandwidth required
to process the action. They will need to specify `max_count` to ensure that the
action can be processed within a single block's maximum allowable limits.

<h1 class="contract">expire</h1>

## Description

`expire` can only be called by {{ proposer }}.

`expire` is used to modify the value of `expires_at` to the new time {{ expires_at }}. Once `expire` has been called,
no more votes will be accepted for {{ proposal_name }}.

<h1 class="contract">post</h1>

## Description

`post` is used to create a post that can either be a parent or
be a response to parent post. They are threaded together using their
unique identifier {{ post_uuid }}.

<h1 class="contract">propose</h1>

## Description

`propose` creates a message on-chain with the intention of receiving
votes from any community members who wish to cast a `vote`.

Each proposal shall be identified with a unique `proposal_name`.

An expiry will be defined in `expires_at`, with {{ expires_at }}
being no later than 6 months in the future.

{{ proposer }} must pay for the RAM to store {{ proposal_name }}, which
will be returned to them once `clnproposal` has been called.

<h1 class="contract">status</h1>

## Description

`status` is used to record a status for the associated {{ account }}.
If the {{ content }} is empty, the action will remove a previous status.
Otherwise, it will add a status entry for the {{ account }} using the
{{ content }} received.

<h1 class="contract">unpost</h1>

## Description

The intent of the `unpost` action is to suggest that a previously posted message (through the `post` action), as referred by {{ post_uuid }}, be removed by the different front-ends reading this contract's transaction flow.

I, {{ poster }} understand that this action will not remove the message from circulation, as it will be imprinted in the blockchain.  I also understand that some front-ends might not remove the message, and even highlight the fact that a message was intended to be removed, potentially attracting attention on an undesired message.

<h1 class="contract">unvote</h1>

## Description

`unvote` allows a user to remove their vote of {{ vote_value }} they have previously
cast on {{ proposal_name }}.

`unvote` will not function during the 72 hour period after
{{ proposal_name }} has expired at {{ expires_at }}.

The RAM that was used to store the vote shall be freed-up immediately
after `unvote` has been called by {{ voter }}.

<h1 class="contract">vote</h1>

## Description

A user is able to cast a vote by associating it to {{ proposal_name }}. To
change a vote, a {{ voter }} only needs to call another `vote` action - only the
most recent vote of {{ vote_value }} by {{ voter }} will be considered as valid . A user
could also use `unvote` to override their previous `vote`.

If I, {{ voter }}, am not the beneficial owner of these tokens, I stipulate I have proof
that I’ve been authorized to vote these tokens by their beneficial owner(s).

A user who has a proxy set on their account will be providing implicit consent
for that proxy to `vote` on their behalf. A user who has a designated proxy
may choose to also cast a `vote`, which will override the delegation of voting
authority to that proxy.

I stipulate I have not and will not accept anything of value in exchange for these
votes, on penalty of confiscation of these tokens, and other penalties.

Any disputes arising out of use of this contract shall be ruled under the Rules
for Dispute Resolution of the EOS Core Arbitration Forum by one or more arbitrators
appointed in accordance with said Rules.