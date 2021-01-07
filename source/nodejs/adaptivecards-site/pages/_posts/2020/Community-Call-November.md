---
title: 🎉  Pic2Card Relase
subtitle: Generate Adaptivecard by Uploading Card Image
date: 2020-11-01
github_username: haridas

---

We are excited share this, finally the **pic2card** service is available on https://adaptivecards.io/designer.

Pic2Card help the new AdpativeCard users to try out card generation by simply uploading a card image. This further reduce the learning cureve of needed to develop adaptive cards using the designer. AdaptiveCard Designer's whole idea was to help the card designers to create new cards. Designer provides a WYSWYG IDE environment to card developers to create their own cards if the template designs aren't fitting their requirements. Here is what team Imageinea want to pitch in and make this process much more easier for the new AdaptiveCards users by simply upload a **card image** that you got from internet or from your designer, upload and right away get your adaptivecard representation of it.

Go ahead and play with it, and let's know your feedbacks via github issues.

## How to use this Feature

![Pic2Card](Pic2Card/pic2card.gif)

## What's Pic2Card

Pic2Card converts image to adaptivecard card schema. The card generated will reproduce the image text, color and font details from the iamge so that the final card looks almost like the image uploaded to the pic2card service.

![what-is-pic2card](Pic2Card/whatispic2card.png)

## Pipeline

We aren't discussed anything much about its inernals till now, here it's. We have both ML and other processing involved to recreate the card from the image. The entire pipeline is shown below. In which the two main parts are the Machine Learning model which identifies the bounding boxes of each element that we need to be extracted for the card, and the second one is the remaining pipeline which does all the layout setting, property extraction etc, based on the ML model output.

![pic2card-pipeline](Pic2Card/pic2card_pipeline.png)


This entire pipeline is part of our backend [pic2card](https://github.com/microsoft/AdaptiveCards/tree/main/source/pic2card) service, which is hosted in azure functions. The frontend part of the pic2card is integrated with the [AdaptiveCards Designer](https://github.com/microsoft/AdaptiveCards/tree/main/source/nodejs/adaptivecards-designer).

## Contribute

Try the service and Let's know your feedbaks on [github issues](https://github.com/microsoft/AdaptiveCards/issues).

@Team Imaginea
