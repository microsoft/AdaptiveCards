[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / GlobalRegistry

# Class: GlobalRegistry

[adaptivecards](../modules/adaptivecards.md).GlobalRegistry

## Table of contents

### Constructors

- [constructor](adaptivecards.globalregistry.md#constructor)

### Properties

- [actions](adaptivecards.globalregistry.md#actions)
- [elements](adaptivecards.globalregistry.md#elements)

### Methods

- [populateWithDefaultActions](adaptivecards.globalregistry.md#populatewithdefaultactions)
- [populateWithDefaultElements](adaptivecards.globalregistry.md#populatewithdefaultelements)
- [reset](adaptivecards.globalregistry.md#reset)

## Constructors

### constructor

\+ **new GlobalRegistry**(): [_GlobalRegistry_](card_elements.globalregistry.md)

**Returns:** [_GlobalRegistry_](card_elements.globalregistry.md)

## Properties

### actions

▪ `Readonly` `Static` **actions**: [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\>

Defined in: [card-elements.ts:6728](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6728)

---

### elements

▪ `Readonly` `Static` **elements**: [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\>

Defined in: [card-elements.ts:6727](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6727)

## Methods

### populateWithDefaultActions

▸ `Static`**populateWithDefaultActions**(`registry`: [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\>): _void_

#### Parameters:

| Name       | Type                                                                                         |
| :--------- | :------------------------------------------------------------------------------------------- |
| `registry` | [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_Action_](card_elements.action.md)\> |

**Returns:** _void_

Defined in: [card-elements.ts:6718](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6718)

---

### populateWithDefaultElements

▸ `Static`**populateWithDefaultElements**(`registry`: [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\>): _void_

#### Parameters:

| Name       | Type                                                                                                   |
| :--------- | :----------------------------------------------------------------------------------------------------- |
| `registry` | [_CardObjectRegistry_](registry.cardobjectregistry.md)<[_CardElement_](card_elements.cardelement.md)\> |

**Returns:** _void_

Defined in: [card-elements.ts:6697](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6697)

---

### reset

▸ `Static`**reset**(): _void_

**Returns:** _void_

Defined in: [card-elements.ts:6730](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6730)
