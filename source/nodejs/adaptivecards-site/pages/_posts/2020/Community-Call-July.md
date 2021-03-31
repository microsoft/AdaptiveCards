---
title: 📣 Community Call - July, 2020 
subtitle: v1.3 update including input validation, and a new VS Code Extension
date: 2020-07-16
featured_image: https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/07/Screenshot-of-input-validation-in-a-card.png
github_username: matthidinger
twitter: matthidinger
---

The Adaptive Cards community call for July, hosted by Matt Hidinger, also had guest speaker Tim Cadenbach):

### V1.3 Update: Input Evolution and Validation

On this call we reviewed the upcoming **Adaptive Cards v1.3** release, which includes the most-requested feature of the past 2 years: **Input Validation**!

With this release you'll be able to mark which **Inputs** are required, as well as any regex-based pattern matching for text, and min/max ranges for things like Numbers and Dates.

We've also streamlined the Input schema by adding a **label** property, which improves the interaction model, automatically renders those red-asterisk "required field indicators", and greatly improves accessibility for Inputs.

**Screenshot of an Input with a *label* and *isRequired* validation:**

![Screenshot of input validation in a card](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/07/Screenshot-of-input-validation-in-a-card.png)

**Example Card with Input Validation and Labels:**

```json
{
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3",
    "body": [
        {
            "type": "Input.Text",
      		"id": "name",
            "placeholder": "First, last",
            "label": "Please enter your name",
            "isRequired": true,
            "errorMessage": "Name is required"
        }
    ],
    "actions": [
        {
            "type": "Action.Submit",
            "title": "Save"
        }
    ]
}
```

**When can I try it?**

We plan to ship the SDK in August, at which time apps like Microsoft Teams can begin integrating and rolling it out. Stay tuned here for an update on exactly when this feature will be available in Microsoft Teams.

-   Track [**progress**](https://github.com/microsoft/AdaptiveCards/projects/15) to completion on our project board
-   Try it out [**in the Adaptive Card Designer**](https://adaptivecardsci.z5.web.core.windows.net/pr/4005/designer)
    -   (*Note*: this link builds out of an "in-development branch" so if it fails to run properly please wait a few hours and then try again)

### Introducing "Adaptive Card Studio" for Visual Studio Code

Up next on the call Tim Cadenbach introduced a new Visual Studio Code Extension called [Adaptive Card Studio](https://marketplace.visualstudio.com/items?itemName=madewithcardsio.adaptivecardsstudiobeta).

This extension for makes it easy to work with Adaptive Cards from the comfort of your favorite editor, **including templating and sample data binding**. He also talked about future plans to integrate the extension with the "[Adaptive Card CMS](https://adaptivecards.io/blog/2020/Community-Call-April/)" once that product is a little more stable.

![Screenshot of the VS Code extension](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/07/Screenshot-of-the-VS-Code-extension-1024x434.png)

-   Install [**Adaptive Card Studio**](https://marketplace.visualstudio.com/items?itemName=madewithcardsio.adaptivecardsstudiobeta) from the VS Code Marketplace
-   Check out [**the source code**](https://github.com/microsoft/AdaptiveCards/pull/4337)

### What else can cards do?

Lastly, Tim pushed the creative bounds of Adaptive Cards by showcasing a full card-powered web app that could be helpful for some scenarios. He also walked through a community-led website that makes it easy to share cards, additional samples, community blog posts and docs, etc.

-   Check it out at [**https://madewithcards.io**](https://madewithcards.io)

Watch the call here

<iframe width="560" height="315" title="Adaptive Cards Community Call-July 2020" src="https://www.youtube.com/embed/lir9cqcCl80" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Resources from this month's call

-   Find Tim on Twitter [**@TimCadenbach**](https://twitter.com/TimCadenbach)
-   <https://madewithcards.io> -- community supported Adaptive Cards
-   [Adaptive Card Studio](https://marketplace.visualstudio.com/items?itemName=madewithcardsio.adaptivecardsstudiobeta) from the VS Code Marketplace
-   [Watch the latest Adaptive Cards session from Build 2020](https://aka.ms/m365sk134)
-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)
-   [Adaptive Card Template Service](https://docs.microsoft.com/en-us/adaptive-cards/templating/service)

Next month's call will be held on **Thursday, August 13, 2020 at 9:00am PST.** We look forward to talking to you then! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Office Development YouTube Channel](https://www.youtube.com/channel/UCV_6HOhwxYLXAGd-JOqKPoQ)

#### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)

The Adaptive Cards developer community call is on the 2nd Thursday of each month. We will provide you with the opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.