[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / PropertyDefinition

# Class: PropertyDefinition

[serialization](../modules/serialization.md).PropertyDefinition

## Hierarchy

- **PropertyDefinition**

  ↳ [_ActionProperty_](card_elements.actionproperty.md)

  ↳ [_StringProperty_](serialization.stringproperty.md)

  ↳ [_BoolProperty_](serialization.boolproperty.md)

  ↳ [_NumProperty_](serialization.numproperty.md)

  ↳ [_PixelSizeProperty_](serialization.pixelsizeproperty.md)

  ↳ [_ValueSetProperty_](serialization.valuesetproperty.md)

  ↳ [_EnumProperty_](serialization.enumproperty.md)

  ↳ [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

  ↳ [_SerializableObjectCollectionProperty_](serialization.serializableobjectcollectionproperty.md)

  ↳ [_CustomProperty_](serialization.customproperty.md)

  ↳ [_StringProperty_](adaptivecards.stringproperty.md)

  ↳ [_BoolProperty_](adaptivecards.boolproperty.md)

  ↳ [_NumProperty_](adaptivecards.numproperty.md)

  ↳ [_PixelSizeProperty_](adaptivecards.pixelsizeproperty.md)

  ↳ [_ValueSetProperty_](adaptivecards.valuesetproperty.md)

  ↳ [_EnumProperty_](adaptivecards.enumproperty.md)

  ↳ [_SerializableObjectProperty_](adaptivecards.serializableobjectproperty.md)

  ↳ [_SerializableObjectCollectionProperty_](adaptivecards.serializableobjectcollectionproperty.md)

  ↳ [_CustomProperty_](adaptivecards.customproperty.md)

  ↳ [_ActionProperty_](adaptivecards.actionproperty.md)

## Table of contents

### Constructors

- [constructor](serialization.propertydefinition.md#constructor)

### Properties

- [defaultValue](serialization.propertydefinition.md#defaultvalue)
- [isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)
- [name](serialization.propertydefinition.md#name)
- [onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)
- [sequentialNumber](serialization.propertydefinition.md#sequentialnumber)
- [targetVersion](serialization.propertydefinition.md#targetversion)

### Methods

- [getInternalName](serialization.propertydefinition.md#getinternalname)
- [parse](serialization.propertydefinition.md#parse)
- [toJSON](serialization.propertydefinition.md#tojson)

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
