[Adaptive Cards Javascript SDK](../README.md) › [ActionsConfig](actionsconfig.md)

# Class: ActionsConfig

## Hierarchy

* **ActionsConfig**

## Index

### Constructors

* [constructor](actionsconfig.md#constructor)

### Properties

* [actionAlignment](actionsconfig.md#actionalignment)
* [actionsOrientation](actionsconfig.md#actionsorientation)
* [allowTitleToWrap](actionsconfig.md#allowtitletowrap)
* [buttonSpacing](actionsconfig.md#buttonspacing)
* [iconPlacement](actionsconfig.md#iconplacement)
* [iconSize](actionsconfig.md#iconsize)
* [maxActions](actionsconfig.md#maxactions)
* [preExpandSingleShowCardAction](actionsconfig.md#optional-preexpandsingleshowcardaction)
* [showCard](actionsconfig.md#showcard)
* [spacing](actionsconfig.md#spacing)

### Methods

* [toJSON](actionsconfig.md#tojson)

## Constructors

###  constructor

\+ **new ActionsConfig**(`obj?`: any): *[ActionsConfig](actionsconfig.md)*

*Defined in [host-config.ts:190](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L190)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ActionsConfig](actionsconfig.md)*

## Properties

###  actionAlignment

• **actionAlignment**: *[ActionAlignment](../enums/actionalignment.md)* = Enums.ActionAlignment.Left

*Defined in [host-config.ts:187](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L187)*

___

###  actionsOrientation

• **actionsOrientation**: *[Orientation](../enums/orientation.md)* = Enums.Orientation.Horizontal

*Defined in [host-config.ts:186](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L186)*

___

###  allowTitleToWrap

• **allowTitleToWrap**: *boolean* = false

*Defined in [host-config.ts:189](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L189)*

___

###  buttonSpacing

• **buttonSpacing**: *number* = 20

*Defined in [host-config.ts:183](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L183)*

___

###  iconPlacement

• **iconPlacement**: *[ActionIconPlacement](../enums/actioniconplacement.md)* = Enums.ActionIconPlacement.LeftOfTitle

*Defined in [host-config.ts:188](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L188)*

___

###  iconSize

• **iconSize**: *number* = 24

*Defined in [host-config.ts:190](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L190)*

___

###  maxActions

• **maxActions**: *number* = 5

*Defined in [host-config.ts:181](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L181)*

___

### `Optional` preExpandSingleShowCardAction

• **preExpandSingleShowCardAction**? : *boolean* = false

*Defined in [host-config.ts:185](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L185)*

___

###  showCard

• **showCard**: *[ShowCardActionConfig](showcardactionconfig.md)* = new ShowCardActionConfig()

*Defined in [host-config.ts:184](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L184)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)* = Enums.Spacing.Default

*Defined in [host-config.ts:182](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L182)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:217](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L217)*

**Returns:** *object*

* **actionAlignment**: *string* = Enums.ActionAlignment[this.actionAlignment]

* **actionsOrientation**: *string* = Enums.Orientation[this.actionsOrientation]

* **buttonSpacing**: *number* = this.buttonSpacing

* **maxActions**: *number* = this.maxActions

* **preExpandSingleShowCardAction**: *boolean* = this.preExpandSingleShowCardAction

* **showCard**: *[ShowCardActionConfig](showcardactionconfig.md)‹›* = this.showCard

* **spacing**: *string* = Enums.Spacing[this.spacing]
