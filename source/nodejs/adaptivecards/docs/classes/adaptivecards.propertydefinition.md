[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / PropertyDefinition

# Class: PropertyDefinition

[adaptivecards](../modules/adaptivecards.md).PropertyDefinition

## Table of contents

### Constructors

- [constructor](adaptivecards.propertydefinition.md#constructor)

### Properties

- [defaultValue](adaptivecards.propertydefinition.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.propertydefinition.md#isserializationenabled)
- [name](adaptivecards.propertydefinition.md#name)
- [onGetInitialValue](adaptivecards.propertydefinition.md#ongetinitialvalue)
- [sequentialNumber](adaptivecards.propertydefinition.md#sequentialnumber)
- [targetVersion](adaptivecards.propertydefinition.md#targetversion)

### Methods

- [getInternalName](adaptivecards.propertydefinition.md#getinternalname)
- [parse](adaptivecards.propertydefinition.md#parse)
- [toJSON](adaptivecards.propertydefinition.md#tojson)

## Constructors

### constructor

\+ **new PropertyDefinition**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `defaultValue?`: *any*, `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*): [*PropertyDefinition*](serialization.propertydefinition.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`defaultValue?` | *any* |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any* |

**Returns:** [*PropertyDefinition*](serialization.propertydefinition.md)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *any*

___

### isSerializationEnabled

• **isSerializationEnabled**: *boolean*= true

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

___

### name

• `Readonly` **name**: *string*

___

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *any*

Defined in: [serialization.ts:266](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L266)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *any*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *any* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Defined in: [serialization.ts:270](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L270)
