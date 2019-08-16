---
title: 📣 Community Call - March 14, 2019
subtitle: Hacking GitHub Desktop to show Azure server stats
date: 2019-03-14
featured_image: https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2019/03/Image-1-1-1024x706.png
github_username: matthidinger
twitter: matthidinger
---

Welcome to our new Adaptive Cards community call series for 2019, the 2nd Thursday of each month. We are excited to provide you with a monthly opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.

You can download a recurring monthly calendar invite at <https://aka.ms/adaptivecardscommunitycall>.

Agenda for this month's call included

-   We'd love your 1-on-1 feedback, reach out if interested in a 30-minute call with the product team
-   Update on the [Data Binding proposal](https://github.com/Microsoft/AdaptiveCards/issues/2448) that was previewed during last month's call
-   Hacking GitHub Desktop to show Azure service stats

### Demo Concept: Hacking GitHub Desktop to show Azure server stats

Now that we have a data binding syntax that enables the separation of a card "template" from the data that powers it, we can start imagining a world where these reusable templates are shared between apps and services.

To illustrate this, I decided to "hack" the GitHub Desktop app, adding a tab that shows the live Azure stats of my currently selected repo.

Here you can see I'm in the AdaptiveCards repo, but there's a mysterious fourth tab in the top nav bar. When opened, I can see the live stats of [https://adaptivecards.io](https://adaptivecards.io/), including the last 3 deployments, and usage metrics.

![Adding a tab that shows the live Azure stats of my currently selected repo.](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2019/03/Image-1-1-1024x706.png)

To achieve this, all I had to do was teach GitHub Desktop to render Adaptive Cards. Then I created a few card templates over the Azure REST API, seen below.

![I created a few card templates over the Azure REST API](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2019/03/Image-2-1-1024x710.png)

This demo is just a "proof of concept" at this point, but we'd love your feedback on is this valuable for you. Would you use something like this in your solutions? Please let us know your thoughts!

Take a look at the video below for full details.

Watch the call here.

<iframe src="https://www.youtube.com/embed/POP_kOO8YP4" height="315" width="560"></iframe>

Next month's call will be held on Thursday, **April 11, 2019 at 9:00am PST**. We look forward to talking to you then!

### Resources

From March's call

-   [Data Bind Spec](https://github.com/Microsoft/AdaptiveCards/issues/2448)

Adaptive Cards community call

-   Recurring monthly community call calendar invite -- <https://aka.ms/adaptivecardscommunitycall>.
-   Previous monthly call recordings -- [Office Development YouTube Channel](https://na01.safelinks.protection.outlook.com/?url=https%3A%2F%2Fwww.youtube.com%2Fchannel%2FUCV_6HOhwxYLXAGd-JOqKPoQ&data=04%7C01%7Cv-chargr%40microsoft.com%7Cbaeead6e3a844690785d08d56d9e6864%7Cee3303d7fb734b0c8589bcd847f1c277%7C1%7C0%7C636535449508737676%7CUnknown%7CTWFpbGZsb3d8eyJWIjoiMC4wLjAwMDAiLCJQIjoiV2luMzIiLCJBTiI6Ik1haWwifQ%3D%3D%7C-2&sdata=emAMNFO82YoWjc2hnXShDlBPRR3jOPxAAfJLTKozgYk%3D&reserved=0)
