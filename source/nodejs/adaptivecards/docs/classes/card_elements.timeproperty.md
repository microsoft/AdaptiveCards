[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / TimeProperty

# Class: TimeProperty

[card-elements](../modules/card_elements.md).TimeProperty

## Hierarchy

- [_CustomProperty_](serialization.customproperty.md)<string \| undefined\>

  ↳ **TimeProperty**

## Table of contents

### Constructors

- [constructor](card_elements.timeproperty.md#constructor)

### Properties

- [defaultValue](card_elements.timeproperty.md#defaultvalue)
- [isSerializationEnabled](card_elements.timeproperty.md#isserializationenabled)
- [name](card_elements.timeproperty.md#name)
- [onGetInitialValue](card_elements.timeproperty.md#ongetinitialvalue)
- [onParse](card_elements.timeproperty.md#onparse)
- [onToJSON](card_elements.timeproperty.md#ontojson)
- [sequentialNumber](card_elements.timeproperty.md#sequentialnumber)
- [targetVersion](card_elements.timeproperty.md#targetversion)

### Methods

- [getInternalName](card_elements.timeproperty.md#getinternalname)
- [parse](card_elements.timeproperty.md#parse)
- [toJSON](card_elements.timeproperty.md#tojson)

## Constructors

### constructor

\+ **new TimeProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_): [_TimeProperty_](card_elements.timeproperty.md)

#### Parameters:

| Name            | Type                                  |
| :-------------- | :------------------------------------ |
| `targetVersion` | [_Version_](serialization.version.md) |
| `name`          | _string_                              |

**Returns:** [_TimeProperty_](card_elements.timeproperty.md)

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [card-elements.ts:3523](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3523)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _undefined_ \| _string_

Inherited from: [CustomProperty](serialization.customproperty.md).[defaultValue](serialization.customproperty.md#defaultvalue)

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_= true

Inherited from: [CustomProperty](serialization.customproperty.md).[isSerializationEnabled](serialization.customproperty.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

---

### name

• `Readonly` **name**: _string_

Inherited from: [CustomProperty](serialization.customproperty.md).[name](serialization.customproperty.md#name)

---

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _undefined_ \| _string_

Inherited from: [CustomProperty](serialization.customproperty.md).[onGetInitialValue](serialization.customproperty.md#ongetinitialvalue)

---

### onParse

• `Readonly` **onParse**: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => _undefined_ \| _string_

#### Type declaration:

▸ (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| _string_

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `sender`   | [_SerializableObject_](serialization.serializableobject.md)             |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md)             |
| `source`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context`  | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| _string_

Defined in: [serialization.ts:695](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L695)

Inherited from: [CustomProperty](serialization.customproperty.md).[onParse](serialization.customproperty.md#onparse)

---

### onToJSON

• `Readonly` **onToJSON**: (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| _string_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)) => _void_

#### Type declaration:

▸ (`sender`: [_SerializableObject_](serialization.serializableobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| _string_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `sender`   | [_SerializableObject_](serialization.serializableobject.md)             |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md)             |
| `target`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `value`    | _undefined_ \| _string_                                                 |
| `context`  | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Defined in: [serialization.ts:696](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L696)

Inherited from: [CustomProperty](serialization.customproperty.md).[onToJSON](serialization.customproperty.md#ontojson)

---

### sequentialNumber

• `Readonly` **sequentialNumber**: _number_

Inherited from: [CustomProperty](serialization.customproperty.md).[sequentialNumber](serialization.customproperty.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

---

### targetVersion

• `Readonly` **targetVersion**: [_Version_](serialization.version.md)

Inherited from: [CustomProperty](serialization.customproperty.md).[targetVersion](serialization.customproperty.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Inherited from: [CustomProperty](serialization.customproperty.md)

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

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [serialization.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L684)

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

Inherited from: [CustomProperty](serialization.customproperty.md)

Defined in: [serialization.ts:688](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L688)
