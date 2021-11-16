[Adaptive Cards Javascript SDK](../README.md) › [PropertyDefinition](propertydefinition.md)

# Class: PropertyDefinition

## Hierarchy

- **PropertyDefinition**

  ↳ [StringProperty](stringproperty.md)

  ↳ [BoolProperty](boolproperty.md)

  ↳ [NumProperty](numproperty.md)

  ↳ [PixelSizeProperty](pixelsizeproperty.md)

  ↳ [StringArrayProperty](stringarrayproperty.md)

  ↳ [ValueSetProperty](valuesetproperty.md)

  ↳ [EnumProperty](enumproperty.md)

  ↳ [SerializableObjectProperty](serializableobjectproperty.md)

  ↳ [SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)

  ↳ [CustomProperty](customproperty.md)

  ↳ [ActionProperty](actionproperty.md)

  ↳ [ImageDimensionProperty](imagedimensionproperty.md)

  ↳ [StringWithSubstitutionProperty](stringwithsubstitutionproperty.md)

## Index

### Constructors

- [constructor](propertydefinition.md#constructor)

### Properties

- [defaultValue](propertydefinition.md#optional-readonly-defaultvalue)
- [isSerializationEnabled](propertydefinition.md#isserializationenabled)
- [name](propertydefinition.md#readonly-name)
- [onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)
- [sequentialNumber](propertydefinition.md#readonly-sequentialnumber)
- [targetVersion](propertydefinition.md#readonly-targetversion)

### Methods

- [getInternalName](propertydefinition.md#getinternalname)
- [parse](propertydefinition.md#parse)
- [toJSON](propertydefinition.md#tojson)

## Constructors

### constructor

\+ **new PropertyDefinition**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): _[PropertyDefinition](propertydefinition.md)_

**Parameters:**

| Name                 | Type                      |
| -------------------- | ------------------------- |
| `targetVersion`      | [Version](version.md)     |
| `name`               | string                    |
| `defaultValue?`      | any                       |
| `onGetInitialValue?` | undefined &#124; function |

**Returns:** _[PropertyDefinition](propertydefinition.md)_

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : _any_

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_ = true

---

### `Readonly` name

• **name**: _string_

---

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : _undefined | function_

---

### `Readonly` sequentialNumber

• **sequentialNumber**: _number_

---

### `Readonly` targetVersion

• **targetVersion**: _[Version](version.md)_

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

---

### parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _any_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `sender`  | [SerializableObject](serializableobject.md)             |
| `source`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _any_

---

### toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: any, `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `sender`  | [SerializableObject](serializableobject.md)             |
| `target`  | [PropertyBag](../README.md#propertybag)                 |
| `value`   | any                                                     |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_
