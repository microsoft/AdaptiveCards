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

\+ **new FontTypeDefinition**(`fontFamily?`: string): *[FontTypeDefinition](fonttypedefinition.md)*

*Defined in [host-config.ts:569](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L569)*

**Parameters:**

Name | Type |
------ | ------ |
`fontFamily?` | string |

**Returns:** *[FontTypeDefinition](fonttypedefinition.md)*

## Properties

### `Optional` fontFamily

• **fontFamily**? : *string* = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif"

*Defined in [host-config.ts:555](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L555)*

___

### `Static` monospace

▪ **monospace**: *[FontTypeDefinition](fonttypedefinition.md)‹›* = new FontTypeDefinition("'Courier New', Courier, monospace")

*Defined in [host-config.ts:553](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L553)*

## Methods

###  parse

▸ **parse**(`obj?`: any): *void*

*Defined in [host-config.ts:577](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L577)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *void*

## Object literals

###  fontSizes

### ▪ **fontSizes**: *object*

*Defined in [host-config.ts:557](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L557)*

###  default

• **default**: *number* = 14

*Defined in [host-config.ts:559](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L559)*

###  extraLarge

• **extraLarge**: *number* = 26

*Defined in [host-config.ts:562](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L562)*

###  large

• **large**: *number* = 21

*Defined in [host-config.ts:561](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L561)*

###  medium

• **medium**: *number* = 17

*Defined in [host-config.ts:560](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L560)*

###  small

• **small**: *number* = 12

*Defined in [host-config.ts:558](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L558)*

___

###  fontWeights

### ▪ **fontWeights**: *object*

*Defined in [host-config.ts:565](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L565)*

###  bolder

• **bolder**: *number* = 600

*Defined in [host-config.ts:568](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L568)*

###  default

• **default**: *number* = 400

*Defined in [host-config.ts:567](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L567)*

###  lighter

• **lighter**: *number* = 200

*Defined in [host-config.ts:566](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L566)*
