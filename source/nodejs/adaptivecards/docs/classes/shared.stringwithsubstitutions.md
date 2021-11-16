[Adaptive Cards Javascript SDK](../README.md) / [shared](../modules/shared.md) / StringWithSubstitutions

# Class: StringWithSubstitutions

[shared](../modules/shared.md).StringWithSubstitutions

## Table of contents

### Constructors

- [constructor](shared.stringwithsubstitutions.md#constructor)

### Methods

- [get](shared.stringwithsubstitutions.md#get)
- [getOriginal](shared.stringwithsubstitutions.md#getoriginal)
- [getReferencedInputs](shared.stringwithsubstitutions.md#getreferencedinputs)
- [set](shared.stringwithsubstitutions.md#set)
- [substituteInputValues](shared.stringwithsubstitutions.md#substituteinputvalues)

## Constructors

### constructor

\+ **new StringWithSubstitutions**(): [*StringWithSubstitutions*](shared.stringwithsubstitutions.md)

**Returns:** [*StringWithSubstitutions*](shared.stringwithsubstitutions.md)

## Methods

### get

▸ **get**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [shared.ts:98](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L98)

___

### getOriginal

▸ **getOriginal**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [shared.ts:94](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L94)

___

### getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [*IInput*](../interfaces/shared.iinput.md)[], `referencedInputs`: [*Dictionary*](../modules/shared.md#dictionary)<[*IInput*](../interfaces/shared.iinput.md)\>): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`inputs` | [*IInput*](../interfaces/shared.iinput.md)[] |
`referencedInputs` | [*Dictionary*](../modules/shared.md#dictionary)<[*IInput*](../interfaces/shared.iinput.md)\> |

**Returns:** *void*

Defined in: [shared.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L43)

___

### set

▸ **set**(`value`: *undefined* \| *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| *string* |

**Returns:** *void*

Defined in: [shared.ts:107](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L107)

___

### substituteInputValues

▸ **substituteInputValues**(`inputs`: [*Dictionary*](../modules/shared.md#dictionary)<[*IInput*](../interfaces/shared.iinput.md)\>, `contentType`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`inputs` | [*Dictionary*](../modules/shared.md#dictionary)<[*IInput*](../interfaces/shared.iinput.md)\> |
`contentType` | *string* |

**Returns:** *void*

Defined in: [shared.ts:57](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L57)
