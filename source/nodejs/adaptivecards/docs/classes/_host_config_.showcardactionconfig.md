[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [ShowCardActionConfig](_host_config_.showcardactionconfig.md)

# Class: ShowCardActionConfig

## Hierarchy

* **ShowCardActionConfig**

## Index

### Constructors

* [constructor](_host_config_.showcardactionconfig.md#constructor)

### Properties

* [actionMode](_host_config_.showcardactionconfig.md#actionmode)
* [inlineTopMargin](_host_config_.showcardactionconfig.md#inlinetopmargin)
* [style](_host_config_.showcardactionconfig.md#optional-style)

### Methods

* [toJSON](_host_config_.showcardactionconfig.md#tojson)

## Constructors

###  constructor

\+ **new ShowCardActionConfig**(`obj?`: any): *[ShowCardActionConfig](_host_config_.showcardactionconfig.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ShowCardActionConfig](_host_config_.showcardactionconfig.md)*

## Properties

###  actionMode

• **actionMode**: *[ShowCardActionMode](../enums/_enums_.showcardactionmode.md)* = Enums.ShowCardActionMode.Inline

___

###  inlineTopMargin

• **inlineTopMargin**: *number* = 16

___

### `Optional` style

• **style**? : *string* = Enums.ContainerStyle.Emphasis

## Methods

###  toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

* **actionMode**: *string* = Enums.ShowCardActionMode[this.actionMode]

* **inlineTopMargin**: *number* = this.inlineTopMargin

* **style**: *string* = this.style
