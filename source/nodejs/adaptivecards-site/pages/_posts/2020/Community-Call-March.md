---
title: 📣 Community Call - March 12, 2020
subtitle: Adaptive Card Management System - Part 2
date: 2020-03-12
featured_image: https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/03/New-Template-960x540.png
github_username: jessHuh
---

Agenda for this month's call, hosted by Matt Hidinger, included a conversation about the new concept we are calling the Adaptive Cards Management System (ACMS). Our team working on this showed a preview of the ACMS admin portal, how to render an adaptive card on Microsoft Teams using Power Automate and what's next to turn this preview into a live offering.

### A live preview of the "Adaptive Card Management System" (ACMS)

We're excited to share an early exploration of a concept we're calling the "Adaptive Cards Management System (ACMS)". ACMS is a supplementary product of Adaptive Cards that allows business users and professional developers to create, organize, and use Adaptive Card templates all within a cohesive turn-key solution.

ACMS is comprised of two parts:

-   **Front-end card management portal**: Designers or frontend developers can design and publish Adaptive Card templates directly within the user-friendly web-based interface.
-   **Back-end REST API**: Developers can utilize the ACMS REST API to retrieve published Adaptive Card templates and bind it with data dynamically.

### A preview of the ACMS Admin Portal

On the **Admin Portal Dashboard**, users can see a summary of card management. Users can browse recently edited and recently viewed cards as well as tags which are associated with their cards.

![A screenshot of ACMS dashboard.](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/03/New-Template-1024x577.png)

On the **New Template** page, users can create and edit Adaptive Cards. Users can expect to create Adaptive Cards effortlessly since [Adaptive Cards Designer Tool](https://adaptivecards.io/designer/) is nicely embedded into the ACMS Admin Portal.

![](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/03/A-screenshot-1024x522.png)

If you click a card on the Dashboard, users will land in **Template View** page where they can check all the details of the card. They can share and publish cards here too! If users **publish** a card template, it can later be retrieved at "run-time" via the ACMS REST API.

![A screenshot of ACMS template view web-page.](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/03/ACMS-template-1024x578.png)

### Now, let's render an adaptive card on Microsoft Teams using Power Automate!

Once you publish your card, you can retrieve your cards through ACMS API!

Now what I want to do is render my adaptive card on Microsoft Teams channel using Microsoft Power Automate. Here, I am getting my card using ACMS API through Microsoft Power Automate. After that, I am passing my card into Teams Connector to render the card on Teams Channel.

![A screenshot of a flow of Microsoft Power Automate.](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/03/Microsoft-Power-1024x507.png)

Once I trigger the power automate flow, voila, the adaptive card is rendered on Teams!

![A screenshot of Microsoft Teams channel. An adaptive cards is rendered on the channel by Microsoft Power Automate. ](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/03/Microsoft-Teams-3-1024x567.png)

A screenshot of Microsoft Teams channel. An adaptive cards is rendered on the channel by Microsoft Power Automate.

### What's Next?

In the short-term, we are working on improved template versioning and sharing features. We are hoping to cover these in more details on the April community call!

In the long-term, we are still working out the best way to turn this product from an exploration into a full-fledged offering. **If this product would help you at your workplace,** [**please let us know!**](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/55-card-author-services)

### For more....

Take a look at the video below for more details and keep an eye on this blog for a deep dive once the feature is more complete. See you soon 😊

Watch the call here.

<iframe width="560" height="315" title="Adaptive Cards Community Call-March 2020" src="https://www.youtube.com/embed/l4PGXwzvVac" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen="allowfullscreen"></iframe>

Resources from this month's call

-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)
-   [Adaptive Card Template Service](https://docs.microsoft.com/en-us/adaptive-cards/templating/service)
-   [New Designer Preview](https://adaptivecardsci.z5.web.core.windows.net/pr/3508/designer/?preview=1)
-   <https://aka.ms/ACFeatures> -- Let us know what features you need

Next month's call will be held on **Thursday, April 9, 2020 at 9:00am PST.** We look forward to talking to you then! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Office Development YouTube Channel](https://na01.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.youtube.com%2Fchannel%2FUCV_6HOhwxYLXAGd-JOqKPoQ&data=04%7C01%7Cv-chargr%40microsoft.com%7Cbaeead6e3a844690785d08d56d9e6864%7Cee3303d7fb734b0c8589bcd847f1c277%7C1%7C0%7C636535449508737676%7CUnknown%7CTWFpbGZsb3d8eyJWIjoiMC4wLjAwMDAiLCJQIjoiV2luMzIiLCJBTiI6Ik1haWwifQ%3D%3D%7C-2&sdata=emAMNFO82YoWjc2hnXShDlBPRR3jOPxAAfJLTKozgYk%3D&reserved=0)

### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)
