[Adaptive Cards Javascript SDK](../README.md) › [BaseTextBlock](basetextblock.md)

# Class: BaseTextBlock

## Hierarchy

  ↳ [CardElement](cardelement.md)

  ↳ **BaseTextBlock**

  ↳ [TextBlock](textblock.md)

  ↳ [TextRun](textrun.md)

## Index

### Properties

* [color](basetextblock.md#color)
* [customCssSelector](basetextblock.md#customcssselector)
* [fontType](basetextblock.md#optional-fonttype)
* [height](basetextblock.md#height)
* [horizontalAlignment](basetextblock.md#optional-horizontalalignment)
* [id](basetextblock.md#id)
* [isSubtle](basetextblock.md#issubtle)
* [minPixelHeight](basetextblock.md#optional-minpixelheight)
* [requires](basetextblock.md#requires)
* [separator](basetextblock.md#separator)
* [size](basetextblock.md#size)
* [spacing](basetextblock.md#spacing)
* [weight](basetextblock.md#weight)

### Accessors

* [allowCustomPadding](basetextblock.md#protected-allowcustompadding)
* [defaultStyle](basetextblock.md#protected-defaultstyle)
* [effectiveColor](basetextblock.md#effectivecolor)
* [hasVisibleSeparator](basetextblock.md#hasvisibleseparator)
* [hostConfig](basetextblock.md#hostconfig)
* [index](basetextblock.md#index)
* [isInline](basetextblock.md#isinline)
* [isInteractive](basetextblock.md#isinteractive)
* [isStandalone](basetextblock.md#isstandalone)
* [isVisible](basetextblock.md#isvisible)
* [lang](basetextblock.md#lang)
* [parent](basetextblock.md#parent)
* [renderedElement](basetextblock.md#renderedelement)
* [selectAction](basetextblock.md#selectaction)
* [separatorElement](basetextblock.md#separatorelement)
* [separatorOrientation](basetextblock.md#protected-separatororientation)
* [supportsMinHeight](basetextblock.md#protected-supportsminheight)
* [text](basetextblock.md#text)
* [useDefaultSizing](basetextblock.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](basetextblock.md#protected-adjustrenderedelementsize)
* [applyPadding](basetextblock.md#protected-applypadding)
* [applyStylesTo](basetextblock.md#applystylesto)
* [asString](basetextblock.md#asstring)
* [createPlaceholderElement](basetextblock.md#protected-createplaceholderelement)
* [getActionAt](basetextblock.md#getactionat)
* [getActionById](basetextblock.md#getactionbyid)
* [getActionCount](basetextblock.md#getactioncount)
* [getAllInputs](basetextblock.md#getallinputs)
* [getColorDefinition](basetextblock.md#protected-getcolordefinition)
* [getCustomProperty](basetextblock.md#getcustomproperty)
* [getDefaultPadding](basetextblock.md#protected-getdefaultpadding)
* [getEffectivePadding](basetextblock.md#geteffectivepadding)
* [getEffectiveStyle](basetextblock.md#geteffectivestyle)
* [getEffectiveStyleDefinition](basetextblock.md#protected-geteffectivestyledefinition)
* [getElementById](basetextblock.md#getelementbyid)
* [getFontSize](basetextblock.md#protected-getfontsize)
* [getForbiddenActionTypes](basetextblock.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](basetextblock.md#getforbiddenelementtypes)
* [getHasBackground](basetextblock.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](basetextblock.md#getimmediatesurroundingpadding)
* [getJsonTypeName](basetextblock.md#abstract-getjsontypename)
* [getPadding](basetextblock.md#protected-getpadding)
* [getParentContainer](basetextblock.md#getparentcontainer)
* [getResourceInformation](basetextblock.md#getresourceinformation)
* [getRootElement](basetextblock.md#getrootelement)
* [indexOf](basetextblock.md#indexof)
* [internalRender](basetextblock.md#protected-abstract-internalrender)
* [internalValidateProperties](basetextblock.md#internalvalidateproperties)
* [isAtTheVeryBottom](basetextblock.md#isattheverybottom)
* [isAtTheVeryLeft](basetextblock.md#isattheveryleft)
* [isAtTheVeryRight](basetextblock.md#isattheveryright)
* [isAtTheVeryTop](basetextblock.md#isattheverytop)
* [isBleeding](basetextblock.md#isbleeding)
* [isBleedingAtBottom](basetextblock.md#isbleedingatbottom)
* [isBleedingAtTop](basetextblock.md#isbleedingattop)
* [isBottomElement](basetextblock.md#isbottomelement)
* [isDesignMode](basetextblock.md#isdesignmode)
* [isFirstElement](basetextblock.md#isfirstelement)
* [isHiddenDueToOverflow](basetextblock.md#ishiddenduetooverflow)
* [isLastElement](basetextblock.md#islastelement)
* [isLeftMostElement](basetextblock.md#isleftmostelement)
* [isRendered](basetextblock.md#isrendered)
* [isRightMostElement](basetextblock.md#isrightmostelement)
* [isTopElement](basetextblock.md#istopelement)
* [overrideInternalRender](basetextblock.md#protected-overrideinternalrender)
* [parse](basetextblock.md#parse)
* [remove](basetextblock.md#remove)
* [render](basetextblock.md#render)
* [setCustomProperty](basetextblock.md#setcustomproperty)
* [setPadding](basetextblock.md#protected-setpadding)
* [setParent](basetextblock.md#setparent)
* [setShouldFallback](basetextblock.md#setshouldfallback)
* [setText](basetextblock.md#protected-settext)
* [shouldFallback](basetextblock.md#shouldfallback)
* [toJSON](basetextblock.md#tojson)
* [truncateOverflow](basetextblock.md#protected-truncateoverflow)
* [undoOverflowTruncation](basetextblock.md#protected-undooverflowtruncation)
* [updateLayout](basetextblock.md#updatelayout)
* [validateProperties](basetextblock.md#validateproperties)

## Properties

###  color

• **color**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Default

*Defined in [card-elements.ts:1013](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1013)*

___

###  customCssSelector

• **customCssSelector**: *string* = null

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#customcssselector)*

*Defined in [card-elements.ts:507](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L507)*

___

### `Optional` fontType

• **fontType**? : *[FontType](../enums/fonttype.md)* = null

*Defined in [card-elements.ts:1015](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1015)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)* = "auto"

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

*Defined in [card-elements.ts:508](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L508)*

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../enums/horizontalalignment.md)* = null

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#optional-horizontalalignment)*

*Defined in [card-elements.ts:504](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L504)*

___

###  id

• **id**: *string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#id)*

*Defined in [card-elements.ts:247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L247)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Defined in [card-elements.ts:1014](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1014)*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *number* = null

*Inherited from [CardElement](cardelement.md).[minPixelHeight](cardelement.md#optional-minpixelheight)*

*Defined in [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L509)*

___

###  requires

• **requires**: *[HostCapabilities](hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

*Inherited from [CardElement](cardelement.md).[requires](cardelement.md#requires)*

*Defined in [card-elements.ts:502](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L502)*

___

###  separator

• **separator**: *boolean* = false

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

*Defined in [card-elements.ts:506](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L506)*

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Defined in [card-elements.ts:1011](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1011)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)* = Enums.Spacing.Default

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

*Defined in [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L505)*

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Default

*Defined in [card-elements.ts:1012](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1012)*

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

*Defined in [card-elements.ts:490](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L490)*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

*Defined in [card-elements.ts:498](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L498)*

**Returns:** *string*

___

###  effectiveColor

• **get effectiveColor**(): *[TextColor](../enums/textcolor.md)*

*Defined in [card-elements.ts:1128](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1128)*

**Returns:** *[TextColor](../enums/textcolor.md)*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Inherited from [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)*

*Defined in [card-elements.ts:928](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L928)*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Defined in [card-elements.ts:881](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L881)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Defined in [card-elements.ts:895](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L895)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

*Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)*

*Defined in [card-elements.ts:899](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L899)*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

*Defined in [card-elements.ts:916](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L916)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

*Defined in [card-elements.ts:908](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L908)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

*Defined in [card-elements.ts:912](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L912)*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

*Defined in [card-elements.ts:924](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L924)*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

*Defined in [card-elements.ts:937](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L937)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

*Defined in [card-elements.ts:853](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L853)*

**Returns:** *string*

• **set lang**(`value`: string): *void*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

*Defined in [card-elements.ts:867](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L867)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)*

*Defined in [card-elements.ts:920](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L920)*

**Returns:** *[CardElement](cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[renderedElement](cardelement.md#renderedelement)*

*Defined in [card-elements.ts:956](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L956)*

**Returns:** *HTMLElement*

___

###  selectAction

• **get selectAction**(): *[Action](action.md)*

*Defined in [card-elements.ts:1140](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1140)*

**Returns:** *[Action](action.md)*

• **set selectAction**(`value`: [Action](action.md)): *void*

*Defined in [card-elements.ts:1144](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1144)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [Action](action.md) |

**Returns:** *void*

___

###  separatorElement

• **get separatorElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)*

*Defined in [card-elements.ts:960](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L960)*

**Returns:** *HTMLElement*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

*Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

*Defined in [card-elements.ts:494](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L494)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

### `Protected` supportsMinHeight

• **get supportsMinHeight**(): *boolean*

*Inherited from [CardElement](cardelement.md).[supportsMinHeight](cardelement.md#protected-supportsminheight)*

*Defined in [card-elements.ts:482](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L482)*

**Returns:** *boolean*

___

###  text

• **get text**(): *string*

*Defined in [card-elements.ts:1132](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1132)*

**Returns:** *string*

• **set text**(`value`: string): *void*

*Defined in [card-elements.ts:1136](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1136)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

*Defined in [card-elements.ts:486](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L486)*

**Returns:** *boolean*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

*Defined in [card-elements.ts:411](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L411)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [CardElement](cardelement.md).[applyPadding](cardelement.md#protected-applypadding)*

*Defined in [card-elements.ts:430](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L430)*

**Returns:** *void*

___

###  applyStylesTo

▸ **applyStylesTo**(`targetElement`: HTMLElement): *void*

*Defined in [card-elements.ts:1034](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1034)*

**Parameters:**

Name | Type |
------ | ------ |
`targetElement` | HTMLElement |

**Returns:** *void*

___

###  asString

▸ **asString**(): *string*

*Overrides [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

*Defined in [card-elements.ts:1017](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1017)*

**Returns:** *string*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

*Defined in [card-elements.ts:400](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L400)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md)*

*Inherited from [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

*Defined in [card-elements.ts:694](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L694)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md)*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md)*

*Inherited from [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

*Defined in [card-elements.ts:835](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L835)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md)*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

*Defined in [card-elements.ts:690](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L690)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](input.md)›*

*Inherited from [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

*Defined in [card-elements.ts:823](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L823)*

**Returns:** *Array‹[Input](input.md)›*

___

### `Protected` getColorDefinition

▸ **getColorDefinition**(`colorSet`: [ColorSetDefinition](colorsetdefinition.md), `color`: [TextColor](../enums/textcolor.md)): *[TextColorDefinition](textcolordefinition.md)*

*Defined in [card-elements.ts:988](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L988)*

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

*Defined in [card-elements.ts:200](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L200)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getDefaultPadding](cardelement.md#protected-getdefaultpadding)*

*Defined in [card-elements.ts:466](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L466)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)*

*Defined in [card-elements.ts:847](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L847)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)*

*Defined in [card-elements.ts:545](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L545)*

**Returns:** *string*

___

### `Protected` getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)‹›*

*Defined in [card-elements.ts:969](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L969)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)‹›*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)*

*Defined in [card-elements.ts:831](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L831)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md)*

___

### `Protected` getFontSize

▸ **getFontSize**(`fontType`: [FontTypeDefinition](fonttypedefinition.md)): *number*

*Defined in [card-elements.ts:973](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L973)*

**Parameters:**

Name | Type |
------ | ------ |
`fontType` | [FontTypeDefinition](fonttypedefinition.md) |

**Returns:** *number*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *Array‹any›*

*Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)*

*Defined in [card-elements.ts:557](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L557)*

**Returns:** *Array‹any›*

___

###  getForbiddenElementTypes

▸ **getForbiddenElementTypes**(): *Array‹string›*

*Inherited from [CardElement](cardelement.md).[getForbiddenElementTypes](cardelement.md#getforbiddenelementtypes)*

*Defined in [card-elements.ts:553](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L553)*

**Returns:** *Array‹string›*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

*Inherited from [CardElement](cardelement.md).[getHasBackground](cardelement.md#protected-gethasbackground)*

*Defined in [card-elements.ts:470](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L470)*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)*

*Defined in [card-elements.ts:561](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L561)*

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

*Inherited from [CardElement](cardelement.md).[getJsonTypeName](cardelement.md#abstract-getjsontypename)*

*Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:511](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L511)*

**Returns:** *string*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)*

*Defined in [card-elements.ts:474](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L474)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md)*

*Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)*

*Defined in [card-elements.ts:809](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L809)*

**Returns:** *[Container](container.md)*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

*Inherited from [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

*Defined in [card-elements.ts:827](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L827)*

**Returns:** *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)*

*Defined in [card-elements.ts:799](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L799)*

**Returns:** *[CardElement](cardelement.md)*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): *number*

*Inherited from [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

*Defined in [card-elements.ts:733](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L733)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

___

### `Protected` `Abstract` internalRender

▸ **internalRender**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

*Defined in [card-elements.ts:424](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L424)*

**Returns:** *HTMLElement*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:249](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L249)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)*

*Defined in [card-elements.ts:767](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L767)*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)*

*Defined in [card-elements.ts:755](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L755)*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)*

*Defined in [card-elements.ts:759](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L759)*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)*

*Defined in [card-elements.ts:763](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L763)*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)*

*Defined in [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L517)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

*Defined in [card-elements.ts:775](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L775)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

*Defined in [card-elements.ts:771](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L771)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)*

*Defined in [card-elements.ts:791](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L791)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)*

*Defined in [card-elements.ts:737](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L737)*

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

*Defined in [card-elements.ts:747](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L747)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)*

*Defined in [card-elements.ts:795](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L795)*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)*

*Defined in [card-elements.ts:751](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L751)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)*

*Defined in [card-elements.ts:779](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L779)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRendered

▸ **isRendered**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isRendered](cardelement.md#isrendered)*

*Defined in [card-elements.ts:743](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L743)*

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)*

*Defined in [card-elements.ts:783](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L783)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)*

*Defined in [card-elements.ts:787](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L787)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)*

*Defined in [card-elements.ts:426](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L426)*

**Returns:** *HTMLElement*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [CardElement](cardelement.md).[parse](cardelement.md#parse)*

*Defined in [card-elements.ts:1084](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1084)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [CardElement](cardelement.md).[remove](cardelement.md#remove)*

*Defined in [card-elements.ts:698](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L698)*

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[render](cardelement.md#render)*

*Defined in [card-elements.ts:706](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L706)*

**Returns:** *HTMLElement*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

*Defined in [card-elements.ts:189](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L189)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](paddingdefinition.md)): *void*

*Inherited from [CardElement](cardelement.md).[setPadding](cardelement.md#protected-setpadding)*

*Defined in [card-elements.ts:478](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L478)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardElement](cardelement.md)): *void*

*Inherited from [CardElement](cardelement.md).[setParent](cardelement.md#setparent)*

*Overrides [CardObject](cardobject.md).[setParent](cardobject.md#abstract-setparent)*

*Defined in [card-elements.ts:541](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L541)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardElement](cardelement.md) |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[setShouldFallback](cardelement.md#setshouldfallback)*

*Defined in [card-elements.ts:843](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L843)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setText

▸ **setText**(`value`: string): *void*

*Defined in [card-elements.ts:1007](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1007)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [CardElement](cardelement.md).[shouldFallback](cardelement.md#shouldfallback)*

*Overrides [CardObject](cardobject.md).[shouldFallback](cardobject.md#abstract-shouldfallback)*

*Defined in [card-elements.ts:839](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L839)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [CardElement](cardelement.md).[toJSON](cardelement.md#tojson)*

*Defined in [card-elements.ts:1021](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L1021)*

**Returns:** *any*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Inherited from [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

*Defined in [card-elements.ts:454](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L454)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Inherited from [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

*Defined in [card-elements.ts:464](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L464)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)*

*Defined in [card-elements.ts:728](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L728)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | true |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

*Defined in [card-elements.ts:284](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L284)*

**Returns:** *[ValidationResults](validationresults.md)*
