[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / SerializableObject

# Class: SerializableObject

[serialization](../modules/serialization.md).SerializableObject

## Hierarchy

- **SerializableObject**

  ↳ [_Fact_](card_elements.fact.md)

  ↳ [_MediaSource_](card_elements.mediasource.md)

  ↳ [_Choice_](card_elements.choice.md)

  ↳ [_HttpHeader_](card_elements.httpheader.md)

  ↳ [_BackgroundImage_](card_elements.backgroundimage.md)

  ↳ [_CardObject_](card_object.cardobject.md)

  ↳ [_HostCapabilities_](host_capabilities.hostcapabilities.md)

  ↳ [_CardObject_](adaptivecards.cardobject.md)

  ↳ [_Fact_](adaptivecards.fact.md)

  ↳ [_MediaSource_](adaptivecards.mediasource.md)

  ↳ [_Choice_](adaptivecards.choice.md)

  ↳ [_HttpHeader_](adaptivecards.httpheader.md)

  ↳ [_BackgroundImage_](adaptivecards.backgroundimage.md)

## Table of contents

### Constructors

- [constructor](serialization.serializableobject.md#constructor)

### Properties

- [maxVersion](serialization.serializableobject.md#maxversion)
- [defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)
- [onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

### Methods

- [getCustomProperty](serialization.serializableobject.md#getcustomproperty)
- [getDefaultSerializationContext](serialization.serializableobject.md#getdefaultserializationcontext)
- [getSchema](serialization.serializableobject.md#getschema)
- [getSchemaKey](serialization.serializableobject.md#getschemakey)
- [getValue](serialization.serializableobject.md#getvalue)
- [hasAllDefaultValues](serialization.serializableobject.md#hasalldefaultvalues)
- [hasDefaultValue](serialization.serializableobject.md#hasdefaultvalue)
- [internalParse](serialization.serializableobject.md#internalparse)
- [internalToJSON](serialization.serializableobject.md#internaltojson)
- [parse](serialization.serializableobject.md#parse)
- [populateSchema](serialization.serializableobject.md#populateschema)
- [resetDefaultValues](serialization.serializableobject.md#resetdefaultvalues)
- [setCustomProperty](serialization.serializableobject.md#setcustomproperty)
- [setValue](serialization.serializableobject.md#setvalue)
- [shouldSerialize](serialization.serializableobject.md#shouldserialize)
- [toJSON](serialization.serializableobject.md#tojson)

## Constructors

### constructor

\+ **new SerializableObject**(): [_SerializableObject_](serialization.serializableobject.md)

**Returns:** [_SerializableObject_](serialization.serializableobject.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

## Methods

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Defined in: [serialization.ts:784](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L784)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected` `Abstract`**getSchemaKey**(): _string_

**Returns:** _string_

Defined in: [serialization.ts:782](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L782)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### internalParse

▸ `Protected`**internalParse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

---

### parse

▸ **parse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `source`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Defined in: [serialization.ts:912](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L912)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

---

### setCustomProperty

▸ **setCustomProperty**(`name`: _string_, `value`: _any_): _void_

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `name`  | _string_ |
| `value` | _any_    |

**Returns:** _void_

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setValue

▸ `Protected`**setValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_): _void_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `value`    | _any_                                                       |

**Returns:** _void_

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _boolean_

Defined in: [serialization.ts:894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L894)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)
