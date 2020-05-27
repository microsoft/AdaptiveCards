[Adaptive Cards Javascript SDK](../README.md) › [HttpAction](httpaction.md)

# Class: HttpAction

## Hierarchy

  ↳ [Action](action.md)

  ↳ **HttpAction**

## Index

### Constructors

* [constructor](httpaction.md#constructor)

### Properties

* [_parent](httpaction.md#protected-optional-_parent)
* [_renderedElement](httpaction.md#protected-optional-_renderedelement)
* [headers](httpaction.md#headers)
* [iconUrl](httpaction.md#optional-iconurl)
* [id](httpaction.md#optional-id)
* [maxVersion](httpaction.md#maxversion)
* [method](httpaction.md#optional-method)
* [onExecute](httpaction.md#onexecute)
* [onPreProcessPropertyValue](httpaction.md#optional-onpreprocesspropertyvalue)
* [style](httpaction.md#style)
* [title](httpaction.md#optional-title)
* [JsonTypeName](httpaction.md#static-jsontypename)
* [bodyProperty](httpaction.md#static-bodyproperty)
* [headersProperty](httpaction.md#static-headersproperty)
* [iconUrlProperty](httpaction.md#static-iconurlproperty)
* [idProperty](httpaction.md#static-idproperty)
* [ignoreInputValidationProperty](httpaction.md#static-ignoreinputvalidationproperty)
* [methodProperty](httpaction.md#static-methodproperty)
* [onRegisterCustomProperties](httpaction.md#static-optional-onregistercustomproperties)
* [requiresProperty](httpaction.md#static-requiresproperty)
* [styleProperty](httpaction.md#static-styleproperty)
* [titleProperty](httpaction.md#static-titleproperty)
* [typeNameProperty](httpaction.md#static-typenameproperty)
* [urlProperty](httpaction.md#static-urlproperty)

### Accessors

* [body](httpaction.md#body)
* [hostConfig](httpaction.md#hostconfig)
* [ignoreInputValidation](httpaction.md#ignoreinputvalidation)
* [isPrimary](httpaction.md#isprimary)
* [parent](httpaction.md#parent)
* [renderedElement](httpaction.md#renderedelement)
* [requires](httpaction.md#requires)
* [url](httpaction.md#url)

### Methods

* [addCssClasses](httpaction.md#protected-addcssclasses)
* [execute](httpaction.md#execute)
* [getActionById](httpaction.md#getactionbyid)
* [getAllInputs](httpaction.md#getallinputs)
* [getCustomProperty](httpaction.md#getcustomproperty)
* [getHref](httpaction.md#gethref)
* [getJsonTypeName](httpaction.md#getjsontypename)
* [getReferencedInputs](httpaction.md#getreferencedinputs)
* [getResourceInformation](httpaction.md#getresourceinformation)
* [getRootObject](httpaction.md#getrootobject)
* [getSchema](httpaction.md#getschema)
* [getSchemaKey](httpaction.md#protected-getschemakey)
* [getValue](httpaction.md#protected-getvalue)
* [hasAllDefaultValues](httpaction.md#hasalldefaultvalues)
* [hasDefaultValue](httpaction.md#hasdefaultvalue)
* [internalGetReferencedInputs](httpaction.md#protected-internalgetreferencedinputs)
* [internalParse](httpaction.md#protected-internalparse)
* [internalPrepareForExecution](httpaction.md#protected-internalprepareforexecution)
* [internalToJSON](httpaction.md#protected-internaltojson)
* [internalValidateInputs](httpaction.md#protected-internalvalidateinputs)
* [internalValidateProperties](httpaction.md#internalvalidateproperties)
* [parse](httpaction.md#parse)
* [populateSchema](httpaction.md#protected-populateschema)
* [preProcessPropertyValue](httpaction.md#preprocesspropertyvalue)
* [prepareForExecution](httpaction.md#prepareforexecution)
* [remove](httpaction.md#remove)
* [render](httpaction.md#render)
* [resetDefaultValues](httpaction.md#resetdefaultvalues)
* [setCustomProperty](httpaction.md#setcustomproperty)
* [setParent](httpaction.md#setparent)
* [setShouldFallback](httpaction.md#setshouldfallback)
* [setValue](httpaction.md#protected-setvalue)
* [shouldFallback](httpaction.md#shouldfallback)
* [shouldSerialize](httpaction.md#protected-shouldserialize)
* [toJSON](httpaction.md#tojson)
* [updateActionButtonCssStyle](httpaction.md#updateactionbuttoncssstyle)
* [validateInputs](httpaction.md#validateinputs)
* [validateProperties](httpaction.md#validateproperties)

## Constructors

###  constructor

\+ **new HttpAction**(): *[HttpAction](httpaction.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

**Returns:** *[HttpAction](httpaction.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

*Defined in [card-object.ts:61](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L61)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

*Defined in [card-object.ts:62](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L62)*

___

###  headers

• **headers**: *[HttpHeader](httpheader.md)[]*

*Defined in [card-elements.ts:3850](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3850)*

___

### `Optional` iconUrl

• **iconUrl**? : *undefined | string*

*Inherited from [Action](action.md).[iconUrl](action.md#optional-iconurl)*

*Defined in [card-elements.ts:3359](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3359)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

*Defined in [card-object.ts:50](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L50)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

___

### `Optional` method

• **method**? : *undefined | string*

*Defined in [card-elements.ts:3847](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3847)*

___

###  onExecute

• **onExecute**: *function*

*Inherited from [Action](action.md).[onExecute](action.md#onexecute)*

*Defined in [card-elements.ts:3400](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3400)*

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

*Defined in [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L64)*

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

*Inherited from [Action](action.md).[style](action.md#style)*

*Defined in [card-elements.ts:3362](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3362)*

___

### `Optional` title

• **title**? : *undefined | string*

*Inherited from [Action](action.md).[title](action.md#optional-title)*

*Defined in [card-elements.ts:3356](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3356)*

___

### `Static` JsonTypeName

▪ **JsonTypeName**: *"Action.Http"* = "Action.Http"

*Defined in [card-elements.ts:3859](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3859)*

___

### `Static` bodyProperty

▪ **bodyProperty**: *StringWithSubstitutionProperty‹›* = new StringWithSubstitutionProperty(Versions.v1_0, "body")

*Defined in [card-elements.ts:3830](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3830)*

___

### `Static` headersProperty

▪ **headersProperty**: *[SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)‹›* = new SerializableObjectCollectionProperty(Versions.v1_0, "headers", HttpHeader)

*Defined in [card-elements.ts:3832](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3832)*

___

### `Static` iconUrlProperty

▪ **iconUrlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "iconUrl")

*Inherited from [Action](action.md).[iconUrlProperty](action.md#static-iconurlproperty)*

*Defined in [card-elements.ts:3342](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3342)*

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

*Defined in [card-object.ts:39](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L39)*

___

### `Static` ignoreInputValidationProperty

▪ **ignoreInputValidationProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.vNext, "ignoreInputValidation", false)

*Inherited from [Action](action.md).[ignoreInputValidationProperty](action.md#static-ignoreinputvalidationproperty)*

*Defined in [card-elements.ts:3353](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3353)*

___

### `Static` methodProperty

▪ **methodProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "method")

*Defined in [card-elements.ts:3831](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3831)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

*Defined in [serialization.ts:729](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L729)*

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities)

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

*Defined in [card-object.ts:40](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L40)*

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

*Defined in [card-elements.ts:3343](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3343)*

___

### `Static` titleProperty

▪ **titleProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "title")

*Inherited from [Action](action.md).[titleProperty](action.md#static-titleproperty)*

*Defined in [card-elements.ts:3341](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3341)*

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

*Defined in [card-object.ts:30](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L30)*

___

### `Static` urlProperty

▪ **urlProperty**: *StringWithSubstitutionProperty‹›* = new StringWithSubstitutionProperty(Versions.v1_0, "url")

*Defined in [card-elements.ts:3829](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3829)*

## Accessors

###  body

• **get body**(): *string | undefined*

*Defined in [card-elements.ts:3935](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3935)*

**Returns:** *string | undefined*

• **set body**(`value`: string | undefined): *void*

*Defined in [card-elements.ts:3939](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3939)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [Action](action.md).[hostConfig](action.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

*Defined in [card-elements.ts:3551](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3551)*

**Returns:** *[HostConfig](hostconfig.md)*

___

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

*Overrides [Action](action.md).[ignoreInputValidation](action.md#ignoreinputvalidation)*

*Defined in [card-elements.ts:3919](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3919)*

**Returns:** *boolean*

• **set ignoreInputValidation**(`value`: boolean): *void*

*Overrides [Action](action.md).[ignoreInputValidation](action.md#ignoreinputvalidation)*

*Defined in [card-elements.ts:3923](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3923)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  isPrimary

• **get isPrimary**(): *boolean*

*Inherited from [Action](action.md).[isPrimary](action.md#isprimary)*

*Defined in [card-elements.ts:3532](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3532)*

**Returns:** *boolean*

• **set isPrimary**(`value`: boolean): *void*

*Inherited from [Action](action.md).[isPrimary](action.md#isprimary)*

*Defined in [card-elements.ts:3536](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3536)*

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

*Defined in [card-elements.ts:3555](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3555)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

*Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)*

*Defined in [card-object.ts:140](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L140)*

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

*Defined in [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L53)*

**Returns:** *HostCapabilities*

___

###  url

• **get url**(): *string | undefined*

*Defined in [card-elements.ts:3927](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3927)*

**Returns:** *string | undefined*

• **set url**(`value`: string | undefined): *void*

*Defined in [card-elements.ts:3931](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3931)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

## Methods

### `Protected` addCssClasses

▸ **addCssClasses**(`element`: HTMLElement): *void*

*Inherited from [Action](action.md).[addCssClasses](action.md#protected-addcssclasses)*

*Defined in [card-elements.ts:3368](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3368)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Inherited from [Action](action.md).[execute](action.md#execute)*

*Defined in [card-elements.ts:3484](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3484)*

**Returns:** *void*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

*Inherited from [Action](action.md).[getActionById](action.md#getactionbyid)*

*Defined in [card-elements.ts:3520](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3520)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getAllInputs

▸ **getAllInputs**(): *[Input](input.md)[]*

*Inherited from [Action](action.md).[getAllInputs](action.md#getallinputs)*

*Defined in [card-elements.ts:3512](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3512)*

**Returns:** *[Input](input.md)[]*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

*Defined in [serialization.ts:922](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L922)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

###  getHref

▸ **getHref**(): *string | undefined*

*Inherited from [Action](action.md).[getHref](action.md#gethref)*

*Defined in [card-elements.ts:3402](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3402)*

**Returns:** *string | undefined*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:3893](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3893)*

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined*

*Inherited from [Action](action.md).[getReferencedInputs](action.md#getreferencedinputs)*

*Defined in [card-elements.ts:3524](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3524)*

**Returns:** *[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

*Inherited from [Action](action.md).[getResourceInformation](action.md#getresourceinformation)*

*Defined in [card-elements.ts:3516](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3516)*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootObject

▸ **getRootObject**(): *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)*

*Defined in [card-object.ts:100](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L100)*

**Returns:** *[CardObject](cardobject.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

*Defined in [serialization.ts:926](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L926)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

*Defined in [card-object.ts:45](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L45)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

*Defined in [serialization.ts:776](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L776)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

*Defined in [serialization.ts:887](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L887)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

*Defined in [serialization.ts:883](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L883)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(`allInputs`: [Input](input.md)[]): *[Dictionary](../README.md#dictionary)‹[Input](input.md)›*

*Overrides [Action](action.md).[internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)*

*Defined in [card-elements.ts:3861](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3861)*

**Parameters:**

Name | Type |
------ | ------ |
`allInputs` | [Input](input.md)[] |

**Returns:** *[Dictionary](../README.md#dictionary)‹[Input](input.md)›*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

*Defined in [serialization.ts:789](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L789)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): *void*

*Overrides [Action](action.md).[internalPrepareForExecution](action.md#protected-internalprepareforexecution)*

*Defined in [card-elements.ts:3875](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3875)*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

*Defined in [serialization.ts:821](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L821)*

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

*Defined in [card-elements.ts:3380](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3380)*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** *[Input](input.md)[]*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Overrides [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:3897](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3897)*

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

*Defined in [card-elements.ts:3410](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3410)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Overrides [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

*Defined in [card-elements.ts:3834](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3834)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): *any*

*Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)*

*Defined in [card-object.ts:70](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L70)*

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

*Defined in [card-elements.ts:3492](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3492)*

**Returns:** *boolean*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [Action](action.md).[remove](action.md#remove)*

*Defined in [card-elements.ts:3504](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3504)*

**Returns:** *boolean*

___

###  render

▸ **render**(`baseCssClass`: string): *void*

*Inherited from [Action](action.md).[render](action.md#render)*

*Defined in [card-elements.ts:3418](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3418)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`baseCssClass` | string | "ac-pushButton" |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

*Defined in [serialization.ts:901](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L901)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

*Defined in [serialization.ts:911](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L911)*

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

*Defined in [card-object.ts:88](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L88)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)*

*Defined in [card-object.ts:92](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L92)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

*Defined in [serialization.ts:780](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L780)*

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

*Defined in [card-object.ts:96](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L96)*

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [SerializationContext](serializationcontext.md)): *boolean*

*Inherited from [Action](action.md).[shouldSerialize](action.md#protected-shouldserialize)*

*Overrides [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

*Defined in [card-elements.ts:3396](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3396)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [Action](action.md).[toJSON](action.md#tojson)*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

*Defined in [card-elements.ts:3414](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3414)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

###  updateActionButtonCssStyle

▸ **updateActionButtonCssStyle**(`actionButtonElement`: HTMLElement): *void*

*Inherited from [Action](action.md).[updateActionButtonCssStyle](action.md#updateactionbuttoncssstyle)*

*Defined in [card-elements.ts:3406](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3406)*

**Parameters:**

Name | Type |
------ | ------ |
`actionButtonElement` | HTMLElement |

**Returns:** *void*

___

###  validateInputs

▸ **validateInputs**(): *[Input](input.md)‹›[]*

*Inherited from [Action](action.md).[validateInputs](action.md#validateinputs)*

*Defined in [card-elements.ts:3528](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3528)*

**Returns:** *[Input](input.md)‹›[]*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

*Defined in [card-object.ts:128](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L128)*

**Returns:** *[ValidationResults](validationresults.md)*
