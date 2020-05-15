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

\+ **new TextColorDefinition**(`defaultColor?`: undefined | string, `subtleColor?`: undefined | string): *[TextColorDefinition](textcolordefinition.md)*

*Inherited from [ColorDefinition](colordefinition.md).[constructor](colordefinition.md#constructor)*

*Defined in [host-config.ts:24](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L24)*

**Parameters:**

Name | Type |
------ | ------ |
`defaultColor?` | undefined &#124; string |
`subtleColor?` | undefined &#124; string |

**Returns:** *[TextColorDefinition](textcolordefinition.md)*

## Properties

###  default

• **default**: *string* = "#000000"

*Inherited from [ColorDefinition](colordefinition.md).[default](colordefinition.md#default)*

*Defined in [host-config.ts:23](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L23)*

___

###  highlightColors

• **highlightColors**: *[ColorDefinition](colordefinition.md)‹›* = new ColorDefinition("#22000000", "#11000000")

*Defined in [host-config.ts:45](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L45)*

___

###  subtle

• **subtle**: *string* = "#666666"

*Inherited from [ColorDefinition](colordefinition.md).[subtle](colordefinition.md#subtle)*

*Defined in [host-config.ts:24](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L24)*

## Methods

###  parse

▸ **parse**(`obj?`: any): *void*

*Overrides [ColorDefinition](colordefinition.md).[parse](colordefinition.md#parse)*

*Defined in [host-config.ts:47](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L47)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *void*
