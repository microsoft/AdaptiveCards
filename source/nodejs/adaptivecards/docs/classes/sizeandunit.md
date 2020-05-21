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

*Defined in [shared.ts:177](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L177)*

**Parameters:**

Name | Type |
------ | ------ |
`physicalSize` | number |
`unit` | [SizeUnit](../enums/sizeunit.md) |

**Returns:** *[SizeAndUnit](sizeandunit.md)*

## Properties

###  physicalSize

• **physicalSize**: *number*

*Defined in [shared.ts:147](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L147)*

___

###  unit

• **unit**: *[SizeUnit](../enums/sizeunit.md)*

*Defined in [shared.ts:148](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L148)*

## Methods

### `Static` parse

▸ **parse**(`input`: string, `requireUnitSpecifier`: boolean): *[SizeAndUnit](sizeandunit.md)*

*Defined in [shared.ts:150](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L150)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`input` | string | - |
`requireUnitSpecifier` | boolean | false |

**Returns:** *[SizeAndUnit](sizeandunit.md)*
