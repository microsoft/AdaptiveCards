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

___

###  highlightColors

• **highlightColors**: *[ColorDefinition](colordefinition.md)‹›* = new ColorDefinition("#22000000", "#11000000")

___

###  subtle

• **subtle**: *string* = "#666666"

*Inherited from [ColorDefinition](colordefinition.md).[subtle](colordefinition.md#subtle)*

## Methods

###  parse

▸ **parse**(`obj?`: any): *void*

*Overrides [ColorDefinition](colordefinition.md).[parse](colordefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *void*
