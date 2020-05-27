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

*Defined in [host-config.ts:171](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L171)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ShowCardActionConfig](showcardactionconfig.md)*

## Properties

###  actionMode

• **actionMode**: *[ShowCardActionMode](../enums/showcardactionmode.md)* = Enums.ShowCardActionMode.Inline

*Defined in [host-config.ts:169](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L169)*

___

###  inlineTopMargin

• **inlineTopMargin**: *number* = 16

*Defined in [host-config.ts:170](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L170)*

___

### `Optional` style

• **style**? : *undefined | string* = Enums.ContainerStyle.Emphasis

*Defined in [host-config.ts:171](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L171)*

## Methods

###  toJSON

▸ **toJSON**(): *object*

*Defined in [host-config.ts:181](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L181)*

**Returns:** *object*

* **actionMode**: *string* = Enums.ShowCardActionMode[this.actionMode]

* **inlineTopMargin**: *number* = this.inlineTopMargin

* **style**: *undefined | string* = this.style
