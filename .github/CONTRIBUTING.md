# Instructions for Logging Issues

## 1. Search for Duplicates
[Search the existing issues](https://github.com/Microsoft/AdaptiveCards/issues?utf8=%E2%9C%93&q=is%3Aissue) before logging a new one.

## 2. Do you have a question?
If you have a *question*, please use [Stack Overflow](https://stackoverflow.com/questions/tagged/adaptive-cards)

## 3. Did you find a bug?
Please use the [bug template](https://github.com/microsoft/AdaptiveCards/issues/new?assignees=&labels=Bug&template=bug_report.md&title=%5BPlatform%5D%5BBroad+Issue+Category+if+applicable+%28eg+Accessibility%29%5D+%5BBug+Title%5D) we provide to raise bugs for us. 
 
## 4. Do you have a suggestion?
We also accept suggestions as github issues. 

Please take a look at our [Core Design Principles](https://docs.microsoft.com/en-us/adaptive-cards/#core-design-principles) to make sure the suggestion is aligned with the project goals.

In general, things we find useful when reviewing suggestions are:
* A description of the problem you're trying to solve
* An overview of the suggested solution
* Examples of how the suggestion would work in various places

# Instructions for Contributing Code

## Contributing bug fixes

Our local dev team is in active development, but we are always looking for community participation in the spirit of open development and accepting external contributions in the form of bug fixes or even broader features if they have the potential to impact the broader AdaptiveCards community.

For contributing to existing isues, check out our [Accepting PRs](https://github.com/microsoft/AdaptiveCards/labels/Accepting%20PRs) list. For new issues, ensure you've created a new issue report and that it's been approved to be fixed by the Adaptive Cards team. 

## Contributing features

We're happy to discuss schema proposals as long as they align with our [Core Design Principles](http://adaptivecards.io/documentation/#about-overview). 

Please open an issue with your schema proposal to get a discussion started.

## Legal

You will need to complete a Contributor License Agreement (CLA). Briefly, this agreement testifies that you are granting us permission to use the submitted change according to the terms of the project's license, and that the work being submitted is under appropriate copyright.

You will be asked to sign the Microsoft Contributor License Agreement (CLA) when you submit a pull request, if there is 
not already a CLA on file for your GitHub account. Once we have received the signed CLA, we'll review the request. 

You can review details of the agreement at https://cla.opensource.microsoft.com.

### Pull Requests
For pull requests, please use the [pull request template](https://github.com/microsoft/AdaptiveCards/blob/main/.github/pull_request_template.md) we provide. Do test your fixes manually (PR support/Buddy builds at this point are not supported but we are working on enabling it) before putting up your change for review. All unit tests should be passing for a PR to be committed into main. Someone from the AdaptiveCards v-team will also have to review your change before the change is allowed to be merged in. They may ask questions for more information or ask you to change things. Be sure to respond to their comments and push additional changes to the branch if they ask you to modify things before they sign off.

#### Stale Pull Request Policy
We mark pull requests as stale after 5 days of inactivity on it and call your attention to it via our fabricbot, and assign the pull request to be reviewed by a member of the Adaptive Cards team formally and should be able to help shepherd the change in. Our team's pull request SLA typically is ~2 business days but please do call us out on this if you see us slipping (we still are a very small team). The bot will automtically close the pull request and notify you after 30 days of continuous inactivity on it. Follow up's would likely be a case-by-case basis depending on why the PR aged out to begin with.
