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

*Defined in [card-elements.ts:6272](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6272)*

___

### `Static` elements

▪ **elements**: *[CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)‹››* = new CardObjectRegistry<CardElement>()

*Defined in [card-elements.ts:6271](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6271)*

## Methods

### `Static` populateWithDefaultActions

▸ **populateWithDefaultActions**(`registry`: [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)›): *void*

*Defined in [card-elements.ts:6262](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6262)*

**Parameters:**

Name | Type |
------ | ------ |
`registry` | [CardObjectRegistry](cardobjectregistry.md)‹[Action](action.md)› |

**Returns:** *void*

___

### `Static` populateWithDefaultElements

▸ **populateWithDefaultElements**(`registry`: [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)›): *void*

*Defined in [card-elements.ts:6241](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6241)*

**Parameters:**

Name | Type |
------ | ------ |
`registry` | [CardObjectRegistry](cardobjectregistry.md)‹[CardElement](cardelement.md)› |

**Returns:** *void*

___

### `Static` reset

▸ **reset**(): *void*

*Defined in [card-elements.ts:6274](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L6274)*

**Returns:** *void*
