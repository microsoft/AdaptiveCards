[Adaptive Cards Javascript SDK](../README.md) › [BackgroundImage](backgroundimage.md)

# Class: BackgroundImage

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **BackgroundImage**

## Index

### Constructors

* [constructor](backgroundimage.md#constructor)

### Properties

* [fillMode](backgroundimage.md#fillmode)
* [horizontalAlignment](backgroundimage.md#horizontalalignment)
* [maxVersion](backgroundimage.md#maxversion)
* [url](backgroundimage.md#optional-url)
* [verticalAlignment](backgroundimage.md#verticalalignment)
* [fillModeProperty](backgroundimage.md#static-fillmodeproperty)
* [horizontalAlignmentProperty](backgroundimage.md#static-horizontalalignmentproperty)
* [onRegisterCustomProperties](backgroundimage.md#static-optional-onregistercustomproperties)
* [urlProperty](backgroundimage.md#static-urlproperty)
* [verticalAlignmentProperty](backgroundimage.md#static-verticalalignmentproperty)

### Methods

* [apply](backgroundimage.md#apply)
* [getCustomProperty](backgroundimage.md#getcustomproperty)
* [getSchema](backgroundimage.md#getschema)
* [getSchemaKey](backgroundimage.md#protected-getschemakey)
* [getValue](backgroundimage.md#protected-getvalue)
* [hasAllDefaultValues](backgroundimage.md#hasalldefaultvalues)
* [hasDefaultValue](backgroundimage.md#hasdefaultvalue)
* [internalParse](backgroundimage.md#protected-internalparse)
* [internalToJSON](backgroundimage.md#protected-internaltojson)
* [isValid](backgroundimage.md#isvalid)
* [parse](backgroundimage.md#parse)
* [populateSchema](backgroundimage.md#protected-populateschema)
* [resetDefaultValues](backgroundimage.md#resetdefaultvalues)
* [setCustomProperty](backgroundimage.md#setcustomproperty)
* [setValue](backgroundimage.md#protected-setvalue)
* [shouldSerialize](backgroundimage.md#protected-shouldserialize)
* [toJSON](backgroundimage.md#tojson)

## Constructors

###  constructor

\+ **new BackgroundImage**(): *[BackgroundImage](backgroundimage.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

**Returns:** *[BackgroundImage](backgroundimage.md)*

## Properties

###  fillMode

• **fillMode**: *[FillMode](../enums/fillmode.md)*

*Defined in [card-elements.ts:4796](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4796)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Defined in [card-elements.ts:4799](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4799)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

___

### `Optional` url

• **url**? : *undefined | string*

*Defined in [card-elements.ts:4793](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4793)*

___

###  verticalAlignment

• **verticalAlignment**: *[VerticalAlignment](../enums/verticalalignment.md)*

*Defined in [card-elements.ts:4802](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4802)*

___

### `Static` fillModeProperty

▪ **fillModeProperty**: *[EnumProperty](enumproperty.md)‹[FillMode](../enums/fillmode.md)›* = new EnumProperty(Versions.v1_2, "fillMode", Enums.FillMode, Enums.FillMode.Cover)

*Defined in [card-elements.ts:4788](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4788)*

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(Versions.v1_2, "horizontalAlignment", Enums.HorizontalAlignment, Enums.HorizontalAlignment.Left)

*Defined in [card-elements.ts:4789](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4789)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

*Defined in [serialization.ts:729](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L729)*

___

### `Static` urlProperty

▪ **urlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "url")

*Defined in [card-elements.ts:4787](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4787)*

___

### `Static` verticalAlignmentProperty

▪ **verticalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[VerticalAlignment](../enums/verticalalignment.md)›* = new EnumProperty(Versions.v1_2, "verticalAlignment", Enums.VerticalAlignment, Enums.VerticalAlignment.Top)

*Defined in [card-elements.ts:4790](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4790)*

## Methods

###  apply

▸ **apply**(`element`: [CardElement](cardelement.md)): *void*

*Defined in [card-elements.ts:4820](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4820)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *void*

___

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

*Defined in [card-elements.ts:4806](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4806)*

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

▸ **internalParse**(`source`: any, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

*Defined in [card-elements.ts:4810](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4810)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
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

*Defined in [card-elements.ts:4861](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4861)*

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
