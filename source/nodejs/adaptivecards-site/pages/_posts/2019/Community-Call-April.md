---
title: 📣 Community Call - April 11, 2019
subtitle: Update on v1.2 release and a new way to sync the designer with an Android device
date: 2019-04-11
featured_image: https://developer.microsoft.com/en-us/graph/blogs/wp-content/uploads/2019/04/image-1.jpg
github_username: matthidinger
twitter: matthidinger
---

Welcome to our new Adaptive Cards community call series for 2019, the 2nd Thursday of each month. We are excited to provide you with a monthly opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.

You can download a recurring monthly calendar invite at <https://aka.ms/adaptivecardscommunitycall>.

Agenda for this month's call included:

### Update on the v1.2 release

-   Take a look at the [features here](https://github.com/Microsoft/AdaptiveCards/issues/2444)
-   We walked through a few demos showcasing 1.2 features
-   The release is targeting the end of April

### Demo: Sync the Designer on your PC to your Android Phone

Andrew Leader shows us a custom version of the Adaptive Card Designer that adds QR-code-based real-time syncing to an Android device. Our goal in the coming months will be to integrate this functionality into the adaptivecards.io designer.

![Adaptive Card designer in a browser on PC and android device screenshot showing the same card in both](https://developer.microsoft.com/en-us/graph/blogs/wp-content/uploads/2019/04/image-1.jpg)

**Try it yourself** by loading up this custom Designer at [http://adaptivecards-sharing.azurewebsites.net/designer](http://adaptivecards-sharing.azurewebsites.net/designer/)

Then install the **Adaptive Cards Visualizer** on Google Play. Scan the QR code from the designer and watch your Android device instantly replicate what you're designing on your PC.
[![Google Play button](https://developer.microsoft.com/en-us/graph/blogs/wp-content/uploads/2019/04/image-2-300x116.png)](https://play.google.com/store/apps/details?id=io.adaptivecards.adaptivecardsvisualizer_master)

### Demo: Adaptive Cards for Teams using Microsoft Flow

Audrie Gordon walks us through a hypothetical construction company that uses Teams, SharePoint, and Flow to automate some business processes. This company tracks their change orders in Excel, which when modified kicks off a Microsoft Flow that calculates the schedule impact and generates an Adaptive Card --<wbr> which gets automatically sent to a Microsoft Teams channel, making sure the organization is aware of the schedule impact. This is a really neat usage of Adaptive Cards in Teams without having to write any code. Take a look at the call and these links for more.

-   [Short 'What is Flow' Video](https://www.youtube.com/watch?v=uY0rjTjebZ4)
-   [Flow Learning Resources](https://flow.microsoft.com/blog/microsoft-flow-learning-resources-materials/)
-   The date expression used: convertTimeZone(utcnow(),'UTC','Pacific Standard Time','MMM-dd-yyyy HH:mm')
-   [Audrie's first impressions with adaptive cards on video](https://www.youtube.com/watch?v=8CKjcl_wAKQ)
-   [Microsoft Flow's YouTube Channel](https://www.youtube.com/channel/UCG98S4lL7nwlN8dxSF322bA)
-   Find Audie on Twitter [@ArtsyPowerApper](https://twitter.com/ArtsyPowerApper)

Watch the call here.

<iframe title="Video of the community call" width="560" height="315" src="https://www.youtube.com/embed/FSfSuGN2yVw" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

Next month's call will be held on Thursday, May 9th, 2019 at 9:00am PST. We look forward to talking to you then.

### Resources:

Adaptive Cards community call

-   Recurring monthly community call calendar invite -- <https://aka.ms/adaptivecardscommunitycall>.
-   Previous monthly call recordings -- [Office Development YouTube Channel](https://na01.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.youtube.com%2Fchannel%2FUCV_6HOhwxYLXAGd-JOqKPoQ&data=04%7C01%7Cv-chargr%40microsoft.com%7Cbaeead6e3a844690785d08d56d9e6864%7Cee3303d7fb734b0c8589bcd847f1c277%7C1%7C0%7C636535449508737676%7CUnknown%7CTWFpbGZsb3d8eyJWIjoiMC4wLjAwMDAiLCJQIjoiV2luMzIiLCJBTiI6Ik1haWwifQ%3D%3D%7C-2&sdata=emAMNFO82YoWjc2hnXShDlBPRR3jOPxAAfJLTKozgYk%3D&reserved=0)

Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)