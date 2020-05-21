[Adaptive Cards Javascript SDK](../README.md) › [ToggleVisibilityAction](togglevisibilityaction.md)

# Class: ToggleVisibilityAction

## Hierarchy

  ↳ [Action](action.md)

  ↳ **ToggleVisibilityAction**

## Index

### Constructors

* [constructor](togglevisibilityaction.md#constructor)

### Properties

* [_parent](togglevisibilityaction.md#protected-optional-_parent)
* [_renderedElement](togglevisibilityaction.md#protected-optional-_renderedelement)
* [iconUrl](togglevisibilityaction.md#optional-iconurl)
* [id](togglevisibilityaction.md#optional-id)
* [maxVersion](togglevisibilityaction.md#maxversion)
* [onExecute](togglevisibilityaction.md#onexecute)
* [onPreProcessPropertyValue](togglevisibilityaction.md#optional-onpreprocesspropertyvalue)
* [style](togglevisibilityaction.md#style)
* [targetElements](togglevisibilityaction.md#targetelements)
* [title](togglevisibilityaction.md#optional-title)
* [JsonTypeName](togglevisibilityaction.md#static-jsontypename)
* [iconUrlProperty](togglevisibilityaction.md#static-iconurlproperty)
* [idProperty](togglevisibilityaction.md#static-idproperty)
* [ignoreInputValidationProperty](togglevisibilityaction.md#static-ignoreinputvalidationproperty)
* [onRegisterCustomProperties](togglevisibilityaction.md#static-optional-onregistercustomproperties)
* [requiresProperty](togglevisibilityaction.md#static-requiresproperty)
* [styleProperty](togglevisibilityaction.md#static-styleproperty)
* [targetElementsProperty](togglevisibilityaction.md#static-targetelementsproperty)
* [titleProperty](togglevisibilityaction.md#static-titleproperty)
* [typeNameProperty](togglevisibilityaction.md#static-typenameproperty)

### Accessors

* [hostConfig](togglevisibilityaction.md#hostconfig)
* [ignoreInputValidation](togglevisibilityaction.md#ignoreinputvalidation)
* [isPrimary](togglevisibilityaction.md#isprimary)
* [parent](togglevisibilityaction.md#parent)
* [renderedElement](togglevisibilityaction.md#renderedelement)
* [requires](togglevisibilityaction.md#requires)

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
* [getRootObject](togglevisibilityaction.md#getrootobject)
* [getSchema](togglevisibilityaction.md#getschema)
* [getSchemaKey](togglevisibilityaction.md#protected-getschemakey)
* [getValue](togglevisibilityaction.md#protected-getvalue)
* [hasAllDefaultValues](togglevisibilityaction.md#hasalldefaultvalues)
* [hasDefaultValue](togglevisibilityaction.md#hasdefaultvalue)
* [internalGetReferencedInputs](togglevisibilityaction.md#protected-internalgetreferencedinputs)
* [internalParse](togglevisibilityaction.md#protected-internalparse)
* [internalPrepareForExecution](togglevisibilityaction.md#protected-internalprepareforexecution)
* [internalToJSON](togglevisibilityaction.md#protected-internaltojson)
* [internalValidateInputs](togglevisibilityaction.md#protected-internalvalidateinputs)
* [internalValidateProperties](togglevisibilityaction.md#internalvalidateproperties)
* [parse](togglevisibilityaction.md#parse)
* [populateSchema](togglevisibilityaction.md#protected-populateschema)
* [preProcessPropertyValue](togglevisibilityaction.md#preprocesspropertyvalue)
* [prepareForExecution](togglevisibilityaction.md#prepareforexecution)
* [remove](togglevisibilityaction.md#remove)
* [removeTargetElement](togglevisibilityaction.md#removetargetelement)
* [render](togglevisibilityaction.md#render)
* [resetDefaultValues](togglevisibilityaction.md#resetdefaultvalues)
* [setCustomProperty](togglevisibilityaction.md#setcustomproperty)
* [setParent](togglevisibilityaction.md#setparent)
* [setShouldFallback](togglevisibilityaction.md#setshouldfallback)
* [setValue](togglevisibilityaction.md#protected-setvalue)
* [shouldFallback](togglevisibilityaction.md#shouldfallback)
* [shouldSerialize](togglevisibilityaction.md#protected-shouldserialize)
* [toJSON](togglevisibilityaction.md#tojson)
* [updateActionButtonCssStyle](togglevisibilityaction.md#updateactionbuttoncssstyle)
* [validateInputs](togglevisibilityaction.md#validateinputs)
* [validateProperties](togglevisibilityaction.md#validateproperties)

## Constructors

###  constructor

\+ **new ToggleVisibilityAction**(): *[ToggleVisibilityAction](togglevisibilityaction.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

**Returns:** *[ToggleVisibilityAction](togglevisibilityaction.md)*

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

###  targetElements

• **targetElements**: *object*

*Defined in [card-elements.ts:3727](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3727)*

#### Type declaration:

* \[ **key**: *string*\]: any

___

### `Optional` title

• **title**? : *undefined | string*

*Inherited from [Action](action.md).[title](action.md#optional-title)*

*Defined in [card-elements.ts:3356](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3356)*

___

### `Static` JsonTypeName

▪ **JsonTypeName**: *"Action.ToggleVisibility"* = "Action.ToggleVisibility"

*Defined in [card-elements.ts:3733](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3733)*

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

### `Static` targetElementsProperty

▪ **targetElementsProperty**: *[CustomProperty](customproperty.md)‹object›* = new CustomProperty<PropertyBag>(
        Versions.v1_2,
        "targetElements",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let result: PropertyBag = {}

            if (Array.isArray(source[property.name])) {
                for (let item of source[property.name]) {
                    if (typeof item === "string") {
                        result[item] = undefined;
                    }
                    else if (typeof item === "object") {
                        let elementId = item["elementId"];

                        if (typeof elementId === "string") {
                            result[elementId] = Utils.parseBool(item["isVisible"]);
                        }
                    }
                }
            }

            return result;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: PropertyBag, context: BaseSerializationContext) => {
            let targetElements: any[] = [];

            for (let id of Object.keys(value)) {
                if (typeof value[id] === "boolean") {
                    targetElements.push(
                        {
                            elementId: id,
                            isVisible: value[id]
                        }
                    );
                }
                else {
                    targetElements.push(id);
                }
            }

            context.serializeArray(target, property.name, targetElements);
        },
        {},
        (sender: SerializableObject) => { return {}; })

*Defined in [card-elements.ts:3681](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3681)*

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

## Accessors

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [Action](action.md).[hostConfig](action.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

*Defined in [card-elements.ts:3551](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3551)*

**Returns:** *[HostConfig](hostconfig.md)*

___

###  ignoreInputValidation

• **get ignoreInputValidation**(): *boolean*

*Inherited from [Action](action.md).[ignoreInputValidation](action.md#ignoreinputvalidation)*

*Defined in [card-elements.ts:3547](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3547)*

**Returns:** *boolean*

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

###  addTargetElement

▸ **addTargetElement**(`elementId`: string, `isVisible`: boolean | undefined): *void*

*Defined in [card-elements.ts:3756](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3756)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`elementId` | string | - |
`isVisible` | boolean &#124; undefined | undefined |

**Returns:** *void*

___

###  execute

▸ **execute**(): *void*

*Overrides [Action](action.md).[execute](action.md#execute)*

*Defined in [card-elements.ts:3739](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3739)*

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

*Defined in [card-elements.ts:3735](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3735)*

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

*Inherited from [Action](action.md).[internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)*

*Defined in [card-elements.ts:3372](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3372)*

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

*Inherited from [Action](action.md).[internalPrepareForExecution](action.md#protected-internalprepareforexecution)*

*Defined in [card-elements.ts:3376](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3376)*

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

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-object.ts:110](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L110)*

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

*Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

*Defined in [serialization.ts:738](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L738)*

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

###  removeTargetElement

▸ **removeTargetElement**(`elementId`: string): *void*

*Defined in [card-elements.ts:3760](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L3760)*

**Parameters:**

Name | Type |
------ | ------ |
`elementId` | string |

**Returns:** *void*

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
