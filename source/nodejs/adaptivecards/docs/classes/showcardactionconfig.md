[Adaptive Cards Javascript SDK](../README.md) › [ShowCardActionConfig](showcardactionconfig.md)

# Class: ShowCardActionConfig

## Hierarchy

* **ShowCardActionConfig**

## Index

### Constructors

* [constructor](showcardactionconfig.md#constructor)

### Properties

* [actionMode](showcardactionconfig.md#actionmode)
* [inlineTopMargin](showcardactionconfig.md#inlinetopmargin)
* [style](showcardactionconfig.md#optional-style)

### Methods

* [toJSON](showcardactionconfig.md#tojson)

## Constructors

###  constructor

\+ **new ShowCardActionConfig**(`obj?`: any): *[ShowCardActionConfig](showcardactionconfig.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ShowCardActionConfig](showcardactionconfig.md)*

## Properties

###  actionMode

• **actionMode**: *[ShowCardActionMode](../enums/showcardactionmode.md)* = Enums.ShowCardActionMode.Inline

___

###  inlineTopMargin

• **inlineTopMargin**: *number* = 16

___

### `Optional` style

• **style**? : *undefined | string* = Enums.ContainerStyle.Emphasis

## Methods

###  toJSON

▸ **toJSON**(): *object*

**Returns:** *object*

* **actionMode**: *string* = Enums.ShowCardActionMode[this.actionMode]

* **inlineTopMargin**: *number* = this.inlineTopMargin

* **style**: *undefined | string* = this.style
