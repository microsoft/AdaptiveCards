[Adaptive Cards Javascript SDK](../README.md) › [SerializableObject](serializableobject.md)

# Class: SerializableObject

## Hierarchy

* **SerializableObject**

  ↳ [CardObject](cardobject.md)

  ↳ [Fact](fact.md)

  ↳ [MediaSource](mediasource.md)

  ↳ [InputValidationOptions](inputvalidationoptions.md)

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

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

**Returns:** *[SerializableObject](serializableobject.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Defined in [serialization.ts:729](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L729)*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Defined in [serialization.ts:922](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L922)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Defined in [serialization.ts:926](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L926)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` `Abstract` getSchemaKey

▸ **getSchemaKey**(): *string*

*Defined in [serialization.ts:736](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L736)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Defined in [serialization.ts:776](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L776)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Defined in [serialization.ts:887](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L887)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Defined in [serialization.ts:883](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L883)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

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

*Defined in [serialization.ts:821](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L821)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

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

*Defined in [serialization.ts:738](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L738)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Defined in [serialization.ts:901](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L901)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

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

*Defined in [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L839)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Defined in [serialization.ts:861](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L861)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*
