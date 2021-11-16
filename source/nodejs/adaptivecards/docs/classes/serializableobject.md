[Adaptive Cards Javascript SDK](../README.md) › [SerializableObject](serializableobject.md)

# Class: SerializableObject

## Hierarchy

- **SerializableObject**

  ↳ [HostCapabilities](hostcapabilities.md)

  ↳ [CardObject](cardobject.md)

  ↳ [Fact](fact.md)

  ↳ [MediaSource](mediasource.md)

  ↳ [Choice](choice.md)

  ↳ [HttpHeader](httpheader.md)

  ↳ [BackgroundImage](backgroundimage.md)

  ↳ [RefreshDefinition](refreshdefinition.md)

## Index

### Constructors

- [constructor](serializableobject.md#constructor)

### Properties

- [maxVersion](serializableobject.md#maxversion)
- [onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)

### Methods

- [getCustomProperty](serializableobject.md#getcustomproperty)
- [getDefaultSerializationContext](serializableobject.md#protected-getdefaultserializationcontext)
- [getSchema](serializableobject.md#getschema)
- [getSchemaKey](serializableobject.md#protected-abstract-getschemakey)
- [getValue](serializableobject.md#protected-getvalue)
- [hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)
- [hasDefaultValue](serializableobject.md#hasdefaultvalue)
- [internalParse](serializableobject.md#protected-internalparse)
- [internalToJSON](serializableobject.md#protected-internaltojson)
- [parse](serializableobject.md#parse)
- [populateSchema](serializableobject.md#protected-populateschema)
- [resetDefaultValues](serializableobject.md#resetdefaultvalues)
- [setCustomProperty](serializableobject.md#setcustomproperty)
- [setValue](serializableobject.md#protected-setvalue)
- [shouldSerialize](serializableobject.md#protected-shouldserialize)
- [toJSON](serializableobject.md#tojson)

## Constructors

### constructor

\+ **new SerializableObject**(): _[SerializableObject](serializableobject.md)_

**Returns:** _[SerializableObject](serializableobject.md)_

## Properties

### maxVersion

• **maxVersion**: _[Version](version.md)_ = Versions.v1_3

---

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : _undefined | function_

## Methods

### getCustomProperty

▸ **getCustomProperty**(`name`: string): _any_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `name` | string |

**Returns:** _any_

---

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): _[BaseSerializationContext](baseserializationcontext.md)_

**Returns:** _[BaseSerializationContext](baseserializationcontext.md)_

---

### getSchema

▸ **getSchema**(): _[SerializableObjectSchema](serializableobjectschema.md)_

**Returns:** _[SerializableObjectSchema](serializableobjectschema.md)_

---

### `Protected` `Abstract` getSchemaKey

▸ **getSchemaKey**(): _string_

**Returns:** _string_

---

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): _any_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _any_

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): _boolean_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _boolean_

---

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `source`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `target`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): _void_

**Parameters:**

| Name       | Type                                                    |
| ---------- | ------------------------------------------------------- |
| `source`   | [PropertyBag](../README.md#propertybag)                 |
| `context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): _void_

**Parameters:**

| Name     | Type                                                    |
| -------- | ------------------------------------------------------- |
| `schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** _void_

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

---

### setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): _void_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `name`  | string |
| `value` | any    |

**Returns:** _void_

---

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): _void_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |
| `value`    | any                                         |

**Returns:** _void_

---

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): _boolean_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _boolean_

---

### toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): _[PropertyBag](../README.md#propertybag) | undefined_

**Parameters:**

| Name       | Type                                                    |
| ---------- | ------------------------------------------------------- |
| `context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _[PropertyBag](../README.md#propertybag) | undefined_
