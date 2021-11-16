[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / StringProperty

# Class: StringProperty

[adaptivecards](../modules/adaptivecards.md).StringProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

  ↳ **StringProperty**

## Table of contents

### Constructors

- [constructor](adaptivecards.stringproperty.md#constructor)

### Properties

- [defaultValue](adaptivecards.stringproperty.md#defaultvalue)
- [isSerializationEnabled](adaptivecards.stringproperty.md#isserializationenabled)
- [name](adaptivecards.stringproperty.md#name)
- [onGetInitialValue](adaptivecards.stringproperty.md#ongetinitialvalue)
- [regEx](adaptivecards.stringproperty.md#regex)
- [sequentialNumber](adaptivecards.stringproperty.md#sequentialnumber)
- [targetVersion](adaptivecards.stringproperty.md#targetversion)
- [treatEmptyAsUndefined](adaptivecards.stringproperty.md#treatemptyasundefined)

### Methods

- [getInternalName](adaptivecards.stringproperty.md#getinternalname)
- [parse](adaptivecards.stringproperty.md#parse)
- [toJSON](adaptivecards.stringproperty.md#tojson)

## Constructors

### constructor

\+ **new StringProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `treatEmptyAsUndefined?`: _boolean_, `regEx?`: _RegExp_, `defaultValue?`: _string_, `onGetInitialValue?`: (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _string_): [_StringProperty_](serialization.stringproperty.md)

#### Parameters:

| Name                    | Type                                                                                | Default value |
| :---------------------- | :---------------------------------------------------------------------------------- | :------------ |
| `targetVersion`         | [_Version_](serialization.version.md)                                               | -             |
| `name`                  | _string_                                                                            | -             |
| `treatEmptyAsUndefined` | _boolean_                                                                           | true          |
| `regEx?`                | _RegExp_                                                                            | -             |
| `defaultValue?`         | _string_                                                                            | -             |
| `onGetInitialValue?`    | (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _string_ | -             |

**Returns:** [_StringProperty_](serialization.stringproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:316](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L316)

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

### regEx

• `Optional` `Readonly` **regEx**: _undefined_ \| _RegExp_

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

### treatEmptyAsUndefined

• `Readonly` **treatEmptyAsUndefined**: _boolean_= true

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

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

Defined in: [serialization.ts:290](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L290)

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

Defined in: [serialization.ts:310](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L310)
