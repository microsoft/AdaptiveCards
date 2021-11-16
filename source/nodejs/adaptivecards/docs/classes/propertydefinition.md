[Adaptive Cards Javascript SDK](../README.md) › [PropertyDefinition](propertydefinition.md)

# Class: PropertyDefinition

## Hierarchy

* **PropertyDefinition**

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

* [constructor](propertydefinition.md#constructor)

### Properties

* [defaultValue](propertydefinition.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](propertydefinition.md#isserializationenabled)
* [name](propertydefinition.md#readonly-name)
* [onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](propertydefinition.md#readonly-sequentialnumber)
* [targetVersion](propertydefinition.md#readonly-targetversion)

### Methods

* [getInternalName](propertydefinition.md#getinternalname)
* [parse](propertydefinition.md#parse)
* [toJSON](propertydefinition.md#tojson)

## Constructors

###  constructor

\+ **new PropertyDefinition**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): *[PropertyDefinition](propertydefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`defaultValue?` | any |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[PropertyDefinition](propertydefinition.md)*

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *any*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

___

### `Readonly` name

• **name**: *string*

___

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

___

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *any*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *any*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: any, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | any |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
