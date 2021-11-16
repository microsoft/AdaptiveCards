[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ContainerStyleSet

# Class: ContainerStyleSet

[adaptivecards](../modules/adaptivecards.md).ContainerStyleSet

## Table of contents

### Constructors

- [constructor](adaptivecards.containerstyleset.md#constructor)

### Accessors

- [default](adaptivecards.containerstyleset.md#default)
- [emphasis](adaptivecards.containerstyleset.md#emphasis)

### Methods

- [getStyleByName](adaptivecards.containerstyleset.md#getstylebyname)
- [toJSON](adaptivecards.containerstyleset.md#tojson)

## Constructors

### constructor

\+ **new ContainerStyleSet**(`obj?`: _any_): [_ContainerStyleSet_](host_config.containerstyleset.md)

#### Parameters:

| Name   | Type  |
| :----- | :---- |
| `obj?` | _any_ |

**Returns:** [_ContainerStyleSet_](host_config.containerstyleset.md)

Defined in: [host-config.ts:389](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L389)

## Accessors

### default

• get **default**(): [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

**Returns:** [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

Defined in: [host-config.ts:462](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L462)

---

### emphasis

• get **emphasis**(): [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

**Returns:** [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

Defined in: [host-config.ts:466](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L466)

## Methods

### getStyleByName

▸ **getStyleByName**(`name`: _undefined_ \| _string_, `defaultValue?`: [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)): [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

#### Parameters:

| Name            | Type                                                                  |
| :-------------- | :-------------------------------------------------------------------- |
| `name`          | _undefined_ \| _string_                                               |
| `defaultValue?` | [_ContainerStyleDefinition_](host_config.containerstyledefinition.md) |

**Returns:** [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

Defined in: [host-config.ts:453](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L453)

---

### toJSON

▸ **toJSON**(): _any_

**Returns:** _any_

Defined in: [host-config.ts:428](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L428)
