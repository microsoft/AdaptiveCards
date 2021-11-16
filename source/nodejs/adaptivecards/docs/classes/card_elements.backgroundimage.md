[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / BackgroundImage

# Class: BackgroundImage

[card-elements](../modules/card_elements.md).BackgroundImage

## Hierarchy

- [_SerializableObject_](serialization.serializableobject.md)

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

\+ **new BackgroundImage**(): [_BackgroundImage_](card_elements.backgroundimage.md)

**Returns:** [_BackgroundImage_](card_elements.backgroundimage.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### fillMode

• **fillMode**: [_FillMode_](../enums/enums.fillmode.md)

Defined in: [card-elements.ts:5245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5245)

---

### horizontalAlignment

• **horizontalAlignment**: [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)

Defined in: [card-elements.ts:5248](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5248)

---

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[maxVersion](serialization.serializableobject.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### url

• `Optional` **url**: _undefined_ \| _string_

Defined in: [card-elements.ts:5242](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5242)

---

### verticalAlignment

• **verticalAlignment**: [_VerticalAlignment_](../enums/enums.verticalalignment.md)

Defined in: [card-elements.ts:5251](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5251)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### fillModeProperty

▪ `Readonly` `Static` **fillModeProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_FillMode_](../enums/enums.fillmode.md)\>

Defined in: [card-elements.ts:5237](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5237)

---

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)\>

Defined in: [card-elements.ts:5238](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5238)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [SerializableObject](serialization.serializableobject.md).[onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### urlProperty

▪ `Readonly` `Static` **urlProperty**: [_StringProperty_](serialization.stringproperty.md)

Defined in: [card-elements.ts:5236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5236)

---

### verticalAlignmentProperty

▪ `Readonly` `Static` **verticalAlignmentProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_VerticalAlignment_](../enums/enums.verticalalignment.md)\>

Defined in: [card-elements.ts:5239](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5239)

## Methods

### apply

▸ **apply**(`element`: [_CardElement_](card_elements.cardelement.md)): _void_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _void_

Defined in: [card-elements.ts:5269](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5269)

---

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:784](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L784)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected`**getSchemaKey**(): _string_

**Returns:** _string_

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [card-elements.ts:5255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5255)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### internalParse

▸ `Protected`**internalParse**(`source`: _any_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | _any_                                                                   |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [card-elements.ts:5259](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5259)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

---

### isValid

▸ **isValid**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5310](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5310)

---

### parse

▸ **parse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `source`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:912](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L912)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

---

### setCustomProperty

▸ **setCustomProperty**(`name`: _string_, `value`: _any_): _void_

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `name`  | _string_ |
| `value` | _any_    |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setValue

▸ `Protected`**setValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_): _void_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `value`    | _any_                                                       |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _boolean_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L894)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)
