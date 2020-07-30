[Adaptive Cards Javascript SDK](../README.md) › [Image](image.md)

# Class: Image

## Hierarchy

  ↳ [CardElement](cardelement.md)

  ↳ **Image**

## Index

### Constructors

* [constructor](image.md#constructor)

### Properties

* [_parent](image.md#protected-optional-_parent)
* [_renderedElement](image.md#protected-optional-_renderedelement)
* [altText](image.md#optional-alttext)
* [backgroundColor](image.md#optional-backgroundcolor)
* [customCssSelector](image.md#optional-customcssselector)
* [height](image.md#height)
* [horizontalAlignment](image.md#horizontalalignment)
* [id](image.md#optional-id)
* [maxHeight](image.md#optional-maxheight)
* [maxVersion](image.md#maxversion)
* [onPreProcessPropertyValue](image.md#optional-onpreprocesspropertyvalue)
* [pixelHeight](image.md#optional-pixelheight)
* [pixelWidth](image.md#optional-pixelwidth)
* [selectAction](image.md#optional-selectaction)
* [separator](image.md#separator)
* [size](image.md#size)
* [spacing](image.md#spacing)
* [style](image.md#style)
* [url](image.md#optional-url)
* [altTextProperty](image.md#static-alttextproperty)
* [backgroundColorProperty](image.md#static-backgroundcolorproperty)
* [heightProperty](image.md#static-heightproperty)
* [horizontalAlignmentProperty](image.md#static-horizontalalignmentproperty)
* [idProperty](image.md#static-idproperty)
* [isVisibleProperty](image.md#static-isvisibleproperty)
* [langProperty](image.md#static-langproperty)
* [onRegisterCustomProperties](image.md#static-optional-onregistercustomproperties)
* [pixelHeightProperty](image.md#static-pixelheightproperty)
* [pixelWidthProperty](image.md#static-pixelwidthproperty)
* [requiresProperty](image.md#static-requiresproperty)
* [selectActionProperty](image.md#static-selectactionproperty)
* [separatorProperty](image.md#static-separatorproperty)
* [sizeProperty](image.md#static-sizeproperty)
* [spacingProperty](image.md#static-spacingproperty)
* [styleProperty](image.md#static-styleproperty)
* [typeNameProperty](image.md#static-typenameproperty)
* [urlProperty](image.md#static-urlproperty)

### Accessors

* [allowCustomPadding](image.md#protected-allowcustompadding)
* [defaultStyle](image.md#protected-defaultstyle)
* [hasVisibleSeparator](image.md#hasvisibleseparator)
* [hostConfig](image.md#hostconfig)
* [index](image.md#index)
* [isInline](image.md#isinline)
* [isInteractive](image.md#isinteractive)
* [isStandalone](image.md#isstandalone)
* [isVisible](image.md#isvisible)
* [lang](image.md#lang)
* [parent](image.md#parent)
* [renderedElement](image.md#renderedelement)
* [requires](image.md#requires)
* [separatorElement](image.md#separatorelement)
* [separatorOrientation](image.md#protected-separatororientation)
* [useDefaultSizing](image.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](image.md#protected-adjustrenderedelementsize)
* [applyPadding](image.md#protected-applypadding)
* [asString](image.md#asstring)
* [createPlaceholderElement](image.md#protected-createplaceholderelement)
* [getActionAt](image.md#getactionat)
* [getActionById](image.md#getactionbyid)
* [getActionCount](image.md#getactioncount)
* [getAllInputs](image.md#getallinputs)
* [getCustomProperty](image.md#getcustomproperty)
* [getDefaultPadding](image.md#protected-getdefaultpadding)
* [getEffectivePadding](image.md#geteffectivepadding)
* [getEffectiveStyle](image.md#geteffectivestyle)
* [getEffectiveStyleDefinition](image.md#geteffectivestyledefinition)
* [getElementById](image.md#getelementbyid)
* [getForbiddenActionTypes](image.md#getforbiddenactiontypes)
* [getHasBackground](image.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](image.md#getimmediatesurroundingpadding)
* [getJsonTypeName](image.md#getjsontypename)
* [getPadding](image.md#protected-getpadding)
* [getParentContainer](image.md#getparentcontainer)
* [getResourceInformation](image.md#getresourceinformation)
* [getRootElement](image.md#getrootelement)
* [getRootObject](image.md#getrootobject)
* [getSchema](image.md#getschema)
* [getSchemaKey](image.md#protected-getschemakey)
* [getValue](image.md#protected-getvalue)
* [hasAllDefaultValues](image.md#hasalldefaultvalues)
* [hasDefaultValue](image.md#hasdefaultvalue)
* [indexOf](image.md#indexof)
* [internalParse](image.md#protected-internalparse)
* [internalRender](image.md#protected-internalrender)
* [internalToJSON](image.md#protected-internaltojson)
* [internalValidateProperties](image.md#internalvalidateproperties)
* [isAtTheVeryBottom](image.md#isattheverybottom)
* [isAtTheVeryLeft](image.md#isattheveryleft)
* [isAtTheVeryRight](image.md#isattheveryright)
* [isAtTheVeryTop](image.md#isattheverytop)
* [isBleeding](image.md#isbleeding)
* [isBleedingAtBottom](image.md#isbleedingatbottom)
* [isBleedingAtTop](image.md#isbleedingattop)
* [isBottomElement](image.md#isbottomelement)
* [isDesignMode](image.md#isdesignmode)
* [isDisplayed](image.md#protected-isdisplayed)
* [isFirstElement](image.md#isfirstelement)
* [isHiddenDueToOverflow](image.md#ishiddenduetooverflow)
* [isLastElement](image.md#islastelement)
* [isLeftMostElement](image.md#isleftmostelement)
* [isRightMostElement](image.md#isrightmostelement)
* [isTopElement](image.md#istopelement)
* [overrideInternalRender](image.md#protected-overrideinternalrender)
* [parse](image.md#parse)
* [populateSchema](image.md#protected-populateschema)
* [preProcessPropertyValue](image.md#preprocesspropertyvalue)
* [remove](image.md#remove)
* [render](image.md#render)
* [resetDefaultValues](image.md#resetdefaultvalues)
* [setCustomProperty](image.md#setcustomproperty)
* [setPadding](image.md#protected-setpadding)
* [setParent](image.md#setparent)
* [setShouldFallback](image.md#setshouldfallback)
* [setValue](image.md#protected-setvalue)
* [shouldFallback](image.md#shouldfallback)
* [shouldSerialize](image.md#protected-shouldserialize)
* [toJSON](image.md#tojson)
* [truncateOverflow](image.md#protected-truncateoverflow)
* [undoOverflowTruncation](image.md#protected-undooverflowtruncation)
* [updateLayout](image.md#updatelayout)
* [validateProperties](image.md#validateproperties)

## Constructors

###  constructor

\+ **new Image**(): *[Image](image.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

Initializes a new SerializableObject instance.

**Returns:** *[Image](image.md)*

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

### `Optional` altText

• **altText**? : *undefined | string*

___

### `Optional` backgroundColor

• **backgroundColor**? : *undefined | string*

___

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

Specifies the height of this element withing its container. Some containers (such as Columns
or Containers with a specified `minHeight` property) may be taller than is required by their
content. In those cases, the `height` property allows for precise placement of this card element
inside of its container.

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)*

Specifies how this element is horizontally aligned within its container.

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

The id of this object.

___

### `Optional` maxHeight

• **maxHeight**? : *undefined | number*

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

### `Optional` pixelHeight

• **pixelHeight**? : *undefined | number*

___

### `Optional` pixelWidth

• **pixelWidth**? : *undefined | number*

___

### `Optional` selectAction

• **selectAction**? : *[Action](action.md)*

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

Specifies if there should be a visible separator between this element and the one before it.
A visible separator is never displayed for the first element in a container, even if
`separator` is set to `true`.

___

###  size

• **size**: *[Size](../enums/size.md)* = Enums.Size.Auto

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

Specified the space between this element and the one that comes before it.

___

###  style

• **style**: *[ImageStyle](../enums/imagestyle.md)* = Enums.ImageStyle.Default

___

### `Optional` url

• **url**? : *undefined | string*

___

### `Static` altTextProperty

▪ **altTextProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "altText")

___

### `Static` backgroundColorProperty

▪ **backgroundColorProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "backgroundColor")

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

*Inherited from [CardElement](cardelement.md).[heightProperty](cardelement.md#static-heightproperty)*

The definition of the `height` property.

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

*Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)*

The definition of the `horizontalAlignment` property.

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

The definition of the `id` property.

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

The definition of the `isVisible` property.

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

*Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-langproperty)*

The definition of the `lang` property.

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

This static event allows consuming applications to register to register custom properties to a `SerializableObject` schema.
Note that while this event technically allows properties to be removed from a schema, it is not recommended to do so.

___

### `Static` pixelHeightProperty

▪ **pixelHeightProperty**: *ImageDimensionProperty‹›* = new ImageDimensionProperty(Versions.v1_1, "height", "pixelHeight")

___

### `Static` pixelWidthProperty

▪ **pixelWidthProperty**: *ImageDimensionProperty‹›* = new ImageDimensionProperty(Versions.v1_1, "width", "pixelWidth")

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

### `Static` selectActionProperty

▪ **selectActionProperty**: *[ActionProperty](actionproperty.md)‹›* = new ActionProperty(Versions.v1_0, "selectAction", [ "Action.ShowCard" ])

___

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

The definition of the `separator` property

___

### `Static` sizeProperty

▪ **sizeProperty**: *[EnumProperty](enumproperty.md)‹[Size](../enums/size.md)›* = new EnumProperty(
        Versions.v1_0,
        "size",
        Enums.Size,
        Enums.Size.Auto)

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

*Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-spacingproperty)*

The definition of the `spacing` property.

___

### `Static` styleProperty

▪ **styleProperty**: *[EnumProperty](enumproperty.md)‹[ImageStyle](../enums/imagestyle.md)›* = new EnumProperty(
        Versions.v1_0,
        "style",
        Enums.ImageStyle,
        Enums.ImageStyle.Default)

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

___

### `Static` urlProperty

▪ **urlProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "url")

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

**Returns:** *string*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Inherited from [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

*Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

Gets a value indicating if this element is visible.

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

Sets a value indicating if this element is visible.

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

Gets the locale this card element is authored in. Each individual element can have its own
`lang` value, although in general `lang` is defined at the Adaptive Card level. If an element
doesn't have an explicit `lang` value, the `lang` of its parent is returned.

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

Sets the locale this card element is authored in.

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)*

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

*Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

*Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Overrides [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

**Returns:** *boolean*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

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

*Inherited from [CardElement](cardelement.md).[applyPadding](cardelement.md#protected-applypadding)*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

**Returns:** *string | undefined*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

Creates a placeholder DOM element in case this element is dropped. This is used only in design mode.

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *undefined | [Action](action.md)‹›*

*Overrides [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *undefined | [Action](action.md)‹›*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

*Inherited from [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

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

*Inherited from [CardElement](cardelement.md).[getDefaultPadding](cardelement.md#protected-getdefaultpadding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)*

**Returns:** *string*

___

###  getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *[ActionType](../README.md#actiontype)[]*

*Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)*

**Returns:** *[ActionType](../README.md#actiontype)[]*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

*Inherited from [CardElement](cardelement.md).[getHasBackground](cardelement.md#protected-gethasbackground)*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)*

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

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

**Returns:** *string*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)*

**Returns:** *[Container](container.md) | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

*Overrides [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)*

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

*Inherited from [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

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

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

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

*Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)*

**Returns:** *boolean*

___

### `Protected` isDisplayed

▸ **isDisplayed**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDisplayed](cardelement.md#protected-isdisplayed)*

Indicates if this crd element id displayed, e.g. if it is rendered and visible on screen.

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)*

**Returns:** *HTMLElement | undefined*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [CardElement](cardelement.md).[parse](cardelement.md#parse)*

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

*Overrides [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

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

*Inherited from [CardElement](cardelement.md).[remove](cardelement.md#remove)*

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[render](cardelement.md#render)*

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

*Inherited from [CardElement](cardelement.md).[setPadding](cardelement.md#protected-setpadding)*

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

*Inherited from [CardElement](cardelement.md).[shouldSerialize](cardelement.md#protected-shouldserialize)*

*Overrides [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [CardElement](cardelement.md).[toJSON](cardelement.md#tojson)*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Inherited from [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Inherited from [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)*

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
