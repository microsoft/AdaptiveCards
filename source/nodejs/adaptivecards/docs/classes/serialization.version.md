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

\+ **new Version**(`major?`: *number*, `minor?`: *number*, `label?`: *string*): [*Version*](serialization.version.md)

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`major` | *number* | 1 |
`minor` | *number* | 1 |
`label?` | *string* | - |

**Returns:** [*Version*](serialization.version.md)

Defined in: [serialization.ts:20](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L20)

## Accessors

### isValid

• get **isValid**(): *boolean*

**Returns:** *boolean*

Defined in: [serialization.ts:98](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L98)

___

### label

• get **label**(): *string*

**Returns:** *string*

Defined in: [serialization.ts:86](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L86)

___

### major

• get **major**(): *number*

**Returns:** *number*

Defined in: [serialization.ts:90](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L90)

___

### minor

• get **minor**(): *number*

**Returns:** *number*

Defined in: [serialization.ts:94](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L94)

## Methods

### compareTo

▸ **compareTo**(`otherVersion`: [*Version*](serialization.version.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`otherVersion` | [*Version*](serialization.version.md) |

**Returns:** *number*

Defined in: [serialization.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L65)

___

### toJSON

▸ **toJSON**(): *any*

**Returns:** *any*

Defined in: [serialization.ts:61](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L61)

___

### toString

▸ **toString**(): *string*

**Returns:** *string*

Defined in: [serialization.ts:57](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L57)

___

### parse

▸ `Static`**parse**(`versionString`: *string*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*Version*](serialization.version.md)

#### Parameters:

Name | Type |
:------ | :------ |
`versionString` | *string* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*Version*](serialization.version.md)

Defined in: [serialization.ts:28](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L28)
