[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [FontTypeDefinition](_host_config_.fonttypedefinition.md)

# Class: FontTypeDefinition

## Hierarchy

* **FontTypeDefinition**

## Index

### Constructors

* [constructor](_host_config_.fonttypedefinition.md#constructor)

### Properties

* [fontFamily](_host_config_.fonttypedefinition.md#optional-fontfamily)
* [monospace](_host_config_.fonttypedefinition.md#static-monospace)

### Methods

* [parse](_host_config_.fonttypedefinition.md#parse)

### Object literals

* [fontSizes](_host_config_.fonttypedefinition.md#fontsizes)
* [fontWeights](_host_config_.fonttypedefinition.md#fontweights)

## Constructors

###  constructor

\+ **new FontTypeDefinition**(`fontFamily?`: string): *[FontTypeDefinition](_host_config_.fonttypedefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`fontFamily?` | string |

**Returns:** *[FontTypeDefinition](_host_config_.fonttypedefinition.md)*

## Properties

### `Optional` fontFamily

• **fontFamily**? : *string* = "Segoe UI,Segoe,Segoe WP,Helvetica Neue,Helvetica,sans-serif"

___

### `Static` monospace

▪ **monospace**: *[FontTypeDefinition](_host_config_.fonttypedefinition.md)‹›* = new FontTypeDefinition("'Courier New', Courier, monospace")

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
