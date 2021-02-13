[Adaptive Cards Javascript SDK](../README.md) › [SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)

# Class: SerializableObjectCollectionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **SerializableObjectCollectionProperty**

## Index

### Constructors

* [constructor](serializableobjectcollectionproperty.md#constructor)

### Properties

* [defaultValue](serializableobjectcollectionproperty.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](serializableobjectcollectionproperty.md#isserializationenabled)
* [name](serializableobjectcollectionproperty.md#readonly-name)
* [objectType](serializableobjectcollectionproperty.md#readonly-objecttype)
* [onGetInitialValue](serializableobjectcollectionproperty.md#optional-readonly-ongetinitialvalue)
* [onItemAdded](serializableobjectcollectionproperty.md#optional-readonly-onitemadded)
* [sequentialNumber](serializableobjectcollectionproperty.md#readonly-sequentialnumber)
* [targetVersion](serializableobjectcollectionproperty.md#readonly-targetversion)

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

### `Optional` `Readonly` onItemAdded

• **onItemAdded**? : *undefined | function*

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
