[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / Action

# Class: Action

[adaptivecards](../modules/adaptivecards.md).Action

## Hierarchy

* [*CardObject*](card_object.cardobject.md)

  ↳ **Action**

## Table of contents

### Constructors

- [constructor](adaptivecards.action.md#constructor)

### Properties

- [\_parent](adaptivecards.action.md#_parent)
- [\_renderedElement](adaptivecards.action.md#_renderedelement)
- [accessibleTitle](adaptivecards.action.md#accessibletitle)
- [expanded](adaptivecards.action.md#expanded)
- [iconUrl](adaptivecards.action.md#iconurl)
- [id](adaptivecards.action.md#id)
- [maxVersion](adaptivecards.action.md#maxversion)
- [onExecute](adaptivecards.action.md#onexecute)
- [onPreProcessPropertyValue](adaptivecards.action.md#onpreprocesspropertyvalue)
- [style](adaptivecards.action.md#style)
- [title](adaptivecards.action.md#title)
- [defaultMaxVersion](adaptivecards.action.md#defaultmaxversion)
- [iconUrlProperty](adaptivecards.action.md#iconurlproperty)
- [idProperty](adaptivecards.action.md#idproperty)
- [onRegisterCustomProperties](adaptivecards.action.md#onregistercustomproperties)
- [requiresProperty](adaptivecards.action.md#requiresproperty)
- [styleProperty](adaptivecards.action.md#styleproperty)
- [titleProperty](adaptivecards.action.md#titleproperty)
- [typeNameProperty](adaptivecards.action.md#typenameproperty)

### Accessors

- [hostConfig](adaptivecards.action.md#hostconfig)
- [isPrimary](adaptivecards.action.md#isprimary)
- [parent](adaptivecards.action.md#parent)
- [renderedElement](adaptivecards.action.md#renderedelement)
- [requires](adaptivecards.action.md#requires)

### Methods

- [addCssClasses](adaptivecards.action.md#addcssclasses)
- [execute](adaptivecards.action.md#execute)
- [getActionById](adaptivecards.action.md#getactionbyid)
- [getAllInputs](adaptivecards.action.md#getallinputs)
- [getAriaRole](adaptivecards.action.md#getariarole)
- [getCustomProperty](adaptivecards.action.md#getcustomproperty)
- [getDefaultSerializationContext](adaptivecards.action.md#getdefaultserializationcontext)
- [getHref](adaptivecards.action.md#gethref)
- [getJsonTypeName](adaptivecards.action.md#getjsontypename)
- [getReferencedInputs](adaptivecards.action.md#getreferencedinputs)
- [getResourceInformation](adaptivecards.action.md#getresourceinformation)
- [getRootObject](adaptivecards.action.md#getrootobject)
- [getSchema](adaptivecards.action.md#getschema)
- [getSchemaKey](adaptivecards.action.md#getschemakey)
- [getValue](adaptivecards.action.md#getvalue)
- [hasAllDefaultValues](adaptivecards.action.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.action.md#hasdefaultvalue)
- [internalGetReferencedInputs](adaptivecards.action.md#internalgetreferencedinputs)
- [internalParse](adaptivecards.action.md#internalparse)
- [internalPrepareForExecution](adaptivecards.action.md#internalprepareforexecution)
- [internalToJSON](adaptivecards.action.md#internaltojson)
- [internalValidateInputs](adaptivecards.action.md#internalvalidateinputs)
- [internalValidateProperties](adaptivecards.action.md#internalvalidateproperties)
- [parse](adaptivecards.action.md#parse)
- [populateSchema](adaptivecards.action.md#populateschema)
- [preProcessPropertyValue](adaptivecards.action.md#preprocesspropertyvalue)
- [prepareForExecution](adaptivecards.action.md#prepareforexecution)
- [raiseExecuteActionEvent](adaptivecards.action.md#raiseexecuteactionevent)
- [remove](adaptivecards.action.md#remove)
- [render](adaptivecards.action.md#render)
- [resetDefaultValues](adaptivecards.action.md#resetdefaultvalues)
- [setCustomProperty](adaptivecards.action.md#setcustomproperty)
- [setParent](adaptivecards.action.md#setparent)
- [setShouldFallback](adaptivecards.action.md#setshouldfallback)
- [setValue](adaptivecards.action.md#setvalue)
- [shouldFallback](adaptivecards.action.md#shouldfallback)
- [shouldSerialize](adaptivecards.action.md#shouldserialize)
- [toJSON](adaptivecards.action.md#tojson)
- [updateActionButtonCssStyle](adaptivecards.action.md#updateactionbuttoncssstyle)
- [validateInputs](adaptivecards.action.md#validateinputs)
- [validateProperties](adaptivecards.action.md#validateproperties)

## Constructors

### constructor

\+ **new Action**(): [*Action*](card_elements.action.md)

**Returns:** [*Action*](card_elements.action.md)

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [CardObject](card_object.cardobject.md).[_parent](card_object.cardobject.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [CardObject](card_object.cardobject.md).[_renderedElement](card_object.cardobject.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### accessibleTitle

• `Optional` **accessibleTitle**: *undefined* \| *string*

Defined in: [card-elements.ts:3789](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3789)

___

### expanded

• `Optional` **expanded**: *undefined* \| *boolean*

Defined in: [card-elements.ts:3790](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3790)

___

### iconUrl

• `Optional` **iconUrl**: *undefined* \| *string*

Defined in: [card-elements.ts:3736](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3736)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [CardObject](card_object.cardobject.md).[id](card_object.cardobject.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [CardObject](card_object.cardobject.md).[maxVersion](card_object.cardobject.md#maxversion)

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

Defined in: [card-elements.ts:3792](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3792)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [CardObject](card_object.cardobject.md).[onPreProcessPropertyValue](card_object.cardobject.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### style

• **style**: *string*

Defined in: [card-elements.ts:3739](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3739)

___

### title

• `Optional` **title**: *undefined* \| *string*

Defined in: [card-elements.ts:3733](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3733)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [CardObject](card_object.cardobject.md).[defaultMaxVersion](card_object.cardobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### iconUrlProperty

▪ `Readonly` `Static` **iconUrlProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:3721](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3721)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [CardObject](card_object.cardobject.md).[idProperty](card_object.cardobject.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [CardObject](card_object.cardobject.md).[onRegisterCustomProperties](card_object.cardobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [CardObject](card_object.cardobject.md).[requiresProperty](card_object.cardobject.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Defined in: [card-elements.ts:3722](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3722)

___

### titleProperty

▪ `Readonly` `Static` **titleProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:3720](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3720)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [CardObject](card_object.cardobject.md).[typeNameProperty](card_object.cardobject.md#typenameproperty)

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

Defined in: [card-elements.ts:3749](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3749)

___

### execute

▸ **execute**(): *void*

**Returns:** *void*

Defined in: [card-elements.ts:3885](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3885)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Defined in: [card-elements.ts:3924](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3924)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Defined in: [card-elements.ts:3916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3916)

___

### getAriaRole

▸ **getAriaRole**(): *string*

**Returns:** *string*

Defined in: [card-elements.ts:3798](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3798)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Overrides: [CardObject](card_object.cardobject.md)

Defined in: [card-elements.ts:3745](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3745)

___

### getHref

▸ **getHref**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [card-elements.ts:3794](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3794)

___

### getJsonTypeName

▸ `Abstract`**getJsonTypeName**(): *string*

**Returns:** *string*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:69](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L69)

___

### getReferencedInputs

▸ **getReferencedInputs**(): *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

**Returns:** *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

Defined in: [card-elements.ts:3928](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3928)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Defined in: [card-elements.ts:3920](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3920)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### internalGetReferencedInputs

▸ `Protected`**internalGetReferencedInputs**(): [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

**Returns:** [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>

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

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

___

### internalPrepareForExecution

▸ `Protected`**internalPrepareForExecution**(`inputs`: *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`inputs` | *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\> |

**Returns:** *void*

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

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

___

### internalValidateInputs

▸ `Protected`**internalValidateInputs**(`referencedInputs`: *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\>): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type |
:------ | :------ |
`referencedInputs` | *undefined* \| [*Dictionary*](../modules/shared.md#dictionary)<[*Input*](card_elements.input.md)\> |

**Returns:** [*Input*](card_elements.input.md)[]

Defined in: [card-elements.ts:3761](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3761)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Inherited from: [CardObject](card_object.cardobject.md)

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

Overrides: [CardObject](card_object.cardobject.md)

Defined in: [card-elements.ts:3806](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3806)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [CardObject](card_object.cardobject.md)

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

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### prepareForExecution

▸ **prepareForExecution**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:3893](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3893)

___

### raiseExecuteActionEvent

▸ `Protected`**raiseExecuteActionEvent**(): *void*

**Returns:** *void*

Defined in: [card-elements.ts:3781](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3781)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:3908](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3908)

___

### render

▸ **render**(`baseCssClass?`: *string*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`baseCssClass` | *string* | "ac-pushButton" |

**Returns:** *void*

Defined in: [card-elements.ts:3810](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3810)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [CardObject](card_object.cardobject.md)

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

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [CardObject](card_object.cardobject.md)

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

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Overrides: [CardObject](card_object.cardobject.md)

Defined in: [card-elements.ts:3777](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3777)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [CardObject](card_object.cardobject.md)

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

Defined in: [card-elements.ts:3802](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3802)

___

### validateInputs

▸ **validateInputs**(): [*Input*](card_elements.input.md)[]

Validates the inputs associated with this action.

**Returns:** [*Input*](card_elements.input.md)[]

A list of inputs that failed validation, or an empty array if no input failed validation.

Defined in: [card-elements.ts:3937](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L3937)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [CardObject](card_object.cardobject.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
