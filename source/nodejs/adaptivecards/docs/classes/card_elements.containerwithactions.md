[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / ContainerWithActions

# Class: ContainerWithActions

[card-elements](../modules/card_elements.md).ContainerWithActions

## Hierarchy

* [*Container*](card_elements.container.md)

  ↳ **ContainerWithActions**

  ↳↳ [*AdaptiveCard*](card_elements.adaptivecard.md)

  ↳↳ [*AdaptiveCard*](adaptivecards.adaptivecard.md)

## Table of contents

### Constructors

- [constructor](card_elements.containerwithactions.md#constructor)

### Properties

- [\_parent](card_elements.containerwithactions.md#_parent)
- [\_renderedElement](card_elements.containerwithactions.md#_renderedelement)
- [\_selectAction](card_elements.containerwithactions.md#_selectaction)
- [allowVerticalOverflow](card_elements.containerwithactions.md#allowverticaloverflow)
- [customCssSelector](card_elements.containerwithactions.md#customcssselector)
- [height](card_elements.containerwithactions.md#height)
- [horizontalAlignment](card_elements.containerwithactions.md#horizontalalignment)
- [id](card_elements.containerwithactions.md#id)
- [maxVersion](card_elements.containerwithactions.md#maxversion)
- [minPixelHeight](card_elements.containerwithactions.md#minpixelheight)
- [onPreProcessPropertyValue](card_elements.containerwithactions.md#onpreprocesspropertyvalue)
- [rtl](card_elements.containerwithactions.md#rtl)
- [separator](card_elements.containerwithactions.md#separator)
- [spacing](card_elements.containerwithactions.md#spacing)
- [verticalContentAlignment](card_elements.containerwithactions.md#verticalcontentalignment)
- [backgroundImageProperty](card_elements.containerwithactions.md#backgroundimageproperty)
- [bleedProperty](card_elements.containerwithactions.md#bleedproperty)
- [defaultMaxVersion](card_elements.containerwithactions.md#defaultmaxversion)
- [heightProperty](card_elements.containerwithactions.md#heightproperty)
- [horizontalAlignmentProperty](card_elements.containerwithactions.md#horizontalalignmentproperty)
- [idProperty](card_elements.containerwithactions.md#idproperty)
- [isVisibleProperty](card_elements.containerwithactions.md#isvisibleproperty)
- [langProperty](card_elements.containerwithactions.md#langproperty)
- [minHeightProperty](card_elements.containerwithactions.md#minheightproperty)
- [onRegisterCustomProperties](card_elements.containerwithactions.md#onregistercustomproperties)
- [requiresProperty](card_elements.containerwithactions.md#requiresproperty)
- [rtlProperty](card_elements.containerwithactions.md#rtlproperty)
- [selectActionProperty](card_elements.containerwithactions.md#selectactionproperty)
- [separatorProperty](card_elements.containerwithactions.md#separatorproperty)
- [spacingProperty](card_elements.containerwithactions.md#spacingproperty)
- [styleProperty](card_elements.containerwithactions.md#styleproperty)
- [typeNameProperty](card_elements.containerwithactions.md#typenameproperty)
- [verticalContentAlignmentProperty](card_elements.containerwithactions.md#verticalcontentalignmentproperty)

### Accessors

- [allowCustomPadding](card_elements.containerwithactions.md#allowcustompadding)
- [allowCustomStyle](card_elements.containerwithactions.md#allowcustomstyle)
- [backgroundImage](card_elements.containerwithactions.md#backgroundimage)
- [bleed](card_elements.containerwithactions.md#bleed)
- [defaultStyle](card_elements.containerwithactions.md#defaultstyle)
- [hasExplicitStyle](card_elements.containerwithactions.md#hasexplicitstyle)
- [hasVisibleSeparator](card_elements.containerwithactions.md#hasvisibleseparator)
- [hostConfig](card_elements.containerwithactions.md#hostconfig)
- [index](card_elements.containerwithactions.md#index)
- [isInline](card_elements.containerwithactions.md#isinline)
- [isInteractive](card_elements.containerwithactions.md#isinteractive)
- [isSelectable](card_elements.containerwithactions.md#isselectable)
- [isStandalone](card_elements.containerwithactions.md#isstandalone)
- [isVisible](card_elements.containerwithactions.md#isvisible)
- [lang](card_elements.containerwithactions.md#lang)
- [padding](card_elements.containerwithactions.md#padding)
- [parent](card_elements.containerwithactions.md#parent)
- [renderIfEmpty](card_elements.containerwithactions.md#renderifempty)
- [renderedActionCount](card_elements.containerwithactions.md#renderedactioncount)
- [renderedElement](card_elements.containerwithactions.md#renderedelement)
- [requires](card_elements.containerwithactions.md#requires)
- [selectAction](card_elements.containerwithactions.md#selectaction)
- [separatorElement](card_elements.containerwithactions.md#separatorelement)
- [separatorOrientation](card_elements.containerwithactions.md#separatororientation)
- [style](card_elements.containerwithactions.md#style)
- [useDefaultSizing](card_elements.containerwithactions.md#usedefaultsizing)

### Methods

- [addAction](card_elements.containerwithactions.md#addaction)
- [addItem](card_elements.containerwithactions.md#additem)
- [adjustRenderedElementSize](card_elements.containerwithactions.md#adjustrenderedelementsize)
- [applyBackground](card_elements.containerwithactions.md#applybackground)
- [applyPadding](card_elements.containerwithactions.md#applypadding)
- [asString](card_elements.containerwithactions.md#asstring)
- [clear](card_elements.containerwithactions.md#clear)
- [createPlaceholderElement](card_elements.containerwithactions.md#createplaceholderelement)
- [getActionAt](card_elements.containerwithactions.md#getactionat)
- [getActionById](card_elements.containerwithactions.md#getactionbyid)
- [getActionCount](card_elements.containerwithactions.md#getactioncount)
- [getAllInputs](card_elements.containerwithactions.md#getallinputs)
- [getBleed](card_elements.containerwithactions.md#getbleed)
- [getCustomProperty](card_elements.containerwithactions.md#getcustomproperty)
- [getDefaultPadding](card_elements.containerwithactions.md#getdefaultpadding)
- [getDefaultSerializationContext](card_elements.containerwithactions.md#getdefaultserializationcontext)
- [getEffectivePadding](card_elements.containerwithactions.md#geteffectivepadding)
- [getEffectiveStyle](card_elements.containerwithactions.md#geteffectivestyle)
- [getEffectiveStyleDefinition](card_elements.containerwithactions.md#geteffectivestyledefinition)
- [getElementById](card_elements.containerwithactions.md#getelementbyid)
- [getFirstVisibleRenderedItem](card_elements.containerwithactions.md#getfirstvisiblerendereditem)
- [getForbiddenActionTypes](card_elements.containerwithactions.md#getforbiddenactiontypes)
- [getHasBackground](card_elements.containerwithactions.md#gethasbackground)
- [getHasExpandedAction](card_elements.containerwithactions.md#gethasexpandedaction)
- [getImmediateSurroundingPadding](card_elements.containerwithactions.md#getimmediatesurroundingpadding)
- [getItemAt](card_elements.containerwithactions.md#getitemat)
- [getItemCount](card_elements.containerwithactions.md#getitemcount)
- [getItemsCollectionPropertyName](card_elements.containerwithactions.md#getitemscollectionpropertyname)
- [getJsonTypeName](card_elements.containerwithactions.md#getjsontypename)
- [getLastVisibleRenderedItem](card_elements.containerwithactions.md#getlastvisiblerendereditem)
- [getPadding](card_elements.containerwithactions.md#getpadding)
- [getParentContainer](card_elements.containerwithactions.md#getparentcontainer)
- [getResourceInformation](card_elements.containerwithactions.md#getresourceinformation)
- [getRootElement](card_elements.containerwithactions.md#getrootelement)
- [getRootObject](card_elements.containerwithactions.md#getrootobject)
- [getSchema](card_elements.containerwithactions.md#getschema)
- [getSchemaKey](card_elements.containerwithactions.md#getschemakey)
- [getValue](card_elements.containerwithactions.md#getvalue)
- [hasAllDefaultValues](card_elements.containerwithactions.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.containerwithactions.md#hasdefaultvalue)
- [indexOf](card_elements.containerwithactions.md#indexof)
- [insertItemAfter](card_elements.containerwithactions.md#insertitemafter)
- [insertItemBefore](card_elements.containerwithactions.md#insertitembefore)
- [internalParse](card_elements.containerwithactions.md#internalparse)
- [internalRender](card_elements.containerwithactions.md#internalrender)
- [internalToJSON](card_elements.containerwithactions.md#internaltojson)
- [internalValidateProperties](card_elements.containerwithactions.md#internalvalidateproperties)
- [isAtTheVeryBottom](card_elements.containerwithactions.md#isattheverybottom)
- [isAtTheVeryLeft](card_elements.containerwithactions.md#isattheveryleft)
- [isAtTheVeryRight](card_elements.containerwithactions.md#isattheveryright)
- [isAtTheVeryTop](card_elements.containerwithactions.md#isattheverytop)
- [isBleeding](card_elements.containerwithactions.md#isbleeding)
- [isBleedingAtBottom](card_elements.containerwithactions.md#isbleedingatbottom)
- [isBleedingAtTop](card_elements.containerwithactions.md#isbleedingattop)
- [isBottomElement](card_elements.containerwithactions.md#isbottomelement)
- [isDesignMode](card_elements.containerwithactions.md#isdesignmode)
- [isDisplayed](card_elements.containerwithactions.md#isdisplayed)
- [isElementAllowed](card_elements.containerwithactions.md#iselementallowed)
- [isFirstElement](card_elements.containerwithactions.md#isfirstelement)
- [isHiddenDueToOverflow](card_elements.containerwithactions.md#ishiddenduetooverflow)
- [isLastElement](card_elements.containerwithactions.md#islastelement)
- [isLeftMostElement](card_elements.containerwithactions.md#isleftmostelement)
- [isRightMostElement](card_elements.containerwithactions.md#isrightmostelement)
- [isRtl](card_elements.containerwithactions.md#isrtl)
- [isTopElement](card_elements.containerwithactions.md#istopelement)
- [overrideInternalRender](card_elements.containerwithactions.md#overrideinternalrender)
- [parse](card_elements.containerwithactions.md#parse)
- [populateSchema](card_elements.containerwithactions.md#populateschema)
- [preProcessPropertyValue](card_elements.containerwithactions.md#preprocesspropertyvalue)
- [remove](card_elements.containerwithactions.md#remove)
- [removeItem](card_elements.containerwithactions.md#removeitem)
- [render](card_elements.containerwithactions.md#render)
- [resetDefaultValues](card_elements.containerwithactions.md#resetdefaultvalues)
- [setBleed](card_elements.containerwithactions.md#setbleed)
- [setCustomProperty](card_elements.containerwithactions.md#setcustomproperty)
- [setPadding](card_elements.containerwithactions.md#setpadding)
- [setParent](card_elements.containerwithactions.md#setparent)
- [setShouldFallback](card_elements.containerwithactions.md#setshouldfallback)
- [setValue](card_elements.containerwithactions.md#setvalue)
- [shouldFallback](card_elements.containerwithactions.md#shouldfallback)
- [shouldSerialize](card_elements.containerwithactions.md#shouldserialize)
- [supportsExcplitiHeight](card_elements.containerwithactions.md#supportsexcplitiheight)
- [toJSON](card_elements.containerwithactions.md#tojson)
- [truncateOverflow](card_elements.containerwithactions.md#truncateoverflow)
- [undoOverflowTruncation](card_elements.containerwithactions.md#undooverflowtruncation)
- [updateLayout](card_elements.containerwithactions.md#updatelayout)
- [validateProperties](card_elements.containerwithactions.md#validateproperties)

## Constructors

### constructor

\+ **new ContainerWithActions**(): [*ContainerWithActions*](card_elements.containerwithactions.md)

**Returns:** [*ContainerWithActions*](card_elements.containerwithactions.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6284](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6284)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [Container](card_elements.container.md).[_parent](card_elements.container.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [Container](card_elements.container.md).[_renderedElement](card_elements.container.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### \_selectAction

• `Protected` `Optional` **\_selectAction**: *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [Container](card_elements.container.md).[_selectAction](card_elements.container.md#_selectaction)

Defined in: [card-elements.ts:1851](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1851)

___

### allowVerticalOverflow

• **allowVerticalOverflow**: *boolean*= false

Inherited from: [Container](card_elements.container.md).[allowVerticalOverflow](card_elements.container.md#allowverticaloverflow)

Defined in: [card-elements.ts:1891](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1891)

___

### customCssSelector

• `Optional` **customCssSelector**: *undefined* \| *string*

Inherited from: [Container](card_elements.container.md).[customCssSelector](card_elements.container.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

___

### height

• **height**: [*CardElementHeight*](../modules/card_elements.md#cardelementheight)

Inherited from: [Container](card_elements.container.md).[height](card_elements.container.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

___

### horizontalAlignment

• **horizontalAlignment**: [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)

Inherited from: [Container](card_elements.container.md).[horizontalAlignment](card_elements.container.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [Container](card_elements.container.md).[id](card_elements.container.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [Container](card_elements.container.md).[maxVersion](card_elements.container.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### minPixelHeight

• `Optional` **minPixelHeight**: *undefined* \| *number*

Inherited from: [Container](card_elements.container.md).[minPixelHeight](card_elements.container.md#minpixelheight)

Defined in: [card-elements.ts:5068](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5068)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [Container](card_elements.container.md).[onPreProcessPropertyValue](card_elements.container.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### rtl

• `Optional` **rtl**: *undefined* \| *boolean*

Inherited from: [Container](card_elements.container.md).[rtl](card_elements.container.md#rtl)

Defined in: [card-elements.ts:5334](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5334)

___

### separator

• **separator**: *boolean*

Inherited from: [Container](card_elements.container.md).[separator](card_elements.container.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

___

### spacing

• **spacing**: [*Spacing*](../enums/enums.spacing.md)

Inherited from: [Container](card_elements.container.md).[spacing](card_elements.container.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

___

### verticalContentAlignment

• **verticalContentAlignment**: [*VerticalAlignment*](../enums/enums.verticalalignment.md)

Inherited from: [Container](card_elements.container.md).[verticalContentAlignment](card_elements.container.md#verticalcontentalignment)

Defined in: [card-elements.ts:5331](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5331)

___

### backgroundImageProperty

▪ `Readonly` `Static` **backgroundImageProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [Container](card_elements.container.md).[backgroundImageProperty](card_elements.container.md#backgroundimageproperty)

Defined in: [card-elements.ts:5318](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5318)

___

### bleedProperty

▪ `Readonly` `Static` **bleedProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Container](card_elements.container.md).[bleedProperty](card_elements.container.md#bleedproperty)

Defined in: [card-elements.ts:5044](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5044)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [Container](card_elements.container.md).[defaultMaxVersion](card_elements.container.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [Container](card_elements.container.md).[heightProperty](card_elements.container.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

___

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)\>

Inherited from: [Container](card_elements.container.md).[horizontalAlignmentProperty](card_elements.container.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Container](card_elements.container.md).[idProperty](card_elements.container.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Container](card_elements.container.md).[isVisibleProperty](card_elements.container.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

___

### langProperty

▪ `Readonly` `Static` **langProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Container](card_elements.container.md).[langProperty](card_elements.container.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

___

### minHeightProperty

▪ `Readonly` `Static` **minHeightProperty**: [*PixelSizeProperty*](serialization.pixelsizeproperty.md)

Inherited from: [Container](card_elements.container.md).[minHeightProperty](card_elements.container.md#minheightproperty)

Defined in: [card-elements.ts:5045](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5045)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [Container](card_elements.container.md).[onRegisterCustomProperties](card_elements.container.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [Container](card_elements.container.md).[requiresProperty](card_elements.container.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### rtlProperty

▪ `Readonly` `Static` **rtlProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Container](card_elements.container.md).[rtlProperty](card_elements.container.md#rtlproperty)

Defined in: [card-elements.ts:5323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5323)

___

### selectActionProperty

▪ `Readonly` `Static` **selectActionProperty**: [*ActionProperty*](card_elements.actionproperty.md)

Inherited from: [Container](card_elements.container.md).[selectActionProperty](card_elements.container.md#selectactionproperty)

Defined in: [card-elements.ts:1840](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1840)

___

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Container](card_elements.container.md).[separatorProperty](card_elements.container.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

___

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*Spacing*](../enums/enums.spacing.md)\>

Inherited from: [Container](card_elements.container.md).[spacingProperty](card_elements.container.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

___

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [Container](card_elements.container.md).[styleProperty](card_elements.container.md#styleproperty)

Defined in: [card-elements.ts:5033](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5033)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Container](card_elements.container.md).[typeNameProperty](card_elements.container.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

___

### verticalContentAlignmentProperty

▪ `Readonly` `Static` **verticalContentAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*VerticalAlignment*](../enums/enums.verticalalignment.md)\>

Inherited from: [Container](card_elements.container.md).[verticalContentAlignmentProperty](card_elements.container.md#verticalcontentalignmentproperty)

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

Defined in: [card-elements.ts:6361](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6361)

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

### renderIfEmpty

• `Protected`get **renderIfEmpty**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:6282](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6282)

___

### renderedActionCount

• `Protected`get **renderedActionCount**(): *number*

**Returns:** *number*

Defined in: [card-elements.ts:6278](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6278)

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

### addAction

▸ **addAction**(`action`: [*Action*](card_elements.action.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`action` | [*Action*](card_elements.action.md) |

**Returns:** *void*

Defined in: [card-elements.ts:6323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6323)

___

### addItem

▸ **addItem**(`item`: [*CardElement*](card_elements.cardelement.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5619](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5619)

___

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5072](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5072)

___

### applyBackground

▸ `Protected`**applyBackground**(): *void*

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5373](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5373)

___

### applyPadding

▸ `Protected`**applyPadding**(): *void*

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5092](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5092)

___

### asString

▸ **asString**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L333)

___

### clear

▸ **clear**(): *void*

**Returns:** *void*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6327)

___

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

___

### getActionAt

▸ **getActionAt**(`index`: *number*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6296](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6296)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6305](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6305)

___

### getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6292](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6292)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6333)

___

### getBleed

▸ `Protected`**getBleed**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5175](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5175)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5162](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5162)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

___

### getEffectivePadding

▸ **getEffectivePadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

___

### getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5226](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5226)

___

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

___

### getElementById

▸ **getElementById**(`id`: *string*): *undefined* \| [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:1996](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1996)

___

### getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5540](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5540)

___

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [*ActionType*](../modules/card_elements.md#actiontype)[]

**Returns:** [*ActionType*](../modules/card_elements.md#actiontype)[]

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

___

### getHasBackground

▸ `Protected`**getHasBackground**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5499](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5499)

___

### getHasExpandedAction

▸ `Protected`**getHasExpandedAction**(): *boolean*

**Returns:** *boolean*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6266](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6266)

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

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

___

### getItemAt

▸ **getItemAt**(`index`: *number*): [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5536](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5536)

___

### getItemCount

▸ **getItemCount**(): *number*

**Returns:** *number*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5532](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5532)

___

### getItemsCollectionPropertyName

▸ `Protected`**getItemsCollectionPropertyName**(): *string*

**Returns:** *string*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5369](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5369)

___

### getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5564](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5564)

___

### getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5552](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5552)

___

### getPadding

▸ `Protected`**getPadding**(): *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

___

### getParentContainer

▸ **getParentContainer**(): *undefined* \| [*Container*](card_elements.container.md)

**Returns:** *undefined* \| [*Container*](card_elements.container.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6343](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6343)

___

### getRootElement

▸ **getRootElement**(): [*CardElement*](card_elements.cardelement.md)

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### indexOf

▸ **indexOf**(`cardElement`: [*CardElement*](card_elements.cardelement.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`cardElement` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *number*

Inherited from: [Container](card_elements.container.md)

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

Inherited from: [Container](card_elements.container.md)

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

Inherited from: [Container](card_elements.container.md)

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

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6224](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6224)

___

### internalRender

▸ `Protected`**internalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6236)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6230](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6230)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6311)

___

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

___

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

___

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

___

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

___

### isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5195](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5195)

___

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6347](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6347)

___

### isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5603](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5603)

___

### isBottomElement

▸ **isBottomElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

___

### isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

___

### isDisplayed

▸ `Protected`**isDisplayed**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

___

### isElementAllowed

▸ `Protected`**isElementAllowed**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:1855](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1855)

___

### isFirstElement

▸ **isFirstElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5568](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5568)

___

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

___

### isLastElement

▸ **isLastElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Overrides: [Container](card_elements.container.md)

Defined in: [card-elements.ts:6319](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6319)

___

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

___

### isRightMostElement

▸ **isRightMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

___

### isRtl

▸ **isRtl**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5592)

___

### isTopElement

▸ **isTopElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

___

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [Container](card_elements.container.md)

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

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

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

Inherited from: [Container](card_elements.container.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

___

### removeItem

▸ **removeItem**(`item`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5631](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5631)

___

### render

▸ **render**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5216](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5216)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### setBleed

▸ `Protected`**setBleed**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

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

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setPadding

▸ `Protected`**setPadding**(`value`: *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md) |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

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

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

___

### supportsExcplitiHeight

▸ `Protected`**supportsExcplitiHeight**(): *boolean*

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5365](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5365)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [Container](card_elements.container.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

___

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: *number*): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`maxHeight` | *number* |

**Returns:** *boolean*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5454](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5454)

___

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): *void*

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:5493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5493)

___

### updateLayout

▸ **updateLayout**(`processChildren?`: *boolean*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processChildren` | *boolean* | true |

**Returns:** *void*

Inherited from: [Container](card_elements.container.md)

Defined in: [card-elements.ts:1966](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1966)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [Container](card_elements.container.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
