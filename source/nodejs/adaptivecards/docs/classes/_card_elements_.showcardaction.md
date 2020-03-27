[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [ShowCardAction](_card_elements_.showcardaction.md)

# Class: ShowCardAction

## Hierarchy

  ↳ [Action](_card_elements_.action.md)

  ↳ **ShowCardAction**

## Index

### Properties

* [card](_card_elements_.showcardaction.md#card)
* [iconUrl](_card_elements_.showcardaction.md#iconurl)
* [id](_card_elements_.showcardaction.md#id)
* [onExecute](_card_elements_.showcardaction.md#onexecute)
* [requires](_card_elements_.showcardaction.md#requires)
* [style](_card_elements_.showcardaction.md#style)
* [title](_card_elements_.showcardaction.md#title)
* [JsonTypeName](_card_elements_.showcardaction.md#static-jsontypename)

### Accessors

* [ignoreInputValidation](_card_elements_.showcardaction.md#ignoreinputvalidation)
* [isPrimary](_card_elements_.showcardaction.md#isprimary)
* [parent](_card_elements_.showcardaction.md#parent)
* [renderedElement](_card_elements_.showcardaction.md#renderedelement)

### Methods

* [addCssClasses](_card_elements_.showcardaction.md#protected-addcssclasses)
* [execute](_card_elements_.showcardaction.md#execute)
* [getActionById](_card_elements_.showcardaction.md#getactionbyid)
* [getAllInputs](_card_elements_.showcardaction.md#getallinputs)
* [getCustomProperty](_card_elements_.showcardaction.md#getcustomproperty)
* [getHref](_card_elements_.showcardaction.md#gethref)
* [getJsonTypeName](_card_elements_.showcardaction.md#getjsontypename)
* [getReferencedInputs](_card_elements_.showcardaction.md#getreferencedinputs)
* [getResourceInformation](_card_elements_.showcardaction.md#getresourceinformation)
* [internalGetReferencedInputs](_card_elements_.showcardaction.md#protected-internalgetreferencedinputs)
* [internalPrepareForExecution](_card_elements_.showcardaction.md#protected-internalprepareforexecution)
* [internalValidateInputs](_card_elements_.showcardaction.md#protected-internalvalidateinputs)
* [internalValidateProperties](_card_elements_.showcardaction.md#internalvalidateproperties)
* [parse](_card_elements_.showcardaction.md#parse)
* [prepareForExecution](_card_elements_.showcardaction.md#prepareforexecution)
* [remove](_card_elements_.showcardaction.md#remove)
* [render](_card_elements_.showcardaction.md#render)
* [setCustomProperty](_card_elements_.showcardaction.md#setcustomproperty)
* [setParent](_card_elements_.showcardaction.md#setparent)
* [shouldFallback](_card_elements_.showcardaction.md#shouldfallback)
* [toJSON](_card_elements_.showcardaction.md#tojson)
* [validateInputs](_card_elements_.showcardaction.md#validateinputs)
* [validateProperties](_card_elements_.showcardaction.md#validateproperties)

## Properties

###  card

• **card**: *[AdaptiveCard](_card_elements_.adaptivecard.md)* = new InlineAdaptiveCard()

___

###  iconUrl

• **iconUrl**: *string*

*Inherited from [Action](_card_elements_.action.md).[iconUrl](_card_elements_.action.md#iconurl)*

___

###  id

• **id**: *string*

*Inherited from [CardObject](_card_elements_.cardobject.md).[id](_card_elements_.cardobject.md#id)*

___

###  onExecute

• **onExecute**: *function*

*Inherited from [Action](_card_elements_.action.md).[onExecute](_card_elements_.action.md#onexecute)*

#### Type declaration:

▸ (`sender`: [Action](_card_elements_.action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Action](_card_elements_.action.md) |

___

###  requires

• **requires**: *[HostCapabilities](_host_config_.hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

*Inherited from [Action](_card_elements_.action.md).[requires](_card_elements_.action.md#requires)*

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

*Inherited from [Action](_card_elements_.action.md).[style](_card_elements_.action.md#style)*

___

###  title

• **title**: *string*

*Inherited from [Action](_card_elements_.action.md).[title](_card_elements_.action.md#title)*

___

### `Static` JsonTypeName

▪ **JsonTypeName**: *"Action.ShowCard"* = "Action.ShowCard"

## Accessors

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

*Inherited from [Action](_card_elements_.action.md).[ignoreInputValidation](_card_elements_.action.md#ignoreinputvalidation)*

**Returns:** *boolean*

___

###  isPrimary

• **get isPrimary**(): *boolean*

*Inherited from [Action](_card_elements_.action.md).[isPrimary](_card_elements_.action.md#isprimary)*

**Returns:** *boolean*

• **set isPrimary**(`value`: boolean): *void*

*Inherited from [Action](_card_elements_.action.md).[isPrimary](_card_elements_.action.md#isprimary)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [Action](_card_elements_.action.md).[parent](_card_elements_.action.md#parent)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Inherited from [Action](_card_elements_.action.md).[renderedElement](_card_elements_.action.md#renderedelement)*

**Returns:** *HTMLElement*

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): *void*

*Overrides [Action](_card_elements_.action.md).[addCssClasses](_card_elements_.action.md#protected-addcssclasses)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Inherited from [Action](_card_elements_.action.md).[execute](_card_elements_.action.md#execute)*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](_card_elements_.action.md)*

*Overrides [Action](_card_elements_.action.md).[getActionById](_card_elements_.action.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](_card_elements_.input.md)›*

*Overrides [Action](_card_elements_.action.md).[getAllInputs](_card_elements_.action.md#getallinputs)*

**Returns:** *Array‹[Input](_card_elements_.input.md)›*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[getCustomProperty](_card_elements_.serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getHref

▸ **getHref**(): *string*

*Inherited from [Action](_card_elements_.action.md).[getHref](_card_elements_.action.md#gethref)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [Action](_card_elements_.action.md).[getJsonTypeName](_card_elements_.action.md#abstract-getjsontypename)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

*Inherited from [Action](_card_elements_.action.md).[getReferencedInputs](_card_elements_.action.md#getreferencedinputs)*

**Returns:** *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

*Overrides [Action](_card_elements_.action.md).[getResourceInformation](_card_elements_.action.md#getresourceinformation)*

**Returns:** *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(`allInputs`: Array‹[Input](_card_elements_.input.md)›): *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

*Inherited from [Action](_card_elements_.action.md).[internalGetReferencedInputs](_card_elements_.action.md#protected-internalgetreferencedinputs)*

**Parameters:**

Name | Type |
------ | ------ |
`allInputs` | Array‹[Input](_card_elements_.input.md)› |

**Returns:** *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: Shared.Dictionary‹[Input](_card_elements_.input.md)›): *void*

*Inherited from [Action](_card_elements_.action.md).[internalPrepareForExecution](_card_elements_.action.md#protected-internalprepareforexecution)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Shared.Dictionary‹[Input](_card_elements_.input.md)› |

**Returns:** *void*

___

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: Shared.Dictionary‹[Input](_card_elements_.input.md)›): *Array‹[Input](_card_elements_.input.md)›*

*Inherited from [Action](_card_elements_.action.md).[internalValidateInputs](_card_elements_.action.md#protected-internalvalidateinputs)*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | Shared.Dictionary‹[Input](_card_elements_.input.md)› |

**Returns:** *Array‹[Input](_card_elements_.input.md)›*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](_card_elements_.validationresults.md)): *void*

*Overrides [CardObject](_card_elements_.cardobject.md).[internalValidateProperties](_card_elements_.cardobject.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](_card_elements_.validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

*Overrides [Action](_card_elements_.action.md).[parse](_card_elements_.action.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *void*

___

###  prepareForExecution

▸ **prepareForExecution**(): *boolean*

*Inherited from [Action](_card_elements_.action.md).[prepareForExecution](_card_elements_.action.md#prepareforexecution)*

**Returns:** *boolean*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [Action](_card_elements_.action.md).[remove](_card_elements_.action.md#remove)*

**Returns:** *boolean*

___

###  render

▸ **render**(`baseCssClass`: string): *void*

*Inherited from [Action](_card_elements_.action.md).[render](_card_elements_.action.md#render)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`baseCssClass` | string | "ac-pushButton" |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[setCustomProperty](_card_elements_.serializableobject.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardElement](_card_elements_.cardelement.md)): *void*

*Overrides [Action](_card_elements_.action.md).[setParent](_card_elements_.action.md#setparent)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [Action](_card_elements_.action.md).[shouldFallback](_card_elements_.action.md#shouldfallback)*

*Overrides [CardObject](_card_elements_.cardobject.md).[shouldFallback](_card_elements_.cardobject.md#abstract-shouldfallback)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [Action](_card_elements_.action.md).[toJSON](_card_elements_.action.md#tojson)*

**Returns:** *any*

___

###  validateInputs

▸ **validateInputs**(): *[Input](_card_elements_.input.md)‹›[]*

*Inherited from [Action](_card_elements_.action.md).[validateInputs](_card_elements_.action.md#validateinputs)*

**Returns:** *[Input](_card_elements_.input.md)‹›[]*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](_card_elements_.validationresults.md)*

*Inherited from [CardObject](_card_elements_.cardobject.md).[validateProperties](_card_elements_.cardobject.md#validateproperties)*

**Returns:** *[ValidationResults](_card_elements_.validationresults.md)*
