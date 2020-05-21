[Adaptive Cards Javascript SDK](../README.md) › [TextInput](textinput.md)

# Class: TextInput

## Hierarchy

  ↳ [Input](input.md)

  ↳ **TextInput**

## Implements

* [IInput](../interfaces/iinput.md)

## Index

### Constructors

* [constructor](textinput.md#constructor)

### Properties

* [_parent](textinput.md#protected-optional-_parent)
* [_renderedElement](textinput.md#protected-optional-_renderedelement)
* [customCssSelector](textinput.md#optional-customcssselector)
* [defaultValue](textinput.md#optional-defaultvalue)
* [height](textinput.md#height)
* [horizontalAlignment](textinput.md#horizontalalignment)
* [id](textinput.md#optional-id)
* [inlineAction](textinput.md#optional-inlineaction)
* [isMultiline](textinput.md#ismultiline)
* [maxLength](textinput.md#optional-maxlength)
* [maxVersion](textinput.md#maxversion)
* [onPreProcessPropertyValue](textinput.md#optional-onpreprocesspropertyvalue)
* [onValueChanged](textinput.md#onvaluechanged)
* [placeholder](textinput.md#optional-placeholder)
* [separator](textinput.md#separator)
* [spacing](textinput.md#spacing)
* [style](textinput.md#style)
* [heightProperty](textinput.md#static-heightproperty)
* [horizontalAlignmentProperty](textinput.md#static-horizontalalignmentproperty)
* [idProperty](textinput.md#static-idproperty)
* [inlineActionProperty](textinput.md#static-inlineactionproperty)
* [isMultilineProperty](textinput.md#static-ismultilineproperty)
* [isVisibleProperty](textinput.md#static-isvisibleproperty)
* [langProperty](textinput.md#static-langproperty)
* [maxLengthProperty](textinput.md#static-maxlengthproperty)
* [onRegisterCustomProperties](textinput.md#static-optional-onregistercustomproperties)
* [placeholderProperty](textinput.md#static-placeholderproperty)
* [requiresProperty](textinput.md#static-requiresproperty)
* [separatorProperty](textinput.md#static-separatorproperty)
* [spacingProperty](textinput.md#static-spacingproperty)
* [styleProperty](textinput.md#static-styleproperty)
* [typeNameProperty](textinput.md#static-typenameproperty)
* [validationProperty](textinput.md#static-validationproperty)
* [valueProperty](textinput.md#static-valueproperty)

### Accessors

* [allowCustomPadding](textinput.md#protected-allowcustompadding)
* [defaultStyle](textinput.md#protected-defaultstyle)
* [hasVisibleSeparator](textinput.md#hasvisibleseparator)
* [hostConfig](textinput.md#hostconfig)
* [index](textinput.md#index)
* [inputControlContainerElement](textinput.md#protected-inputcontrolcontainerelement)
* [isInline](textinput.md#isinline)
* [isInteractive](textinput.md#isinteractive)
* [isNullable](textinput.md#protected-isnullable)
* [isStandalone](textinput.md#isstandalone)
* [isVisible](textinput.md#isvisible)
* [lang](textinput.md#lang)
* [parent](textinput.md#parent)
* [renderedElement](textinput.md#renderedelement)
* [renderedInputControlElement](textinput.md#protected-renderedinputcontrolelement)
* [requires](textinput.md#requires)
* [separatorElement](textinput.md#separatorelement)
* [separatorOrientation](textinput.md#protected-separatororientation)
* [useDefaultSizing](textinput.md#protected-usedefaultsizing)
* [validation](textinput.md#validation)
* [value](textinput.md#value)

### Methods

* [adjustRenderedElementSize](textinput.md#protected-adjustrenderedelementsize)
* [applyPadding](textinput.md#protected-applypadding)
* [asString](textinput.md#asstring)
* [createPlaceholderElement](textinput.md#protected-createplaceholderelement)
* [getActionAt](textinput.md#getactionat)
* [getActionById](textinput.md#getactionbyid)
* [getActionCount](textinput.md#getactioncount)
* [getAllInputs](textinput.md#getallinputs)
* [getCustomProperty](textinput.md#getcustomproperty)
* [getDefaultPadding](textinput.md#protected-getdefaultpadding)
* [getEffectivePadding](textinput.md#geteffectivepadding)
* [getEffectiveStyle](textinput.md#geteffectivestyle)
* [getEffectiveStyleDefinition](textinput.md#geteffectivestyledefinition)
* [getElementById](textinput.md#getelementbyid)
* [getForbiddenActionTypes](textinput.md#getforbiddenactiontypes)
* [getHasBackground](textinput.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](textinput.md#getimmediatesurroundingpadding)
* [getJsonTypeName](textinput.md#getjsontypename)
* [getPadding](textinput.md#protected-getpadding)
* [getParentContainer](textinput.md#getparentcontainer)
* [getResourceInformation](textinput.md#getresourceinformation)
* [getRootElement](textinput.md#getrootelement)
* [getRootObject](textinput.md#getrootobject)
* [getSchema](textinput.md#getschema)
* [getSchemaKey](textinput.md#protected-getschemakey)
* [getValue](textinput.md#protected-getvalue)
* [hasAllDefaultValues](textinput.md#hasalldefaultvalues)
* [hasDefaultValue](textinput.md#hasdefaultvalue)
* [indexOf](textinput.md#indexof)
* [internalParse](textinput.md#protected-internalparse)
* [internalRender](textinput.md#protected-internalrender)
* [internalToJSON](textinput.md#protected-internaltojson)
* [internalValidateProperties](textinput.md#internalvalidateproperties)
* [isAtTheVeryBottom](textinput.md#isattheverybottom)
* [isAtTheVeryLeft](textinput.md#isattheveryleft)
* [isAtTheVeryRight](textinput.md#isattheveryright)
* [isAtTheVeryTop](textinput.md#isattheverytop)
* [isBleeding](textinput.md#isbleeding)
* [isBleedingAtBottom](textinput.md#isbleedingatbottom)
* [isBleedingAtTop](textinput.md#isbleedingattop)
* [isBottomElement](textinput.md#isbottomelement)
* [isDesignMode](textinput.md#isdesignmode)
* [isDisplayed](textinput.md#protected-isdisplayed)
* [isFirstElement](textinput.md#isfirstelement)
* [isHiddenDueToOverflow](textinput.md#ishiddenduetooverflow)
* [isLastElement](textinput.md#islastelement)
* [isLeftMostElement](textinput.md#isleftmostelement)
* [isRightMostElement](textinput.md#isrightmostelement)
* [isSet](textinput.md#isset)
* [isTopElement](textinput.md#istopelement)
* [overrideInternalRender](textinput.md#protected-overrideinternalrender)
* [parse](textinput.md#parse)
* [populateSchema](textinput.md#protected-populateschema)
* [preProcessPropertyValue](textinput.md#preprocesspropertyvalue)
* [remove](textinput.md#remove)
* [render](textinput.md#render)
* [resetDefaultValues](textinput.md#resetdefaultvalues)
* [resetValidationFailureCue](textinput.md#protected-resetvalidationfailurecue)
* [setCustomProperty](textinput.md#setcustomproperty)
* [setPadding](textinput.md#protected-setpadding)
* [setParent](textinput.md#setparent)
* [setShouldFallback](textinput.md#setshouldfallback)
* [setValue](textinput.md#protected-setvalue)
* [shouldFallback](textinput.md#shouldfallback)
* [shouldSerialize](textinput.md#protected-shouldserialize)
* [showValidationErrorMessage](textinput.md#protected-showvalidationerrormessage)
* [toJSON](textinput.md#tojson)
* [truncateOverflow](textinput.md#protected-truncateoverflow)
* [undoOverflowTruncation](textinput.md#protected-undooverflowtruncation)
* [updateLayout](textinput.md#updatelayout)
* [validateProperties](textinput.md#validateproperties)
* [validateValue](textinput.md#validatevalue)
* [valueChanged](textinput.md#protected-valuechanged)

## Constructors

###  constructor

\+ **new TextInput**(): *[TextInput](textinput.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

**Returns:** *[TextInput](textinput.md)*

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

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

*Defined in [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L311)*

___

### `Optional` defaultValue

• **defaultValue**? : *undefined | string*

*Defined in [card-elements.ts:2469](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2469)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

*Defined in [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L53)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)*

*Defined in [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L44)*

___

### `Optional` id

• **id**? : *undefined | string*

*Implementation of [IInput](../interfaces/iinput.md).[id](../interfaces/iinput.md#optional-id)*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

*Defined in [card-object.ts:50](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L50)*

___

### `Optional` inlineAction

• **inlineAction**? : *[Action](action.md)*

*Defined in [card-elements.ts:2484](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2484)*

___

###  isMultiline

• **isMultiline**: *boolean* = false

*Defined in [card-elements.ts:2475](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2475)*

___

### `Optional` maxLength

• **maxLength**? : *undefined | number*

*Defined in [card-elements.ts:2472](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2472)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

*Defined in [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L64)*

___

###  onValueChanged

• **onValueChanged**: *function*

*Inherited from [Input](input.md).[onValueChanged](input.md#onvaluechanged)*

*Defined in [card-elements.ts:2415](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2415)*

#### Type declaration:

▸ (`sender`: [Input](input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Input](input.md) |

___

### `Optional` placeholder

• **placeholder**? : *undefined | string*

*Defined in [card-elements.ts:2478](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2478)*

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

*Defined in [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L50)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

*Defined in [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L47)*

___

###  style

• **style**: *[InputTextStyle](../enums/inputtextstyle.md)* = Enums.InputTextStyle.Text

*Defined in [card-elements.ts:2481](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2481)*

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

*Defined in [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L24)*

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

*Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)*

*Defined in [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L32)*

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

*Defined in [card-object.ts:39](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L39)*

___

### `Static` inlineActionProperty

▪ **inlineActionProperty**: *[ActionProperty](actionproperty.md)‹›* = new ActionProperty(Versions.v1_0, "inlineAction", [ "Action.ShowCard" ])

*Defined in [card-elements.ts:2466](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2466)*

___

### `Static` isMultilineProperty

▪ **isMultilineProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "isMultiline", false)

*Defined in [card-elements.ts:2463](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2463)*

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

*Defined in [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L22)*

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

*Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-langproperty)*

*Defined in [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L21)*

___

### `Static` maxLengthProperty

▪ **maxLengthProperty**: *[NumProperty](numproperty.md)‹›* = new NumProperty(Versions.v1_0, "maxLength")

*Defined in [card-elements.ts:2462](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2462)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

*Defined in [serialization.ts:729](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L729)*

___

### `Static` placeholderProperty

▪ **placeholderProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "placeholder")

*Defined in [card-elements.ts:2464](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2464)*

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities)

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

*Defined in [card-object.ts:40](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L40)*

___

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

*Defined in [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L23)*

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

*Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-spacingproperty)*

*Defined in [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L37)*

___

### `Static` styleProperty

▪ **styleProperty**: *[EnumProperty](enumproperty.md)‹[InputTextStyle](../enums/inputtextstyle.md)›* = new EnumProperty(Versions.v1_0, "style", Enums.InputTextStyle, Enums.InputTextStyle.Text)

*Defined in [card-elements.ts:2465](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2465)*

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

### `Static` validationProperty

▪ **validationProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.vNext,
        "validation",
        InputValidationOptions)

*Inherited from [Input](input.md).[validationProperty](input.md#static-validationproperty)*

*Defined in [card-elements.ts:2313](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2313)*

___

### `Static` valueProperty

▪ **valueProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "value")

*Defined in [card-elements.ts:2461](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2461)*

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

*Defined in [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L299)*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

*Defined in [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L307)*

**Returns:** *string*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Inherited from [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)*

*Defined in [card-elements.ts:580](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L580)*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

*Defined in [card-elements.ts:541](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L541)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

*Defined in [card-elements.ts:555](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L555)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

*Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)*

*Defined in [card-elements.ts:559](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L559)*

**Returns:** *number*

___

### `Protected` inputControlContainerElement

• **get inputControlContainerElement**(): *HTMLElement*

*Inherited from [Input](input.md).[inputControlContainerElement](input.md#protected-inputcontrolcontainerelement)*

*Defined in [card-elements.ts:2346](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2346)*

**Returns:** *HTMLElement*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

*Defined in [card-elements.ts:576](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L576)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [Input](input.md).[isInteractive](input.md#isinteractive)*

*Overrides [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

*Defined in [card-elements.ts:2453](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2453)*

**Returns:** *boolean*

___

### `Protected` isNullable

• **get isNullable**(): *boolean*

*Inherited from [Input](input.md).[isNullable](input.md#protected-isnullable)*

*Defined in [card-elements.ts:2338](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2338)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

*Defined in [card-elements.ts:572](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L572)*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

*Defined in [card-elements.ts:77](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L77)*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

*Defined in [card-elements.ts:81](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L81)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

*Defined in [card-elements.ts:56](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L56)*

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

*Defined in [card-elements.ts:72](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L72)*

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

*Defined in [card-elements.ts:593](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L593)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

*Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)*

*Defined in [card-object.ts:140](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L140)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` renderedInputControlElement

• **get renderedInputControlElement**(): *HTMLElement*

*Inherited from [Input](input.md).[renderedInputControlElement](input.md#protected-renderedinputcontrolelement)*

*Defined in [card-elements.ts:2342](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2342)*

**Returns:** *HTMLElement*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

*Defined in [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L53)*

**Returns:** *HostCapabilities*

___

###  separatorElement

• **get separatorElement**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)*

*Defined in [card-elements.ts:589](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L589)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

*Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

*Defined in [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L303)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

*Defined in [card-elements.ts:295](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L295)*

**Returns:** *boolean*

___

###  validation

• **get validation**(): *[InputValidationOptions](inputvalidationoptions.md)*

*Inherited from [Input](input.md).[validation](input.md#validation)*

*Defined in [card-elements.ts:2327](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2327)*

**Returns:** *[InputValidationOptions](inputvalidationoptions.md)*

___

###  value

• **get value**(): *string | undefined*

*Overrides [Input](input.md).[value](input.md#value)*

*Defined in [card-elements.ts:2613](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2613)*

**Returns:** *string | undefined*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

*Defined in [card-elements.ts:220](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L220)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [CardElement](cardelement.md).[applyPadding](cardelement.md#protected-applypadding)*

*Defined in [card-elements.ts:239](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L239)*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

*Defined in [card-elements.ts:321](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L321)*

**Returns:** *string | undefined*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

*Defined in [card-elements.ts:205](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L205)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

*Defined in [card-elements.ts:400](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L400)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *undefined | [Action](action.md)‹›*

*Overrides [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

*Defined in [card-elements.ts:2599](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2599)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *undefined | [Action](action.md)‹›*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

*Defined in [card-elements.ts:396](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L396)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *[Input](input.md)[]*

*Inherited from [Input](input.md).[getAllInputs](input.md#getallinputs)*

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

*Defined in [card-elements.ts:2449](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2449)*

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

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getDefaultPadding](cardelement.md#protected-getdefaultpadding)*

*Defined in [card-elements.ts:275](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L275)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)*

*Defined in [card-elements.ts:535](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L535)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)*

*Defined in [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L329)*

**Returns:** *string*

___

###  getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)*

*Defined in [card-elements.ts:337](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L337)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)*

*Defined in [card-elements.ts:527](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L527)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *[ActionType](../README.md#actiontype)[]*

*Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)*

*Defined in [card-elements.ts:341](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L341)*

**Returns:** *[ActionType](../README.md#actiontype)[]*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

*Inherited from [CardElement](cardelement.md).[getHasBackground](cardelement.md#protected-gethasbackground)*

*Defined in [card-elements.ts:279](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L279)*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)*

*Defined in [card-elements.ts:345](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L345)*

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

*Defined in [card-elements.ts:2595](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2595)*

**Returns:** *string*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)*

*Defined in [card-elements.ts:283](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L283)*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)*

*Defined in [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L505)*

**Returns:** *[Container](container.md) | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

*Inherited from [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

*Defined in [card-elements.ts:523](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L523)*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)*

*Defined in [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L501)*

**Returns:** *[CardElement](cardelement.md)*

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

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): *number*

*Inherited from [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

*Defined in [card-elements.ts:439](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L439)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

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

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

*Defined in [card-elements.ts:2514](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2514)*

**Returns:** *HTMLElement | undefined*

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

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [Input](input.md).[internalValidateProperties](input.md#internalvalidateproperties)*

*Overrides [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:2419](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2419)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)*

*Defined in [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L469)*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)*

*Defined in [card-elements.ts:457](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L457)*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)*

*Defined in [card-elements.ts:461](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L461)*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)*

*Defined in [card-elements.ts:465](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L465)*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)*

*Defined in [card-elements.ts:325](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L325)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

*Defined in [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L477)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

*Defined in [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L473)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)*

*Defined in [card-elements.ts:493](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L493)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)*

*Defined in [card-elements.ts:443](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L443)*

**Returns:** *boolean*

___

### `Protected` isDisplayed

▸ **isDisplayed**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDisplayed](cardelement.md#protected-isdisplayed)*

*Defined in [card-elements.ts:229](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L229)*

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

*Defined in [card-elements.ts:449](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L449)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)*

*Defined in [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L497)*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)*

*Defined in [card-elements.ts:453](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L453)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)*

*Defined in [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L481)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)*

*Defined in [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L485)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isSet

▸ **isSet**(): *boolean*

*Overrides [Input](input.md).[isSet](input.md#abstract-isset)*

*Defined in [card-elements.ts:2609](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2609)*

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)*

*Defined in [card-elements.ts:489](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L489)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

*Overrides [Input](input.md).[overrideInternalRender](input.md#protected-overrideinternalrender)*

*Defined in [card-elements.ts:2532](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2532)*

**Returns:** *HTMLElement | undefined*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [CardElement](cardelement.md).[parse](cardelement.md#parse)*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:313](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L313)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [Input](input.md).[populateSchema](input.md#protected-populateschema)*

*Overrides [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

*Defined in [card-elements.ts:2318](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2318)*

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

###  remove

▸ **remove**(): *boolean*

*Inherited from [CardElement](cardelement.md).[remove](cardelement.md#remove)*

*Defined in [card-elements.ts:404](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L404)*

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[render](cardelement.md#render)*

*Defined in [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L412)*

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

*Defined in [serialization.ts:901](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L901)*

**Returns:** *void*

___

### `Protected` resetValidationFailureCue

▸ **resetValidationFailureCue**(): *void*

*Inherited from [Input](input.md).[resetValidationFailureCue](input.md#protected-resetvalidationfailurecue)*

*Defined in [card-elements.ts:2391](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2391)*

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

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): *void*

*Inherited from [CardElement](cardelement.md).[setPadding](cardelement.md#protected-setpadding)*

*Defined in [card-elements.ts:287](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L287)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

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

*Inherited from [CardElement](cardelement.md).[shouldSerialize](cardelement.md#protected-shouldserialize)*

*Overrides [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

*Defined in [card-elements.ts:291](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L291)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *boolean*

___

### `Protected` showValidationErrorMessage

▸ **showValidationErrorMessage**(): *void*

*Inherited from [Input](input.md).[showValidationErrorMessage](input.md#protected-showvalidationerrormessage)*

*Defined in [card-elements.ts:2403](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2403)*

**Returns:** *void*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [CardElement](cardelement.md).[toJSON](cardelement.md#tojson)*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

*Defined in [card-elements.ts:317](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L317)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Inherited from [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

*Defined in [card-elements.ts:263](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L263)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Inherited from [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

*Defined in [card-elements.ts:273](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L273)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)*

*Defined in [card-elements.ts:434](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L434)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | true |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

*Defined in [card-object.ts:128](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L128)*

**Returns:** *[ValidationResults](validationresults.md)*

___

###  validateValue

▸ **validateValue**(): *boolean*

*Implementation of [IInput](../interfaces/iinput.md)*

*Inherited from [Input](input.md).[validateValue](input.md#validatevalue)*

*Defined in [card-elements.ts:2430](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2430)*

**Returns:** *boolean*

___

### `Protected` valueChanged

▸ **valueChanged**(): *void*

*Inherited from [Input](input.md).[valueChanged](input.md#protected-valuechanged)*

*Defined in [card-elements.ts:2381](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L2381)*

**Returns:** *void*
