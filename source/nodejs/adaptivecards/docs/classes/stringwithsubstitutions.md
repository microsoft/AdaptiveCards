[Adaptive Cards Javascript SDK](../README.md) › [StringWithSubstitutions](stringwithsubstitutions.md)

# Class: StringWithSubstitutions

## Hierarchy

* **StringWithSubstitutions**

## Index

### Methods

* [get](stringwithsubstitutions.md#get)
* [getOriginal](stringwithsubstitutions.md#getoriginal)
* [getReferencedInputs](stringwithsubstitutions.md#getreferencedinputs)
* [set](stringwithsubstitutions.md#set)
* [substituteInputValues](stringwithsubstitutions.md#substituteinputvalues)

## Methods

###  get

▸ **get**(): *string*

*Defined in [shared.ts:85](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L85)*

**Returns:** *string*

___

###  getOriginal

▸ **getOriginal**(): *string*

*Defined in [shared.ts:81](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L81)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [IInput](../interfaces/iinput.md)[], `referencedInputs`: [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)›): *void*

*Defined in [shared.ts:29](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L29)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [IInput](../interfaces/iinput.md)[] |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)› |

**Returns:** *void*

___

###  set

▸ **set**(`value`: string): *void*

*Defined in [shared.ts:94](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L94)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  substituteInputValues

▸ **substituteInputValues**(`inputs`: [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)›, `contentType`: string): *void*

*Defined in [shared.ts:43](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L43)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)› |
`contentType` | string |

**Returns:** *void*
