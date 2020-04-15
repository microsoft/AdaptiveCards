[Adaptive Cards Javascript SDK](../README.md) › [Column](column.md)

# Class: Column

## Hierarchy

  ↳ [Container](container.md)

  ↳ **Column**

## Index

### Constructors

* [constructor](column.md#constructor)

### Properties

* [allowVerticalOverflow](column.md#allowverticaloverflow)
* [backgroundImage](column.md#backgroundimage)
* [customCssSelector](column.md#customcssselector)
* [height](column.md#height)
* [horizontalAlignment](column.md#optional-horizontalalignment)
* [id](column.md#id)
* [minPixelHeight](column.md#optional-minpixelheight)
* [requires](column.md#requires)
* [rtl](column.md#optional-rtl)
* [separator](column.md#separator)
* [spacing](column.md#spacing)
* [verticalContentAlignment](column.md#verticalcontentalignment)
* [width](column.md#width)

### Accessors

* [allowCustomPadding](column.md#protected-allowcustompadding)
* [allowCustomStyle](column.md#protected-allowcustomstyle)
* [bleed](column.md#bleed)
* [defaultStyle](column.md#protected-defaultstyle)
* [hasExplicitStyle](column.md#protected-hasexplicitstyle)
* [hasVisibleSeparator](column.md#hasvisibleseparator)
* [hostConfig](column.md#hostconfig)
* [index](column.md#index)
* [isInline](column.md#isinline)
* [isInteractive](column.md#isinteractive)
* [isSelectable](column.md#protected-isselectable)
* [isStandalone](column.md#isstandalone)
* [isVisible](column.md#isvisible)
* [lang](column.md#lang)
* [padding](column.md#padding)
* [parent](column.md#parent)
* [renderedActionCount](column.md#protected-renderedactioncount)
* [renderedElement](column.md#renderedelement)
* [selectAction](column.md#selectaction)
* [separatorElement](column.md#separatorelement)
* [separatorOrientation](column.md#protected-separatororientation)
* [style](column.md#style)
* [supportsMinHeight](column.md#protected-supportsminheight)
* [useDefaultSizing](column.md#protected-usedefaultsizing)

### Methods

* [addItem](column.md#additem)
* [adjustRenderedElementSize](column.md#protected-adjustrenderedelementsize)
* [applyBackground](column.md#protected-applybackground)
* [applyPadding](column.md#protected-applypadding)
* [asString](column.md#asstring)
* [clear](column.md#clear)
* [createPlaceholderElement](column.md#protected-createplaceholderelement)
* [getActionAt](column.md#getactionat)
* [getActionById](column.md#getactionbyid)
* [getActionCount](column.md#getactioncount)
* [getAllInputs](column.md#getallinputs)
* [getBleed](column.md#protected-getbleed)
* [getCustomProperty](column.md#getcustomproperty)
* [getDefaultPadding](column.md#protected-getdefaultpadding)
* [getEffectivePadding](column.md#geteffectivepadding)
* [getEffectiveStyle](column.md#geteffectivestyle)
* [getElementById](column.md#getelementbyid)
* [getFirstVisibleRenderedItem](column.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](column.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](column.md#getforbiddenelementtypes)
* [getHasBackground](column.md#protected-gethasbackground)
* [getHasExpandedAction](column.md#protected-gethasexpandedaction)
* [getImmediateSurroundingPadding](column.md#getimmediatesurroundingpadding)
* [getItemAt](column.md#getitemat)
* [getItemCount](column.md#getitemcount)
* [getItemsCollectionPropertyName](column.md#protected-getitemscollectionpropertyname)
* [getJsonTypeName](column.md#getjsontypename)
* [getLastVisibleRenderedItem](column.md#getlastvisiblerendereditem)
* [getPadding](column.md#protected-getpadding)
* [getParentContainer](column.md#getparentcontainer)
* [getResourceInformation](column.md#getresourceinformation)
* [getRootElement](column.md#getrootelement)
* [getSelectAction](column.md#protected-getselectaction)
* [indexOf](column.md#indexof)
* [insertItemAfter](column.md#insertitemafter)
* [insertItemBefore](column.md#insertitembefore)
* [internalRender](column.md#protected-internalrender)
* [internalValidateProperties](column.md#internalvalidateproperties)
* [isAtTheVeryBottom](column.md#isattheverybottom)
* [isAtTheVeryLeft](column.md#isattheveryleft)
* [isAtTheVeryRight](column.md#isattheveryright)
* [isAtTheVeryTop](column.md#isattheverytop)
* [isBleeding](column.md#isbleeding)
* [isBleedingAtBottom](column.md#isbleedingatbottom)
* [isBleedingAtTop](column.md#isbleedingattop)
* [isBottomElement](column.md#isbottomelement)
* [isDesignMode](column.md#isdesignmode)
* [isElementAllowed](column.md#protected-iselementallowed)
* [isFirstElement](column.md#isfirstelement)
* [isHiddenDueToOverflow](column.md#ishiddenduetooverflow)
* [isLastElement](column.md#islastelement)
* [isLeftMostElement](column.md#isleftmostelement)
* [isRendered](column.md#isrendered)
* [isRightMostElement](column.md#isrightmostelement)
* [isRtl](column.md#isrtl)
* [isTopElement](column.md#istopelement)
* [overrideInternalRender](column.md#protected-overrideinternalrender)
* [parse](column.md#parse)
* [remove](column.md#remove)
* [removeItem](column.md#removeitem)
* [render](column.md#render)
* [setBleed](column.md#protected-setbleed)
* [setCustomProperty](column.md#setcustomproperty)
* [setPadding](column.md#protected-setpadding)
* [setParent](column.md#setparent)
* [setSelectAction](column.md#protected-setselectaction)
* [setShouldFallback](column.md#setshouldfallback)
* [shouldFallback](column.md#shouldfallback)
* [supportsExcplitiHeight](column.md#protected-supportsexcplitiheight)
* [toJSON](column.md#tojson)
* [truncateOverflow](column.md#protected-truncateoverflow)
* [undoOverflowTruncation](column.md#protected-undooverflowtruncation)
* [updateLayout](column.md#updatelayout)
* [validateProperties](column.md#validateproperties)

## Constructors

###  constructor

\+ **new Column**(`width`: [ColumnWidth](../README.md#columnwidth)): *[Column](column.md)*

*Defined in [card-elements.ts:5862](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5862)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`width` | [ColumnWidth](../README.md#columnwidth) | "stretch" |

**Returns:** *[Column](column.md)*

## Properties

###  allowVerticalOverflow

• **allowVerticalOverflow**: *boolean* = false

*Inherited from [CardElementContainer](cardelementcontainer.md).[allowVerticalOverflow](cardelementcontainer.md#allowverticaloverflow)*

*Defined in [card-elements.ts:2229](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2229)*

___

###  backgroundImage

• **backgroundImage**: *[BackgroundImage](backgroundimage.md)* = new BackgroundImage()

*Inherited from [Container](container.md).[backgroundImage](container.md#backgroundimage)*

*Defined in [card-elements.ts:5571](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5571)*

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

### `Optional` rtl

• **rtl**? : *boolean* = null

*Inherited from [Container](container.md).[rtl](container.md#optional-rtl)*

*Defined in [card-elements.ts:5574](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5574)*

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

___

###  verticalContentAlignment

• **verticalContentAlignment**: *[VerticalAlignment](../enums/verticalalignment.md)* = Enums.VerticalAlignment.Top

*Inherited from [Container](container.md).[verticalContentAlignment](container.md#verticalcontentalignment)*

*Defined in [card-elements.ts:5573](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5573)*

___

###  width

• **width**: *[ColumnWidth](../README.md#columnwidth)* = "stretch"

*Defined in [card-elements.ts:5862](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5862)*

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

*Inherited from [Container](container.md).[bleed](container.md#bleed)*

*Defined in [card-elements.ts:5810](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5810)*

**Returns:** *boolean*

• **set bleed**(`value`: boolean): *void*

*Inherited from [Container](container.md).[bleed](container.md#bleed)*

*Defined in [card-elements.ts:5814](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5814)*

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

*Overrides [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)*

*Defined in [card-elements.ts:5938](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5938)*

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

*Inherited from [Container](container.md).[isSelectable](container.md#protected-isselectable)*

*Overrides [CardElementContainer](cardelementcontainer.md).[isSelectable](cardelementcontainer.md#protected-isselectable)*

*Defined in [card-elements.ts:5567](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5567)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Overrides [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

*Defined in [card-elements.ts:5947](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5947)*

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

*Inherited from [Container](container.md).[padding](container.md#padding)*

*Defined in [card-elements.ts:5794](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5794)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

• **set padding**(`value`: [PaddingDefinition](paddingdefinition.md)): *void*

*Inherited from [Container](container.md).[padding](container.md#padding)*

*Defined in [card-elements.ts:5798](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5798)*

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

*Inherited from [Container](container.md).[selectAction](container.md#selectaction)*

*Defined in [card-elements.ts:5802](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5802)*

**Returns:** *[Action](action.md)*

• **set selectAction**(`value`: [Action](action.md)): *void*

*Inherited from [Container](container.md).[selectAction](container.md#selectaction)*

*Defined in [card-elements.ts:5806](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5806)*

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

*Overrides [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

*Defined in [card-elements.ts:5858](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5858)*

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

###  addItem

▸ **addItem**(`item`: [CardElement](cardelement.md)): *void*

*Inherited from [Container](container.md).[addItem](container.md#additem)*

*Defined in [card-elements.ts:5730](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5730)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |

**Returns:** *void*

___

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Overrides [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

*Defined in [card-elements.ts:5824](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5824)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyBackground

▸ **applyBackground**(): *void*

*Inherited from [Container](container.md).[applyBackground](container.md#protected-applybackground)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[applyBackground](stylablecardelementcontainer.md#protected-applybackground)*

*Defined in [card-elements.ts:5441](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5441)*

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

###  clear

▸ **clear**(): *void*

*Inherited from [Container](container.md).[clear](container.md#clear)*

*Defined in [card-elements.ts:5758](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5758)*

**Returns:** *void*

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

*Inherited from [Container](container.md).[getActionById](container.md#getactionbyid)*

*Overrides [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

*Defined in [card-elements.ts:5772](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5772)*

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

*Inherited from [Container](container.md).[getFirstVisibleRenderedItem](container.md#getfirstvisiblerendereditem)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getFirstVisibleRenderedItem](cardelementcontainer.md#abstract-getfirstvisiblerendereditem)*

*Defined in [card-elements.ts:5606](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5606)*

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

*Inherited from [Container](container.md).[getHasBackground](container.md#protected-gethasbackground)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasBackground](stylablecardelementcontainer.md#protected-gethasbackground)*

*Defined in [card-elements.ts:5563](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5563)*

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

*Inherited from [Container](container.md).[getItemAt](container.md#getitemat)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemAt](cardelementcontainer.md#abstract-getitemat)*

*Defined in [card-elements.ts:5602](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5602)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[CardElement](cardelement.md)*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Inherited from [Container](container.md).[getItemCount](container.md#getitemcount)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemCount](cardelementcontainer.md#abstract-getitemcount)*

*Defined in [card-elements.ts:5598](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5598)*

**Returns:** *number*

___

### `Protected` getItemsCollectionPropertyName

▸ **getItemsCollectionPropertyName**(): *string*

*Inherited from [Container](container.md).[getItemsCollectionPropertyName](container.md#protected-getitemscollectionpropertyname)*

*Defined in [card-elements.ts:5437](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5437)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [Container](container.md).[getJsonTypeName](container.md#getjsontypename)*

*Defined in [card-elements.ts:5870](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5870)*

**Returns:** *string*

___

###  getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *[CardElement](cardelement.md)*

*Inherited from [Container](container.md).[getLastVisibleRenderedItem](container.md#getlastvisiblerendereditem)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getLastVisibleRenderedItem](cardelementcontainer.md#abstract-getlastvisiblerendereditem)*

*Defined in [card-elements.ts:5618](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5618)*

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

*Inherited from [Container](container.md).[getResourceInformation](container.md#getresourceinformation)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getResourceInformation](cardelementcontainer.md#getresourceinformation)*

*Defined in [card-elements.ts:5762](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5762)*

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

*Inherited from [Container](container.md).[indexOf](container.md#indexof)*

*Overrides [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

*Defined in [card-elements.ts:5726](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5726)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

___

###  insertItemAfter

▸ **insertItemAfter**(`item`: [CardElement](cardelement.md), `insertAfter`: [CardElement](cardelement.md)): *void*

*Inherited from [Container](container.md).[insertItemAfter](container.md#insertitemafter)*

*Defined in [card-elements.ts:5738](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5738)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |
`insertAfter` | [CardElement](cardelement.md) |

**Returns:** *void*

___

###  insertItemBefore

▸ **insertItemBefore**(`item`: [CardElement](cardelement.md), `insertBefore`: [CardElement](cardelement.md)): *void*

*Inherited from [Container](container.md).[insertItemBefore](container.md#insertitembefore)*

*Defined in [card-elements.ts:5734](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5734)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |
`insertBefore` | [CardElement](cardelement.md) |

**Returns:** *void*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement*

*Inherited from [Container](container.md).[internalRender](container.md#protected-internalrender)*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

*Defined in [card-elements.ts:5449](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5449)*

**Returns:** *HTMLElement*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[internalValidateProperties](stylablecardelementcontainer.md#internalvalidateproperties)*

*Overrides [CardElementContainer](cardelementcontainer.md).[internalValidateProperties](cardelementcontainer.md#internalvalidateproperties)*

*Defined in [card-elements.ts:5256](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5256)*

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

*Inherited from [Container](container.md).[isBleedingAtBottom](container.md#isbleedingatbottom)*

*Overrides [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

*Defined in [card-elements.ts:5675](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5675)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [Container](container.md).[isBleedingAtTop](container.md#isbleedingattop)*

*Overrides [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

*Defined in [card-elements.ts:5669](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5669)*

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

*Inherited from [Container](container.md).[isFirstElement](container.md#isfirstelement)*

*Overrides [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

*Defined in [card-elements.ts:5634](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5634)*

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

*Inherited from [Container](container.md).[isLastElement](container.md#islastelement)*

*Overrides [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)*

*Defined in [card-elements.ts:5646](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5646)*

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

###  isRtl

▸ **isRtl**(): *boolean*

*Inherited from [Container](container.md).[isRtl](container.md#isrtl)*

*Defined in [card-elements.ts:5658](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5658)*

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

*Overrides [Container](container.md).[parse](container.md#parse)*

*Defined in [card-elements.ts:5892](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5892)*

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

*Inherited from [Container](container.md).[removeItem](container.md#removeitem)*

*Overrides [CardElementContainer](cardelementcontainer.md).[removeItem](cardelementcontainer.md#abstract-removeitem)*

*Defined in [card-elements.ts:5742](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5742)*

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

### `Protected` supportsExcplitiHeight

▸ **supportsExcplitiHeight**(): *boolean*

*Inherited from [Container](container.md).[supportsExcplitiHeight](container.md#protected-supportsexcplitiheight)*

*Defined in [card-elements.ts:5433](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5433)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [Container](container.md).[toJSON](container.md#tojson)*

*Defined in [card-elements.ts:5874](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5874)*

**Returns:** *any*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Inherited from [Container](container.md).[truncateOverflow](container.md#protected-truncateoverflow)*

*Overrides [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

*Defined in [card-elements.ts:5522](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5522)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Inherited from [Container](container.md).[undoOverflowTruncation](container.md#protected-undooverflowtruncation)*

*Overrides [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

*Defined in [card-elements.ts:5557](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5557)*

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
