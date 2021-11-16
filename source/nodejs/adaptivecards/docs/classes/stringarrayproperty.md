[Adaptive Cards Javascript SDK](../README.md) › [StringArrayProperty](stringarrayproperty.md)

# Class: StringArrayProperty

## Hierarchy

- [PropertyDefinition](propertydefinition.md)

  ↳ **StringArrayProperty**

## Index

### Constructors

- [constructor](stringarrayproperty.md#constructor)

### Properties

- [defaultValue](stringarrayproperty.md#optional-defaultvalue)
- [isSerializationEnabled](stringarrayproperty.md#isserializationenabled)
- [name](stringarrayproperty.md#name)
- [onGetInitialValue](stringarrayproperty.md#optional-ongetinitialvalue)
- [sequentialNumber](stringarrayproperty.md#sequentialnumber)
- [targetVersion](stringarrayproperty.md#targetversion)

### Methods

- [getInternalName](stringarrayproperty.md#getinternalname)
- [parse](stringarrayproperty.md#parse)
- [toJSON](stringarrayproperty.md#tojson)

## Constructors

### constructor

\+ **new StringArrayProperty**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: string[], `onGetInitialValue?`: undefined | function): _[StringArrayProperty](stringarrayproperty.md)_

_Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)_

**Parameters:**

| Name                 | Type                      |
| -------------------- | ------------------------- |
| `targetVersion`      | [Version](version.md)     |
| `name`               | string                    |
| `defaultValue?`      | string[]                  |
| `onGetInitialValue?` | undefined &#124; function |

**Returns:** _[StringArrayProperty](stringarrayproperty.md)_

## Properties

### `Optional` defaultValue

• **defaultValue**? : _string[]_

_Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)_

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_ = true

_Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)_

---

### name

• **name**: _string_

_Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)_

---

### `Optional` onGetInitialValue

• **onGetInitialValue**? : _undefined | function_

_Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)_

---

### sequentialNumber

• **sequentialNumber**: _number_

_Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)_

---

### targetVersion

• **targetVersion**: _[Version](version.md)_

_Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)_

## Methods

### getInternalName

▸ **getInternalName**(): _string_

_Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)_

**Returns:** _string_

---

### parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _string[] | undefined_

_Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `sender`  | [SerializableObject](serializableobject.md)             |
| `source`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _string[] | undefined_

---

### toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string[] | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

_Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `sender`  | [SerializableObject](serializableobject.md)             |
| `target`  | [PropertyBag](../README.md#propertybag)                 |
| `value`   | string[] &#124; undefined                               |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_
