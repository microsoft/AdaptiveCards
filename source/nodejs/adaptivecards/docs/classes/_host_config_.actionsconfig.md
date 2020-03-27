[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [ActionsConfig](_host_config_.actionsconfig.md)

# Class: ActionsConfig

## Hierarchy

* **ActionsConfig**

## Index

### Constructors

* [constructor](_host_config_.actionsconfig.md#constructor)

### Properties

* [actionAlignment](_host_config_.actionsconfig.md#actionalignment)
* [actionsOrientation](_host_config_.actionsconfig.md#actionsorientation)
* [allowTitleToWrap](_host_config_.actionsconfig.md#allowtitletowrap)
* [buttonSpacing](_host_config_.actionsconfig.md#buttonspacing)
* [iconPlacement](_host_config_.actionsconfig.md#iconplacement)
* [iconSize](_host_config_.actionsconfig.md#iconsize)
* [maxActions](_host_config_.actionsconfig.md#maxactions)
* [preExpandSingleShowCardAction](_host_config_.actionsconfig.md#optional-preexpandsingleshowcardaction)
* [showCard](_host_config_.actionsconfig.md#showcard)
* [spacing](_host_config_.actionsconfig.md#spacing)

### Methods

* [toJSON](_host_config_.actionsconfig.md#tojson)

## Constructors

###  constructor

\+ **new ActionsConfig**(`obj?`: any): *[ActionsConfig](_host_config_.actionsconfig.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ActionsConfig](_host_config_.actionsconfig.md)*

## Properties

###  actionAlignment

• **actionAlignment**: *[ActionAlignment](../enums/_enums_.actionalignment.md)* = Enums.ActionAlignment.Left

___

###  actionsOrientation

• **actionsOrientation**: *[Orientation](../enums/_enums_.orientation.md)* = Enums.Orientation.Horizontal

___

###  allowTitleToWrap

• **allowTitleToWrap**: *boolean* = false

___

###  buttonSpacing

• **buttonSpacing**: *number* = 20

___

###  iconPlacement

• **iconPlacement**: *[ActionIconPlacement](../enums/_enums_.actioniconplacement.md)* = Enums.ActionIconPlacement.LeftOfTitle

___

###  iconSize

• **iconSize**: *number* = 24

___

###  maxActions

• **maxActions**: *number* = 5

___

### `Optional` preExpandSingleShowCardAction

• **preExpandSingleShowCardAction**? : *boolean* = false

___

###  showCard

• **showCard**: *[ShowCardActionConfig](_host_config_.showcardactionconfig.md)* = new ShowCardActionConfig()

___

###  spacing

• **spacing**: *[Spacing](../enums/_enums_.spacing.md)* = Enums.Spacing.Default

## Methods

###  toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

* **actionAlignment**: *string* = Enums.ActionAlignment[this.actionAlignment]

* **actionsOrientation**: *string* = Enums.Orientation[this.actionsOrientation]

* **buttonSpacing**: *number* = this.buttonSpacing

* **maxActions**: *number* = this.maxActions

* **preExpandSingleShowCardAction**: *boolean* = this.preExpandSingleShowCardAction

* **showCard**: *[ShowCardActionConfig](_host_config_.showcardactionconfig.md)‹›* = this.showCard

* **spacing**: *string* = Enums.Spacing[this.spacing]
