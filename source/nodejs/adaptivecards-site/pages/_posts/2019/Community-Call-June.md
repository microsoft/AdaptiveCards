---
title: 📣 Community Call - June 13, 2019
subtitle: v1.2 shipped, 1.3 planning underway, and a new JavaScript templating library available
date: 2019-06-13
featured_image: flight.jpg
github_username: matthidinger
twitter: matthidinger
---

Welcome to our Adaptive Cards community call series for 2019, the 2nd Thursday of each month. We are excited to provide you with a monthly opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.

Agenda for this month's call, hosted by Matt Hidinger, included:

## v1.2 shipped!

The team polished up and released the [v1.2 SDKs](https://github.com/Microsoft/AdaptiveCards#install-and-build) for Android, iOS, UWP, .NET, and JavaScript.

The [Expense Report sample](https://adaptivecards.io/samples/ExpenseReport.html) showcases a bunch of the new 1.2 features:

- [ToggleVisibility](https://adaptivecards.io/explorer/Action.ToggleVisibility.html) to add more interactivity in cards
- [ActionSet](https://adaptivecards.io/explorer/ActionSet.html) to place buttons anywhere in the body
- [Container bleed](https://adaptivecards.io/explorer/Container.html) to visually enhance the look of styled containers

The [full list of v1.2 features](https://github.com/Microsoft/AdaptiveCards/issues/2444) can be found on GitHub. We&#39;re working closely with our partners to roll-out v1.2 as soon as possible. To see which version the major platforms are currently on see the [Host App Docs](https://docs.microsoft.com/en-us/adaptive-cards/resources/partners).

{% adaptivecard ExpenseReport.json %}

## v1.3 planning is underway

We also walked through some high-level [features that are under consideration for v1.3](https://portal.productboard.com/adaptivecards/1-adaptive-cards-portal/tabs/4-1-3-proposed). This list is not final and will not include everything listed. Now is the best time to [suggest things](https://portal.productboard.com/adaptivecards/1-adaptive-cards-portal/tabs/4-1-3-proposed) we haven&#39;t considered!
1.3 feature list

![planning screenshot](https://developer.microsoft.com/en-us/graph/blogs/wp-content/uploads/2019/06/Image-1.png)

## Adaptive Cards templating library for JavaScript available

Lastly we walked through the [adaptivecards-templating](https://www.npmjs.com/package/adaptivecards-templating) package (preview) which is available on NPM. This library adds [templating support](https://github.com/microsoft/AdaptiveCards/issues/2448) to Adaptive Cards, allowing the separation of content from the card layout. This work is currently in active development, so your feedback is most welcome. For plenty of deep dives on templating, take a look at previous Community Calls, and please reach out with any issues or feature suggestions.

You can also experiment with templating adaptive cards using the "next designer" at [https://vnext.adaptivecards.io/designer](https://vnext.adaptivecards.io/designer).

To use the **adaptivecards-templating** library, simply take an adaptive card you created in the vnext designer, and add templating expressions for the values you want to replace with real data, then pass that data along to the library as seen below. It will create a fully-populated adaptive card – ready to render!

```js
// Define a template payload
var templatePayload = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "Hello {name}!"
        }
    ]
};
 
// Create a Template instance from the template payload
var template = new ACData.Template(templatePayload);
 
// Create a data context, and set its $root property to the
// data object to bind the template to
var context = new ACData.EvaluationContext();
context.$root = {
    "name": "Groot"
};
 
// "Expand" the template - this generates the final Adaptive Card,
// ready to render
var card = template.expand(context);
 
// Render the card
var adaptiveCard = new AdaptiveCards.AdaptiveCard();
adaptiveCard.parse(card);
 
document.getElementById('exampleDiv').appendChild(adaptiveCard.render());
```


Watch the call here.
<iframe width="560" height="315" src="https://www.youtube.com/embed/UfHDlfN3E10" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Next month’s call will be held on **Thursday, July 20, 2019 at 9:00am PST**.  We look forward to talking to you then! Download a recurring calendar invite here at https://aka.ms/adaptivecardscommunitycall.
