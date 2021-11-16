[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / CustomProperty

# Class: CustomProperty<T\>

[serialization](../modules/serialization.md).CustomProperty

## Type parameters

| Name |
| :--- |
| `T`  |

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **CustomProperty**

  ↳↳ [_TimeProperty_](card_elements.timeproperty.md)

  ↳↳ [_TimeProperty_](adaptivecards.timeproperty.md)

## Table of contents

### Constructors

- [constructor](serialization.customproperty.md#constructor)

### Properties

- [defaultValue](serialization.customproperty.md#defaultvalue)
- [isSerializationEnabled](serialization.customproperty.md#isserializationenabled)
- [name](serialization.customproperty.md#name)
- [onGetInitialValue](serialization.customproperty.md#ongetinitialvalue)
- [onParse](serialization.customproperty.md#onparse)
- [onToJSON](serialization.customproperty.md#ontojson)
- [sequentialNumber](serialization.customproperty.md#sequentialnumber)
- [targetVersion](serialization.customproperty.md#targetversion)

### Methods

- [getInternalName](serialization.customproperty.md#getinternalname)
- [parse](serialization.customproperty.md#parse)
- [toJSON](serialization.customproperty.md#tojson)

## Constructors

### constructor

\+ **new CustomProperty**<T\>(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `onParse`: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => T, `onToJSON`: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: T, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => _void_, `defaultValue?`: T, `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => T): [_CustomProperty_](serialization.customproperty.md)<T\>

#### Type parameters:

| Name |
| :--- |
| `T`  |

#### Parameters:

| Name                 | Type                                                                                                                                                                                                                                                                                                                           |
| :------------------- | :----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `targetVersion`      | [_Version_](serialization.version.md)                                                                                                                                                                                                                                                                                          |
| `name`               | _string_                                                                                                                                                                                                                                                                                                                       |
| `onParse`            | (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => T                  |
| `onToJSON`           | (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: T, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => _void_ |
| `defaultValue?`      | T                                                                                                                                                                                                                                                                                                                              |
| `onGetInitialValue?` | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => T                                                                                                                                                                                                                                                   |

**Returns:** [_CustomProperty_](serialization.customproperty.md)<T\>

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:690](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L690)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _undefined_ \| T

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

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => T

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

---

### onParse

• `Readonly` **onParse**: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => T

#### Type declaration:

▸ (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): T

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `sender`   | [_SerializableObject_](serialization.serializableobject.md)             |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md)             |
| `source`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context`  | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** T

Defined in: [serialization.ts:695](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L695)

---

### onToJSON

• `Readonly` **onToJSON**: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: T, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => _void_

#### Type declaration:

▸ (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: T, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `sender`   | [_SerializableObject_](serialization.serializableobject.md)             |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md)             |
| `target`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `value`    | T                                                                       |
| `context`  | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Defined in: [serialization.ts:696](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L696)

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

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): T

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** T

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L684)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: T, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `value`   | T                                                                       |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:688](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L688)
