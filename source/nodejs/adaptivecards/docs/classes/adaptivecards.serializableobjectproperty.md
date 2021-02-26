[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SerializableObjectProperty

# Class: SerializableObjectProperty

[adaptivecards](../modules/adaptivecards.md).SerializableObjectProperty

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **SerializableObjectProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.serializableobjectproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.serializableobjectproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.serializableobjectproperty.md#isserializationenabled)
- [name](adaptivecards.serializableobjectproperty.md#name)
- [objectType](adaptivecards.serializableobjectproperty.md#objecttype)
- [onGetInitialValue](adaptivecards.serializableobjectproperty.md#ongetinitialvalue)
- [sequentialNumber](adaptivecards.serializableobjectproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.serializableobjectproperty.md#targetversion)

### Methods

- [getInternalName](adaptivecards.serializableobjectproperty.md#getinternalname)
- [parse](adaptivecards.serializableobjectproperty.md#parse)
- [toJSON](adaptivecards.serializableobjectproperty.md#tojson)

## Constructors

### constructor

\+ **new SerializableObjectProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `objectType`: [*SerializableObjectType*](../modules/serialization.md#serializableobjecttype), `defaultValue?`: [*SerializableObject*](serialization.serializableobject.md)): [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`objectType` | [*SerializableObjectType*](../modules/serialization.md#serializableobjecttype) |
`defaultValue?` | [*SerializableObject*](serialization.serializableobject.md) |

**Returns:** [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:629](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L629)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *any*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

___

### isSerializationEnabled

• **isSerializationEnabled**: *boolean*= true

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

___

### name

• `Readonly` **name**: *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[name](serialization.propertydefinition.md#name)

___

### objectType

• `Readonly` **objectType**: [*SerializableObjectType*](../modules/serialization.md#serializableobjecttype)

___

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*SerializableObject*](serialization.serializableobject.md)

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*SerializableObject*](serialization.serializableobject.md)

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:608](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L608)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| [*SerializableObject*](serialization.serializableobject.md), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *undefined* \| [*SerializableObject*](serialization.serializableobject.md) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:621](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L621)
