[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [ContainerStyleDefinition](_host_config_.containerstyledefinition.md)

# Class: ContainerStyleDefinition

## Hierarchy

* **ContainerStyleDefinition**

## Index

### Constructors

* [constructor](_host_config_.containerstyledefinition.md#constructor)

### Properties

* [backgroundColor](_host_config_.containerstyledefinition.md#optional-backgroundcolor)
* [foregroundColors](_host_config_.containerstyledefinition.md#foregroundcolors)
* [highlightBackgroundColor](_host_config_.containerstyledefinition.md#optional-highlightbackgroundcolor)
* [highlightForegroundColor](_host_config_.containerstyledefinition.md#optional-highlightforegroundcolor)

### Accessors

* [isBuiltIn](_host_config_.containerstyledefinition.md#isbuiltin)

### Methods

* [parse](_host_config_.containerstyledefinition.md#parse)

## Constructors

###  constructor

\+ **new ContainerStyleDefinition**(`obj?`: any): *[ContainerStyleDefinition](_host_config_.containerstyledefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ContainerStyleDefinition](_host_config_.containerstyledefinition.md)*

## Properties

### `Optional` backgroundColor

• **backgroundColor**? : *string*

___

###  foregroundColors

• **foregroundColors**: *[ColorSetDefinition](_host_config_.colorsetdefinition.md)* = new ColorSetDefinition(
        {
            "default": { default: "#333333", subtle: "#EE333333" },
            "dark": { default: "#000000", subtle: "#66000000" },
            "light": { default: "#FFFFFF", subtle: "#33000000" },
            "accent": { default: "#2E89FC", subtle: "#882E89FC" },
            "good": { default: "#54A254", subtle: "#DD54A254" },
            "warning": { default: "#E69500", subtle: "#DDE69500" },
            "attention": { default: "#CC3300", subtle: "#DDCC3300" }
        }
    )

___

### `Optional` highlightBackgroundColor

• **highlightBackgroundColor**? : *string*

___

### `Optional` highlightForegroundColor

• **highlightForegroundColor**? : *string*

## Accessors

###  isBuiltIn

• **get isBuiltIn**(): *boolean*

**Returns:** *boolean*

## Methods

###  parse

▸ **parse**(`obj`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`obj` | any |

**Returns:** *void*
