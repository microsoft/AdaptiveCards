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

*Defined in [host-config.ts:325](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L325)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[ContainerStyleSet](containerstyleset.md)*

## Accessors

###  default

• **get default**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Defined in [host-config.ts:398](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L398)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  emphasis

• **get emphasis**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Defined in [host-config.ts:402](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L402)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

## Methods

###  getStyleByName

▸ **getStyleByName**(`name`: string | undefined, `defaultValue?`: [ContainerStyleDefinition](containerstyledefinition.md)): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Defined in [host-config.ts:389](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L389)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string &#124; undefined |
`defaultValue?` | [ContainerStyleDefinition](containerstyledefinition.md) |

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Defined in [host-config.ts:364](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L364)*

**Returns:** *any*
