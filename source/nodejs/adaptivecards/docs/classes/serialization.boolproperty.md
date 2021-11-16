[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / BoolProperty

# Class: BoolProperty

[serialization](../modules/serialization.md).BoolProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **BoolProperty**

## Table of contents

### Constructors

- [constructor](serialization.boolproperty.md#constructor)

### Properties

- [defaultValue](serialization.boolproperty.md#defaultvalue)
- [isSerializationEnabled](serialization.boolproperty.md#isserializationenabled)
- [name](serialization.boolproperty.md#name)
- [onGetInitialValue](serialization.boolproperty.md#ongetinitialvalue)
- [sequentialNumber](serialization.boolproperty.md#sequentialnumber)
- [targetVersion](serialization.boolproperty.md#targetversion)

### Methods

- [getInternalName](serialization.boolproperty.md#getinternalname)
- [parse](serialization.boolproperty.md#parse)
- [toJSON](serialization.boolproperty.md#tojson)

## Constructors

### constructor

\+ **new BoolProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `defaultValue?`: _any_, `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_): [_BoolProperty_](serialization.boolproperty.md)

#### Parameters:

| Name                 | Type                                                                             |
| :------------------- | :------------------------------------------------------------------------------- |
| `targetVersion`      | [_Version_](serialization.version.md)                                            |
| `name`               | _string_                                                                         |
| `defaultValue?`      | _any_                                                                            |
| `onGetInitialValue?` | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_ |

**Returns:** [_BoolProperty_](serialization.boolproperty.md)

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

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| _boolean_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| _boolean_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:330](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L330)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: _object_, `value`: _undefined_ \| _boolean_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)             |
| `target`  | _object_                                                                |
| `value`   | _undefined_ \| _boolean_                                                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:334](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L334)
