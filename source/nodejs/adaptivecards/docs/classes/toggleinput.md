[Adaptive Cards Javascript SDK](../README.md) › [ToggleInput](toggleinput.md)

# Class: ToggleInput

## Hierarchy

↳ [Input](input.md)

↳ **ToggleInput**

## Implements

- [IInput](../interfaces/iinput.md)

## Index

### Constructors

- [constructor](toggleinput.md#constructor)

### Properties

- [\_parent](toggleinput.md#protected-optional-_parent)
- [\_renderedElement](toggleinput.md#protected-optional-_renderedelement)
- [customCssSelector](toggleinput.md#optional-customcssselector)
- [defaultValue](toggleinput.md#optional-defaultvalue)
- [errorMessage](toggleinput.md#optional-errormessage)
- [height](toggleinput.md#height)
- [horizontalAlignment](toggleinput.md#horizontalalignment)
- [id](toggleinput.md#optional-id)
- [isRequired](toggleinput.md#isrequired)
- [label](toggleinput.md#optional-label)
- [maxVersion](toggleinput.md#maxversion)
- [onPreProcessPropertyValue](toggleinput.md#optional-onpreprocesspropertyvalue)
- [onValueChanged](toggleinput.md#onvaluechanged)
- [separator](toggleinput.md#separator)
- [spacing](toggleinput.md#spacing)
- [title](toggleinput.md#optional-title)
- [valueOff](toggleinput.md#valueoff)
- [valueOn](toggleinput.md#valueon)
- [wrap](toggleinput.md#wrap)
- [errorMessageProperty](toggleinput.md#static-readonly-errormessageproperty)
- [heightProperty](toggleinput.md#static-readonly-heightproperty)
- [horizontalAlignmentProperty](toggleinput.md#static-readonly-horizontalalignmentproperty)
- [idProperty](toggleinput.md#static-readonly-idproperty)
- [isRequiredProperty](toggleinput.md#static-readonly-isrequiredproperty)
- [isVisibleProperty](toggleinput.md#static-readonly-isvisibleproperty)
- [labelProperty](toggleinput.md#static-readonly-labelproperty)
- [langProperty](toggleinput.md#static-readonly-langproperty)
- [onRegisterCustomProperties](toggleinput.md#static-optional-onregistercustomproperties)
- [requiresProperty](toggleinput.md#static-readonly-requiresproperty)
- [separatorProperty](toggleinput.md#static-readonly-separatorproperty)
- [spacingProperty](toggleinput.md#static-readonly-spacingproperty)
- [titleProperty](toggleinput.md#static-readonly-titleproperty)
- [typeNameProperty](toggleinput.md#static-readonly-typenameproperty)
- [valueOffProperty](toggleinput.md#static-readonly-valueoffproperty)
- [valueOnProperty](toggleinput.md#static-readonly-valueonproperty)
- [valueProperty](toggleinput.md#static-readonly-valueproperty)
- [wrapProperty](toggleinput.md#static-readonly-wrapproperty)

### Accessors

- [allowCustomPadding](toggleinput.md#protected-allowcustompadding)
- [defaultStyle](toggleinput.md#protected-defaultstyle)
- [hasVisibleSeparator](toggleinput.md#hasvisibleseparator)
- [hostConfig](toggleinput.md#hostconfig)
- [index](toggleinput.md#index)
- [inputControlContainerElement](toggleinput.md#protected-inputcontrolcontainerelement)
- [isInline](toggleinput.md#isinline)
- [isInteractive](toggleinput.md#isinteractive)
- [isNullable](toggleinput.md#protected-isnullable)
- [isStandalone](toggleinput.md#isstandalone)
- [isVisible](toggleinput.md#isvisible)
- [lang](toggleinput.md#lang)
- [parent](toggleinput.md#parent)
- [renderedElement](toggleinput.md#renderedelement)
- [renderedInputControlElement](toggleinput.md#protected-renderedinputcontrolelement)
- [requires](toggleinput.md#requires)
- [separatorElement](toggleinput.md#separatorelement)
- [separatorOrientation](toggleinput.md#protected-separatororientation)
- [useDefaultSizing](toggleinput.md#protected-usedefaultsizing)
- [value](toggleinput.md#value)

### Methods

- [adjustRenderedElementSize](toggleinput.md#protected-adjustrenderedelementsize)
- [applyPadding](toggleinput.md#protected-applypadding)
- [asString](toggleinput.md#asstring)
- [createPlaceholderElement](toggleinput.md#protected-createplaceholderelement)
- [focus](toggleinput.md#focus)
- [getActionAt](toggleinput.md#getactionat)
- [getActionById](toggleinput.md#getactionbyid)
- [getActionCount](toggleinput.md#getactioncount)
- [getAllInputs](toggleinput.md#getallinputs)
- [getAllLabelIds](toggleinput.md#protected-getalllabelids)
- [getCustomProperty](toggleinput.md#getcustomproperty)
- [getDefaultPadding](toggleinput.md#protected-getdefaultpadding)
- [getDefaultSerializationContext](toggleinput.md#protected-getdefaultserializationcontext)
- [getEffectivePadding](toggleinput.md#geteffectivepadding)
- [getEffectiveStyle](toggleinput.md#geteffectivestyle)
- [getEffectiveStyleDefinition](toggleinput.md#geteffectivestyledefinition)
- [getElementById](toggleinput.md#getelementbyid)
- [getForbiddenActionTypes](toggleinput.md#getforbiddenactiontypes)
- [getHasBackground](toggleinput.md#protected-gethasbackground)
- [getImmediateSurroundingPadding](toggleinput.md#getimmediatesurroundingpadding)
- [getJsonTypeName](toggleinput.md#getjsontypename)
- [getPadding](toggleinput.md#protected-getpadding)
- [getParentContainer](toggleinput.md#getparentcontainer)
- [getResourceInformation](toggleinput.md#getresourceinformation)
- [getRootElement](toggleinput.md#getrootelement)
- [getRootObject](toggleinput.md#getrootobject)
- [getSchema](toggleinput.md#getschema)
- [getSchemaKey](toggleinput.md#protected-getschemakey)
- [getValue](toggleinput.md#protected-getvalue)
- [hasAllDefaultValues](toggleinput.md#hasalldefaultvalues)
- [hasDefaultValue](toggleinput.md#hasdefaultvalue)
- [indexOf](toggleinput.md#indexof)
- [internalParse](toggleinput.md#protected-internalparse)
- [internalRender](toggleinput.md#protected-internalrender)
- [internalToJSON](toggleinput.md#protected-internaltojson)
- [internalValidateProperties](toggleinput.md#internalvalidateproperties)
- [isAtTheVeryBottom](toggleinput.md#isattheverybottom)
- [isAtTheVeryLeft](toggleinput.md#isattheveryleft)
- [isAtTheVeryRight](toggleinput.md#isattheveryright)
- [isAtTheVeryTop](toggleinput.md#isattheverytop)
- [isBleeding](toggleinput.md#isbleeding)
- [isBleedingAtBottom](toggleinput.md#isbleedingatbottom)
- [isBleedingAtTop](toggleinput.md#isbleedingattop)
- [isBottomElement](toggleinput.md#isbottomelement)
- [isDesignMode](toggleinput.md#isdesignmode)
- [isDisplayed](toggleinput.md#protected-isdisplayed)
- [isFirstElement](toggleinput.md#isfirstelement)
- [isHiddenDueToOverflow](toggleinput.md#ishiddenduetooverflow)
- [isLastElement](toggleinput.md#islastelement)
- [isLeftMostElement](toggleinput.md#isleftmostelement)
- [isRightMostElement](toggleinput.md#isrightmostelement)
- [isSet](toggleinput.md#isset)
- [isTopElement](toggleinput.md#istopelement)
- [isValid](toggleinput.md#isvalid)
- [overrideInternalRender](toggleinput.md#protected-overrideinternalrender)
- [parse](toggleinput.md#parse)
- [populateSchema](toggleinput.md#protected-populateschema)
- [preProcessPropertyValue](toggleinput.md#preprocesspropertyvalue)
- [remove](toggleinput.md#remove)
- [render](toggleinput.md#render)
- [resetDefaultValues](toggleinput.md#resetdefaultvalues)
- [resetValidationFailureCue](toggleinput.md#protected-resetvalidationfailurecue)
- [setCustomProperty](toggleinput.md#setcustomproperty)
- [setPadding](toggleinput.md#protected-setpadding)
- [setParent](toggleinput.md#setparent)
- [setShouldFallback](toggleinput.md#setshouldfallback)
- [setValue](toggleinput.md#protected-setvalue)
- [shouldFallback](toggleinput.md#shouldfallback)
- [shouldSerialize](toggleinput.md#protected-shouldserialize)
- [showValidationErrorMessage](toggleinput.md#protected-showvalidationerrormessage)
- [toJSON](toggleinput.md#tojson)
- [truncateOverflow](toggleinput.md#protected-truncateoverflow)
- [undoOverflowTruncation](toggleinput.md#protected-undooverflowtruncation)
- [updateInputControlAriaLabelledBy](toggleinput.md#protected-updateinputcontrolarialabelledby)
- [updateLayout](toggleinput.md#updatelayout)
- [validateProperties](toggleinput.md#validateproperties)
- [validateValue](toggleinput.md#validatevalue)
- [valueChanged](toggleinput.md#protected-valuechanged)

## Constructors

### constructor

\+ **new ToggleInput**(): _[ToggleInput](toggleinput.md)_

_Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)_

**Returns:** _[ToggleInput](toggleinput.md)_

## Properties

### `Protected` `Optional` \_parent

• **\_parent**? : _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[\_parent](cardobject.md#protected-optional-_parent)_

---

### `Protected` `Optional` \_renderedElement

• **\_renderedElement**? : _HTMLElement_

_Inherited from [CardObject](cardobject.md).[\_renderedElement](cardobject.md#protected-optional-_renderedelement)_

---

### `Optional` customCssSelector

• **customCssSelector**? : _undefined | string_

_Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)_

---

### `Optional` defaultValue

• **defaultValue**? : _undefined | string_

---

### `Optional` errorMessage

• **errorMessage**? : _undefined | string_

_Inherited from [Input](input.md).[errorMessage](input.md#optional-errormessage)_

---

### height

• **height**: _[CardElementHeight](../README.md#cardelementheight)_

_Implementation of [IInput](../interfaces/iinput.md).[height](../interfaces/iinput.md#optional-height)_

_Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)_

---

### horizontalAlignment

• **horizontalAlignment**: _[HorizontalAlignment](../enums/horizontalalignment.md)_

_Implementation of [IInput](../interfaces/iinput.md).[horizontalAlignment](../interfaces/iinput.md#optional-horizontalalignment)_

_Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)_

---

### `Optional` id

• **id**? : _undefined | string_

_Implementation of [IInput](../interfaces/iinput.md).[id](../interfaces/iinput.md#optional-id)_

_Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)_

---

### isRequired

• **isRequired**: _boolean_

_Inherited from [Input](input.md).[isRequired](input.md#isrequired)_

---

### `Optional` label

• **label**? : _undefined | string_

_Inherited from [Input](input.md).[label](input.md#optional-label)_

---

### maxVersion

• **maxVersion**: _[Version](version.md)_ = Versions.v1_3

_Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)_

---

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : _undefined | function_

_Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)_

---

### onValueChanged

• **onValueChanged**: _function_

_Inherited from [Input](input.md).[onValueChanged](input.md#onvaluechanged)_

#### Type declaration:

▸ (`sender`: [Input](input.md)): _void_

**Parameters:**

| Name     | Type              |
| -------- | ----------------- |
| `sender` | [Input](input.md) |

---

### separator

• **separator**: _boolean_

_Implementation of [IInput](../interfaces/iinput.md).[separator](../interfaces/iinput.md#optional-separator)_

_Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)_

---

### spacing

• **spacing**: _[Spacing](../enums/spacing.md)_

_Implementation of [IInput](../interfaces/iinput.md).[spacing](../interfaces/iinput.md#optional-spacing)_

_Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)_

---

### `Optional` title

• **title**? : _undefined | string_

---

### valueOff

• **valueOff**: _string_ = "false"

---

### valueOn

• **valueOn**: _string_ = "true"

---

### wrap

• **wrap**: _boolean_ = false

---

### `Static` `Readonly` errorMessageProperty

▪ **errorMessageProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_3, "errorMessage", true)

_Inherited from [Input](input.md).[errorMessageProperty](input.md#static-readonly-errormessageproperty)_

---

### `Static` `Readonly` heightProperty

▪ **heightProperty**: _[ValueSetProperty](valuesetproperty.md)‹›_ = new ValueSetProperty(
Versions.v1_1,
"height",
[
{ value: "auto" },
{ value: "stretch" }
],
"auto")

_Inherited from [CardElement](cardelement.md).[heightProperty](cardelement.md#static-readonly-heightproperty)_

---

### `Static` `Readonly` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: _[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›_ = new EnumProperty(
Versions.v1_0,
"horizontalAlignment",
Enums.HorizontalAlignment,
Enums.HorizontalAlignment.Left)

_Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-readonly-horizontalalignmentproperty)_

---

### `Static` `Readonly` idProperty

▪ **idProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "id")

_Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-readonly-idproperty)_

---

### `Static` `Readonly` isRequiredProperty

▪ **isRequiredProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_3, "isRequired", false)

_Inherited from [Input](input.md).[isRequiredProperty](input.md#static-readonly-isrequiredproperty)_

---

### `Static` `Readonly` isVisibleProperty

▪ **isVisibleProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "isVisible", true)

_Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-readonly-isvisibleproperty)_

---

### `Static` `Readonly` labelProperty

▪ **labelProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_3, "label", true)

_Inherited from [Input](input.md).[labelProperty](input.md#static-readonly-labelproperty)_

---

### `Static` `Readonly` langProperty

▪ **langProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

_Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-readonly-langproperty)_

---

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : _undefined | function_

_Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)_

---

### `Static` `Readonly` requiresProperty

▪ **requiresProperty**: _[SerializableObjectProperty](serializableobjectproperty.md)‹›_ = new SerializableObjectProperty(
Versions.v1_2,
"requires",
HostCapabilities,
false,
new HostCapabilities())

_Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-readonly-requiresproperty)_

---

### `Static` `Readonly` separatorProperty

▪ **separatorProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_0, "separator", false)

_Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-readonly-separatorproperty)_

---

### `Static` `Readonly` spacingProperty

▪ **spacingProperty**: _[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›_ = new EnumProperty(
Versions.v1_0,
"spacing",
Enums.Spacing,
Enums.Spacing.Default)

_Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-readonly-spacingproperty)_

---

### `Static` `Readonly` titleProperty

▪ **titleProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "title")

---

### `Static` `Readonly` typeNameProperty

▪ **typeNameProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(
Versions.v1_0,
"type",
undefined,
undefined,
undefined,
(sender: object) => {
return (<CardObject>sender).getJsonTypeName()
})

_Inherited from [CardObject](cardobject.md).[typeNameProperty](cardobject.md#static-readonly-typenameproperty)_

---

### `Static` `Readonly` valueOffProperty

▪ **valueOffProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "valueOff", true, undefined, "false", (sender: SerializableObject) => { return "false"; })

---

### `Static` `Readonly` valueOnProperty

▪ **valueOnProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "valueOn", true, undefined, "true", (sender: SerializableObject) => { return "true"; })

---

### `Static` `Readonly` valueProperty

▪ **valueProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "value")

---

### `Static` `Readonly` wrapProperty

▪ **wrapProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "wrap", false)

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): _boolean_

_Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)_

**Returns:** _boolean_

---

### `Protected` defaultStyle

• **get defaultStyle**(): _string_

_Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)_

**Returns:** _string_

---

### hasVisibleSeparator

• **get hasVisibleSeparator**(): _boolean_

_Inherited from [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)_

**Returns:** _boolean_

---

### hostConfig

• **get hostConfig**(): _[HostConfig](hostconfig.md)_

_Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)_

_Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)_

**Returns:** _[HostConfig](hostconfig.md)_

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): _void_

_Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)_

_Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)_

**Parameters:**

| Name    | Type                        |
| ------- | --------------------------- |
| `value` | [HostConfig](hostconfig.md) |

**Returns:** _void_

---

### index

• **get index**(): _number_

_Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)_

**Returns:** _number_

---

### `Protected` inputControlContainerElement

• **get inputControlContainerElement**(): _HTMLElement_

_Inherited from [Input](input.md).[inputControlContainerElement](input.md#protected-inputcontrolcontainerelement)_

**Returns:** _HTMLElement_

---

### isInline

• **get isInline**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)_

**Returns:** _boolean_

---

### isInteractive

• **get isInteractive**(): _boolean_

_Inherited from [Input](input.md).[isInteractive](input.md#isinteractive)_

_Overrides [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)_

**Returns:** _boolean_

---

### `Protected` isNullable

• **get isNullable**(): _boolean_

_Overrides [Input](input.md).[isNullable](input.md#protected-isnullable)_

**Returns:** _boolean_

---

### isStandalone

• **get isStandalone**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)_

**Returns:** _boolean_

---

### isVisible

• **get isVisible**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)_

**Returns:** _boolean_

• **set isVisible**(`value`: boolean): _void_

_Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### lang

• **get lang**(): _string | undefined_

_Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)_

**Returns:** _string | undefined_

• **set lang**(`value`: string | undefined): _void_

_Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)_

**Parameters:**

| Name    | Type                    |
| ------- | ----------------------- |
| `value` | string &#124; undefined |

**Returns:** _void_

---

### parent

• **get parent**(): _[CardElement](cardelement.md) | undefined_

_Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)_

_Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)_

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### renderedElement

• **get renderedElement**(): _HTMLElement | undefined_

_Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)_

**Returns:** _HTMLElement | undefined_

---

### `Protected` renderedInputControlElement

• **get renderedInputControlElement**(): _HTMLElement | undefined_

_Inherited from [Input](input.md).[renderedInputControlElement](input.md#protected-renderedinputcontrolelement)_

**Returns:** _HTMLElement | undefined_

---

### requires

• **get requires**(): _[HostCapabilities](hostcapabilities.md)_

_Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)_

**Returns:** _[HostCapabilities](hostcapabilities.md)_

---

### separatorElement

• **get separatorElement**(): _HTMLElement | undefined_

_Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)_

**Returns:** _HTMLElement | undefined_

---

### `Protected` separatorOrientation

• **get separatorOrientation**(): _[Orientation](../enums/orientation.md)_

_Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)_

**Returns:** _[Orientation](../enums/orientation.md)_

---

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): _boolean_

_Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)_

**Returns:** _boolean_

---

### value

• **get value**(): _string | undefined_

_Overrides [Input](input.md).[value](input.md#value)_

**Returns:** _string | undefined_

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): _void_

_Inherited from [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)_

**Parameters:**

| Name              | Type        |
| ----------------- | ----------- |
| `renderedElement` | HTMLElement |

**Returns:** _void_

---

### `Protected` applyPadding

▸ **applyPadding**(): _void_

_Inherited from [CardElement](cardelement.md).[applyPadding](cardelement.md#protected-applypadding)_

**Returns:** _void_

---

### asString

▸ **asString**(): _string | undefined_

_Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)_

**Returns:** _string | undefined_

---

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): _HTMLElement_

_Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)_

**Returns:** _HTMLElement_

---

### focus

▸ **focus**(): _void_

_Overrides [Input](input.md).[focus](input.md#focus)_

**Returns:** _void_

---

### getActionAt

▸ **getActionAt**(`index`: number): _[Action](action.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `index` | number |

**Returns:** _[Action](action.md) | undefined_

---

### getActionById

▸ **getActionById**(`id`: string): _[Action](action.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)_

**Parameters:**

| Name | Type   |
| ---- | ------ |
| `id` | string |

**Returns:** _[Action](action.md) | undefined_

---

### getActionCount

▸ **getActionCount**(): _number_

_Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)_

**Returns:** _number_

---

### getAllInputs

▸ **getAllInputs**(`processActions`: boolean): _[Input](input.md)[]_

_Inherited from [Input](input.md).[getAllInputs](input.md#getallinputs)_

_Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)_

**Parameters:**

| Name             | Type    | Default |
| ---------------- | ------- | ------- |
| `processActions` | boolean | true    |

**Returns:** _[Input](input.md)[]_

---

### `Protected` getAllLabelIds

▸ **getAllLabelIds**(): _string[]_

_Inherited from [Input](input.md).[getAllLabelIds](input.md#protected-getalllabelids)_

**Returns:** _string[]_

---

### getCustomProperty

▸ **getCustomProperty**(`name`: string): _any_

_Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `name` | string |

**Returns:** _any_

---

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): _[PaddingDefinition](paddingdefinition.md)_

_Inherited from [CardElement](cardelement.md).[getDefaultPadding](cardelement.md#protected-getdefaultpadding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md)_

---

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): _[BaseSerializationContext](baseserializationcontext.md)_

_Inherited from [CardElement](cardelement.md).[getDefaultSerializationContext](cardelement.md#protected-getdefaultserializationcontext)_

_Overrides [SerializableObject](serializableobject.md).[getDefaultSerializationContext](serializableobject.md#protected-getdefaultserializationcontext)_

**Returns:** _[BaseSerializationContext](baseserializationcontext.md)_

---

### getEffectivePadding

▸ **getEffectivePadding**(): _[PaddingDefinition](paddingdefinition.md)_

_Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md)_

---

### getEffectiveStyle

▸ **getEffectiveStyle**(): _string_

_Inherited from [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)_

**Returns:** _string_

---

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): _[ContainerStyleDefinition](containerstyledefinition.md)_

_Inherited from [CardElement](cardelement.md).[getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)_

**Returns:** _[ContainerStyleDefinition](containerstyledefinition.md)_

---

### getElementById

▸ **getElementById**(`id`: string): _[CardElement](cardelement.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)_

**Parameters:**

| Name | Type   |
| ---- | ------ |
| `id` | string |

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): _[ActionType](../README.md#actiontype)[]_

_Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)_

**Returns:** _[ActionType](../README.md#actiontype)[]_

---

### `Protected` getHasBackground

▸ **getHasBackground**(): _boolean_

_Inherited from [CardElement](cardelement.md).[getHasBackground](cardelement.md#protected-gethasbackground)_

**Returns:** _boolean_

---

### getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): _void_

_Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)_

**Parameters:**

| Name            | Type                                      | Default |
| --------------- | ----------------------------------------- | ------- |
| `result`        | [PaddingDefinition](paddingdefinition.md) | -       |
| `processTop`    | boolean                                   | true    |
| `processRight`  | boolean                                   | true    |
| `processBottom` | boolean                                   | true    |
| `processLeft`   | boolean                                   | true    |

**Returns:** _void_

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

_Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)_

**Returns:** _string_

---

### `Protected` getPadding

▸ **getPadding**(): _[PaddingDefinition](paddingdefinition.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md) | undefined_

---

### getParentContainer

▸ **getParentContainer**(): _[Container](container.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)_

**Returns:** _[Container](container.md) | undefined_

---

### getResourceInformation

▸ **getResourceInformation**(): _[IResourceInformation](../interfaces/iresourceinformation.md)[]_

_Inherited from [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)_

**Returns:** _[IResourceInformation](../interfaces/iresourceinformation.md)[]_

---

### getRootElement

▸ **getRootElement**(): _[CardElement](cardelement.md)_

_Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)_

**Returns:** _[CardElement](cardelement.md)_

---

### getRootObject

▸ **getRootObject**(): _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)_

**Returns:** _[CardObject](cardobject.md)_

---

### getSchema

▸ **getSchema**(): _[SerializableObjectSchema](serializableobjectschema.md)_

_Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)_

**Returns:** _[SerializableObjectSchema](serializableobjectschema.md)_

---

### `Protected` getSchemaKey

▸ **getSchemaKey**(): _string_

_Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)_

_Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)_

**Returns:** _string_

---

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): _any_

_Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _any_

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)_

**Returns:** _boolean_

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _boolean_

---

### indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): _number_

_Inherited from [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)_

**Parameters:**

| Name          | Type                          |
| ------------- | ----------------------------- |
| `cardElement` | [CardElement](cardelement.md) |

**Returns:** _number_

---

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

_Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `source`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### `Protected` internalRender

▸ **internalRender**(): _HTMLElement | undefined_

_Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)_

**Returns:** _HTMLElement | undefined_

---

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): _void_

_Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `target`  | [PropertyBag](../README.md#propertybag)                 |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _void_

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): _void_

_Inherited from [Input](input.md).[internalValidateProperties](input.md#internalvalidateproperties)_

_Overrides [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)_

**Parameters:**

| Name      | Type                                      |
| --------- | ----------------------------------------- |
| `context` | [ValidationResults](validationresults.md) |

**Returns:** _void_

---

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)_

**Returns:** _boolean_

---

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)_

**Returns:** _boolean_

---

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)_

**Returns:** _boolean_

---

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)_

**Returns:** _boolean_

---

### isBleeding

▸ **isBleeding**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)_

**Returns:** _boolean_

---

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)_

**Returns:** _boolean_

---

### isBleedingAtTop

▸ **isBleedingAtTop**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)_

**Returns:** _boolean_

---

### isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isDesignMode

▸ **isDesignMode**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)_

**Returns:** _boolean_

---

### `Protected` isDisplayed

▸ **isDisplayed**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isDisplayed](cardelement.md#protected-isdisplayed)_

**Returns:** _boolean_

---

### isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)_

**Returns:** _boolean_

---

### isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isSet

▸ **isSet**(): _boolean_

_Overrides [Input](input.md).[isSet](input.md#abstract-isset)_

**Returns:** _boolean_

---

### isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isValid

▸ **isValid**(): _boolean_

_Inherited from [Input](input.md).[isValid](input.md#isvalid)_

**Returns:** _boolean_

---

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): _HTMLElement | undefined_

_Inherited from [Input](input.md).[overrideInternalRender](input.md#protected-overrideinternalrender)_

_Overrides [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)_

**Returns:** _HTMLElement | undefined_

---

### parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): _void_

_Inherited from [CardElement](cardelement.md).[parse](cardelement.md#parse)_

_Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)_

**Parameters:**

| Name       | Type                                            |
| ---------- | ----------------------------------------------- |
| `source`   | any                                             |
| `context?` | [SerializationContext](serializationcontext.md) |

**Returns:** _void_

---

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): _void_

_Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)_

**Parameters:**

| Name     | Type                                                    |
| -------- | ------------------------------------------------------- |
| `schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** _void_

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): _any_

_Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)_

**Parameters:**

| Name             | Type                                        |
| ---------------- | ------------------------------------------- |
| `property`       | [PropertyDefinition](propertydefinition.md) |
| `propertyValue?` | any                                         |

**Returns:** _any_

---

### remove

▸ **remove**(): _boolean_

_Inherited from [CardElement](cardelement.md).[remove](cardelement.md#remove)_

**Returns:** _boolean_

---

### render

▸ **render**(): _HTMLElement | undefined_

_Inherited from [CardElement](cardelement.md).[render](cardelement.md#render)_

**Returns:** _HTMLElement | undefined_

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

_Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)_

**Returns:** _void_

---

### `Protected` resetValidationFailureCue

▸ **resetValidationFailureCue**(): _void_

_Inherited from [Input](input.md).[resetValidationFailureCue](input.md#protected-resetvalidationfailurecue)_

**Returns:** _void_

---

### setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): _void_

_Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `name`  | string |
| `value` | any    |

**Returns:** _void_

---

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): _void_

_Inherited from [CardElement](cardelement.md).[setPadding](cardelement.md#protected-setpadding)_

**Parameters:**

| Name    | Type                                                       |
| ------- | ---------------------------------------------------------- |
| `value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** _void_

---

### setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): _void_

_Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)_

**Parameters:**

| Name    | Type                                         |
| ------- | -------------------------------------------- |
| `value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** _void_

---

### setShouldFallback

▸ **setShouldFallback**(`value`: boolean): _void_

_Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): _void_

_Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |
| `value`    | any                                         |

**Returns:** _void_

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

_Inherited from [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)_

**Returns:** _boolean_

---

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _boolean_

---

### `Protected` showValidationErrorMessage

▸ **showValidationErrorMessage**(): _void_

_Inherited from [Input](input.md).[showValidationErrorMessage](input.md#protected-showvalidationerrormessage)_

**Returns:** _void_

---

### toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): _[PropertyBag](../README.md#propertybag) | undefined_

_Inherited from [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)_

**Parameters:**

| Name       | Type                                                    |
| ---------- | ------------------------------------------------------- |
| `context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _[PropertyBag](../README.md#propertybag) | undefined_

---

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): _boolean_

_Inherited from [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)_

**Parameters:**

| Name        | Type   |
| ----------- | ------ |
| `maxHeight` | number |

**Returns:** _boolean_

---

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): _void_

_Inherited from [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)_

**Returns:** _void_

---

### `Protected` updateInputControlAriaLabelledBy

▸ **updateInputControlAriaLabelledBy**(): _void_

_Overrides [Input](input.md).[updateInputControlAriaLabelledBy](input.md#protected-updateinputcontrolarialabelledby)_

**Returns:** _void_

---

### updateLayout

▸ **updateLayout**(`processChildren`: boolean): _void_

_Inherited from [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)_

**Parameters:**

| Name              | Type    | Default |
| ----------------- | ------- | ------- |
| `processChildren` | boolean | true    |

**Returns:** _void_

---

### validateProperties

▸ **validateProperties**(): _[ValidationResults](validationresults.md)_

_Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)_

**Returns:** _[ValidationResults](validationresults.md)_

---

### validateValue

▸ **validateValue**(): _boolean_

_Implementation of [IInput](../interfaces/iinput.md)_

_Inherited from [Input](input.md).[validateValue](input.md#validatevalue)_

**Returns:** _boolean_

---

### `Protected` valueChanged

▸ **valueChanged**(): _void_

_Inherited from [Input](input.md).[valueChanged](input.md#protected-valuechanged)_

**Returns:** _void_
