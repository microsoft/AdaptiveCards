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

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ActionsConfig](actionsconfig.md)*

## Properties

###  actionAlignment

• **actionAlignment**: *[ActionAlignment](../enums/actionalignment.md)* = Enums.ActionAlignment.Left

___

###  actionsOrientation

• **actionsOrientation**: *[Orientation](../enums/orientation.md)* = Enums.Orientation.Horizontal

___

###  allowTitleToWrap

• **allowTitleToWrap**: *boolean* = false

___

###  buttonSpacing

• **buttonSpacing**: *number* = 20

___

###  iconPlacement

• **iconPlacement**: *[ActionIconPlacement](../enums/actioniconplacement.md)* = Enums.ActionIconPlacement.LeftOfTitle

___

###  iconSize

• **iconSize**: *number* = 16

___

###  maxActions

• **maxActions**: *number* = 5

___

### `Optional` preExpandSingleShowCardAction

• **preExpandSingleShowCardAction**? : *undefined | false | true* = false

___

###  showCard

• **showCard**: *[ShowCardActionConfig](showcardactionconfig.md)* = new ShowCardActionConfig()

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)* = Enums.Spacing.Default

## Methods

###  toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

* **actionAlignment**: *string* = Enums.ActionAlignment[this.actionAlignment]

* **actionsOrientation**: *string* = Enums.Orientation[this.actionsOrientation]

* **buttonSpacing**: *number* = this.buttonSpacing

* **maxActions**: *number* = this.maxActions

* **preExpandSingleShowCardAction**: *undefined | false | true* = this.preExpandSingleShowCardAction

* **showCard**: *[ShowCardActionConfig](showcardactionconfig.md)‹›* = this.showCard

* **spacing**: *string* = Enums.Spacing[this.spacing]
