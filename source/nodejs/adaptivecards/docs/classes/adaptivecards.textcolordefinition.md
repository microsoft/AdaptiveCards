[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / TextColorDefinition

# Class: TextColorDefinition

[adaptivecards](../modules/adaptivecards.md).TextColorDefinition

## Hierarchy

- [_ColorDefinition_](host_config.colordefinition.md)

  ↳ **TextColorDefinition**

## Table of contents

### Constructors

- [constructor](adaptivecards.textcolordefinition.md#constructor)

### Properties

- [default](adaptivecards.textcolordefinition.md#default)
- [highlightColors](adaptivecards.textcolordefinition.md#highlightcolors)
- [subtle](adaptivecards.textcolordefinition.md#subtle)

### Methods

- [parse](adaptivecards.textcolordefinition.md#parse)

## Constructors

### constructor

\+ **new TextColorDefinition**(`defaultColor?`: _string_, `subtleColor?`: _string_): [_TextColorDefinition_](host_config.textcolordefinition.md)

#### Parameters:

| Name            | Type     |
| :-------------- | :------- |
| `defaultColor?` | _string_ |
| `subtleColor?`  | _string_ |

**Returns:** [_TextColorDefinition_](host_config.textcolordefinition.md)

Inherited from: [ColorDefinition](host_config.colordefinition.md)

Defined in: [host-config.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L24)

## Properties

### default

• **default**: _string_= "#000000"

Inherited from: [ColorDefinition](host_config.colordefinition.md).[default](host_config.colordefinition.md#default)

Defined in: [host-config.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L23)

---

### highlightColors

• `Readonly` **highlightColors**: [_ColorDefinition_](host_config.colordefinition.md)

Defined in: [host-config.ts:45](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L45)

---

### subtle

• **subtle**: _string_= "#666666"

Inherited from: [ColorDefinition](host_config.colordefinition.md).[subtle](host_config.colordefinition.md#subtle)

Defined in: [host-config.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L24)

## Methods

### parse

▸ **parse**(`obj?`: _any_): _void_

#### Parameters:

| Name   | Type  |
| :----- | :---- |
| `obj?` | _any_ |

**Returns:** _void_

Overrides: [ColorDefinition](host_config.colordefinition.md)

Defined in: [host-config.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L47)
