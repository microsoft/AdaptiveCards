[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SizeAndUnit

# Class: SizeAndUnit

[adaptivecards](../modules/adaptivecards.md).SizeAndUnit

## Table of contents

### Constructors

- [constructor](adaptivecards.sizeandunit.md#constructor)

### Properties

- [physicalSize](adaptivecards.sizeandunit.md#physicalsize)
- [unit](adaptivecards.sizeandunit.md#unit)

### Methods

- [parse](adaptivecards.sizeandunit.md#parse)

## Constructors

### constructor

\+ **new SizeAndUnit**(`physicalSize`: *number*, `unit`: [*SizeUnit*](../enums/enums.sizeunit.md)): [*SizeAndUnit*](shared.sizeandunit.md)

#### Parameters:

Name | Type |
:------ | :------ |
`physicalSize` | *number* |
`unit` | [*SizeUnit*](../enums/enums.sizeunit.md) |

**Returns:** [*SizeAndUnit*](shared.sizeandunit.md)

Defined in: [shared.ts:178](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L178)

## Properties

### physicalSize

• **physicalSize**: *number*

Defined in: [shared.ts:148](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L148)

___

### unit

• **unit**: [*SizeUnit*](../enums/enums.sizeunit.md)

Defined in: [shared.ts:149](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L149)

## Methods

### parse

▸ `Static`**parse**(`input`: *string*, `requireUnitSpecifier?`: *boolean*): [*SizeAndUnit*](shared.sizeandunit.md)

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`input` | *string* | - |
`requireUnitSpecifier` | *boolean* | false |

**Returns:** [*SizeAndUnit*](shared.sizeandunit.md)

Defined in: [shared.ts:151](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L151)
