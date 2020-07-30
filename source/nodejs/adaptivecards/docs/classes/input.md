[Adaptive Cards Javascript SDK](../README.md) › [Input](input.md)

# Class: Input

## Hierarchy

  ↳ [CardElement](cardelement.md)

  ↳ **Input**

  ↳ [TextInput](textinput.md)

  ↳ [ToggleInput](toggleinput.md)

  ↳ [ChoiceSetInput](choicesetinput.md)

  ↳ [NumberInput](numberinput.md)

  ↳ [DateInput](dateinput.md)

  ↳ [TimeInput](timeinput.md)

## Implements

* [IInput](../interfaces/iinput.md)

## Index

### Constructors

* [constructor](input.md#constructor)

### Properties

* [_parent](input.md#protected-optional-_parent)
* [_renderedElement](input.md#protected-optional-_renderedelement)
* [customCssSelector](input.md#optional-customcssselector)
* [errorMessage](input.md#optional-errormessage)
* [height](input.md#height)
* [horizontalAlignment](input.md#horizontalalignment)
* [id](input.md#optional-id)
* [isRequired](input.md#isrequired)
* [label](input.md#optional-label)
* [maxVersion](input.md#maxversion)
* [onPreProcessPropertyValue](input.md#optional-onpreprocesspropertyvalue)
* [onValueChanged](input.md#onvaluechanged)
* [separator](input.md#separator)
* [spacing](input.md#spacing)
* [errorMessageProperty](input.md#static-errormessageproperty)
* [heightProperty](input.md#static-heightproperty)
* [horizontalAlignmentProperty](input.md#static-horizontalalignmentproperty)
* [idProperty](input.md#static-idproperty)
* [isRequiredProperty](input.md#static-isrequiredproperty)
* [isVisibleProperty](input.md#static-isvisibleproperty)
* [labelProperty](input.md#static-labelproperty)
* [langProperty](input.md#static-langproperty)
* [onRegisterCustomProperties](input.md#static-optional-onregistercustomproperties)
* [requiresProperty](input.md#static-requiresproperty)
* [separatorProperty](input.md#static-separatorproperty)
* [spacingProperty](input.md#static-spacingproperty)
* [typeNameProperty](input.md#static-typenameproperty)

### Accessors

* [allowCustomPadding](input.md#protected-allowcustompadding)
* [defaultStyle](input.md#protected-defaultstyle)
* [hasVisibleSeparator](input.md#hasvisibleseparator)
* [hostConfig](input.md#hostconfig)
* [index](input.md#index)
* [inputControlContainerElement](input.md#protected-inputcontrolcontainerelement)
* [isInline](input.md#isinline)
* [isInteractive](input.md#isinteractive)
* [isNullable](input.md#protected-isnullable)
* [isStandalone](input.md#isstandalone)
* [isVisible](input.md#isvisible)
* [lang](input.md#lang)
* [parent](input.md#parent)
* [renderedElement](input.md#renderedelement)
* [renderedInputControlElement](input.md#protected-renderedinputcontrolelement)
* [requires](input.md#requires)
* [separatorElement](input.md#separatorelement)
* [separatorOrientation](input.md#protected-separatororientation)
* [useDefaultSizing](input.md#protected-usedefaultsizing)
* [value](input.md#value)

### Methods

* [adjustRenderedElementSize](input.md#protected-adjustrenderedelementsize)
* [applyPadding](input.md#protected-applypadding)
* [asString](input.md#asstring)
* [createPlaceholderElement](input.md#protected-createplaceholderelement)
* [focus](input.md#focus)
* [getActionAt](input.md#getactionat)
* [getActionById](input.md#getactionbyid)
* [getActionCount](input.md#getactioncount)
* [getAllInputs](input.md#getallinputs)
* [getAllLabelIds](input.md#protected-getalllabelids)
* [getCustomProperty](input.md#getcustomproperty)
* [getDefaultPadding](input.md#protected-getdefaultpadding)
* [getEffectivePadding](input.md#geteffectivepadding)
* [getEffectiveStyle](input.md#geteffectivestyle)
* [getEffectiveStyleDefinition](input.md#geteffectivestyledefinition)
* [getElementById](input.md#getelementbyid)
* [getForbiddenActionTypes](input.md#getforbiddenactiontypes)
* [getHasBackground](input.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](input.md#getimmediatesurroundingpadding)
* [getJsonTypeName](input.md#abstract-getjsontypename)
* [getPadding](input.md#protected-getpadding)
* [getParentContainer](input.md#getparentcontainer)
* [getResourceInformation](input.md#getresourceinformation)
* [getRootElement](input.md#getrootelement)
* [getRootObject](input.md#getrootobject)
* [getSchema](input.md#getschema)
* [getSchemaKey](input.md#protected-getschemakey)
* [getValue](input.md#protected-getvalue)
* [hasAllDefaultValues](input.md#hasalldefaultvalues)
* [hasDefaultValue](input.md#hasdefaultvalue)
* [indexOf](input.md#indexof)
* [internalParse](input.md#protected-internalparse)
* [internalRender](input.md#protected-abstract-internalrender)
* [internalToJSON](input.md#protected-internaltojson)
* [internalValidateProperties](input.md#internalvalidateproperties)
* [isAtTheVeryBottom](input.md#isattheverybottom)
* [isAtTheVeryLeft](input.md#isattheveryleft)
* [isAtTheVeryRight](input.md#isattheveryright)
* [isAtTheVeryTop](input.md#isattheverytop)
* [isBleeding](input.md#isbleeding)
* [isBleedingAtBottom](input.md#isbleedingatbottom)
* [isBleedingAtTop](input.md#isbleedingattop)
* [isBottomElement](input.md#isbottomelement)
* [isDesignMode](input.md#isdesignmode)
* [isDisplayed](input.md#protected-isdisplayed)
* [isFirstElement](input.md#isfirstelement)
* [isHiddenDueToOverflow](input.md#ishiddenduetooverflow)
* [isLastElement](input.md#islastelement)
* [isLeftMostElement](input.md#isleftmostelement)
* [isRightMostElement](input.md#isrightmostelement)
* [isSet](input.md#abstract-isset)
* [isTopElement](input.md#istopelement)
* [isValid](input.md#isvalid)
* [overrideInternalRender](input.md#protected-overrideinternalrender)
* [parse](input.md#parse)
* [populateSchema](input.md#protected-populateschema)
* [preProcessPropertyValue](input.md#preprocesspropertyvalue)
* [remove](input.md#remove)
* [render](input.md#render)
* [resetDefaultValues](input.md#resetdefaultvalues)
* [resetValidationFailureCue](input.md#protected-resetvalidationfailurecue)
* [setCustomProperty](input.md#setcustomproperty)
* [setPadding](input.md#protected-setpadding)
* [setParent](input.md#setparent)
* [setShouldFallback](input.md#setshouldfallback)
* [setValue](input.md#protected-setvalue)
* [shouldFallback](input.md#shouldfallback)
* [shouldSerialize](input.md#protected-shouldserialize)
* [showValidationErrorMessage](input.md#protected-showvalidationerrormessage)
* [toJSON](input.md#tojson)
* [truncateOverflow](input.md#protected-truncateoverflow)
* [undoOverflowTruncation](input.md#protected-undooverflowtruncation)
* [updateInputControlAriaLabelledBy](input.md#protected-updateinputcontrolarialabelledby)
* [updateLayout](input.md#updatelayout)
* [validateProperties](input.md#validateproperties)
* [validateValue](input.md#validatevalue)
* [valueChanged](input.md#protected-valuechanged)

## Constructors

###  constructor

\+ **new Input**(): *[Input](input.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

Initializes a new SerializableObject instance.

**Returns:** *[Input](input.md)*

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

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

___

### `Optional` errorMessage

• **errorMessage**? : *undefined | string*

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

*Implementation of [IInput](../interfaces/iinput.md).[id](../interfaces/iinput.md#optional-id)*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

The id of this object.

___

###  isRequired

• **isRequired**: *boolean*

___

### `Optional` label

• **label**? : *undefined | string*

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

###  onValueChanged

• **onValueChanged**: *function*

#### Type declaration:

▸ (`sender`: [Input](input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Input](input.md) |

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

Specifies if there should be a visible separator between this element and the one before it.
A visible separator is never displayed for the first element in a container, even if
`separator` is set to `true`.

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

Specified the space between this element and the one that comes before it.

___

### `Static` errorMessageProperty

▪ **errorMessageProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_3, "errorMessage", true)

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

### `Static` isRequiredProperty

▪ **isRequiredProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_3, "isRequired", false)

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

The definition of the `isVisible` property.

___

### `Static` labelProperty

▪ **labelProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_3, "label", true)

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

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

The definition of the `separator` property

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

### `Protected` inputControlContainerElement

• **get inputControlContainerElement**(): *HTMLElement*

**Returns:** *HTMLElement*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Overrides [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

**Returns:** *boolean*

___

### `Protected` isNullable

• **get isNullable**(): *boolean*

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

### `Protected` renderedInputControlElement

• **get renderedInputControlElement**(): *HTMLElement | undefined*

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

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

**Returns:** *boolean*

___

###  value

• **get value**(): *any*

**Returns:** *any*

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

###  focus

▸ **focus**(): *void*

**Returns:** *void*

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

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

### `Protected` getAllLabelIds

▸ **getAllLabelIds**(): *string[]*

**Returns:** *string[]*

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

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Inherited from [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

Gets the JSON type name of this object. The JSON type name is the type as used in raw card payloads,
e.g. "AdaptiveCard", "Action.OpenUrl", "Input.Text", etc.

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

*Inherited from [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

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

### `Protected` `Abstract` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

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

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Overrides [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

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

### `Abstract` isSet

▸ **isSet**(): *boolean*

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

###  isValid

▸ **isValid**(): *boolean*

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

*Overrides [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)*

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

### `Protected` resetValidationFailureCue

▸ **resetValidationFailureCue**(): *void*

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

### `Protected` showValidationErrorMessage

▸ **showValidationErrorMessage**(): *void*

**Returns:** *void*

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

### `Protected` updateInputControlAriaLabelledBy

▸ **updateInputControlAriaLabelledBy**(): *void*

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

___

###  validateValue

▸ **validateValue**(): *boolean*

*Implementation of [IInput](../interfaces/iinput.md)*

**Returns:** *boolean*

___

### `Protected` valueChanged

▸ **valueChanged**(): *void*

**Returns:** *void*
