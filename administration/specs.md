# Specs

## Stage 1: Spec draft

After [a proposal](proposals.md) has been approved, it now becomes a spec draft. The Adaptive Cards team will rename the proposal to be a "Spec", for example...

**Spec: Markdown support for inline text colors**

Either the author of the proposal, or the Adpative Cards team, will begin finalizing the spec draft. Any missing details need to be completed.

The spec should be complete enough that anyone can implement the feature without ambiguity.


## Stage 2: Submit spec for review

After the spec has been fully finished with details, let the Adaptive Cards team know by posting a new comment in [this specs ready for review issue](). We'll schedule a review of the spec.


## Stage 3: Spec review

Once we're ready to open a spec for review, we'll post it in the [spec reviews issue](). Anyone interested in contributing to reviews should subscribe to this issue.

When a spec is posted, it will remain open for a minimum of 3 business days. This allows anyone online to contribute to the review in a reasonable amount of time.

On the 4th (or later) business day, the Adaptive Cards spec review team will meet to internally review the spec (and the feedback from online), and will vote on whether the spec is approved or needs more work.

If the spec is approved, we will mark it approved.

### Internal spec review team

The internal spec review team will be composed of key spec-level stakeholders.

* The devs of Adaptive Cards
* The PMs of Adaptive Cards (Matt Hidinger, Andrew Leader, David Claux)

The purpose of this meeting is to obtain consensus on whether the spec is complete, and whether all the small details like naming are agreed upon.

Minimum participants to have a quorum...

* At least 2 devs from Adaptive Cards
* At least 2 PMs from Adaptive Cards

At the end of the review, voting will occur. Participants can either vote **Approved**, **Denied**, or **No Opinion**. If the number of **Approved** is greater than or equal to the number of **Denied**, and there are at least 2 votes of **Approved**, the spec will be approved.

Each partner of Adaptive Cards will only get one vote (so even if one partner brings 5 people with them, they can only cast one collective vote). Everyone else's votes will be counted as-is.


## Stage 4: Implementation

The devs can now start coding! As with any feature, new realizations might happen while implementing the feature. If these realizations challenge statements in the spec (or identify ambiguity in the spec), these changes need to be reviewed again. We will flag the spec as `Spec-Has Concerns` so all devs know it is no longer approved, and a new comment on the spec should be posted with the proposed changes.


## Stage 5: Submit spec for re-review

After the proposed changes have been described in a comment on the spec, a new comment in [the specs ready for review issue]() will be posted. We'll schedule a follow-up review of the spec.


## Stage 6: Spec re-review

Once we're ready to re-review the spec, we'll post it in the [spec reviews issue](). Anyone interested in contributing to reviews should subscribe to this issue.

When a re-review of a spec is posted, it will remain open for a minimum of 1 business days. The timespan is shorter considering these might be higher priority with release deadlines approaching soon.

On the 2th (or later) business day, the Adaptive Cards spec review team will meet to internally review the proposed changes to the spec (and the feedback from online), and will vote on whether the new proposed changes are approved or needs more work.

If the proposed changes are approved, the spec will be marked approved and the proposed changes will be integrated into the spec.