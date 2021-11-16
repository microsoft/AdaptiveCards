[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / SubmitAction

# Class: SubmitAction

[card-elements](../modules/card_elements.md).SubmitAction

## Hierarchy

- [_Action_](card_elements.action.md)

  ↳ **SubmitAction**

## Table of contents

### Constructors

- [constructor](card_elements.submitaction.md#constructor)

### Properties

- [\_parent](card_elements.submitaction.md#_parent)
- [\_renderedElement](card_elements.submitaction.md#_renderedelement)
- [accessibleTitle](card_elements.submitaction.md#accessibletitle)
- [associatedInputs](card_elements.submitaction.md#associatedinputs)
- [expanded](card_elements.submitaction.md#expanded)
- [iconUrl](card_elements.submitaction.md#iconurl)
- [id](card_elements.submitaction.md#id)
- [maxVersion](card_elements.submitaction.md#maxversion)
- [onExecute](card_elements.submitaction.md#onexecute)
- [onPreProcessPropertyValue](card_elements.submitaction.md#onpreprocesspropertyvalue)
- [style](card_elements.submitaction.md#style)
- [title](card_elements.submitaction.md#title)
- [JsonTypeName](card_elements.submitaction.md#jsontypename)
- [associatedInputsProperty](card_elements.submitaction.md#associatedinputsproperty)
- [dataProperty](card_elements.submitaction.md#dataproperty)
- [defaultMaxVersion](card_elements.submitaction.md#defaultmaxversion)
- [iconUrlProperty](card_elements.submitaction.md#iconurlproperty)
- [idProperty](card_elements.submitaction.md#idproperty)
- [onRegisterCustomProperties](card_elements.submitaction.md#onregistercustomproperties)
- [requiresProperty](card_elements.submitaction.md#requiresproperty)
- [styleProperty](card_elements.submitaction.md#styleproperty)
- [titleProperty](card_elements.submitaction.md#titleproperty)
- [typeNameProperty](card_elements.submitaction.md#typenameproperty)

### Accessors

- [data](card_elements.submitaction.md#data)
- [hostConfig](card_elements.submitaction.md#hostconfig)
- [isPrimary](card_elements.submitaction.md#isprimary)
- [parent](card_elements.submitaction.md#parent)
- [renderedElement](card_elements.submitaction.md#renderedelement)
- [requires](card_elements.submitaction.md#requires)

### Methods

- [addCssClasses](card_elements.submitaction.md#addcssclasses)
- [execute](card_elements.submitaction.md#execute)
- [getActionById](card_elements.submitaction.md#getactionbyid)
- [getAllInputs](card_elements.submitaction.md#getallinputs)
- [getAriaRole](card_elements.submitaction.md#getariarole)
- [getCustomProperty](card_elements.submitaction.md#getcustomproperty)
- [getDefaultSerializationContext](card_elements.submitaction.md#getdefaultserializationcontext)
- [getHref](card_elements.submitaction.md#gethref)
- [getJsonTypeName](card_elements.submitaction.md#getjsontypename)
- [getReferencedInputs](card_elements.submitaction.md#getreferencedinputs)
- [getResourceInformation](card_elements.submitaction.md#getresourceinformation)
- [getRootObject](card_elements.submitaction.md#getrootobject)
- [getSchema](card_elements.submitaction.md#getschema)
- [getSchemaKey](card_elements.submitaction.md#getschemakey)
- [getValue](card_elements.submitaction.md#getvalue)
- [hasAllDefaultValues](card_elements.submitaction.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.submitaction.md#hasdefaultvalue)
- [internalGetReferencedInputs](card_elements.submitaction.md#internalgetreferencedinputs)
- [internalParse](card_elements.submitaction.md#internalparse)
- [internalPrepareForExecution](card_elements.submitaction.md#internalprepareforexecution)
- [internalToJSON](card_elements.submitaction.md#internaltojson)
- [internalValidateInputs](card_elements.submitaction.md#internalvalidateinputs)
- [internalValidateProperties](card_elements.submitaction.md#internalvalidateproperties)
- [parse](card_elements.submitaction.md#parse)
- [populateSchema](card_elements.submitaction.md#populateschema)
- [preProcessPropertyValue](card_elements.submitaction.md#preprocesspropertyvalue)
- [prepareForExecution](card_elements.submitaction.md#prepareforexecution)
- [raiseExecuteActionEvent](card_elements.submitaction.md#raiseexecuteactionevent)
- [remove](card_elements.submitaction.md#remove)
- [render](card_elements.submitaction.md#render)
- [resetDefaultValues](card_elements.submitaction.md#resetdefaultvalues)
- [setCustomProperty](card_elements.submitaction.md#setcustomproperty)
- [setParent](card_elements.submitaction.md#setparent)
- [setShouldFallback](card_elements.submitaction.md#setshouldfallback)
- [setValue](card_elements.submitaction.md#setvalue)
- [shouldFallback](card_elements.submitaction.md#shouldfallback)
- [shouldSerialize](card_elements.submitaction.md#shouldserialize)
- [toJSON](card_elements.submitaction.md#tojson)
- [updateActionButtonCssStyle](card_elements.submitaction.md#updateactionbuttoncssstyle)
- [validateInputs](card_elements.submitaction.md#validateinputs)
- [validateProperties](card_elements.submitaction.md#validateproperties)

## Constructors

### constructor

\+ **new SubmitAction**(): [_SubmitAction_](card_elements.submitaction.md)

**Returns:** [_SubmitAction_](card_elements.submitaction.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: _undefined_ \| [_CardObject_](card_object.cardobject.md)

Inherited from: [Action](card_elements.action.md).[\_parent](card_elements.action.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

---

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: _undefined_ \| HTMLElement

Inherited from: [Action](card_elements.action.md).[\_renderedElement](card_elements.action.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

---

### accessibleTitle

• `Optional` **accessibleTitle**: _undefined_ \| _string_

Inherited from: [Action](card_elements.action.md).[accessibleTitle](card_elements.action.md#accessibletitle)

Defined in: [card-elements.ts:3789](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3789)

---

### associatedInputs

• `Optional` **associatedInputs**: _undefined_ \| _auto_ \| _none_

Defined in: [card-elements.ts:3989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3989)

---

### expanded

• `Optional` **expanded**: _undefined_ \| _boolean_

Inherited from: [Action](card_elements.action.md).[expanded](card_elements.action.md#expanded)

Defined in: [card-elements.ts:3790](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3790)

---

### iconUrl

• `Optional` **iconUrl**: _undefined_ \| _string_

Inherited from: [Action](card_elements.action.md).[iconUrl](card_elements.action.md#iconurl)

Defined in: [card-elements.ts:3736](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3736)

---

### id

• `Optional` **id**: _undefined_ \| _string_

Inherited from: [Action](card_elements.action.md).[id](card_elements.action.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

---

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [Action](card_elements.action.md).[maxVersion](card_elements.action.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### onExecute

• **onExecute**: (`sender`: [_Action_](card_elements.action.md)) => _void_

#### Type declaration:

▸ (`sender`: [_Action_](card_elements.action.md)): _void_

#### Parameters:

| Name     | Type                                |
| :------- | :---------------------------------- |
| `sender` | [_Action_](card_elements.action.md) |

**Returns:** _void_

Defined in: [card-elements.ts:3792](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3792)

Inherited from: [Action](card_elements.action.md).[onExecute](card_elements.action.md#onexecute)

Defined in: [card-elements.ts:3792](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3792)

---

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: _undefined_ \| (`sender`: [_CardObject_](card_object.cardobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_) => _any_

Inherited from: [Action](card_elements.action.md).[onPreProcessPropertyValue](card_elements.action.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

---

### style

• **style**: _string_

Inherited from: [Action](card_elements.action.md).[style](card_elements.action.md#style)

Defined in: [card-elements.ts:3739](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3739)

---

### title

• `Optional` **title**: _undefined_ \| _string_

Inherited from: [Action](card_elements.action.md).[title](card_elements.action.md#title)

Defined in: [card-elements.ts:3733](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3733)

---

### JsonTypeName

▪ `Readonly` `Static` **JsonTypeName**: _Action.Submit_= "Action.Submit"

Defined in: [card-elements.ts:3995](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3995)

---

### associatedInputsProperty

▪ `Readonly` `Static` **associatedInputsProperty**: [_CustomProperty_](serialization.customproperty.md)<undefined \| string\>

Defined in: [card-elements.ts:3969](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3969)

---

### dataProperty

▪ `Readonly` `Static` **dataProperty**: [_PropertyDefinition_](serialization.propertydefinition.md)

Defined in: [card-elements.ts:3968](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3968)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [Action](card_elements.action.md).[defaultMaxVersion](card_elements.action.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### iconUrlProperty

▪ `Readonly` `Static` **iconUrlProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[iconUrlProperty](card_elements.action.md#iconurlproperty)

Defined in: [card-elements.ts:3721](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3721)

---

### idProperty

▪ `Readonly` `Static` **idProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[idProperty](card_elements.action.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [Action](card_elements.action.md).[onRegisterCustomProperties](card_elements.action.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

Inherited from: [Action](card_elements.action.md).[requiresProperty](card_elements.action.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

---

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [_ValueSetProperty_](serialization.valuesetproperty.md)

Inherited from: [Action](card_elements.action.md).[styleProperty](card_elements.action.md#styleproperty)

Defined in: [card-elements.ts:3722](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3722)

---

### titleProperty

▪ `Readonly` `Static` **titleProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[titleProperty](card_elements.action.md#titleproperty)

Defined in: [card-elements.ts:3720](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3720)

---

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[typeNameProperty](card_elements.action.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

## Accessors

### data

• get **data**(): _undefined_ \| _object_

**Returns:** _undefined_ \| _object_

Defined in: [card-elements.ts:4048](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4048)

• set **data**(`value`: _undefined_ \| _object_): _void_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `value` | _undefined_ \| _object_ |

**Returns:** _void_

Defined in: [card-elements.ts:4052](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4052)

---

### hostConfig

• get **hostConfig**(): [_HostConfig_](host_config.hostconfig.md)

**Returns:** [_HostConfig_](host_config.hostconfig.md)

Defined in: [card-elements.ts:3956](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3956)

---

### isPrimary

• get **isPrimary**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:3941](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3941)

• set **isPrimary**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Defined in: [card-elements.ts:3945](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3945)

---

### parent

• get **parent**(): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Defined in: [card-elements.ts:3960](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3960)

---

### renderedElement

• get **renderedElement**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Defined in: [card-object.ts:143](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L143)

---

### requires

• get **requires**(): [_HostCapabilities_](host_capabilities.hostcapabilities.md)

**Returns:** [_HostCapabilities_](host_capabilities.hostcapabilities.md)

Defined in: [card-object.ts:56](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L56)

## Methods

### addCssClasses

▸ `Protected`**addCssClasses**(`element`: HTMLElement): _void_

#### Parameters:

| Name      | Type        |
| :-------- | :---------- |
| `element` | HTMLElement |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3749](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3749)

---

### execute

▸ **execute**(): _void_

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3885](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3885)

---

### getActionById

▸ **getActionById**(`id`: _string_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3924](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3924)

---

### getAllInputs

▸ **getAllInputs**(`processActions?`: _boolean_): [_Input_](card_elements.input.md)[]

#### Parameters:

| Name             | Type      | Default value |
| :--------------- | :-------- | :------------ |
| `processActions` | _boolean_ | true          |

**Returns:** [_Input_](card_elements.input.md)[]

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3916)

---

### getAriaRole

▸ **getAriaRole**(): _string_

**Returns:** _string_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3798](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3798)

---

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3745](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3745)

---

### getHref

▸ **getHref**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3794](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3794)

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

**Returns:** _string_

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4044](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4044)

---

### getReferencedInputs

▸ **getReferencedInputs**(): _undefined_ \| [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>

**Returns:** _undefined_ \| [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3928](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3928)

---

### getResourceInformation

▸ **getResourceInformation**(): [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3920](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3920)

---

### getRootObject

▸ **getRootObject**(): [_CardObject_](card_object.cardobject.md)

**Returns:** [_CardObject_](card_object.cardobject.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected`**getSchemaKey**(): _string_

**Returns:** _string_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### internalGetReferencedInputs

▸ `Protected`**internalGetReferencedInputs**(): [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>

**Returns:** [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4000](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4000)

---

### internalParse

▸ `Protected`**internalParse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

---

### internalPrepareForExecution

▸ `Protected`**internalPrepareForExecution**(`inputs`: _undefined_ \| [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>): _void_

#### Parameters:

| Name     | Type                                                                                               |
| :------- | :------------------------------------------------------------------------------------------------- |
| `inputs` | _undefined_ \| [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\> |

**Returns:** _void_

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4023](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4023)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

---

### internalValidateInputs

▸ `Protected`**internalValidateInputs**(`referencedInputs`: _undefined_ \| [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\>): [_Input_](card_elements.input.md)[]

#### Parameters:

| Name               | Type                                                                                               |
| :----------------- | :------------------------------------------------------------------------------------------------- |
| `referencedInputs` | _undefined_ \| [_Dictionary_](../modules/shared.md#dictionary)<[_Input_](card_elements.input.md)\> |

**Returns:** [_Input_](card_elements.input.md)[]

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3761](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3761)

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [_ValidationResults_](card_object.validationresults.md)): _void_

#### Parameters:

| Name      | Type                                                    |
| :-------- | :------------------------------------------------------ |
| `context` | [_ValidationResults_](card_object.validationresults.md) |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L113)

---

### parse

▸ **parse**(`source`: _any_, `context?`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                            |
| :--------- | :-------------------------------------------------------------- |
| `source`   | _any_                                                           |
| `context?` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3806](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3806)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `propertyValue?`: _any_): _any_

#### Parameters:

| Name             | Type                                                        |
| :--------------- | :---------------------------------------------------------- |
| `property`       | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `propertyValue?` | _any_                                                       |

**Returns:** _any_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

---

### prepareForExecution

▸ **prepareForExecution**(): _boolean_

**Returns:** _boolean_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3893](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3893)

---

### raiseExecuteActionEvent

▸ `Protected`**raiseExecuteActionEvent**(): _void_

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3781](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3781)

---

### remove

▸ **remove**(): _boolean_

**Returns:** _boolean_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3908](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3908)

---

### render

▸ **render**(`baseCssClass?`: _string_): _void_

#### Parameters:

| Name           | Type     | Default value   |
| :------------- | :------- | :-------------- |
| `baseCssClass` | _string_ | "ac-pushButton" |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3810](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3810)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

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

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setParent

▸ **setParent**(`value`: _undefined_ \| [_CardObject_](card_object.cardobject.md)): _void_

#### Parameters:

| Name    | Type                                                     |
| :------ | :------------------------------------------------------- |
| `value` | _undefined_ \| [_CardObject_](card_object.cardobject.md) |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

---

### setShouldFallback

▸ **setShouldFallback**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:95](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L95)

---

### setValue

▸ `Protected`**setValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_): _void_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `value`    | _any_                                                       |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

**Returns:** _boolean_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_SerializationContext_](card_elements.serializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _boolean_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3777](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3777)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

---

### updateActionButtonCssStyle

▸ **updateActionButtonCssStyle**(`actionButtonElement`: HTMLElement, `buttonState?`: ActionButtonState): _void_

#### Parameters:

| Name                  | Type              |
| :-------------------- | :---------------- |
| `actionButtonElement` | HTMLElement       |
| `buttonState`         | ActionButtonState |

**Returns:** _void_

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3802](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3802)

---

### validateInputs

▸ **validateInputs**(): [_Input_](card_elements.input.md)[]

Validates the inputs associated with this action.

**Returns:** [_Input_](card_elements.input.md)[]

A list of inputs that failed validation, or an empty array if no input failed validation.

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3937](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3937)

---

### validateProperties

▸ **validateProperties**(): [_ValidationResults_](card_object.validationresults.md)

**Returns:** [_ValidationResults_](card_object.validationresults.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
