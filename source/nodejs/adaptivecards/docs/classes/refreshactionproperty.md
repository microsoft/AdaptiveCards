[Adaptive Cards Javascript SDK](../README.md) › [RefreshActionProperty](refreshactionproperty.md)

# Class: RefreshActionProperty

## Hierarchy

- [PropertyDefinition](propertydefinition.md)

  ↳ **RefreshActionProperty**

## Index

### Constructors

- [constructor](refreshactionproperty.md#constructor)

### Properties

- [defaultValue](refreshactionproperty.md#optional-defaultvalue)
- [isSerializationEnabled](refreshactionproperty.md#isserializationenabled)
- [name](refreshactionproperty.md#name)
- [onGetInitialValue](refreshactionproperty.md#optional-ongetinitialvalue)
- [sequentialNumber](refreshactionproperty.md#sequentialnumber)
- [targetVersion](refreshactionproperty.md#targetversion)

### Methods

- [getInternalName](refreshactionproperty.md#getinternalname)
- [parse](refreshactionproperty.md#parse)
- [toJSON](refreshactionproperty.md#tojson)

## Constructors

### constructor

\+ **new RefreshActionProperty**(`targetVersion`: [Version](version.md), `name`: string): _[RefreshActionProperty](refreshactionproperty.md)_

_Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)_

**Parameters:**

| Name            | Type                  |
| --------------- | --------------------- |
| `targetVersion` | [Version](version.md) |
| `name`          | string                |

**Returns:** _[RefreshActionProperty](refreshactionproperty.md)_

## Properties

### `Optional` defaultValue

• **defaultValue**? : _any_

_Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)_

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

_Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)_

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

▸ **parse**(`sender`: [RefreshDefinition](refreshdefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): _[ExecuteAction](executeaction.md) | undefined_

_Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)_

**Parameters:**

| Name      | Type                                            |
| --------- | ----------------------------------------------- |
| `sender`  | [RefreshDefinition](refreshdefinition.md)       |
| `source`  | [PropertyBag](../README.md#propertybag)         |
| `context` | [SerializationContext](serializationcontext.md) |

**Returns:** _[ExecuteAction](executeaction.md) | undefined_

---

### toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [ExecuteAction](executeaction.md) | undefined, `context`: [SerializationContext](serializationcontext.md)): _void_

_Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)_

**Parameters:**

| Name      | Type                                               |
| --------- | -------------------------------------------------- |
| `sender`  | [SerializableObject](serializableobject.md)        |
| `target`  | [PropertyBag](../README.md#propertybag)            |
| `value`   | [ExecuteAction](executeaction.md) &#124; undefined |
| `context` | [SerializationContext](serializationcontext.md)    |

**Returns:** _void_
