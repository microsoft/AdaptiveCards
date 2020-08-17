[Adaptive Cards Javascript SDK](../README.md) › [SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)

# Class: SerializableObjectCollectionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **SerializableObjectCollectionProperty**

## Index

### Constructors

* [constructor](serializableobjectcollectionproperty.md#constructor)

### Properties

* [defaultValue](serializableobjectcollectionproperty.md#optional-defaultvalue)
* [isSerializationEnabled](serializableobjectcollectionproperty.md#isserializationenabled)
* [name](serializableobjectcollectionproperty.md#name)
* [objectType](serializableobjectcollectionproperty.md#objecttype)
* [onGetInitialValue](serializableobjectcollectionproperty.md#optional-ongetinitialvalue)
* [onItemAdded](serializableobjectcollectionproperty.md#optional-onitemadded)
* [sequentialNumber](serializableobjectcollectionproperty.md#sequentialnumber)
* [targetVersion](serializableobjectcollectionproperty.md#targetversion)

### Methods

* [getInternalName](serializableobjectcollectionproperty.md#getinternalname)
* [parse](serializableobjectcollectionproperty.md#parse)
* [toJSON](serializableobjectcollectionproperty.md#tojson)

## Constructors

###  constructor

\+ **new SerializableObjectCollectionProperty**(`targetVersion`: [Version](version.md), `name`: string, `objectType`: [SerializableObjectType](../README.md#serializableobjecttype), `onItemAdded?`: undefined | function): *[SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`objectType` | [SerializableObjectType](../README.md#serializableobjecttype) |
`onItemAdded?` | undefined &#124; function |

**Returns:** *[SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)*

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

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

___

###  objectType

• **objectType**: *[SerializableObjectType](../README.md#serializableobjecttype)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

___

### `Optional` onItemAdded

• **onItemAdded**? : *undefined | function*

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

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *[SerializableObject](serializableobject.md)[] | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[SerializableObject](serializableobject.md)[] | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [SerializableObject](serializableobject.md)[] | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [SerializableObject](serializableobject.md)[] &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
