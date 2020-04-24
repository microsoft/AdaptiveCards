[Adaptive Cards Javascript SDK](../README.md) › [OpenUrlAction](openurlaction.md)

# Class: OpenUrlAction

## Hierarchy

  ↳ [Action](action.md)

  ↳ **OpenUrlAction**

## Index

### Properties

* [iconUrl](openurlaction.md#iconurl)
* [id](openurlaction.md#id)
* [onExecute](openurlaction.md#onexecute)
* [requires](openurlaction.md#requires)
* [style](openurlaction.md#style)
* [title](openurlaction.md#title)
* [url](openurlaction.md#url)
* [JsonTypeName](openurlaction.md#static-jsontypename)

### Accessors

* [ignoreInputValidation](openurlaction.md#ignoreinputvalidation)
* [isPrimary](openurlaction.md#isprimary)
* [parent](openurlaction.md#parent)
* [renderedElement](openurlaction.md#renderedelement)

### Methods

* [addCssClasses](openurlaction.md#protected-addcssclasses)
* [execute](openurlaction.md#execute)
* [getActionById](openurlaction.md#getactionbyid)
* [getAllInputs](openurlaction.md#getallinputs)
* [getCustomProperty](openurlaction.md#getcustomproperty)
* [getHref](openurlaction.md#gethref)
* [getJsonTypeName](openurlaction.md#getjsontypename)
* [getReferencedInputs](openurlaction.md#getreferencedinputs)
* [getResourceInformation](openurlaction.md#getresourceinformation)
* [internalGetReferencedInputs](openurlaction.md#protected-internalgetreferencedinputs)
* [internalPrepareForExecution](openurlaction.md#protected-internalprepareforexecution)
* [internalValidateInputs](openurlaction.md#protected-internalvalidateinputs)
* [internalValidateProperties](openurlaction.md#internalvalidateproperties)
* [parse](openurlaction.md#parse)
* [prepareForExecution](openurlaction.md#prepareforexecution)
* [remove](openurlaction.md#remove)
* [render](openurlaction.md#render)
* [setCustomProperty](openurlaction.md#setcustomproperty)
* [setParent](openurlaction.md#setparent)
* [shouldFallback](openurlaction.md#shouldfallback)
* [toJSON](openurlaction.md#tojson)
* [validateInputs](openurlaction.md#validateinputs)
* [validateProperties](openurlaction.md#validateproperties)

## Properties

###  iconUrl

• **iconUrl**: *string*

*Inherited from [Action](action.md).[iconUrl](action.md#iconurl)*

*Defined in [card-elements.ts:3905](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3905)*

___

###  id

• **id**: *string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#id)*

*Defined in [card-elements.ts:247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L247)*

___

###  onExecute

• **onExecute**: *function*

*Inherited from [Action](action.md).[onExecute](action.md#onexecute)*

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

*Inherited from [Action](action.md).[requires](action.md#requires)*

*Defined in [card-elements.ts:3902](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3902)*

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

*Inherited from [Action](action.md).[style](action.md#style)*

*Defined in [card-elements.ts:3906](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3906)*

___

###  title

• **title**: *string*

*Inherited from [Action](action.md).[title](action.md#title)*

*Defined in [card-elements.ts:3904](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3904)*

___

###  url

• **url**: *string*

*Defined in [card-elements.ts:4183](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4183)*

___

### `Static` JsonTypeName

▪ **JsonTypeName**: *"Action.OpenUrl"* = "Action.OpenUrl"

*Defined in [card-elements.ts:4181](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4181)*

## Accessors

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

*Inherited from [Action](action.md).[ignoreInputValidation](action.md#ignoreinputvalidation)*

*Defined in [card-elements.ts:4088](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4088)*

**Returns:** *boolean*

___

###  isPrimary

• **get isPrimary**(): *boolean*

*Inherited from [Action](action.md).[isPrimary](action.md#isprimary)*

*Defined in [card-elements.ts:4073](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4073)*

**Returns:** *boolean*

• **set isPrimary**(`value`: boolean): *void*

*Inherited from [Action](action.md).[isPrimary](action.md#isprimary)*

*Defined in [card-elements.ts:4077](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4077)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md)*

*Inherited from [Action](action.md).[parent](action.md#parent)*

*Defined in [card-elements.ts:4092](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4092)*

**Returns:** *[CardElement](cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Inherited from [Action](action.md).[renderedElement](action.md#renderedelement)*

*Defined in [card-elements.ts:4096](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4096)*

**Returns:** *HTMLElement*

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): *void*

*Inherited from [Action](action.md).[addCssClasses](action.md#protected-addcssclasses)*

*Defined in [card-elements.ts:3872](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3872)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Inherited from [Action](action.md).[execute](action.md#execute)*

*Defined in [card-elements.ts:3992](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3992)*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md)*

*Inherited from [Action](action.md).[getActionById](action.md#getactionbyid)*

*Defined in [card-elements.ts:4055](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4055)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md)*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](input.md)›*

*Inherited from [Action](action.md).[getAllInputs](action.md#getallinputs)*

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

*Overrides [Action](action.md).[getHref](action.md#gethref)*

*Defined in [card-elements.ts:4216](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4216)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [Action](action.md).[getJsonTypeName](action.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:4185](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4185)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *Shared.Dictionary‹[Input](input.md)›*

*Inherited from [Action](action.md).[getReferencedInputs](action.md#getreferencedinputs)*

*Defined in [card-elements.ts:4061](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4061)*

**Returns:** *Shared.Dictionary‹[Input](input.md)›*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

*Inherited from [Action](action.md).[getResourceInformation](action.md#getresourceinformation)*

*Defined in [card-elements.ts:4046](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4046)*

**Returns:** *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(`allInputs`: Array‹[Input](input.md)›): *Shared.Dictionary‹[Input](input.md)›*

*Inherited from [Action](action.md).[internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)*

*Defined in [card-elements.ts:3876](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3876)*

**Parameters:**

Name | Type |
------ | ------ |
`allInputs` | Array‹[Input](input.md)› |

**Returns:** *Shared.Dictionary‹[Input](input.md)›*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: Shared.Dictionary‹[Input](input.md)›): *void*

*Inherited from [Action](action.md).[internalPrepareForExecution](action.md#protected-internalprepareforexecution)*

*Defined in [card-elements.ts:3880](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3880)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | Shared.Dictionary‹[Input](input.md)› |

**Returns:** *void*

___

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: Shared.Dictionary‹[Input](input.md)›): *Array‹[Input](input.md)›*

*Inherited from [Action](action.md).[internalValidateInputs](action.md#protected-internalvalidateinputs)*

*Defined in [card-elements.ts:3884](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3884)*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | Shared.Dictionary‹[Input](input.md)› |

**Returns:** *Array‹[Input](input.md)›*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Overrides [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:4197](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4197)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [Action](action.md).[parse](action.md#parse)*

*Defined in [card-elements.ts:4210](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4210)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*

___

###  prepareForExecution

▸ **prepareForExecution**(): *boolean*

*Inherited from [Action](action.md).[prepareForExecution](action.md#prepareforexecution)*

*Defined in [card-elements.ts:4000](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4000)*

**Returns:** *boolean*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [Action](action.md).[remove](action.md#remove)*

*Defined in [card-elements.ts:4034](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4034)*

**Returns:** *boolean*

___

###  render

▸ **render**(`baseCssClass`: string): *void*

*Inherited from [Action](action.md).[render](action.md#render)*

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

*Inherited from [Action](action.md).[setParent](action.md#setparent)*

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

*Inherited from [Action](action.md).[shouldFallback](action.md#shouldfallback)*

*Overrides [CardObject](cardobject.md).[shouldFallback](cardobject.md#abstract-shouldfallback)*

*Defined in [card-elements.ts:4069](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4069)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [Action](action.md).[toJSON](action.md#tojson)*

*Defined in [card-elements.ts:4189](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4189)*

**Returns:** *any*

___

###  validateInputs

▸ **validateInputs**(): *[Input](input.md)‹›[]*

*Inherited from [Action](action.md).[validateInputs](action.md#validateinputs)*

*Defined in [card-elements.ts:4065](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4065)*

**Returns:** *[Input](input.md)‹›[]*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

*Defined in [card-elements.ts:284](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L284)*

**Returns:** *[ValidationResults](validationresults.md)*
