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

*Defined in [card-elements.ts:2027](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2027)*

**Parameters:**

Name | Type |
------ | ------ |
`url?` | undefined &#124; string |
`mimeType?` | undefined &#124; string |

**Returns:** *[MediaSource](mediasource.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

___

### `Optional` mimeType

• **mimeType**? : *undefined | string*

*Defined in [card-elements.ts:2018](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2018)*

___

### `Optional` url

• **url**? : *undefined | string*

*Defined in [card-elements.ts:2021](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2021)*

___

### `Static` mimeTypeProperty

▪ **mimeTypeProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "mimeType")

*Defined in [card-elements.ts:2014](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2014)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

*Defined in [serialization.ts:729](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L729)*

___

### `Static` urlProperty

▪ **urlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "url")

*Defined in [card-elements.ts:2015](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2015)*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

*Defined in [serialization.ts:922](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L922)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

*Defined in [serialization.ts:926](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L926)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

*Defined in [card-elements.ts:2025](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2025)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

*Defined in [serialization.ts:776](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L776)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

*Defined in [serialization.ts:887](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L887)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

*Defined in [serialization.ts:883](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L883)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

*Defined in [serialization.ts:789](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L789)*

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

*Defined in [serialization.ts:821](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L821)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  isValid

▸ **isValid**(): *boolean*

*Defined in [card-elements.ts:2036](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2036)*

**Returns:** *boolean*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [serialization.ts:857](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L857)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

*Defined in [serialization.ts:738](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L738)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  render

▸ **render**(): *HTMLElement | undefined*

*Defined in [card-elements.ts:2040](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2040)*

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

*Defined in [serialization.ts:901](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L901)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

*Defined in [serialization.ts:911](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L911)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

*Defined in [serialization.ts:780](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L780)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

*Defined in [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L839)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

*Defined in [serialization.ts:861](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L861)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*
