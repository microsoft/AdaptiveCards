---
title: 📣 Community Call - April 9, 2020 
subtitle: Adaptive Card Management System - Part 3
date: 2020-04-09
featured_image: https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/04/publis.png
github_username: jessHuh
---

Welcome to the final episode of the Adaptive Cards Management System (ACMS)!

**Hold on... Let's take a step back... What is ACMS?**

ACMS is a supplementary product of Adaptive Cards that allows business users and professional developers to create, organize, and use Adaptive Card templates all within a cohesive turn-key solution.

ACMS is comprised of two parts:

-   **Front-end card management portal**: Designers or frontend developers can design and publish Adaptive Card templates directly within the user-friendly web-based interface.
-   **Back-end REST API**: Developers can utilize the ACMS REST API to retrieve published Adaptive Card templates and bind them with data dynamically.

**Okay... But why should I use ACMS?**

The key benefits of ACMS will be **cost savings to organizations, improved ability to collaborate, and ease of installation**. The cost savings come from the simplified workflow, eliminating much of the tedious actions involved with using adaptive cards. Microsoft Teams will be empowered to collaborate since the latest templates will be available to everyone. Lastly, the tool is designed to be easy to install, available through NPM and supports many database providers.

**Awesome! How can I start ACMS?**

**We proudly announce that we now support a quick-start feature using the "Deploy to Azure" button on our** [**Github Repo**](https://github.com/microsoft/adaptivecards-templates/tree/dev/private-templates-service)**.** You can find a thorough explanation at the GitHub repository.

![A screenshot of deploy to azure button](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/04/deploy.png)

1.  Click the blue '**Deploy to Azure**'. Select the subscription and resource group under which you wish to deploy ACMS.
2.  Enter in the URL the portal will be hosted at into the '**Sites_adaptivecms_name**' field. Make sure this URL is added under the '**Redirect URIs**' section of your AAD App Registration. Detailed instructions and screenshots are listed below.
3.  Enter in the Azure Active Directory App Registration application (client) id into the '**App_id**' field.
4.  Enter the id of your App Service Plan into the '**Server_farm_id**' field.
5.  If 'Yes' is selected for '**Telemetry_opt_in**', we will collect feedback from your instance of ACMS using App Insights.
6.  Click '**Next**' and '**Deploy**'.

**A preview of the ACMS Admin Portal**

Okay, now that you've set up ACMS on your end, let's take a look!

On the **Admin Portal Dashboard**, users can see a summary of card management. Users can browse recently edited and recently viewed cards as well as tags that are associated with their cards.

![A screenshot of ACMS dashboard.](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/04/Admin-portal.png)

On the **New Template** page, users can create and edit Adaptive Cards. Users can expect to create Adaptive Cards effortlessly since [Adaptive Cards Designer Tool](https://adaptivecards.io/designer/) is nicely embedded into the ACMS Admin Portal.

![A screenshot of ACM new template web-page. Adaptive Cards Designer Tool is embedded in it. ](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/04/New-template.png)

If you click a card on the Dashboard, users will land in the **Template View** page where they can check all the details of the card. They can share and publish cards here too! If users **publish** a card template, it can later be retrieved at "run-time" via the ACMS REST API.

![A screenshot of ACMS template view web-page.](https://developer.microsoft.com/en-us/office/blogs/wp-content/uploads/2020/04/publis.png)

Now, it's all set! **You can consume the API from your source code or leverage Microsoft Power automate to fetch Adaptive Cards!** We are making YouTube tutorials on building a Power Automate Private Connector to use ACMS API, so stay tuned!

* Additional information regarding deploy to azure feature

Prerequisites:

-   Azure account
-   Azure Active Directory (AAD) App Registration (instructions below)
-   [Azure resource group](https://docs.microsoft.com/en-us/azure/azure-resource-manager/management/manage-resource-groups-portal)
-   Azure App Service Plan

### Creating a new AAD App Registration

1.  Go to the [Azure Portal](https://github.com/microsoft/adaptivecards-templates/blob/users/grzhan/docs/private-templates-service/portal.azure.com).
2.  In the searchbar, type 'Azure Active Directory' and select the AAD service.
3.  Select 'App Registrations' under the 'Manage' header.
4.  Click 'New registration'.
5.  Fill in the details for a new AAD registration. Under 'Redirect URI', enter the URL at which the admin portal is hosted at from the 'Deploy to Azure' instructions.
6.  Click 'Register'.

### For more....

Take a look at the video below for more details and keep an eye on this blog for a deep dive once the feature is more complete. See you soon!

Watch the call here

<iframe width="560" height="315" title="Adaptive Cards Community Call-April 2020" src="https://www.youtube.com/embed/Rpf3jTsap9k" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen="allowfullscreen"></iframe>

Resources from this month's call

-   [Adaptive Cards Roadmap](https://aka.ms/ACRoadmap)
-   [Adaptive Card Templating Overview](https://docs.microsoft.com/en-us/adaptive-cards/templating/)
-   [Adaptive Card Template Service](https://docs.microsoft.com/en-us/adaptive-cards/templating/service)
-   [New Designer Preview](https://adaptivecardsci.z5.web.core.windows.net/pr/3508/designer/?preview=1)
-   <https://aka.ms/ACFeatures> -- Let us know what features you need

Next month's call will be cancelled in lieu of the Microsoft Build Conference. We look forward to talking to virtually at the conference and we'll see everyone in June! Download a recurring calendar invite here at <https://aka.ms/adaptivecardscommunitycall>.

Check out the previous month's call recording on our [Microsoft 365 Development YouTube Channel](https://www.youtube.com/channel/UCV_6HOhwxYLXAGd-JOqKPoQ)

### Adaptive Cards feedback channels

-   [Issues and feature requests](https://github.com/Microsoft/AdaptiveCards/issues)
-   [Technical questions](https://stackoverflow.com/questions/tagged/adaptive-cards)
