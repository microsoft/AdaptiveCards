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

*Defined in [host-config.ts:289](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L289)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

## Properties

### `Optional` backgroundColor

• **backgroundColor**? : *string*

*Defined in [host-config.ts:263](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L263)*

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

*Defined in [host-config.ts:265](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L265)*

___

### `Optional` highlightBackgroundColor

• **highlightBackgroundColor**? : *string*

*Defined in [host-config.ts:277](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L277)*

___

### `Optional` highlightForegroundColor

• **highlightForegroundColor**? : *string*

*Defined in [host-config.ts:278](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L278)*

## Accessors

###  isBuiltIn

• **get isBuiltIn**(): *boolean*

*Defined in [host-config.ts:295](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L295)*

**Returns:** *boolean*

## Methods

###  parse

▸ **parse**(`obj`: any): *void*

*Defined in [host-config.ts:280](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L280)*

**Parameters:**

Name | Type |
------ | ------ |
`obj` | any |

**Returns:** *void*
