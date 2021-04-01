[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / MediaSource

# Class: MediaSource

[adaptivecards](../modules/adaptivecards.md).MediaSource

## Hierarchy

* [*SerializableObject*](serialization.serializableobject.md)

  ↳ **MediaSource**

## Table of contents

### Constructors

- [constructor](adaptivecards.mediasource.md#constructor)

### Properties

- [maxVersion](adaptivecards.mediasource.md#maxversion)
- [mimeType](adaptivecards.mediasource.md#mimetype)
- [url](adaptivecards.mediasource.md#url)
- [defaultMaxVersion](adaptivecards.mediasource.md#defaultmaxversion)
- [mimeTypeProperty](adaptivecards.mediasource.md#mimetypeproperty)
- [onRegisterCustomProperties](adaptivecards.mediasource.md#onregistercustomproperties)
- [urlProperty](adaptivecards.mediasource.md#urlproperty)

### Methods

- [getCustomProperty](adaptivecards.mediasource.md#getcustomproperty)
- [getDefaultSerializationContext](adaptivecards.mediasource.md#getdefaultserializationcontext)
- [getSchema](adaptivecards.mediasource.md#getschema)
- [getSchemaKey](adaptivecards.mediasource.md#getschemakey)
- [getValue](adaptivecards.mediasource.md#getvalue)
- [hasAllDefaultValues](adaptivecards.mediasource.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.mediasource.md#hasdefaultvalue)
- [internalParse](adaptivecards.mediasource.md#internalparse)
- [internalToJSON](adaptivecards.mediasource.md#internaltojson)
- [isValid](adaptivecards.mediasource.md#isvalid)
- [parse](adaptivecards.mediasource.md#parse)
- [populateSchema](adaptivecards.mediasource.md#populateschema)
- [render](adaptivecards.mediasource.md#render)
- [resetDefaultValues](adaptivecards.mediasource.md#resetdefaultvalues)
- [setCustomProperty](adaptivecards.mediasource.md#setcustomproperty)
- [setValue](adaptivecards.mediasource.md#setvalue)
- [shouldSerialize](adaptivecards.mediasource.md#shouldserialize)
- [toJSON](adaptivecards.mediasource.md#tojson)

## Constructors

### constructor

\+ **new MediaSource**(`url?`: *string*, `mimeType?`: *string*): [*MediaSource*](card_elements.mediasource.md)

#### Parameters:

Name | Type |
:------ | :------ |
`url?` | *string* |
`mimeType?` | *string* |

**Returns:** [*MediaSource*](card_elements.mediasource.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [card-elements.ts:2143](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2143)

## Properties

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[maxVersion](serialization.serializableobject.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### mimeType

• `Optional` **mimeType**: *undefined* \| *string*

Defined in: [card-elements.ts:2134](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2134)

___

### url

• `Optional` **url**: *undefined* \| *string*

Defined in: [card-elements.ts:2137](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2137)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### mimeTypeProperty

▪ `Readonly` `Static` **mimeTypeProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:2130](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2130)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [SerializableObject](serialization.serializableobject.md).[onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### urlProperty

▪ `Readonly` `Static` **urlProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:2131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2131)

## Methods

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:784](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L784)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [card-elements.ts:2141](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2141)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### internalParse

▸ `Protected`**internalParse**(`source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

___

### isValid

▸ **isValid**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:2152](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2152)

___

### parse

▸ **parse**(`source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:912](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L912)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

___

### render

▸ **render**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Defined in: [card-elements.ts:2156](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2156)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### setCustomProperty

▸ **setCustomProperty**(`name`: *string*, `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`value` | *any* |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setValue

▸ `Protected`**setValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`value` | *any* |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *boolean*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L894)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)
