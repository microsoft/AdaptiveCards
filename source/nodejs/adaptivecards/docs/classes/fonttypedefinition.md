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

**Parameters:**

Name | Type |
------ | ------ |
`fontFamily?` | undefined &#124; string |

**Returns:** *[FontTypeDefinition](fonttypedefinition.md)*

## Properties

### `Optional` fontFamily

• **fontFamily**? : *undefined | string* = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif"

___

### `Static` monospace

▪ **monospace**: *[FontTypeDefinition](fonttypedefinition.md)‹›* = new FontTypeDefinition("'Courier New', Courier, monospace")

## Methods

###  parse

▸ **parse**(`obj?`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *void*

## Object literals

###  fontSizes

### ▪ **fontSizes**: *object*

###  default

• **default**: *number* = 14

###  extraLarge

• **extraLarge**: *number* = 26

###  large

• **large**: *number* = 21

###  medium

• **medium**: *number* = 17

###  small

• **small**: *number* = 12

___

###  fontWeights

### ▪ **fontWeights**: *object*

###  bolder

• **bolder**: *number* = 600

###  default

• **default**: *number* = 400

###  lighter

• **lighter**: *number* = 200
