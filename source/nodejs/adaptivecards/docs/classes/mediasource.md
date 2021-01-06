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
* [mimeTypeProperty](mediasource.md#static-readonly-mimetypeproperty)
* [onRegisterCustomProperties](mediasource.md#static-optional-onregistercustomproperties)
* [urlProperty](mediasource.md#static-readonly-urlproperty)

### Methods

* [getCustomProperty](mediasource.md#getcustomproperty)
* [getDefaultSerializationContext](mediasource.md#protected-getdefaultserializationcontext)
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

*Overrides [HostCapabilities](hostcapabilities.md).[constructor](hostcapabilities.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`url?` | undefined &#124; string |
`mimeType?` | undefined &#124; string |

**Returns:** *[MediaSource](mediasource.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [HostCapabilities](hostcapabilities.md).[maxVersion](hostcapabilities.md#maxversion)*

___

### `Optional` mimeType

• **mimeType**? : *undefined | string*

___

### `Optional` url

• **url**? : *undefined | string*

___

### `Static` `Readonly` mimeTypeProperty

▪ **mimeTypeProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "mimeType")

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [HostCapabilities](hostcapabilities.md).[onRegisterCustomProperties](hostcapabilities.md#static-optional-onregistercustomproperties)*

___

### `Static` `Readonly` urlProperty

▪ **urlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "url")

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [HostCapabilities](hostcapabilities.md).[getCustomProperty](hostcapabilities.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): *[BaseSerializationContext](baseserializationcontext.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[getDefaultSerializationContext](hostcapabilities.md#protected-getdefaultserializationcontext)*

**Returns:** *[BaseSerializationContext](baseserializationcontext.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[getSchema](hostcapabilities.md#getschema)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [HostCapabilities](hostcapabilities.md).[getValue](hostcapabilities.md#protected-getvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[hasAllDefaultValues](hostcapabilities.md#hasalldefaultvalues)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[hasDefaultValue](hostcapabilities.md#hasdefaultvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  isValid

▸ **isValid**(): *boolean*

**Returns:** *boolean*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[parse](hostcapabilities.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[populateSchema](hostcapabilities.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  render

▸ **render**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[resetDefaultValues](hostcapabilities.md#resetdefaultvalues)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[setCustomProperty](hostcapabilities.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[setValue](hostcapabilities.md#protected-setvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[shouldSerialize](hostcapabilities.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [HostCapabilities](hostcapabilities.md).[toJSON](hostcapabilities.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*
