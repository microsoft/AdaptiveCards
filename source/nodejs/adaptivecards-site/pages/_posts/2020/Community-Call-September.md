---
title: 📣 Community Call - September, 2020 
subtitle: Roadmap updates and an early look at Adaptive Components
date: 2020-09-11
featured_image: https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/09/two-%E2%80%9CPersonas%E2%80%9D-next-to-Requested-by-and-Approver-showing-the-profile-picture-and-name..png
github_username: matthidinger
twitter: matthidinger
---

In the Adaptive Cards community call for September, Matt Hidinger shared the Q4 roadmap and a sneak peek at a new concept called "Adaptive Components."

### Roadmap Updates

We've divided the [Roadmap Portal](https://aka.ms/ACRoadmap) to 3 distinct sections: **Under Consideration**, **Planned**, and **Launched**. This change provides more clarity into what stage any given feature currently is and when you can expect a given enhancement.

![Snippet of the product roadmap portal](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/09/Snippet-of-the-product-roadmap-portal-1024x401.png)

Coming in Q4 and Q1 2021 you can expect the following things:

-   [**Templating SDKs**](https://docs.microsoft.com/en-us/adaptive-cards/templating/sdk) **for iOS, Android, and UWP**. Currently the templating SDKs are only available for .NET and JavaScript. This work will pave the way for exciting improvements once we are able to evaluate template bindings and expressions directly on the client where the cards are being rendered.
-   **A new Universal Action model for handling actions in your backend in a consistent way**, whether the card appears in Teams, Outlook, or elsewhere. We'll share more details on this shortly.
-   **In the Rendering/Schema category, we've got some nice fit-and-finish improvements under way:**
    -   Improved accessibility across the board.
    -   [Text password masking](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/63-input-text-password-masking).
    -   ChoiceSet is getting a new [filtering UX](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/64-input-choiceset-search-filtering-ux-static-list-of-choices), [Auto Complete](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/15-input-choiceset-auto-complete) support, and the ability to [trigger an Action when a choice is made](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/65-input-choiceset-changeaction).
    -   For Actions we're adding an [isEnabled property to disable actions](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/67-action-isenabled-property) and creating enhanced UX for additional actions by allowing them [overflow into a "..." menu](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/58-actionset-overflow-into-a-flyout).
-   And much more that we are still fleshing out the details on...

As always, be sure to vote on the features that are important to you and click that **Submit Idea** button if you don't already see it!

### Adaptive Components

[Adaptive Components](https://github.com/microsoft/AdaptiveCards/issues/4761) are a new concept that enable the creation of high-level UI "components" powered by [templating](https://aka.ms/ACTemplating) and Adaptive Card elements.

For example, in the card below there are two great use-cases for "components":

1.  The File Chiclet, showing the file icon, title, URL and set of actions.
2.  The two "Personas" next to **Requested by** and **Approver** showing the profile picture and name.

![screenshot of a card with a file and user component](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/09/two-%E2%80%9CPersonas%E2%80%9D-next-to-Requested-by-and-Approver-showing-the-profile-picture-and-name..png)

The way components are used within a Card is by a **Component.<NAME>** convention. For example, see the **Component.File** usage below. Notice only the data is provided to the component, so for files, you pass along the **title**, **fileType**, and the **objectUrl**.

```json
{
	"type": "AdaptiveCard",
	"body": [
		{
			"type": "Component.File",
			"title": "FY2020-Contoso.docx",
			"fileType": "docx",
			"objectUrl": "https://example.com/assets/AdaptiveCardsSpec.docx"
		}
	]
}
```

When authoring a component, the creator describes the shape of the data it expects using JSON-Schema and uses Templating and Expressions to transform the data into Adaptive Card elements. Take a look at the [GitHub issue](https://github.com/microsoft/AdaptiveCards/issues/4761) for a detailed example of this.

The power of components is really in 3 areas:

1.  **Allow apps to learn new UI components on the fly.** Because Components are purely declarative, we can rely on component registries to allow the fetching of remote components via HTTP.
2.  **Help bootstrap the sharing of common types of UI** among teams internally or with the public. Components can be hosted in GitHub repos and shared with others, making developers much more productive when building Cards.
3.  **Support multiple views over data.** Lastly, we plan to make a component broadly useful, on different Hosts, with different display constraints, and different renderer schema versions. The example below shows a simple "Thing" component that has 3 different views over the same data.

![Hero, thumbnail and stack image of golden gate bridge](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/09/Hero-thumbnail-and-stack-image-of-golden-gate-bridge-1024x361.png)

Let us know on [GitHub](https://github.com/microsoft/AdaptiveCards/issues/4761) or [Productboard](https://adaptivecards.productboard.com/portal/1-adaptive-cards-features/tabs/c88173a2-a3a1-4bc5-ad15-11051b3c7942/features/5478079/portal/expanded) if components is something you would benefit from in your day-to-day card usage!

### Watch the call here

<iframe width="560" height="315" title="Adaptive Cards Community Call Recording" src="https://www.youtube.com/embed/DkDfB5I8tJI" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen="allowfullscreen"></iframe>

### Resources

-   [Watch the latest Adaptive Cards session from Build 2020](https://aka.ms/m365sk134)
-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)

Next month's call will be held on **Thursday, October 8, 2020 at 9:00am PST.** We look forward to talking to you then! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Office Development YouTube Channel](https://www.youtube.com/channel/UCV_6HOhwxYLXAGd-JOqKPoQ)