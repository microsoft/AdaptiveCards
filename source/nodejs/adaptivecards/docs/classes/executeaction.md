[Adaptive Cards Javascript SDK](../README.md) › [ExecuteAction](executeaction.md)

# Class: ExecuteAction

## Hierarchy

  ↳ [SubmitAction](submitaction.md)

  ↳ **ExecuteAction**

## Index

### Constructors

* [constructor](executeaction.md#constructor)

### Properties

* [_parent](executeaction.md#protected-optional-_parent)
* [_renderedElement](executeaction.md#protected-optional-_renderedelement)
* [iconUrl](executeaction.md#optional-iconurl)
* [id](executeaction.md#optional-id)
* [maxVersion](executeaction.md#maxversion)
* [onExecute](executeaction.md#onexecute)
* [onPreProcessPropertyValue](executeaction.md#optional-onpreprocesspropertyvalue)
* [style](executeaction.md#style)
* [title](executeaction.md#optional-title)
* [verb](executeaction.md#verb)
* [JsonTypeName](executeaction.md#static-jsontypename)
* [dataProperty](executeaction.md#static-dataproperty)
* [iconUrlProperty](executeaction.md#static-iconurlproperty)
* [idProperty](executeaction.md#static-idproperty)
* [ignoreInputValidationProperty](executeaction.md#static-ignoreinputvalidationproperty)
* [onRegisterCustomProperties](executeaction.md#static-optional-onregistercustomproperties)
* [requiresProperty](executeaction.md#static-requiresproperty)
* [styleProperty](executeaction.md#static-styleproperty)
* [titleProperty](executeaction.md#static-titleproperty)
* [typeNameProperty](executeaction.md#static-typenameproperty)
* [verbProperty](executeaction.md#static-verbproperty)

### Accessors

* [data](executeaction.md#data)
* [hostConfig](executeaction.md#hostconfig)
* [ignoreInputValidation](executeaction.md#ignoreinputvalidation)
* [isPrimary](executeaction.md#isprimary)
* [parent](executeaction.md#parent)
* [renderedElement](executeaction.md#renderedelement)
* [requires](executeaction.md#requires)

### Methods

* [addCssClasses](executeaction.md#protected-addcssclasses)
* [execute](executeaction.md#execute)
* [getActionById](executeaction.md#getactionbyid)
* [getAllInputs](executeaction.md#getallinputs)
* [getAriaRole](executeaction.md#getariarole)
* [getCustomProperty](executeaction.md#getcustomproperty)
* [getHref](executeaction.md#gethref)
* [getJsonTypeName](executeaction.md#getjsontypename)
* [getReferencedInputs](executeaction.md#getreferencedinputs)
* [getResourceInformation](executeaction.md#getresourceinformation)
* [getRootObject](executeaction.md#getrootobject)
* [getSchema](executeaction.md#getschema)
* [getSchemaKey](executeaction.md#protected-getschemakey)
* [getValue](executeaction.md#protected-getvalue)
* [hasAllDefaultValues](executeaction.md#hasalldefaultvalues)
* [hasDefaultValue](executeaction.md#hasdefaultvalue)
* [internalGetReferencedInputs](executeaction.md#protected-internalgetreferencedinputs)
* [internalParse](executeaction.md#protected-internalparse)
* [internalPrepareForExecution](executeaction.md#protected-internalprepareforexecution)
* [internalToJSON](executeaction.md#protected-internaltojson)
* [internalValidateInputs](executeaction.md#protected-internalvalidateinputs)
* [internalValidateProperties](executeaction.md#internalvalidateproperties)
* [parse](executeaction.md#parse)
* [populateSchema](executeaction.md#protected-populateschema)
* [preProcessPropertyValue](executeaction.md#preprocesspropertyvalue)
* [prepareForExecution](executeaction.md#prepareforexecution)
* [remove](executeaction.md#remove)
* [render](executeaction.md#render)
* [resetDefaultValues](executeaction.md#resetdefaultvalues)
* [setCustomProperty](executeaction.md#setcustomproperty)
* [setParent](executeaction.md#setparent)
* [setShouldFallback](executeaction.md#setshouldfallback)
* [setValue](executeaction.md#protected-setvalue)
* [shouldFallback](executeaction.md#shouldfallback)
* [shouldSerialize](executeaction.md#protected-shouldserialize)
* [toJSON](executeaction.md#tojson)
* [updateActionButtonCssStyle](executeaction.md#updateactionbuttoncssstyle)
* [validateInputs](executeaction.md#validateinputs)
* [validateProperties](executeaction.md#validateproperties)

## Constructors

###  constructor

\+ **new ExecuteAction**(): *[ExecuteAction](executeaction.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Returns:** *[ExecuteAction](executeaction.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

___

### `Optional` iconUrl

• **iconUrl**? : *undefined | string*

*Inherited from [Action](action.md).[iconUrl](action.md#optional-iconurl)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

###  onExecute

• **onExecute**: *function*

*Inherited from [Action](action.md).[onExecute](action.md#onexecute)*

#### Type declaration:

▸ (`sender`: [Action](action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Action](action.md) |

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

*Inherited from [Action](action.md).[style](action.md#style)*

___

### `Optional` title

• **title**? : *undefined | string*

*Inherited from [Action](action.md).[title](action.md#optional-title)*

___

###  verb

• **verb**: *string*

___

### `Static` JsonTypeName

▪ **JsonTypeName**: *"Action.Submit"* = "Action.Submit"

*Inherited from [SubmitAction](submitaction.md).[JsonTypeName](submitaction.md#static-jsontypename)*

___

### `Static` dataProperty

▪ **dataProperty**: *[PropertyDefinition](propertydefinition.md)‹›* = new PropertyDefinition(Versions.v1_0, "data")

*Inherited from [SubmitAction](submitaction.md).[dataProperty](submitaction.md#static-dataproperty)*

___

### `Static` iconUrlProperty

▪ **iconUrlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "iconUrl")

*Inherited from [Action](action.md).[iconUrlProperty](action.md#static-iconurlproperty)*

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

___

### `Static` ignoreInputValidationProperty

▪ **ignoreInputValidationProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_3, "ignoreInputValidation", false)

*Inherited from [Action](action.md).[ignoreInputValidationProperty](action.md#static-ignoreinputvalidationproperty)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        false,
        new HostCapabilities())

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

___

### `Static` styleProperty

▪ **styleProperty**: *[ValueSetProperty](valuesetproperty.md)‹›* = new ValueSetProperty(
        Versions.v1_2,
        "style",
        [
            { value: Enums.ActionStyle.Default },
            { value: Enums.ActionStyle.Positive },
            { value: Enums.ActionStyle.Destructive }
        ],
        Enums.ActionStyle.Default)

*Inherited from [Action](action.md).[styleProperty](action.md#static-styleproperty)*

___

### `Static` titleProperty

▪ **titleProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "title")

*Inherited from [Action](action.md).[titleProperty](action.md#static-titleproperty)*

___

### `Static` typeNameProperty

▪ **typeNameProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(
        Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName()
        })

*Inherited from [CardObject](cardobject.md).[typeNameProperty](cardobject.md#static-typenameproperty)*

___

### `Static` verbProperty

▪ **verbProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_2, "verb")

## Accessors

###  data

• **get data**(): *object | undefined*

*Inherited from [SubmitAction](submitaction.md).[data](submitaction.md#data)*

**Returns:** *object | undefined*

• **set data**(`value`: object | undefined): *void*

*Inherited from [SubmitAction](submitaction.md).[data](submitaction.md#data)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | object &#124; undefined |

**Returns:** *void*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [Action](action.md).[hostConfig](action.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Returns:** *[HostConfig](hostconfig.md)*

___

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

*Inherited from [SubmitAction](submitaction.md).[ignoreInputValidation](submitaction.md#ignoreinputvalidation)*

*Overrides [Action](action.md).[ignoreInputValidation](action.md#ignoreinputvalidation)*

**Returns:** *boolean*

• **set ignoreInputValidation**(`value`: boolean): *void*

*Inherited from [SubmitAction](submitaction.md).[ignoreInputValidation](submitaction.md#ignoreinputvalidation)*

*Overrides [Action](action.md).[ignoreInputValidation](action.md#ignoreinputvalidation)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  isPrimary

• **get isPrimary**(): *boolean*

*Inherited from [Action](action.md).[isPrimary](action.md#isprimary)*

**Returns:** *boolean*

• **set isPrimary**(`value`: boolean): *void*

*Inherited from [Action](action.md).[isPrimary](action.md#isprimary)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md) | undefined*

*Inherited from [Action](action.md).[parent](action.md#parent)*

*Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

*Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)*

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

**Returns:** *HostCapabilities*

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): *void*

*Inherited from [Action](action.md).[addCssClasses](action.md#protected-addcssclasses)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Inherited from [Action](action.md).[execute](action.md#execute)*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

*Inherited from [Action](action.md).[getActionById](action.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

*Inherited from [Action](action.md).[getAllInputs](action.md#getallinputs)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

###  getAriaRole

▸ **getAriaRole**(): *string*

*Inherited from [Action](action.md).[getAriaRole](action.md#getariarole)*

**Returns:** *string*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getHref

▸ **getHref**(): *string | undefined*

*Inherited from [Action](action.md).[getHref](action.md#gethref)*

**Returns:** *string | undefined*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [SubmitAction](submitaction.md).[getJsonTypeName](submitaction.md#getjsontypename)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined*

*Inherited from [Action](action.md).[getReferencedInputs](action.md#getreferencedinputs)*

**Returns:** *[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

*Inherited from [Action](action.md).[getResourceInformation](action.md#getresourceinformation)*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootObject

▸ **getRootObject**(): *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)*

**Returns:** *[CardObject](cardobject.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(): *[Dictionary](../README.md#dictionary)‹[Input](input.md)›*

*Inherited from [SubmitAction](submitaction.md).[internalGetReferencedInputs](submitaction.md#protected-internalgetreferencedinputs)*

*Overrides [Action](action.md).[internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)*

**Returns:** *[Dictionary](../README.md#dictionary)‹[Input](input.md)›*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): *void*

*Inherited from [SubmitAction](submitaction.md).[internalPrepareForExecution](submitaction.md#protected-internalprepareforexecution)*

*Overrides [Action](action.md).[internalPrepareForExecution](action.md#protected-internalprepareforexecution)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): *[Input](input.md)[]*

*Inherited from [Action](action.md).[internalValidateInputs](action.md#protected-internalvalidateinputs)*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** *[Input](input.md)[]*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [Action](action.md).[parse](action.md#parse)*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): *any*

*Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`propertyValue?` | any |

**Returns:** *any*

___

###  prepareForExecution

▸ **prepareForExecution**(): *boolean*

*Inherited from [Action](action.md).[prepareForExecution](action.md#prepareforexecution)*

**Returns:** *boolean*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [Action](action.md).[remove](action.md#remove)*

**Returns:** *boolean*

___

###  render

▸ **render**(`baseCssClass`: string): *void*

*Inherited from [Action](action.md).[render](action.md#render)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`baseCssClass` | string | "ac-pushButton" |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): *void*

*Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)*

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [Action](action.md).[toJSON](action.md#tojson)*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

###  updateActionButtonCssStyle

▸ **updateActionButtonCssStyle**(`actionButtonElement`: HTMLElement, `buttonState`: ActionButtonState): *void*

*Inherited from [Action](action.md).[updateActionButtonCssStyle](action.md#updateactionbuttoncssstyle)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`actionButtonElement` | HTMLElement | - |
`buttonState` | ActionButtonState | ActionButtonState.Normal |

**Returns:** *void*

___

###  validateInputs

▸ **validateInputs**(): *[Input](input.md)[]*

*Inherited from [Action](action.md).[validateInputs](action.md#validateinputs)*

Validates the inputs associated with this action.

**Returns:** *[Input](input.md)[]*

A list of inputs that failed validation, or an empty array if no input failed validation.

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

**Returns:** *[ValidationResults](validationresults.md)*
