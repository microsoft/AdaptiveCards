[Adaptive Cards Javascript SDK](../README.md) › [Action](action.md)

# Class: Action

## Hierarchy

  ↳ [CardObject](cardobject.md)

  ↳ **Action**

  ↳ [SubmitAction](submitaction.md)

  ↳ [OpenUrlAction](openurlaction.md)

  ↳ [ToggleVisibilityAction](togglevisibilityaction.md)

  ↳ [HttpAction](httpaction.md)

  ↳ [ShowCardAction](showcardaction.md)

## Index

### Properties

* [iconUrl](action.md#iconurl)
* [id](action.md#id)
* [onExecute](action.md#onexecute)
* [requires](action.md#requires)
* [style](action.md#style)
* [title](action.md#title)

### Accessors

* [ignoreInputValidation](action.md#ignoreinputvalidation)
* [isPrimary](action.md#isprimary)
* [parent](action.md#parent)
* [renderedElement](action.md#renderedelement)

### Methods

* [addCssClasses](action.md#protected-addcssclasses)
* [execute](action.md#execute)
* [getActionById](action.md#getactionbyid)
* [getAllInputs](action.md#getallinputs)
* [getCustomProperty](action.md#getcustomproperty)
* [getHref](action.md#gethref)
* [getJsonTypeName](action.md#abstract-getjsontypename)
* [getReferencedInputs](action.md#getreferencedinputs)
* [getResourceInformation](action.md#getresourceinformation)
* [internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)
* [internalPrepareForExecution](action.md#protected-internalprepareforexecution)
* [internalValidateInputs](action.md#protected-internalvalidateinputs)
* [internalValidateProperties](action.md#internalvalidateproperties)
* [parse](action.md#parse)
* [prepareForExecution](action.md#prepareforexecution)
* [remove](action.md#remove)
* [render](action.md#render)
* [setCustomProperty](action.md#setcustomproperty)
* [setParent](action.md#setparent)
* [shouldFallback](action.md#shouldfallback)
* [toJSON](action.md#tojson)
* [validateInputs](action.md#validateinputs)
* [validateProperties](action.md#validateproperties)

## Properties

###  iconUrl

• **iconUrl**: *string*

*Defined in [card-elements.ts:3905](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3905)*

___

###  id

• **id**: *string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#id)*

*Defined in [card-elements.ts:247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L247)*

___

###  onExecute

• **onExecute**: *function*

*Defined in [card-elements.ts:3908](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3908)*

#### Type declaration:

▸ (`sender`: [Action](action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Action](action.md) |

___

###  requires

• **requires**: *[HostCapabilities](hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

*Defined in [card-elements.ts:3902](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3902)*

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

*Defined in [card-elements.ts:3906](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3906)*

___

###  title

• **title**: *string*

*Defined in [card-elements.ts:3904](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3904)*

## Accessors

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

*Defined in [card-elements.ts:4088](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4088)*

**Returns:** *boolean*

___

###  isPrimary

• **get isPrimary**(): *boolean*

*Defined in [card-elements.ts:4073](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4073)*

**Returns:** *boolean*

• **set isPrimary**(`value`: boolean): *void*

*Defined in [card-elements.ts:4077](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4077)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md)*

*Defined in [card-elements.ts:4092](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4092)*

**Returns:** *[CardElement](cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Defined in [card-elements.ts:4096](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4096)*

**Returns:** *HTMLElement*

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): *void*

*Defined in [card-elements.ts:3872](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3872)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Defined in [card-elements.ts:3992](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3992)*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md)*

*Defined in [card-elements.ts:4055](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4055)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md)*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](input.md)›*

*Defined in [card-elements.ts:4042](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4042)*

**Returns:** *Array‹[Input](input.md)›*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

*Defined in [card-elements.ts:200](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L200)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getHref

▸ **getHref**(): *string*

*Defined in [card-elements.ts:3910](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3910)*

**Returns:** *string*

___

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:3900](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3900)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *Shared.Dictionary‹[Input](input.md)›*

*Defined in [card-elements.ts:4061](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4061)*

**Returns:** *Shared.Dictionary‹[Input](input.md)›*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

*Defined in [card-elements.ts:4046](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4046)*

**Returns:** *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(`allInputs`: Array‹[Input](input.md)›): *Shared.Dictionary‹[Input](input.md)›*

*Defined in [card-elements.ts:3876](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3876)*

**Parameters:**

Name | Type |
------ | ------ |
`allInputs` | Array‹[Input](input.md)› |

**Returns:** *Shared.Dictionary‹[Input](input.md)›*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: Shared.Dictionary‹[Input](input.md)›): *void*

*Defined in [card-elements.ts:3880](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3880)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Shared.Dictionary‹[Input](input.md)› |

**Returns:** *void*

___

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: Shared.Dictionary‹[Input](input.md)›): *Array‹[Input](input.md)›*

*Defined in [card-elements.ts:3884](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3884)*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | Shared.Dictionary‹[Input](input.md)› |

**Returns:** *Array‹[Input](input.md)›*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:249](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L249)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [CardObject](cardobject.md).[parse](cardobject.md#parse)*

*Defined in [card-elements.ts:4012](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4012)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*

___

###  prepareForExecution

▸ **prepareForExecution**(): *boolean*

*Defined in [card-elements.ts:4000](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4000)*

**Returns:** *boolean*

___

###  remove

▸ **remove**(): *boolean*

*Defined in [card-elements.ts:4034](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4034)*

**Returns:** *boolean*

___

###  render

▸ **render**(`baseCssClass`: string): *void*

*Defined in [card-elements.ts:3925](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3925)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`baseCssClass` | string | "ac-pushButton" |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

*Defined in [card-elements.ts:189](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L189)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardElement](cardelement.md)): *void*

*Overrides [CardObject](cardobject.md).[setParent](cardobject.md#abstract-setparent)*

*Defined in [card-elements.ts:3988](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3988)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardElement](cardelement.md) |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Overrides [CardObject](cardobject.md).[shouldFallback](cardobject.md#abstract-shouldfallback)*

*Defined in [card-elements.ts:4069](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4069)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [CardObject](cardobject.md).[toJSON](cardobject.md#tojson)*

*Defined in [card-elements.ts:3914](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3914)*

**Returns:** *any*

___

###  validateInputs

▸ **validateInputs**(): *[Input](input.md)‹›[]*

*Defined in [card-elements.ts:4065](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4065)*

**Returns:** *[Input](input.md)‹›[]*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

*Defined in [card-elements.ts:284](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L284)*

**Returns:** *[ValidationResults](validationresults.md)*
