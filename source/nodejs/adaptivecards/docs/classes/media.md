[Adaptive Cards Javascript SDK](../README.md) › [Media](media.md)

# Class: Media

## Hierarchy

  ↳ [CardElement](cardelement.md)

  ↳ **Media**

## Index

### Properties

* [altText](media.md#alttext)
* [customCssSelector](media.md#customcssselector)
* [height](media.md#height)
* [horizontalAlignment](media.md#optional-horizontalalignment)
* [id](media.md#id)
* [minPixelHeight](media.md#optional-minpixelheight)
* [poster](media.md#poster)
* [requires](media.md#requires)
* [separator](media.md#separator)
* [sources](media.md#sources)
* [spacing](media.md#spacing)
* [onPlay](media.md#static-onplay)
* [supportedMediaTypes](media.md#static-supportedmediatypes)

### Accessors

* [allowCustomPadding](media.md#protected-allowcustompadding)
* [defaultStyle](media.md#protected-defaultstyle)
* [hasVisibleSeparator](media.md#hasvisibleseparator)
* [hostConfig](media.md#hostconfig)
* [index](media.md#index)
* [isInline](media.md#isinline)
* [isInteractive](media.md#isinteractive)
* [isStandalone](media.md#isstandalone)
* [isVisible](media.md#isvisible)
* [lang](media.md#lang)
* [parent](media.md#parent)
* [renderedElement](media.md#renderedelement)
* [selectedMediaType](media.md#selectedmediatype)
* [separatorElement](media.md#separatorelement)
* [separatorOrientation](media.md#protected-separatororientation)
* [supportsMinHeight](media.md#protected-supportsminheight)
* [useDefaultSizing](media.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](media.md#protected-adjustrenderedelementsize)
* [applyPadding](media.md#protected-applypadding)
* [asString](media.md#asstring)
* [createPlaceholderElement](media.md#protected-createplaceholderelement)
* [getActionAt](media.md#getactionat)
* [getActionById](media.md#getactionbyid)
* [getActionCount](media.md#getactioncount)
* [getAllInputs](media.md#getallinputs)
* [getCustomProperty](media.md#getcustomproperty)
* [getDefaultPadding](media.md#protected-getdefaultpadding)
* [getEffectivePadding](media.md#geteffectivepadding)
* [getEffectiveStyle](media.md#geteffectivestyle)
* [getElementById](media.md#getelementbyid)
* [getForbiddenActionTypes](media.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](media.md#getforbiddenelementtypes)
* [getHasBackground](media.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](media.md#getimmediatesurroundingpadding)
* [getJsonTypeName](media.md#getjsontypename)
* [getPadding](media.md#protected-getpadding)
* [getParentContainer](media.md#getparentcontainer)
* [getResourceInformation](media.md#getresourceinformation)
* [getRootElement](media.md#getrootelement)
* [indexOf](media.md#indexof)
* [internalRender](media.md#protected-internalrender)
* [internalValidateProperties](media.md#internalvalidateproperties)
* [isAtTheVeryBottom](media.md#isattheverybottom)
* [isAtTheVeryLeft](media.md#isattheveryleft)
* [isAtTheVeryRight](media.md#isattheveryright)
* [isAtTheVeryTop](media.md#isattheverytop)
* [isBleeding](media.md#isbleeding)
* [isBleedingAtBottom](media.md#isbleedingatbottom)
* [isBleedingAtTop](media.md#isbleedingattop)
* [isBottomElement](media.md#isbottomelement)
* [isDesignMode](media.md#isdesignmode)
* [isFirstElement](media.md#isfirstelement)
* [isHiddenDueToOverflow](media.md#ishiddenduetooverflow)
* [isLastElement](media.md#islastelement)
* [isLeftMostElement](media.md#isleftmostelement)
* [isRendered](media.md#isrendered)
* [isRightMostElement](media.md#isrightmostelement)
* [isTopElement](media.md#istopelement)
* [overrideInternalRender](media.md#protected-overrideinternalrender)
* [parse](media.md#parse)
* [remove](media.md#remove)
* [render](media.md#render)
* [setCustomProperty](media.md#setcustomproperty)
* [setPadding](media.md#protected-setpadding)
* [setParent](media.md#setparent)
* [setShouldFallback](media.md#setshouldfallback)
* [shouldFallback](media.md#shouldfallback)
* [toJSON](media.md#tojson)
* [truncateOverflow](media.md#protected-truncateoverflow)
* [undoOverflowTruncation](media.md#protected-undooverflowtruncation)
* [updateLayout](media.md#updatelayout)
* [validateProperties](media.md#validateproperties)

## Properties

###  altText

• **altText**: *string*

*Defined in [card-elements.ts:2696](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2696)*

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

###  poster

• **poster**: *string*

*Defined in [card-elements.ts:2695](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2695)*

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

###  sources

• **sources**: *Array‹[MediaSource](mediasource.md)›* = []

*Defined in [card-elements.ts:2694](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2694)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)* = Enums.Spacing.Default

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

*Defined in [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L505)*

___

### `Static` onPlay

▪ **onPlay**: *function* = null

*Defined in [card-elements.ts:2692](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2692)*

#### Type declaration:

▸ (`sender`: [Media](media.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Media](media.md) |

___

### `Static` supportedMediaTypes

▪ **supportedMediaTypes**: *string[]* = ["audio", "video"]

*Defined in [card-elements.ts:2521](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2521)*

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

###  selectedMediaType

• **get selectedMediaType**(): *string*

*Defined in [card-elements.ts:2761](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2761)*

**Returns:** *string*

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

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardElement](cardelement.md).[getJsonTypeName](cardelement.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:2739](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2739)*

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

*Overrides [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

*Defined in [card-elements.ts:2743](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2743)*

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

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

*Defined in [card-elements.ts:2681](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2681)*

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

*Defined in [card-elements.ts:2698](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2698)*

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

*Defined in [card-elements.ts:2716](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2716)*

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
