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

*Defined in [host-config.ts:299](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L299)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

## Properties

### `Optional` backgroundColor

• **backgroundColor**? : *undefined | string*

*Defined in [host-config.ts:273](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L273)*

___

###  foregroundColors

• **foregroundColors**: *[ColorSetDefinition](colorsetdefinition.md)* = new ColorSetDefinition(
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

*Defined in [host-config.ts:275](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L275)*

___

### `Optional` highlightBackgroundColor

• **highlightBackgroundColor**? : *undefined | string*

*Defined in [host-config.ts:287](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L287)*

___

### `Optional` highlightForegroundColor

• **highlightForegroundColor**? : *undefined | string*

*Defined in [host-config.ts:288](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L288)*

## Accessors

###  isBuiltIn

• **get isBuiltIn**(): *boolean*

*Defined in [host-config.ts:305](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L305)*

**Returns:** *boolean*

## Methods

###  parse

▸ **parse**(`obj`: any): *void*

*Defined in [host-config.ts:290](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L290)*

**Parameters:**

Name | Type |
------ | ------ |
`obj` | any |

**Returns:** *void*
