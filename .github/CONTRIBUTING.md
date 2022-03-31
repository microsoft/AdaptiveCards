# Instructions for Logging Issues

## 1. Search for Duplicates

[Search the existing issues](https://github.com/Microsoft/AdaptiveCards/issues?utf8=%E2%9C%93&q=is%3Aissue) before logging a new one.

## 2. Do you have a question?

Please use the issue tracker for bugs and suggestions.

If you have a *question*, please use [Stack Overflow](https://stackoverflow.com/questions/tagged/adaptive-cards)

## 3. Did you find a bug?

I'm not surprised, we're still in the early stages, so there are plenty of them right now :)

When logging a bug, please be sure to include the following:
 * The platform you were using
 * If at all possible, an *isolated* way to reproduce the behavior
 * The behavior you expect to see, and the actual behavior
 
## 4. Do you have a suggestion?

We also accept suggestions in the issue tracker. 

Please take a look at our [Core Design Principles](https://docs.microsoft.com/en-us/adaptive-cards/#core-design-principles) to make sure the suggestion is aligned with the project goals.

In general, things we find useful when reviewing suggestions are:
* A description of the problem you're trying to solve
* An overview of the suggested solution
* Examples of how the suggestion would work in various places

# Instructions for Contributing Code

## Contributing bug fixes

Our local dev team is in active development, but we are still accepting external contributions in the form of bug fixes.

A bug must have an issue tracking it in the issue tracker that has been approved by the Adaptive Cards team. Your pull request should include a link to the bug that you are fixing. If you've submitted a PR for a bug, please post a comment in the bug to avoid duplication of effort.

## Contributing features

Thank you for wanting to contribute to Adaptive Cards. If you are planning to make changes to the Core SDK, please make sure these changes align with our [Core Design Principles](https://docs.microsoft.com/en-us/adaptive-cards/#core-design-principles). Prior to writing any code that affects rendering, please make sure you follow the following steps:
1.	Open a "Feature Request" issue to start the discussion on the feature you wish to see in the product. Please make sure you search our [planned work](https://github.com/microsoft/AdaptiveCards/projects/32) to see if your feature is already planned.
2.	Open a PR with a .MD file to the [following directory](https://github.com/microsoft/AdaptiveCards/tree/main/specs/elements) with a spec that clearly outlines the feature you are implementing. **Include as much detail on the feature as possible**.
    1.	At a bare minimum you must answer the following questions:
        1.	Why do you need this feature and what will the feature do?
        2.	What will the API surface look like?
        3.	What will the schema look like?
        4.	What is the down-level impact of this feature?
    2.  Please make sure your PR follows a similar format as our [Spec](https://github.com/microsoft/AdaptiveCards/blob/main/specs/SpecTemplate.md) template including a summary, rationale, scope, and examples.
3.	Once you open the PR with the spec, the team will review it and schedule a call with the community to walk through the feature. This is where the discussion will happen.
4.	If the spec is approved, you may begin writing the implementation for your feature and submit a PR.
    1.	Note: In order for your feature to release with Adaptive Cards it must be implemented on all platforms (.NET, iOS, Android, JavaScript) as per our Core Design Principles. You may choose to implement on any number on these platforms as a starting point for our team, but please keep in mind we wont be able to merge anything until all platforms are implemented.
    2.	Your PR must also include sample cards in the following directory 
    3.	For all schema changes make sure to include them in the schemas directory and validate them in the schema explorer. Once you submit a PR you will get a build of the website   that includes your changes in the schema explorer. This PR specific build will follow the following format: ``https://adaptivecardsci.z5.web.core.windows.net/pr/<PR-NUMBER>/explorer``
5.	The team will once again review the PR and make sure all the requirements are met.
    1.	Please keep in mind that Adaptive Cards works in a production environment and thus requires production-ready code with appropriate tests and at least two approvals from the team before it is merged.



## Legal

You will need to complete a Contributor License Agreement (CLA). Briefly, this agreement testifies that you are granting us permission to use the submitted change according to the terms of the project's license, and that the work being submitted is under appropriate copyright.

You will be asked to sign the Microsoft Contributor License Agreement (CLA) when you submit a pull request, if there is 
not already a CLA on file for your GitHub account. Once we have received the signed CLA, we'll review the request. 

You can review details of the agreement at https://cla.opensource.microsoft.com.

## Housekeeping

Your pull request should: 

* Include a description of what your change intends to do
* Be a child commit of a reasonably recent commit in the **main** branch 
    * Requests need not be a single commit, but should be a linear sequence of commits (i.e. no merge commits in your PR)
* Have clear commit messages 
    * e.g. "Refactor feature", "Fix issue", "Add tests for issue"

## Running the Tests

*Coming soon*
