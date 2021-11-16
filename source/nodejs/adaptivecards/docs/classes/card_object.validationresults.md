[Adaptive Cards Javascript SDK](../README.md) / [card-object](../modules/card_object.md) / ValidationResults

# Class: ValidationResults

[card-object](../modules/card_object.md).ValidationResults

## Table of contents

### Constructors

- [constructor](card_object.validationresults.md#constructor)

### Properties

- [allIds](card_object.validationresults.md#allids)
- [validationEvents](card_object.validationresults.md#validationevents)

### Methods

- [addFailure](card_object.validationresults.md#addfailure)

## Constructors

### constructor

\+ **new ValidationResults**(): [_ValidationResults_](card_object.validationresults.md)

**Returns:** [_ValidationResults_](card_object.validationresults.md)

## Properties

### allIds

• `Readonly` **allIds**: [_Dictionary_](../modules/shared.md#dictionary)<number\>

Defined in: [card-object.ts:12](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L12)

---

### validationEvents

• `Readonly` **validationEvents**: [_IValidationEvent_](../interfaces/serialization.ivalidationevent.md)[]

Defined in: [card-object.ts:13](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L13)

## Methods

### addFailure

▸ **addFailure**(`cardObject`: [_CardObject_](card_object.cardobject.md), `event`: [_ValidationEvent_](../enums/enums.validationevent.md), `message`: _string_): _void_

#### Parameters:

| Name         | Type                                                   |
| :----------- | :----------------------------------------------------- |
| `cardObject` | [_CardObject_](card_object.cardobject.md)              |
| `event`      | [_ValidationEvent_](../enums/enums.validationevent.md) |
| `message`    | _string_                                               |

**Returns:** _void_

Defined in: [card-object.ts:15](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L15)
