---
title: 📣 Community Call - July, 2022
subtitle: Action.ToggleVisibility Deprecation (non-breaking change)
date: 2022-07-14
featured_image: https://pnp.github.io/blog/adaptive-cards-community-call/adaptive-cards-community-call-july-2022/images/recording-adaptive-cards-july-call_hufb42edcfeb6bfc1cc800f7fd057797ff_271174_700x0_resize_q100_h2_box_3.webp
github_username: JeanRoca
twitter: jpthepm
---

In this month’s community call the following topics were presented - Action.ToggleVisibility Deprecation (a non-breaking change for a control that needs to support accessibility requirements for all users), GA release for Adaptive Cards Handle Responses Connector, teaser on the React Native Adaptive Cards Renderer capability used in Microsoft Viva Connections mobile app to be demoed next month, and a 10-minute Q&A covering a host of topics - release schedule, integration, challenges, and demo requests. This call was hosted by [J.P. Roca](http://twitter.com/jpthepm) (Microsoft) \| @jpthepm. Recorded on July 14, 2022.

### Watch the call here

<iframe width="680" height="383" src="https://www.youtube.com/embed/YtnW60YHwS8" title="Community Call July 2022 video" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

### Agenda:
- Action.ToggleVisibility Deprecation – [00:34](https://youtu.be/YtnW60YHwS8?t=34)
- Adaptive Cards Handle Responses Connector in GA – [04:18](https://youtu.be/YtnW60YHwS8?t=258)
- React Native Adaptive Cards Renderer – [05:35](https://youtu.be/YtnW60YHwS8?t=335)
- Q&A – [06:14](https://youtu.be/YtnW60YHwS8?t=374)

### Topic summaries:
- **Action.ToggleVisibility Deprecation –** introduced in schema 1.2, Toggles (trigger action) the visibility of associated card elements. Why deprecating? The content changes on screen are not detectable by screen readers. Impact on card authors? None while developing a proper expander control that meets accessibility requirements. Let us know how you are using this capability today - issue 7678. This is a formality, not a breaking change.
- **Adaptive Cards Handle Responses Connector in GA –** the connector has been released into production, blog post coming soon, get an MSA account and try it at flow.microsoft.com. You can find learn more in the Microsoft Teams connector trigger documentation focused on responding to an Adaptive Card.
- **React Native Adaptive Cards Renderer** – developed and maintained by BigThinkCode and recently used in a Microsoft Viva Connections mobile app. Join the Adaptive Cards call next month to see a demo delivered by Vasanthakumar Sarpasayanam, CEO & Founder at BigThinkCode Technologies about using this capability.
- **Q & A –** topics include availability of WinUI 3 Renderer and v1.6 schema, adoption of latest GA schema version (v1.5) by Viva Connections (presently using V1.3 today) and by other groups in general - release schedule coordination. Incorporation of Microsoft Loop components, building Adaptive Cards presentations, and getting a Power Virtual Agent speaker on this call.

### Referenced in this call:
* **Action.ToggleVisibility Deprecation**
    * Tool – [Adaptive Cards Schema Explorer](https://adaptivecards.io/explorer/Action.ToggleVisibility.html)
    * Feedback - [[Feature Request] Action.ToggleVisibility -\> Expander Control \#7678](https://github.com/microsoft/AdaptiveCards/issues/7678) Adaptive Cards
* **Handle Responses Connector in GA**
    * Website – [Power Automate](https://powerautomate.microsoft.com/) \| flow.microsoft.com
    * Documentation Trigger - [When someone responds to an adaptive card](https://docs.microsoft.com/connectors/teams/#when-someone-responds-to-an-adaptive-card)
    * May call - [Handling multi-user responses for Adaptive Cards in Microsoft Teams](https://youtu.be/V0iTtOYcP6w) **-** [Josh Friedman](https://www.linkedin.com/in/josh-friedman-2a812254) (Microsoft)
    * MSA Account - [Getting Started with Group Managed Service Accounts](https://docs.microsoft.com/windows-server/security/group-managed-service-accounts/getting-started-with-group-managed-service-accounts)
* **React Native Adaptive Cards Renderer**
    * Tool npm - [adaptivecards-reactnative](https://www.npmjs.com/package/adaptivecards-reactnative)
    * Repo - [BigThinkcode/AdaptiveCards](https://github.com/Bigthinkcode/AdaptiveCards/tree/main)
* **Q&A**
    * Preview – [Adaptive Cards Designer v1.6 (windows.net)](https://adaptivecardsci.z5.web.core.windows.net/designer)
    * Article - [Announcing Adaptive Cards 1.5 GA](https://adaptivecards.io/blog/2021/Announcing-1.5/)
    * Microsoft Build Presentation: [Building great apps with the open platform of Windows (microsoft.com)](https://mybuild.microsoft.com/en-US/sessions/3a0b225f-279e-4973-8106-20ce58f16ed1?source=/home) (Windows 11 Widgets - a.k.a., Adaptive Cards at 40:56)
    * Feedback Portal – [Microsoft Viva Connections](https://feedbackportal.microsoft.com/feedback/forum/5092ec4b-1d1c-ec11-b6e7-0022481f8472)

### Resources in General: 
- Let us know the features you need    https://aka.ms/ACRoadmap
- Schema Explorer - https://adaptivecards.io/explorer/Action.Execute.html
- Designer - https://adaptivecards.io/designer/ 
- Get started with Templating - https://aka.ms/ACTemplating
- Browse the Adaptive Cards Code - https://aka.ms/ACRepo
- Find tools, sample cards, and more - https://www.madewithcards.io
- Contribution Guidelines – https://aka.ms/ACRepo 

### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)

The Adaptive Cards developer community call is on the 2nd Thursday of each month. We will provide you with the opportunity to learn about Adaptive Cards in general, how they could be a great tool in your applications and contribute to the evolution of the format and SDKs. Each month, we'll discuss new features we are bringing to the platform, our roadmap, and listen to your feedback and suggestions.