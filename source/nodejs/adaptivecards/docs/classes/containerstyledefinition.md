[Adaptive Cards Javascript SDK](../README.md) › [ContainerStyleDefinition](containerstyledefinition.md)

# Class: ContainerStyleDefinition

## Hierarchy

* **ContainerStyleDefinition**

## Index

### Constructors

* [constructor](containerstyledefinition.md#constructor)

### Properties

* [backgroundColor](containerstyledefinition.md#optional-backgroundcolor)
* [foregroundColors](containerstyledefinition.md#foregroundcolors)
* [highlightBackgroundColor](containerstyledefinition.md#optional-highlightbackgroundcolor)
* [highlightForegroundColor](containerstyledefinition.md#optional-highlightforegroundcolor)

### Accessors

* [isBuiltIn](containerstyledefinition.md#isbuiltin)

### Methods

* [parse](containerstyledefinition.md#parse)

## Constructors

###  constructor

\+ **new ContainerStyleDefinition**(`obj?`: any): *[ContainerStyleDefinition](containerstyledefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

## Properties

### `Optional` backgroundColor

• **backgroundColor**? : *undefined | string*

___

###  foregroundColors

• **foregroundColors**: *[ColorSetDefinition](colorsetdefinition.md)* = new ColorSetDefinition(
        {
            "default": { default: "#333333", subtle: "#EE333333" },
            "dark": { default: "#000000", subtle: "#66000000" },
            "light": { default: "#FFFFFF", subtle: "#33000000" },
            "accent": { default: "#2E89FC", subtle: "#882E89FC" },
            "good": { default: "#028A02", subtle: "#DD027502" },
            "warning": { default: "#E69500", subtle: "#DDE69500" },
            "attention": { default: "#CC3300", subtle: "#DDCC3300" }
        }
    )

___

### `Optional` highlightBackgroundColor

• **highlightBackgroundColor**? : *undefined | string*

___

### `Optional` highlightForegroundColor

• **highlightForegroundColor**? : *undefined | string*

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
