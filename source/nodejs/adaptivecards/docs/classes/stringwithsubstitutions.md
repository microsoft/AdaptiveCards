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

▸ **get**(): *string | undefined*

*Defined in [shared.ts:97](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L97)*

**Returns:** *string | undefined*

___

###  getOriginal

▸ **getOriginal**(): *string | undefined*

*Defined in [shared.ts:93](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L93)*

**Returns:** *string | undefined*

___

###  getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [IInput](../interfaces/iinput.md)[], `referencedInputs`: [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)›): *void*

*Defined in [shared.ts:42](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L42)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [IInput](../interfaces/iinput.md)[] |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)› |

**Returns:** *void*

___

###  set

▸ **set**(`value`: string | undefined): *void*

*Defined in [shared.ts:106](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L106)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  substituteInputValues

▸ **substituteInputValues**(`inputs`: [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)›, `contentType`: string): *void*

*Defined in [shared.ts:56](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/shared.ts#L56)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[IInput](../interfaces/iinput.md)› |
`contentType` | string |

**Returns:** *void*
