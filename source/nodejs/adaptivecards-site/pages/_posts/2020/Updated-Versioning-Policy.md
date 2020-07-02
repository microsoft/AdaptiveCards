---
title: Updated Versioning and Release policy
subtitle: Packaging and release software can be complicated, here's what we're doing
date: 2020-07-05
github_username: matthidinger
twitter: matthidinger
---

## THIS IS A DRAFT

This is an early proposal and we may change these decisions before publishing this post :)

# Updated Versioning and Release policy

Versioning, releasing, and marketing software can be complicated. We're making some changes this year to clarify a few things that should help our customers and developers better understand **what the versions mean**, and **when to expect updates**.

## TL;DR

- Adaptive Cards is an umbrella term for multiple interconnected products: the Adaptive Card schema, the renderer SDKs, the templating schema and templating SDKs, and the card designer.
- Each of those products exist on different platforms and have their own release cycles.
- We will follow Semantic Versioning (SemVer) where possible, which means if any individual product has a major update or API breaking change, we will increment the version as appropriate for that product. As such, our different products will necessarily have different versions (e.g., the latest JavaScript rendering SDK may be version `2.0`, but the latest Adaptive Card Schema is `1.3`).  
- We're planning to release software every month, with whatever combination of products that are stable and ready to ship. These releases will be named after the year and month that they fall in (e.g., `2020.06`) and each product inside the release will be versioned on its own.
- Major feature updates will be released on a roughly 6 month interval.
- In general, when we talk about Adaptive Cards as the umbrella product, we are talking about the latest Adaptive Card Schema version and the major functionality. E.g., Adaptive Cards 2.0 will be the first major rev of the schema, and include a major new feature called "Universal Actions".

## Deep dive into each section

## Schema versions:

- **V1.2**: latest shipped
- **V1.3**: In progress, including Input Validation, and likely only input validation
- **V2.0**: Announced at Build, this is the version which we will introduce Universal Actions as a feature 

Schema versions are what the majority of our customers know about, since most of our customers are Card Authors and not using the renderer SDKs. It’s the version that’s all over our docs, on our Roadmap slide, inside the card payload “version” property, the Designer Target Version dropdown, and Schema Explorer. It is the broad/all-encompassing feature-set when we describe what the product actually is and it spans all renderer SDKs.

## Renderer versions:

- **JavaScript**: Recently changed to V2.0 due to some major API breaking changes and to [support all prior and future schema versions](https://www.npmjs.com/package/adaptivecards/v/2.0.0-rc.0#fyi-new-policy-on-versioning) (which was necessary for the Designer)
- **ReactNative**: V2.0 (Imaginea chose to bump the major version to follow SemVer rules regarding API changes)
- **All others**: V1.2.x, but we are looking to bump these to 2.0. My understanding is this is due to similar reasons as Imaginea, where we had some API changes in main and we want to take them now. 

Unlike the Schema, Renderers are developer libraries which should follow Semantic Versioning rules. We should default to those rules unless we have a good reason not to, even if that means there is a disconnect from the SDK version and the Shema Version. So if we have a major API breaking change on one platform we should bump the major version of that SDK, otherwise we risk developers taking a patch release only to discover their builds are failing until they change their code. 

If there are no API breaking changes we can still bump the major version if we meet other SemVer criteria, or I suppose if we just “feel like it” – but in general, I think we should forego trying to keep all the different platforms on the same version since it feels like a losing battle and will compromise the SemVer rules on a specific platform.

## Templating 

v1.0 for .NET and JS

## Adaptive Card Designer

v1.0

## GitHub and Package releases

Every month, toward the end of the month, we will create a release in GitHub and publish updated packages that are ready to ship. 

These releases will be named after the calendar year/month: e.g., `2020.06` for the June, 2020 release.

