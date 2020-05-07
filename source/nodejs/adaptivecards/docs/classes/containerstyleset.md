[Adaptive Cards Javascript SDK](../README.md) › [ContainerStyleSet](containerstyleset.md)

# Class: ContainerStyleSet

## Hierarchy

* **ContainerStyleSet**

## Index

### Constructors

* [constructor](containerstyleset.md#constructor)

### Accessors

* [default](containerstyleset.md#default)
* [emphasis](containerstyleset.md#emphasis)

### Methods

* [getStyleByName](containerstyleset.md#getstylebyname)
* [toJSON](containerstyleset.md#tojson)

## Constructors

###  constructor

\+ **new ContainerStyleSet**(`obj?`: any): *[ContainerStyleSet](containerstyleset.md)*

*Defined in [host-config.ts:315](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L315)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ContainerStyleSet](containerstyleset.md)*

## Accessors

###  default

• **get default**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Defined in [host-config.ts:383](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L383)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  emphasis

• **get emphasis**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Defined in [host-config.ts:387](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L387)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

## Methods

###  getStyleByName

▸ **getStyleByName**(`name`: string, `defaultValue`: [ContainerStyleDefinition](containerstyledefinition.md)): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Defined in [host-config.ts:379](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L379)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | - |
`defaultValue` | [ContainerStyleDefinition](containerstyledefinition.md) | null |

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Defined in [host-config.ts:354](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L354)*

**Returns:** *any*
