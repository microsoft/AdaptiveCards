[Adaptive Cards Javascript SDK](../README.md) › [PixelSizeProperty](pixelsizeproperty.md)

# Class: PixelSizeProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **PixelSizeProperty**

## Index

### Constructors

* [constructor](pixelsizeproperty.md#constructor)

### Properties

* [defaultValue](pixelsizeproperty.md#optional-defaultvalue)
* [isSerializationEnabled](pixelsizeproperty.md#isserializationenabled)
* [name](pixelsizeproperty.md#name)
* [onGetInitialValue](pixelsizeproperty.md#optional-ongetinitialvalue)
* [sequentialNumber](pixelsizeproperty.md#sequentialnumber)
* [targetVersion](pixelsizeproperty.md#targetversion)

### Methods

* [getInternalName](pixelsizeproperty.md#getinternalname)
* [parse](pixelsizeproperty.md#parse)
* [toJSON](pixelsizeproperty.md#tojson)

## Constructors

###  constructor

\+ **new PixelSizeProperty**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): *[PixelSizeProperty](pixelsizeproperty.md)*

*Inherited from [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`defaultValue?` | any |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[PixelSizeProperty](pixelsizeproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

###  name

• **name**: *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Inherited from [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *number | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *number | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: number | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | number &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
