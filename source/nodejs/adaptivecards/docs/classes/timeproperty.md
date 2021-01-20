[Adaptive Cards Javascript SDK](../README.md) › [TimeProperty](timeproperty.md)

# Class: TimeProperty

## Hierarchy

  ↳ [CustomProperty](customproperty.md)‹string | undefined›

  ↳ **TimeProperty**

## Index

### Constructors

* [constructor](timeproperty.md#constructor)

### Properties

* [defaultValue](timeproperty.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](timeproperty.md#isserializationenabled)
* [name](timeproperty.md#readonly-name)
* [onGetInitialValue](timeproperty.md#optional-readonly-ongetinitialvalue)
* [onParse](timeproperty.md#readonly-onparse)
* [onToJSON](timeproperty.md#readonly-ontojson)
* [sequentialNumber](timeproperty.md#readonly-sequentialnumber)
* [targetVersion](timeproperty.md#readonly-targetversion)

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

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *T*

*Inherited from [CustomProperty](customproperty.md).[defaultValue](customproperty.md#optional-readonly-defaultvalue)*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

### `Readonly` name

• **name**: *string*

*Overrides [CustomProperty](customproperty.md).[name](customproperty.md#readonly-name)*

___

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [CustomProperty](customproperty.md).[onGetInitialValue](customproperty.md#optional-readonly-ongetinitialvalue)*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)*

___

### `Readonly` onParse

• **onParse**: *function*

*Inherited from [CustomProperty](customproperty.md).[onParse](customproperty.md#readonly-onparse)*

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

### `Readonly` onToJSON

• **onToJSON**: *function*

*Inherited from [CustomProperty](customproperty.md).[onToJSON](customproperty.md#readonly-ontojson)*

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

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [CustomProperty](customproperty.md).[targetVersion](customproperty.md#readonly-targetversion)*

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
