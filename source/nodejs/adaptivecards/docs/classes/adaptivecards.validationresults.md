[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ValidationResults

# Class: ValidationResults

[adaptivecards](../modules/adaptivecards.md).ValidationResults

## Table of contents

### Constructors

- [constructor](adaptivecards.validationresults.md#constructor)

### Properties

- [allIds](adaptivecards.validationresults.md#allids)
- [validationEvents](adaptivecards.validationresults.md#validationevents)

### Methods

- [addFailure](adaptivecards.validationresults.md#addfailure)

## Constructors

### constructor

\+ **new ValidationResults**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

## Properties

### allIds

• `Readonly` **allIds**: [*Dictionary*](../modules/shared.md#dictionary)<number\>

Defined in: [card-object.ts:12](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L12)

___

### validationEvents

• `Readonly` **validationEvents**: [*IValidationEvent*](../interfaces/serialization.ivalidationevent.md)[]

Defined in: [card-object.ts:13](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L13)

## Methods

### addFailure

▸ **addFailure**(`cardObject`: [*CardObject*](card_object.cardobject.md), `event`: [*ValidationEvent*](../enums/enums.validationevent.md), `message`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`cardObject` | [*CardObject*](card_object.cardobject.md) |
`event` | [*ValidationEvent*](../enums/enums.validationevent.md) |
`message` | *string* |

**Returns:** *void*

Defined in: [card-object.ts:15](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L15)
