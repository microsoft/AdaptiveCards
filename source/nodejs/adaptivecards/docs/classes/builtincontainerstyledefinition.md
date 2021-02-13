[Adaptive Cards Javascript SDK](../README.md) › [BuiltInContainerStyleDefinition](builtincontainerstyledefinition.md)

# Class: BuiltInContainerStyleDefinition

## Hierarchy

* [ContainerStyleDefinition](containerstyledefinition.md)

  ↳ **BuiltInContainerStyleDefinition**

## Index

### Constructors

* [constructor](builtincontainerstyledefinition.md#constructor)

### Properties

* [backgroundColor](builtincontainerstyledefinition.md#optional-backgroundcolor)
* [foregroundColors](builtincontainerstyledefinition.md#readonly-foregroundcolors)
* [highlightBackgroundColor](builtincontainerstyledefinition.md#optional-highlightbackgroundcolor)
* [highlightForegroundColor](builtincontainerstyledefinition.md#optional-highlightforegroundcolor)

### Accessors

* [isBuiltIn](builtincontainerstyledefinition.md#isbuiltin)

### Methods

* [parse](builtincontainerstyledefinition.md#parse)

## Constructors

###  constructor

\+ **new BuiltInContainerStyleDefinition**(`obj?`: any): *[BuiltInContainerStyleDefinition](builtincontainerstyledefinition.md)*

*Inherited from [ContainerStyleDefinition](containerstyledefinition.md).[constructor](containerstyledefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[BuiltInContainerStyleDefinition](builtincontainerstyledefinition.md)*

## Properties

### `Optional` backgroundColor

• **backgroundColor**? : *undefined | string*

*Inherited from [ContainerStyleDefinition](containerstyledefinition.md).[backgroundColor](containerstyledefinition.md#optional-backgroundcolor)*

___

### `Readonly` foregroundColors

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

*Inherited from [ContainerStyleDefinition](containerstyledefinition.md).[foregroundColors](containerstyledefinition.md#readonly-foregroundcolors)*

___

### `Optional` highlightBackgroundColor

• **highlightBackgroundColor**? : *undefined | string*

*Inherited from [ContainerStyleDefinition](containerstyledefinition.md).[highlightBackgroundColor](containerstyledefinition.md#optional-highlightbackgroundcolor)*

___

### `Optional` highlightForegroundColor

• **highlightForegroundColor**? : *undefined | string*

*Inherited from [ContainerStyleDefinition](containerstyledefinition.md).[highlightForegroundColor](containerstyledefinition.md#optional-highlightforegroundcolor)*

## Accessors

###  isBuiltIn

• **get isBuiltIn**(): *boolean*

*Overrides [ContainerStyleDefinition](containerstyledefinition.md).[isBuiltIn](containerstyledefinition.md#isbuiltin)*

**Returns:** *boolean*

## Methods

###  parse

▸ **parse**(`obj`: any): *void*

*Inherited from [ContainerStyleDefinition](containerstyledefinition.md).[parse](containerstyledefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`obj` | any |

**Returns:** *void*
