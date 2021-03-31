[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ToggleVisibilityAction

# Class: ToggleVisibilityAction

[adaptivecards](../modules/adaptivecards.md).ToggleVisibilityAction

## Hierarchy

* [*Action*](card_elements.action.md)

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

\+ **new ToggleVisibilityAction**(): [*ToggleVisibilityAction*](card_elements.togglevisibilityaction.md)

**Returns:** [*ToggleVisibilityAction*](card_elements.togglevisibilityaction.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [Action](card_elements.action.md).[_parent](card_elements.action.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [Action](card_elements.action.md).[_renderedElement](card_elements.action.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### accessibleTitle

• `Optional` **accessibleTitle**: *undefined* \| *string*

Inherited from: [Action](card_elements.action.md).[accessibleTitle](card_elements.action.md#accessibletitle)

Defined in: [card-elements.ts:3789](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3789)

___

### expanded

• `Optional` **expanded**: *undefined* \| *boolean*

Inherited from: [Action](card_elements.action.md).[expanded](card_elements.action.md#expanded)

Defined in: [card-elements.ts:3790](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3790)

___

### iconUrl

• `Optional` **iconUrl**: *undefined* \| *string*

Inherited from: [Action](card_elements.action.md).[iconUrl](card_elements.action.md#iconurl)

Defined in: [card-elements.ts:3736](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3736)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [Action](card_elements.action.md).[id](card_elements.action.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [Action](card_elements.action.md).[maxVersion](card_elements.action.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### onExecute

• **onExecute**: (`sender`: [*Action*](card_elements.action.md)) => *void*

#### Type declaration:

▸ (`sender`: [*Action*](card_elements.action.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*Action*](card_elements.action.md) |

**Returns:** *void*

Defined in: [card-elements.ts:3792](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3792)

Inherited from: [Action](card_elements.action.md).[onExecute](card_elements.action.md#onexecute)

Defined in: [card-elements.ts:3792](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3792)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [Action](card_elements.action.md).[onPreProcessPropertyValue](card_elements.action.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### style

• **style**: *string*

Inherited from: [Action](card_elements.action.md).[style](card_elements.action.md#style)

Defined in: [card-elements.ts:3739](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3739)

___

### targetElements

• **targetElements**: *object*

#### Type declaration:

Defined in: [card-elements.ts:4145](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4145)

___

### title

• `Optional` **title**: *undefined* \| *string*

Inherited from: [Action](card_elements.action.md).[title](card_elements.action.md#title)

Defined in: [card-elements.ts:3733](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3733)

___

### JsonTypeName

▪ `Readonly` `Static` **JsonTypeName**: *Action.ToggleVisibility*= "Action.ToggleVisibility"

Defined in: [card-elements.ts:4151](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4151)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [Action](card_elements.action.md).[defaultMaxVersion](card_elements.action.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### iconUrlProperty

▪ `Readonly` `Static` **iconUrlProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[iconUrlProperty](card_elements.action.md#iconurlproperty)

Defined in: [card-elements.ts:3721](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3721)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[idProperty](card_elements.action.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [Action](card_elements.action.md).[onRegisterCustomProperties](card_elements.action.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [Action](card_elements.action.md).[requiresProperty](card_elements.action.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [Action](card_elements.action.md).[styleProperty](card_elements.action.md#styleproperty)

Defined in: [card-elements.ts:3722](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3722)

___

### targetElementsProperty

▪ `Readonly` `Static` **targetElementsProperty**: [*CustomProperty*](serialization.customproperty.md)<[*PropertyBag*](../modules/serialization.md#propertybag)\>

Defined in: [card-elements.ts:4099](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4099)

___

### titleProperty

▪ `Readonly` `Static` **titleProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[titleProperty](card_elements.action.md#titleproperty)

Defined in: [card-elements.ts:3720](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3720)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Action](card_elements.action.md).[typeNameProperty](card_elements.action.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

## Accessors

### hostConfig

• get **hostConfig**(): [*HostConfig*](host_config.hostconfig.md)

**Returns:** [*HostConfig*](host_config.hostconfig.md)

Defined in: [card-elements.ts:3956](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3956)

___

### isPrimary

• get **isPrimary**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:3941](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3941)

• set **isPrimary**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Defined in: [card-elements.ts:3945](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3945)

___

### parent

• get **parent**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Defined in: [card-elements.ts:3960](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3960)

___

### renderedElement

• get **renderedElement**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Defined in: [card-object.ts:143](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L143)

___

### requires

• get **requires**(): [*HostCapabilities*](host_capabilities.hostcapabilities.md)

**Returns:** [*HostCapabilities*](host_capabilities.hostcapabilities.md)

Defined in: [card-object.ts:56](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L56)

## Methods

### addCssClasses

▸ `Protected`**addCssClasses**(`element`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | HTMLElement |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3749](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3749)

___

### addTargetElement

▸ **addTargetElement**(`elementId`: *string*, `isVisible?`: *undefined* \| *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`elementId` | *string* |
`isVisible` | *undefined* \| *boolean* |

**Returns:** *void*

Defined in: [card-elements.ts:4195](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4195)

___

### execute

▸ **execute**(): *void*

**Returns:** *void*

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4178](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4178)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3924](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3924)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3916)

___

### getAriaRole

▸ **getAriaRole**(): *string*

**Returns:** *string*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3798](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3798)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3745](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3745)

___

### getHref

▸ **getHref**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3794](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3794)

___

### getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4169](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4169)

___

### getReferencedInputs

▸ **getReferencedInputs**(): *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

**Returns:** *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3928](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3928)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3920](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3920)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### internalGetReferencedInputs

▸ `Protected`**internalGetReferencedInputs**(): [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

**Returns:** [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3753](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3753)

___

### internalParse

▸ `Protected`**internalParse**(`source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

___

### internalPrepareForExecution

▸ `Protected`**internalPrepareForExecution**(`inputs`: *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`inputs` | *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\> |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3757](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3757)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

___

### internalValidateInputs

▸ `Protected`**internalValidateInputs**(`referencedInputs`: *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type |
:------ | :------ |
`referencedInputs` | *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\> |

**Returns:** [*Input*](card_elements.input.md)[]

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3761](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3761)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L113)

___

### parse

▸ **parse**(`source`: *any*, `context?`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *any* |
`context?` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3806](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3806)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

___

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `propertyValue?`: *any*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`propertyValue?` | *any* |

**Returns:** *any*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### prepareForExecution

▸ **prepareForExecution**(): *boolean*

**Returns:** *boolean*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3893](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3893)

___

### raiseExecuteActionEvent

▸ `Protected`**raiseExecuteActionEvent**(): *void*

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3781](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3781)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3908](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3908)

___

### removeTargetElement

▸ **removeTargetElement**(`elementId`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`elementId` | *string* |

**Returns:** *void*

Defined in: [card-elements.ts:4200](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4200)

___

### render

▸ **render**(`baseCssClass?`: *string*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`baseCssClass` | *string* | "ac-pushButton" |

**Returns:** *void*

Overrides: [Action](card_elements.action.md)

Defined in: [card-elements.ts:4173](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L4173)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

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

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:95](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L95)

___

### setValue

▸ `Protected`**setValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`value` | *any* |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3777](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3777)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [Action](card_elements.action.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

___

### updateActionButtonCssStyle

▸ **updateActionButtonCssStyle**(`actionButtonElement`: HTMLElement, `buttonState?`: ActionButtonState): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`actionButtonElement` | HTMLElement |
`buttonState` | ActionButtonState |

**Returns:** *void*

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3802](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3802)

___

### validateInputs

▸ **validateInputs**(): [*Input*](card_elements.input.md)[]

Validates the inputs associated with this action.

**Returns:** [*Input*](card_elements.input.md)[]

A list of inputs that failed validation, or an empty array if no input failed validation.

Inherited from: [Action](card_elements.action.md)

Defined in: [card-elements.ts:3937](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3937)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [Action](card_elements.action.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
