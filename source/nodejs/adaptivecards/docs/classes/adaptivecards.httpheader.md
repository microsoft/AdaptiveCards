[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / HttpHeader

# Class: HttpHeader

[adaptivecards](../modules/adaptivecards.md).HttpHeader

## Hierarchy

- [_SerializableObject_](serialization.serializableobject.md)

  ↳ **HttpHeader**

## Table of contents

### Constructors

- [constructor](adaptivecards.httpheader.md#constructor)

### Properties

- [maxVersion](adaptivecards.httpheader.md#maxversion)
- [name](adaptivecards.httpheader.md#name)
- [defaultMaxVersion](adaptivecards.httpheader.md#defaultmaxversion)
- [nameProperty](adaptivecards.httpheader.md#nameproperty)
- [onRegisterCustomProperties](adaptivecards.httpheader.md#onregistercustomproperties)
- [valueProperty](adaptivecards.httpheader.md#valueproperty)

### Accessors

- [value](adaptivecards.httpheader.md#value)

### Methods

- [getCustomProperty](adaptivecards.httpheader.md#getcustomproperty)
- [getDefaultSerializationContext](adaptivecards.httpheader.md#getdefaultserializationcontext)
- [getReferencedInputs](adaptivecards.httpheader.md#getreferencedinputs)
- [getSchema](adaptivecards.httpheader.md#getschema)
- [getSchemaKey](adaptivecards.httpheader.md#getschemakey)
- [getValue](adaptivecards.httpheader.md#getvalue)
- [hasAllDefaultValues](adaptivecards.httpheader.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.httpheader.md#hasdefaultvalue)
- [internalParse](adaptivecards.httpheader.md#internalparse)
- [internalToJSON](adaptivecards.httpheader.md#internaltojson)
- [parse](adaptivecards.httpheader.md#parse)
- [populateSchema](adaptivecards.httpheader.md#populateschema)
- [prepareForExecution](adaptivecards.httpheader.md#prepareforexecution)
- [resetDefaultValues](adaptivecards.httpheader.md#resetdefaultvalues)
- [setCustomProperty](adaptivecards.httpheader.md#setcustomproperty)
- [setValue](adaptivecards.httpheader.md#setvalue)
- [shouldSerialize](adaptivecards.httpheader.md#shouldserialize)
- [toJSON](adaptivecards.httpheader.md#tojson)

## Constructors

### constructor

\+ **new HttpHeader**(`name?`: _string_, `value?`: _string_): [_HttpHeader_](card_elements.httpheader.md)

#### Parameters:

| Name    | Type     | Default value |
| :------ | :------- | :------------ |
| `name`  | _string_ | ""            |
| `value` | _string_ | ""            |

**Returns:** [_HttpHeader_](card_elements.httpheader.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [card-elements.ts:4239](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4239)

## Properties

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[maxVersion](serialization.serializableobject.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### name

• **name**: _string_

Defined in: [card-elements.ts:4236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4236)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### nameProperty

▪ `Readonly` `Static` **nameProperty**: [_StringProperty_](serialization.stringproperty.md)

Defined in: [card-elements.ts:4228](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4228)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [SerializableObject](serialization.serializableobject.md).[onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### valueProperty

▪ `Readonly` `Static` **valueProperty**: _StringWithSubstitutionProperty_

Defined in: [card-elements.ts:4229](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4229)

## Accessors

### value

• get **value**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [card-elements.ts:4258](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4258)

• set **value**(`newValue`: _undefined_ \| _string_): _void_

#### Parameters:

| Name       | Type                    |
| :--------- | :---------------------- |
| `newValue` | _undefined_ \| _string_ |

**Returns:** _void_

Defined in: [card-elements.ts:4262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4262)

## Methods

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

### getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [_Input_](card_elements.input.md)[], `referencedInputs`: [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>): _void_

#### Parameters:

| Name               | Type                                                                                |
| :----------------- | :---------------------------------------------------------------------------------- |
| `inputs`           | [_Input_](card_elements.input.md)[]                                                 |
| `referencedInputs` | [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\> |

**Returns:** _void_

Defined in: [card-elements.ts:4250](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4250)

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

Defined in: [card-elements.ts:4231](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4231)

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

▸ `Protected`**internalParse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

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

### prepareForExecution

▸ **prepareForExecution**(`inputs`: [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>): _void_

#### Parameters:

| Name     | Type                                                                                |
| :------- | :---------------------------------------------------------------------------------- |
| `inputs` | [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\> |

**Returns:** _void_

Defined in: [card-elements.ts:4254](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4254)

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
