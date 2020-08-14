---
title: 📣 Community Call - July 11, 2019
subtitle: Adaptive Cards 💙 Fabric, and a new Template Service prototype
date: 2019-07-11
featured_image: https://developer.microsoft.com/en-us/access/blogs/wp-content/uploads/2019/07/Standard-Adaptive-Card-payload-using-Microsoft-UI-Fabric.jpg
github_username: matthidinger
twitter: matthidinger
---

Welcome to our Adaptive Cards community call series for 2019, the 2nd Thursday of each month. We are excited to provide you with a monthly opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we’ll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.

Agenda for this month’s call, hosted by Matt Hidinger, included: 

## Adaptive Cards 💙 Fabric

[Microsoft UI Fabric](https://developer.microsoft.com/en-us/fabric#/) helps React developers build and integrate Fluent experiences into various Microsoft products. This month we released the [adaptivecards-fabric](https://www.npmjs.com/package/adaptivecards-fabric) package, which makes "lighting up" an Adaptive Cards with Fabric components seamless. 

Below is a standard Adaptive Card payload, but many of the inputs are rendered using Fabric components. If you’re using Fabric and Adaptive Cards give it a shot and let us know your thoughts!

![Fabric screenshot](https://developer.microsoft.com/en-us/access/blogs/wp-content/uploads/2019/07/Standard-Adaptive-Card-payload-using-Microsoft-UI-Fabric.jpg)
 
## Adaptive Cards Template Service Prototype

We also walked through a very early preview of an “Adaptive Card Template Service”, with the goal of making it easy to visualize any type of data using Adaptive Cards templates. This service empowers anyone to author and share card templates with the world -- all with the simplicity of a GitHub backing store.

*Legal terms: this _alpha-level_ service is provided “as-is” with all faults and is not supported. Any data collection from the service is subject to the [Microsoft privacy statement](https://go.microsoft.com/fwlink/?LinkID=824704)*

The service currently offers some basic functionality:
 
•	**FIND** a template for a type of data (if one exists)
•	**GET** a known template. The template can then be used for client-side data binding using the [adaptivecards-template](https://www.npmjs.com/package/adaptivecards-templating) package. (See the [June community call](https://developer.microsoft.com/en-us/office/blogs/adaptive-cards-community-call-june-13-2019/) for more on this library)
•	**POPULATE** a known template with data server-side that can then be delivered to any adaptive card host

We’d love feedback on this service as you have it, please reach out to us on GitHub or Twitter if you have any thoughts, use-cases, or feedback! 

Currently we have no date on when this will be production-ready as we are eager to learn how customers might use the service before we determine what our MVP is.

![postman screenshot](https://developer.microsoft.com/en-us/access/blogs/wp-content/uploads/2019/07/preview-of-an-%E2%80%9CAdaptive-Card-Template-Service%E2%80%9D-768x708.png)

Watch the call here.
{% youtube s4EOZyKbKog %}


Next month’s call will be held on **Thursday, August 8th, 2019 at 9:00am PST**.  We look forward to talking to you then! Download a recurring calendar invite here at https://aka.ms/adaptivecardscommunitycall.
