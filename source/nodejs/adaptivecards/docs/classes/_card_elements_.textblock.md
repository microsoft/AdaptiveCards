[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [TextBlock](_card_elements_.textblock.md)

# Class: TextBlock

## Hierarchy

  ↳ [BaseTextBlock](_card_elements_.basetextblock.md)

  ↳ **TextBlock**

## Index

### Properties

* [color](_card_elements_.textblock.md#color)
* [customCssSelector](_card_elements_.textblock.md#customcssselector)
* [fontType](_card_elements_.textblock.md#optional-fonttype)
* [height](_card_elements_.textblock.md#height)
* [horizontalAlignment](_card_elements_.textblock.md#optional-horizontalalignment)
* [id](_card_elements_.textblock.md#id)
* [isSubtle](_card_elements_.textblock.md#issubtle)
* [maxLines](_card_elements_.textblock.md#maxlines)
* [minPixelHeight](_card_elements_.textblock.md#optional-minpixelheight)
* [requires](_card_elements_.textblock.md#requires)
* [separator](_card_elements_.textblock.md#separator)
* [size](_card_elements_.textblock.md#size)
* [spacing](_card_elements_.textblock.md#spacing)
* [useMarkdown](_card_elements_.textblock.md#usemarkdown)
* [weight](_card_elements_.textblock.md#weight)
* [wrap](_card_elements_.textblock.md#wrap)

### Accessors

* [allowCustomPadding](_card_elements_.textblock.md#protected-allowcustompadding)
* [defaultStyle](_card_elements_.textblock.md#protected-defaultstyle)
* [effectiveColor](_card_elements_.textblock.md#effectivecolor)
* [hasVisibleSeparator](_card_elements_.textblock.md#hasvisibleseparator)
* [hostConfig](_card_elements_.textblock.md#hostconfig)
* [index](_card_elements_.textblock.md#index)
* [isInline](_card_elements_.textblock.md#isinline)
* [isInteractive](_card_elements_.textblock.md#isinteractive)
* [isStandalone](_card_elements_.textblock.md#isstandalone)
* [isVisible](_card_elements_.textblock.md#isvisible)
* [lang](_card_elements_.textblock.md#lang)
* [parent](_card_elements_.textblock.md#parent)
* [renderedElement](_card_elements_.textblock.md#renderedelement)
* [selectAction](_card_elements_.textblock.md#selectaction)
* [separatorElement](_card_elements_.textblock.md#separatorelement)
* [separatorOrientation](_card_elements_.textblock.md#protected-separatororientation)
* [supportsMinHeight](_card_elements_.textblock.md#protected-supportsminheight)
* [text](_card_elements_.textblock.md#text)
* [useDefaultSizing](_card_elements_.textblock.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](_card_elements_.textblock.md#protected-adjustrenderedelementsize)
* [applyPadding](_card_elements_.textblock.md#protected-applypadding)
* [applyStylesTo](_card_elements_.textblock.md#applystylesto)
* [asString](_card_elements_.textblock.md#asstring)
* [createPlaceholderElement](_card_elements_.textblock.md#protected-createplaceholderelement)
* [getActionAt](_card_elements_.textblock.md#getactionat)
* [getActionById](_card_elements_.textblock.md#getactionbyid)
* [getActionCount](_card_elements_.textblock.md#getactioncount)
* [getAllInputs](_card_elements_.textblock.md#getallinputs)
* [getColorDefinition](_card_elements_.textblock.md#protected-getcolordefinition)
* [getCustomProperty](_card_elements_.textblock.md#getcustomproperty)
* [getDefaultPadding](_card_elements_.textblock.md#protected-getdefaultpadding)
* [getEffectivePadding](_card_elements_.textblock.md#geteffectivepadding)
* [getEffectiveStyle](_card_elements_.textblock.md#geteffectivestyle)
* [getEffectiveStyleDefinition](_card_elements_.textblock.md#protected-geteffectivestyledefinition)
* [getElementById](_card_elements_.textblock.md#getelementbyid)
* [getFontSize](_card_elements_.textblock.md#protected-getfontsize)
* [getForbiddenActionTypes](_card_elements_.textblock.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](_card_elements_.textblock.md#getforbiddenelementtypes)
* [getHasBackground](_card_elements_.textblock.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](_card_elements_.textblock.md#getimmediatesurroundingpadding)
* [getJsonTypeName](_card_elements_.textblock.md#getjsontypename)
* [getPadding](_card_elements_.textblock.md#protected-getpadding)
* [getParentContainer](_card_elements_.textblock.md#getparentcontainer)
* [getRenderedDomElementType](_card_elements_.textblock.md#protected-getrendereddomelementtype)
* [getResourceInformation](_card_elements_.textblock.md#getresourceinformation)
* [getRootElement](_card_elements_.textblock.md#getrootelement)
* [indexOf](_card_elements_.textblock.md#indexof)
* [internalRender](_card_elements_.textblock.md#protected-internalrender)
* [internalValidateProperties](_card_elements_.textblock.md#internalvalidateproperties)
* [isAtTheVeryBottom](_card_elements_.textblock.md#isattheverybottom)
* [isAtTheVeryLeft](_card_elements_.textblock.md#isattheveryleft)
* [isAtTheVeryRight](_card_elements_.textblock.md#isattheveryright)
* [isAtTheVeryTop](_card_elements_.textblock.md#isattheverytop)
* [isBleeding](_card_elements_.textblock.md#isbleeding)
* [isBleedingAtBottom](_card_elements_.textblock.md#isbleedingatbottom)
* [isBleedingAtTop](_card_elements_.textblock.md#isbleedingattop)
* [isBottomElement](_card_elements_.textblock.md#isbottomelement)
* [isDesignMode](_card_elements_.textblock.md#isdesignmode)
* [isFirstElement](_card_elements_.textblock.md#isfirstelement)
* [isHiddenDueToOverflow](_card_elements_.textblock.md#ishiddenduetooverflow)
* [isLastElement](_card_elements_.textblock.md#islastelement)
* [isLeftMostElement](_card_elements_.textblock.md#isleftmostelement)
* [isRendered](_card_elements_.textblock.md#isrendered)
* [isRightMostElement](_card_elements_.textblock.md#isrightmostelement)
* [isTopElement](_card_elements_.textblock.md#istopelement)
* [overrideInternalRender](_card_elements_.textblock.md#protected-overrideinternalrender)
* [parse](_card_elements_.textblock.md#parse)
* [remove](_card_elements_.textblock.md#remove)
* [render](_card_elements_.textblock.md#render)
* [setCustomProperty](_card_elements_.textblock.md#setcustomproperty)
* [setPadding](_card_elements_.textblock.md#protected-setpadding)
* [setParent](_card_elements_.textblock.md#setparent)
* [setShouldFallback](_card_elements_.textblock.md#setshouldfallback)
* [setText](_card_elements_.textblock.md#protected-settext)
* [shouldFallback](_card_elements_.textblock.md#shouldfallback)
* [toJSON](_card_elements_.textblock.md#tojson)
* [truncateOverflow](_card_elements_.textblock.md#protected-truncateoverflow)
* [undoOverflowTruncation](_card_elements_.textblock.md#protected-undooverflowtruncation)
* [updateLayout](_card_elements_.textblock.md#updatelayout)
* [validateProperties](_card_elements_.textblock.md#validateproperties)

## Properties

###  color

• **color**: *[TextColor](../enums/_enums_.textcolor.md)* = Enums.TextColor.Default

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[color](_card_elements_.basetextblock.md#color)*

___

###  customCssSelector

• **customCssSelector**: *string* = null

*Inherited from [CardElement](_card_elements_.cardelement.md).[customCssSelector](_card_elements_.cardelement.md#customcssselector)*

___

### `Optional` fontType

• **fontType**? : *[FontType](../enums/_enums_.fonttype.md)* = null

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[fontType](_card_elements_.basetextblock.md#optional-fonttype)*

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

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[isSubtle](_card_elements_.basetextblock.md#issubtle)*

___

###  maxLines

• **maxLines**: *number*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *number* = null

*Inherited from [CardElement](_card_elements_.cardelement.md).[minPixelHeight](_card_elements_.cardelement.md#optional-minpixelheight)*

___

###  requires

• **requires**: *[HostCapabilities](_host_config_.hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

*Inherited from [CardElement](_card_elements_.cardelement.md).[requires](_card_elements_.cardelement.md#requires)*

___

###  separator

• **separator**: *boolean* = false

*Inherited from [CardElement](_card_elements_.cardelement.md).[separator](_card_elements_.cardelement.md#separator)*

___

###  size

• **size**: *[TextSize](../enums/_enums_.textsize.md)* = Enums.TextSize.Default

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[size](_card_elements_.basetextblock.md#size)*

___

###  spacing

• **spacing**: *[Spacing](../enums/_enums_.spacing.md)* = Enums.Spacing.Default

*Inherited from [CardElement](_card_elements_.cardelement.md).[spacing](_card_elements_.cardelement.md#spacing)*

___

###  useMarkdown

• **useMarkdown**: *boolean* = true

___

###  weight

• **weight**: *[TextWeight](../enums/_enums_.textweight.md)* = Enums.TextWeight.Default

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[weight](_card_elements_.basetextblock.md#weight)*

___

###  wrap

• **wrap**: *boolean* = false

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[allowCustomPadding](_card_elements_.cardelement.md#protected-allowcustompadding)*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](_card_elements_.cardelement.md).[defaultStyle](_card_elements_.cardelement.md#protected-defaultstyle)*

**Returns:** *string*

___

###  effectiveColor

• **get effectiveColor**(): *[TextColor](../enums/_enums_.textcolor.md)*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[effectiveColor](_card_elements_.basetextblock.md#effectivecolor)*

**Returns:** *[TextColor](../enums/_enums_.textcolor.md)*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[hasVisibleSeparator](_card_elements_.cardelement.md#hasvisibleseparator)*

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

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isStandalone](_card_elements_.cardelement.md#isstandalone)*

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

###  parent

• **get parent**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[parent](_card_elements_.cardelement.md#parent)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[renderedElement](_card_elements_.cardelement.md#renderedelement)*

**Returns:** *HTMLElement*

___

###  selectAction

• **get selectAction**(): *[Action](_card_elements_.action.md)*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[selectAction](_card_elements_.basetextblock.md#selectaction)*

**Returns:** *[Action](_card_elements_.action.md)*

• **set selectAction**(`value`: [Action](_card_elements_.action.md)): *void*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[selectAction](_card_elements_.basetextblock.md#selectaction)*

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

### `Protected` supportsMinHeight

• **get supportsMinHeight**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[supportsMinHeight](_card_elements_.cardelement.md#protected-supportsminheight)*

**Returns:** *boolean*

___

###  text

• **get text**(): *string*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[text](_card_elements_.basetextblock.md#text)*

**Returns:** *string*

• **set text**(`value`: string): *void*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[text](_card_elements_.basetextblock.md#text)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[useDefaultSizing](_card_elements_.cardelement.md#protected-usedefaultsizing)*

**Returns:** *boolean*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[adjustRenderedElementSize](_card_elements_.cardelement.md#protected-adjustrenderedelementsize)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[applyPadding](_card_elements_.cardelement.md#protected-applypadding)*

**Returns:** *void*

___

###  applyStylesTo

▸ **applyStylesTo**(`targetElement`: HTMLElement): *void*

*Overrides [BaseTextBlock](_card_elements_.basetextblock.md).[applyStylesTo](_card_elements_.basetextblock.md#applystylesto)*

**Parameters:**

Name | Type |
------ | ------ |
`targetElement` | HTMLElement |

**Returns:** *void*

___

###  asString

▸ **asString**(): *string*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[asString](_card_elements_.basetextblock.md#asstring)*

*Overrides [CardElement](_card_elements_.cardelement.md).[asString](_card_elements_.cardelement.md#asstring)*

**Returns:** *string*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[createPlaceholderElement](_card_elements_.cardelement.md#protected-createplaceholderelement)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](_card_elements_.action.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getActionAt](_card_elements_.cardelement.md#getactionat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](_card_elements_.action.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getActionById](_card_elements_.cardelement.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getActionCount](_card_elements_.cardelement.md#getactioncount)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](_card_elements_.input.md)›*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getAllInputs](_card_elements_.cardelement.md#getallinputs)*

**Returns:** *Array‹[Input](_card_elements_.input.md)›*

___

### `Protected` getColorDefinition

▸ **getColorDefinition**(`colorSet`: [ColorSetDefinition](_host_config_.colorsetdefinition.md), `color`: [TextColor](../enums/_enums_.textcolor.md)): *[TextColorDefinition](_host_config_.textcolordefinition.md)*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[getColorDefinition](_card_elements_.basetextblock.md#protected-getcolordefinition)*

**Parameters:**

Name | Type |
------ | ------ |
`colorSet` | [ColorSetDefinition](_host_config_.colorsetdefinition.md) |
`color` | [TextColor](../enums/_enums_.textcolor.md) |

**Returns:** *[TextColorDefinition](_host_config_.textcolordefinition.md)*

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

*Inherited from [CardElement](_card_elements_.cardelement.md).[getDefaultPadding](_card_elements_.cardelement.md#protected-getdefaultpadding)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getEffectivePadding](_card_elements_.cardelement.md#geteffectivepadding)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getEffectiveStyle](_card_elements_.cardelement.md#geteffectivestyle)*

**Returns:** *string*

___

### `Protected` getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](_host_config_.containerstyledefinition.md)‹›*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[getEffectiveStyleDefinition](_card_elements_.basetextblock.md#protected-geteffectivestyledefinition)*

**Returns:** *[ContainerStyleDefinition](_host_config_.containerstyledefinition.md)‹›*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getElementById](_card_elements_.cardelement.md#getelementbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

### `Protected` getFontSize

▸ **getFontSize**(`fontType`: [FontTypeDefinition](_host_config_.fonttypedefinition.md)): *number*

*Inherited from [BaseTextBlock](_card_elements_.basetextblock.md).[getFontSize](_card_elements_.basetextblock.md#protected-getfontsize)*

**Parameters:**

Name | Type |
------ | ------ |
`fontType` | [FontTypeDefinition](_host_config_.fonttypedefinition.md) |

**Returns:** *number*

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

*Inherited from [CardElement](_card_elements_.cardelement.md).[getHasBackground](_card_elements_.cardelement.md#protected-gethasbackground)*

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

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardElement](_card_elements_.cardelement.md).[getJsonTypeName](_card_elements_.cardelement.md#abstract-getjsontypename)*

**Returns:** *string*

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

### `Protected` getRenderedDomElementType

▸ **getRenderedDomElementType**(): *string*

**Returns:** *string*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getResourceInformation](_card_elements_.cardelement.md#getresourceinformation)*

**Returns:** *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](_card_elements_.cardelement.md)*

*Inherited from [CardElement](_card_elements_.cardelement.md).[getRootElement](_card_elements_.cardelement.md#getrootelement)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](_card_elements_.cardelement.md)): *number*

*Inherited from [CardElement](_card_elements_.cardelement.md).[indexOf](_card_elements_.cardelement.md#indexof)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *number*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement*

*Overrides [CardElement](_card_elements_.cardelement.md).[internalRender](_card_elements_.cardelement.md#protected-abstract-internalrender)*

**Returns:** *HTMLElement*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](_card_elements_.validationresults.md)): *void*

*Inherited from [CardObject](_card_elements_.cardobject.md).[internalValidateProperties](_card_elements_.cardobject.md#internalvalidateproperties)*

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

*Inherited from [CardElement](_card_elements_.cardelement.md).[isBleeding](_card_elements_.cardelement.md#isbleeding)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isBleedingAtBottom](_card_elements_.cardelement.md#isbleedingatbottom)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isBleedingAtTop](_card_elements_.cardelement.md#isbleedingattop)*

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

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[isFirstElement](_card_elements_.cardelement.md#isfirstelement)*

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

*Inherited from [CardElement](_card_elements_.cardelement.md).[isLastElement](_card_elements_.cardelement.md#islastelement)*

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

*Overrides [BaseTextBlock](_card_elements_.basetextblock.md).[parse](_card_elements_.basetextblock.md#parse)*

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

###  render

▸ **render**(): *HTMLElement*

*Inherited from [CardElement](_card_elements_.cardelement.md).[render](_card_elements_.cardelement.md#render)*

**Returns:** *HTMLElement*

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

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardElement](_card_elements_.cardelement.md).[setShouldFallback](_card_elements_.cardelement.md#setshouldfallback)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setText

▸ **setText**(`value`: string): *void*

*Overrides [BaseTextBlock](_card_elements_.basetextblock.md).[setText](_card_elements_.basetextblock.md#protected-settext)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [CardElement](_card_elements_.cardelement.md).[shouldFallback](_card_elements_.cardelement.md#shouldfallback)*

*Overrides [CardObject](_card_elements_.cardobject.md).[shouldFallback](_card_elements_.cardobject.md#abstract-shouldfallback)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [BaseTextBlock](_card_elements_.basetextblock.md).[toJSON](_card_elements_.basetextblock.md#tojson)*

**Returns:** *any*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Overrides [CardElement](_card_elements_.cardelement.md).[truncateOverflow](_card_elements_.cardelement.md#protected-truncateoverflow)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Overrides [CardElement](_card_elements_.cardelement.md).[undoOverflowTruncation](_card_elements_.cardelement.md#protected-undooverflowtruncation)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Overrides [CardElement](_card_elements_.cardelement.md).[updateLayout](_card_elements_.cardelement.md#updatelayout)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | false |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](_card_elements_.validationresults.md)*

*Inherited from [CardObject](_card_elements_.cardobject.md).[validateProperties](_card_elements_.cardobject.md#validateproperties)*

**Returns:** *[ValidationResults](_card_elements_.validationresults.md)*
