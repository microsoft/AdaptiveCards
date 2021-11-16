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

\+ **new PropertyDefinition**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `defaultValue?`: _any_, `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_): [_PropertyDefinition_](serialization.propertydefinition.md)

#### Parameters:

| Name                 | Type                                                                             |
| :------------------- | :------------------------------------------------------------------------------- |
| `targetVersion`      | [_Version_](serialization.version.md)                                            |
| `name`               | _string_                                                                         |
| `defaultValue?`      | _any_                                                                            |
| `onGetInitialValue?` | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_ |

**Returns:** [_PropertyDefinition_](serialization.propertydefinition.md)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _any_

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_= true

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

---

### name

• `Readonly` **name**: _string_

---

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_

---

### sequentialNumber

• `Readonly` **sequentialNumber**: _number_

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

---

### targetVersion

• `Readonly` **targetVersion**: [_Version_](serialization.version.md)

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

---

### parse

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _any_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _any_

Defined in: [serialization.ts:266](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L266)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _any_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `value`   | _any_                                                                   |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Defined in: [serialization.ts:270](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L270)
