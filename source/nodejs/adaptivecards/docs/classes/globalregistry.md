[Adaptive Cards Javascript SDK](../README.md) › [GlobalRegistry](globalregistry.md)

# Class: GlobalRegistry

## Hierarchy

* **GlobalRegistry**

## Index

### Properties

* [actions](globalregistry.md#static-actions)
* [elements](globalregistry.md#static-elements)

### Methods

* [populateWithDefaultActions](globalregistry.md#static-populatewithdefaultactions)
* [populateWithDefaultElements](globalregistry.md#static-populatewithdefaultelements)
* [reset](globalregistry.md#static-reset)

## Properties

### `Static` actions

▪ **actions**: *[CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)‹››* = new CardObjectRegistry<Action>()

*Defined in [card-elements.ts:6240](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L6240)*

___

### `Static` elements

▪ **elements**: *[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)‹››* = new CardObjectRegistry<CardElement>()

*Defined in [card-elements.ts:6239](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L6239)*

## Methods

### `Static` populateWithDefaultActions

▸ **populateWithDefaultActions**(`registry`: [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›): *void*

*Defined in [card-elements.ts:6230](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L6230)*

**Parameters:**

Name | Type |
------ | ------ |
`registry` | [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› |

**Returns:** *void*

___

### `Static` populateWithDefaultElements

▸ **populateWithDefaultElements**(`registry`: [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›): *void*

*Defined in [card-elements.ts:6209](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L6209)*

**Parameters:**

Name | Type |
------ | ------ |
`registry` | [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› |

**Returns:** *void*

___

### `Static` reset

▸ **reset**(): *void*

*Defined in [card-elements.ts:6242](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/card-elements.ts#L6242)*

**Returns:** *void*
