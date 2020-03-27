[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [AdaptiveCard](_card_elements_.adaptivecard.md)

# Class: AdaptiveCard

## Hierarchy

  ↳ [ContainerWithActions](_card_elements_.containerwithactions.md)

  ↳ **AdaptiveCard**

## Index

### Constructors

* [constructor](_card_elements_.adaptivecard.md#constructor)

### Properties

* [allowVerticalOverflow](_card_elements_.adaptivecard.md#allowverticaloverflow)
* [backgroundImage](_card_elements_.adaptivecard.md#backgroundimage)
* [customCssSelector](_card_elements_.adaptivecard.md#customcssselector)
* [designMode](_card_elements_.adaptivecard.md#designmode)
* [fallbackText](_card_elements_.adaptivecard.md#fallbacktext)
* [height](_card_elements_.adaptivecard.md#height)
* [horizontalAlignment](_card_elements_.adaptivecard.md#optional-horizontalalignment)
* [id](_card_elements_.adaptivecard.md#id)
* [minPixelHeight](_card_elements_.adaptivecard.md#optional-minpixelheight)
* [onAnchorClicked](_card_elements_.adaptivecard.md#onanchorclicked)
* [onElementVisibilityChanged](_card_elements_.adaptivecard.md#onelementvisibilitychanged)
* [onExecuteAction](_card_elements_.adaptivecard.md#onexecuteaction)
* [onImageLoaded](_card_elements_.adaptivecard.md#onimageloaded)
* [onInlineCardExpanded](_card_elements_.adaptivecard.md#oninlinecardexpanded)
* [onInputValueChanged](_card_elements_.adaptivecard.md#oninputvaluechanged)
* [onParseAction](_card_elements_.adaptivecard.md#onparseaction)
* [onParseElement](_card_elements_.adaptivecard.md#onparseelement)
* [requires](_card_elements_.adaptivecard.md#requires)
* [rtl](_card_elements_.adaptivecard.md#optional-rtl)
* [separator](_card_elements_.adaptivecard.md#separator)
* [spacing](_card_elements_.adaptivecard.md#spacing)
* [speak](_card_elements_.adaptivecard.md#speak)
* [version](_card_elements_.adaptivecard.md#optional-version)
* [verticalContentAlignment](_card_elements_.adaptivecard.md#verticalcontentalignment)
* [actionTypeRegistry](_card_elements_.adaptivecard.md#static-actiontyperegistry)
* [allowMarkForTextHighlighting](_card_elements_.adaptivecard.md#static-allowmarkfortexthighlighting)
* [alwaysBleedSeparators](_card_elements_.adaptivecard.md#static-alwaysbleedseparators)
* [displayInputValidationErrors](_card_elements_.adaptivecard.md#static-displayinputvalidationerrors)
* [elementTypeRegistry](_card_elements_.adaptivecard.md#static-elementtyperegistry)
* [enableFullJsonRoundTrip](_card_elements_.adaptivecard.md#static-enablefulljsonroundtrip)
* [onAnchorClicked](_card_elements_.adaptivecard.md#static-onanchorclicked)
* [onElementVisibilityChanged](_card_elements_.adaptivecard.md#static-onelementvisibilitychanged)
* [onExecuteAction](_card_elements_.adaptivecard.md#static-onexecuteaction)
* [onImageLoaded](_card_elements_.adaptivecard.md#static-onimageloaded)
* [onInlineCardExpanded](_card_elements_.adaptivecard.md#static-oninlinecardexpanded)
* [onInputValueChanged](_card_elements_.adaptivecard.md#static-oninputvaluechanged)
* [onParseAction](_card_elements_.adaptivecard.md#static-onparseaction)
* [onParseElement](_card_elements_.adaptivecard.md#static-onparseelement)
* [onParseError](_card_elements_.adaptivecard.md#static-onparseerror)
* [onProcessMarkdown](_card_elements_.adaptivecard.md#static-onprocessmarkdown)
* [useAdvancedCardBottomTruncation](_card_elements_.adaptivecard.md#static-useadvancedcardbottomtruncation)
* [useAdvancedTextBlockTruncation](_card_elements_.adaptivecard.md#static-useadvancedtextblocktruncation)
* [useBuiltInInputValidation](_card_elements_.adaptivecard.md#static-usebuiltininputvalidation)
* [useMarkdownInRadioButtonAndCheckbox](_card_elements_.adaptivecard.md#static-usemarkdowninradiobuttonandcheckbox)

### Accessors

* [allowCustomPadding](_card_elements_.adaptivecard.md#protected-allowcustompadding)
* [allowCustomStyle](_card_elements_.adaptivecard.md#protected-allowcustomstyle)
* [bleed](_card_elements_.adaptivecard.md#bleed)
* [bypassVersionCheck](_card_elements_.adaptivecard.md#protected-bypassversioncheck)
* [defaultStyle](_card_elements_.adaptivecard.md#protected-defaultstyle)
* [hasBackground](_card_elements_.adaptivecard.md#protected-hasbackground)
* [hasExplicitStyle](_card_elements_.adaptivecard.md#protected-hasexplicitstyle)
* [hasVisibleSeparator](_card_elements_.adaptivecard.md#hasvisibleseparator)
* [hostConfig](_card_elements_.adaptivecard.md#hostconfig)
* [index](_card_elements_.adaptivecard.md#index)
* [isInline](_card_elements_.adaptivecard.md#isinline)
* [isInteractive](_card_elements_.adaptivecard.md#isinteractive)
* [isSelectable](_card_elements_.adaptivecard.md#protected-isselectable)
* [isStandalone](_card_elements_.adaptivecard.md#isstandalone)
* [isVisible](_card_elements_.adaptivecard.md#isvisible)
* [lang](_card_elements_.adaptivecard.md#lang)
* [padding](_card_elements_.adaptivecard.md#padding)
* [parent](_card_elements_.adaptivecard.md#parent)
* [renderIfEmpty](_card_elements_.adaptivecard.md#protected-renderifempty)
* [renderedActionCount](_card_elements_.adaptivecard.md#protected-renderedactioncount)
* [renderedElement](_card_elements_.adaptivecard.md#renderedelement)
* [selectAction](_card_elements_.adaptivecard.md#selectaction)
* [separatorElement](_card_elements_.adaptivecard.md#separatorelement)
* [separatorOrientation](_card_elements_.adaptivecard.md#protected-separatororientation)
* [style](_card_elements_.adaptivecard.md#style)
* [supportsMinHeight](_card_elements_.adaptivecard.md#protected-supportsminheight)
* [useDefaultSizing](_card_elements_.adaptivecard.md#protected-usedefaultsizing)
* [processMarkdown](_card_elements_.adaptivecard.md#static-processmarkdown)

### Methods

* [addAction](_card_elements_.adaptivecard.md#addaction)
* [addItem](_card_elements_.adaptivecard.md#additem)
* [adjustRenderedElementSize](_card_elements_.adaptivecard.md#protected-adjustrenderedelementsize)
* [applyBackground](_card_elements_.adaptivecard.md#protected-applybackground)
* [applyPadding](_card_elements_.adaptivecard.md#protected-applypadding)
* [asString](_card_elements_.adaptivecard.md#asstring)
* [clear](_card_elements_.adaptivecard.md#clear)
* [createPlaceholderElement](_card_elements_.adaptivecard.md#protected-createplaceholderelement)
* [getActionAt](_card_elements_.adaptivecard.md#getactionat)
* [getActionById](_card_elements_.adaptivecard.md#getactionbyid)
* [getActionCount](_card_elements_.adaptivecard.md#getactioncount)
* [getAllInputs](_card_elements_.adaptivecard.md#getallinputs)
* [getBleed](_card_elements_.adaptivecard.md#protected-getbleed)
* [getCustomProperty](_card_elements_.adaptivecard.md#getcustomproperty)
* [getDefaultPadding](_card_elements_.adaptivecard.md#protected-getdefaultpadding)
* [getEffectivePadding](_card_elements_.adaptivecard.md#geteffectivepadding)
* [getEffectiveStyle](_card_elements_.adaptivecard.md#geteffectivestyle)
* [getElementById](_card_elements_.adaptivecard.md#getelementbyid)
* [getFirstVisibleRenderedItem](_card_elements_.adaptivecard.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](_card_elements_.adaptivecard.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](_card_elements_.adaptivecard.md#getforbiddenelementtypes)
* [getHasBackground](_card_elements_.adaptivecard.md#protected-gethasbackground)
* [getHasExpandedAction](_card_elements_.adaptivecard.md#protected-gethasexpandedaction)
* [getImmediateSurroundingPadding](_card_elements_.adaptivecard.md#getimmediatesurroundingpadding)
* [getItemAt](_card_elements_.adaptivecard.md#getitemat)
* [getItemCount](_card_elements_.adaptivecard.md#getitemcount)
* [getItemsCollectionPropertyName](_card_elements_.adaptivecard.md#protected-getitemscollectionpropertyname)
* [getJsonTypeName](_card_elements_.adaptivecard.md#getjsontypename)
* [getLastVisibleRenderedItem](_card_elements_.adaptivecard.md#getlastvisiblerendereditem)
* [getPadding](_card_elements_.adaptivecard.md#protected-getpadding)
* [getParentContainer](_card_elements_.adaptivecard.md#getparentcontainer)
* [getResourceInformation](_card_elements_.adaptivecard.md#getresourceinformation)
* [getRootElement](_card_elements_.adaptivecard.md#getrootelement)
* [getSelectAction](_card_elements_.adaptivecard.md#protected-getselectaction)
* [indexOf](_card_elements_.adaptivecard.md#indexof)
* [insertItemAfter](_card_elements_.adaptivecard.md#insertitemafter)
* [insertItemBefore](_card_elements_.adaptivecard.md#insertitembefore)
* [internalRender](_card_elements_.adaptivecard.md#protected-internalrender)
* [internalValidateProperties](_card_elements_.adaptivecard.md#internalvalidateproperties)
* [isAtTheVeryBottom](_card_elements_.adaptivecard.md#isattheverybottom)
* [isAtTheVeryLeft](_card_elements_.adaptivecard.md#isattheveryleft)
* [isAtTheVeryRight](_card_elements_.adaptivecard.md#isattheveryright)
* [isAtTheVeryTop](_card_elements_.adaptivecard.md#isattheverytop)
* [isBleeding](_card_elements_.adaptivecard.md#isbleeding)
* [isBleedingAtBottom](_card_elements_.adaptivecard.md#isbleedingatbottom)
* [isBleedingAtTop](_card_elements_.adaptivecard.md#isbleedingattop)
* [isBottomElement](_card_elements_.adaptivecard.md#isbottomelement)
* [isDesignMode](_card_elements_.adaptivecard.md#isdesignmode)
* [isElementAllowed](_card_elements_.adaptivecard.md#protected-iselementallowed)
* [isFirstElement](_card_elements_.adaptivecard.md#isfirstelement)
* [isHiddenDueToOverflow](_card_elements_.adaptivecard.md#ishiddenduetooverflow)
* [isLastElement](_card_elements_.adaptivecard.md#islastelement)
* [isLeftMostElement](_card_elements_.adaptivecard.md#isleftmostelement)
* [isRendered](_card_elements_.adaptivecard.md#isrendered)
* [isRightMostElement](_card_elements_.adaptivecard.md#isrightmostelement)
* [isRtl](_card_elements_.adaptivecard.md#isrtl)
* [isTopElement](_card_elements_.adaptivecard.md#istopelement)
* [overrideInternalRender](_card_elements_.adaptivecard.md#protected-overrideinternalrender)
* [parse](_card_elements_.adaptivecard.md#parse)
* [remove](_card_elements_.adaptivecard.md#remove)
* [removeItem](_card_elements_.adaptivecard.md#removeitem)
* [render](_card_elements_.adaptivecard.md#render)
* [setBleed](_card_elements_.adaptivecard.md#protected-setbleed)
* [setCustomProperty](_card_elements_.adaptivecard.md#setcustomproperty)
* [setPadding](_card_elements_.adaptivecard.md#protected-setpadding)
* [setParent](_card_elements_.adaptivecard.md#setparent)
* [setSelectAction](_card_elements_.adaptivecard.md#protected-setselectaction)
* [setShouldFallback](_card_elements_.adaptivecard.md#setshouldfallback)
* [shouldFallback](_card_elements_.adaptivecard.md#shouldfallback)
* [supportsExcplitiHeight](_card_elements_.adaptivecard.md#protected-supportsexcplitiheight)
* [toJSON](_card_elements_.adaptivecard.md#tojson)
* [truncateOverflow](_card_elements_.adaptivecard.md#protected-truncateoverflow)
* [undoOverflowTruncation](_card_elements_.adaptivecard.md#protected-undooverflowtruncation)
* [updateLayout](_card_elements_.adaptivecard.md#updatelayout)
* [validateProperties](_card_elements_.adaptivecard.md#validateproperties)
* [applyMarkdown](_card_elements_.adaptivecard.md#static-applymarkdown)

## Constructors

###  constructor

\+ **new AdaptiveCard**(): *[AdaptiveCard](_card_elements_.adaptivecard.md)*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[constructor](_card_elements_.containerwithactions.md#constructor)*

**Returns:** *[AdaptiveCard](_card_elements_.adaptivecard.md)*

## Properties

###  allowVerticalOverflow

• **allowVerticalOverflow**: *boolean* = false

*Inherited from [CardElementContainer](_card_elements_.cardelementcontainer.md).[allowVerticalOverflow](_card_elements_.cardelementcontainer.md#allowverticaloverflow)*

___

###  backgroundImage

• **backgroundImage**: *[BackgroundImage](_card_elements_.backgroundimage.md)* = new BackgroundImage()

*Inherited from [Container](_card_elements_.container.md).[backgroundImage](_card_elements_.container.md#backgroundimage)*

___

###  customCssSelector

• **customCssSelector**: *string* = null

*Inherited from [CardElement](_card_elements_.cardelement.md).[customCssSelector](_card_elements_.cardelement.md#customcssselector)*

___

###  designMode

• **designMode**: *boolean* = false

___

###  fallbackText

• **fallbackText**: *string*

___

###  height

• **height**: *[CardElementHeight](../modules/_card_elements_.md#cardelementheight)* = "auto"

*Inherited from [CardElement](_card_elements_.cardelement.md).[height](_card_elements_.cardelement.md#height)*

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../enums/_enums_.horizontalalignment.md)* = null

*Inherited from [CardElement](_card_elements_.cardelement.md).[horizontalAlignment](_card_elements_.cardelement.md#optional-horizontalalignment)*

___

###  id

• **id**: *string*

*Inherited from [CardObject](_card_elements_.cardobject.md).[id](_card_elements_.cardobject.md#id)*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *number* = null

*Inherited from [CardElement](_card_elements_.cardelement.md).[minPixelHeight](_card_elements_.cardelement.md#optional-minpixelheight)*

___

###  onAnchorClicked

• **onAnchorClicked**: *function* = null

#### Type declaration:

▸ (`element`: [CardElement](_card_elements_.cardelement.md), `anchor`: HTMLAnchorElement): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |
`anchor` | HTMLAnchorElement |

___

###  onElementVisibilityChanged

• **onElementVisibilityChanged**: *function* = null

#### Type declaration:

▸ (`element`: [CardElement](_card_elements_.cardelement.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

___

###  onExecuteAction

• **onExecuteAction**: *function* = null

#### Type declaration:

▸ (`action`: [Action](_card_elements_.action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](_card_elements_.action.md) |

___

###  onImageLoaded

• **onImageLoaded**: *function* = null

#### Type declaration:

▸ (`image`: [Image](_card_elements_.image.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`image` | [Image](_card_elements_.image.md) |

___

###  onInlineCardExpanded

• **onInlineCardExpanded**: *function* = null

#### Type declaration:

▸ (`action`: [ShowCardAction](_card_elements_.showcardaction.md), `isExpanded`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [ShowCardAction](_card_elements_.showcardaction.md) |
`isExpanded` | boolean |

___

###  onInputValueChanged

• **onInputValueChanged**: *function* = null

#### Type declaration:

▸ (`input`: [Input](_card_elements_.input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`input` | [Input](_card_elements_.input.md) |

___

###  onParseAction

• **onParseAction**: *function* = null

#### Type declaration:

▸ (`element`: [Action](_card_elements_.action.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [Action](_card_elements_.action.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

___

###  onParseElement

• **onParseElement**: *function* = null

#### Type declaration:

▸ (`element`: [CardElement](_card_elements_.cardelement.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

___

###  requires

• **requires**: *[HostCapabilities](_host_config_.hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

*Inherited from [CardElement](_card_elements_.cardelement.md).[requires](_card_elements_.cardelement.md#requires)*

___

### `Optional` rtl

• **rtl**? : *boolean* = null

*Inherited from [Container](_card_elements_.container.md).[rtl](_card_elements_.container.md#optional-rtl)*

___

###  separator

• **separator**: *boolean* = false

*Inherited from [CardElement](_card_elements_.cardelement.md).[separator](_card_elements_.cardelement.md#separator)*

___

###  spacing

• **spacing**: *[Spacing](../enums/_enums_.spacing.md)* = Enums.Spacing.Default

*Inherited from [CardElement](_card_elements_.cardelement.md).[spacing](_card_elements_.cardelement.md#spacing)*

___

###  speak

• **speak**: *string*

___

### `Optional` version

• **version**? : *[Version](_host_config_.version.md)* = new HostConfig.Version(1, 0)

___

###  verticalContentAlignment

• **verticalContentAlignment**: *[VerticalAlignment](../enums/_enums_.verticalalignment.md)* = Enums.VerticalAlignment.Top

*Inherited from [Container](_card_elements_.container.md).[verticalContentAlignment](_card_elements_.container.md#verticalcontentalignment)*

___

### `Static` actionTypeRegistry

▪ **actionTypeRegistry**: *[ActionTypeRegistry](_card_elements_.actiontyperegistry.md)‹›* = new ActionTypeRegistry()

___

### `Static` allowMarkForTextHighlighting

▪ **allowMarkForTextHighlighting**: *boolean* = false

___

### `Static` alwaysBleedSeparators

▪ **alwaysBleedSeparators**: *boolean* = false

___

### `Static` displayInputValidationErrors

▪ **displayInputValidationErrors**: *boolean* = true

___

### `Static` elementTypeRegistry

▪ **elementTypeRegistry**: *[ElementTypeRegistry](_card_elements_.elementtyperegistry.md)‹›* = new ElementTypeRegistry()

___

### `Static` enableFullJsonRoundTrip

▪ **enableFullJsonRoundTrip**: *boolean* = false

___

### `Static` onAnchorClicked

▪ **onAnchorClicked**: *function* = null

#### Type declaration:

▸ (`element`: [CardElement](_card_elements_.cardelement.md), `anchor`: HTMLAnchorElement): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |
`anchor` | HTMLAnchorElement |

___

### `Static` onElementVisibilityChanged

▪ **onElementVisibilityChanged**: *function* = null

#### Type declaration:

▸ (`element`: [CardElement](_card_elements_.cardelement.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

___

### `Static` onExecuteAction

▪ **onExecuteAction**: *function* = null

#### Type declaration:

▸ (`action`: [Action](_card_elements_.action.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](_card_elements_.action.md) |

___

### `Static` onImageLoaded

▪ **onImageLoaded**: *function* = null

#### Type declaration:

▸ (`image`: [Image](_card_elements_.image.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`image` | [Image](_card_elements_.image.md) |

___

### `Static` onInlineCardExpanded

▪ **onInlineCardExpanded**: *function* = null

#### Type declaration:

▸ (`action`: [ShowCardAction](_card_elements_.showcardaction.md), `isExpanded`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [ShowCardAction](_card_elements_.showcardaction.md) |
`isExpanded` | boolean |

___

### `Static` onInputValueChanged

▪ **onInputValueChanged**: *function* = null

#### Type declaration:

▸ (`input`: [Input](_card_elements_.input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`input` | [Input](_card_elements_.input.md) |

___

### `Static` onParseAction

▪ **onParseAction**: *function* = null

#### Type declaration:

▸ (`element`: [Action](_card_elements_.action.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [Action](_card_elements_.action.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

___

### `Static` onParseElement

▪ **onParseElement**: *function* = null

#### Type declaration:

▸ (`element`: [CardElement](_card_elements_.cardelement.md), `json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

___

### `Static` onParseError

▪ **onParseError**: *function* = null

#### Type declaration:

▸ (`error`: [IValidationError](../interfaces/_host_config_.ivalidationerror.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`error` | [IValidationError](../interfaces/_host_config_.ivalidationerror.md) |

___

### `Static` onProcessMarkdown

▪ **onProcessMarkdown**: *function* = null

#### Type declaration:

▸ (`text`: string, `result`: [IMarkdownProcessingResult](../interfaces/_card_elements_.imarkdownprocessingresult.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |
`result` | [IMarkdownProcessingResult](../interfaces/_card_elements_.imarkdownprocessingresult.md) |

___

### `Static` useAdvancedCardBottomTruncation

▪ **useAdvancedCardBottomTruncation**: *boolean* = false

___

### `Static` useAdvancedTextBlockTruncation

▪ **useAdvancedTextBlockTruncation**: *boolean* = true

___

### `Static` useBuiltInInputValidation

▪ **useBuiltInInputValidation**: *boolean* = true

___

### `Static` useMarkdownInRadioButtonAndCheckbox

▪ **useMarkdownInRadioButtonAndCheckbox**: *boolean* = true

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[allowCustomPadding](_card_elements_.cardelement.md#protected-allowcustompadding)*

**Returns:** *boolean*

___

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): *boolean*

*Overrides [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[allowCustomStyle](_card_elements_.stylablecardelementcontainer.md#protected-allowcustomstyle)*

**Returns:** *boolean*

___

###  bleed

• **get bleed**(): *boolean*

*Inherited from [Container](_card_elements_.container.md).[bleed](_card_elements_.container.md#bleed)*

**Returns:** *boolean*

• **set bleed**(`value`: boolean): *void*

*Inherited from [Container](_card_elements_.container.md).[bleed](_card_elements_.container.md#bleed)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` bypassVersionCheck

• **get bypassVersionCheck**(): *boolean*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](_card_elements_.cardelement.md).[defaultStyle](_card_elements_.cardelement.md#protected-defaultstyle)*

**Returns:** *string*

___

### `Protected` hasBackground

• **get hasBackground**(): *boolean*

**Returns:** *boolean*

___

### `Protected` hasExplicitStyle

• **get hasExplicitStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[hasExplicitStyle](_card_elements_.stylablecardelementcontainer.md#protected-hasexplicitstyle)*

**Returns:** *boolean*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Overrides [CardElement](_card_elements_.cardelement.md).[hasVisibleSeparator](_card_elements_.cardelement.md#hasvisibleseparator)*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](_host_config_.hostconfig.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[hostConfig](_card_elements_.cardelement.md#hostconfig)*

**Returns:** *[HostConfig](_host_config_.hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](_host_config_.hostconfig.md)): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[hostConfig](_card_elements_.cardelement.md#hostconfig)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](_host_config_.hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

*Inherited from [CardElement](_card_elements_.cardelement.md).[index](_card_elements_.cardelement.md#index)*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isInline](_card_elements_.cardelement.md#isinline)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isInteractive](_card_elements_.cardelement.md#isinteractive)*

**Returns:** *boolean*

___

### `Protected` isSelectable

• **get isSelectable**(): *boolean*

*Inherited from [Container](_card_elements_.container.md).[isSelectable](_card_elements_.container.md#protected-isselectable)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[isSelectable](_card_elements_.cardelementcontainer.md#protected-isselectable)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[isStandalone](_card_elements_.containerwithactions.md#isstandalone)*

*Overrides [CardElement](_card_elements_.cardelement.md).[isStandalone](_card_elements_.cardelement.md#isstandalone)*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isVisible](_card_elements_.cardelement.md#isvisible)*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isVisible](_card_elements_.cardelement.md#isvisible)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string*

*Inherited from [CardElement](_card_elements_.cardelement.md).[lang](_card_elements_.cardelement.md#lang)*

**Returns:** *string*

• **set lang**(`value`: string): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[lang](_card_elements_.cardelement.md#lang)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  padding

• **get padding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

*Inherited from [Container](_card_elements_.container.md).[padding](_card_elements_.container.md#padding)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

• **set padding**(`value`: [PaddingDefinition](_shared_.paddingdefinition.md)): *void*

*Inherited from [Container](_card_elements_.container.md).[padding](_card_elements_.container.md#padding)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](_shared_.paddingdefinition.md) |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[parent](_card_elements_.cardelement.md#parent)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

### `Protected` renderIfEmpty

• **get renderIfEmpty**(): *boolean*

*Overrides [ContainerWithActions](_card_elements_.containerwithactions.md).[renderIfEmpty](_card_elements_.containerwithactions.md#protected-renderifempty)*

**Returns:** *boolean*

___

### `Protected` renderedActionCount

• **get renderedActionCount**(): *number*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[renderedActionCount](_card_elements_.containerwithactions.md#protected-renderedactioncount)*

*Overrides [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[renderedActionCount](_card_elements_.stylablecardelementcontainer.md#protected-renderedactioncount)*

**Returns:** *number*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[renderedElement](_card_elements_.cardelement.md#renderedelement)*

**Returns:** *HTMLElement*

___

###  selectAction

• **get selectAction**(): *[Action](_card_elements_.action.md)*

*Inherited from [Container](_card_elements_.container.md).[selectAction](_card_elements_.container.md#selectaction)*

**Returns:** *[Action](_card_elements_.action.md)*

• **set selectAction**(`value`: [Action](_card_elements_.action.md)): *void*

*Inherited from [Container](_card_elements_.container.md).[selectAction](_card_elements_.container.md#selectaction)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [Action](_card_elements_.action.md) |

**Returns:** *void*

___

###  separatorElement

• **get separatorElement**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[separatorElement](_card_elements_.cardelement.md#separatorelement)*

**Returns:** *HTMLElement*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/_enums_.orientation.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[separatorOrientation](_card_elements_.cardelement.md#protected-separatororientation)*

**Returns:** *[Orientation](../enums/_enums_.orientation.md)*

___

###  style

• **get style**(): *string*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[style](_card_elements_.stylablecardelementcontainer.md#style)*

**Returns:** *string*

• **set style**(`value`: string): *void*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[style](_card_elements_.stylablecardelementcontainer.md#style)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

### `Protected` supportsMinHeight

• **get supportsMinHeight**(): *boolean*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[supportsMinHeight](_card_elements_.stylablecardelementcontainer.md#protected-supportsminheight)*

*Overrides [CardElement](_card_elements_.cardelement.md).[supportsMinHeight](_card_elements_.cardelement.md#protected-supportsminheight)*

**Returns:** *boolean*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[useDefaultSizing](_card_elements_.cardelement.md#protected-usedefaultsizing)*

**Returns:** *boolean*

___

### `Static` processMarkdown

• **get processMarkdown**(): *function*

**Returns:** *function*

▸ (`text`: string): *string*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

• **set processMarkdown**(`value`: function): *void*

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

▸ **addAction**(`action`: [Action](_card_elements_.action.md)): *void*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[addAction](_card_elements_.containerwithactions.md#addaction)*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](_card_elements_.action.md) |

**Returns:** *void*

___

###  addItem

▸ **addItem**(`item`: [CardElement](_card_elements_.cardelement.md)): *void*

*Inherited from [Container](_card_elements_.container.md).[addItem](_card_elements_.container.md#additem)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[adjustRenderedElementSize](_card_elements_.cardelement.md#protected-adjustrenderedelementsize)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyBackground

▸ **applyBackground**(): *void*

*Inherited from [Container](_card_elements_.container.md).[applyBackground](_card_elements_.container.md#protected-applybackground)*

*Overrides [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[applyBackground](_card_elements_.stylablecardelementcontainer.md#protected-applybackground)*

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[applyPadding](_card_elements_.stylablecardelementcontainer.md#protected-applypadding)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[applyPadding](_card_elements_.cardelementcontainer.md#protected-applypadding)*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string*

*Inherited from [CardElement](_card_elements_.cardelement.md).[asString](_card_elements_.cardelement.md#asstring)*

**Returns:** *string*

___

###  clear

▸ **clear**(): *void*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[clear](_card_elements_.containerwithactions.md#clear)*

*Overrides [Container](_card_elements_.container.md).[clear](_card_elements_.container.md#clear)*

**Returns:** *void*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[createPlaceholderElement](_card_elements_.cardelement.md#protected-createplaceholderelement)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](_card_elements_.action.md)*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[getActionAt](_card_elements_.containerwithactions.md#getactionat)*

*Overrides [CardElement](_card_elements_.cardelement.md).[getActionAt](_card_elements_.cardelement.md#getactionat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](_card_elements_.action.md)*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[getActionById](_card_elements_.containerwithactions.md#getactionbyid)*

*Overrides [Container](_card_elements_.container.md).[getActionById](_card_elements_.container.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[getActionCount](_card_elements_.containerwithactions.md#getactioncount)*

*Overrides [CardElement](_card_elements_.cardelement.md).[getActionCount](_card_elements_.cardelement.md#getactioncount)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](_card_elements_.input.md)›*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[getAllInputs](_card_elements_.containerwithactions.md#getallinputs)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[getAllInputs](_card_elements_.cardelementcontainer.md#getallinputs)*

**Returns:** *Array‹[Input](_card_elements_.input.md)›*

___

### `Protected` getBleed

▸ **getBleed**(): *boolean*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[getBleed](_card_elements_.stylablecardelementcontainer.md#protected-getbleed)*

**Returns:** *boolean*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[getCustomProperty](_card_elements_.serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

*Overrides [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[getDefaultPadding](_card_elements_.stylablecardelementcontainer.md#protected-getdefaultpadding)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getEffectivePadding](_card_elements_.cardelement.md#geteffectivepadding)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[getEffectiveStyle](_card_elements_.stylablecardelementcontainer.md#geteffectivestyle)*

*Overrides [CardElement](_card_elements_.cardelement.md).[getEffectiveStyle](_card_elements_.cardelement.md#geteffectivestyle)*

**Returns:** *string*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [CardElementContainer](_card_elements_.cardelementcontainer.md).[getElementById](_card_elements_.cardelementcontainer.md#getelementbyid)*

*Overrides [CardElement](_card_elements_.cardelement.md).[getElementById](_card_elements_.cardelement.md#getelementbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [Container](_card_elements_.container.md).[getFirstVisibleRenderedItem](_card_elements_.container.md#getfirstvisiblerendereditem)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[getFirstVisibleRenderedItem](_card_elements_.cardelementcontainer.md#abstract-getfirstvisiblerendereditem)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *Array‹any›*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getForbiddenActionTypes](_card_elements_.cardelement.md#getforbiddenactiontypes)*

**Returns:** *Array‹any›*

___

###  getForbiddenElementTypes

▸ **getForbiddenElementTypes**(): *Array‹string›*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getForbiddenElementTypes](_card_elements_.cardelement.md#getforbiddenelementtypes)*

**Returns:** *Array‹string›*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

*Overrides [Container](_card_elements_.container.md).[getHasBackground](_card_elements_.container.md#protected-gethasbackground)*

**Returns:** *boolean*

___

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): *boolean*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[getHasExpandedAction](_card_elements_.containerwithactions.md#protected-gethasexpandedaction)*

*Overrides [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[getHasExpandedAction](_card_elements_.stylablecardelementcontainer.md#protected-gethasexpandedaction)*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](_shared_.paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getImmediateSurroundingPadding](_card_elements_.cardelement.md#getimmediatesurroundingpadding)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`result` | [PaddingDefinition](_shared_.paddingdefinition.md) | - |
`processTop` | boolean | true |
`processRight` | boolean | true |
`processBottom` | boolean | true |
`processLeft` | boolean | true |

**Returns:** *void*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [Container](_card_elements_.container.md).[getItemAt](_card_elements_.container.md#getitemat)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[getItemAt](_card_elements_.cardelementcontainer.md#abstract-getitemat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Inherited from [Container](_card_elements_.container.md).[getItemCount](_card_elements_.container.md#getitemcount)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[getItemCount](_card_elements_.cardelementcontainer.md#abstract-getitemcount)*

**Returns:** *number*

___

### `Protected` getItemsCollectionPropertyName

▸ **getItemsCollectionPropertyName**(): *string*

*Overrides [Container](_card_elements_.container.md).[getItemsCollectionPropertyName](_card_elements_.container.md#protected-getitemscollectionpropertyname)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [Container](_card_elements_.container.md).[getJsonTypeName](_card_elements_.container.md#getjsontypename)*

**Returns:** *string*

___

###  getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [Container](_card_elements_.container.md).[getLastVisibleRenderedItem](_card_elements_.container.md#getlastvisiblerendereditem)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[getLastVisibleRenderedItem](_card_elements_.cardelementcontainer.md#abstract-getlastvisiblerendereditem)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getPadding](_card_elements_.cardelement.md#protected-getpadding)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](_card_elements_.container.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getParentContainer](_card_elements_.cardelement.md#getparentcontainer)*

**Returns:** *[Container](_card_elements_.container.md)*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[getResourceInformation](_card_elements_.containerwithactions.md#getresourceinformation)*

*Overrides [Container](_card_elements_.container.md).[getResourceInformation](_card_elements_.container.md#getresourceinformation)*

**Returns:** *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getRootElement](_card_elements_.cardelement.md#getrootelement)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

### `Protected` getSelectAction

▸ **getSelectAction**(): *[Action](_card_elements_.action.md)*

*Inherited from [CardElementContainer](_card_elements_.cardelementcontainer.md).[getSelectAction](_card_elements_.cardelementcontainer.md#protected-getselectaction)*

**Returns:** *[Action](_card_elements_.action.md)*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](_card_elements_.cardelement.md)): *number*

*Inherited from [Container](_card_elements_.container.md).[indexOf](_card_elements_.container.md#indexof)*

*Overrides [CardElement](_card_elements_.cardelement.md).[indexOf](_card_elements_.cardelement.md#indexof)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *number*

___

###  insertItemAfter

▸ **insertItemAfter**(`item`: [CardElement](_card_elements_.cardelement.md), `insertAfter`: [CardElement](_card_elements_.cardelement.md)): *void*

*Inherited from [Container](_card_elements_.container.md).[insertItemAfter](_card_elements_.container.md#insertitemafter)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](_card_elements_.cardelement.md) |
`insertAfter` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

###  insertItemBefore

▸ **insertItemBefore**(`item`: [CardElement](_card_elements_.cardelement.md), `insertBefore`: [CardElement](_card_elements_.cardelement.md)): *void*

*Inherited from [Container](_card_elements_.container.md).[insertItemBefore](_card_elements_.container.md#insertitembefore)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](_card_elements_.cardelement.md) |
`insertBefore` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement*

*Overrides [ContainerWithActions](_card_elements_.containerwithactions.md).[internalRender](_card_elements_.containerwithactions.md#protected-internalrender)*

**Returns:** *HTMLElement*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](_card_elements_.validationresults.md)): *void*

*Overrides [ContainerWithActions](_card_elements_.containerwithactions.md).[internalValidateProperties](_card_elements_.containerwithactions.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](_card_elements_.validationresults.md) |

**Returns:** *void*

___

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isAtTheVeryBottom](_card_elements_.cardelement.md#isattheverybottom)*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isAtTheVeryLeft](_card_elements_.cardelement.md#isattheveryleft)*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isAtTheVeryRight](_card_elements_.cardelement.md#isattheveryright)*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isAtTheVeryTop](_card_elements_.cardelement.md#isattheverytop)*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[isBleeding](_card_elements_.stylablecardelementcontainer.md#isbleeding)*

*Overrides [CardElement](_card_elements_.cardelement.md).[isBleeding](_card_elements_.cardelement.md#isbleeding)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[isBleedingAtBottom](_card_elements_.containerwithactions.md#isbleedingatbottom)*

*Overrides [Container](_card_elements_.container.md).[isBleedingAtBottom](_card_elements_.container.md#isbleedingatbottom)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [Container](_card_elements_.container.md).[isBleedingAtTop](_card_elements_.container.md#isbleedingattop)*

*Overrides [CardElement](_card_elements_.cardelement.md).[isBleedingAtTop](_card_elements_.cardelement.md#isbleedingattop)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isBottomElement](_card_elements_.cardelement.md#isbottomelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isDesignMode](_card_elements_.cardelement.md#isdesignmode)*

**Returns:** *boolean*

___

### `Protected` isElementAllowed

▸ **isElementAllowed**(`element`: [CardElement](_card_elements_.cardelement.md), `forbiddenElementTypes`: Array‹string›): *boolean*

*Inherited from [CardElementContainer](_card_elements_.cardelementcontainer.md).[isElementAllowed](_card_elements_.cardelementcontainer.md#protected-iselementallowed)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |
`forbiddenElementTypes` | Array‹string› |

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [Container](_card_elements_.container.md).[isFirstElement](_card_elements_.container.md#isfirstelement)*

*Overrides [CardElement](_card_elements_.cardelement.md).[isFirstElement](_card_elements_.cardelement.md#isfirstelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isHiddenDueToOverflow](_card_elements_.cardelement.md#ishiddenduetooverflow)*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [ContainerWithActions](_card_elements_.containerwithactions.md).[isLastElement](_card_elements_.containerwithactions.md#islastelement)*

*Overrides [Container](_card_elements_.container.md).[isLastElement](_card_elements_.container.md#islastelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isLeftMostElement](_card_elements_.cardelement.md#isleftmostelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isRendered

▸ **isRendered**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isRendered](_card_elements_.cardelement.md#isrendered)*

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isRightMostElement](_card_elements_.cardelement.md#isrightmostelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isRtl

▸ **isRtl**(): *boolean*

*Inherited from [Container](_card_elements_.container.md).[isRtl](_card_elements_.container.md#isrtl)*

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isTopElement](_card_elements_.cardelement.md#istopelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[overrideInternalRender](_card_elements_.cardelement.md#protected-overrideinternalrender)*

**Returns:** *HTMLElement*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

*Overrides [ContainerWithActions](_card_elements_.containerwithactions.md).[parse](_card_elements_.containerwithactions.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *void*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[remove](_card_elements_.cardelement.md#remove)*

**Returns:** *boolean*

___

###  removeItem

▸ **removeItem**(`item`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [Container](_card_elements_.container.md).[removeItem](_card_elements_.container.md#removeitem)*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[removeItem](_card_elements_.cardelementcontainer.md#abstract-removeitem)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  render

▸ **render**(`target?`: HTMLElement): *HTMLElement*

*Overrides [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[render](_card_elements_.stylablecardelementcontainer.md#render)*

**Parameters:**

Name | Type |
------ | ------ |
`target?` | HTMLElement |

**Returns:** *HTMLElement*

___

### `Protected` setBleed

▸ **setBleed**(`value`: boolean): *void*

*Inherited from [StylableCardElementContainer](_card_elements_.stylablecardelementcontainer.md).[setBleed](_card_elements_.stylablecardelementcontainer.md#protected-setbleed)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](_card_elements_.serializableobject.md).[setCustomProperty](_card_elements_.serializableobject.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](_shared_.paddingdefinition.md)): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[setPadding](_card_elements_.cardelement.md#protected-setpadding)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](_shared_.paddingdefinition.md) |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardElement](_card_elements_.cardelement.md)): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[setParent](_card_elements_.cardelement.md#setparent)*

*Overrides [CardObject](_card_elements_.cardobject.md).[setParent](_card_elements_.cardobject.md#abstract-setparent)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

### `Protected` setSelectAction

▸ **setSelectAction**(`value`: [Action](_card_elements_.action.md)): *void*

*Inherited from [CardElementContainer](_card_elements_.cardelementcontainer.md).[setSelectAction](_card_elements_.cardelementcontainer.md#protected-setselectaction)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [Action](_card_elements_.action.md) |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[setShouldFallback](_card_elements_.cardelement.md#setshouldfallback)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Overrides [CardElement](_card_elements_.cardelement.md).[shouldFallback](_card_elements_.cardelement.md#shouldfallback)*

**Returns:** *boolean*

___

### `Protected` supportsExcplitiHeight

▸ **supportsExcplitiHeight**(): *boolean*

*Inherited from [Container](_card_elements_.container.md).[supportsExcplitiHeight](_card_elements_.container.md#protected-supportsexcplitiheight)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [ContainerWithActions](_card_elements_.containerwithactions.md).[toJSON](_card_elements_.containerwithactions.md#tojson)*

**Returns:** *any*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Inherited from [Container](_card_elements_.container.md).[truncateOverflow](_card_elements_.container.md#protected-truncateoverflow)*

*Overrides [CardElement](_card_elements_.cardelement.md).[truncateOverflow](_card_elements_.cardelement.md#protected-truncateoverflow)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Inherited from [Container](_card_elements_.container.md).[undoOverflowTruncation](_card_elements_.container.md#protected-undooverflowtruncation)*

*Overrides [CardElement](_card_elements_.cardelement.md).[undoOverflowTruncation](_card_elements_.cardelement.md#protected-undooverflowtruncation)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Overrides [CardElementContainer](_card_elements_.cardelementcontainer.md).[updateLayout](_card_elements_.cardelementcontainer.md#updatelayout)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | true |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](_card_elements_.validationresults.md)*

*Inherited from [CardObject](_card_elements_.cardobject.md).[validateProperties](_card_elements_.cardobject.md#validateproperties)*

**Returns:** *[ValidationResults](_card_elements_.validationresults.md)*

___

### `Static` applyMarkdown

▸ **applyMarkdown**(`text`: string): *[IMarkdownProcessingResult](../interfaces/_card_elements_.imarkdownprocessingresult.md)*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

**Returns:** *[IMarkdownProcessingResult](../interfaces/_card_elements_.imarkdownprocessingresult.md)*
