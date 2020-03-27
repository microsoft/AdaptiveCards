[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [Action](_card_elements_.action.md)

# Class: Action

## Hierarchy

  ↳ [CardObject](_card_elements_.cardobject.md)

  ↳ **Action**

  ↳ [SubmitAction](_card_elements_.submitaction.md)

  ↳ [OpenUrlAction](_card_elements_.openurlaction.md)

  ↳ [ToggleVisibilityAction](_card_elements_.togglevisibilityaction.md)

  ↳ [HttpAction](_card_elements_.httpaction.md)

  ↳ [ShowCardAction](_card_elements_.showcardaction.md)

## Index

### Properties

* [iconUrl](_card_elements_.action.md#iconurl)
* [id](_card_elements_.action.md#id)
* [onExecute](_card_elements_.action.md#onexecute)
* [requires](_card_elements_.action.md#requires)
* [style](_card_elements_.action.md#style)
* [title](_card_elements_.action.md#title)

### Accessors

* [ignoreInputValidation](_card_elements_.action.md#ignoreinputvalidation)
* [isPrimary](_card_elements_.action.md#isprimary)
* [parent](_card_elements_.action.md#parent)
* [renderedElement](_card_elements_.action.md#renderedelement)

### Methods

* [addCssClasses](_card_elements_.action.md#protected-addcssclasses)
* [execute](_card_elements_.action.md#execute)
* [getActionById](_card_elements_.action.md#getactionbyid)
* [getAllInputs](_card_elements_.action.md#getallinputs)
* [getCustomProperty](_card_elements_.action.md#getcustomproperty)
* [getHref](_card_elements_.action.md#gethref)
* [getJsonTypeName](_card_elements_.action.md#abstract-getjsontypename)
* [getReferencedInputs](_card_elements_.action.md#getreferencedinputs)
* [getResourceInformation](_card_elements_.action.md#getresourceinformation)
* [internalGetReferencedInputs](_card_elements_.action.md#protected-internalgetreferencedinputs)
* [internalPrepareForExecution](_card_elements_.action.md#protected-internalprepareforexecution)
* [internalValidateInputs](_card_elements_.action.md#protected-internalvalidateinputs)
* [internalValidateProperties](_card_elements_.action.md#internalvalidateproperties)
* [parse](_card_elements_.action.md#parse)
* [prepareForExecution](_card_elements_.action.md#prepareforexecution)
* [remove](_card_elements_.action.md#remove)
* [render](_card_elements_.action.md#render)
* [setCustomProperty](_card_elements_.action.md#setcustomproperty)
* [setParent](_card_elements_.action.md#setparent)
* [shouldFallback](_card_elements_.action.md#shouldfallback)
* [toJSON](_card_elements_.action.md#tojson)
* [validateInputs](_card_elements_.action.md#validateinputs)
* [validateProperties](_card_elements_.action.md#validateproperties)

## Properties

###  iconUrl

• **iconUrl**: *string*

___

###  id

• **id**: *string*

*Inherited from [CardObject](_card_elements_.cardobject.md).[id](_card_elements_.cardobject.md#id)*

___

###  onExecute

• **onExecute**: *function*

#### Type declaration:

▸ (`sender`: [Action](_card_elements_.action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Action](_card_elements_.action.md) |

___

###  requires

• **requires**: *[HostCapabilities](_host_config_.hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

___

###  title

• **title**: *string*

## Accessors

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

**Returns:** *boolean*

___

###  isPrimary

• **get isPrimary**(): *boolean*

**Returns:** *boolean*

• **set isPrimary**(`value`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](_card_elements_.cardelement.md)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

**Returns:** *HTMLElement*

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](_card_elements_.action.md)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](_card_elements_.input.md)›*

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

**Returns:** *string*

___

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardObject](_card_elements_.cardobject.md).[getJsonTypeName](_card_elements_.cardobject.md#abstract-getjsontypename)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

**Returns:** *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

**Returns:** *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(`allInputs`: Array‹[Input](_card_elements_.input.md)›): *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

**Parameters:**

Name | Type |
------ | ------ |
`allInputs` | Array‹[Input](_card_elements_.input.md)› |

**Returns:** *Shared.Dictionary‹[Input](_card_elements_.input.md)›*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: Shared.Dictionary‹[Input](_card_elements_.input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Shared.Dictionary‹[Input](_card_elements_.input.md)› |

**Returns:** *void*

___

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: Shared.Dictionary‹[Input](_card_elements_.input.md)›): *Array‹[Input](_card_elements_.input.md)›*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | Shared.Dictionary‹[Input](_card_elements_.input.md)› |

**Returns:** *Array‹[Input](_card_elements_.input.md)›*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](_card_elements_.validationresults.md)): *void*

*Inherited from [CardObject](_card_elements_.cardobject.md).[internalValidateProperties](_card_elements_.cardobject.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](_card_elements_.validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

*Overrides [CardObject](_card_elements_.cardobject.md).[parse](_card_elements_.cardobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *void*

___

###  prepareForExecution

▸ **prepareForExecution**(): *boolean*

**Returns:** *boolean*

___

###  remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

___

###  render

▸ **render**(`baseCssClass`: string): *void*

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

*Overrides [CardObject](_card_elements_.cardobject.md).[setParent](_card_elements_.cardobject.md#abstract-setparent)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Overrides [CardObject](_card_elements_.cardobject.md).[shouldFallback](_card_elements_.cardobject.md#abstract-shouldfallback)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [CardObject](_card_elements_.cardobject.md).[toJSON](_card_elements_.cardobject.md#tojson)*

**Returns:** *any*

___

###  validateInputs

▸ **validateInputs**(): *[Input](_card_elements_.input.md)‹›[]*

**Returns:** *[Input](_card_elements_.input.md)‹›[]*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](_card_elements_.validationresults.md)*

*Inherited from [CardObject](_card_elements_.cardobject.md).[validateProperties](_card_elements_.cardobject.md#validateproperties)*

**Returns:** *[ValidationResults](_card_elements_.validationresults.md)*
