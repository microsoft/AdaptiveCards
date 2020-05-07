[Adaptive Cards Javascript SDK](../README.md) › [AdaptiveCard](adaptivecard.md)

# Class: AdaptiveCard

## Hierarchy

  ↳ [ContainerWithActions](containerwithactions.md)

  ↳ **AdaptiveCard**

## Index

### Constructors

* [constructor](adaptivecard.md#constructor)

### Properties

* [allowVerticalOverflow](adaptivecard.md#allowverticaloverflow)
* [backgroundImage](adaptivecard.md#backgroundimage)
* [customCssSelector](adaptivecard.md#customcssselector)
* [designMode](adaptivecard.md#designmode)
* [fallbackText](adaptivecard.md#fallbacktext)
* [height](adaptivecard.md#height)
* [horizontalAlignment](adaptivecard.md#optional-horizontalalignment)
* [id](adaptivecard.md#id)
* [minPixelHeight](adaptivecard.md#optional-minpixelheight)
* [onAnchorClicked](adaptivecard.md#onanchorclicked)
* [onElementVisibilityChanged](adaptivecard.md#onelementvisibilitychanged)
* [onExecuteAction](adaptivecard.md#onexecuteaction)
* [onImageLoaded](adaptivecard.md#onimageloaded)
* [onInlineCardExpanded](adaptivecard.md#oninlinecardexpanded)
* [onInputValueChanged](adaptivecard.md#oninputvaluechanged)
* [onParseAction](adaptivecard.md#onparseaction)
* [onParseElement](adaptivecard.md#onparseelement)
* [requires](adaptivecard.md#requires)
* [rtl](adaptivecard.md#optional-rtl)
* [separator](adaptivecard.md#separator)
* [spacing](adaptivecard.md#spacing)
* [speak](adaptivecard.md#speak)
* [version](adaptivecard.md#optional-version)
* [verticalContentAlignment](adaptivecard.md#verticalcontentalignment)
* [actionTypeRegistry](adaptivecard.md#static-actiontyperegistry)
* [allowMarkForTextHighlighting](adaptivecard.md#static-allowmarkfortexthighlighting)
* [alwaysBleedSeparators](adaptivecard.md#static-alwaysbleedseparators)
* [displayInputValidationErrors](adaptivecard.md#static-displayinputvalidationerrors)
* [elementTypeRegistry](adaptivecard.md#static-elementtyperegistry)
* [enableFullJsonRoundTrip](adaptivecard.md#static-enablefulljsonroundtrip)
* [onAnchorClicked](adaptivecard.md#static-onanchorclicked)
* [onElementVisibilityChanged](adaptivecard.md#static-onelementvisibilitychanged)
* [onExecuteAction](adaptivecard.md#static-onexecuteaction)
* [onImageLoaded](adaptivecard.md#static-onimageloaded)
* [onInlineCardExpanded](adaptivecard.md#static-oninlinecardexpanded)
* [onInputValueChanged](adaptivecard.md#static-oninputvaluechanged)
* [onParseAction](adaptivecard.md#static-onparseaction)
* [onParseElement](adaptivecard.md#static-onparseelement)
* [onParseError](adaptivecard.md#static-onparseerror)
* [onProcessMarkdown](adaptivecard.md#static-onprocessmarkdown)
* [useAdvancedCardBottomTruncation](adaptivecard.md#static-useadvancedcardbottomtruncation)
* [useAdvancedTextBlockTruncation](adaptivecard.md#static-useadvancedtextblocktruncation)
* [useBuiltInInputValidation](adaptivecard.md#static-usebuiltininputvalidation)
* [useMarkdownInRadioButtonAndCheckbox](adaptivecard.md#static-usemarkdowninradiobuttonandcheckbox)

### Accessors

* [allowCustomPadding](adaptivecard.md#protected-allowcustompadding)
* [allowCustomStyle](adaptivecard.md#protected-allowcustomstyle)
* [bleed](adaptivecard.md#bleed)
* [bypassVersionCheck](adaptivecard.md#protected-bypassversioncheck)
* [defaultStyle](adaptivecard.md#protected-defaultstyle)
* [hasBackground](adaptivecard.md#protected-hasbackground)
* [hasExplicitStyle](adaptivecard.md#protected-hasexplicitstyle)
* [hasVisibleSeparator](adaptivecard.md#hasvisibleseparator)
* [hostConfig](adaptivecard.md#hostconfig)
* [index](adaptivecard.md#index)
* [isInline](adaptivecard.md#isinline)
* [isInteractive](adaptivecard.md#isinteractive)
* [isSelectable](adaptivecard.md#protected-isselectable)
* [isStandalone](adaptivecard.md#isstandalone)
* [isVisible](adaptivecard.md#isvisible)
* [lang](adaptivecard.md#lang)
* [padding](adaptivecard.md#padding)
* [parent](adaptivecard.md#parent)
* [renderIfEmpty](adaptivecard.md#protected-renderifempty)
* [renderedActionCount](adaptivecard.md#protected-renderedactioncount)
* [renderedElement](adaptivecard.md#renderedelement)
* [selectAction](adaptivecard.md#selectaction)
* [separatorElement](adaptivecard.md#separatorelement)
* [separatorOrientation](adaptivecard.md#protected-separatororientation)
* [style](adaptivecard.md#style)
* [supportsMinHeight](adaptivecard.md#protected-supportsminheight)
* [useDefaultSizing](adaptivecard.md#protected-usedefaultsizing)
* [processMarkdown](adaptivecard.md#static-processmarkdown)

### Methods

* [addAction](adaptivecard.md#addaction)
* [addItem](adaptivecard.md#additem)
* [adjustRenderedElementSize](adaptivecard.md#protected-adjustrenderedelementsize)
* [applyBackground](adaptivecard.md#protected-applybackground)
* [applyPadding](adaptivecard.md#protected-applypadding)
* [asString](adaptivecard.md#asstring)
* [clear](adaptivecard.md#clear)
* [createPlaceholderElement](adaptivecard.md#protected-createplaceholderelement)
* [getActionAt](adaptivecard.md#getactionat)
* [getActionById](adaptivecard.md#getactionbyid)
* [getActionCount](adaptivecard.md#getactioncount)
* [getAllInputs](adaptivecard.md#getallinputs)
* [getBleed](adaptivecard.md#protected-getbleed)
* [getCustomProperty](adaptivecard.md#getcustomproperty)
* [getDefaultPadding](adaptivecard.md#protected-getdefaultpadding)
* [getEffectivePadding](adaptivecard.md#geteffectivepadding)
* [getEffectiveStyle](adaptivecard.md#geteffectivestyle)
* [getElementById](adaptivecard.md#getelementbyid)
* [getFirstVisibleRenderedItem](adaptivecard.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](adaptivecard.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](adaptivecard.md#getforbiddenelementtypes)
* [getHasBackground](adaptivecard.md#protected-gethasbackground)
* [getHasExpandedAction](adaptivecard.md#protected-gethasexpandedaction)
* [getImmediateSurroundingPadding](adaptivecard.md#getimmediatesurroundingpadding)
* [getItemAt](adaptivecard.md#getitemat)
* [getItemCount](adaptivecard.md#getitemcount)
* [getItemsCollectionPropertyName](adaptivecard.md#protected-getitemscollectionpropertyname)
* [getJsonTypeName](adaptivecard.md#getjsontypename)
* [getLastVisibleRenderedItem](adaptivecard.md#getlastvisiblerendereditem)
* [getPadding](adaptivecard.md#protected-getpadding)
* [getParentContainer](adaptivecard.md#getparentcontainer)
* [getResourceInformation](adaptivecard.md#getresourceinformation)
* [getRootElement](adaptivecard.md#getrootelement)
* [getSelectAction](adaptivecard.md#protected-getselectaction)
* [indexOf](adaptivecard.md#indexof)
* [insertItemAfter](adaptivecard.md#insertitemafter)
* [insertItemBefore](adaptivecard.md#insertitembefore)
* [internalRender](adaptivecard.md#protected-internalrender)
* [internalValidateProperties](adaptivecard.md#internalvalidateproperties)
* [isAtTheVeryBottom](adaptivecard.md#isattheverybottom)
* [isAtTheVeryLeft](adaptivecard.md#isattheveryleft)
* [isAtTheVeryRight](adaptivecard.md#isattheveryright)
* [isAtTheVeryTop](adaptivecard.md#isattheverytop)
* [isBleeding](adaptivecard.md#isbleeding)
* [isBleedingAtBottom](adaptivecard.md#isbleedingatbottom)
* [isBleedingAtTop](adaptivecard.md#isbleedingattop)
* [isBottomElement](adaptivecard.md#isbottomelement)
* [isDesignMode](adaptivecard.md#isdesignmode)
* [isElementAllowed](adaptivecard.md#protected-iselementallowed)
* [isFirstElement](adaptivecard.md#isfirstelement)
* [isHiddenDueToOverflow](adaptivecard.md#ishiddenduetooverflow)
* [isLastElement](adaptivecard.md#islastelement)
* [isLeftMostElement](adaptivecard.md#isleftmostelement)
* [isRendered](adaptivecard.md#isrendered)
* [isRightMostElement](adaptivecard.md#isrightmostelement)
* [isRtl](adaptivecard.md#isrtl)
* [isTopElement](adaptivecard.md#istopelement)
* [overrideInternalRender](adaptivecard.md#protected-overrideinternalrender)
* [parse](adaptivecard.md#parse)
* [remove](adaptivecard.md#remove)
* [removeItem](adaptivecard.md#removeitem)
* [render](adaptivecard.md#render)
* [setBleed](adaptivecard.md#protected-setbleed)
* [setCustomProperty](adaptivecard.md#setcustomproperty)
* [setPadding](adaptivecard.md#protected-setpadding)
* [setParent](adaptivecard.md#setparent)
* [setSelectAction](adaptivecard.md#protected-setselectaction)
* [setShouldFallback](adaptivecard.md#setshouldfallback)
* [shouldFallback](adaptivecard.md#shouldfallback)
* [supportsExcplitiHeight](adaptivecard.md#protected-supportsexcplitiheight)
* [toJSON](adaptivecard.md#tojson)
* [truncateOverflow](adaptivecard.md#protected-truncateoverflow)
* [undoOverflowTruncation](adaptivecard.md#protected-undooverflowtruncation)
* [updateLayout](adaptivecard.md#updatelayout)
* [validateProperties](adaptivecard.md#validateproperties)
* [applyMarkdown](adaptivecard.md#static-applymarkdown)

## Constructors

###  constructor

\+ **new AdaptiveCard**(): *[AdaptiveCard](adaptivecard.md)*

*Inherited from [ContainerWithActions](containerwithactions.md).[constructor](containerwithactions.md#constructor)*

*Defined in [card-elements.ts:6438](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6438)*

**Returns:** *[AdaptiveCard](adaptivecard.md)*

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

###  designMode

• **designMode**: *boolean* = false

*Defined in [card-elements.ts:6761](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6761)*

___

###  fallbackText

• **fallbackText**: *string*

*Defined in [card-elements.ts:6759](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6759)*

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

###  onAnchorClicked

• **onAnchorClicked**: *function* = null

*Defined in [card-elements.ts:6749](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6749)*

#### Type declaration:

▸ (`element`: [CardElement](cardelement.md), `anchor`: HTMLAnchorElement): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |
`anchor` | HTMLAnchorElement |

___

###  onElementVisibilityChanged

• **onElementVisibilityChanged**: *function* = null

*Defined in [card-elements.ts:6751](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6751)*

#### Type declaration:

▸ (`element`: [CardElement](cardelement.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

___

###  onExecuteAction

• **onExecuteAction**: *function* = null

*Defined in [card-elements.ts:6750](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6750)*

#### Type declaration:

▸ (`action`: [Action](action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

___

###  onImageLoaded

• **onImageLoaded**: *function* = null

*Defined in [card-elements.ts:6752](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6752)*

#### Type declaration:

▸ (`image`: [Image](image.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`image` | [Image](image.md) |

___

###  onInlineCardExpanded

• **onInlineCardExpanded**: *function* = null

*Defined in [card-elements.ts:6753](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6753)*

#### Type declaration:

▸ (`action`: [ShowCardAction](showcardaction.md), `isExpanded`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [ShowCardAction](showcardaction.md) |
`isExpanded` | boolean |

___

###  onInputValueChanged

• **onInputValueChanged**: *function* = null

*Defined in [card-elements.ts:6754](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6754)*

#### Type declaration:

▸ (`input`: [Input](input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`input` | [Input](input.md) |

___

###  onParseAction

• **onParseAction**: *function* = null

*Defined in [card-elements.ts:6756](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6756)*

#### Type declaration:

▸ (`element`: [Action](action.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [Action](action.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

___

###  onParseElement

• **onParseElement**: *function* = null

*Defined in [card-elements.ts:6755](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6755)*

#### Type declaration:

▸ (`element`: [CardElement](cardelement.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

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

###  speak

• **speak**: *string*

*Defined in [card-elements.ts:6760](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6760)*

___

### `Optional` version

• **version**? : *[Version](version.md)* = new HostConfig.Version(1, 0)

*Defined in [card-elements.ts:6758](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6758)*

___

###  verticalContentAlignment

• **verticalContentAlignment**: *[VerticalAlignment](../enums/verticalalignment.md)* = Enums.VerticalAlignment.Top

*Inherited from [Container](container.md).[verticalContentAlignment](container.md#verticalcontentalignment)*

*Defined in [card-elements.ts:5573](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5573)*

___

### `Static` actionTypeRegistry

▪ **actionTypeRegistry**: *[ActionTypeRegistry](actiontyperegistry.md)‹›* = new ActionTypeRegistry()

*Defined in [card-elements.ts:6645](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6645)*

___

### `Static` allowMarkForTextHighlighting

▪ **allowMarkForTextHighlighting**: *boolean* = false

*Defined in [card-elements.ts:6638](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6638)*

___

### `Static` alwaysBleedSeparators

▪ **alwaysBleedSeparators**: *boolean* = false

*Defined in [card-elements.ts:6639](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6639)*

___

### `Static` displayInputValidationErrors

▪ **displayInputValidationErrors**: *boolean* = true

*Defined in [card-elements.ts:6642](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6642)*

___

### `Static` elementTypeRegistry

▪ **elementTypeRegistry**: *[ElementTypeRegistry](elementtyperegistry.md)‹›* = new ElementTypeRegistry()

*Defined in [card-elements.ts:6644](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6644)*

___

### `Static` enableFullJsonRoundTrip

▪ **enableFullJsonRoundTrip**: *boolean* = false

*Defined in [card-elements.ts:6640](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6640)*

___

### `Static` onAnchorClicked

▪ **onAnchorClicked**: *function* = null

*Defined in [card-elements.ts:6647](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6647)*

#### Type declaration:

▸ (`element`: [CardElement](cardelement.md), `anchor`: HTMLAnchorElement): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |
`anchor` | HTMLAnchorElement |

___

### `Static` onElementVisibilityChanged

▪ **onElementVisibilityChanged**: *function* = null

*Defined in [card-elements.ts:6649](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6649)*

#### Type declaration:

▸ (`element`: [CardElement](cardelement.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

___

### `Static` onExecuteAction

▪ **onExecuteAction**: *function* = null

*Defined in [card-elements.ts:6648](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6648)*

#### Type declaration:

▸ (`action`: [Action](action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

___

### `Static` onImageLoaded

▪ **onImageLoaded**: *function* = null

*Defined in [card-elements.ts:6650](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6650)*

#### Type declaration:

▸ (`image`: [Image](image.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`image` | [Image](image.md) |

___

### `Static` onInlineCardExpanded

▪ **onInlineCardExpanded**: *function* = null

*Defined in [card-elements.ts:6651](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6651)*

#### Type declaration:

▸ (`action`: [ShowCardAction](showcardaction.md), `isExpanded`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [ShowCardAction](showcardaction.md) |
`isExpanded` | boolean |

___

### `Static` onInputValueChanged

▪ **onInputValueChanged**: *function* = null

*Defined in [card-elements.ts:6652](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6652)*

#### Type declaration:

▸ (`input`: [Input](input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`input` | [Input](input.md) |

___

### `Static` onParseAction

▪ **onParseAction**: *function* = null

*Defined in [card-elements.ts:6654](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6654)*

#### Type declaration:

▸ (`element`: [Action](action.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [Action](action.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

___

### `Static` onParseElement

▪ **onParseElement**: *function* = null

*Defined in [card-elements.ts:6653](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6653)*

#### Type declaration:

▸ (`element`: [CardElement](cardelement.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

___

### `Static` onParseError

▪ **onParseError**: *function* = null

*Defined in [card-elements.ts:6655](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6655)*

#### Type declaration:

▸ (`error`: [IValidationError](../interfaces/ivalidationerror.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`error` | [IValidationError](../interfaces/ivalidationerror.md) |

___

### `Static` onProcessMarkdown

▪ **onProcessMarkdown**: *function* = null

*Defined in [card-elements.ts:6656](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6656)*

#### Type declaration:

▸ (`text`: string, `result`: [IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |
`result` | [IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md) |

___

### `Static` useAdvancedCardBottomTruncation

▪ **useAdvancedCardBottomTruncation**: *boolean* = false

*Defined in [card-elements.ts:6636](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6636)*

___

### `Static` useAdvancedTextBlockTruncation

▪ **useAdvancedTextBlockTruncation**: *boolean* = true

*Defined in [card-elements.ts:6635](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6635)*

___

### `Static` useBuiltInInputValidation

▪ **useBuiltInInputValidation**: *boolean* = true

*Defined in [card-elements.ts:6641](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6641)*

___

### `Static` useMarkdownInRadioButtonAndCheckbox

▪ **useMarkdownInRadioButtonAndCheckbox**: *boolean* = true

*Defined in [card-elements.ts:6637](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6637)*

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

*Defined in [card-elements.ts:490](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L490)*

**Returns:** *boolean*

___

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): *boolean*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[allowCustomStyle](stylablecardelementcontainer.md#protected-allowcustomstyle)*

*Defined in [card-elements.ts:6741](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6741)*

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

### `Protected` bypassVersionCheck

• **get bypassVersionCheck**(): *boolean*

*Defined in [card-elements.ts:6737](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6737)*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

*Defined in [card-elements.ts:498](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L498)*

**Returns:** *string*

___

### `Protected` hasBackground

• **get hasBackground**(): *boolean*

*Defined in [card-elements.ts:6745](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6745)*

**Returns:** *boolean*

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

*Defined in [card-elements.ts:6899](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6899)*

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

*Inherited from [ContainerWithActions](containerwithactions.md).[isStandalone](containerwithactions.md#isstandalone)*

*Overrides [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

*Defined in [card-elements.ts:6523](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6523)*

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

### `Protected` renderIfEmpty

• **get renderIfEmpty**(): *boolean*

*Overrides [ContainerWithActions](containerwithactions.md).[renderIfEmpty](containerwithactions.md#protected-renderifempty)*

*Defined in [card-elements.ts:6733](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6733)*

**Returns:** *boolean*

___

### `Protected` renderedActionCount

• **get renderedActionCount**(): *number*

*Inherited from [ContainerWithActions](containerwithactions.md).[renderedActionCount](containerwithactions.md#protected-renderedactioncount)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[renderedActionCount](stylablecardelementcontainer.md#protected-renderedactioncount)*

*Defined in [card-elements.ts:6432](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6432)*

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

___

### `Static` processMarkdown

• **get processMarkdown**(): *function*

*Defined in [card-elements.ts:6658](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6658)*

**Returns:** *function*

▸ (`text`: string): *string*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

• **set processMarkdown**(`value`: function): *void*

*Defined in [card-elements.ts:6662](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6662)*

**Parameters:**

▪ **value**: *function*

▸ (`text`: string): *string*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

**Returns:** *void*

## Methods

###  addAction

▸ **addAction**(`action`: [Action](action.md)): *void*

*Inherited from [ContainerWithActions](containerwithactions.md).[addAction](containerwithactions.md#addaction)*

*Defined in [card-elements.ts:6491](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6491)*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

**Returns:** *void*

___

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

*Inherited from [ContainerWithActions](containerwithactions.md).[clear](containerwithactions.md#clear)*

*Overrides [Container](container.md).[clear](container.md#clear)*

*Defined in [card-elements.ts:6495](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6495)*

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

*Inherited from [ContainerWithActions](containerwithactions.md).[getActionAt](containerwithactions.md#getactionat)*

*Overrides [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

*Defined in [card-elements.ts:6458](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6458)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md)*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md)*

*Inherited from [ContainerWithActions](containerwithactions.md).[getActionById](containerwithactions.md#getactionbyid)*

*Overrides [Container](container.md).[getActionById](container.md#getactionbyid)*

*Defined in [card-elements.ts:6467](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6467)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md)*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [ContainerWithActions](containerwithactions.md).[getActionCount](containerwithactions.md#getactioncount)*

*Overrides [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

*Defined in [card-elements.ts:6454](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6454)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](input.md)›*

*Inherited from [ContainerWithActions](containerwithactions.md).[getAllInputs](containerwithactions.md#getallinputs)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getAllInputs](cardelementcontainer.md#getallinputs)*

*Defined in [card-elements.ts:6501](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6501)*

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

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getDefaultPadding](stylablecardelementcontainer.md#protected-getdefaultpadding)*

*Defined in [card-elements.ts:6725](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6725)*

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

*Overrides [Container](container.md).[getHasBackground](container.md#protected-gethasbackground)*

*Defined in [card-elements.ts:6721](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6721)*

**Returns:** *boolean*

___

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): *boolean*

*Inherited from [ContainerWithActions](containerwithactions.md).[getHasExpandedAction](containerwithactions.md#protected-gethasexpandedaction)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasExpandedAction](stylablecardelementcontainer.md#protected-gethasexpandedaction)*

*Defined in [card-elements.ts:6420](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6420)*

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

*Overrides [Container](container.md).[getItemsCollectionPropertyName](container.md#protected-getitemscollectionpropertyname)*

*Defined in [card-elements.ts:6704](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6704)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [Container](container.md).[getJsonTypeName](container.md#getjsontypename)*

*Defined in [card-elements.ts:6763](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6763)*

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

*Inherited from [ContainerWithActions](containerwithactions.md).[getResourceInformation](containerwithactions.md#getresourceinformation)*

*Overrides [Container](container.md).[getResourceInformation](container.md#getresourceinformation)*

*Defined in [card-elements.ts:6505](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6505)*

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

*Overrides [ContainerWithActions](containerwithactions.md).[internalRender](containerwithactions.md#protected-internalrender)*

*Defined in [card-elements.ts:6708](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6708)*

**Returns:** *HTMLElement*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Overrides [ContainerWithActions](containerwithactions.md).[internalValidateProperties](containerwithactions.md#internalvalidateproperties)*

*Defined in [card-elements.ts:6783](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6783)*

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

*Inherited from [ContainerWithActions](containerwithactions.md).[isBleedingAtBottom](containerwithactions.md#isbleedingatbottom)*

*Overrides [Container](container.md).[isBleedingAtBottom](container.md#isbleedingatbottom)*

*Defined in [card-elements.ts:6509](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6509)*

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

*Inherited from [ContainerWithActions](containerwithactions.md).[isLastElement](containerwithactions.md#islastelement)*

*Overrides [Container](container.md).[isLastElement](container.md#islastelement)*

*Defined in [card-elements.ts:6487](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6487)*

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

*Overrides [ContainerWithActions](containerwithactions.md).[parse](containerwithactions.md#parse)*

*Defined in [card-elements.ts:6813](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6813)*

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

▸ **render**(`target?`: HTMLElement): *HTMLElement*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[render](stylablecardelementcontainer.md#render)*

*Defined in [card-elements.ts:6854](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6854)*

**Parameters:**

Name | Type |
------ | ------ |
`target?` | HTMLElement |

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

*Overrides [CardElement](cardelement.md).[shouldFallback](cardelement.md#shouldfallback)*

*Defined in [card-elements.ts:6895](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6895)*

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

*Overrides [ContainerWithActions](containerwithactions.md).[toJSON](containerwithactions.md#tojson)*

*Defined in [card-elements.ts:6767](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6767)*

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

*Overrides [CardElementContainer](cardelementcontainer.md).[updateLayout](cardelementcontainer.md#updatelayout)*

*Defined in [card-elements.ts:6884](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6884)*

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

___

### `Static` applyMarkdown

▸ **applyMarkdown**(`text`: string): *[IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)*

*Defined in [card-elements.ts:6666](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L6666)*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

**Returns:** *[IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)*
