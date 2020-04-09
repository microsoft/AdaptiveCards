[Adaptive Cards Javascript SDK](../README.md) › [ColumnSet](columnset.md)

# Class: ColumnSet

## Hierarchy

  ↳ [StylableCardElementContainer](stylablecardelementcontainer.md)

  ↳ **ColumnSet**

## Index

### Properties

* [allowVerticalOverflow](columnset.md#allowverticaloverflow)
* [customCssSelector](columnset.md#customcssselector)
* [height](columnset.md#height)
* [horizontalAlignment](columnset.md#optional-horizontalalignment)
* [id](columnset.md#id)
* [minPixelHeight](columnset.md#optional-minpixelheight)
* [requires](columnset.md#requires)
* [separator](columnset.md#separator)
* [spacing](columnset.md#spacing)

### Accessors

* [allowCustomPadding](columnset.md#protected-allowcustompadding)
* [allowCustomStyle](columnset.md#protected-allowcustomstyle)
* [bleed](columnset.md#bleed)
* [defaultStyle](columnset.md#protected-defaultstyle)
* [hasExplicitStyle](columnset.md#protected-hasexplicitstyle)
* [hasVisibleSeparator](columnset.md#hasvisibleseparator)
* [hostConfig](columnset.md#hostconfig)
* [index](columnset.md#index)
* [isInline](columnset.md#isinline)
* [isInteractive](columnset.md#isinteractive)
* [isSelectable](columnset.md#protected-isselectable)
* [isStandalone](columnset.md#isstandalone)
* [isVisible](columnset.md#isvisible)
* [lang](columnset.md#lang)
* [padding](columnset.md#padding)
* [parent](columnset.md#parent)
* [renderedActionCount](columnset.md#protected-renderedactioncount)
* [renderedElement](columnset.md#renderedelement)
* [selectAction](columnset.md#selectaction)
* [separatorElement](columnset.md#separatorelement)
* [separatorOrientation](columnset.md#protected-separatororientation)
* [style](columnset.md#style)
* [supportsMinHeight](columnset.md#protected-supportsminheight)
* [useDefaultSizing](columnset.md#protected-usedefaultsizing)

### Methods

* [addColumn](columnset.md#addcolumn)
* [adjustRenderedElementSize](columnset.md#protected-adjustrenderedelementsize)
* [applyBackground](columnset.md#protected-applybackground)
* [applyPadding](columnset.md#protected-applypadding)
* [asString](columnset.md#asstring)
* [createPlaceholderElement](columnset.md#protected-createplaceholderelement)
* [getActionAt](columnset.md#getactionat)
* [getActionById](columnset.md#getactionbyid)
* [getActionCount](columnset.md#getactioncount)
* [getAllInputs](columnset.md#getallinputs)
* [getBleed](columnset.md#protected-getbleed)
* [getColumnAt](columnset.md#getcolumnat)
* [getCount](columnset.md#getcount)
* [getCustomProperty](columnset.md#getcustomproperty)
* [getDefaultPadding](columnset.md#protected-getdefaultpadding)
* [getEffectivePadding](columnset.md#geteffectivepadding)
* [getEffectiveStyle](columnset.md#geteffectivestyle)
* [getElementById](columnset.md#getelementbyid)
* [getFirstVisibleRenderedItem](columnset.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](columnset.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](columnset.md#getforbiddenelementtypes)
* [getHasBackground](columnset.md#protected-gethasbackground)
* [getHasExpandedAction](columnset.md#protected-gethasexpandedaction)
* [getImmediateSurroundingPadding](columnset.md#getimmediatesurroundingpadding)
* [getItemAt](columnset.md#getitemat)
* [getItemCount](columnset.md#getitemcount)
* [getJsonTypeName](columnset.md#getjsontypename)
* [getLastVisibleRenderedItem](columnset.md#getlastvisiblerendereditem)
* [getPadding](columnset.md#protected-getpadding)
* [getParentContainer](columnset.md#getparentcontainer)
* [getResourceInformation](columnset.md#getresourceinformation)
* [getRootElement](columnset.md#getrootelement)
* [getSelectAction](columnset.md#protected-getselectaction)
* [indexOf](columnset.md#indexof)
* [internalRender](columnset.md#protected-internalrender)
* [internalValidateProperties](columnset.md#internalvalidateproperties)
* [isAtTheVeryBottom](columnset.md#isattheverybottom)
* [isAtTheVeryLeft](columnset.md#isattheveryleft)
* [isAtTheVeryRight](columnset.md#isattheveryright)
* [isAtTheVeryTop](columnset.md#isattheverytop)
* [isBleeding](columnset.md#isbleeding)
* [isBleedingAtBottom](columnset.md#isbleedingatbottom)
* [isBleedingAtTop](columnset.md#isbleedingattop)
* [isBottomElement](columnset.md#isbottomelement)
* [isDesignMode](columnset.md#isdesignmode)
* [isElementAllowed](columnset.md#protected-iselementallowed)
* [isFirstElement](columnset.md#isfirstelement)
* [isHiddenDueToOverflow](columnset.md#ishiddenduetooverflow)
* [isLastElement](columnset.md#islastelement)
* [isLeftMostElement](columnset.md#isleftmostelement)
* [isRendered](columnset.md#isrendered)
* [isRightMostElement](columnset.md#isrightmostelement)
* [isTopElement](columnset.md#istopelement)
* [overrideInternalRender](columnset.md#protected-overrideinternalrender)
* [parse](columnset.md#parse)
* [remove](columnset.md#remove)
* [removeItem](columnset.md#removeitem)
* [render](columnset.md#render)
* [setBleed](columnset.md#protected-setbleed)
* [setCustomProperty](columnset.md#setcustomproperty)
* [setPadding](columnset.md#protected-setpadding)
* [setParent](columnset.md#setparent)
* [setSelectAction](columnset.md#protected-setselectaction)
* [setShouldFallback](columnset.md#setshouldfallback)
* [shouldFallback](columnset.md#shouldfallback)
* [toJSON](columnset.md#tojson)
* [truncateOverflow](columnset.md#protected-truncateoverflow)
* [undoOverflowTruncation](columnset.md#protected-undooverflowtruncation)
* [updateLayout](columnset.md#updatelayout)
* [validateProperties](columnset.md#validateproperties)

## Properties

###  allowVerticalOverflow

• **allowVerticalOverflow**: *boolean* = false

*Inherited from [CardElementContainer](cardelementcontainer.md).[allowVerticalOverflow](cardelementcontainer.md#allowverticaloverflow)*

*Defined in [card-elements.ts:2229](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2229)*

___

###  customCssSelector

• **customCssSelector**: *string* = null

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#customcssselector)*

*Defined in [card-elements.ts:507](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L507)*

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

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)* = Enums.Spacing.Default

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

*Defined in [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L505)*

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

*Defined in [card-elements.ts:490](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L490)*

**Returns:** *boolean*

___

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[allowCustomStyle](stylablecardelementcontainer.md#protected-allowcustomstyle)*

*Defined in [card-elements.ts:5236](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5236)*

**Returns:** *boolean*

___

###  bleed

• **get bleed**(): *boolean*

*Defined in [card-elements.ts:6272](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6272)*

**Returns:** *boolean*

• **set bleed**(`value`: boolean): *void*

*Defined in [card-elements.ts:6276](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6276)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

*Defined in [card-elements.ts:498](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L498)*

**Returns:** *string*

___

### `Protected` hasExplicitStyle

• **get hasExplicitStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[hasExplicitStyle](stylablecardelementcontainer.md#protected-hasexplicitstyle)*

*Defined in [card-elements.ts:5232](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5232)*

**Returns:** *boolean*

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

### `Protected` isSelectable

• **get isSelectable**(): *boolean*

*Overrides [CardElementContainer](cardelementcontainer.md).[isSelectable](cardelementcontainer.md#protected-isselectable)*

*Defined in [card-elements.ts:6062](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6062)*

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

###  padding

• **get padding**(): *[PaddingDefinition](paddingdefinition.md)*

*Defined in [card-elements.ts:6280](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6280)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

• **set padding**(`value`: [PaddingDefinition](paddingdefinition.md)): *void*

*Defined in [card-elements.ts:6284](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6284)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)*

*Defined in [card-elements.ts:920](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L920)*

**Returns:** *[CardElement](cardelement.md)*

___

### `Protected` renderedActionCount

• **get renderedActionCount**(): *number*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[renderedActionCount](stylablecardelementcontainer.md#protected-renderedactioncount)*

*Defined in [card-elements.ts:5228](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5228)*

**Returns:** *number*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[renderedElement](cardelement.md#renderedelement)*

*Defined in [card-elements.ts:956](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L956)*

**Returns:** *HTMLElement*

___

###  selectAction

• **get selectAction**(): *[Action](action.md)*

*Defined in [card-elements.ts:6288](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6288)*

**Returns:** *[Action](action.md)*

• **set selectAction**(`value`: [Action](action.md)): *void*

*Defined in [card-elements.ts:6292](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6292)*

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

###  style

• **get style**(): *string*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)*

*Defined in [card-elements.ts:5295](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5295)*

**Returns:** *string*

• **set style**(`value`: string): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)*

*Defined in [card-elements.ts:5305](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5305)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

### `Protected` supportsMinHeight

• **get supportsMinHeight**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[supportsMinHeight](stylablecardelementcontainer.md#protected-supportsminheight)*

*Overrides [CardElement](cardelement.md).[supportsMinHeight](cardelement.md#protected-supportsminheight)*

*Defined in [card-elements.ts:5240](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5240)*

**Returns:** *boolean*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

*Defined in [card-elements.ts:486](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L486)*

**Returns:** *boolean*

## Methods

###  addColumn

▸ **addColumn**(`column`: [Column](column.md)): *void*

*Defined in [card-elements.ts:6209](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6209)*

**Parameters:**

Name | Type |
------ | ------ |
`column` | [Column](column.md) |

**Returns:** *void*

___

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

### `Protected` applyBackground

▸ **applyBackground**(): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[applyBackground](stylablecardelementcontainer.md#protected-applybackground)*

*Defined in [card-elements.ts:5129](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5129)*

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[applyPadding](stylablecardelementcontainer.md#protected-applypadding)*

*Overrides [CardElementContainer](cardelementcontainer.md).[applyPadding](cardelementcontainer.md#protected-applypadding)*

*Defined in [card-elements.ts:5137](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5137)*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string*

*Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

*Defined in [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L513)*

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

*Overrides [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

*Defined in [card-elements.ts:6258](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6258)*

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

*Inherited from [CardElementContainer](cardelementcontainer.md).[getAllInputs](cardelementcontainer.md#getallinputs)*

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

*Defined in [card-elements.ts:2334](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2334)*

**Returns:** *Array‹[Input](input.md)›*

___

### `Protected` getBleed

▸ **getBleed**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getBleed](stylablecardelementcontainer.md#protected-getbleed)*

*Defined in [card-elements.ts:5220](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5220)*

**Returns:** *boolean*

___

###  getColumnAt

▸ **getColumnAt**(`index`: number): *[Column](column.md)*

*Defined in [card-elements.ts:6152](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6152)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Column](column.md)*

___

###  getCount

▸ **getCount**(): *number*

*Defined in [card-elements.ts:6126](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6126)*

**Returns:** *number*

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

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getDefaultPadding](stylablecardelementcontainer.md#protected-getdefaultpadding)*

*Overrides [CardElement](cardelement.md).[getDefaultPadding](cardelement.md#protected-getdefaultpadding)*

*Defined in [card-elements.ts:5207](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5207)*

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

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getEffectiveStyle](stylablecardelementcontainer.md#geteffectivestyle)*

*Overrides [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)*

*Defined in [card-elements.ts:5289](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5289)*

**Returns:** *string*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md)*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getElementById](cardelementcontainer.md#getelementbyid)*

*Overrides [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)*

*Defined in [card-elements.ts:2354](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2354)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md)*

___

###  getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *[CardElement](cardelement.md)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getFirstVisibleRenderedItem](cardelementcontainer.md#abstract-getfirstvisiblerendereditem)*

*Defined in [card-elements.ts:6134](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6134)*

**Returns:** *[CardElement](cardelement.md)*

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

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasBackground](stylablecardelementcontainer.md#protected-gethasbackground)*

*Overrides [CardElement](cardelement.md).[getHasBackground](cardelement.md#protected-gethasbackground)*

*Defined in [card-elements.ts:5189](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5189)*

**Returns:** *boolean*

___

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasExpandedAction](stylablecardelementcontainer.md#protected-gethasexpandedaction)*

*Defined in [card-elements.ts:5216](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5216)*

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

###  getItemAt

▸ **getItemAt**(`index`: number): *[CardElement](cardelement.md)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemAt](cardelementcontainer.md#abstract-getitemat)*

*Defined in [card-elements.ts:6156](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6156)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[CardElement](cardelement.md)*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemCount](cardelementcontainer.md#abstract-getitemcount)*

*Defined in [card-elements.ts:6130](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6130)*

**Returns:** *number*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardElement](cardelement.md).[getJsonTypeName](cardelement.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:6160](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6160)*

**Returns:** *string*

___

###  getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *[CardElement](cardelement.md)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getLastVisibleRenderedItem](cardelementcontainer.md#abstract-getlastvisiblerendereditem)*

*Defined in [card-elements.ts:6143](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6143)*

**Returns:** *[CardElement](cardelement.md)*

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

*Inherited from [CardElementContainer](cardelementcontainer.md).[getResourceInformation](cardelementcontainer.md#getresourceinformation)*

*Overrides [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

*Defined in [card-elements.ts:2344](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2344)*

**Returns:** *Array‹[IResourceInformation](../interfaces/iresourceinformation.md)›*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)*

*Defined in [card-elements.ts:799](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L799)*

**Returns:** *[CardElement](cardelement.md)*

___

### `Protected` getSelectAction

▸ **getSelectAction**(): *[Action](action.md)*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getSelectAction](cardelementcontainer.md#protected-getselectaction)*

*Defined in [card-elements.ts:2207](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2207)*

**Returns:** *[Action](action.md)*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): *number*

*Overrides [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

*Defined in [card-elements.ts:6238](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6238)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

*Defined in [card-elements.ts:5982](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5982)*

**Returns:** *HTMLElement*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[internalValidateProperties](stylablecardelementcontainer.md#internalvalidateproperties)*

*Defined in [card-elements.ts:6184](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6184)*

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

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[isBleeding](stylablecardelementcontainer.md#isbleeding)*

*Overrides [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)*

*Defined in [card-elements.ts:5244](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5244)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Overrides [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

*Defined in [card-elements.ts:6110](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6110)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Overrides [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

*Defined in [card-elements.ts:6094](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6094)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)*

*Defined in [card-elements.ts:6254](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6254)*

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

### `Protected` isElementAllowed

▸ **isElementAllowed**(`element`: [CardElement](cardelement.md), `forbiddenElementTypes`: Array‹string›): *boolean*

*Inherited from [CardElementContainer](cardelementcontainer.md).[isElementAllowed](cardelementcontainer.md#protected-iselementallowed)*

*Defined in [card-elements.ts:2169](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2169)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |
`forbiddenElementTypes` | Array‹string› |

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

*Defined in [card-elements.ts:6084](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6084)*

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

*Overrides [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)*

*Defined in [card-elements.ts:6242](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6242)*

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

*Overrides [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)*

*Defined in [card-elements.ts:6246](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6246)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)*

*Defined in [card-elements.ts:6250](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6250)*

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

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[parse](stylablecardelementcontainer.md#parse)*

*Defined in [card-elements.ts:6164](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6164)*

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

###  removeItem

▸ **removeItem**(`item`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElementContainer](cardelementcontainer.md).[removeItem](cardelementcontainer.md#abstract-removeitem)*

*Defined in [card-elements.ts:6220](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6220)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[render](stylablecardelementcontainer.md#render)*

*Overrides [CardElementContainer](cardelementcontainer.md).[render](cardelementcontainer.md#render)*

*Defined in [card-elements.ts:5279](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5279)*

**Returns:** *HTMLElement*

___

### `Protected` setBleed

▸ **setBleed**(`value`: boolean): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[setBleed](stylablecardelementcontainer.md#protected-setbleed)*

*Defined in [card-elements.ts:5224](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5224)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

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

### `Protected` setSelectAction

▸ **setSelectAction**(`value`: [Action](action.md)): *void*

*Inherited from [CardElementContainer](cardelementcontainer.md).[setSelectAction](cardelementcontainer.md#protected-setselectaction)*

*Defined in [card-elements.ts:2211](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2211)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [Action](action.md) |

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

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [CardElement](cardelement.md).[shouldFallback](cardelement.md#shouldfallback)*

*Overrides [CardObject](cardobject.md).[shouldFallback](cardobject.md#abstract-shouldfallback)*

*Defined in [card-elements.ts:839](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L839)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[toJSON](stylablecardelementcontainer.md#tojson)*

*Defined in [card-elements.ts:6066](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6066)*

**Returns:** *any*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Overrides [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

*Defined in [card-elements.ts:6048](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6048)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Overrides [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

*Defined in [card-elements.ts:6056](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6056)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Inherited from [CardElementContainer](cardelementcontainer.md).[updateLayout](cardelementcontainer.md#updatelayout)*

*Overrides [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)*

*Defined in [card-elements.ts:2324](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2324)*

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
