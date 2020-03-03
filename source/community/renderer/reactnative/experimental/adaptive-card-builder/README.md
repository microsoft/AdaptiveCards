
## Description

This module uses our [AdaptiveCards renderer package](https://www.npmjs.com/package/adaptivecards-reactnative) and a mapper to support card types other than AdaptiveCards. Here we map the payloads of MS cards such as HeroCard, ThumbnailCard, etc to Adaptive card payload format.

## Supported Cards

As of now, this mapper supports below types of cards.

*  [ Hero Card ](https://docs.microsoft.com/en-us/microsoftteams/platform/concepts/cards/cards-reference#example-hero-card)
*  [ Thumbnail Card](https://docs.microsoft.com/en-us/microsoftteams/platform/concepts/cards/cards-reference#thumbnail-card)

## Payload Mapper

The payload mapper file `AdaptiveCardBuilder.js` builds the payload for AdaptiveCard from any HeroCard/ThumbnailCard payload content.

## Test

Follow the below steps to run the sample project in local machine.

* Clone the Repo `https://github.com/microsoft/AdaptiveCards.git`
* Navigate to source/reactnative/ **>** Run **`npm install`**
* iOS **> `react-native run-ios`**
* Android **> `react-native run-android`**
* Click on **`Other Cards`** section