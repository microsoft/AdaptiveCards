[Adaptive Cards Javascript SDK](../README.md) › [TextColorDefinition](textcolordefinition.md)

# Class: TextColorDefinition

## Hierarchy

* [ColorDefinition](colordefinition.md)

  ↳ **TextColorDefinition**

## Index

### Constructors

* [constructor](textcolordefinition.md#constructor)

### Properties

* [default](textcolordefinition.md#default)
* [highlightColors](textcolordefinition.md#highlightcolors)
* [subtle](textcolordefinition.md#subtle)

### Methods

* [parse](textcolordefinition.md#parse)

## Constructors

###  constructor

\+ **new TextColorDefinition**(`defaultColor?`: string, `subtleColor?`: string): *[TextColorDefinition](textcolordefinition.md)*

*Inherited from [ColorDefinition](colordefinition.md).[constructor](colordefinition.md#constructor)*

*Defined in [host-config.ts:14](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L14)*

**Parameters:**

Name | Type |
------ | ------ |
`defaultColor?` | string |
`subtleColor?` | string |

**Returns:** *[TextColorDefinition](textcolordefinition.md)*

## Properties

###  default

• **default**: *string* = "#000000"

*Inherited from [ColorDefinition](colordefinition.md).[default](colordefinition.md#default)*

*Defined in [host-config.ts:13](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L13)*

___

###  highlightColors

• **highlightColors**: *[ColorDefinition](colordefinition.md)‹›* = new ColorDefinition("#22000000", "#11000000")

*Defined in [host-config.ts:35](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L35)*

___

###  subtle

• **subtle**: *string* = "#666666"

*Inherited from [ColorDefinition](colordefinition.md).[subtle](colordefinition.md#subtle)*

*Defined in [host-config.ts:14](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L14)*

## Methods

###  parse

▸ **parse**(`obj?`: any): *void*

*Overrides [ColorDefinition](colordefinition.md).[parse](colordefinition.md#parse)*

*Defined in [host-config.ts:37](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L37)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *void*
