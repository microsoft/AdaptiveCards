[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ValueSetProperty

# Class: ValueSetProperty

[adaptivecards](../modules/adaptivecards.md).ValueSetProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **ValueSetProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.valuesetproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.valuesetproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.valuesetproperty.md#isserializationenabled)
- [name](adaptivecards.valuesetproperty.md#name)
- [onGetInitialValue](adaptivecards.valuesetproperty.md#ongetinitialvalue)
- [sequentialNumber](adaptivecards.valuesetproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.valuesetproperty.md#targetversion)
- [values](adaptivecards.valuesetproperty.md#values)

### Methods

- [getInternalName](adaptivecards.valuesetproperty.md#getinternalname)
- [isValidValue](adaptivecards.valuesetproperty.md#isvalidvalue)
- [parse](adaptivecards.valuesetproperty.md#parse)
- [toJSON](adaptivecards.valuesetproperty.md#tojson)

## Constructors

### constructor

\+ **new ValueSetProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `values`: [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<string\>[], `defaultValue?`: _string_, `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _string_): [_ValueSetProperty_](serialization.valuesetproperty.md)

#### Parameters:

| Name                 | Type                                                                                |
| :------------------- | :---------------------------------------------------------------------------------- |
| `targetVersion`      | [_Version_](serialization.version.md)                                               |
| `name`               | _string_                                                                            |
| `values`             | [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<string\>[]      |
| `defaultValue?`      | _string_                                                                            |
| `onGetInitialValue?` | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _string_ |

**Returns:** [_ValueSetProperty_](serialization.valuesetproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:487](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L487)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _undefined_ \| _string_

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

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _string_

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

---

### values

• `Readonly` **values**: [_IVersionedValue_](../interfaces/serialization.iversionedvalue.md)<string\>[]

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

---

### isValidValue

▸ **isValidValue**(`value`: _string_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `value`   | _string_                                                                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _boolean_

Defined in: [serialization.ts:403](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L403)

---

### parse

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| _string_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| _string_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:415](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L415)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| _string_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `value`   | _undefined_ \| _string_                                                 |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:454](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L454)
