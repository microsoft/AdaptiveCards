[Adaptive Cards Javascript SDK](../README.md) › [StringArrayProperty](stringarrayproperty.md)

# Class: StringArrayProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **StringArrayProperty**

## Index

### Constructors

* [constructor](stringarrayproperty.md#constructor)

### Properties

* [defaultValue](stringarrayproperty.md#optional-defaultvalue)
* [isSerializationEnabled](stringarrayproperty.md#isserializationenabled)
* [name](stringarrayproperty.md#name)
* [onGetInitialValue](stringarrayproperty.md#optional-ongetinitialvalue)
* [sequentialNumber](stringarrayproperty.md#sequentialnumber)
* [targetVersion](stringarrayproperty.md#targetversion)

### Methods

* [getInternalName](stringarrayproperty.md#getinternalname)
* [parse](stringarrayproperty.md#parse)
* [toJSON](stringarrayproperty.md#tojson)

## Constructors

###  constructor

\+ **new StringArrayProperty**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: string[], `onGetInitialValue?`: undefined | function): *[StringArrayProperty](stringarrayproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`defaultValue?` | string[] |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[StringArrayProperty](stringarrayproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *string[]*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string[] | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *string[] | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string[] | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string[] &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
