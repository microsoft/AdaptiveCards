[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / SerializableObjectCollectionProperty

# Class: SerializableObjectCollectionProperty

[serialization](../modules/serialization.md).SerializableObjectCollectionProperty

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **SerializableObjectCollectionProperty**

## Table of contents

### Constructors

- [constructor](serialization.serializableobjectcollectionproperty.md#constructor)

### Properties

- [defaultValue](serialization.serializableobjectcollectionproperty.md#defaultvalue)
- [isSerializationEnabled](serialization.serializableobjectcollectionproperty.md#isserializationenabled)
- [name](serialization.serializableobjectcollectionproperty.md#name)
- [objectType](serialization.serializableobjectcollectionproperty.md#objecttype)
- [onGetInitialValue](serialization.serializableobjectcollectionproperty.md#ongetinitialvalue)
- [onItemAdded](serialization.serializableobjectcollectionproperty.md#onitemadded)
- [sequentialNumber](serialization.serializableobjectcollectionproperty.md#sequentialnumber)
- [targetVersion](serialization.serializableobjectcollectionproperty.md#targetversion)

### Methods

- [getInternalName](serialization.serializableobjectcollectionproperty.md#getinternalname)
- [parse](serialization.serializableobjectcollectionproperty.md#parse)
- [toJSON](serialization.serializableobjectcollectionproperty.md#tojson)

## Constructors

### constructor

\+ **new SerializableObjectCollectionProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `objectType`: [*SerializableObjectType*](../modules/serialization.md#serializableobjecttype), `onItemAdded?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md), `item`: [*SerializableObject*](serialization.serializableobject.md)) => *void*): [*SerializableObjectCollectionProperty*](serialization.serializableobjectcollectionproperty.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`objectType` | [*SerializableObjectType*](../modules/serialization.md#serializableobjecttype) |
`onItemAdded?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md), `item`: [*SerializableObject*](serialization.serializableobject.md)) => *void* |

**Returns:** [*SerializableObjectCollectionProperty*](serialization.serializableobjectcollectionproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:668](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L668)

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

### onItemAdded

• `Optional` `Readonly` **onItemAdded**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `item`: [*SerializableObject*](serialization.serializableobject.md)) => *void*

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

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*SerializableObject*](serialization.serializableobject.md)[]

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*SerializableObject*](serialization.serializableobject.md)[]

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:645](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L645)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| [*SerializableObject*](serialization.serializableobject.md)[], `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *undefined* \| [*SerializableObject*](serialization.serializableobject.md)[] |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:666](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L666)
