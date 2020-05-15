[Adaptive Cards Javascript SDK](../README.md) › [ValidationResults](validationresults.md)

# Class: ValidationResults

## Hierarchy

* **ValidationResults**

## Index

### Properties

* [allIds](validationresults.md#allids)
* [validationEvents](validationresults.md#validationevents)

### Methods

* [addFailure](validationresults.md#addfailure)

## Properties

###  allIds

• **allIds**: *[Dictionary](../README.md#dictionary)‹number›*

*Defined in [card-object.ts:10](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-object.ts#L10)*

___

###  validationEvents

• **validationEvents**: *[IValidationEvent](../interfaces/ivalidationevent.md)[]* = []

*Defined in [card-object.ts:11](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-object.ts#L11)*

## Methods

###  addFailure

▸ **addFailure**(`cardObject`: [CardObject](cardobject.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): *void*

*Defined in [card-object.ts:13](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-object.ts#L13)*

**Parameters:**

Name | Type |
------ | ------ |
`cardObject` | [CardObject](cardobject.md) |
`event` | [ValidationEvent](../enums/validationevent.md) |
`message` | string |

**Returns:** *void*
