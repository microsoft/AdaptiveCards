[Adaptive Cards Javascript SDK](../README.md) › [SerializableObjectProperty](serializableobjectproperty.md)

# Class: SerializableObjectProperty

## Hierarchy

- [PropertyDefinition](propertydefinition.md)

  ↳ **SerializableObjectProperty**

## Index

### Constructors

- [constructor](serializableobjectproperty.md#constructor)

### Properties

- [defaultValue](serializableobjectproperty.md#optional-readonly-defaultvalue)
- [isSerializationEnabled](serializableobjectproperty.md#isserializationenabled)
- [name](serializableobjectproperty.md#readonly-name)
- [nullable](serializableobjectproperty.md#nullable)
- [objectType](serializableobjectproperty.md#readonly-objecttype)
- [onGetInitialValue](serializableobjectproperty.md#optional-readonly-ongetinitialvalue)
- [sequentialNumber](serializableobjectproperty.md#readonly-sequentialnumber)
- [targetVersion](serializableobjectproperty.md#readonly-targetversion)

### Methods

- [getInternalName](serializableobjectproperty.md#getinternalname)
- [parse](serializableobjectproperty.md#parse)
- [toJSON](serializableobjectproperty.md#tojson)

## Constructors

### constructor

\+ **new SerializableObjectProperty**(`targetVersion`: [Version](version.md), `name`: string, `objectType`: [SerializableObjectType](../README.md#serializableobjecttype), `nullable`: boolean, `defaultValue?`: [SerializableObject](serializableobject.md)): _[SerializableObjectProperty](serializableobjectproperty.md)_

_Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)_

**Parameters:**

| Name            | Type                                                          | Default |
| --------------- | ------------------------------------------------------------- | ------- |
| `targetVersion` | [Version](version.md)                                         | -       |
| `name`          | string                                                        | -       |
| `objectType`    | [SerializableObjectType](../README.md#serializableobjecttype) | -       |
| `nullable`      | boolean                                                       | false   |
| `defaultValue?` | [SerializableObject](serializableobject.md)                   | -       |

**Returns:** _[SerializableObjectProperty](serializableobjectproperty.md)_

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : _any_

_Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)_

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_ = true

_Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)_

---

### `Readonly` name

• **name**: _string_

_Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)_

---

### nullable

• **nullable**: _boolean_

---

### `Readonly` objectType

• **objectType**: _[SerializableObjectType](../README.md#serializableobjecttype)_

---

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : _undefined | function_

_Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)_

---

### `Readonly` sequentialNumber

• **sequentialNumber**: _number_

_Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)_

---

### `Readonly` targetVersion

• **targetVersion**: _[Version](version.md)_

_Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)_

## Methods

### getInternalName

▸ **getInternalName**(): _string_

_Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)_

**Returns:** _string_

---

### parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _[SerializableObject](serializableobject.md) | undefined_

_Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `sender`  | [SerializableObject](serializableobject.md)             |
| `source`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _[SerializableObject](serializableobject.md) | undefined_

---

### toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [SerializableObject](serializableobject.md) | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

_Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)_

**Parameters:**

| Name      | Type                                                         |
| --------- | ------------------------------------------------------------ |
| `sender`  | [SerializableObject](serializableobject.md)                  |
| `target`  | [PropertyBag](../README.md#propertybag)                      |
| `value`   | [SerializableObject](serializableobject.md) &#124; undefined |
| `context` | [BaseSerializationContext](baseserializationcontext.md)      |

**Returns:** _void_
