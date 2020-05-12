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

*Defined in [host-config.ts:161](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L161)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ShowCardActionConfig](showcardactionconfig.md)*

## Properties

###  actionMode

• **actionMode**: *[ShowCardActionMode](../enums/showcardactionmode.md)* = Enums.ShowCardActionMode.Inline

*Defined in [host-config.ts:159](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L159)*

___

###  inlineTopMargin

• **inlineTopMargin**: *number* = 16

*Defined in [host-config.ts:160](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L160)*

___

### `Optional` style

• **style**? : *string* = Enums.ContainerStyle.Emphasis

*Defined in [host-config.ts:161](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L161)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:171](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L171)*

**Returns:** *object*

* **actionMode**: *string* = Enums.ShowCardActionMode[this.actionMode]

* **inlineTopMargin**: *number* = this.inlineTopMargin

* **style**: *string* = this.style
