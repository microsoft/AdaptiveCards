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

\+ **new ContainerStyleSet**(`obj?`: *any*): [*ContainerStyleSet*](host_config.containerstyleset.md)

#### Parameters:

Name | Type |
:------ | :------ |
`obj?` | *any* |

**Returns:** [*ContainerStyleSet*](host_config.containerstyleset.md)

Defined in: [host-config.ts:389](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L389)

## Accessors

### default

• get **default**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Defined in: [host-config.ts:462](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L462)

___

### emphasis

• get **emphasis**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Defined in: [host-config.ts:466](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L466)

## Methods

### getStyleByName

▸ **getStyleByName**(`name`: *undefined* \| *string*, `defaultValue?`: [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *undefined* \| *string* |
`defaultValue?` | [*ContainerStyleDefinition*](host_config.containerstyledefinition.md) |

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Defined in: [host-config.ts:453](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L453)

___

### toJSON

▸ **toJSON**(): *any*

**Returns:** *any*

Defined in: [host-config.ts:428](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L428)
