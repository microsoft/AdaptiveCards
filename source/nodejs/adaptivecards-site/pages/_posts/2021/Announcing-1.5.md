---
title: 🎉 Announcing Adaptive Cards 1.5
subtitle: RTL, Text masking, ActionSet overflow, Tooltip for actions, and Table element!
date: 2021-10-08
github_username: JeanRoca
twitter: jpthepm
---

We are excited to announce the release of Adaptive Cards 1.5!

This release contains some highly requested asks from our community as well as improvements to accessibility. One of our most requested features has been support for a Table element and we are happy to support this in Adaptive Cards 1.5!

## New features

1. [RTL](https://github.com/microsoft/AdaptiveCards/blob/main/specs/features/RTL.md)
2. [Input.Text Masking](https://github.com/microsoft/AdaptiveCards/issues/4673)
3. [ActionSet Overflow](https://github.com/microsoft/AdaptiveCards/issues/4715)
4. [Tooltip for Actions](https://github.com/microsoft/AdaptiveCards/issues/4668)
5. [Tables](https://github.com/microsoft/AdaptiveCards/blob/main/specs/features/Tables.md)
6. [Static Filtered ChoiceSet](https://github.com/microsoft/AdaptiveCards/issues/4713)
7. [Action.isEnabled](https://github.com/microsoft/AdaptiveCards/issues/4670)

## A closer look
### RTL Support
Right to left support will enable users from around the globe. Begining in 1.5, users will now be able to set this optional `rtl` boolean at the `Adaptive Card`, `Container`, and `Column` level.

![rtl-sample](rtl-sample.png)

### Input.Text Masking
By setting `style` to `password` in `Input.Text`, card authors will now have the ability to mask text such as passwords.

![masking-sample](masking-sample.png)

### ActionSet Overflow
The ActionSet Overflow flyout menu will allow card authors to provide additional actions on their card when limited space is available. This feature introduces the optional `mode` property to all action types. If this `mode` property is set to `secondary` for a given action, then a `...` overflow menu will render next to the actions that are set to `primary`.

![overflow-sample](overflow-sample.gif)

### Tooltip for Actions
This feature will now allow card authors to specify text that should be displayed to the end user when they hover over an action. Narration software will also pick up on the text further improving our accessibility story. Text can be set using the `tooltip` property for actions.

![tooltip-sample](tooltip-sample.png)

### 🆕Table Element🆕
The table element has been a highly requested feature and is now available in 1.5. This means that card authors will no longer need to nest `ColumnSets` to mimic table-like behavior and this new approach for tabular data is much more accessible. This new table element will have a concept of columns and rows working as you would expect it to. Note: advanced functionality like sorting and dynamic sizing is not supported in this initial release.

![table-sample](table-sample.gif)

### Static Filtered ChoiceSet
`Input.ChoiceSet` has been improved with the addition of a new `style` known as `filtered`. Setting the `style` to `filtered` will enable search and auto complete on the `Input.ChoiceSet` for a static list of choices.

![choiceset-sample](choiceset-sample.gif)

### Action.isEnabled
All actions will now have a boolean `isEnabled` property that is initially set to `true`. Setting this property to `false` will both visually and functionaly disable the element associated with the action.

![isEnabled-sample](isEnabled-sample.png)

## When can I use it?

These features are available today for you to test in our designer! We will keep working closely with our partners to ensure they can support this update as soon as possible. [The Adaptive Cards community call](http://aka.ms/adaptivecardscommunitycall) and our [partner status](https://docs.microsoft.com/en-us/adaptive-cards/resources/partners) page are both great resources to find out when these updates are supported on different hosts.

## Learn more

Check out the [full release notes](https://github.com/microsoft/AdaptiveCards/releases/tag/21.09) to learn more and get started!
