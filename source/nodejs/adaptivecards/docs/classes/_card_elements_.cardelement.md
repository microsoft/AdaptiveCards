[Adaptive Cards Javascript SDK](../README.md) › ["card-elements"](../modules/_card_elements_.md) › [CardElement](_card_elements_.cardelement.md)

# Class: CardElement

## Hierarchy

  ↳ [CardObject](_card_elements_.cardobject.md)

  ↳ **CardElement**

  ↳ [BaseTextBlock](_card_elements_.basetextblock.md)

  ↳ [RichTextBlock](_card_elements_.richtextblock.md)

  ↳ [FactSet](_card_elements_.factset.md)

  ↳ [Image](_card_elements_.image.md)

  ↳ [CardElementContainer](_card_elements_.cardelementcontainer.md)

  ↳ [Media](_card_elements_.media.md)

  ↳ [Input](_card_elements_.input.md)

  ↳ [ActionSet](_card_elements_.actionset.md)

## Index

### Properties

* [customCssSelector](_card_elements_.cardelement.md#customcssselector)
* [height](_card_elements_.cardelement.md#height)
* [horizontalAlignment](_card_elements_.cardelement.md#optional-horizontalalignment)
* [id](_card_elements_.cardelement.md#id)
* [minPixelHeight](_card_elements_.cardelement.md#optional-minpixelheight)
* [requires](_card_elements_.cardelement.md#requires)
* [separator](_card_elements_.cardelement.md#separator)
* [spacing](_card_elements_.cardelement.md#spacing)

### Accessors

* [allowCustomPadding](_card_elements_.cardelement.md#protected-allowcustompadding)
* [defaultStyle](_card_elements_.cardelement.md#protected-defaultstyle)
* [hasVisibleSeparator](_card_elements_.cardelement.md#hasvisibleseparator)
* [hostConfig](_card_elements_.cardelement.md#hostconfig)
* [index](_card_elements_.cardelement.md#index)
* [isInline](_card_elements_.cardelement.md#isinline)
* [isInteractive](_card_elements_.cardelement.md#isinteractive)
* [isStandalone](_card_elements_.cardelement.md#isstandalone)
* [isVisible](_card_elements_.cardelement.md#isvisible)
* [lang](_card_elements_.cardelement.md#lang)
* [parent](_card_elements_.cardelement.md#parent)
* [renderedElement](_card_elements_.cardelement.md#renderedelement)
* [separatorElement](_card_elements_.cardelement.md#separatorelement)
* [separatorOrientation](_card_elements_.cardelement.md#protected-separatororientation)
* [supportsMinHeight](_card_elements_.cardelement.md#protected-supportsminheight)
* [useDefaultSizing](_card_elements_.cardelement.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](_card_elements_.cardelement.md#protected-adjustrenderedelementsize)
* [applyPadding](_card_elements_.cardelement.md#protected-applypadding)
* [asString](_card_elements_.cardelement.md#asstring)
* [createPlaceholderElement](_card_elements_.cardelement.md#protected-createplaceholderelement)
* [getActionAt](_card_elements_.cardelement.md#getactionat)
* [getActionById](_card_elements_.cardelement.md#getactionbyid)
* [getActionCount](_card_elements_.cardelement.md#getactioncount)
* [getAllInputs](_card_elements_.cardelement.md#getallinputs)
* [getCustomProperty](_card_elements_.cardelement.md#getcustomproperty)
* [getDefaultPadding](_card_elements_.cardelement.md#protected-getdefaultpadding)
* [getEffectivePadding](_card_elements_.cardelement.md#geteffectivepadding)
* [getEffectiveStyle](_card_elements_.cardelement.md#geteffectivestyle)
* [getElementById](_card_elements_.cardelement.md#getelementbyid)
* [getForbiddenActionTypes](_card_elements_.cardelement.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](_card_elements_.cardelement.md#getforbiddenelementtypes)
* [getHasBackground](_card_elements_.cardelement.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](_card_elements_.cardelement.md#getimmediatesurroundingpadding)
* [getJsonTypeName](_card_elements_.cardelement.md#abstract-getjsontypename)
* [getPadding](_card_elements_.cardelement.md#protected-getpadding)
* [getParentContainer](_card_elements_.cardelement.md#getparentcontainer)
* [getResourceInformation](_card_elements_.cardelement.md#getresourceinformation)
* [getRootElement](_card_elements_.cardelement.md#getrootelement)
* [indexOf](_card_elements_.cardelement.md#indexof)
* [internalRender](_card_elements_.cardelement.md#protected-abstract-internalrender)
* [internalValidateProperties](_card_elements_.cardelement.md#internalvalidateproperties)
* [isAtTheVeryBottom](_card_elements_.cardelement.md#isattheverybottom)
* [isAtTheVeryLeft](_card_elements_.cardelement.md#isattheveryleft)
* [isAtTheVeryRight](_card_elements_.cardelement.md#isattheveryright)
* [isAtTheVeryTop](_card_elements_.cardelement.md#isattheverytop)
* [isBleeding](_card_elements_.cardelement.md#isbleeding)
* [isBleedingAtBottom](_card_elements_.cardelement.md#isbleedingatbottom)
* [isBleedingAtTop](_card_elements_.cardelement.md#isbleedingattop)
* [isBottomElement](_card_elements_.cardelement.md#isbottomelement)
* [isDesignMode](_card_elements_.cardelement.md#isdesignmode)
* [isFirstElement](_card_elements_.cardelement.md#isfirstelement)
* [isHiddenDueToOverflow](_card_elements_.cardelement.md#ishiddenduetooverflow)
* [isLastElement](_card_elements_.cardelement.md#islastelement)
* [isLeftMostElement](_card_elements_.cardelement.md#isleftmostelement)
* [isRendered](_card_elements_.cardelement.md#isrendered)
* [isRightMostElement](_card_elements_.cardelement.md#isrightmostelement)
* [isTopElement](_card_elements_.cardelement.md#istopelement)
* [overrideInternalRender](_card_elements_.cardelement.md#protected-overrideinternalrender)
* [parse](_card_elements_.cardelement.md#parse)
* [remove](_card_elements_.cardelement.md#remove)
* [render](_card_elements_.cardelement.md#render)
* [setCustomProperty](_card_elements_.cardelement.md#setcustomproperty)
* [setPadding](_card_elements_.cardelement.md#protected-setpadding)
* [setParent](_card_elements_.cardelement.md#setparent)
* [setShouldFallback](_card_elements_.cardelement.md#setshouldfallback)
* [shouldFallback](_card_elements_.cardelement.md#shouldfallback)
* [toJSON](_card_elements_.cardelement.md#tojson)
* [truncateOverflow](_card_elements_.cardelement.md#protected-truncateoverflow)
* [undoOverflowTruncation](_card_elements_.cardelement.md#protected-undooverflowtruncation)
* [updateLayout](_card_elements_.cardelement.md#updatelayout)
* [validateProperties](_card_elements_.cardelement.md#validateproperties)

## Properties

###  customCssSelector

• **customCssSelector**: *string* = null

___

###  height

• **height**: *[CardElementHeight](../modules/_card_elements_.md#cardelementheight)* = "auto"

___

### `Optional` horizontalAlignment

• **horizontalAlignment**? : *[HorizontalAlignment](../enums/_enums_.horizontalalignment.md)* = null

___

###  id

• **id**: *string*

*Inherited from [CardObject](_card_elements_.cardobject.md).[id](_card_elements_.cardobject.md#id)*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *number* = null

___

###  requires

• **requires**: *[HostCapabilities](_host_config_.hostcapabilities.md)‹›* = new HostConfig.HostCapabilities()

___

###  separator

• **separator**: *boolean* = false

___

###  spacing

• **spacing**: *[Spacing](../enums/_enums_.spacing.md)* = Enums.Spacing.Default

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

**Returns:** *string*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](_host_config_.hostconfig.md)*

**Returns:** *[HostConfig](_host_config_.hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](_host_config_.hostconfig.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](_host_config_.hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string*

**Returns:** *string*

• **set lang**(`value`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](_card_elements_.cardelement.md)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement*

**Returns:** *HTMLElement*

___

###  separatorElement

• **get separatorElement**(): *HTMLElement*

**Returns:** *HTMLElement*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/_enums_.orientation.md)*

**Returns:** *[Orientation](../enums/_enums_.orientation.md)*

___

### `Protected` supportsMinHeight

• **get supportsMinHeight**(): *boolean*

**Returns:** *boolean*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

**Returns:** *boolean*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string*

**Returns:** *string*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](_card_elements_.action.md)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](_card_elements_.action.md)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](_card_elements_.action.md)*

___

###  getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *Array‹[Input](_card_elements_.input.md)›*

**Returns:** *Array‹[Input](_card_elements_.input.md)›*

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

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](_card_elements_.cardelement.md)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *Array‹any›*

**Returns:** *Array‹any›*

___

###  getForbiddenElementTypes

▸ **getForbiddenElementTypes**(): *Array‹string›*

**Returns:** *Array‹string›*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](_shared_.paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

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

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardObject](_card_elements_.cardobject.md).[getJsonTypeName](_card_elements_.cardobject.md#abstract-getjsontypename)*

**Returns:** *string*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](_shared_.paddingdefinition.md)*

**Returns:** *[PaddingDefinition](_shared_.paddingdefinition.md)*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](_card_elements_.container.md)*

**Returns:** *[Container](_card_elements_.container.md)*

___

###  getResourceInformation

▸ **getResourceInformation**(): *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

**Returns:** *Array‹[IResourceInformation](../interfaces/_shared_.iresourceinformation.md)›*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](_card_elements_.cardelement.md)*

**Returns:** *[CardElement](_card_elements_.cardelement.md)*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](_card_elements_.cardelement.md)): *number*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *number*

___

### `Protected` `Abstract` internalRender

▸ **internalRender**(): *HTMLElement*

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

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isRendered

▸ **isRendered**(): *boolean*

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](_card_elements_.cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement*

**Returns:** *HTMLElement*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

*Overrides [CardObject](_card_elements_.cardobject.md).[parse](_card_elements_.cardobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *void*

___

###  remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement*

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

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](_shared_.paddingdefinition.md) |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardElement](_card_elements_.cardelement.md)): *void*

*Overrides [CardObject](_card_elements_.cardobject.md).[setParent](_card_elements_.cardobject.md#abstract-setparent)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardElement](_card_elements_.cardelement.md) |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Overrides [CardObject](_card_elements_.cardobject.md).[shouldFallback](_card_elements_.cardobject.md#abstract-shouldfallback)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [CardObject](_card_elements_.cardobject.md).[toJSON](_card_elements_.cardobject.md#tojson)*

**Returns:** *any*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

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
