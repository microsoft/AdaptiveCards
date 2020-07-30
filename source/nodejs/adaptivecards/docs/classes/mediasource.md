[Adaptive Cards Javascript SDK](../README.md) › [MediaSource](mediasource.md)

# Class: MediaSource

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **MediaSource**

## Index

### Constructors

* [constructor](mediasource.md#constructor)

### Properties

* [maxVersion](mediasource.md#maxversion)
* [mimeType](mediasource.md#optional-mimetype)
* [url](mediasource.md#optional-url)
* [mimeTypeProperty](mediasource.md#static-mimetypeproperty)
* [onRegisterCustomProperties](mediasource.md#static-optional-onregistercustomproperties)
* [urlProperty](mediasource.md#static-urlproperty)

### Methods

* [getCustomProperty](mediasource.md#getcustomproperty)
* [getSchema](mediasource.md#getschema)
* [getSchemaKey](mediasource.md#protected-getschemakey)
* [getValue](mediasource.md#protected-getvalue)
* [hasAllDefaultValues](mediasource.md#hasalldefaultvalues)
* [hasDefaultValue](mediasource.md#hasdefaultvalue)
* [internalParse](mediasource.md#protected-internalparse)
* [internalToJSON](mediasource.md#protected-internaltojson)
* [isValid](mediasource.md#isvalid)
* [parse](mediasource.md#parse)
* [populateSchema](mediasource.md#protected-populateschema)
* [render](mediasource.md#render)
* [resetDefaultValues](mediasource.md#resetdefaultvalues)
* [setCustomProperty](mediasource.md#setcustomproperty)
* [setValue](mediasource.md#protected-setvalue)
* [shouldSerialize](mediasource.md#protected-shouldserialize)
* [toJSON](mediasource.md#tojson)

## Constructors

###  constructor

\+ **new MediaSource**(`url?`: undefined | string, `mimeType?`: undefined | string): *[MediaSource](mediasource.md)*

*Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`url?` | undefined &#124; string |
`mimeType?` | undefined &#124; string |

**Returns:** *[MediaSource](mediasource.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

The maximum Adaptive Card schema version supported by serializable objects.

___

### `Optional` mimeType

• **mimeType**? : *undefined | string*

___

### `Optional` url

• **url**? : *undefined | string*

___

### `Static` mimeTypeProperty

▪ **mimeTypeProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "mimeType")

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

This static event allows consuming applications to register to register custom properties to a `SerializableObject` schema.
Note that while this event technically allows properties to be removed from a schema, it is not recommended to do so.

___

### `Static` urlProperty

▪ **urlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "url")

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

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

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

Gets the schema of this serializable object.

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

The schema of this serializable object.

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

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

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

Determines if all the properties of this serializable object have their default values.

**Returns:** *boolean*

`true` if all the properties have their default value, `false` otherwise.

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

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

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

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

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

Serializes this serializable object to the specified target object.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) | The target object to sets the fields of. |
`context` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context.  |

**Returns:** *void*

___

###  isValid

▸ **isValid**(): *boolean*

**Returns:** *boolean*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

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

*Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

Populates a schema with properties by looking up publis static fields that are of type PropertyDefinition or derived.
There is in general no need for a descendant class to override this method, unless that class uses custom schema
population logic. When overriding this method, always call `super.populateSchema(schema)`

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) | The schema instance to populate.  |

**Returns:** *void*

___

###  render

▸ **render**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

Resets this object by reverting all its properties to their default values.

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

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

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

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

*Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

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

*Inherited from [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

Serializes this serializable object into a property bag.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context. |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

A property bag representing the serialized version of this serializable object.
