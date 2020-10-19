---
title: 📣 Community Call - October, 2020 
subtitle: Deep dive into Adaptive Components
date: 2020-10-08
featured_image: https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/10/Picture3-1.png
github_username: matthidinger
twitter: matthidinger
---

In the Adaptive Cards community call for October, Matt Hidinger gave a demo and deep-dive into Adaptive Components.

### Deep dive into Adaptive Components

*(Note: we've iterated on this quite a bit since last month's community call)*

[Adaptive Components](https://github.com/microsoft/AdaptiveCards/issues/4761) are a new concept that enable the creation of high-level UI "components" powered by [templating](https://aka.ms/ACTemplating) and Adaptive Card elements. You can think of them like "molecules", built by arranging Adaptive Card elements ("atoms") into unique and helpful ways.

For example, the card below contains two Components:

1.  The "File Component", showing the file icon, title, URL and set of actions to open the file.
2.  The two "People Components", next to **Requested by** and **Approver** showing the person's profile picture and name.

![screenshot of a card with two components](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/10/Picture1-2.png)

Components can be rendered within the card body by providing the `name` of the component you want to use, using the convention of `[COMPONENT-DOMAIN]/[COMPONENT-NAME]`. For example, if you want to use the File Chiclet component seen above, you'll use the name `"graph.microsoft.com/file"` and provide the file `properties` received from the Graph API.

Notice only the data properties are needed to render the component, so for Files, you pass along the **name**, **fileType, and webUrl**.

```json
{
    "type": "AdaptiveCard",
    "body": [
        {
            "type": "Component",
            "name": "graph.microsoft.com/file",
            "properties": {
               "name": "FY2020-Contoso.docx",
               "fileType": "docx",
               "webUrl": "https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsSpec.docx"
            }
        }
    ]
}
```

When authoring a component for others to use, the creator gives the component a name, describes the shape of the data it expects, and uses [Templating and Expressions](https://aka.ms/ACTemplating) to transform the data into Adaptive Card elements. Check out the [GitHub issue](https://github.com/microsoft/AdaptiveCards/issues/4761) for some example components, or see the [backend component registry](https://github.com/microsoft/adaptivecards-templates/tree/components/components) for the full list.

The power of components is really in 3 areas:

1.  **Allow apps to learn new UI components on the fly.** Because Components are purely declarative, we can rely on component registries to allow the fetching of remote components via HTTP.
2.  **Help bootstrap the sharing of common types of UI** among teams internally or with the public. Components can be hosted in GitHub repos and shared with others, making developers much more productive when building Cards.
3.  **Support multiple views over data.** Lastly, we plan to make a component broadly useful, on different Hosts, with different display constraints, and different renderer schema versions. The example below shows a simple "Thing" component that has 3 different views over the same data.

![screenshot of a component with three different views](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/10/Picture2-2.png)

### Try it yourself

Interested in trying it out? You're in luck! We have an early [prototype to play with](https://adaptivecardsci.z5.web.core.windows.net/pr/4894/designer), note that it is *pre-alpha and will be buggy!*

![Screenshot of a Stock component in the Card Designer](https://developer.microsoft.com/en-us/microsoft-365/blogs/wp-content/uploads/2020/10/Picture3-1.png)

1.  Load up the Designer from the above URL.
2.  Drag over a **Component** from Card Elements toolbox on the left.
3.  On the designer surface, select the Component, and click **Choose...**
4.  A dialog should open with a list of available components, this might take ~30 seconds or so due to the service starting up.
5.  Click on the **iextrading.com/stockQuote** component.
6.  Change the **Element Properties** and observe the component UI updating. E.g., Set **Change value** to **-2.69**
7.  Play around with it by mix-and-matching different components that are currently available.

### Want to contribute components?

[Component definitions are stored in a GitHub repo](https://github.com/microsoft/adaptivecards-templates/tree/components/components) and published to a service. They are purely declarative files that can be downloaded directly on the client without having to manually build up Adaptive Card UI directly. This means anyone can contribute new Components just by opening a PR in this repo and sharing them with the world.

Let us know on [GitHub](https://github.com/microsoft/AdaptiveCards/issues/4761) or [Productboard](https://adaptivecards.productboard.com/portal/1-adaptive-cards-features/tabs/c88173a2-a3a1-4bc5-ad15-11051b3c7942/features/5478079/portal/expanded) if components is something you would benefit from in your day-to-day card usage!

Watch the call here

<iframe width="560" title="Community Call Recording" height="315" src="https://www.youtube.com/embed/rG5QtL4vhRk" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen="allowfullscreen"></iframe>

### Resources

-   [Watch the latest Adaptive Cards session from Build 2020](https://aka.ms/m365sk134)
-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)
-   <https://aka.ms/ACFeatures> -- Let us know what features you need

Next month's call will be held on **Thursday, November 12, 2020 at 9:00am PST.** We look forward to talking to you then! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Office Development YouTube Channel](https://www.youtube.com/channel/UCV_6HOhwxYLXAGd-JOqKPoQ)

### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)

The Adaptive Cards developer community call is on the 2nd Thursday of each month. We will provide you with the opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.
