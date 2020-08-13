[Adaptive Cards Javascript SDK](../README.md) › [TimeProperty](timeproperty.md)

# Class: TimeProperty

## Hierarchy

  ↳ [CustomProperty](customproperty.md)‹string | undefined›

  ↳ **TimeProperty**

## Index

### Constructors

* [constructor](timeproperty.md#constructor)

### Properties

* [defaultValue](timeproperty.md#optional-defaultvalue)
* [isSerializationEnabled](timeproperty.md#isserializationenabled)
* [name](timeproperty.md#name)
* [onGetInitialValue](timeproperty.md#optional-ongetinitialvalue)
* [onParse](timeproperty.md#onparse)
* [onToJSON](timeproperty.md#ontojson)
* [sequentialNumber](timeproperty.md#sequentialnumber)
* [targetVersion](timeproperty.md#targetversion)

### Methods

* [getInternalName](timeproperty.md#getinternalname)
* [parse](timeproperty.md#parse)
* [toJSON](timeproperty.md#tojson)

## Constructors

###  constructor

\+ **new TimeProperty**(`targetVersion`: [Version](version.md), `name`: string): *[TimeProperty](timeproperty.md)*

*Overrides [CustomProperty](customproperty.md).[constructor](customproperty.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |

**Returns:** *[TimeProperty](timeproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *T*

*Inherited from [CustomProperty](customproperty.md).[defaultValue](customproperty.md#optional-defaultvalue)*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

###  name

• **name**: *string*

*Overrides [CustomProperty](customproperty.md).[name](customproperty.md#name)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [CustomProperty](customproperty.md).[onGetInitialValue](customproperty.md#optional-ongetinitialvalue)*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

___

###  onParse

• **onParse**: *function*

*Inherited from [CustomProperty](customproperty.md).[onParse](customproperty.md#onparse)*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  onToJSON

• **onToJSON**: *function*

*Inherited from [CustomProperty](customproperty.md).[onToJSON](customproperty.md#ontojson)*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [CustomProperty](customproperty.md).[targetVersion](customproperty.md#targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string | undefined*

*Inherited from [CustomProperty](customproperty.md).[parse](customproperty.md#parse)*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *string | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [CustomProperty](customproperty.md).[toJSON](customproperty.md#tojson)*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
