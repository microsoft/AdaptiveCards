[Adaptive Cards Javascript SDK](../README.md) / [host-config](../modules/host_config.md) / TextColorDefinition

# Class: TextColorDefinition

[host-config](../modules/host_config.md).TextColorDefinition

## Hierarchy

* [*ColorDefinition*](host_config.colordefinition.md)

  ↳ **TextColorDefinition**

## Table of contents

### Constructors

- [constructor](host_config.textcolordefinition.md#constructor)

### Properties

- [default](host_config.textcolordefinition.md#default)
- [highlightColors](host_config.textcolordefinition.md#highlightcolors)
- [subtle](host_config.textcolordefinition.md#subtle)

### Methods

- [parse](host_config.textcolordefinition.md#parse)

## Constructors

### constructor

\+ **new TextColorDefinition**(`defaultColor?`: *string*, `subtleColor?`: *string*): [*TextColorDefinition*](host_config.textcolordefinition.md)

#### Parameters:

Name | Type |
:------ | :------ |
`defaultColor?` | *string* |
`subtleColor?` | *string* |

**Returns:** [*TextColorDefinition*](host_config.textcolordefinition.md)

Inherited from: [ColorDefinition](host_config.colordefinition.md)

Defined in: [host-config.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L24)

## Properties

### default

• **default**: *string*= "#000000"

Inherited from: [ColorDefinition](host_config.colordefinition.md).[default](host_config.colordefinition.md#default)

Defined in: [host-config.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L23)

___

### highlightColors

• `Readonly` **highlightColors**: [*ColorDefinition*](host_config.colordefinition.md)

Defined in: [host-config.ts:45](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L45)

___

### subtle

• **subtle**: *string*= "#666666"

Inherited from: [ColorDefinition](host_config.colordefinition.md).[subtle](host_config.colordefinition.md#subtle)

Defined in: [host-config.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L24)

## Methods

### parse

▸ **parse**(`obj?`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`obj?` | *any* |

**Returns:** *void*

Overrides: [ColorDefinition](host_config.colordefinition.md)

Defined in: [host-config.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L47)
