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

*Defined in [host-config.ts:200](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L200)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ActionsConfig](actionsconfig.md)*

## Properties

###  actionAlignment

• **actionAlignment**: *[ActionAlignment](../enums/actionalignment.md)* = Enums.ActionAlignment.Left

*Defined in [host-config.ts:197](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L197)*

___

###  actionsOrientation

• **actionsOrientation**: *[Orientation](../enums/orientation.md)* = Enums.Orientation.Horizontal

*Defined in [host-config.ts:196](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L196)*

___

###  allowTitleToWrap

• **allowTitleToWrap**: *boolean* = false

*Defined in [host-config.ts:199](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L199)*

___

###  buttonSpacing

• **buttonSpacing**: *number* = 20

*Defined in [host-config.ts:193](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L193)*

___

###  iconPlacement

• **iconPlacement**: *[ActionIconPlacement](../enums/actioniconplacement.md)* = Enums.ActionIconPlacement.LeftOfTitle

*Defined in [host-config.ts:198](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L198)*

___

###  iconSize

• **iconSize**: *number* = 16

*Defined in [host-config.ts:200](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L200)*

___

###  maxActions

• **maxActions**: *number* = 5

*Defined in [host-config.ts:191](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L191)*

___

### `Optional` preExpandSingleShowCardAction

• **preExpandSingleShowCardAction**? : *undefined | false | true* = false

*Defined in [host-config.ts:195](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L195)*

___

###  showCard

• **showCard**: *[ShowCardActionConfig](showcardactionconfig.md)* = new ShowCardActionConfig()

*Defined in [host-config.ts:194](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L194)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)* = Enums.Spacing.Default

*Defined in [host-config.ts:192](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L192)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:227](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L227)*

**Returns:** *object*

* **actionAlignment**: *string* = Enums.ActionAlignment[this.actionAlignment]

* **actionsOrientation**: *string* = Enums.Orientation[this.actionsOrientation]

* **buttonSpacing**: *number* = this.buttonSpacing

* **maxActions**: *number* = this.maxActions

* **preExpandSingleShowCardAction**: *undefined | false | true* = this.preExpandSingleShowCardAction

* **showCard**: *[ShowCardActionConfig](showcardactionconfig.md)‹›* = this.showCard

* **spacing**: *string* = Enums.Spacing[this.spacing]
