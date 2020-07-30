[Adaptive Cards Javascript SDK](../README.md) › [CardElement](cardelement.md)

# Class: CardElement

Representd the base card element class. All actual card elements (TextBlock, Image, etc.) extend CardElement.
Custom card element classes must extend CardElement.

## Hierarchy

  ↳ [CardObject](cardobject.md)

  ↳ **CardElement**

  ↳ [BaseTextBlock](basetextblock.md)

  ↳ [RichTextBlock](richtextblock.md)

  ↳ [FactSet](factset.md)

  ↳ [Image](image.md)

  ↳ [CardElementContainer](cardelementcontainer.md)

  ↳ [Media](media.md)

  ↳ [Input](input.md)

  ↳ [ActionSet](actionset.md)

## Index

### Constructors

* [constructor](cardelement.md#constructor)

### Properties

* [_parent](cardelement.md#protected-optional-_parent)
* [_renderedElement](cardelement.md#protected-optional-_renderedelement)
* [customCssSelector](cardelement.md#optional-customcssselector)
* [height](cardelement.md#height)
* [horizontalAlignment](cardelement.md#horizontalalignment)
* [id](cardelement.md#optional-id)
* [maxVersion](cardelement.md#maxversion)
* [onPreProcessPropertyValue](cardelement.md#optional-onpreprocesspropertyvalue)
* [separator](cardelement.md#separator)
* [spacing](cardelement.md#spacing)
* [heightProperty](cardelement.md#static-heightproperty)
* [horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)
* [idProperty](cardelement.md#static-idproperty)
* [isVisibleProperty](cardelement.md#static-isvisibleproperty)
* [langProperty](cardelement.md#static-langproperty)
* [onRegisterCustomProperties](cardelement.md#static-optional-onregistercustomproperties)
* [requiresProperty](cardelement.md#static-requiresproperty)
* [separatorProperty](cardelement.md#static-separatorproperty)
* [spacingProperty](cardelement.md#static-spacingproperty)
* [typeNameProperty](cardelement.md#static-typenameproperty)

### Accessors

* [allowCustomPadding](cardelement.md#protected-allowcustompadding)
* [defaultStyle](cardelement.md#protected-defaultstyle)
* [hasVisibleSeparator](cardelement.md#hasvisibleseparator)
* [hostConfig](cardelement.md#hostconfig)
* [index](cardelement.md#index)
* [isInline](cardelement.md#isinline)
* [isInteractive](cardelement.md#isinteractive)
* [isStandalone](cardelement.md#isstandalone)
* [isVisible](cardelement.md#isvisible)
* [lang](cardelement.md#lang)
* [parent](cardelement.md#parent)
* [renderedElement](cardelement.md#renderedelement)
* [requires](cardelement.md#requires)
* [separatorElement](cardelement.md#separatorelement)
* [separatorOrientation](cardelement.md#protected-separatororientation)
* [useDefaultSizing](cardelement.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)
* [applyPadding](cardelement.md#protected-applypadding)
* [asString](cardelement.md#asstring)
* [createPlaceholderElement](cardelement.md#protected-createplaceholderelement)
* [getActionAt](cardelement.md#getactionat)
* [getActionById](cardelement.md#getactionbyid)
* [getActionCount](cardelement.md#getactioncount)
* [getAllInputs](cardelement.md#getallinputs)
* [getCustomProperty](cardelement.md#getcustomproperty)
* [getDefaultPadding](cardelement.md#protected-getdefaultpadding)
* [getEffectivePadding](cardelement.md#geteffectivepadding)
* [getEffectiveStyle](cardelement.md#geteffectivestyle)
* [getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)
* [getElementById](cardelement.md#getelementbyid)
* [getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)
* [getHasBackground](cardelement.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)
* [getJsonTypeName](cardelement.md#abstract-getjsontypename)
* [getPadding](cardelement.md#protected-getpadding)
* [getParentContainer](cardelement.md#getparentcontainer)
* [getResourceInformation](cardelement.md#getresourceinformation)
* [getRootElement](cardelement.md#getrootelement)
* [getRootObject](cardelement.md#getrootobject)
* [getSchema](cardelement.md#getschema)
* [getSchemaKey](cardelement.md#protected-getschemakey)
* [getValue](cardelement.md#protected-getvalue)
* [hasAllDefaultValues](cardelement.md#hasalldefaultvalues)
* [hasDefaultValue](cardelement.md#hasdefaultvalue)
* [indexOf](cardelement.md#indexof)
* [internalParse](cardelement.md#protected-internalparse)
* [internalRender](cardelement.md#protected-abstract-internalrender)
* [internalToJSON](cardelement.md#protected-internaltojson)
* [internalValidateProperties](cardelement.md#internalvalidateproperties)
* [isAtTheVeryBottom](cardelement.md#isattheverybottom)
* [isAtTheVeryLeft](cardelement.md#isattheveryleft)
* [isAtTheVeryRight](cardelement.md#isattheveryright)
* [isAtTheVeryTop](cardelement.md#isattheverytop)
* [isBleeding](cardelement.md#isbleeding)
* [isBleedingAtBottom](cardelement.md#isbleedingatbottom)
* [isBleedingAtTop](cardelement.md#isbleedingattop)
* [isBottomElement](cardelement.md#isbottomelement)
* [isDesignMode](cardelement.md#isdesignmode)
* [isDisplayed](cardelement.md#protected-isdisplayed)
* [isFirstElement](cardelement.md#isfirstelement)
* [isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)
* [isLastElement](cardelement.md#islastelement)
* [isLeftMostElement](cardelement.md#isleftmostelement)
* [isRightMostElement](cardelement.md#isrightmostelement)
* [isTopElement](cardelement.md#istopelement)
* [overrideInternalRender](cardelement.md#protected-overrideinternalrender)
* [parse](cardelement.md#parse)
* [populateSchema](cardelement.md#protected-populateschema)
* [preProcessPropertyValue](cardelement.md#preprocesspropertyvalue)
* [remove](cardelement.md#remove)
* [render](cardelement.md#render)
* [resetDefaultValues](cardelement.md#resetdefaultvalues)
* [setCustomProperty](cardelement.md#setcustomproperty)
* [setPadding](cardelement.md#protected-setpadding)
* [setParent](cardelement.md#setparent)
* [setShouldFallback](cardelement.md#setshouldfallback)
* [setValue](cardelement.md#protected-setvalue)
* [shouldFallback](cardelement.md#shouldfallback)
* [shouldSerialize](cardelement.md#protected-shouldserialize)
* [toJSON](cardelement.md#tojson)
* [truncateOverflow](cardelement.md#protected-truncateoverflow)
* [undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)
* [updateLayout](cardelement.md#updatelayout)
* [validateProperties](cardelement.md#validateproperties)

## Constructors

###  constructor

\+ **new CardElement**(): *[CardElement](cardelement.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

Initializes a new SerializableObject instance.

**Returns:** *[CardElement](cardelement.md)*

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

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

Specifies the height of this element withing its container. Some containers (such as Columns
or Containers with a specified `minHeight` property) may be taller than is required by their
content. In those cases, the `height` property allows for precise placement of this card element
inside of its container.

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

Specifies how this element is horizontally aligned within its container.

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

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

This event allows a consuming application to pre-process the value of a property before it is rendered.
This is useful for text processing, for instance.

___

###  separator

• **separator**: *boolean*

Specifies if there should be a visible separator between this element and the one before it.
A visible separator is never displayed for the first element in a container, even if
`separator` is set to `true`.

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

Specified the space between this element and the one that comes before it.

___

### `Static` heightProperty

▪ **heightProperty**: *[ValueSetProperty](valuesetproperty.md)‹›* = new ValueSetProperty(
        Versions.v1_1,
        "height",
        [
            { value: "auto" },
            { value: "stretch" }
        ],
        "auto")

The definition of the `height` property.

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

The definition of the `horizontalAlignment` property.

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

The definition of the `id` property.

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

The definition of the `isVisible` property.

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

The definition of the `lang` property.

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

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

The definition of the `separator` property

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

The definition of the `spacing` property.

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

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

**Returns:** *string*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

Gets a value indicating if this element is visible.

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

Sets a value indicating if this element is visible.

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

Gets the locale this card element is authored in. Each individual element can have its own
`lang` value, although in general `lang` is defined at the Adaptive Card level. If an element
doesn't have an explicit `lang` value, the `lang` of its parent is returned.

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

Sets the locale this card element is authored in.

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

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

___

###  separatorElement

• **get separatorElement**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

**Returns:** *boolean*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

Adjusts the size of the rendered DOM element (for example, to aply the `height` property). Derived
classes may override this method if theyur have specific size adjustment needs. This method is called
each time a card element is rendered.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`renderedElement` | HTMLElement | The rendered DOM element to adjust the size of.  |

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

**Returns:** *string | undefined*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

Creates a placeholder DOM element in case this element is dropped. This is used only in design mode.

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

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

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): *[PaddingDefinition](paddingdefinition.md)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

___

###  getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *[ActionType](../README.md#actiontype)[]*

**Returns:** *[ActionType](../README.md#actiontype)[]*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`result` | [PaddingDefinition](paddingdefinition.md) | - |
`processTop` | boolean | true |
`processRight` | boolean | true |
`processBottom` | boolean | true |
`processLeft` | boolean | true |

**Returns:** *void*

___

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Inherited from [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

Gets the JSON type name of this object. The JSON type name is the type as used in raw card payloads,
e.g. "AdaptiveCard", "Action.OpenUrl", "Input.Text", etc.

**Returns:** *string*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md) | undefined*

**Returns:** *[Container](container.md) | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

**Returns:** *[CardElement](cardelement.md)*

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

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): *number*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

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

### `Protected` `Abstract` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

Effectively renders the card element. Derived classes must override `internalRender`.

**Returns:** *HTMLElement | undefined*

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

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

___

### `Protected` isDisplayed

▸ **isDisplayed**(): *boolean*

Indicates if this crd element id displayed, e.g. if it is rendered and visible on screen.

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

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

###  remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

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

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

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

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | true |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

Validates the values of this object's properties.

**`results`** The validation results to add potential failures to.

**Returns:** *[ValidationResults](validationresults.md)*
