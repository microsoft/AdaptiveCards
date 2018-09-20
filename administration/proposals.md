# Proposal process

## Stage 1: Write a proposal

After the [requests and requirements](requests.md) have been collected, a proposal needs to be authored.

The title of the proposal issue should be in the format of...

**Proposal: [Name]**

For example...

**Proposal: Markdown support for inline text colors**

The proposal body needs a few rough details, like...

```
# Solves requests

* Request name (#issue-number)


# Summary
Brief summary of the proposed solution


# Schema
**New** property on `Action` 

Property | Type | Required | Description
---|---|---|---
Style | enum [default, emphasized, destructive] | false | Applies a style to an Action to indicate to intent


# Example
Provide an example payload


# Host Config
Describe changes to the host config, if any.


# Down-level impact
Describe how down-level is impacted for authors.


# Host burden
Describe the burden hosts have when we introduce this feature. For example, are they going to have to add something new to their host config or native styling as a result of a new element we're adding? Are there breaking API changes that hosts have to use? Are we deprecating something from host config that could cause potential confusion?
```

If there's another proposal, it should be created as a separate issue.


## Stage 2: Submit proposal for review

Once your proposal is ready for review, let the Adaptive Cards team know by posting a new comment in [this proposals ready for review issue](https://github.com/Microsoft/AdaptiveCards/issues/1928). We'll schedule a review of the proposal.


## Stage 3: Proposal review

When we open a proposal for review, we'll post it in the [proposal reviews issue](https://github.com/Microsoft/AdaptiveCards/issues/1927). Anyone interested in contributing to reviews should subscribe to this issue.

When a proposal is posted, it will remain open for a minimum of 3 business days. This allows anyone online to contribute to the review in a reasonable amount of time.

On the 4th (or later) business day, the Adaptive Cards team will meet to internally review the proposal (and the feedback from online), and will vote on whether the proposal is approved or needs more work.

If the proposal is approved, it now moves on to [the spec stage](specs.md). We'll re-name the title of the issue to be "Spec" rather than "Proposal".


### Internal proposal review team

The internal proposal review team will be composed of key stakeholders.

* Whoever asked for the feature (the initial requester)
  * If this was a community request, we'll ping the community members when posting the proposal for review so they can share their feedback
* The devs of Adaptive Cards
* The PMs of Adaptive Cards (Matt Hidinger, Andrew Leader, David Claux)
* The partners of Adaptive Cards (Timeline, Bots, Outlook, Cortana, etc)

The purpose of this meeting is to obtain consensus on whether the proposal is going in the right direction and should move on to the detailed spec'ing stage.

Minimum participants to have a quorum...

* The initial requester(s) that the proposal is addressing
  * If this was a community request and they didn't provide their feedback online, we will continue without them
* At least 2 devs from Adaptive Cards
* At least 2 PMs from Adaptive Cards

At the end of the review, voting will occur. Participants can either vote **Approved**, **Denied**, or **No Opinion**. If the number of **Approved** is greater than or equal to the number of **Denied**, and there are at least 2 votes of **Approved**, the proposal will be approved.

Each partner of Adaptive Cards will only get one vote (so even if one partner brings 5 people with them, they can only cast one collective vote). Everyone else's votes will be counted as-is.