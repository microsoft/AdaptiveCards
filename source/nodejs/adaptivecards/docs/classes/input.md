[Adaptive Cards Javascript SDK](../README.md) › [Input](input.md)

# Class: Input

## Hierarchy

  ↳ [CardElement](cardelement.md)

  ↳ **Input**

  ↳ [TextInput](textinput.md)

  ↳ [ToggleInput](toggleinput.md)

  ↳ [ChoiceSetInput](choicesetinput.md)

  ↳ [NumberInput](numberinput.md)

  ↳ [DateInput](dateinput.md)

  ↳ [TimeInput](timeinput.md)

## Implements

* [IInput](../interfaces/iinput.md)

## Index

### Properties

* [customCssSelector](input.md#customcssselector)
* [height](input.md#height)
* [horizontalAlignment](input.md#optional-horizontalalignment)
* [id](input.md#id)
* [minPixelHeight](input.md#optional-minpixelheight)
* [onValueChanged](input.md#onvaluechanged)
* [requires](input.md#requires)
* [separator](input.md#separator)
* [spacing](input.md#spacing)
* [title](input.md#title)
* [validation](input.md#validation)

### Accessors

* [allowCustomPadding](input.md#protected-allowcustompadding)
* [defaultStyle](input.md#protected-defaultstyle)
* [defaultValue](input.md#defaultvalue)
* [hasVisibleSeparator](input.md#hasvisibleseparator)
* [hostConfig](input.md#hostconfig)
* [index](input.md#index)
* [inputControlContainerElement](input.md#protected-inputcontrolcontainerelement)
* [isInline](input.md#isinline)
* [isInteractive](input.md#isinteractive)
* [isNullable](input.md#protected-isnullable)
* [isStandalone](input.md#isstandalone)
* [isVisible](input.md#isvisible)
* [lang](input.md#lang)
* [parent](input.md#parent)
* [renderedElement](input.md#renderedelement)
* [renderedInputControlElement](input.md#protected-renderedinputcontrolelement)
* [separatorElement](input.md#separatorelement)
* [separatorOrientation](input.md#protected-separatororientation)
* [supportsMinHeight](input.md#protected-supportsminheight)
* [useDefaultSizing](input.md#protected-usedefaultsizing)
* [value](input.md#value)

### Methods

* [adjustRenderedElementSize](input.md#protected-adjustrenderedelementsize)
* [applyPadding](input.md#protected-applypadding)
* [asString](input.md#asstring)
* [createPlaceholderElement](input.md#protected-createplaceholderelement)
* [getActionAt](input.md#getactionat)
* [getActionById](input.md#getactionbyid)
* [getActionCount](input.md#getactioncount)
* [getAllInputs](input.md#getallinputs)
* [getCustomProperty](input.md#getcustomproperty)
* [getDefaultPadding](input.md#protected-getdefaultpadding)
* [getEffectivePadding](input.md#geteffectivepadding)
* [getEffectiveStyle](input.md#geteffectivestyle)
* [getElementById](input.md#getelementbyid)
* [getForbiddenActionTypes](input.md#getforbiddenactiontypes)
* [getForbiddenElementTypes](input.md#getforbiddenelementtypes)
* [getHasBackground](input.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](input.md#getimmediatesurroundingpadding)
* [getJsonTypeName](input.md#abstract-getjsontypename)
* [getPadding](input.md#protected-getpadding)
* [getParentContainer](input.md#getparentcontainer)
* [getResourceInformation](input.md#getresourceinformation)
* [getRootElement](input.md#getrootelement)
* [indexOf](input.md#indexof)
* [internalRender](input.md#protected-abstract-internalrender)
* [internalValidateProperties](input.md#internalvalidateproperties)
* [isAtTheVeryBottom](input.md#isattheverybottom)
* [isAtTheVeryLeft](input.md#isattheveryleft)
* [isAtTheVeryRight](input.md#isattheveryright)
* [isAtTheVeryTop](input.md#isattheverytop)
* [isBleeding](input.md#isbleeding)
* [isBleedingAtBottom](input.md#isbleedingatbottom)
* [isBleedingAtTop](input.md#isbleedingattop)
* [isBottomElement](input.md#isbottomelement)
* [isDesignMode](input.md#isdesignmode)
* [isFirstElement](input.md#isfirstelement)
* [isHiddenDueToOverflow](input.md#ishiddenduetooverflow)
* [isLastElement](input.md#islastelement)
* [isLeftMostElement](input.md#isleftmostelement)
* [isRendered](input.md#isrendered)
* [isRightMostElement](input.md#isrightmostelement)
* [isTopElement](input.md#istopelement)
* [overrideInternalRender](input.md#protected-overrideinternalrender)
* [parse](input.md#parse)
* [parseInputValue](input.md#protected-parseinputvalue)
* [remove](input.md#remove)
* [render](input.md#render)
* [resetValidationFailureCue](input.md#protected-resetvalidationfailurecue)
* [setCustomProperty](input.md#setcustomproperty)
* [setPadding](input.md#protected-setpadding)
* [setParent](input.md#setparent)
* [setShouldFallback](input.md#setshouldfallback)
* [shouldFallback](input.md#shouldfallback)
* [showValidationErrorMessage](input.md#protected-showvalidationerrormessage)
* [toJSON](input.md#tojson)
* [truncateOverflow](input.md#protected-truncateoverflow)
* [undoOverflowTruncation](input.md#protected-undooverflowtruncation)
* [updateLayout](input.md#updatelayout)
* [validateProperties](input.md#validateproperties)
* [validateValue](input.md#validatevalue)
* [valueChanged](input.md#protected-valuechanged)

## Properties

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

*Implementation of [IInput](../interfaces/iinput.md).[id](../interfaces/iinput.md#id)*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#id)*

*Defined in [card-elements.ts:247](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L247)*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *number* = null

*Inherited from [CardElement](cardelement.md).[minPixelHeight](cardelement.md#optional-minpixelheight)*

*Defined in [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L509)*

___

###  onValueChanged

• **onValueChanged**: *function*

*Defined in [card-elements.ts:2874](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2874)*

#### Type declaration:

▸ (`sender`: [Input](input.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [Input](input.md) |

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

___

###  title

• **title**: *string*

*Defined in [card-elements.ts:2878](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2878)*

___

###  validation

• **validation**: *[InputValidationOptions](inputvalidationoptions.md)‹›* = new InputValidationOptions()

*Defined in [card-elements.ts:2876](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2876)*

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

###  defaultValue

• **get defaultValue**(): *string*

*Defined in [card-elements.ts:2944](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2944)*

**Returns:** *string*

• **set defaultValue**(`value`: string): *void*

*Defined in [card-elements.ts:2948](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2948)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

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

### `Protected` inputControlContainerElement

• **get inputControlContainerElement**(): *HTMLElement*

*Defined in [card-elements.ts:2807](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2807)*

**Returns:** *HTMLElement*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

*Defined in [card-elements.ts:916](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L916)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Overrides [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

*Defined in [card-elements.ts:2952](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2952)*

**Returns:** *boolean*

___

### `Protected` isNullable

• **get isNullable**(): *boolean*

*Defined in [card-elements.ts:2799](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2799)*

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

### `Protected` renderedInputControlElement

• **get renderedInputControlElement**(): *HTMLElement*

*Defined in [card-elements.ts:2803](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2803)*

**Returns:** *HTMLElement*

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

___

###  value

• **get value**(): *string*

*Defined in [card-elements.ts:2872](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2872)*

**Returns:** *string*

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

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

*Defined in [card-elements.ts:2940](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2940)*

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

*Overrides [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

*Defined in [card-elements.ts:2893](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2893)*

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

*Overrides [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)*

*Defined in [card-elements.ts:2811](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2811)*

**Returns:** *HTMLElement*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Overrides [CardElement](cardelement.md).[parse](cardelement.md#parse)*

*Defined in [card-elements.ts:2925](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2925)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*

___

### `Protected` parseInputValue

▸ **parseInputValue**(`value`: string): *string*

*Defined in [card-elements.ts:2868](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2868)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *string*

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

### `Protected` resetValidationFailureCue

▸ **resetValidationFailureCue**(): *void*

*Defined in [card-elements.ts:2846](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2846)*

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

### `Protected` showValidationErrorMessage

▸ **showValidationErrorMessage**(): *void*

*Defined in [card-elements.ts:2858](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2858)*

**Returns:** *void*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [CardElement](cardelement.md).[toJSON](cardelement.md#tojson)*

*Defined in [card-elements.ts:2880](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2880)*

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

___

###  validateValue

▸ **validateValue**(): *boolean*

*Implementation of [IInput](../interfaces/iinput.md)*

*Defined in [card-elements.ts:2906](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2906)*

**Returns:** *boolean*

___

### `Protected` valueChanged

▸ **valueChanged**(): *void*

*Defined in [card-elements.ts:2836](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L2836)*

**Returns:** *void*
