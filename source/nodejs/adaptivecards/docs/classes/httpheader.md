[Adaptive Cards Javascript SDK](../README.md) › [HttpHeader](httpheader.md)

# Class: HttpHeader

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **HttpHeader**

## Index

### Constructors

* [constructor](httpheader.md#constructor)

### Properties

* [maxVersion](httpheader.md#maxversion)
* [name](httpheader.md#name)
* [nameProperty](httpheader.md#static-nameproperty)
* [onRegisterCustomProperties](httpheader.md#static-optional-onregistercustomproperties)
* [valueProperty](httpheader.md#static-valueproperty)

### Accessors

* [value](httpheader.md#value)

### Methods

* [getCustomProperty](httpheader.md#getcustomproperty)
* [getReferencedInputs](httpheader.md#getreferencedinputs)
* [getSchema](httpheader.md#getschema)
* [getSchemaKey](httpheader.md#protected-getschemakey)
* [getValue](httpheader.md#protected-getvalue)
* [hasAllDefaultValues](httpheader.md#hasalldefaultvalues)
* [hasDefaultValue](httpheader.md#hasdefaultvalue)
* [internalParse](httpheader.md#protected-internalparse)
* [internalToJSON](httpheader.md#protected-internaltojson)
* [parse](httpheader.md#parse)
* [populateSchema](httpheader.md#protected-populateschema)
* [prepareForExecution](httpheader.md#prepareforexecution)
* [resetDefaultValues](httpheader.md#resetdefaultvalues)
* [setCustomProperty](httpheader.md#setcustomproperty)
* [setValue](httpheader.md#protected-setvalue)
* [shouldSerialize](httpheader.md#protected-shouldserialize)
* [toJSON](httpheader.md#tojson)

## Constructors

###  constructor

\+ **new HttpHeader**(`name`: string, `value`: string): *[HttpHeader](httpheader.md)*

*Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | "" |
`value` | string | "" |

**Returns:** *[HttpHeader](httpheader.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

The maximum Adaptive Card schema version supported by serializable objects.

___

###  name

• **name**: *string*

___

### `Static` nameProperty

▪ **nameProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "name")

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

This static event allows consuming applications to register to register custom properties to a `SerializableObject` schema.
Note that while this event technically allows properties to be removed from a schema, it is not recommended to do so.

___

### `Static` valueProperty

▪ **valueProperty**: *StringWithSubstitutionProperty‹›* = new StringWithSubstitutionProperty(Versions.v1_0, "value")

## Accessors

###  value

• **get value**(): *string | undefined*

**Returns:** *string | undefined*

• **set value**(`newValue`: string | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`newValue` | string &#124; undefined |

**Returns:** *void*

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

###  getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [Input](input.md)[], `referencedInputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Input](input.md)[] |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› |

**Returns:** *void*

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

###  prepareForExecution

▸ **prepareForExecution**(`inputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› |

**Returns:** *void*

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
