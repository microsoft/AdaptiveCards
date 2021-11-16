[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ToggleVisibilityAction

# Class: ToggleVisibilityAction

[adaptivecards](../modules/adaptivecards.md).ToggleVisibilityAction

## Hierarchy

- [_Action_](card_elements.action.md)

  ↳ **ToggleVisibilityAction**

## Table of contents

### Constructors

- [constructor](adaptivecards.togglevisibilityaction.md#constructor)

### Properties

- [\_parent](adaptivecards.togglevisibilityaction.md#_parent)
- [\_renderedElement](adaptivecards.togglevisibilityaction.md#_renderedelement)
- [accessibleTitle](adaptivecards.togglevisibilityaction.md#accessibletitle)
- [expanded](adaptivecards.togglevisibilityaction.md#expanded)
- [iconUrl](adaptivecards.togglevisibilityaction.md#iconurl)
- [id](adaptivecards.togglevisibilityaction.md#id)
- [maxVersion](adaptivecards.togglevisibilityaction.md#maxversion)
- [onExecute](adaptivecards.togglevisibilityaction.md#onexecute)
- [onPreProcessPropertyValue](adaptivecards.togglevisibilityaction.md#onpreprocesspropertyvalue)
- [style](adaptivecards.togglevisibilityaction.md#style)
- [targetElements](adaptivecards.togglevisibilityaction.md#targetelements)
- [title](adaptivecards.togglevisibilityaction.md#title)
- [JsonTypeName](adaptivecards.togglevisibilityaction.md#jsontypename)
- [defaultMaxVersion](adaptivecards.togglevisibilityaction.md#defaultmaxversion)
- [iconUrlProperty](adaptivecards.togglevisibilityaction.md#iconurlproperty)
- [idProperty](adaptivecards.togglevisibilityaction.md#idproperty)
- [onRegisterCustomProperties](adaptivecards.togglevisibilityaction.md#onregistercustomproperties)
- [requiresProperty](adaptivecards.togglevisibilityaction.md#requiresproperty)
- [styleProperty](adaptivecards.togglevisibilityaction.md#styleproperty)
- [targetElementsProperty](adaptivecards.togglevisibilityaction.md#targetelementsproperty)
- [titleProperty](adaptivecards.togglevisibilityaction.md#titleproperty)
- [typeNameProperty](adaptivecards.togglevisibilityaction.md#typenameproperty)

### Accessors

- [hostConfig](adaptivecards.togglevisibilityaction.md#hostconfig)
- [isPrimary](adaptivecards.togglevisibilityaction.md#isprimary)
- [parent](adaptivecards.togglevisibilityaction.md#parent)
- [renderedElement](adaptivecards.togglevisibilityaction.md#renderedelement)
- [requires](adaptivecards.togglevisibilityaction.md#requires)

### Methods

- [addCssClasses](adaptivecards.togglevisibilityaction.md#addcssclasses)
- [addTargetElement](adaptivecards.togglevisibilityaction.md#addtargetelement)
- [execute](adaptivecards.togglevisibilityaction.md#execute)
- [getActionById](adaptivecards.togglevisibilityaction.md#getactionbyid)
- [getAllInputs](adaptivecards.togglevisibilityaction.md#getallinputs)
- [getAriaRole](adaptivecards.togglevisibilityaction.md#getariarole)
- [getCustomProperty](adaptivecards.togglevisibilityaction.md#getcustomproperty)
- [getDefaultSerializationContext](adaptivecards.togglevisibilityaction.md#getdefaultserializationcontext)
- [getHref](adaptivecards.togglevisibilityaction.md#gethref)
- [getJsonTypeName](adaptivecards.togglevisibilityaction.md#getjsontypename)
- [getReferencedInputs](adaptivecards.togglevisibilityaction.md#getreferencedinputs)
- [getResourceInformation](adaptivecards.togglevisibilityaction.md#getresourceinformation)
- [getRootObject](adaptivecards.togglevisibilityaction.md#getrootobject)
- [getSchema](adaptivecards.togglevisibilityaction.md#getschema)
- [getSchemaKey](adaptivecards.togglevisibilityaction.md#getschemakey)
- [getValue](adaptivecards.togglevisibilityaction.md#getvalue)
- [hasAllDefaultValues](adaptivecards.togglevisibilityaction.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.togglevisibilityaction.md#hasdefaultvalue)
- [internalGetReferencedInputs](adaptivecards.togglevisibilityaction.md#internalgetreferencedinputs)
- [internalParse](adaptivecards.togglevisibilityaction.md#internalparse)
- [internalPrepareForExecution](adaptivecards.togglevisibilityaction.md#internalprepareforexecution)
- [internalToJSON](adaptivecards.togglevisibilityaction.md#internaltojson)
- [internalValidateInputs](adaptivecards.togglevisibilityaction.md#internalvalidateinputs)
- [internalValidateProperties](adaptivecards.togglevisibilityaction.md#internalvalidateproperties)
- [parse](adaptivecards.togglevisibilityaction.md#parse)
- [populateSchema](adaptivecards.togglevisibilityaction.md#populateschema)
- [preProcessPropertyValue](adaptivecards.togglevisibilityaction.md#preprocesspropertyvalue)
- [prepareForExecution](adaptivecards.togglevisibilityaction.md#prepareforexecution)
- [raiseExecuteActionEvent](adaptivecards.togglevisibilityaction.md#raiseexecuteactionevent)
- [remove](adaptivecards.togglevisibilityaction.md#remove)
- [removeTargetElement](adaptivecards.togglevisibilityaction.md#removetargetelement)
- [render](adaptivecards.togglevisibilityaction.md#render)
- [resetDefaultValues](adaptivecards.togglevisibilityaction.md#resetdefaultvalues)
- [setCustomProperty](adaptivecards.togglevisibilityaction.md#setcustomproperty)
- [setParent](adaptivecards.togglevisibilityaction.md#setparent)
- [setShouldFallback](adaptivecards.togglevisibilityaction.md#setshouldfallback)
- [setValue](adaptivecards.togglevisibilityaction.md#setvalue)
- [shouldFallback](adaptivecards.togglevisibilityaction.md#shouldfallback)
- [shouldSerialize](adaptivecards.togglevisibilityaction.md#shouldserialize)
- [toJSON](adaptivecards.togglevisibilityaction.md#tojson)
- [updateActionButtonCssStyle](adaptivecards.togglevisibilityaction.md#updateactionbuttoncssstyle)
- [validateInputs](adaptivecards.togglevisibilityaction.md#validateinputs)
- [validateProperties](adaptivecards.togglevisibilityaction.md#validateproperties)

## Constructors

### constructor

\+ **new ToggleVisibilityAction**(): [_ToggleVisibilityAction_](card_elements.togglevisibilityaction.md)

**Returns:** [_ToggleVisibilityAction_](card_elements.togglevisibilityaction.md)

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

### targetElements

• **targetElements**: _object_

#### Type declaration:

Defined in: [card-elements.ts:4145](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4145)

---

### title

• `Optional` **title**: _undefined_ \| _string_

Inherited from: [Action](card_elements.action.md).[title](card_elements.action.md#title)

Defined in: [card-elements.ts:3733](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3733)

---

### JsonTypeName

▪ `Readonly` `Static` **JsonTypeName**: _Action.ToggleVisibility_= "Action.ToggleVisibility"

Defined in: [card-elements.ts:4151](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4151)

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

### targetElementsProperty

▪ `Readonly` `Static` **targetElementsProperty**: [_CustomProperty_](serialization.customproperty.md)<[_PropertyBag_](../modules/serialization.md#propertybag)\>

Defined in: [card-elements.ts:4099](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4099)

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

### addTargetElement

▸ **addTargetElement**(`elementId`: _string_, `isVisible?`: _undefined_ \| _boolean_): _void_

#### Parameters:

| Name        | Type                     |
| :---------- | :----------------------- |
| `elementId` | _string_                 |
| `isVisible` | _undefined_ \| _boolean_ |

**Returns:** _void_

Defined in: [card-elements.ts:4195](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4195)

---

### execute

▸ **execute**(): _void_

**Returns:** _void_

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4178](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4178)

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

Defined in: [card-elements.ts:4169](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4169)

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

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3753](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3753)

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

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3757](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3757)

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

### removeTargetElement

▸ **removeTargetElement**(`elementId`: _string_): _void_

#### Parameters:

| Name        | Type     |
| :---------- | :------- |
| `elementId` | _string_ |

**Returns:** _void_

Defined in: [card-elements.ts:4200](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4200)

---

### render

▸ **render**(`baseCssClass?`: _string_): _void_

#### Parameters:

| Name           | Type     | Default value   |
| :------------- | :------- | :-------------- |
| `baseCssClass` | _string_ | "ac-pushButton" |

**Returns:** _void_

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4173](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4173)

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
