[Adaptive Cards Javascript SDK](../README.md) › [FontTypeDefinition](fonttypedefinition.md)

# Class: FontTypeDefinition

## Hierarchy

* **FontTypeDefinition**

## Index

### Constructors

* [constructor](fonttypedefinition.md#constructor)

### Properties

* [fontFamily](fonttypedefinition.md#optional-fontfamily)
* [monospace](fonttypedefinition.md#static-monospace)

### Methods

* [parse](fonttypedefinition.md#parse)

### Object literals

* [fontSizes](fonttypedefinition.md#fontsizes)
* [fontWeights](fonttypedefinition.md#fontweights)

## Constructors

###  constructor

\+ **new FontTypeDefinition**(`fontFamily?`: undefined | string): *[FontTypeDefinition](fonttypedefinition.md)*

*Defined in [host-config.ts:438](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L438)*

**Parameters:**

Name | Type |
------ | ------ |
`fontFamily?` | undefined &#124; string |

**Returns:** *[FontTypeDefinition](fonttypedefinition.md)*

## Properties

### `Optional` fontFamily

• **fontFamily**? : *undefined | string* = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif"

*Defined in [host-config.ts:424](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L424)*

___

### `Static` monospace

▪ **monospace**: *[FontTypeDefinition](fonttypedefinition.md)‹›* = new FontTypeDefinition("'Courier New', Courier, monospace")

*Defined in [host-config.ts:422](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L422)*

## Methods

###  parse

▸ **parse**(`obj?`: any): *void*

*Defined in [host-config.ts:446](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L446)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *void*

## Object literals

###  fontSizes

### ▪ **fontSizes**: *object*

*Defined in [host-config.ts:426](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L426)*

###  default

• **default**: *number* = 14

*Defined in [host-config.ts:428](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L428)*

###  extraLarge

• **extraLarge**: *number* = 26

*Defined in [host-config.ts:431](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L431)*

###  large

• **large**: *number* = 21

*Defined in [host-config.ts:430](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L430)*

###  medium

• **medium**: *number* = 17

*Defined in [host-config.ts:429](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L429)*

###  small

• **small**: *number* = 12

*Defined in [host-config.ts:427](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L427)*

___

###  fontWeights

### ▪ **fontWeights**: *object*

*Defined in [host-config.ts:434](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L434)*

###  bolder

• **bolder**: *number* = 600

*Defined in [host-config.ts:437](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L437)*

###  default

• **default**: *number* = 400

*Defined in [host-config.ts:436](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L436)*

###  lighter

• **lighter**: *number* = 200

*Defined in [host-config.ts:435](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L435)*
