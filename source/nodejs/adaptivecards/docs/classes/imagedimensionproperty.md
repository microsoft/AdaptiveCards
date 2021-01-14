[Adaptive Cards Javascript SDK](../README.md) › [ImageDimensionProperty](imagedimensionproperty.md)

# Class: ImageDimensionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **ImageDimensionProperty**

## Index

### Constructors

* [constructor](imagedimensionproperty.md#constructor)

### Properties

* [defaultValue](imagedimensionproperty.md#optional-readonly-defaultvalue)
* [fallbackProperty](imagedimensionproperty.md#optional-readonly-fallbackproperty)
* [internalName](imagedimensionproperty.md#readonly-internalname)
* [isSerializationEnabled](imagedimensionproperty.md#isserializationenabled)
* [name](imagedimensionproperty.md#readonly-name)
* [onGetInitialValue](imagedimensionproperty.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](imagedimensionproperty.md#readonly-sequentialnumber)
* [targetVersion](imagedimensionproperty.md#readonly-targetversion)

### Methods

* [getInternalName](imagedimensionproperty.md#getinternalname)
* [parse](imagedimensionproperty.md#parse)
* [toJSON](imagedimensionproperty.md#tojson)

## Constructors

###  constructor

\+ **new ImageDimensionProperty**(`targetVersion`: [Version](version.md), `name`: string, `internalName`: string, `fallbackProperty?`: [ValueSetProperty](valuesetproperty.md)): *[ImageDimensionProperty](imagedimensionproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`internalName` | string |
`fallbackProperty?` | [ValueSetProperty](valuesetproperty.md) |

**Returns:** *[ImageDimensionProperty](imagedimensionproperty.md)*

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

### `Optional` `Readonly` fallbackProperty

• **fallbackProperty**? : *[ValueSetProperty](valuesetproperty.md)*

___

### `Readonly` internalName

• **internalName**: *string*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

### `Readonly` name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)*

___

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)*

___

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Overrides [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

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
