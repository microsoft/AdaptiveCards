[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / Container

# Class: Container

[adaptivecards](../modules/adaptivecards.md).Container

## Hierarchy

* [*StylableCardElementContainer*](card_elements.stylablecardelementcontainer.md)

  ↳ **Container**

## Table of contents

### Constructors

- [constructor](adaptivecards.container.md#constructor)

### Properties

- [\_parent](adaptivecards.container.md#_parent)
- [\_renderedElement](adaptivecards.container.md#_renderedelement)
- [\_selectAction](adaptivecards.container.md#_selectaction)
- [allowVerticalOverflow](adaptivecards.container.md#allowverticaloverflow)
- [customCssSelector](adaptivecards.container.md#customcssselector)
- [height](adaptivecards.container.md#height)
- [horizontalAlignment](adaptivecards.container.md#horizontalalignment)
- [id](adaptivecards.container.md#id)
- [maxVersion](adaptivecards.container.md#maxversion)
- [minPixelHeight](adaptivecards.container.md#minpixelheight)
- [onPreProcessPropertyValue](adaptivecards.container.md#onpreprocesspropertyvalue)
- [rtl](adaptivecards.container.md#rtl)
- [separator](adaptivecards.container.md#separator)
- [spacing](adaptivecards.container.md#spacing)
- [verticalContentAlignment](adaptivecards.container.md#verticalcontentalignment)
- [backgroundImageProperty](adaptivecards.container.md#backgroundimageproperty)
- [bleedProperty](adaptivecards.container.md#bleedproperty)
- [defaultMaxVersion](adaptivecards.container.md#defaultmaxversion)
- [heightProperty](adaptivecards.container.md#heightproperty)
- [horizontalAlignmentProperty](adaptivecards.container.md#horizontalalignmentproperty)
- [idProperty](adaptivecards.container.md#idproperty)
- [isVisibleProperty](adaptivecards.container.md#isvisibleproperty)
- [langProperty](adaptivecards.container.md#langproperty)
- [minHeightProperty](adaptivecards.container.md#minheightproperty)
- [onRegisterCustomProperties](adaptivecards.container.md#onregistercustomproperties)
- [requiresProperty](adaptivecards.container.md#requiresproperty)
- [rtlProperty](adaptivecards.container.md#rtlproperty)
- [selectActionProperty](adaptivecards.container.md#selectactionproperty)
- [separatorProperty](adaptivecards.container.md#separatorproperty)
- [spacingProperty](adaptivecards.container.md#spacingproperty)
- [styleProperty](adaptivecards.container.md#styleproperty)
- [typeNameProperty](adaptivecards.container.md#typenameproperty)
- [verticalContentAlignmentProperty](adaptivecards.container.md#verticalcontentalignmentproperty)

### Accessors

- [allowCustomPadding](adaptivecards.container.md#allowcustompadding)
- [allowCustomStyle](adaptivecards.container.md#allowcustomstyle)
- [backgroundImage](adaptivecards.container.md#backgroundimage)
- [bleed](adaptivecards.container.md#bleed)
- [defaultStyle](adaptivecards.container.md#defaultstyle)
- [hasExplicitStyle](adaptivecards.container.md#hasexplicitstyle)
- [hasVisibleSeparator](adaptivecards.container.md#hasvisibleseparator)
- [hostConfig](adaptivecards.container.md#hostconfig)
- [index](adaptivecards.container.md#index)
- [isInline](adaptivecards.container.md#isinline)
- [isInteractive](adaptivecards.container.md#isinteractive)
- [isSelectable](adaptivecards.container.md#isselectable)
- [isStandalone](adaptivecards.container.md#isstandalone)
- [isVisible](adaptivecards.container.md#isvisible)
- [lang](adaptivecards.container.md#lang)
- [padding](adaptivecards.container.md#padding)
- [parent](adaptivecards.container.md#parent)
- [renderedActionCount](adaptivecards.container.md#renderedactioncount)
- [renderedElement](adaptivecards.container.md#renderedelement)
- [requires](adaptivecards.container.md#requires)
- [selectAction](adaptivecards.container.md#selectaction)
- [separatorElement](adaptivecards.container.md#separatorelement)
- [separatorOrientation](adaptivecards.container.md#separatororientation)
- [style](adaptivecards.container.md#style)
- [useDefaultSizing](adaptivecards.container.md#usedefaultsizing)

### Methods

- [addItem](adaptivecards.container.md#additem)
- [adjustRenderedElementSize](adaptivecards.container.md#adjustrenderedelementsize)
- [applyBackground](adaptivecards.container.md#applybackground)
- [applyPadding](adaptivecards.container.md#applypadding)
- [asString](adaptivecards.container.md#asstring)
- [clear](adaptivecards.container.md#clear)
- [createPlaceholderElement](adaptivecards.container.md#createplaceholderelement)
- [getActionAt](adaptivecards.container.md#getactionat)
- [getActionById](adaptivecards.container.md#getactionbyid)
- [getActionCount](adaptivecards.container.md#getactioncount)
- [getAllInputs](adaptivecards.container.md#getallinputs)
- [getBleed](adaptivecards.container.md#getbleed)
- [getCustomProperty](adaptivecards.container.md#getcustomproperty)
- [getDefaultPadding](adaptivecards.container.md#getdefaultpadding)
- [getDefaultSerializationContext](adaptivecards.container.md#getdefaultserializationcontext)
- [getEffectivePadding](adaptivecards.container.md#geteffectivepadding)
- [getEffectiveStyle](adaptivecards.container.md#geteffectivestyle)
- [getEffectiveStyleDefinition](adaptivecards.container.md#geteffectivestyledefinition)
- [getElementById](adaptivecards.container.md#getelementbyid)
- [getFirstVisibleRenderedItem](adaptivecards.container.md#getfirstvisiblerendereditem)
- [getForbiddenActionTypes](adaptivecards.container.md#getforbiddenactiontypes)
- [getHasBackground](adaptivecards.container.md#gethasbackground)
- [getHasExpandedAction](adaptivecards.container.md#gethasexpandedaction)
- [getImmediateSurroundingPadding](adaptivecards.container.md#getimmediatesurroundingpadding)
- [getItemAt](adaptivecards.container.md#getitemat)
- [getItemCount](adaptivecards.container.md#getitemcount)
- [getItemsCollectionPropertyName](adaptivecards.container.md#getitemscollectionpropertyname)
- [getJsonTypeName](adaptivecards.container.md#getjsontypename)
- [getLastVisibleRenderedItem](adaptivecards.container.md#getlastvisiblerendereditem)
- [getPadding](adaptivecards.container.md#getpadding)
- [getParentContainer](adaptivecards.container.md#getparentcontainer)
- [getResourceInformation](adaptivecards.container.md#getresourceinformation)
- [getRootElement](adaptivecards.container.md#getrootelement)
- [getRootObject](adaptivecards.container.md#getrootobject)
- [getSchema](adaptivecards.container.md#getschema)
- [getSchemaKey](adaptivecards.container.md#getschemakey)
- [getValue](adaptivecards.container.md#getvalue)
- [hasAllDefaultValues](adaptivecards.container.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.container.md#hasdefaultvalue)
- [indexOf](adaptivecards.container.md#indexof)
- [insertItemAfter](adaptivecards.container.md#insertitemafter)
- [insertItemBefore](adaptivecards.container.md#insertitembefore)
- [internalParse](adaptivecards.container.md#internalparse)
- [internalRender](adaptivecards.container.md#internalrender)
- [internalToJSON](adaptivecards.container.md#internaltojson)
- [internalValidateProperties](adaptivecards.container.md#internalvalidateproperties)
- [isAtTheVeryBottom](adaptivecards.container.md#isattheverybottom)
- [isAtTheVeryLeft](adaptivecards.container.md#isattheveryleft)
- [isAtTheVeryRight](adaptivecards.container.md#isattheveryright)
- [isAtTheVeryTop](adaptivecards.container.md#isattheverytop)
- [isBleeding](adaptivecards.container.md#isbleeding)
- [isBleedingAtBottom](adaptivecards.container.md#isbleedingatbottom)
- [isBleedingAtTop](adaptivecards.container.md#isbleedingattop)
- [isBottomElement](adaptivecards.container.md#isbottomelement)
- [isDesignMode](adaptivecards.container.md#isdesignmode)
- [isDisplayed](adaptivecards.container.md#isdisplayed)
- [isElementAllowed](adaptivecards.container.md#iselementallowed)
- [isFirstElement](adaptivecards.container.md#isfirstelement)
- [isHiddenDueToOverflow](adaptivecards.container.md#ishiddenduetooverflow)
- [isLastElement](adaptivecards.container.md#islastelement)
- [isLeftMostElement](adaptivecards.container.md#isleftmostelement)
- [isRightMostElement](adaptivecards.container.md#isrightmostelement)
- [isRtl](adaptivecards.container.md#isrtl)
- [isTopElement](adaptivecards.container.md#istopelement)
- [overrideInternalRender](adaptivecards.container.md#overrideinternalrender)
- [parse](adaptivecards.container.md#parse)
- [populateSchema](adaptivecards.container.md#populateschema)
- [preProcessPropertyValue](adaptivecards.container.md#preprocesspropertyvalue)
- [remove](adaptivecards.container.md#remove)
- [removeItem](adaptivecards.container.md#removeitem)
- [render](adaptivecards.container.md#render)
- [resetDefaultValues](adaptivecards.container.md#resetdefaultvalues)
- [setBleed](adaptivecards.container.md#setbleed)
- [setCustomProperty](adaptivecards.container.md#setcustomproperty)
- [setPadding](adaptivecards.container.md#setpadding)
- [setParent](adaptivecards.container.md#setparent)
- [setShouldFallback](adaptivecards.container.md#setshouldfallback)
- [setValue](adaptivecards.container.md#setvalue)
- [shouldFallback](adaptivecards.container.md#shouldfallback)
- [shouldSerialize](adaptivecards.container.md#shouldserialize)
- [supportsExcplitiHeight](adaptivecards.container.md#supportsexcplitiheight)
- [toJSON](adaptivecards.container.md#tojson)
- [truncateOverflow](adaptivecards.container.md#truncateoverflow)
- [undoOverflowTruncation](adaptivecards.container.md#undooverflowtruncation)
- [updateLayout](adaptivecards.container.md#updatelayout)
- [validateProperties](adaptivecards.container.md#validateproperties)

## Constructors

### constructor

\+ **new Container**(): [*Container*](card_elements.container.md)

**Returns:** [*Container*](card_elements.container.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[_parent](card_elements.stylablecardelementcontainer.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[_renderedElement](card_elements.stylablecardelementcontainer.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### \_selectAction

• `Protected` `Optional` **\_selectAction**: *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[_selectAction](card_elements.stylablecardelementcontainer.md#_selectaction)

Defined in: [card-elements.ts:1851](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1851)

___

### allowVerticalOverflow

• **allowVerticalOverflow**: *boolean*= false

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[allowVerticalOverflow](card_elements.stylablecardelementcontainer.md#allowverticaloverflow)

Defined in: [card-elements.ts:1891](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1891)

___

### customCssSelector

• `Optional` **customCssSelector**: *undefined* \| *string*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[customCssSelector](card_elements.stylablecardelementcontainer.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

___

### height

• **height**: [*CardElementHeight*](../modules/card_elements.md#cardelementheight)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[height](card_elements.stylablecardelementcontainer.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

___

### horizontalAlignment

• **horizontalAlignment**: [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[horizontalAlignment](card_elements.stylablecardelementcontainer.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[id](card_elements.stylablecardelementcontainer.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[maxVersion](card_elements.stylablecardelementcontainer.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### minPixelHeight

• `Optional` **minPixelHeight**: *undefined* \| *number*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[minPixelHeight](card_elements.stylablecardelementcontainer.md#minpixelheight)

Defined in: [card-elements.ts:5068](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5068)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[onPreProcessPropertyValue](card_elements.stylablecardelementcontainer.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### rtl

• `Optional` **rtl**: *undefined* \| *boolean*

Defined in: [card-elements.ts:5334](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5334)

___

### separator

• **separator**: *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[separator](card_elements.stylablecardelementcontainer.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

___

### spacing

• **spacing**: [*Spacing*](../enums/enums.spacing.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[spacing](card_elements.stylablecardelementcontainer.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

___

### verticalContentAlignment

• **verticalContentAlignment**: [*VerticalAlignment*](../enums/enums.verticalalignment.md)

Defined in: [card-elements.ts:5331](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5331)

___

### backgroundImageProperty

▪ `Readonly` `Static` **backgroundImageProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Defined in: [card-elements.ts:5318](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5318)

___

### bleedProperty

▪ `Readonly` `Static` **bleedProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[bleedProperty](card_elements.stylablecardelementcontainer.md#bleedproperty)

Defined in: [card-elements.ts:5044](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5044)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[defaultMaxVersion](card_elements.stylablecardelementcontainer.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[heightProperty](card_elements.stylablecardelementcontainer.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

___

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)\>

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[horizontalAlignmentProperty](card_elements.stylablecardelementcontainer.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[idProperty](card_elements.stylablecardelementcontainer.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[isVisibleProperty](card_elements.stylablecardelementcontainer.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

___

### langProperty

▪ `Readonly` `Static` **langProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[langProperty](card_elements.stylablecardelementcontainer.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

___

### minHeightProperty

▪ `Readonly` `Static` **minHeightProperty**: [*PixelSizeProperty*](serialization.pixelsizeproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[minHeightProperty](card_elements.stylablecardelementcontainer.md#minheightproperty)

Defined in: [card-elements.ts:5045](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5045)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[onRegisterCustomProperties](card_elements.stylablecardelementcontainer.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[requiresProperty](card_elements.stylablecardelementcontainer.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### rtlProperty

▪ `Readonly` `Static` **rtlProperty**: [*BoolProperty*](serialization.boolproperty.md)

Defined in: [card-elements.ts:5323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5323)

___

### selectActionProperty

▪ `Readonly` `Static` **selectActionProperty**: [*ActionProperty*](card_elements.actionproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[selectActionProperty](card_elements.stylablecardelementcontainer.md#selectactionproperty)

Defined in: [card-elements.ts:1840](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1840)

___

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[separatorProperty](card_elements.stylablecardelementcontainer.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

___

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*Spacing*](../enums/enums.spacing.md)\>

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[spacingProperty](card_elements.stylablecardelementcontainer.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

___

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[styleProperty](card_elements.stylablecardelementcontainer.md#styleproperty)

Defined in: [card-elements.ts:5033](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5033)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[typeNameProperty](card_elements.stylablecardelementcontainer.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

___

### verticalContentAlignmentProperty

▪ `Readonly` `Static` **verticalContentAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*VerticalAlignment*](../enums/enums.verticalalignment.md)\>

Defined in: [card-elements.ts:5322](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5322)

## Accessors

### allowCustomPadding

• `Protected`get **allowCustomPadding**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:315](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L315)

___

### allowCustomStyle

• `Protected`get **allowCustomStyle**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5191](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5191)

___

### backgroundImage

• get **backgroundImage**(): [*BackgroundImage*](card_elements.backgroundimage.md)

**Returns:** [*BackgroundImage*](card_elements.backgroundimage.md)

Defined in: [card-elements.ts:5326](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5326)

___

### bleed

• get **bleed**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5705](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5705)

• set **bleed**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Defined in: [card-elements.ts:5709](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5709)

___

### defaultStyle

• `Protected`get **defaultStyle**(): *string*

**Returns:** *string*

Defined in: [card-elements.ts:323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L323)

___

### hasExplicitStyle

• `Protected`get **hasExplicitStyle**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5187](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5187)

___

### hasVisibleSeparator

• get **hasVisibleSeparator**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:596](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L596)

___

### hostConfig

• get **hostConfig**(): [*HostConfig*](host_config.hostconfig.md)

**Returns:** [*HostConfig*](host_config.hostconfig.md)

Defined in: [card-elements.ts:557](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L557)

• set **hostConfig**(`value`: [*HostConfig*](host_config.hostconfig.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | [*HostConfig*](host_config.hostconfig.md) |

**Returns:** *void*

Defined in: [card-elements.ts:571](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L571)

___

### index

• get **index**(): *number*

**Returns:** *number*

Defined in: [card-elements.ts:575](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L575)

___

### isInline

• get **isInline**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L592)

___

### isInteractive

• get **isInteractive**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:584](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L584)

___

### isSelectable

• `Protected`get **isSelectable**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5528](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5528)

___

### isStandalone

• get **isStandalone**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:588](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L588)

___

### isVisible

• get **isVisible**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:77](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L77)

• set **isVisible**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Defined in: [card-elements.ts:81](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L81)

___

### lang

• get **lang**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [card-elements.ts:56](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L56)

• set **lang**(`value`: *undefined* \| *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| *string* |

**Returns:** *void*

Defined in: [card-elements.ts:72](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L72)

___

### padding

• get **padding**(): *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

Defined in: [card-elements.ts:5689](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5689)

• set **padding**(`value`: *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md) |

**Returns:** *void*

Defined in: [card-elements.ts:5693](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5693)

___

### parent

• get **parent**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Defined in: [card-elements.ts:609](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L609)

___

### renderedActionCount

• `Protected`get **renderedActionCount**(): *number*

**Returns:** *number*

Defined in: [card-elements.ts:5183](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5183)

___

### renderedElement

• get **renderedElement**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Defined in: [card-object.ts:143](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L143)

___

### requires

• get **requires**(): [*HostCapabilities*](host_capabilities.hostcapabilities.md)

**Returns:** [*HostCapabilities*](host_capabilities.hostcapabilities.md)

Defined in: [card-object.ts:56](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L56)

___

### selectAction

• get **selectAction**(): *undefined* \| [*Action*](card_elements.action.md)

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Defined in: [card-elements.ts:5697](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5697)

• set **selectAction**(`value`: *undefined* \| [*Action*](card_elements.action.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*Action*](card_elements.action.md) |

**Returns:** *void*

Defined in: [card-elements.ts:5701](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5701)

___

### separatorElement

• get **separatorElement**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Defined in: [card-elements.ts:605](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L605)

___

### separatorOrientation

• `Protected`get **separatorOrientation**(): [*Orientation*](../enums/enums.orientation.md)

**Returns:** [*Orientation*](../enums/enums.orientation.md)

Defined in: [card-elements.ts:319](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L319)

___

### style

• get **style**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [card-elements.ts:5048](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5048)

• set **style**(`value`: *undefined* \| *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| *string* |

**Returns:** *void*

Defined in: [card-elements.ts:5060](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5060)

___

### useDefaultSizing

• `Protected`get **useDefaultSizing**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L311)

## Methods

### addItem

▸ **addItem**(`item`: [*CardElement*](card_elements.cardelement.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *void*

Defined in: [card-elements.ts:5619](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5619)

___

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5072](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5072)

___

### applyBackground

▸ `Protected`**applyBackground**(): *void*

**Returns:** *void*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5373](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5373)

___

### applyPadding

▸ `Protected`**applyPadding**(): *void*

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5092](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5092)

___

### asString

▸ **asString**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L333)

___

### clear

▸ **clear**(): *void*

**Returns:** *void*

Defined in: [card-elements.ts:5647](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5647)

___

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

___

### getActionAt

▸ **getActionAt**(`index`: *number*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L412)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5667](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5667)

___

### getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:408](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L408)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1976](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1976)

___

### getBleed

▸ `Protected`**getBleed**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5175](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5175)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5162](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5162)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

___

### getEffectivePadding

▸ **getEffectivePadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

___

### getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5226](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5226)

___

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

___

### getElementById

▸ **getElementById**(`id`: *string*): *undefined* \| [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1996](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1996)

___

### getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5540](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5540)

___

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [*ActionType*](../modules/card_elements.md#actiontype)[]

**Returns:** [*ActionType*](../modules/card_elements.md#actiontype)[]

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

___

### getHasBackground

▸ `Protected`**getHasBackground**(): *boolean*

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5499](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5499)

___

### getHasExpandedAction

▸ `Protected`**getHasExpandedAction**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5171](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5171)

___

### getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [*PaddingDefinition*](shared.paddingdefinition.md), `processTop?`: *boolean*, `processRight?`: *boolean*, `processBottom?`: *boolean*, `processLeft?`: *boolean*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`result` | [*PaddingDefinition*](shared.paddingdefinition.md) | - |
`processTop` | *boolean* | true |
`processRight` | *boolean* | true |
`processBottom` | *boolean* | true |
`processLeft` | *boolean* | true |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

___

### getItemAt

▸ **getItemAt**(`index`: *number*): [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*CardElement*](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5536](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5536)

___

### getItemCount

▸ **getItemCount**(): *number*

**Returns:** *number*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5532](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5532)

___

### getItemsCollectionPropertyName

▸ `Protected`**getItemsCollectionPropertyName**(): *string*

**Returns:** *string*

Defined in: [card-elements.ts:5369](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5369)

___

### getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5564](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5564)

___

### getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5552](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5552)

___

### getPadding

▸ `Protected`**getPadding**(): *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

___

### getParentContainer

▸ **getParentContainer**(): *undefined* \| [*Container*](card_elements.container.md)

**Returns:** *undefined* \| [*Container*](card_elements.container.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5652](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5652)

___

### getRootElement

▸ **getRootElement**(): [*CardElement*](card_elements.cardelement.md)

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### indexOf

▸ **indexOf**(`cardElement`: [*CardElement*](card_elements.cardelement.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`cardElement` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *number*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5615](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5615)

___

### insertItemAfter

▸ **insertItemAfter**(`item`: [*CardElement*](card_elements.cardelement.md), `insertAfter`: [*CardElement*](card_elements.cardelement.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |
`insertAfter` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *void*

Defined in: [card-elements.ts:5627](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5627)

___

### insertItemBefore

▸ **insertItemBefore**(`item`: [*CardElement*](card_elements.cardelement.md), `insertBefore`: [*CardElement*](card_elements.cardelement.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |
`insertBefore` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *void*

Defined in: [card-elements.ts:5623](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5623)

___

### internalParse

▸ `Protected`**internalParse**(`source`: *any*, `context`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *any* |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5503](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5503)

___

### internalRender

▸ `Protected`**internalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5381](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5381)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5522](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5522)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5199](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5199)

___

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

___

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

___

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

___

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

___

### isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5195](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5195)

___

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5609](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5609)

___

### isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5603](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5603)

___

### isBottomElement

▸ **isBottomElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

___

### isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

___

### isDisplayed

▸ `Protected`**isDisplayed**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

___

### isElementAllowed

▸ `Protected`**isElementAllowed**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1855](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1855)

___

### isFirstElement

▸ **isFirstElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5568](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5568)

___

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

___

### isLastElement

▸ **isLastElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5580](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5580)

___

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

___

### isRightMostElement

▸ **isRightMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

___

### isRtl

▸ **isRtl**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5592)

___

### isTopElement

▸ **isTopElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

___

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:251](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L251)

___

### parse

▸ **parse**(`source`: *any*, `context?`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *any* |
`context?` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1842](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1842)

___

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `propertyValue?`: *any*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`propertyValue?` | *any* |

**Returns:** *any*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

___

### removeItem

▸ **removeItem**(`item`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5631](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5631)

___

### render

▸ **render**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5216](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5216)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### setBleed

▸ `Protected`**setBleed**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5179](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5179)

___

### setCustomProperty

▸ **setCustomProperty**(`name`: *string*, `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`value` | *any* |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setPadding

▸ `Protected`**setPadding**(`value`: *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md) |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:95](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L95)

___

### setValue

▸ `Protected`**setValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`value` | *any* |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

___

### supportsExcplitiHeight

▸ `Protected`**supportsExcplitiHeight**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5365](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5365)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

___

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: *number*): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`maxHeight` | *number* |

**Returns:** *boolean*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5454](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5454)

___

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): *void*

**Returns:** *void*

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5493)

___

### updateLayout

▸ **updateLayout**(`processChildren?`: *boolean*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processChildren` | *boolean* | true |

**Returns:** *void*

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1966](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1966)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
