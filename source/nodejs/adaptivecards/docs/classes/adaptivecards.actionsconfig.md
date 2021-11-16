[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ActionsConfig

# Class: ActionsConfig

[adaptivecards](../modules/adaptivecards.md).ActionsConfig

## Table of contents

### Constructors

- [constructor](adaptivecards.actionsconfig.md#constructor)

### Properties

- [actionAlignment](adaptivecards.actionsconfig.md#actionalignment)
- [actionsOrientation](adaptivecards.actionsconfig.md#actionsorientation)
- [allowTitleToWrap](adaptivecards.actionsconfig.md#allowtitletowrap)
- [buttonSpacing](adaptivecards.actionsconfig.md#buttonspacing)
- [iconPlacement](adaptivecards.actionsconfig.md#iconplacement)
- [iconSize](adaptivecards.actionsconfig.md#iconsize)
- [maxActions](adaptivecards.actionsconfig.md#maxactions)
- [preExpandSingleShowCardAction](adaptivecards.actionsconfig.md#preexpandsingleshowcardaction)
- [showCard](adaptivecards.actionsconfig.md#showcard)
- [spacing](adaptivecards.actionsconfig.md#spacing)

### Methods

- [toJSON](adaptivecards.actionsconfig.md#tojson)

## Constructors

### constructor

\+ **new ActionsConfig**(`obj?`: _any_): [_ActionsConfig_](host_config.actionsconfig.md)

#### Parameters:

| Name   | Type  |
| :----- | :---- |
| `obj?` | _any_ |

**Returns:** [_ActionsConfig_](host_config.actionsconfig.md)

Defined in: [host-config.ts:264](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L264)

## Properties

### actionAlignment

• **actionAlignment**: [_ActionAlignment_](../enums/enums.actionalignment.md)

Defined in: [host-config.ts:261](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L261)

---

### actionsOrientation

• **actionsOrientation**: [_Orientation_](../enums/enums.orientation.md)

Defined in: [host-config.ts:260](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L260)

---

### allowTitleToWrap

• **allowTitleToWrap**: _boolean_= false

Defined in: [host-config.ts:263](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L263)

---

### buttonSpacing

• **buttonSpacing**: _number_= 20

Defined in: [host-config.ts:257](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L257)

---

### iconPlacement

• **iconPlacement**: [_ActionIconPlacement_](../enums/enums.actioniconplacement.md)

Defined in: [host-config.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L262)

---

### iconSize

• **iconSize**: _number_= 16

Defined in: [host-config.ts:264](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L264)

---

### maxActions

• **maxActions**: _number_= 5

Defined in: [host-config.ts:255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L255)

---

### preExpandSingleShowCardAction

• `Optional` **preExpandSingleShowCardAction**: _undefined_ \| _boolean_= false

Defined in: [host-config.ts:259](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L259)

---

### showCard

• `Readonly` **showCard**: [_ShowCardActionConfig_](host_config.showcardactionconfig.md)

Defined in: [host-config.ts:258](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L258)

---

### spacing

• **spacing**: [_Spacing_](../enums/enums.spacing.md)

Defined in: [host-config.ts:256](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L256)

## Methods

### toJSON

▸ **toJSON**(): _object_

**Returns:** _object_

| Name                            | Type                                                          |
| :------------------------------ | :------------------------------------------------------------ |
| `actionAlignment`               | _string_                                                      |
| `actionsOrientation`            | _string_                                                      |
| `buttonSpacing`                 | _number_                                                      |
| `maxActions`                    | _number_                                                      |
| `preExpandSingleShowCardAction` | _undefined_ \| _boolean_                                      |
| `showCard`                      | [_ShowCardActionConfig_](host_config.showcardactionconfig.md) |
| `spacing`                       | _string_                                                      |

Defined in: [host-config.ts:291](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L291)
