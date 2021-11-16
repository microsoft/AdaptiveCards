[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / SerializableObjectProperty

# Class: SerializableObjectProperty

[adaptivecards](../modules/adaptivecards.md).SerializableObjectProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

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

\+ **new SerializableObjectProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `objectType`: [_SerializableObjectType_](../modules/serialization.md#serializableobjecttype), `defaultValue?`: [_SerializableObject_](serialization.serializableobject.md)): [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

#### Parameters:

| Name            | Type                                                                           |
| :-------------- | :----------------------------------------------------------------------------- |
| `targetVersion` | [_Version_](serialization.version.md)                                          |
| `name`          | _string_                                                                       |
| `objectType`    | [_SerializableObjectType_](../modules/serialization.md#serializableobjecttype) |
| `defaultValue?` | [_SerializableObject_](serialization.serializableobject.md)                    |

**Returns:** [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:629](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L629)

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

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_SerializableObject_](serialization.serializableobject.md)

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_SerializableObject_](serialization.serializableobject.md)

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:608](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L608)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| [_SerializableObject_](serialization.serializableobject.md), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                       |
| :-------- | :------------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)                |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                   |
| `value`   | _undefined_ \| [_SerializableObject_](serialization.serializableobject.md) |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md)    |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:621](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L621)
