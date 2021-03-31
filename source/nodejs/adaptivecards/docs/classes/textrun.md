[Adaptive Cards Javascript SDK](../README.md) › [TextRun](textrun.md)

# Class: TextRun

## Hierarchy

  ↳ [BaseTextBlock](basetextblock.md)

  ↳ **TextRun**

## Index

### Constructors

* [constructor](textrun.md#constructor)

### Properties

* [_parent](textrun.md#protected-optional-_parent)
* [_renderedElement](textrun.md#protected-optional-_renderedelement)
* [ariaHidden](textrun.md#ariahidden)
* [color](textrun.md#color)
* [customCssSelector](textrun.md#optional-customcssselector)
* [fontType](textrun.md#optional-fonttype)
* [height](textrun.md#height)
* [highlight](textrun.md#highlight)
* [horizontalAlignment](textrun.md#horizontalalignment)
* [id](textrun.md#optional-id)
* [isSubtle](textrun.md#issubtle)
* [italic](textrun.md#italic)
* [maxVersion](textrun.md#maxversion)
* [onPreProcessPropertyValue](textrun.md#optional-onpreprocesspropertyvalue)
* [selectAction](textrun.md#optional-selectaction)
* [separator](textrun.md#separator)
* [size](textrun.md#size)
* [spacing](textrun.md#spacing)
* [strikethrough](textrun.md#strikethrough)
* [underline](textrun.md#underline)
* [weight](textrun.md#weight)
* [colorProperty](textrun.md#static-colorproperty)
* [fontTypeProperty](textrun.md#static-fonttypeproperty)
* [heightProperty](textrun.md#static-heightproperty)
* [highlightProperty](textrun.md#static-highlightproperty)
* [horizontalAlignmentProperty](textrun.md#static-horizontalalignmentproperty)
* [idProperty](textrun.md#static-idproperty)
* [isSubtleProperty](textrun.md#static-issubtleproperty)
* [isVisibleProperty](textrun.md#static-isvisibleproperty)
* [italicProperty](textrun.md#static-italicproperty)
* [langProperty](textrun.md#static-langproperty)
* [onRegisterCustomProperties](textrun.md#static-optional-onregistercustomproperties)
* [requiresProperty](textrun.md#static-requiresproperty)
* [selectActionProperty](textrun.md#static-selectactionproperty)
* [separatorProperty](textrun.md#static-separatorproperty)
* [sizeProperty](textrun.md#static-sizeproperty)
* [spacingProperty](textrun.md#static-spacingproperty)
* [strikethroughProperty](textrun.md#static-strikethroughproperty)
* [textProperty](textrun.md#static-textproperty)
* [typeNameProperty](textrun.md#static-typenameproperty)
* [underlineProperty](textrun.md#static-underlineproperty)
* [weightProperty](textrun.md#static-weightproperty)

### Accessors

* [allowCustomPadding](textrun.md#protected-allowcustompadding)
* [defaultStyle](textrun.md#protected-defaultstyle)
* [effectiveColor](textrun.md#effectivecolor)
* [hasVisibleSeparator](textrun.md#hasvisibleseparator)
* [hostConfig](textrun.md#hostconfig)
* [index](textrun.md#index)
* [isInline](textrun.md#isinline)
* [isInteractive](textrun.md#isinteractive)
* [isStandalone](textrun.md#isstandalone)
* [isVisible](textrun.md#isvisible)
* [lang](textrun.md#lang)
* [parent](textrun.md#parent)
* [renderedElement](textrun.md#renderedelement)
* [requires](textrun.md#requires)
* [separatorElement](textrun.md#separatorelement)
* [separatorOrientation](textrun.md#protected-separatororientation)
* [text](textrun.md#text)
* [useDefaultSizing](textrun.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](textrun.md#protected-adjustrenderedelementsize)
* [applyPadding](textrun.md#protected-applypadding)
* [applyStylesTo](textrun.md#applystylesto)
* [asString](textrun.md#asstring)
* [createPlaceholderElement](textrun.md#protected-createplaceholderelement)
* [getActionAt](textrun.md#getactionat)
* [getActionById](textrun.md#getactionbyid)
* [getActionCount](textrun.md#getactioncount)
* [getAllInputs](textrun.md#getallinputs)
* [getColorDefinition](textrun.md#protected-getcolordefinition)
* [getCustomProperty](textrun.md#getcustomproperty)
* [getDefaultPadding](textrun.md#protected-getdefaultpadding)
* [getEffectivePadding](textrun.md#geteffectivepadding)
* [getEffectiveStyle](textrun.md#geteffectivestyle)
* [getEffectiveStyleDefinition](textrun.md#geteffectivestyledefinition)
* [getElementById](textrun.md#getelementbyid)
* [getFontSize](textrun.md#protected-getfontsize)
* [getForbiddenActionTypes](textrun.md#getforbiddenactiontypes)
* [getHasBackground](textrun.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](textrun.md#getimmediatesurroundingpadding)
* [getJsonTypeName](textrun.md#getjsontypename)
* [getPadding](textrun.md#protected-getpadding)
* [getParentContainer](textrun.md#getparentcontainer)
* [getResourceInformation](textrun.md#getresourceinformation)
* [getRootElement](textrun.md#getrootelement)
* [getRootObject](textrun.md#getrootobject)
* [getSchema](textrun.md#getschema)
* [getSchemaKey](textrun.md#protected-getschemakey)
* [getValue](textrun.md#protected-getvalue)
* [hasAllDefaultValues](textrun.md#hasalldefaultvalues)
* [hasDefaultValue](textrun.md#hasdefaultvalue)
* [indexOf](textrun.md#indexof)
* [init](textrun.md#init)
* [internalParse](textrun.md#protected-internalparse)
* [internalRender](textrun.md#protected-internalrender)
* [internalToJSON](textrun.md#protected-internaltojson)
* [internalValidateProperties](textrun.md#internalvalidateproperties)
* [isAtTheVeryBottom](textrun.md#isattheverybottom)
* [isAtTheVeryLeft](textrun.md#isattheveryleft)
* [isAtTheVeryRight](textrun.md#isattheveryright)
* [isAtTheVeryTop](textrun.md#isattheverytop)
* [isBleeding](textrun.md#isbleeding)
* [isBleedingAtBottom](textrun.md#isbleedingatbottom)
* [isBleedingAtTop](textrun.md#isbleedingattop)
* [isBottomElement](textrun.md#isbottomelement)
* [isDesignMode](textrun.md#isdesignmode)
* [isDisplayed](textrun.md#protected-isdisplayed)
* [isFirstElement](textrun.md#isfirstelement)
* [isHiddenDueToOverflow](textrun.md#ishiddenduetooverflow)
* [isLastElement](textrun.md#islastelement)
* [isLeftMostElement](textrun.md#isleftmostelement)
* [isRightMostElement](textrun.md#isrightmostelement)
* [isTopElement](textrun.md#istopelement)
* [overrideInternalRender](textrun.md#protected-overrideinternalrender)
* [parse](textrun.md#parse)
* [populateSchema](textrun.md#protected-populateschema)
* [preProcessPropertyValue](textrun.md#preprocesspropertyvalue)
* [remove](textrun.md#remove)
* [render](textrun.md#render)
* [resetDefaultValues](textrun.md#resetdefaultvalues)
* [setCustomProperty](textrun.md#setcustomproperty)
* [setPadding](textrun.md#protected-setpadding)
* [setParent](textrun.md#setparent)
* [setShouldFallback](textrun.md#setshouldfallback)
* [setText](textrun.md#protected-settext)
* [setValue](textrun.md#protected-setvalue)
* [shouldFallback](textrun.md#shouldfallback)
* [shouldSerialize](textrun.md#protected-shouldserialize)
* [toJSON](textrun.md#tojson)
* [truncateOverflow](textrun.md#protected-truncateoverflow)
* [undoOverflowTruncation](textrun.md#protected-undooverflowtruncation)
* [updateLayout](textrun.md#updatelayout)
* [validateProperties](textrun.md#validateproperties)

## Constructors

###  constructor

\+ **new TextRun**(`text?`: undefined | string): *[TextRun](textrun.md)*

*Inherited from [BaseTextBlock](basetextblock.md).[constructor](basetextblock.md#constructor)*

*Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`text?` | undefined &#124; string |

**Returns:** *[TextRun](textrun.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

___

###  ariaHidden

• **ariaHidden**: *boolean* = false

*Inherited from [BaseTextBlock](basetextblock.md).[ariaHidden](basetextblock.md#ariahidden)*

___

###  color

• **color**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Default

*Inherited from [BaseTextBlock](basetextblock.md).[color](basetextblock.md#color)*

___

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

___

### `Optional` fontType

• **fontType**? : *Enums.FontType*

*Inherited from [BaseTextBlock](basetextblock.md).[fontType](basetextblock.md#optional-fonttype)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

___

###  highlight

• **highlight**: *boolean* = false

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [BaseTextBlock](basetextblock.md).[isSubtle](basetextblock.md#issubtle)*

___

###  italic

• **italic**: *boolean* = false

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

___

### `Optional` selectAction

• **selectAction**? : *[Action](action.md)*

*Inherited from [BaseTextBlock](basetextblock.md).[selectAction](basetextblock.md#optional-selectaction)*

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Inherited from [BaseTextBlock](basetextblock.md).[size](basetextblock.md#size)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

___

###  strikethrough

• **strikethrough**: *boolean* = false

___

###  underline

• **underline**: *boolean* = false

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Default

*Inherited from [BaseTextBlock](basetextblock.md).[weight](basetextblock.md#weight)*

___

### `Static` colorProperty

▪ **colorProperty**: *[EnumProperty](enumproperty.md)‹[TextColor](../enums/textcolor.md)›* = new EnumProperty(
        Versions.v1_0,
        "color",
        Enums.TextColor,
        Enums.TextColor.Default)

*Inherited from [BaseTextBlock](basetextblock.md).[colorProperty](basetextblock.md#static-colorproperty)*

___

### `Static` fontTypeProperty

▪ **fontTypeProperty**: *[EnumProperty](enumproperty.md)‹[FontType](../enums/fonttype.md)›* = new EnumProperty(
        Versions.v1_2,
        "fontType",
        Enums.FontType)

*Inherited from [BaseTextBlock](basetextblock.md).[fontTypeProperty](basetextblock.md#static-fonttypeproperty)*

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

### `Static` highlightProperty

▪ **highlightProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "highlight", false)

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

### `Static` isSubtleProperty

▪ **isSubtleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(
        Versions.v1_0,
        "isSubtle",
        false)

*Inherited from [BaseTextBlock](basetextblock.md).[isSubtleProperty](basetextblock.md#static-issubtleproperty)*

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

___

### `Static` italicProperty

▪ **italicProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "italic", false)

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

*Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-langproperty)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities())

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

___

### `Static` selectActionProperty

▪ **selectActionProperty**: *[ActionProperty](actionproperty.md)‹›* = new ActionProperty(Versions.v1_0, "selectAction", [ "Action.ShowCard" ])

*Inherited from [BaseTextBlock](basetextblock.md).[selectActionProperty](basetextblock.md#static-selectactionproperty)*

___

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

___

### `Static` sizeProperty

▪ **sizeProperty**: *[EnumProperty](enumproperty.md)‹[TextSize](../enums/textsize.md)›* = new EnumProperty(
        Versions.v1_0,
        "size",
        Enums.TextSize,
        Enums.TextSize.Default)

*Inherited from [BaseTextBlock](basetextblock.md).[sizeProperty](basetextblock.md#static-sizeproperty)*

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

*Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-spacingproperty)*

___

### `Static` strikethroughProperty

▪ **strikethroughProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "strikethrough", false)

___

### `Static` textProperty

▪ **textProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(
        Versions.v1_0,
        "text",
        true)

*Inherited from [BaseTextBlock](basetextblock.md).[textProperty](basetextblock.md#static-textproperty)*

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

### `Static` underlineProperty

▪ **underlineProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_3, "underline", false)

___

### `Static` weightProperty

▪ **weightProperty**: *[EnumProperty](enumproperty.md)‹[TextWeight](../enums/textweight.md)›* = new EnumProperty(
        Versions.v1_0,
        "weight",
        Enums.TextWeight,
        Enums.TextWeight.Default)

*Inherited from [BaseTextBlock](basetextblock.md).[weightProperty](basetextblock.md#static-weightproperty)*

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

###  effectiveColor

• **get effectiveColor**(): *[TextColor](../enums/textcolor.md)*

*Inherited from [BaseTextBlock](basetextblock.md).[effectiveColor](basetextblock.md#effectivecolor)*

**Returns:** *[TextColor](../enums/textcolor.md)*

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

*Overrides [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Overrides [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

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

###  text

• **get text**(): *string | undefined*

*Inherited from [BaseTextBlock](basetextblock.md).[text](basetextblock.md#text)*

**Returns:** *string | undefined*

• **set text**(`value`: string | undefined): *void*

*Inherited from [BaseTextBlock](basetextblock.md).[text](basetextblock.md#text)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

**Returns:** *boolean*

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

###  applyStylesTo

▸ **applyStylesTo**(`targetElement`: HTMLElement): *void*

*Overrides [BaseTextBlock](basetextblock.md).[applyStylesTo](basetextblock.md#applystylesto)*

**Parameters:**

Name | Type |
------ | ------ |
`targetElement` | HTMLElement |

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

*Inherited from [BaseTextBlock](basetextblock.md).[asString](basetextblock.md#asstring)*

*Overrides [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

**Returns:** *string | undefined*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

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

*Inherited from [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

### `Protected` getColorDefinition

▸ **getColorDefinition**(`colorSet`: [ColorSetDefinition](colorsetdefinition.md), `color`: [TextColor](../enums/textcolor.md)): *[TextColorDefinition](textcolordefinition.md)*

*Inherited from [BaseTextBlock](basetextblock.md).[getColorDefinition](basetextblock.md#protected-getcolordefinition)*

**Parameters:**

Name | Type |
------ | ------ |
`colorSet` | [ColorSetDefinition](colorsetdefinition.md) |
`color` | [TextColor](../enums/textcolor.md) |

**Returns:** *[TextColorDefinition](textcolordefinition.md)*

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

### `Protected` getFontSize

▸ **getFontSize**(`fontType`: [FontTypeDefinition](fonttypedefinition.md)): *number*

*Inherited from [BaseTextBlock](basetextblock.md).[getFontSize](basetextblock.md#protected-getfontsize)*

**Parameters:**

Name | Type |
------ | ------ |
`fontType` | [FontTypeDefinition](fonttypedefinition.md) |

**Returns:** *number*

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

###  init

▸ **init**(`textDefinition`: [BaseTextDefinition](basetextdefinition.md)): *void*

*Inherited from [BaseTextBlock](basetextblock.md).[init](basetextblock.md#init)*

**Parameters:**

Name | Type |
------ | ------ |
`textDefinition` | [BaseTextDefinition](basetextdefinition.md) |

**Returns:** *void*

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

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

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

*Overrides [BaseTextBlock](basetextblock.md).[populateSchema](basetextblock.md#protected-populateschema)*

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

### `Protected` setText

▸ **setText**(`value`: string | undefined): *void*

*Inherited from [BaseTextBlock](basetextblock.md).[setText](basetextblock.md#protected-settext)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

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

**Returns:** *[ValidationResults](validationresults.md)*
