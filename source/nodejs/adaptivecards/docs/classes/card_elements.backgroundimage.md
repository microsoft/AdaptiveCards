[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / BackgroundImage

# Class: BackgroundImage

[card-elements](../modules/card_elements.md).BackgroundImage

## Hierarchy

* [*SerializableObject*](serialization.serializableobject.md)

  ↳ **BackgroundImage**

## Table of contents

### Constructors

- [constructor](card_elements.backgroundimage.md#constructor)

### Properties

- [fillMode](card_elements.backgroundimage.md#fillmode)
- [horizontalAlignment](card_elements.backgroundimage.md#horizontalalignment)
- [maxVersion](card_elements.backgroundimage.md#maxversion)
- [url](card_elements.backgroundimage.md#url)
- [verticalAlignment](card_elements.backgroundimage.md#verticalalignment)
- [defaultMaxVersion](card_elements.backgroundimage.md#defaultmaxversion)
- [fillModeProperty](card_elements.backgroundimage.md#fillmodeproperty)
- [horizontalAlignmentProperty](card_elements.backgroundimage.md#horizontalalignmentproperty)
- [onRegisterCustomProperties](card_elements.backgroundimage.md#onregistercustomproperties)
- [urlProperty](card_elements.backgroundimage.md#urlproperty)
- [verticalAlignmentProperty](card_elements.backgroundimage.md#verticalalignmentproperty)

### Methods

- [apply](card_elements.backgroundimage.md#apply)
- [getCustomProperty](card_elements.backgroundimage.md#getcustomproperty)
- [getDefaultSerializationContext](card_elements.backgroundimage.md#getdefaultserializationcontext)
- [getSchema](card_elements.backgroundimage.md#getschema)
- [getSchemaKey](card_elements.backgroundimage.md#getschemakey)
- [getValue](card_elements.backgroundimage.md#getvalue)
- [hasAllDefaultValues](card_elements.backgroundimage.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.backgroundimage.md#hasdefaultvalue)
- [internalParse](card_elements.backgroundimage.md#internalparse)
- [internalToJSON](card_elements.backgroundimage.md#internaltojson)
- [isValid](card_elements.backgroundimage.md#isvalid)
- [parse](card_elements.backgroundimage.md#parse)
- [populateSchema](card_elements.backgroundimage.md#populateschema)
- [resetDefaultValues](card_elements.backgroundimage.md#resetdefaultvalues)
- [setCustomProperty](card_elements.backgroundimage.md#setcustomproperty)
- [setValue](card_elements.backgroundimage.md#setvalue)
- [shouldSerialize](card_elements.backgroundimage.md#shouldserialize)
- [toJSON](card_elements.backgroundimage.md#tojson)

## Constructors

### constructor

\+ **new BackgroundImage**(): [*BackgroundImage*](card_elements.backgroundimage.md)

**Returns:** [*BackgroundImage*](card_elements.backgroundimage.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### fillMode

• **fillMode**: [*FillMode*](../enums/enums.fillmode.md)

Defined in: [card-elements.ts:5245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5245)

___

### horizontalAlignment

• **horizontalAlignment**: [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)

Defined in: [card-elements.ts:5248](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5248)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[maxVersion](serialization.serializableobject.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### url

• `Optional` **url**: *undefined* \| *string*

Defined in: [card-elements.ts:5242](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5242)

___

### verticalAlignment

• **verticalAlignment**: [*VerticalAlignment*](../enums/enums.verticalalignment.md)

Defined in: [card-elements.ts:5251](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5251)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### fillModeProperty

▪ `Readonly` `Static` **fillModeProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*FillMode*](../enums/enums.fillmode.md)\>

Defined in: [card-elements.ts:5237](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5237)

___

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)\>

Defined in: [card-elements.ts:5238](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5238)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [SerializableObject](serialization.serializableobject.md).[onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### urlProperty

▪ `Readonly` `Static` **urlProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:5236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5236)

___

### verticalAlignmentProperty

▪ `Readonly` `Static` **verticalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*VerticalAlignment*](../enums/enums.verticalalignment.md)\>

Defined in: [card-elements.ts:5239](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5239)

## Methods

### apply

▸ **apply**(`element`: [*CardElement*](card_elements.cardelement.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *void*

Defined in: [card-elements.ts:5269](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5269)

___

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

Defined in: [card-elements.ts:5255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5255)

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

▸ `Protected`**internalParse**(`source`: *any*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *any* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [card-elements.ts:5259](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5259)

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

Defined in: [card-elements.ts:5310](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5310)

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
