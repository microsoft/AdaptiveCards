[Adaptive Cards Javascript SDK](../README.md) › [SerializableObject](serializableobject.md)

# Class: SerializableObject

The base class for any object than can serialize/deserialize itself.

## Hierarchy

* **SerializableObject**

  ↳ [CardObject](cardobject.md)

  ↳ [Fact](fact.md)

  ↳ [MediaSource](mediasource.md)

  ↳ [Choice](choice.md)

  ↳ [HttpHeader](httpheader.md)

  ↳ [BackgroundImage](backgroundimage.md)

## Index

### Constructors

* [constructor](serializableobject.md#constructor)

### Properties

* [maxVersion](serializableobject.md#maxversion)
* [onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)

### Methods

* [getCustomProperty](serializableobject.md#getcustomproperty)
* [getSchema](serializableobject.md#getschema)
* [getSchemaKey](serializableobject.md#protected-abstract-getschemakey)
* [getValue](serializableobject.md#protected-getvalue)
* [hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)
* [hasDefaultValue](serializableobject.md#hasdefaultvalue)
* [internalParse](serializableobject.md#protected-internalparse)
* [internalToJSON](serializableobject.md#protected-internaltojson)
* [parse](serializableobject.md#parse)
* [populateSchema](serializableobject.md#protected-populateschema)
* [resetDefaultValues](serializableobject.md#resetdefaultvalues)
* [setCustomProperty](serializableobject.md#setcustomproperty)
* [setValue](serializableobject.md#protected-setvalue)
* [shouldSerialize](serializableobject.md#protected-shouldserialize)
* [toJSON](serializableobject.md#tojson)

## Constructors

###  constructor

\+ **new SerializableObject**(): *[SerializableObject](serializableobject.md)*

Initializes a new SerializableObject instance.

**Returns:** *[SerializableObject](serializableobject.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

The maximum Adaptive Card schema version supported by serializable objects.

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

This static event allows consuming applications to register to register custom properties to a `SerializableObject` schema.
Note that while this event technically allows properties to be removed from a schema, it is not recommended to do so.

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

Gets the value of a custom property.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | The custom property to get the value of. |

**Returns:** *any*

The value of the custom property.

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

Gets the schema of this serializable object.

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

The schema of this serializable object.

___

### `Protected` `Abstract` getSchemaKey

▸ **getSchemaKey**(): *string*

Get the unique schema key for this particular type of serializable object. This key is used by the SDK to index schemas for
the various serializable objects it uses.

**Returns:** *string*

The schema key for this type of serializable object.

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

Gets the value of the specified property.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to get the value of. |

**Returns:** *any*

The value of the property.

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

Determines if all the properties of this serializable object have their default values.

**Returns:** *boolean*

`true` if all the properties have their default value, `false` otherwise.

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

Determines if the specified property has its default value.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to check. |

**Returns:** *boolean*

`true` if the property has its default value, `false` otherwise.

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

Parses the source object and initializes this serializable object's properties. Descendent classes
should typically not override this method.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) | The source object to parse. |
`context` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context.  |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

Serializes this serializable object to the specified target object.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) | The target object to sets the fields of. |
`context` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context.  |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

Parses the specified source object and initializes the properties of this serializable object.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) | The source object to parse from. |
`context?` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context.  |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

Populates a schema with properties by looking up publis static fields that are of type PropertyDefinition or derived.
There is in general no need for a descendant class to override this method, unless that class uses custom schema
population logic. When overriding this method, always call `super.populateSchema(schema)`

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) | The schema instance to populate.  |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

Resets this object by reverting all its properties to their default values.

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

Allows a consuming application to set custom properties on any serializable object instance.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | The name of the custom property to set. |
`value` | any | The value of the custom property.  |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

Sets the value of a property.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to set the value of. |
`value` | any | The new value of the property.  |

**Returns:** *void*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

Indicates if this object should be serialized, given the serialization context.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context. |

**Returns:** *boolean*

`true` if this object should be serialized, `false` otherwise.

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

Serializes this serializable object into a property bag.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context. |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

A property bag representing the serialized version of this serializable object.
