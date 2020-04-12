[Adaptive Cards Javascript SDK](../README.md) › [SizeAndUnit](sizeandunit.md)

# Class: SizeAndUnit

## Hierarchy

* **SizeAndUnit**

## Index

### Constructors

* [constructor](sizeandunit.md#constructor)

### Properties

* [physicalSize](sizeandunit.md#physicalsize)
* [unit](sizeandunit.md#unit)

### Methods

* [parse](sizeandunit.md#static-parse)

## Constructors

###  constructor

\+ **new SizeAndUnit**(`physicalSize`: number, `unit`: [SizeUnit](../enums/sizeunit.md)): *[SizeAndUnit](sizeandunit.md)*

*Defined in [shared.ts:165](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L165)*

**Parameters:**

Name | Type |
------ | ------ |
`physicalSize` | number |
`unit` | [SizeUnit](../enums/sizeunit.md) |

**Returns:** *[SizeAndUnit](sizeandunit.md)*

## Properties

###  physicalSize

• **physicalSize**: *number*

*Defined in [shared.ts:135](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L135)*

___

###  unit

• **unit**: *[SizeUnit](../enums/sizeunit.md)*

*Defined in [shared.ts:136](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L136)*

## Methods

### `Static` parse

▸ **parse**(`input`: any, `requireUnitSpecifier`: boolean): *[SizeAndUnit](sizeandunit.md)*

*Defined in [shared.ts:138](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L138)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`input` | any | - |
`requireUnitSpecifier` | boolean | false |

**Returns:** *[SizeAndUnit](sizeandunit.md)*
