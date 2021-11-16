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

\+ **new StringWithSubstitutions**(): [_StringWithSubstitutions_](shared.stringwithsubstitutions.md)

**Returns:** [_StringWithSubstitutions_](shared.stringwithsubstitutions.md)

## Methods

### get

▸ **get**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [shared.ts:98](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L98)

---

### getOriginal

▸ **getOriginal**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [shared.ts:94](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L94)

---

### getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [_IInput_](../interfaces/shared.iinput.md)[], `referencedInputs`: [_Dictionary_](../modules/shared.md#dictionary)<[_IInput_](../interfaces/shared.iinput.md)\>): _void_

#### Parameters:

| Name               | Type                                                                                         |
| :----------------- | :------------------------------------------------------------------------------------------- |
| `inputs`           | [_IInput_](../interfaces/shared.iinput.md)[]                                                 |
| `referencedInputs` | [_Dictionary_](../modules/shared.md#dictionary)<[_IInput_](../interfaces/shared.iinput.md)\> |

**Returns:** _void_

Defined in: [shared.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L43)

---

### set

▸ **set**(`value`: _undefined_ \| _string_): _void_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `value` | _undefined_ \| _string_ |

**Returns:** _void_

Defined in: [shared.ts:107](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L107)

---

### substituteInputValues

▸ **substituteInputValues**(`inputs`: [_Dictionary_](../modules/shared.md#dictionary)<[_IInput_](../interfaces/shared.iinput.md)\>, `contentType`: _string_): _void_

#### Parameters:

| Name          | Type                                                                                         |
| :------------ | :------------------------------------------------------------------------------------------- |
| `inputs`      | [_Dictionary_](../modules/shared.md#dictionary)<[_IInput_](../interfaces/shared.iinput.md)\> |
| `contentType` | _string_                                                                                     |

**Returns:** _void_

Defined in: [shared.ts:57](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/shared.ts#L57)
