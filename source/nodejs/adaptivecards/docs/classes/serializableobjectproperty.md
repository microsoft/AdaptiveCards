[Adaptive Cards Javascript SDK](../README.md) › [SerializableObjectProperty](serializableobjectproperty.md)

# Class: SerializableObjectProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **SerializableObjectProperty**

## Index

### Constructors

* [constructor](serializableobjectproperty.md#constructor)

### Properties

* [defaultValue](serializableobjectproperty.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](serializableobjectproperty.md#isserializationenabled)
* [name](serializableobjectproperty.md#readonly-name)
* [objectType](serializableobjectproperty.md#readonly-objecttype)
* [onGetInitialValue](serializableobjectproperty.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](serializableobjectproperty.md#readonly-sequentialnumber)
* [targetVersion](serializableobjectproperty.md#readonly-targetversion)

### Methods

* [getInternalName](serializableobjectproperty.md#getinternalname)
* [parse](serializableobjectproperty.md#parse)
* [toJSON](serializableobjectproperty.md#tojson)

## Constructors

###  constructor

\+ **new SerializableObjectProperty**(`targetVersion`: [Version](version.md), `name`: string, `objectType`: [SerializableObjectType](../README.md#serializableobjecttype), `defaultValue?`: [SerializableObject](serializableobject.md)): *[SerializableObjectProperty](serializableobjectproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`objectType` | [SerializableObjectType](../README.md#serializableobjecttype) |
`defaultValue?` | [SerializableObject](serializableobject.md) |

**Returns:** *[SerializableObjectProperty](serializableobjectproperty.md)*

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

### `Readonly` name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)*

___

### `Readonly` objectType

• **objectType**: *[SerializableObjectType](../README.md#serializableobjecttype)*

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

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *[SerializableObject](serializableobject.md) | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[SerializableObject](serializableobject.md) | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [SerializableObject](serializableobject.md) | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [SerializableObject](serializableobject.md) &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
