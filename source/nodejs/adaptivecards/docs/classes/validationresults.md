[Adaptive Cards Javascript SDK](../README.md) › [ValidationResults](validationresults.md)

# Class: ValidationResults

## Hierarchy

* **ValidationResults**

## Index

### Properties

* [allIds](validationresults.md#allids)
* [failures](validationresults.md#failures)

### Methods

* [addFailure](validationresults.md#addfailure)

## Properties

###  allIds

• **allIds**: *Shared.Dictionary‹number›*

*Defined in [card-elements.ts:222](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L222)*

___

###  failures

• **failures**: *[ValidationFailure](validationfailure.md)[]* = []

*Defined in [card-elements.ts:223](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L223)*

## Methods

###  addFailure

▸ **addFailure**(`cardObject`: [CardObject](cardobject.md), `error`: [IValidationError](../interfaces/ivalidationerror.md)): *void*

*Defined in [card-elements.ts:225](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L225)*

**Parameters:**

Name | Type |
------ | ------ |
`cardObject` | [CardObject](cardobject.md) |
`error` | [IValidationError](../interfaces/ivalidationerror.md) |

**Returns:** *void*
