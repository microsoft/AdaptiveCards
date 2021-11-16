[Adaptive Cards Javascript SDK](../README.md) › [TextRun](textrun.md)

# Class: TextRun

## Hierarchy

↳ [BaseTextBlock](basetextblock.md)

↳ **TextRun**

## Index

### Constructors

- [constructor](textrun.md#constructor)

### Properties

- [\_parent](textrun.md#protected-optional-_parent)
- [\_renderedElement](textrun.md#protected-optional-_renderedelement)
- [ariaHidden](textrun.md#ariahidden)
- [color](textrun.md#color)
- [customCssSelector](textrun.md#optional-customcssselector)
- [fontType](textrun.md#optional-fonttype)
- [height](textrun.md#height)
- [highlight](textrun.md#highlight)
- [horizontalAlignment](textrun.md#horizontalalignment)
- [id](textrun.md#optional-id)
- [isSubtle](textrun.md#issubtle)
- [italic](textrun.md#italic)
- [maxVersion](textrun.md#maxversion)
- [onPreProcessPropertyValue](textrun.md#optional-onpreprocesspropertyvalue)
- [selectAction](textrun.md#optional-selectaction)
- [separator](textrun.md#separator)
- [size](textrun.md#size)
- [spacing](textrun.md#spacing)
- [strikethrough](textrun.md#strikethrough)
- [underline](textrun.md#underline)
- [weight](textrun.md#weight)
- [colorProperty](textrun.md#static-readonly-colorproperty)
- [fontTypeProperty](textrun.md#static-readonly-fonttypeproperty)
- [heightProperty](textrun.md#static-readonly-heightproperty)
- [highlightProperty](textrun.md#static-readonly-highlightproperty)
- [horizontalAlignmentProperty](textrun.md#static-readonly-horizontalalignmentproperty)
- [idProperty](textrun.md#static-readonly-idproperty)
- [isSubtleProperty](textrun.md#static-readonly-issubtleproperty)
- [isVisibleProperty](textrun.md#static-readonly-isvisibleproperty)
- [italicProperty](textrun.md#static-readonly-italicproperty)
- [langProperty](textrun.md#static-readonly-langproperty)
- [onRegisterCustomProperties](textrun.md#static-optional-onregistercustomproperties)
- [requiresProperty](textrun.md#static-readonly-requiresproperty)
- [selectActionProperty](textrun.md#static-readonly-selectactionproperty)
- [separatorProperty](textrun.md#static-readonly-separatorproperty)
- [sizeProperty](textrun.md#static-readonly-sizeproperty)
- [spacingProperty](textrun.md#static-readonly-spacingproperty)
- [strikethroughProperty](textrun.md#static-readonly-strikethroughproperty)
- [textProperty](textrun.md#static-readonly-textproperty)
- [typeNameProperty](textrun.md#static-readonly-typenameproperty)
- [underlineProperty](textrun.md#static-readonly-underlineproperty)
- [weightProperty](textrun.md#static-readonly-weightproperty)

### Accessors

- [allowCustomPadding](textrun.md#protected-allowcustompadding)
- [defaultStyle](textrun.md#protected-defaultstyle)
- [effectiveColor](textrun.md#effectivecolor)
- [hasVisibleSeparator](textrun.md#hasvisibleseparator)
- [hostConfig](textrun.md#hostconfig)
- [index](textrun.md#index)
- [isInline](textrun.md#isinline)
- [isInteractive](textrun.md#isinteractive)
- [isStandalone](textrun.md#isstandalone)
- [isVisible](textrun.md#isvisible)
- [lang](textrun.md#lang)
- [parent](textrun.md#parent)
- [renderedElement](textrun.md#renderedelement)
- [requires](textrun.md#requires)
- [separatorElement](textrun.md#separatorelement)
- [separatorOrientation](textrun.md#protected-separatororientation)
- [text](textrun.md#text)
- [useDefaultSizing](textrun.md#protected-usedefaultsizing)

### Methods

- [adjustRenderedElementSize](textrun.md#protected-adjustrenderedelementsize)
- [applyPadding](textrun.md#protected-applypadding)
- [applyStylesTo](textrun.md#applystylesto)
- [asString](textrun.md#asstring)
- [createPlaceholderElement](textrun.md#protected-createplaceholderelement)
- [getActionAt](textrun.md#getactionat)
- [getActionById](textrun.md#getactionbyid)
- [getActionCount](textrun.md#getactioncount)
- [getAllInputs](textrun.md#getallinputs)
- [getColorDefinition](textrun.md#protected-getcolordefinition)
- [getCustomProperty](textrun.md#getcustomproperty)
- [getDefaultPadding](textrun.md#protected-getdefaultpadding)
- [getDefaultSerializationContext](textrun.md#protected-getdefaultserializationcontext)
- [getEffectivePadding](textrun.md#geteffectivepadding)
- [getEffectiveStyle](textrun.md#geteffectivestyle)
- [getEffectiveStyleDefinition](textrun.md#geteffectivestyledefinition)
- [getElementById](textrun.md#getelementbyid)
- [getFontSize](textrun.md#protected-getfontsize)
- [getForbiddenActionTypes](textrun.md#getforbiddenactiontypes)
- [getHasBackground](textrun.md#protected-gethasbackground)
- [getImmediateSurroundingPadding](textrun.md#getimmediatesurroundingpadding)
- [getJsonTypeName](textrun.md#getjsontypename)
- [getPadding](textrun.md#protected-getpadding)
- [getParentContainer](textrun.md#getparentcontainer)
- [getResourceInformation](textrun.md#getresourceinformation)
- [getRootElement](textrun.md#getrootelement)
- [getRootObject](textrun.md#getrootobject)
- [getSchema](textrun.md#getschema)
- [getSchemaKey](textrun.md#protected-getschemakey)
- [getValue](textrun.md#protected-getvalue)
- [hasAllDefaultValues](textrun.md#hasalldefaultvalues)
- [hasDefaultValue](textrun.md#hasdefaultvalue)
- [indexOf](textrun.md#indexof)
- [init](textrun.md#init)
- [internalParse](textrun.md#protected-internalparse)
- [internalRender](textrun.md#protected-internalrender)
- [internalToJSON](textrun.md#protected-internaltojson)
- [internalValidateProperties](textrun.md#internalvalidateproperties)
- [isAtTheVeryBottom](textrun.md#isattheverybottom)
- [isAtTheVeryLeft](textrun.md#isattheveryleft)
- [isAtTheVeryRight](textrun.md#isattheveryright)
- [isAtTheVeryTop](textrun.md#isattheverytop)
- [isBleeding](textrun.md#isbleeding)
- [isBleedingAtBottom](textrun.md#isbleedingatbottom)
- [isBleedingAtTop](textrun.md#isbleedingattop)
- [isBottomElement](textrun.md#isbottomelement)
- [isDesignMode](textrun.md#isdesignmode)
- [isDisplayed](textrun.md#protected-isdisplayed)
- [isFirstElement](textrun.md#isfirstelement)
- [isHiddenDueToOverflow](textrun.md#ishiddenduetooverflow)
- [isLastElement](textrun.md#islastelement)
- [isLeftMostElement](textrun.md#isleftmostelement)
- [isRightMostElement](textrun.md#isrightmostelement)
- [isTopElement](textrun.md#istopelement)
- [overrideInternalRender](textrun.md#protected-overrideinternalrender)
- [parse](textrun.md#parse)
- [populateSchema](textrun.md#protected-populateschema)
- [preProcessPropertyValue](textrun.md#preprocesspropertyvalue)
- [remove](textrun.md#remove)
- [render](textrun.md#render)
- [resetDefaultValues](textrun.md#resetdefaultvalues)
- [setCustomProperty](textrun.md#setcustomproperty)
- [setPadding](textrun.md#protected-setpadding)
- [setParent](textrun.md#setparent)
- [setShouldFallback](textrun.md#setshouldfallback)
- [setText](textrun.md#protected-settext)
- [setValue](textrun.md#protected-setvalue)
- [shouldFallback](textrun.md#shouldfallback)
- [shouldSerialize](textrun.md#protected-shouldserialize)
- [toJSON](textrun.md#tojson)
- [truncateOverflow](textrun.md#protected-truncateoverflow)
- [undoOverflowTruncation](textrun.md#protected-undooverflowtruncation)
- [updateLayout](textrun.md#updatelayout)
- [validateProperties](textrun.md#validateproperties)

## Constructors

### constructor

\+ **new TextRun**(`text?`: undefined | string): _[TextRun](textrun.md)_

_Inherited from [BaseTextBlock](basetextblock.md).[constructor](basetextblock.md#constructor)_

_Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)_

**Parameters:**

| Name    | Type                    |
| ------- | ----------------------- |
| `text?` | undefined &#124; string |

**Returns:** _[TextRun](textrun.md)_

## Properties

### `Protected` `Optional` \_parent

• **\_parent**? : _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[\_parent](cardobject.md#protected-optional-_parent)_

---

### `Protected` `Optional` \_renderedElement

• **\_renderedElement**? : _HTMLElement_

_Inherited from [CardObject](cardobject.md).[\_renderedElement](cardobject.md#protected-optional-_renderedelement)_

---

### ariaHidden

• **ariaHidden**: _boolean_ = false

_Inherited from [BaseTextBlock](basetextblock.md).[ariaHidden](basetextblock.md#ariahidden)_

---

### color

• **color**: _[TextColor](../enums/textcolor.md)_ = Enums.TextColor.Default

_Inherited from [BaseTextBlock](basetextblock.md).[color](basetextblock.md#color)_

---

### `Optional` customCssSelector

• **customCssSelector**? : _undefined | string_

_Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)_

---

### `Optional` fontType

• **fontType**? : _Enums.FontType_

_Inherited from [BaseTextBlock](basetextblock.md).[fontType](basetextblock.md#optional-fonttype)_

---

### height

• **height**: _[CardElementHeight](../README.md#cardelementheight)_

_Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)_

---

### highlight

• **highlight**: _boolean_ = false

---

### horizontalAlignment

• **horizontalAlignment**: _[HorizontalAlignment](../enums/horizontalalignment.md)_

_Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)_

---

### `Optional` id

• **id**? : _undefined | string_

_Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)_

---

### isSubtle

• **isSubtle**: _boolean_ = false

_Inherited from [BaseTextBlock](basetextblock.md).[isSubtle](basetextblock.md#issubtle)_

---

### italic

• **italic**: _boolean_ = false

---

### maxVersion

• **maxVersion**: _[Version](version.md)_ = Versions.v1_3

_Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)_

---

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : _undefined | function_

_Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)_

---

### `Optional` selectAction

• **selectAction**? : _[Action](action.md)_

_Inherited from [BaseTextBlock](basetextblock.md).[selectAction](basetextblock.md#optional-selectaction)_

---

### separator

• **separator**: _boolean_

_Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)_

---

### size

• **size**: _[TextSize](../enums/textsize.md)_ = Enums.TextSize.Default

_Inherited from [BaseTextBlock](basetextblock.md).[size](basetextblock.md#size)_

---

### spacing

• **spacing**: _[Spacing](../enums/spacing.md)_

_Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)_

---

### strikethrough

• **strikethrough**: _boolean_ = false

---

### underline

• **underline**: _boolean_ = false

---

### weight

• **weight**: _[TextWeight](../enums/textweight.md)_ = Enums.TextWeight.Default

_Inherited from [BaseTextBlock](basetextblock.md).[weight](basetextblock.md#weight)_

---

### `Static` `Readonly` colorProperty

▪ **colorProperty**: _[EnumProperty](enumproperty.md)‹[TextColor](../enums/textcolor.md)›_ = new EnumProperty(
Versions.v1_0,
"color",
Enums.TextColor,
Enums.TextColor.Default)

_Inherited from [BaseTextBlock](basetextblock.md).[colorProperty](basetextblock.md#static-readonly-colorproperty)_

---

### `Static` `Readonly` fontTypeProperty

▪ **fontTypeProperty**: _[EnumProperty](enumproperty.md)‹[FontType](../enums/fonttype.md)›_ = new EnumProperty(
Versions.v1_2,
"fontType",
Enums.FontType)

_Inherited from [BaseTextBlock](basetextblock.md).[fontTypeProperty](basetextblock.md#static-readonly-fonttypeproperty)_

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

### `Static` `Readonly` highlightProperty

▪ **highlightProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "highlight", false)

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

### `Static` `Readonly` isSubtleProperty

▪ **isSubtleProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(
Versions.v1_0,
"isSubtle",
false)

_Inherited from [BaseTextBlock](basetextblock.md).[isSubtleProperty](basetextblock.md#static-readonly-issubtleproperty)_

---

### `Static` `Readonly` isVisibleProperty

▪ **isVisibleProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "isVisible", true)

_Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-readonly-isvisibleproperty)_

---

### `Static` `Readonly` italicProperty

▪ **italicProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "italic", false)

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

### `Static` `Readonly` selectActionProperty

▪ **selectActionProperty**: _[ActionProperty](actionproperty.md)‹›_ = new ActionProperty(Versions.v1_1, "selectAction", [ "Action.ShowCard" ])

_Inherited from [BaseTextBlock](basetextblock.md).[selectActionProperty](basetextblock.md#static-readonly-selectactionproperty)_

---

### `Static` `Readonly` separatorProperty

▪ **separatorProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_0, "separator", false)

_Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-readonly-separatorproperty)_

---

### `Static` `Readonly` sizeProperty

▪ **sizeProperty**: _[EnumProperty](enumproperty.md)‹[TextSize](../enums/textsize.md)›_ = new EnumProperty(
Versions.v1_0,
"size",
Enums.TextSize,
Enums.TextSize.Default)

_Inherited from [BaseTextBlock](basetextblock.md).[sizeProperty](basetextblock.md#static-readonly-sizeproperty)_

---

### `Static` `Readonly` spacingProperty

▪ **spacingProperty**: _[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›_ = new EnumProperty(
Versions.v1_0,
"spacing",
Enums.Spacing,
Enums.Spacing.Default)

_Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-readonly-spacingproperty)_

---

### `Static` `Readonly` strikethroughProperty

▪ **strikethroughProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "strikethrough", false)

---

### `Static` `Readonly` textProperty

▪ **textProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(
Versions.v1_0,
"text",
true)

_Inherited from [BaseTextBlock](basetextblock.md).[textProperty](basetextblock.md#static-readonly-textproperty)_

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

### `Static` `Readonly` underlineProperty

▪ **underlineProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_3, "underline", false)

---

### `Static` `Readonly` weightProperty

▪ **weightProperty**: _[EnumProperty](enumproperty.md)‹[TextWeight](../enums/textweight.md)›_ = new EnumProperty(
Versions.v1_0,
"weight",
Enums.TextWeight,
Enums.TextWeight.Default)

_Inherited from [BaseTextBlock](basetextblock.md).[weightProperty](basetextblock.md#static-readonly-weightproperty)_

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

### effectiveColor

• **get effectiveColor**(): _[TextColor](../enums/textcolor.md)_

_Inherited from [BaseTextBlock](basetextblock.md).[effectiveColor](basetextblock.md#effectivecolor)_

**Returns:** _[TextColor](../enums/textcolor.md)_

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

### isInline

• **get isInline**(): _boolean_

_Overrides [CardElement](cardelement.md).[isInline](cardelement.md#isinline)_

**Returns:** _boolean_

---

### isInteractive

• **get isInteractive**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)_

**Returns:** _boolean_

---

### isStandalone

• **get isStandalone**(): _boolean_

_Overrides [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)_

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

### text

• **get text**(): _string | undefined_

_Inherited from [BaseTextBlock](basetextblock.md).[text](basetextblock.md#text)_

**Returns:** _string | undefined_

• **set text**(`value`: string | undefined): _void_

_Inherited from [BaseTextBlock](basetextblock.md).[text](basetextblock.md#text)_

**Parameters:**

| Name    | Type                    |
| ------- | ----------------------- |
| `value` | string &#124; undefined |

**Returns:** _void_

---

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): _boolean_

_Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)_

**Returns:** _boolean_

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

### applyStylesTo

▸ **applyStylesTo**(`targetElement`: HTMLElement): _void_

_Overrides [BaseTextBlock](basetextblock.md).[applyStylesTo](basetextblock.md#applystylesto)_

**Parameters:**

| Name            | Type        |
| --------------- | ----------- |
| `targetElement` | HTMLElement |

**Returns:** _void_

---

### asString

▸ **asString**(): _string | undefined_

_Inherited from [BaseTextBlock](basetextblock.md).[asString](basetextblock.md#asstring)_

_Overrides [CardElement](cardelement.md).[asString](cardelement.md#asstring)_

**Returns:** _string | undefined_

---

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): _HTMLElement_

_Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)_

**Returns:** _HTMLElement_

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

_Inherited from [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)_

**Parameters:**

| Name             | Type    | Default |
| ---------------- | ------- | ------- |
| `processActions` | boolean | true    |

**Returns:** _[Input](input.md)[]_

---

### `Protected` getColorDefinition

▸ **getColorDefinition**(`colorSet`: [ColorSetDefinition](colorsetdefinition.md), `color`: [TextColor](../enums/textcolor.md)): _[TextColorDefinition](textcolordefinition.md)_

_Inherited from [BaseTextBlock](basetextblock.md).[getColorDefinition](basetextblock.md#protected-getcolordefinition)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `colorSet` | [ColorSetDefinition](colorsetdefinition.md) |
| `color`    | [TextColor](../enums/textcolor.md)          |

**Returns:** _[TextColorDefinition](textcolordefinition.md)_

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

### `Protected` getFontSize

▸ **getFontSize**(`fontType`: [FontTypeDefinition](fonttypedefinition.md)): _number_

_Inherited from [BaseTextBlock](basetextblock.md).[getFontSize](basetextblock.md#protected-getfontsize)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `fontType` | [FontTypeDefinition](fonttypedefinition.md) |

**Returns:** _number_

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

### init

▸ **init**(`textDefinition`: [BaseTextDefinition](basetextdefinition.md)): _void_

_Inherited from [BaseTextBlock](basetextblock.md).[init](basetextblock.md#init)_

**Parameters:**

| Name             | Type                                        |
| ---------------- | ------------------------------------------- |
| `textDefinition` | [BaseTextDefinition](basetextdefinition.md) |

**Returns:** _void_

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

_Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)_

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

### isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): _HTMLElement | undefined_

_Inherited from [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)_

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

_Overrides [BaseTextBlock](basetextblock.md).[populateSchema](basetextblock.md#protected-populateschema)_

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

### `Protected` setText

▸ **setText**(`value`: string | undefined): _void_

_Inherited from [BaseTextBlock](basetextblock.md).[setText](basetextblock.md#protected-settext)_

**Parameters:**

| Name    | Type                    |
| ------- | ----------------------- |
| `value` | string &#124; undefined |

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
