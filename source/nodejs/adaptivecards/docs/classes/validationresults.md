[Adaptive Cards Javascript SDK](../README.md) › [ValidationResults](validationresults.md)

# Class: ValidationResults

Hols the results of a card deserialization.

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

Holds a map of all the element and action Ids found during the deserialization of
a card, along with the number of times they appear.

___

###  validationEvents

• **validationEvents**: *[IValidationEvent](../interfaces/ivalidationevent.md)[]* = []

Holds a collection of validation events (information, warnings, etc.) that occured
while deserializing a card.

## Methods

###  addFailure

▸ **addFailure**(`cardObject`: [CardObject](cardobject.md), `event`: [ValidationEvent](../enums/validationevent.md), `message`: string): *void*

Add a validation event/failure to the `validationEvents` collection.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`cardObject` | [CardObject](cardobject.md) | The card object that triggered the failure event |
`event` | [ValidationEvent](../enums/validationevent.md) | The validation event |
`message` | string | A message describing the event  |

**Returns:** *void*
