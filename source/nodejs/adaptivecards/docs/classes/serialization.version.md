[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / Version

# Class: Version

[serialization](../modules/serialization.md).Version

## Table of contents

### Constructors

- [constructor](serialization.version.md#constructor)

### Accessors

- [isValid](serialization.version.md#isvalid)
- [label](serialization.version.md#label)
- [major](serialization.version.md#major)
- [minor](serialization.version.md#minor)

### Methods

- [compareTo](serialization.version.md#compareto)
- [toJSON](serialization.version.md#tojson)
- [toString](serialization.version.md#tostring)
- [parse](serialization.version.md#parse)

## Constructors

### constructor

\+ **new Version**(`major?`: _number_, `minor?`: _number_, `label?`: _string_): [_Version_](serialization.version.md)

#### Parameters:

| Name     | Type     | Default value |
| :------- | :------- | :------------ |
| `major`  | _number_ | 1             |
| `minor`  | _number_ | 1             |
| `label?` | _string_ | -             |

**Returns:** [_Version_](serialization.version.md)

Defined in: [serialization.ts:20](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L20)

## Accessors

### isValid

• get **isValid**(): _boolean_

**Returns:** _boolean_

Defined in: [serialization.ts:98](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L98)

---

### label

• get **label**(): _string_

**Returns:** _string_

Defined in: [serialization.ts:86](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L86)

---

### major

• get **major**(): _number_

**Returns:** _number_

Defined in: [serialization.ts:90](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L90)

---

### minor

• get **minor**(): _number_

**Returns:** _number_

Defined in: [serialization.ts:94](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L94)

## Methods

### compareTo

▸ **compareTo**(`otherVersion`: [_Version_](serialization.version.md)): _number_

#### Parameters:

| Name           | Type                                  |
| :------------- | :------------------------------------ |
| `otherVersion` | [_Version_](serialization.version.md) |

**Returns:** _number_

Defined in: [serialization.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L65)

---

### toJSON

▸ **toJSON**(): _any_

**Returns:** _any_

Defined in: [serialization.ts:61](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L61)

---

### toString

▸ **toString**(): _string_

**Returns:** _string_

Defined in: [serialization.ts:57](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L57)

---

### parse

▸ `Static`**parse**(`versionString`: _string_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_Version_](serialization.version.md)

#### Parameters:

| Name            | Type                                                                    |
| :-------------- | :---------------------------------------------------------------------- |
| `versionString` | _string_                                                                |
| `context`       | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_Version_](serialization.version.md)

Defined in: [serialization.ts:28](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L28)
