[Adaptive Cards Javascript SDK](../README.md) › [SerializableObject](serializableobject.md)

# Class: SerializableObject

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

**Returns:** *[SerializableObject](serializableobject.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` `Abstract` getSchemaKey

▸ **getSchemaKey**(): *string*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*
