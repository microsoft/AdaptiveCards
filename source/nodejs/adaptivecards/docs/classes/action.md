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

### Constructors

* [constructor](action.md#constructor)

### Properties

* [_parent](action.md#protected-optional-_parent)
* [_renderedElement](action.md#protected-optional-_renderedelement)
* [iconUrl](action.md#optional-iconurl)
* [id](action.md#optional-id)
* [maxVersion](action.md#maxversion)
* [onExecute](action.md#onexecute)
* [onPreProcessPropertyValue](action.md#optional-onpreprocesspropertyvalue)
* [style](action.md#style)
* [title](action.md#optional-title)
* [iconUrlProperty](action.md#static-iconurlproperty)
* [idProperty](action.md#static-idproperty)
* [ignoreInputValidationProperty](action.md#static-ignoreinputvalidationproperty)
* [onRegisterCustomProperties](action.md#static-optional-onregistercustomproperties)
* [requiresProperty](action.md#static-requiresproperty)
* [styleProperty](action.md#static-styleproperty)
* [titleProperty](action.md#static-titleproperty)
* [typeNameProperty](action.md#static-typenameproperty)

### Accessors

* [hostConfig](action.md#hostconfig)
* [ignoreInputValidation](action.md#ignoreinputvalidation)
* [isPrimary](action.md#isprimary)
* [parent](action.md#parent)
* [renderedElement](action.md#renderedelement)
* [requires](action.md#requires)

### Methods

* [addCssClasses](action.md#protected-addcssclasses)
* [execute](action.md#execute)
* [getActionById](action.md#getactionbyid)
* [getAllInputs](action.md#getallinputs)
* [getAriaRole](action.md#getariarole)
* [getCustomProperty](action.md#getcustomproperty)
* [getHref](action.md#gethref)
* [getJsonTypeName](action.md#abstract-getjsontypename)
* [getReferencedInputs](action.md#getreferencedinputs)
* [getResourceInformation](action.md#getresourceinformation)
* [getRootObject](action.md#getrootobject)
* [getSchema](action.md#getschema)
* [getSchemaKey](action.md#protected-getschemakey)
* [getValue](action.md#protected-getvalue)
* [hasAllDefaultValues](action.md#hasalldefaultvalues)
* [hasDefaultValue](action.md#hasdefaultvalue)
* [internalGetReferencedInputs](action.md#protected-internalgetreferencedinputs)
* [internalParse](action.md#protected-internalparse)
* [internalPrepareForExecution](action.md#protected-internalprepareforexecution)
* [internalToJSON](action.md#protected-internaltojson)
* [internalValidateInputs](action.md#protected-internalvalidateinputs)
* [internalValidateProperties](action.md#internalvalidateproperties)
* [parse](action.md#parse)
* [populateSchema](action.md#protected-populateschema)
* [preProcessPropertyValue](action.md#preprocesspropertyvalue)
* [prepareForExecution](action.md#prepareforexecution)
* [remove](action.md#remove)
* [render](action.md#render)
* [resetDefaultValues](action.md#resetdefaultvalues)
* [setCustomProperty](action.md#setcustomproperty)
* [setParent](action.md#setparent)
* [setShouldFallback](action.md#setshouldfallback)
* [setValue](action.md#protected-setvalue)
* [shouldFallback](action.md#shouldfallback)
* [shouldSerialize](action.md#protected-shouldserialize)
* [toJSON](action.md#tojson)
* [updateActionButtonCssStyle](action.md#updateactionbuttoncssstyle)
* [validateInputs](action.md#validateinputs)
* [validateProperties](action.md#validateproperties)

## Constructors

###  constructor

\+ **new Action**(): *[Action](action.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

Initializes a new SerializableObject instance.

**Returns:** *[Action](action.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

The parent of this object. Do NOT set explicitly. This field is handled internally.

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

The rendered DOM element for this object. Do NOT set explicitly. This field is handled internally.

___

### `Optional` iconUrl

• **iconUrl**? : *undefined | string*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

The id of this object.

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

The maximum Adaptive Card schema version supported by serializable objects.

___

###  onExecute

• **onExecute**: *function*

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

This event allows a consuming application to pre-process the value of a property before it is rendered.
This is useful for text processing, for instance.

___

###  style

• **style**: *string* = Enums.ActionStyle.Default

___

### `Optional` title

• **title**? : *undefined | string*

___

### `Static` iconUrlProperty

▪ **iconUrlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "iconUrl")

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

The definition of the `id` property.

___

### `Static` ignoreInputValidationProperty

▪ **ignoreInputValidationProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_3, "ignoreInputValidation", false)

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

This static event allows consuming applications to register to register custom properties to a `SerializableObject` schema.
Note that while this event technically allows properties to be removed from a schema, it is not recommended to do so.

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities())

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

The definition of the `requires` property.

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

___

### `Static` titleProperty

▪ **titleProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "title")

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

The definition of the `type` property

## Accessors

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Returns:** *[HostConfig](hostconfig.md)*

___

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

• **get parent**(): *[CardElement](cardelement.md) | undefined*

*Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

*Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)*

Gets the rendered DOM element for this object. `renderedElement` is initialized after the object has been rendered.

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

The list of capabilities required by this object.

**Returns:** *HostCapabilities*

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

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

###  getAriaRole

▸ **getAriaRole**(): *string*

**Returns:** *string*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

Gets the value of a custom property.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | The custom property to get the value of. |

**Returns:** *any*

The value of the custom property.

___

###  getHref

▸ **getHref**(): *string | undefined*

**Returns:** *string | undefined*

___

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Inherited from [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

Gets the JSON type name of this object. The JSON type name is the type as used in raw card payloads,
e.g. "AdaptiveCard", "Action.OpenUrl", "Input.Text", etc.

**Returns:** *string*

___

###  getReferencedInputs

▸ **getReferencedInputs**(): *[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined*

**Returns:** *[Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootObject

▸ **getRootObject**(): *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)*

Walks the parent tree to find the root object this object is a child of. Typically the root object is the Adaptive Card.

**Returns:** *[CardObject](cardobject.md)*

The root object this object is a child of. If this object doesn't have a parent, then it is its own root.

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

Gets the schema of this serializable object.

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

The schema of this serializable object.

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

Gets the value of the specified property.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to get the value of. |

**Returns:** *any*

The value of the property.

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

Determines if all the properties of this serializable object have their default values.

**Returns:** *boolean*

`true` if all the properties have their default value, `false` otherwise.

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

Determines if the specified property has its default value.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to check. |

**Returns:** *boolean*

`true` if the property has its default value, `false` otherwise.

___

### `Protected` internalGetReferencedInputs

▸ **internalGetReferencedInputs**(): *[Dictionary](../README.md#dictionary)‹[Input](input.md)›*

**Returns:** *[Dictionary](../README.md#dictionary)‹[Input](input.md)›*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

Parses the source object and initializes this serializable object's properties. Descendent classes
should typically not override this method.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) | The source object to parse. |
`context` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context.  |

**Returns:** *void*

___

### `Protected` internalPrepareForExecution

▸ **internalPrepareForExecution**(`inputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

Serializes this serializable object to the specified target object.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) | The target object to sets the fields of. |
`context` | [BaseSerializationContext](baseserializationcontext.md) | The serialization context.  |

**Returns:** *void*

___

### `Protected` internalValidateInputs

▸ **internalValidateInputs**(`referencedInputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)› | undefined): *[Input](input.md)[]*

**Parameters:**

Name | Type |
------ | ------ |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› &#124; undefined |

**Returns:** *[Input](input.md)[]*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`results`: [ValidationResults](validationresults.md)): *void*

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

Validates the values of this object's properties. Derived classes should override `internalValidateProperties` to
implement their own property validation logic. Always call `super.internalValidateProperties(results)`. Do not call this
method directly. Instead, call `validateProperties`.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`results` | [ValidationResults](validationresults.md) | The validation results to add potential failures to.  |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

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

Populates a schema with properties by looking up publis static fields that are of type PropertyDefinition or derived.
There is in general no need for a descendant class to override this method, unless that class uses custom schema
population logic. When overriding this method, always call `super.populateSchema(schema)`

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) | The schema instance to populate.  |

**Returns:** *void*

___

###  preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): *any*

*Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)*

Pre-processes the value of a property by invoking the `onPreProcessPropertyValue` event, if set.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to pre-process the value of. |
`propertyValue?` | any | The current value of the property. This value might itself be a processed version of the property's raw value. |

**Returns:** *any*

The processed value of the property.

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

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

Resets this object by reverting all its properties to their default values.

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

Allows a consuming application to set custom properties on any serializable object instance.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`name` | string | The name of the custom property to set. |
`value` | any | The value of the custom property.  |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): *void*

*Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)*

Sets the parent of this object. Derived classes that hold references to other CardObject instances MUST sets those
objects' parent.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`value` | [CardObject](cardobject.md) &#124; undefined | The new parent of this object.  |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)*

Marks this object for fallback. This method is used during deserialization and has no effect in other contexts. Do not use.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`value` | boolean | `true` to mark this object for fallback.  |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

Sets the value of a property.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) | The property to set the value of. |
`value` | any | The new value of the property.  |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)*

Indicates if this object should fall back, for example if its required capabilities are not satisfied. This method is
only meaningful during deserialization.

**`returns&#x60;true&#x60;`** if this object should fall back, `false` otherwise.

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [SerializationContext](serializationcontext.md)): *boolean*

*Overrides [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

###  updateActionButtonCssStyle

▸ **updateActionButtonCssStyle**(`actionButtonElement`: HTMLElement, `buttonState`: ActionButtonState): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`actionButtonElement` | HTMLElement | - |
`buttonState` | ActionButtonState | ActionButtonState.Normal |

**Returns:** *void*

___

###  validateInputs

▸ **validateInputs**(): *[Input](input.md)[]*

Validates the inputs associated with this action.

**Returns:** *[Input](input.md)[]*

A list of inputs that failed validation, or an empty array if no input failed validation.

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

Validates the values of this object's properties.

**`results`** The validation results to add potential failures to.

**Returns:** *[ValidationResults](validationresults.md)*
