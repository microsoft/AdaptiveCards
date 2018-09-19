# Proposal process

## Stage 1: Write a proposal

After the [requests and requirements](requests.md) have been collected, a proposal needs to be authored.

The title of the proposal issue should be in the format of...

**Proposal: [Name]**

For example...

**Proposal: Markdown support for inline text colors**

The proposal body needs a few rough details, like...

* **Requirements**: Link to request collection issue. Can link to multiple if proposal solves multiple.
* **Summary**: Brief summary of the proposed solution
* **Schema**: Schema changes
* **Example**: Provide an example of the schema changes
* **Host Config**: Describe changes to the host config, if any
* **Down-level impact**: Describe the impact to authors when their card goes down-level
* **Host burden**: Describe the impact hosts have when they update their renderer library (do they have to add new host config properties because of this?)
* **Renderer requirements**: Can be filled out later.

If there's another proposal, it should be created as a separate issue.


## Stage 2: Submit proposal for review

Once your proposal is ready for review, let the Adaptive Cards team know by posting a new comment in [this proposals ready for review issue](https://github.com/Microsoft/AdaptiveCards/issues/1928). We'll schedule a review of the proposal.


## Stage 3: Proposal review

When we open a proposal for review, we'll post it in the [proposal reviews issue](https://github.com/Microsoft/AdaptiveCards/issues/1927). Anyone interested in contributing to reviews should subscribe to this issue.

When a proposal is posted, it will remain open for a minimum of 3 business days. This allows anyone online to contribute to the review in a reasonable amount of time.

On the 4th (or later) business day, the Adaptive Cards team will meet to internally review the proposal (and the feedback from online), and will vote on whether the proposal is approved or needs more work.

If the proposal is approved, it now moves on to [the spec stage](specs.md). We'll re-name the title of the issue to be "Spec" rather than "Proposal".