[Adaptive Cards Javascript SDK](../README.md) › [ToggleVisibilityAction](togglevisibilityaction.md)

# Class: ToggleVisibilityAction

## Hierarchy

  ↳ [Action](action.md)

  ↳ **ToggleVisibilityAction**

## Index

### Properties

* [iconUrl](togglevisibilityaction.md#iconurl)
* [id](togglevisibilityaction.md#id)
* [onExecute](togglevisibilityaction.md#onexecute)
* [requires](togglevisibilityaction.md#requires)
* [style](togglevisibilityaction.md#style)
* [targetElements](togglevisibilityaction.md#targetelements)
* [title](togglevisibilityaction.md#title)
* [JsonTypeName](togglevisibilityaction.md#static-jsontypename)

### Accessors

* [ignoreInputValidation](togglevisibilityaction.md#ignoreinputvalidation)
* [isPrimary](togglevisibilityaction.md#isprimary)
* [parent](togglevisibilityaction.md#parent)
* [renderedElement](togglevisibilityaction.md#renderedelement)

### Methods

* [addCssClasses](togglevisibilityaction.md#protected-addcssclasses)
* [addTargetElement](togglevisibilityaction.md#addtargetelement)
* [execute](togglevisibilityaction.md#execute)
* [getActionById](togglevisibilityaction.md#getactionbyid)
* [getAllInputs](togglevisibilityaction.md#getallinputs)
* [getCustomProperty](togglevisibilityaction.md#getcustomproperty)
* [getHref](togglevisibilityaction.md#gethref)
* [getJsonTypeName](togglevisibilityaction.md#getjsontypename)
* [getReferencedInputs](togglevisibilityaction.md#getreferencedinputs)
* [getResourceInformation](togglevisibilityaction.md#getresourceinformation)
* [internalGetReferencedInputs](togglevisibilityaction.md#protected-internalgetreferencedinputs)
* [internalPrepareForExecution](togglevisibilityaction.md#protected-internalprepareforexecution)
* [internalValidateInputs](togglevisibilityaction.md#protected-internalvalidateinputs)
* [internalValidateProperties](togglevisibilityaction.md#internalvalidateproperties)
* [parse](togglevisibilityaction.md#parse)
* [prepareForExecution](togglevisibilityaction.md#prepareforexecution)
* [remove](togglevisibilityaction.md#remove)
* [removeTargetElement](togglevisibilityaction.md#removetargetelement)
* [render](togglevisibilityaction.md#render)
* [setCustomProperty](togglevisibilityaction.md#setcustomproperty)
* [setParent](togglevisibilityaction.md#setparent)
* [shouldFallback](togglevisibilityaction.md#shouldfallback)
* [toJSON](togglevisibilityaction.md#tojson)
* [validateInputs](togglevisibilityaction.md#validateinputs)
* [validateProperties](togglevisibilityaction.md#validateproperties)

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

###  targetElements

• **targetElements**: *object*

*Defined in [card-elements.ts:4226](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4226)*

#### Type declaration:

___

###  title

• **title**: *string*

*Inherited from [Action](action.md).[title](action.md#title)*

*Defined in [card-elements.ts:3904](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3904)*

___

### `Static` JsonTypeName

▪ **JsonTypeName**: *"Action.ToggleVisibility"* = "Action.ToggleVisibility"

*Defined in [card-elements.ts:4224](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4224)*

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

###  addTargetElement

▸ **addTargetElement**(`elementId`: string, `isVisible`: boolean): *void*

*Defined in [card-elements.ts:4294](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4294)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`elementId` | string | - |
`isVisible` | boolean | undefined |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Overrides [Action](action.md).[execute](action.md#execute)*

*Defined in [card-elements.ts:4232](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4232)*

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

*Inherited from [Action](action.md).[getHref](action.md#gethref)*

*Defined in [card-elements.ts:3910](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L3910)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [Action](action.md).[getJsonTypeName](action.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:4228](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4228)*

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

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:249](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L249)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`json`: any): *void*

*Overrides [Action](action.md).[parse](action.md#parse)*

*Defined in [card-elements.ts:4247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4247)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |

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

###  removeTargetElement

▸ **removeTargetElement**(`elementId`: any): *void*

*Defined in [card-elements.ts:4298](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4298)*

**Parameters:**

Name | Type |
------ | ------ |
`elementId` | any |

**Returns:** *void*

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

*Defined in [card-elements.ts:4270](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L4270)*

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
