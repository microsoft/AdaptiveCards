[Adaptive Cards Javascript SDK](../README.md) › [DateInput](dateinput.md)

# Class: DateInput

## Hierarchy

  ↳ [Input](input.md)

  ↳ **DateInput**

## Implements

* [IInput](../interfaces/iinput.md)

## Index

### Constructors

* [constructor](dateinput.md#constructor)

### Properties

* [_parent](dateinput.md#protected-optional-_parent)
* [_renderedElement](dateinput.md#protected-optional-_renderedelement)
* [customCssSelector](dateinput.md#optional-customcssselector)
* [defaultValue](dateinput.md#optional-defaultvalue)
* [errorMessage](dateinput.md#optional-errormessage)
* [height](dateinput.md#height)
* [horizontalAlignment](dateinput.md#horizontalalignment)
* [id](dateinput.md#optional-id)
* [isRequired](dateinput.md#isrequired)
* [label](dateinput.md#optional-label)
* [max](dateinput.md#optional-max)
* [maxVersion](dateinput.md#maxversion)
* [min](dateinput.md#optional-min)
* [onPreProcessPropertyValue](dateinput.md#optional-onpreprocesspropertyvalue)
* [onValueChanged](dateinput.md#onvaluechanged)
* [placeholder](dateinput.md#optional-placeholder)
* [separator](dateinput.md#separator)
* [spacing](dateinput.md#spacing)
* [errorMessageProperty](dateinput.md#static-errormessageproperty)
* [heightProperty](dateinput.md#static-heightproperty)
* [horizontalAlignmentProperty](dateinput.md#static-horizontalalignmentproperty)
* [idProperty](dateinput.md#static-idproperty)
* [isRequiredProperty](dateinput.md#static-isrequiredproperty)
* [isVisibleProperty](dateinput.md#static-isvisibleproperty)
* [labelProperty](dateinput.md#static-labelproperty)
* [langProperty](dateinput.md#static-langproperty)
* [maxProperty](dateinput.md#static-maxproperty)
* [minProperty](dateinput.md#static-minproperty)
* [onRegisterCustomProperties](dateinput.md#static-optional-onregistercustomproperties)
* [placeholderProperty](dateinput.md#static-placeholderproperty)
* [requiresProperty](dateinput.md#static-requiresproperty)
* [separatorProperty](dateinput.md#static-separatorproperty)
* [spacingProperty](dateinput.md#static-spacingproperty)
* [typeNameProperty](dateinput.md#static-typenameproperty)
* [valueProperty](dateinput.md#static-valueproperty)

### Accessors

* [allowCustomPadding](dateinput.md#protected-allowcustompadding)
* [defaultStyle](dateinput.md#protected-defaultstyle)
* [hasVisibleSeparator](dateinput.md#hasvisibleseparator)
* [hostConfig](dateinput.md#hostconfig)
* [index](dateinput.md#index)
* [inputControlContainerElement](dateinput.md#protected-inputcontrolcontainerelement)
* [isInline](dateinput.md#isinline)
* [isInteractive](dateinput.md#isinteractive)
* [isNullable](dateinput.md#protected-isnullable)
* [isStandalone](dateinput.md#isstandalone)
* [isVisible](dateinput.md#isvisible)
* [lang](dateinput.md#lang)
* [parent](dateinput.md#parent)
* [renderedElement](dateinput.md#renderedelement)
* [renderedInputControlElement](dateinput.md#protected-renderedinputcontrolelement)
* [requires](dateinput.md#requires)
* [separatorElement](dateinput.md#separatorelement)
* [separatorOrientation](dateinput.md#protected-separatororientation)
* [useDefaultSizing](dateinput.md#protected-usedefaultsizing)
* [value](dateinput.md#value)

### Methods

* [adjustRenderedElementSize](dateinput.md#protected-adjustrenderedelementsize)
* [applyPadding](dateinput.md#protected-applypadding)
* [asString](dateinput.md#asstring)
* [createPlaceholderElement](dateinput.md#protected-createplaceholderelement)
* [focus](dateinput.md#focus)
* [getActionAt](dateinput.md#getactionat)
* [getActionById](dateinput.md#getactionbyid)
* [getActionCount](dateinput.md#getactioncount)
* [getAllInputs](dateinput.md#getallinputs)
* [getAllLabelIds](dateinput.md#protected-getalllabelids)
* [getCustomProperty](dateinput.md#getcustomproperty)
* [getDefaultPadding](dateinput.md#protected-getdefaultpadding)
* [getEffectivePadding](dateinput.md#geteffectivepadding)
* [getEffectiveStyle](dateinput.md#geteffectivestyle)
* [getEffectiveStyleDefinition](dateinput.md#geteffectivestyledefinition)
* [getElementById](dateinput.md#getelementbyid)
* [getForbiddenActionTypes](dateinput.md#getforbiddenactiontypes)
* [getHasBackground](dateinput.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](dateinput.md#getimmediatesurroundingpadding)
* [getJsonTypeName](dateinput.md#getjsontypename)
* [getPadding](dateinput.md#protected-getpadding)
* [getParentContainer](dateinput.md#getparentcontainer)
* [getResourceInformation](dateinput.md#getresourceinformation)
* [getRootElement](dateinput.md#getrootelement)
* [getRootObject](dateinput.md#getrootobject)
* [getSchema](dateinput.md#getschema)
* [getSchemaKey](dateinput.md#protected-getschemakey)
* [getValue](dateinput.md#protected-getvalue)
* [hasAllDefaultValues](dateinput.md#hasalldefaultvalues)
* [hasDefaultValue](dateinput.md#hasdefaultvalue)
* [indexOf](dateinput.md#indexof)
* [internalParse](dateinput.md#protected-internalparse)
* [internalRender](dateinput.md#protected-internalrender)
* [internalToJSON](dateinput.md#protected-internaltojson)
* [internalValidateProperties](dateinput.md#internalvalidateproperties)
* [isAtTheVeryBottom](dateinput.md#isattheverybottom)
* [isAtTheVeryLeft](dateinput.md#isattheveryleft)
* [isAtTheVeryRight](dateinput.md#isattheveryright)
* [isAtTheVeryTop](dateinput.md#isattheverytop)
* [isBleeding](dateinput.md#isbleeding)
* [isBleedingAtBottom](dateinput.md#isbleedingatbottom)
* [isBleedingAtTop](dateinput.md#isbleedingattop)
* [isBottomElement](dateinput.md#isbottomelement)
* [isDesignMode](dateinput.md#isdesignmode)
* [isDisplayed](dateinput.md#protected-isdisplayed)
* [isFirstElement](dateinput.md#isfirstelement)
* [isHiddenDueToOverflow](dateinput.md#ishiddenduetooverflow)
* [isLastElement](dateinput.md#islastelement)
* [isLeftMostElement](dateinput.md#isleftmostelement)
* [isRightMostElement](dateinput.md#isrightmostelement)
* [isSet](dateinput.md#isset)
* [isTopElement](dateinput.md#istopelement)
* [isValid](dateinput.md#isvalid)
* [overrideInternalRender](dateinput.md#protected-overrideinternalrender)
* [parse](dateinput.md#parse)
* [populateSchema](dateinput.md#protected-populateschema)
* [preProcessPropertyValue](dateinput.md#preprocesspropertyvalue)
* [remove](dateinput.md#remove)
* [render](dateinput.md#render)
* [resetDefaultValues](dateinput.md#resetdefaultvalues)
* [resetValidationFailureCue](dateinput.md#protected-resetvalidationfailurecue)
* [setCustomProperty](dateinput.md#setcustomproperty)
* [setPadding](dateinput.md#protected-setpadding)
* [setParent](dateinput.md#setparent)
* [setShouldFallback](dateinput.md#setshouldfallback)
* [setValue](dateinput.md#protected-setvalue)
* [shouldFallback](dateinput.md#shouldfallback)
* [shouldSerialize](dateinput.md#protected-shouldserialize)
* [showValidationErrorMessage](dateinput.md#protected-showvalidationerrormessage)
* [toJSON](dateinput.md#tojson)
* [truncateOverflow](dateinput.md#protected-truncateoverflow)
* [undoOverflowTruncation](dateinput.md#protected-undooverflowtruncation)
* [updateInputControlAriaLabelledBy](dateinput.md#protected-updateinputcontrolarialabelledby)
* [updateLayout](dateinput.md#updatelayout)
* [validateProperties](dateinput.md#validateproperties)
* [validateValue](dateinput.md#validatevalue)
* [valueChanged](dateinput.md#protected-valuechanged)

## Constructors

###  constructor

\+ **new DateInput**(): *[DateInput](dateinput.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Returns:** *[DateInput](dateinput.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

___

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

___

### `Optional` defaultValue

• **defaultValue**? : *undefined | string*

___

### `Optional` errorMessage

• **errorMessage**? : *undefined | string*

*Inherited from [Input](input.md).[errorMessage](input.md#optional-errormessage)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)*

___

### `Optional` id

• **id**? : *undefined | string*

*Implementation of [IInput](../interfaces/iinput.md).[id](../interfaces/iinput.md#optional-id)*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

___

###  isRequired

• **isRequired**: *boolean*

*Inherited from [Input](input.md).[isRequired](input.md#isrequired)*

___

### `Optional` label

• **label**? : *undefined | string*

*Inherited from [Input](input.md).[label](input.md#optional-label)*

___

### `Optional` max

• **max**? : *undefined | string*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

### `Optional` min

• **min**? : *undefined | string*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

___

###  onValueChanged

• **onValueChanged**: *function*

*Inherited from [Input](input.md).[onValueChanged](input.md#onvaluechanged)*

#### Type declaration:

▸ (`sender`: [Input](input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Input](input.md) |

___

### `Optional` placeholder

• **placeholder**? : *undefined | string*

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

___

### `Static` errorMessageProperty

▪ **errorMessageProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_3, "errorMessage", true)

*Inherited from [Input](input.md).[errorMessageProperty](input.md#static-errormessageproperty)*

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

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

*Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)*

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

___

### `Static` isRequiredProperty

▪ **isRequiredProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_3, "isRequired", false)

*Inherited from [Input](input.md).[isRequiredProperty](input.md#static-isrequiredproperty)*

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

___

### `Static` labelProperty

▪ **labelProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_3, "label", true)

*Inherited from [Input](input.md).[labelProperty](input.md#static-labelproperty)*

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

*Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-langproperty)*

___

### `Static` maxProperty

▪ **maxProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "max")

___

### `Static` minProperty

▪ **minProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "min")

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

___

### `Static` placeholderProperty

▪ **placeholderProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "placeholder")

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities())

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

___

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

*Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-spacingproperty)*

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

### `Static` valueProperty

▪ **valueProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "value")

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

*Inherited from [Input](input.md).[inputControlContainerElement](input.md#protected-inputcontrolcontainerelement)*

**Returns:** *HTMLElement*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [Input](input.md).[isInteractive](input.md#isinteractive)*

*Overrides [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

**Returns:** *boolean*

___

### `Protected` isNullable

• **get isNullable**(): *boolean*

*Inherited from [Input](input.md).[isNullable](input.md#protected-isnullable)*

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

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

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

**Returns:** *HTMLElement | undefined*

___

### `Protected` renderedInputControlElement

• **get renderedInputControlElement**(): *HTMLElement | undefined*

*Inherited from [Input](input.md).[renderedInputControlElement](input.md#protected-renderedinputcontrolelement)*

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

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

• **get value**(): *string | undefined*

*Overrides [Input](input.md).[value](input.md#value)*

**Returns:** *string | undefined*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

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

**Returns:** *HTMLElement*

___

###  focus

▸ **focus**(): *void*

*Inherited from [Input](input.md).[focus](input.md#focus)*

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

*Inherited from [Input](input.md).[getAllInputs](input.md#getallinputs)*

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

### `Protected` getAllLabelIds

▸ **getAllLabelIds**(): *string[]*

*Inherited from [Input](input.md).[getAllLabelIds](input.md#protected-getalllabelids)*

**Returns:** *string[]*

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

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

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

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [Input](input.md).[internalValidateProperties](input.md#internalvalidateproperties)*

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

###  isSet

▸ **isSet**(): *boolean*

*Overrides [Input](input.md).[isSet](input.md#abstract-isset)*

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

*Overrides [Input](input.md).[isValid](input.md#isvalid)*

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

*Inherited from [Input](input.md).[overrideInternalRender](input.md#protected-overrideinternalrender)*

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

**Returns:** *void*

___

### `Protected` resetValidationFailureCue

▸ **resetValidationFailureCue**(): *void*

*Inherited from [Input](input.md).[resetValidationFailureCue](input.md#protected-resetvalidationfailurecue)*

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

*Inherited from [Input](input.md).[showValidationErrorMessage](input.md#protected-showvalidationerrormessage)*

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

*Inherited from [Input](input.md).[updateInputControlAriaLabelledBy](input.md#protected-updateinputcontrolarialabelledby)*

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

**Returns:** *[ValidationResults](validationresults.md)*

___

###  validateValue

▸ **validateValue**(): *boolean*

*Implementation of [IInput](../interfaces/iinput.md)*

*Inherited from [Input](input.md).[validateValue](input.md#validatevalue)*

**Returns:** *boolean*

___

### `Protected` valueChanged

▸ **valueChanged**(): *void*

*Inherited from [Input](input.md).[valueChanged](input.md#protected-valuechanged)*

**Returns:** *void*
