---
title: 📣 Community Call - December 12, 2019
subtitle: Power Automate and the Template Service
date: 2019-12-12
featured_image: https://developer.microsoft.com/en-us/sharepoint/blogs/wp-content/uploads/2019/12/Image-adaptive-card.png
github_username: matthidinger
twitter: matthidinger
---

Welcome to our Adaptive Cards community call series, the 2nd Thursday of each month. We are excited to provide you with a monthly opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.

Agenda for this month's call, hosted by Matt Hidinger, included:

### Power Automate and the Template Service

The goal of [Adaptive Card Templating](https://docs.microsoft.com/en-us/adaptive-cards/templating/) is to **save you time** when building cards. And what's better than building a card template yourself? *Having someone else build it!*

The [Adaptive Card Template Service](https://docs.microsoft.com/en-us/adaptive-cards/templating/service) enables the community to contribute, discover, and share reusable templates over common data types, like the Microsoft Graph. If someone already wrote a template over the same data you have, why not use it! And while this service is already available in preview form, we wanted to go one step further: make it simple to use from Power Automate.

### What the heck is Power Automate?

Last month, Microsoft rebranded Flow into Power Automate. [Power Automate](https://flow.microsoft.com/en-us/) is part of the Microsoft Power Platform which allows anyone (even non-developers) to optimize business workflows without having to write any code --<wbr> all from the convenience of their browser.

Below is a Flow I created for demo purposes during the community call. It's a simple Flow that activates on the push of a button and presents an Adaptive Card to a Teams channel. **The magic is that I didn't have to build an Adaptive Card at all, and the entire thing took literally 5 minutes to create!**

**![Screenshot of a Power Automate flow using the custom Adaptive Card connector](https://developer.microsoft.com/en-us/sharepoint/blogs/wp-content/uploads/2019/12/Image-adaptive-card.png)**

In the real world, Flows are typically kicked off by a "trigger." Triggers can range from receiving an email, a message in a Teams channel, an issue filed in GitHub, to just about anything you can imagine. And of course, Power Automate is extensible so third parties can contribute Triggers and Actions to make your Flows even more powerful.

### The Adaptive Card Custom Connector

Did you notice the box above that says, "Populate an Adaptive Card with a template and data"? That is a Custom Connector that I hope to make available shortly. It offers the same functionality as the template service, which means you can start using Adaptive Cards without having to write one yourself --<wbr> or even having to write any code!

![Screenshot of a new preview of an Adaptive Card Power Automate Connector](https://developer.microsoft.com/en-us/sharepoint/blogs/wp-content/uploads/2019/12/Adaptive-cards-2-917x1024.png)

We're very excited about the possibilities here to make Adaptive Cards available to more people and with less effort. Stay tuned as we figure out the next steps to make this connector publicly available.

### Lots of Designer improvements coming soon

We also demoed some major improvements coming soon to the Designer. You can even [try it out](https://adaptivecardsci.z5.web.core.windows.net/pr/3508/designer/?preview=1) right now!

### Improved Data Binding UI

As templating gains traction, we want to ensure a smooth designer experience when building templates.

In the upcoming release you'll be able to select any element and quickly bind it to data using the **Bind...** flyout. This same dialog is available in the **Element Properties** pane as well.

![Screenshot of the designer with a new data binding flyout ](https://developer.microsoft.com/en-us/sharepoint/blogs/wp-content/uploads/2019/12/Adaptive-cards-3.png)

### Schema Version Selection

We're also addressing a long-standing pain point: making sure the Designer builds cards that are as close as possible to the Host app you're using. While we are working diligently with our partners to update to the latest Adaptive Cards version, we know schedules can be tricky and sometimes unforeseen compatibility bugs can delay the update.

To help alleviate this we've added a new **Target version** drop-down in in the designer toolbar. This drop-down helps ensure you won't get any nasty surprises after you design a card and then try using it in a real app, like Teams or Outlook, which may not yet be on the latest version.

![Screenshot of the designer with Schema Version Selector drop down](https://developer.microsoft.com/en-us/sharepoint/blogs/wp-content/uploads/2019/12/Adaptive-cards-4.png)

To use it, simply select the Schema Version that you're targeting, and the Designer will remove elements and properties that are not available, as well as show warnings for any incompatible fields in the JSON.

[**Try it out**](https://adaptivecardsci.z5.web.core.windows.net/pr/3508/designer/?preview=1), and please [let us know](https://github.com/Microsoft/AdaptiveCards/issues/new?title=%5BDesigner%5D%20%5BYour%20feedback%20title%20here%5D&body=%5BYour%20detailed%20feedback%20here%5D) if you hit any snags or have suggestions!

### **Happy Holidays and thank you for a fantastic 2019!**

I can't believe this marks 12 months of the Adaptive Cards community call. I was nervous making this monthly commitment at the start of the year, mainly because I wasn't sure we could come up with relevant content for you folks every month. Thankfully the feedback has been positive, and we will be continuing the series in 2020! We're always looking for feedback and suggestions to make these calls more valuable to you, so please don't hesitate to reach out.

**Be sure to** [**add the 2020 meeting series**](https://aka.ms/adaptivecardscommunitycall) **to your calendar --<wbr> same time, same place!**

See you in 2020!

Watch the call here.

<iframe width="560" height="315" allowfullscreen="allowfullscreen" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" frameborder="0" src="https://www.youtube.com/embed/B9d354AY_GA"></iframe>

Resources from this month's call

-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)
-   [Adaptive Card Template Service](https://docs.microsoft.com/en-us/adaptive-cards/templating/service)
-   [New Designer Preview](https://adaptivecardsci.z5.web.core.windows.net/pr/3508/designer/?preview=1)
-   <https://aka.ms/ACFeatures> -- Let us know what features you need

Next month's call will be held on **Thursday, January 9th, 2020 at 9:00am PST.** We look forward to talking to you then! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Office Development YouTube Channel](https://na01.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.youtube.com%2Fchannel%2FUCV_6HOhwxYLXAGd-JOqKPoQ&data=04%7C01%7Cv-chargr%40microsoft.com%7Cbaeead6e3a844690785d08d56d9e6864%7Cee3303d7fb734b0c8589bcd847f1c277%7C1%7C0%7C636535449508737676%7CUnknown%7CTWFpbGZsb3d8eyJWIjoiMC4wLjAwMDAiLCJQIjoiV2luMzIiLCJBTiI6Ik1haWwifQ%3D%3D%7C-2&sdata=emAMNFO82YoWjc2hnXShDlBPRR3jOPxAAfJLTKozgYk%3D&reserved=0)

### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)