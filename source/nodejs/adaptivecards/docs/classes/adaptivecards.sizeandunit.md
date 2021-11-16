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

\+ **new SizeAndUnit**(`physicalSize`: _number_, `unit`: [_SizeUnit_](../enums/enums.sizeunit.md)): [_SizeAndUnit_](shared.sizeandunit.md)

#### Parameters:

| Name           | Type                                     |
| :------------- | :--------------------------------------- |
| `physicalSize` | _number_                                 |
| `unit`         | [_SizeUnit_](../enums/enums.sizeunit.md) |

**Returns:** [_SizeAndUnit_](shared.sizeandunit.md)

Defined in: [shared.ts:178](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L178)

## Properties

### physicalSize

• **physicalSize**: _number_

Defined in: [shared.ts:148](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L148)

---

### unit

• **unit**: [_SizeUnit_](../enums/enums.sizeunit.md)

Defined in: [shared.ts:149](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L149)

## Methods

### parse

▸ `Static`**parse**(`input`: _string_, `requireUnitSpecifier?`: _boolean_): [_SizeAndUnit_](shared.sizeandunit.md)

#### Parameters:

| Name                   | Type      | Default value |
| :--------------------- | :-------- | :------------ |
| `input`                | _string_  | -             |
| `requireUnitSpecifier` | _boolean_ | false         |

**Returns:** [_SizeAndUnit_](shared.sizeandunit.md)

Defined in: [shared.ts:151](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L151)
