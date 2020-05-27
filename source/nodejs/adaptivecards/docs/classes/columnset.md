[Adaptive Cards Javascript SDK](../README.md) › [ColumnSet](columnset.md)

# Class: ColumnSet

## Hierarchy

  ↳ [StylableCardElementContainer](stylablecardelementcontainer.md)

  ↳ **ColumnSet**

## Index

### Constructors

* [constructor](columnset.md#constructor)

### Properties

* [_parent](columnset.md#protected-optional-_parent)
* [_renderedElement](columnset.md#protected-optional-_renderedelement)
* [_selectAction](columnset.md#protected-optional-_selectaction)
* [allowVerticalOverflow](columnset.md#allowverticaloverflow)
* [customCssSelector](columnset.md#optional-customcssselector)
* [height](columnset.md#height)
* [horizontalAlignment](columnset.md#horizontalalignment)
* [id](columnset.md#optional-id)
* [maxVersion](columnset.md#maxversion)
* [minPixelHeight](columnset.md#optional-minpixelheight)
* [onPreProcessPropertyValue](columnset.md#optional-onpreprocesspropertyvalue)
* [separator](columnset.md#separator)
* [spacing](columnset.md#spacing)
* [bleedProperty](columnset.md#static-bleedproperty)
* [heightProperty](columnset.md#static-heightproperty)
* [horizontalAlignmentProperty](columnset.md#static-horizontalalignmentproperty)
* [idProperty](columnset.md#static-idproperty)
* [isVisibleProperty](columnset.md#static-isvisibleproperty)
* [langProperty](columnset.md#static-langproperty)
* [minHeightProperty](columnset.md#static-minheightproperty)
* [onRegisterCustomProperties](columnset.md#static-optional-onregistercustomproperties)
* [requiresProperty](columnset.md#static-requiresproperty)
* [selectActionProperty](columnset.md#static-selectactionproperty)
* [separatorProperty](columnset.md#static-separatorproperty)
* [spacingProperty](columnset.md#static-spacingproperty)
* [styleProperty](columnset.md#static-styleproperty)
* [typeNameProperty](columnset.md#static-typenameproperty)

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
* [requires](columnset.md#requires)
* [selectAction](columnset.md#selectaction)
* [separatorElement](columnset.md#separatorelement)
* [separatorOrientation](columnset.md#protected-separatororientation)
* [style](columnset.md#style)
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
* [getCustomProperty](columnset.md#getcustomproperty)
* [getDefaultPadding](columnset.md#protected-getdefaultpadding)
* [getEffectivePadding](columnset.md#geteffectivepadding)
* [getEffectiveStyle](columnset.md#geteffectivestyle)
* [getEffectiveStyleDefinition](columnset.md#geteffectivestyledefinition)
* [getElementById](columnset.md#getelementbyid)
* [getFirstVisibleRenderedItem](columnset.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](columnset.md#getforbiddenactiontypes)
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
* [getRootObject](columnset.md#getrootobject)
* [getSchema](columnset.md#getschema)
* [getSchemaKey](columnset.md#protected-getschemakey)
* [getValue](columnset.md#protected-getvalue)
* [hasAllDefaultValues](columnset.md#hasalldefaultvalues)
* [hasDefaultValue](columnset.md#hasdefaultvalue)
* [indexOf](columnset.md#indexof)
* [internalParse](columnset.md#protected-internalparse)
* [internalRender](columnset.md#protected-internalrender)
* [internalToJSON](columnset.md#protected-internaltojson)
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
* [isDisplayed](columnset.md#protected-isdisplayed)
* [isElementAllowed](columnset.md#protected-iselementallowed)
* [isFirstElement](columnset.md#isfirstelement)
* [isHiddenDueToOverflow](columnset.md#ishiddenduetooverflow)
* [isLastElement](columnset.md#islastelement)
* [isLeftMostElement](columnset.md#isleftmostelement)
* [isRightMostElement](columnset.md#isrightmostelement)
* [isTopElement](columnset.md#istopelement)
* [overrideInternalRender](columnset.md#protected-overrideinternalrender)
* [parse](columnset.md#parse)
* [populateSchema](columnset.md#protected-populateschema)
* [preProcessPropertyValue](columnset.md#preprocesspropertyvalue)
* [remove](columnset.md#remove)
* [removeItem](columnset.md#removeitem)
* [render](columnset.md#render)
* [resetDefaultValues](columnset.md#resetdefaultvalues)
* [setBleed](columnset.md#protected-setbleed)
* [setCustomProperty](columnset.md#setcustomproperty)
* [setPadding](columnset.md#protected-setpadding)
* [setParent](columnset.md#setparent)
* [setShouldFallback](columnset.md#setshouldfallback)
* [setValue](columnset.md#protected-setvalue)
* [shouldFallback](columnset.md#shouldfallback)
* [shouldSerialize](columnset.md#protected-shouldserialize)
* [toJSON](columnset.md#tojson)
* [truncateOverflow](columnset.md#protected-truncateoverflow)
* [undoOverflowTruncation](columnset.md#protected-undooverflowtruncation)
* [updateLayout](columnset.md#updatelayout)
* [validateProperties](columnset.md#validateproperties)

## Constructors

###  constructor

\+ **new ColumnSet**(): *[ColumnSet](columnset.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

**Returns:** *[ColumnSet](columnset.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

*Defined in [card-object.ts:61](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L61)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

*Defined in [card-object.ts:62](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L62)*

___

### `Protected` `Optional` _selectAction

• **_selectAction**? : *[Action](action.md)*

*Inherited from [CardElementContainer](cardelementcontainer.md).[_selectAction](cardelementcontainer.md#protected-optional-_selectaction)*

*Defined in [card-elements.ts:1747](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1747)*

___

###  allowVerticalOverflow

• **allowVerticalOverflow**: *boolean* = false

*Inherited from [CardElementContainer](cardelementcontainer.md).[allowVerticalOverflow](cardelementcontainer.md#allowverticaloverflow)*

*Defined in [card-elements.ts:1787](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1787)*

___

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

*Defined in [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L311)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

*Defined in [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L53)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)*

*Defined in [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L44)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

*Defined in [card-object.ts:50](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L50)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

*Defined in [serialization.ts:843](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L843)*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *undefined | number*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[minPixelHeight](stylablecardelementcontainer.md#optional-minpixelheight)*

*Defined in [card-elements.ts:4621](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4621)*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

*Defined in [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L64)*

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

*Defined in [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L50)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

*Defined in [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L47)*

___

### `Static` bleedProperty

▪ **bleedProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "bleed", false)

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[bleedProperty](stylablecardelementcontainer.md#static-bleedproperty)*

*Defined in [card-elements.ts:4597](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4597)*

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

*Defined in [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L24)*

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

*Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)*

*Defined in [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L32)*

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

*Defined in [card-object.ts:39](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L39)*

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

*Defined in [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L22)*

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

*Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-langproperty)*

*Defined in [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L21)*

___

### `Static` minHeightProperty

▪ **minHeightProperty**: *[PixelSizeProperty](pixelsizeproperty.md)‹›* = new PixelSizeProperty(Versions.v1_2, "minHeight")

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[minHeightProperty](stylablecardelementcontainer.md#static-minheightproperty)*

*Defined in [card-elements.ts:4598](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4598)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

*Defined in [serialization.ts:729](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L729)*

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities)

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

*Defined in [card-object.ts:40](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L40)*

___

### `Static` selectActionProperty

▪ **selectActionProperty**: *[ActionProperty](actionproperty.md)‹›* = new ActionProperty(Versions.v1_0, "selectAction", [ "Action.ShowCard" ])

*Inherited from [CardElementContainer](cardelementcontainer.md).[selectActionProperty](cardelementcontainer.md#static-selectactionproperty)*

*Defined in [card-elements.ts:1736](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1736)*

___

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

*Defined in [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L23)*

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

*Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-spacingproperty)*

*Defined in [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L37)*

___

### `Static` styleProperty

▪ **styleProperty**: *[ValueSetProperty](valuesetproperty.md)‹›* = new ValueSetProperty(
        Versions.v1_0,
        "style",
        [
            { value: Enums.ContainerStyle.Default },
            { value: Enums.ContainerStyle.Emphasis },
            { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Accent },
            { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Good },
            { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Attention },
            { targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Warning }
        ])

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[styleProperty](stylablecardelementcontainer.md#static-styleproperty)*

*Defined in [card-elements.ts:4586](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4586)*

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

*Defined in [card-object.ts:30](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L30)*

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

*Defined in [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L299)*

**Returns:** *boolean*

___

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[allowCustomStyle](stylablecardelementcontainer.md#protected-allowcustomstyle)*

*Defined in [card-elements.ts:4742](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4742)*

**Returns:** *boolean*

___

###  bleed

• **get bleed**(): *boolean*

*Defined in [card-elements.ts:5689](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5689)*

**Returns:** *boolean*

• **set bleed**(`value`: boolean): *void*

*Defined in [card-elements.ts:5693](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5693)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

*Defined in [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L307)*

**Returns:** *string*

___

### `Protected` hasExplicitStyle

• **get hasExplicitStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[hasExplicitStyle](stylablecardelementcontainer.md#protected-hasexplicitstyle)*

*Defined in [card-elements.ts:4738](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4738)*

**Returns:** *boolean*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Inherited from [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)*

*Defined in [card-elements.ts:580](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L580)*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

*Defined in [card-elements.ts:541](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L541)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

*Defined in [card-elements.ts:555](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L555)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

*Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)*

*Defined in [card-elements.ts:559](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L559)*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

*Defined in [card-elements.ts:576](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L576)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

*Defined in [card-elements.ts:568](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L568)*

**Returns:** *boolean*

___

### `Protected` isSelectable

• **get isSelectable**(): *boolean*

*Overrides [CardElementContainer](cardelementcontainer.md).[isSelectable](cardelementcontainer.md#protected-isselectable)*

*Defined in [card-elements.ts:5498](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5498)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

*Defined in [card-elements.ts:572](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L572)*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

*Defined in [card-elements.ts:77](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L77)*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

*Defined in [card-elements.ts:81](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L81)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

*Defined in [card-elements.ts:56](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L56)*

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

*Defined in [card-elements.ts:72](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L72)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  padding

• **get padding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

*Defined in [card-elements.ts:5697](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5697)*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

• **set padding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): *void*

*Defined in [card-elements.ts:5701](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5701)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)*

*Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)*

*Defined in [card-elements.ts:593](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L593)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

### `Protected` renderedActionCount

• **get renderedActionCount**(): *number*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[renderedActionCount](stylablecardelementcontainer.md#protected-renderedactioncount)*

*Defined in [card-elements.ts:4734](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4734)*

**Returns:** *number*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

*Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)*

*Defined in [card-object.ts:140](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L140)*

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

*Defined in [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L53)*

**Returns:** *HostCapabilities*

___

###  selectAction

• **get selectAction**(): *[Action](action.md) | undefined*

*Defined in [card-elements.ts:5705](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5705)*

**Returns:** *[Action](action.md) | undefined*

• **set selectAction**(`value`: [Action](action.md) | undefined): *void*

*Defined in [card-elements.ts:5709](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5709)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [Action](action.md) &#124; undefined |

**Returns:** *void*

___

###  separatorElement

• **get separatorElement**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)*

*Defined in [card-elements.ts:589](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L589)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

*Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

*Defined in [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L303)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

###  style

• **get style**(): *string | undefined*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)*

*Defined in [card-elements.ts:4601](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4601)*

**Returns:** *string | undefined*

• **set style**(`value`: string | undefined): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)*

*Defined in [card-elements.ts:4613](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4613)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

*Defined in [card-elements.ts:295](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L295)*

**Returns:** *boolean*

## Methods

###  addColumn

▸ **addColumn**(`column`: [Column](column.md)): *void*

*Defined in [card-elements.ts:5626](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5626)*

**Parameters:**

Name | Type |
------ | ------ |
`column` | [Column](column.md) |

**Returns:** *void*

___

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[adjustRenderedElementSize](stylablecardelementcontainer.md#protected-adjustrenderedelementsize)*

*Overrides [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

*Defined in [card-elements.ts:4625](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4625)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyBackground

▸ **applyBackground**(): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[applyBackground](stylablecardelementcontainer.md#protected-applybackground)*

*Defined in [card-elements.ts:4633](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4633)*

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[applyPadding](stylablecardelementcontainer.md#protected-applypadding)*

*Overrides [CardElementContainer](cardelementcontainer.md).[applyPadding](cardelementcontainer.md#protected-applypadding)*

*Defined in [card-elements.ts:4643](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4643)*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

*Defined in [card-elements.ts:321](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L321)*

**Returns:** *string | undefined*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

*Defined in [card-elements.ts:205](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L205)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

*Defined in [card-elements.ts:400](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L400)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

*Overrides [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

*Defined in [card-elements.ts:5675](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5675)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

*Defined in [card-elements.ts:396](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L396)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(): *[Input](input.md)[]*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getAllInputs](cardelementcontainer.md#getallinputs)*

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

*Defined in [card-elements.ts:1871](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1871)*

**Returns:** *[Input](input.md)[]*

___

### `Protected` getBleed

▸ **getBleed**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getBleed](stylablecardelementcontainer.md#protected-getbleed)*

*Defined in [card-elements.ts:4726](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4726)*

**Returns:** *boolean*

___

###  getColumnAt

▸ **getColumnAt**(`index`: number): *[Column](column.md)*

*Defined in [card-elements.ts:5591](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5591)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Column](column.md)*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

*Defined in [serialization.ts:922](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L922)*

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

*Defined in [card-elements.ts:4713](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4713)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)*

*Defined in [card-elements.ts:535](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L535)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getEffectiveStyle](stylablecardelementcontainer.md#geteffectivestyle)*

*Overrides [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)*

*Defined in [card-elements.ts:4777](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4777)*

**Returns:** *string*

___

###  getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)*

*Defined in [card-elements.ts:337](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L337)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getElementById](cardelementcontainer.md#getelementbyid)*

*Overrides [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)*

*Defined in [card-elements.ts:1891](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1891)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *[CardElement](cardelement.md) | undefined*

*Overrides [CardElementContainer](cardelementcontainer.md).[getFirstVisibleRenderedItem](cardelementcontainer.md#abstract-getfirstvisiblerendereditem)*

*Defined in [card-elements.ts:5573](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5573)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *[ActionType](../README.md#actiontype)[]*

*Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)*

*Defined in [card-elements.ts:341](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L341)*

**Returns:** *[ActionType](../README.md#actiontype)[]*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasBackground](stylablecardelementcontainer.md#protected-gethasbackground)*

*Overrides [CardElement](cardelement.md).[getHasBackground](cardelement.md#protected-gethasbackground)*

*Defined in [card-elements.ts:4695](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4695)*

**Returns:** *boolean*

___

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasExpandedAction](stylablecardelementcontainer.md#protected-gethasexpandedaction)*

*Defined in [card-elements.ts:4722](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4722)*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)*

*Defined in [card-elements.ts:345](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L345)*

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

*Defined in [card-elements.ts:5595](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5595)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[CardElement](cardelement.md)*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemCount](cardelementcontainer.md#abstract-getitemcount)*

*Defined in [card-elements.ts:5569](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5569)*

**Returns:** *number*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Overrides [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

*Defined in [card-elements.ts:5599](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5599)*

**Returns:** *string*

___

###  getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *[CardElement](cardelement.md) | undefined*

*Overrides [CardElementContainer](cardelementcontainer.md).[getLastVisibleRenderedItem](cardelementcontainer.md#abstract-getlastvisiblerendereditem)*

*Defined in [card-elements.ts:5582](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5582)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)*

*Defined in [card-elements.ts:283](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L283)*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)*

*Defined in [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L505)*

**Returns:** *[Container](container.md) | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getResourceInformation](cardelementcontainer.md#getresourceinformation)*

*Overrides [CardElement](cardelement.md).[getResourceInformation](cardelement.md#getresourceinformation)*

*Defined in [card-elements.ts:1881](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1881)*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)*

*Defined in [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L501)*

**Returns:** *[CardElement](cardelement.md)*

___

###  getRootObject

▸ **getRootObject**(): *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)*

*Defined in [card-object.ts:100](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L100)*

**Returns:** *[CardObject](cardobject.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

*Defined in [serialization.ts:926](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L926)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

*Defined in [card-object.ts:45](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L45)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

*Defined in [serialization.ts:776](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L776)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

*Defined in [serialization.ts:887](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L887)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

*Defined in [serialization.ts:883](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L883)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): *number*

*Overrides [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

*Defined in [card-elements.ts:5655](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5655)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

___

### `Protected` internalParse

▸ **internalParse**(`source`: any, `context`: [SerializationContext](serializationcontext.md)): *void*

*Overrides [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

*Defined in [card-elements.ts:5502](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5502)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

*Defined in [card-elements.ts:5418](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5418)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): *void*

*Overrides [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

*Defined in [card-elements.ts:5521](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5521)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[internalValidateProperties](stylablecardelementcontainer.md#internalvalidateproperties)*

*Defined in [card-elements.ts:5603](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5603)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)*

*Defined in [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L469)*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)*

*Defined in [card-elements.ts:457](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L457)*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)*

*Defined in [card-elements.ts:461](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L461)*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)*

*Defined in [card-elements.ts:465](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L465)*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[isBleeding](stylablecardelementcontainer.md#isbleeding)*

*Overrides [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)*

*Defined in [card-elements.ts:4746](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4746)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Overrides [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

*Defined in [card-elements.ts:5553](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5553)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Overrides [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

*Defined in [card-elements.ts:5537](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5537)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)*

*Defined in [card-elements.ts:5671](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5671)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)*

*Defined in [card-elements.ts:443](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L443)*

**Returns:** *boolean*

___

### `Protected` isDisplayed

▸ **isDisplayed**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDisplayed](cardelement.md#protected-isdisplayed)*

*Defined in [card-elements.ts:229](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L229)*

**Returns:** *boolean*

___

### `Protected` isElementAllowed

▸ **isElementAllowed**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElementContainer](cardelementcontainer.md).[isElementAllowed](cardelementcontainer.md#protected-iselementallowed)*

*Defined in [card-elements.ts:1751](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1751)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

*Defined in [card-elements.ts:5527](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5527)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)*

*Defined in [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L497)*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)*

*Defined in [card-elements.ts:453](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L453)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)*

*Defined in [card-elements.ts:5659](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5659)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)*

*Defined in [card-elements.ts:5663](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5663)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)*

*Defined in [card-elements.ts:5667](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5667)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)*

*Defined in [card-elements.ts:235](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L235)*

**Returns:** *HTMLElement | undefined*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [CardElement](cardelement.md).[parse](cardelement.md#parse)*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

*Defined in [card-elements.ts:313](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L313)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [CardElementContainer](cardelementcontainer.md).[populateSchema](cardelementcontainer.md#protected-populateschema)*

*Overrides [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

*Defined in [card-elements.ts:1738](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1738)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): *any*

*Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)*

*Defined in [card-object.ts:70](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L70)*

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

*Defined in [card-elements.ts:404](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L404)*

**Returns:** *boolean*

___

###  removeItem

▸ **removeItem**(`item`: [CardElement](cardelement.md)): *boolean*

*Overrides [CardElementContainer](cardelementcontainer.md).[removeItem](cardelementcontainer.md#abstract-removeitem)*

*Defined in [card-elements.ts:5637](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5637)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement | undefined*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[render](stylablecardelementcontainer.md#render)*

*Overrides [CardElementContainer](cardelementcontainer.md).[render](cardelementcontainer.md#render)*

*Defined in [card-elements.ts:4767](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4767)*

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

*Defined in [serialization.ts:901](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L901)*

**Returns:** *void*

___

### `Protected` setBleed

▸ **setBleed**(`value`: boolean): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[setBleed](stylablecardelementcontainer.md#protected-setbleed)*

*Defined in [card-elements.ts:4730](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L4730)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

*Defined in [serialization.ts:911](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L911)*

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

*Defined in [card-elements.ts:287](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L287)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): *void*

*Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)*

*Defined in [card-object.ts:88](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L88)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)*

*Defined in [card-object.ts:92](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L92)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

*Defined in [serialization.ts:780](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L780)*

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

*Defined in [card-object.ts:96](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L96)*

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [SerializationContext](serializationcontext.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[shouldSerialize](cardelement.md#protected-shouldserialize)*

*Overrides [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

*Defined in [card-elements.ts:291](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L291)*

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

*Defined in [card-elements.ts:317](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L317)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Overrides [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

*Defined in [card-elements.ts:5484](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5484)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Overrides [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

*Defined in [card-elements.ts:5492](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L5492)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Inherited from [CardElementContainer](cardelementcontainer.md).[updateLayout](cardelementcontainer.md#updatelayout)*

*Overrides [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)*

*Defined in [card-elements.ts:1861](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L1861)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | true |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

*Defined in [card-object.ts:128](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-object.ts#L128)*

**Returns:** *[ValidationResults](validationresults.md)*
