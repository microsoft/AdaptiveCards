---
title: 📣 Community Call - July, 2020 
subtitle: v1.3 is released, and a real-world look at automating business processes with Cards and Power Automate
date: 2020-08-24
featured_image: https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/08/A-screenshot-of-a-social-media-post-768x712.png
github_username: matthidinger
twitter: matthidinger
---

The Adaptive Cards community call for August, hosted by Matt Hidinger, also included guest speakers Hammad Hassan and Tomasz Poszytek.

### Adaptive Cards v1.3 is now available!

On this call we reviewed the [**Adaptive Cards v1.3**](https://github.com/microsoft/AdaptiveCards/releases/tag/2020.07) release, which includes the most-requested feature of the past 2 years: [**Input Validation and Input Labels**](https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/input-validation)!

With this release you'll be able to mark which **Inputs** are required, as well as any regex-based pattern matching for text, and min/max ranges for things like numbers and dates.

We've also streamlined the [Input schema](https://adaptivecards.io/explorer/Input.Text.html) by adding a **label** property, which improves the interaction model, automatically renders those red-asterisk "required field indicators", and greatly improves accessibility for Inputs.

**Screenshot of an Input with a *label* and *isRequired* validation:**

➡ [Try it yourself in the Designer](https://adaptivecards.io/designer/index.html?card=/payloads/InputsWithValidation.template.json&data=/payloads/InputsWithValidation.data.json)

![Screenshot of input validation in a card](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/08/Designer.png)

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

### What we're doing to improve rendering consistency on every platform

Adaptive Cards are designed to work great on every major platform, and that means all the features, functionality, styles, and behaviors need to work consistently everywhere that Adaptive Cards are supported.

**Hammad Hassan** is an intern with us this summer and set out to improve the guarantees we make along those lines. He kicked off a project called "[Consistent Cards](https://adaptivecards.io/explorer/Input.Text.html)" that facilitates rapid end-to-end testing of any changes we make to the various renderers and instantly see how the various payloads look on live machines.

It works by sending a card payload through virtual machines that are hosting our Adaptive Card renderers on the various platforms, like NodeJS, .NET WPF, Android, and UWP. Below is a screenshot of a card that has been rendered live, on all 4 platforms, and returns their screenshots to the web app. This allows us to quickly see differences and troubleshoot visual bugs on the different UI stacks.

![Screenshot of Consistent Cards showing a card rendering on 4 different platforms](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/08/Screenshot-of-Consistent-Cards-showing-a-card-rendering-on-4-different-platforms-1024x464.png)

Currently, this tool is used internally for us during development, but we see the value of it being publicly available. We don't have any plans to share on this front just yet but keep us posted if this is something you would be interested in!

To learn more, check out [the project outline and spec](https://github.com/microsoft/AdaptiveCards/blob/main/specs/DesignDiscussions/ConsistentCards.md) or just jump right into the [source code](https://github.com/microsoft/AdaptiveCards/tree/hammad-h/test-card-consistency/source/tools/testConsistency).

### Automating real-world scenarios using Power Automate

Lastly, [**Tomasz Poszytek**](https://twitter.com/TomaszPoszytek?s=20), a Power Platform MVP, walked through some amazing real-world business processes that can be streamlined and improved using Power Automate. Take a look at the call below to get the full details!

![A screenshot of a social media post](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/08/A-screenshot-of-a-social-media-post.png)

### Watch the call here

<iframe width="560" height="315" title="Adaptive Cards Community Call" src="https://www.youtube.com/embed/R0ij6SLuJXY" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen="allowfullscreen"></iframe>

Resources from this month's call

-   [Watch the latest Adaptive Cards session from Build 2020](https://aka.ms/m365sk134)
-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)
-   [Adaptive Card Template Service](https://docs.microsoft.com/en-us/adaptive-cards/templating/service)
-   <https://aka.ms/ACFeatures> -- Let us know what features you need

Next month's call will be held on **Thursday, September 10, 2020 at 9:00am PST.** We look forward to talking to you then! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Office Development YouTube Channel](https://www.youtube.com/channel/UCV_6HOhwxYLXAGd-JOqKPoQ)

### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)

The Adaptive Cards developer community call is on the 2nd Thursday of each month. We will provide you with the opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.