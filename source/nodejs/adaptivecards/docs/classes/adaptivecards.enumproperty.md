[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / EnumProperty

# Class: EnumProperty<TEnum\>

[adaptivecards](../modules/adaptivecards.md).EnumProperty

## Type parameters

| Name    | Type     |
| :------ | :------- |
| `TEnum` | _object_ |

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **EnumProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.enumproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.enumproperty.md#defaultvalue)
- [enumType](adaptivecards.enumproperty.md#enumtype)
- [isSerializationEnabled](adaptivecards.enumproperty.md#isserializationenabled)
- [name](adaptivecards.enumproperty.md#name)
- [onGetInitialValue](adaptivecards.enumproperty.md#ongetinitialvalue)
- [sequentialNumber](adaptivecards.enumproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.enumproperty.md#targetversion)

### Accessors

- [values](adaptivecards.enumproperty.md#values)

### Methods

- [getInternalName](adaptivecards.enumproperty.md#getinternalname)
- [parse](adaptivecards.enumproperty.md#parse)
- [toJSON](adaptivecards.enumproperty.md#tojson)

## Constructors

### constructor

\+ **new EnumProperty**<TEnum\>(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `enumType`: TEnum, `defaultValue?`: _number_, `values?`: [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<number\>[], `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _number_): [_EnumProperty_](serialization.enumproperty.md)<TEnum\>

#### Type parameters:

| Name    | Type     |
| :------ | :------- |
| `TEnum` | _object_ |

#### Parameters:

| Name                 | Type                                                                                |
| :------------------- | :---------------------------------------------------------------------------------- |
| `targetVersion`      | [_Version_](serialization.version.md)                                               |
| `name`               | _string_                                                                            |
| `enumType`           | TEnum                                                                               |
| `defaultValue?`      | _number_                                                                            |
| `values?`            | [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<number\>[]      |
| `onGetInitialValue?` | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _number_ |

**Returns:** [_EnumProperty_](serialization.enumproperty.md)<TEnum\>

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:575](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L575)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _undefined_ \| _number_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

---

### enumType

• `Readonly` **enumType**: TEnum

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

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _number_

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

## Accessors

### values

• get **values**(): [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<number\>[]

**Returns:** [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<number\>[]

Defined in: [serialization.ts:600](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L600)

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

---

### parse

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| _number_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| _number_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:502](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L502)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| _number_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `value`   | _undefined_ \| _number_                                                 |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:543](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L543)
