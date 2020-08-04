[Adaptive Cards Javascript SDK](../README.md) › [PropertyDefinition](propertydefinition.md)

# Class: PropertyDefinition

## Hierarchy

* **PropertyDefinition**

  ↳ [StringProperty](stringproperty.md)

  ↳ [BoolProperty](boolproperty.md)

  ↳ [NumProperty](numproperty.md)

  ↳ [PixelSizeProperty](pixelsizeproperty.md)

  ↳ [ValueSetProperty](valuesetproperty.md)

  ↳ [EnumProperty](enumproperty.md)

  ↳ [SerializableObjectProperty](serializableobjectproperty.md)

  ↳ [SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)

  ↳ [CustomProperty](customproperty.md)

  ↳ [ActionProperty](actionproperty.md)

## Index

### Constructors

* [constructor](propertydefinition.md#constructor)

### Properties

* [defaultValue](propertydefinition.md#optional-defaultvalue)
* [isSerializationEnabled](propertydefinition.md#isserializationenabled)
* [name](propertydefinition.md#name)
* [onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)
* [sequentialNumber](propertydefinition.md#sequentialnumber)
* [targetVersion](propertydefinition.md#targetversion)

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

### `Optional` defaultValue

• **defaultValue**? : *any*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

___

###  name

• **name**: *string*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

___

###  sequentialNumber

• **sequentialNumber**: *number*

___

###  targetVersion

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
