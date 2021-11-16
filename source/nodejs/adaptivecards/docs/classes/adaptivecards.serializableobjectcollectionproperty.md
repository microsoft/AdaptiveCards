[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SerializableObjectCollectionProperty

# Class: SerializableObjectCollectionProperty

[adaptivecards](../modules/adaptivecards.md).SerializableObjectCollectionProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **SerializableObjectCollectionProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.serializableobjectcollectionproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.serializableobjectcollectionproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.serializableobjectcollectionproperty.md#isserializationenabled)
- [name](adaptivecards.serializableobjectcollectionproperty.md#name)
- [objectType](adaptivecards.serializableobjectcollectionproperty.md#objecttype)
- [onGetInitialValue](adaptivecards.serializableobjectcollectionproperty.md#ongetinitialvalue)
- [onItemAdded](adaptivecards.serializableobjectcollectionproperty.md#onitemadded)
- [sequentialNumber](adaptivecards.serializableobjectcollectionproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.serializableobjectcollectionproperty.md#targetversion)

### Methods

- [getInternalName](adaptivecards.serializableobjectcollectionproperty.md#getinternalname)
- [parse](adaptivecards.serializableobjectcollectionproperty.md#parse)
- [toJSON](adaptivecards.serializableobjectcollectionproperty.md#tojson)

## Constructors

### constructor

\+ **new SerializableObjectCollectionProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `objectType`: [_SerializableObjectType_](../modules/serialization.md#serializableobjecttype), `onItemAdded?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `item`: [_SerializableObject_](serialization.serializableobject.md)) => _void_): [_SerializableObjectCollectionProperty_](serialization.serializableobjectcollectionproperty.md)

#### Parameters:

| Name            | Type                                                                                                                                                   |
| :-------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------- |
| `targetVersion` | [_Version_](serialization.version.md)                                                                                                                  |
| `name`          | _string_                                                                                                                                               |
| `objectType`    | [_SerializableObjectType_](../modules/serialization.md#serializableobjecttype)                                                                         |
| `onItemAdded?`  | (`sender`: [_SerializableObject_](serialization.serializableobject.md), `item`: [_SerializableObject_](serialization.serializableobject.md)) => _void_ |

**Returns:** [_SerializableObjectCollectionProperty_](serialization.serializableobjectcollectionproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:668](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L668)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _any_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_= true

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

---

### name

• `Readonly` **name**: _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[name](serialization.propertydefinition.md#name)

---

### objectType

• `Readonly` **objectType**: [_SerializableObjectType_](../modules/serialization.md#serializableobjecttype)

---

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

---

### onItemAdded

• `Optional` `Readonly` **onItemAdded**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `item`: [_SerializableObject_](serialization.serializableobject.md)) => _void_

---

### sequentialNumber

• `Readonly` **sequentialNumber**: _number_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

---

### targetVersion

• `Readonly` **targetVersion**: [_Version_](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

---

### parse

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_SerializableObject_](serialization.serializableobject.md)[]

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_SerializableObject_](serialization.serializableobject.md)[]

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:645](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L645)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| [_SerializableObject_](serialization.serializableobject.md)[], `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                         |
| :-------- | :--------------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)                  |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                     |
| `value`   | _undefined_ \| [_SerializableObject_](serialization.serializableobject.md)[] |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md)      |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:666](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L666)
