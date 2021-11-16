[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / PixelSizeProperty

# Class: PixelSizeProperty

[adaptivecards](../modules/adaptivecards.md).PixelSizeProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **PixelSizeProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.pixelsizeproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.pixelsizeproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.pixelsizeproperty.md#isserializationenabled)
- [name](adaptivecards.pixelsizeproperty.md#name)
- [onGetInitialValue](adaptivecards.pixelsizeproperty.md#ongetinitialvalue)
- [sequentialNumber](adaptivecards.pixelsizeproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.pixelsizeproperty.md#targetversion)

### Methods

- [getInternalName](adaptivecards.pixelsizeproperty.md#getinternalname)
- [parse](adaptivecards.pixelsizeproperty.md#parse)
- [toJSON](adaptivecards.pixelsizeproperty.md#tojson)

## Constructors

### constructor

\+ **new PixelSizeProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `defaultValue?`: _any_, `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_): [_PixelSizeProperty_](serialization.pixelsizeproperty.md)

#### Parameters:

| Name                 | Type                                                                             |
| :------------------- | :------------------------------------------------------------------------------- |
| `targetVersion`      | [_Version_](serialization.version.md)                                            |
| `name`               | _string_                                                                         |
| `defaultValue?`      | _any_                                                                            |
| `onGetInitialValue?` | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_ |

**Returns:** [_PixelSizeProperty_](serialization.pixelsizeproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

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

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| _number_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| _number_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:358](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L358)

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

Defined in: [serialization.ts:389](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L389)
