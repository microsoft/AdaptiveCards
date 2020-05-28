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

**Parameters:**

Name | Type |
------ | ------ |
`physicalSize` | number |
`unit` | [SizeUnit](../enums/sizeunit.md) |

**Returns:** *[SizeAndUnit](sizeandunit.md)*

## Properties

###  physicalSize

• **physicalSize**: *number*

___

###  unit

• **unit**: *[SizeUnit](../enums/sizeunit.md)*

## Methods

### `Static` parse

▸ **parse**(`input`: string, `requireUnitSpecifier`: boolean): *[SizeAndUnit](sizeandunit.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`input` | string | - |
`requireUnitSpecifier` | boolean | false |

**Returns:** *[SizeAndUnit](sizeandunit.md)*
