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

\+ **new ActionsConfig**(`obj?`: *any*): [*ActionsConfig*](host_config.actionsconfig.md)

#### Parameters:

Name | Type |
:------ | :------ |
`obj?` | *any* |

**Returns:** [*ActionsConfig*](host_config.actionsconfig.md)

Defined in: [host-config.ts:264](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L264)

## Properties

### actionAlignment

• **actionAlignment**: [*ActionAlignment*](../enums/enums.actionalignment.md)

Defined in: [host-config.ts:261](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L261)

___

### actionsOrientation

• **actionsOrientation**: [*Orientation*](../enums/enums.orientation.md)

Defined in: [host-config.ts:260](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L260)

___

### allowTitleToWrap

• **allowTitleToWrap**: *boolean*= false

Defined in: [host-config.ts:263](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L263)

___

### buttonSpacing

• **buttonSpacing**: *number*= 20

Defined in: [host-config.ts:257](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L257)

___

### iconPlacement

• **iconPlacement**: [*ActionIconPlacement*](../enums/enums.actioniconplacement.md)

Defined in: [host-config.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L262)

___

### iconSize

• **iconSize**: *number*= 16

Defined in: [host-config.ts:264](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L264)

___

### maxActions

• **maxActions**: *number*= 5

Defined in: [host-config.ts:255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L255)

___

### preExpandSingleShowCardAction

• `Optional` **preExpandSingleShowCardAction**: *undefined* \| *boolean*= false

Defined in: [host-config.ts:259](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L259)

___

### showCard

• `Readonly` **showCard**: [*ShowCardActionConfig*](host_config.showcardactionconfig.md)

Defined in: [host-config.ts:258](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L258)

___

### spacing

• **spacing**: [*Spacing*](../enums/enums.spacing.md)

Defined in: [host-config.ts:256](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L256)

## Methods

### toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

Name | Type |
:------ | :------ |
`actionAlignment` | *string* |
`actionsOrientation` | *string* |
`buttonSpacing` | *number* |
`maxActions` | *number* |
`preExpandSingleShowCardAction` | *undefined* \| *boolean* |
`showCard` | [*ShowCardActionConfig*](host_config.showcardactionconfig.md) |
`spacing` | *string* |

Defined in: [host-config.ts:291](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L291)
