[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / AdaptiveCard

# Class: AdaptiveCard

[card-elements](../modules/card_elements.md).AdaptiveCard

## Hierarchy

* [*ContainerWithActions*](card_elements.containerwithactions.md)

  ↳ **AdaptiveCard**

## Table of contents

### Constructors

- [constructor](card_elements.adaptivecard.md#constructor)

### Properties

- [\_parent](card_elements.adaptivecard.md#_parent)
- [\_renderedElement](card_elements.adaptivecard.md#_renderedelement)
- [\_selectAction](card_elements.adaptivecard.md#_selectaction)
- [allowVerticalOverflow](card_elements.adaptivecard.md#allowverticaloverflow)
- [customCssSelector](card_elements.adaptivecard.md#customcssselector)
- [designMode](card_elements.adaptivecard.md#designmode)
- [fallbackText](card_elements.adaptivecard.md#fallbacktext)
- [height](card_elements.adaptivecard.md#height)
- [horizontalAlignment](card_elements.adaptivecard.md#horizontalalignment)
- [id](card_elements.adaptivecard.md#id)
- [maxVersion](card_elements.adaptivecard.md#maxversion)
- [minPixelHeight](card_elements.adaptivecard.md#minpixelheight)
- [onAnchorClicked](card_elements.adaptivecard.md#onanchorclicked)
- [onElementVisibilityChanged](card_elements.adaptivecard.md#onelementvisibilitychanged)
- [onExecuteAction](card_elements.adaptivecard.md#onexecuteaction)
- [onImageLoaded](card_elements.adaptivecard.md#onimageloaded)
- [onInlineCardExpanded](card_elements.adaptivecard.md#oninlinecardexpanded)
- [onInputValueChanged](card_elements.adaptivecard.md#oninputvaluechanged)
- [onPreProcessPropertyValue](card_elements.adaptivecard.md#onpreprocesspropertyvalue)
- [rtl](card_elements.adaptivecard.md#rtl)
- [separator](card_elements.adaptivecard.md#separator)
- [spacing](card_elements.adaptivecard.md#spacing)
- [speak](card_elements.adaptivecard.md#speak)
- [version](card_elements.adaptivecard.md#version)
- [verticalContentAlignment](card_elements.adaptivecard.md#verticalcontentalignment)
- [$schemaProperty](card_elements.adaptivecard.md#$schemaproperty)
- [backgroundImageProperty](card_elements.adaptivecard.md#backgroundimageproperty)
- [bleedProperty](card_elements.adaptivecard.md#bleedproperty)
- [defaultMaxVersion](card_elements.adaptivecard.md#defaultmaxversion)
- [fallbackTextProperty](card_elements.adaptivecard.md#fallbacktextproperty)
- [heightProperty](card_elements.adaptivecard.md#heightproperty)
- [horizontalAlignmentProperty](card_elements.adaptivecard.md#horizontalalignmentproperty)
- [idProperty](card_elements.adaptivecard.md#idproperty)
- [isVisibleProperty](card_elements.adaptivecard.md#isvisibleproperty)
- [langProperty](card_elements.adaptivecard.md#langproperty)
- [minHeightProperty](card_elements.adaptivecard.md#minheightproperty)
- [onAnchorClicked](card_elements.adaptivecard.md#onanchorclicked)
- [onElementVisibilityChanged](card_elements.adaptivecard.md#onelementvisibilitychanged)
- [onExecuteAction](card_elements.adaptivecard.md#onexecuteaction)
- [onImageLoaded](card_elements.adaptivecard.md#onimageloaded)
- [onInlineCardExpanded](card_elements.adaptivecard.md#oninlinecardexpanded)
- [onInputValueChanged](card_elements.adaptivecard.md#oninputvaluechanged)
- [onProcessMarkdown](card_elements.adaptivecard.md#onprocessmarkdown)
- [onRegisterCustomProperties](card_elements.adaptivecard.md#onregistercustomproperties)
- [requiresProperty](card_elements.adaptivecard.md#requiresproperty)
- [rtlProperty](card_elements.adaptivecard.md#rtlproperty)
- [schemaUrl](card_elements.adaptivecard.md#schemaurl)
- [selectActionProperty](card_elements.adaptivecard.md#selectactionproperty)
- [separatorProperty](card_elements.adaptivecard.md#separatorproperty)
- [spacingProperty](card_elements.adaptivecard.md#spacingproperty)
- [speakProperty](card_elements.adaptivecard.md#speakproperty)
- [styleProperty](card_elements.adaptivecard.md#styleproperty)
- [typeNameProperty](card_elements.adaptivecard.md#typenameproperty)
- [versionProperty](card_elements.adaptivecard.md#versionproperty)
- [verticalContentAlignmentProperty](card_elements.adaptivecard.md#verticalcontentalignmentproperty)

### Accessors

- [allowCustomPadding](card_elements.adaptivecard.md#allowcustompadding)
- [allowCustomStyle](card_elements.adaptivecard.md#allowcustomstyle)
- [backgroundImage](card_elements.adaptivecard.md#backgroundimage)
- [bleed](card_elements.adaptivecard.md#bleed)
- [bypassVersionCheck](card_elements.adaptivecard.md#bypassversioncheck)
- [defaultStyle](card_elements.adaptivecard.md#defaultstyle)
- [hasBackground](card_elements.adaptivecard.md#hasbackground)
- [hasExplicitStyle](card_elements.adaptivecard.md#hasexplicitstyle)
- [hasVisibleSeparator](card_elements.adaptivecard.md#hasvisibleseparator)
- [hostConfig](card_elements.adaptivecard.md#hostconfig)
- [index](card_elements.adaptivecard.md#index)
- [isInline](card_elements.adaptivecard.md#isinline)
- [isInteractive](card_elements.adaptivecard.md#isinteractive)
- [isSelectable](card_elements.adaptivecard.md#isselectable)
- [isStandalone](card_elements.adaptivecard.md#isstandalone)
- [isVisible](card_elements.adaptivecard.md#isvisible)
- [lang](card_elements.adaptivecard.md#lang)
- [padding](card_elements.adaptivecard.md#padding)
- [parent](card_elements.adaptivecard.md#parent)
- [renderIfEmpty](card_elements.adaptivecard.md#renderifempty)
- [renderedActionCount](card_elements.adaptivecard.md#renderedactioncount)
- [renderedElement](card_elements.adaptivecard.md#renderedelement)
- [requires](card_elements.adaptivecard.md#requires)
- [selectAction](card_elements.adaptivecard.md#selectaction)
- [separatorElement](card_elements.adaptivecard.md#separatorelement)
- [separatorOrientation](card_elements.adaptivecard.md#separatororientation)
- [style](card_elements.adaptivecard.md#style)
- [useDefaultSizing](card_elements.adaptivecard.md#usedefaultsizing)
- [processMarkdown](card_elements.adaptivecard.md#processmarkdown)

### Methods

- [addAction](card_elements.adaptivecard.md#addaction)
- [addItem](card_elements.adaptivecard.md#additem)
- [adjustRenderedElementSize](card_elements.adaptivecard.md#adjustrenderedelementsize)
- [applyBackground](card_elements.adaptivecard.md#applybackground)
- [applyPadding](card_elements.adaptivecard.md#applypadding)
- [asString](card_elements.adaptivecard.md#asstring)
- [clear](card_elements.adaptivecard.md#clear)
- [createPlaceholderElement](card_elements.adaptivecard.md#createplaceholderelement)
- [getActionAt](card_elements.adaptivecard.md#getactionat)
- [getActionById](card_elements.adaptivecard.md#getactionbyid)
- [getActionCount](card_elements.adaptivecard.md#getactioncount)
- [getAllInputs](card_elements.adaptivecard.md#getallinputs)
- [getBleed](card_elements.adaptivecard.md#getbleed)
- [getCustomProperty](card_elements.adaptivecard.md#getcustomproperty)
- [getDefaultPadding](card_elements.adaptivecard.md#getdefaultpadding)
- [getDefaultSerializationContext](card_elements.adaptivecard.md#getdefaultserializationcontext)
- [getEffectivePadding](card_elements.adaptivecard.md#geteffectivepadding)
- [getEffectiveStyle](card_elements.adaptivecard.md#geteffectivestyle)
- [getEffectiveStyleDefinition](card_elements.adaptivecard.md#geteffectivestyledefinition)
- [getElementById](card_elements.adaptivecard.md#getelementbyid)
- [getFirstVisibleRenderedItem](card_elements.adaptivecard.md#getfirstvisiblerendereditem)
- [getForbiddenActionTypes](card_elements.adaptivecard.md#getforbiddenactiontypes)
- [getHasBackground](card_elements.adaptivecard.md#gethasbackground)
- [getHasExpandedAction](card_elements.adaptivecard.md#gethasexpandedaction)
- [getImmediateSurroundingPadding](card_elements.adaptivecard.md#getimmediatesurroundingpadding)
- [getItemAt](card_elements.adaptivecard.md#getitemat)
- [getItemCount](card_elements.adaptivecard.md#getitemcount)
- [getItemsCollectionPropertyName](card_elements.adaptivecard.md#getitemscollectionpropertyname)
- [getJsonTypeName](card_elements.adaptivecard.md#getjsontypename)
- [getLastVisibleRenderedItem](card_elements.adaptivecard.md#getlastvisiblerendereditem)
- [getPadding](card_elements.adaptivecard.md#getpadding)
- [getParentContainer](card_elements.adaptivecard.md#getparentcontainer)
- [getResourceInformation](card_elements.adaptivecard.md#getresourceinformation)
- [getRootElement](card_elements.adaptivecard.md#getrootelement)
- [getRootObject](card_elements.adaptivecard.md#getrootobject)
- [getSchema](card_elements.adaptivecard.md#getschema)
- [getSchemaKey](card_elements.adaptivecard.md#getschemakey)
- [getValue](card_elements.adaptivecard.md#getvalue)
- [hasAllDefaultValues](card_elements.adaptivecard.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.adaptivecard.md#hasdefaultvalue)
- [indexOf](card_elements.adaptivecard.md#indexof)
- [insertItemAfter](card_elements.adaptivecard.md#insertitemafter)
- [insertItemBefore](card_elements.adaptivecard.md#insertitembefore)
- [internalParse](card_elements.adaptivecard.md#internalparse)
- [internalRender](card_elements.adaptivecard.md#internalrender)
- [internalToJSON](card_elements.adaptivecard.md#internaltojson)
- [internalValidateProperties](card_elements.adaptivecard.md#internalvalidateproperties)
- [isAtTheVeryBottom](card_elements.adaptivecard.md#isattheverybottom)
- [isAtTheVeryLeft](card_elements.adaptivecard.md#isattheveryleft)
- [isAtTheVeryRight](card_elements.adaptivecard.md#isattheveryright)
- [isAtTheVeryTop](card_elements.adaptivecard.md#isattheverytop)
- [isBleeding](card_elements.adaptivecard.md#isbleeding)
- [isBleedingAtBottom](card_elements.adaptivecard.md#isbleedingatbottom)
- [isBleedingAtTop](card_elements.adaptivecard.md#isbleedingattop)
- [isBottomElement](card_elements.adaptivecard.md#isbottomelement)
- [isDesignMode](card_elements.adaptivecard.md#isdesignmode)
- [isDisplayed](card_elements.adaptivecard.md#isdisplayed)
- [isElementAllowed](card_elements.adaptivecard.md#iselementallowed)
- [isFirstElement](card_elements.adaptivecard.md#isfirstelement)
- [isHiddenDueToOverflow](card_elements.adaptivecard.md#ishiddenduetooverflow)
- [isLastElement](card_elements.adaptivecard.md#islastelement)
- [isLeftMostElement](card_elements.adaptivecard.md#isleftmostelement)
- [isRightMostElement](card_elements.adaptivecard.md#isrightmostelement)
- [isRtl](card_elements.adaptivecard.md#isrtl)
- [isTopElement](card_elements.adaptivecard.md#istopelement)
- [overrideInternalRender](card_elements.adaptivecard.md#overrideinternalrender)
- [parse](card_elements.adaptivecard.md#parse)
- [populateSchema](card_elements.adaptivecard.md#populateschema)
- [preProcessPropertyValue](card_elements.adaptivecard.md#preprocesspropertyvalue)
- [remove](card_elements.adaptivecard.md#remove)
- [removeItem](card_elements.adaptivecard.md#removeitem)
- [render](card_elements.adaptivecard.md#render)
- [resetDefaultValues](card_elements.adaptivecard.md#resetdefaultvalues)
- [setBleed](card_elements.adaptivecard.md#setbleed)
- [setCustomProperty](card_elements.adaptivecard.md#setcustomproperty)
- [setPadding](card_elements.adaptivecard.md#setpadding)
- [setParent](card_elements.adaptivecard.md#setparent)
- [setShouldFallback](card_elements.adaptivecard.md#setshouldfallback)
- [setValue](card_elements.adaptivecard.md#setvalue)
- [shouldFallback](card_elements.adaptivecard.md#shouldfallback)
- [shouldSerialize](card_elements.adaptivecard.md#shouldserialize)
- [supportsExcplitiHeight](card_elements.adaptivecard.md#supportsexcplitiheight)
- [toJSON](card_elements.adaptivecard.md#tojson)
- [truncateOverflow](card_elements.adaptivecard.md#truncateoverflow)
- [undoOverflowTruncation](card_elements.adaptivecard.md#undooverflowtruncation)
- [updateLayout](card_elements.adaptivecard.md#updatelayout)
- [validateProperties](card_elements.adaptivecard.md#validateproperties)
- [applyMarkdown](card_elements.adaptivecard.md#applymarkdown)

## Constructors

### constructor

\+ **new AdaptiveCard**(): [*AdaptiveCard*](card_elements.adaptivecard.md)

**Returns:** [*AdaptiveCard*](card_elements.adaptivecard.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6284](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6284)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[_parent](card_elements.containerwithactions.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[_renderedElement](card_elements.containerwithactions.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### \_selectAction

• `Protected` `Optional` **\_selectAction**: *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[_selectAction](card_elements.containerwithactions.md#_selectaction)

Defined in: [card-elements.ts:1851](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1851)

___

### allowVerticalOverflow

• **allowVerticalOverflow**: *boolean*= false

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[allowVerticalOverflow](card_elements.containerwithactions.md#allowverticaloverflow)

Defined in: [card-elements.ts:1891](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1891)

___

### customCssSelector

• `Optional` **customCssSelector**: *undefined* \| *string*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[customCssSelector](card_elements.containerwithactions.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

___

### designMode

• **designMode**: *boolean*= false

Defined in: [card-elements.ts:6557](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6557)

___

### fallbackText

• `Optional` **fallbackText**: *undefined* \| *string*

Defined in: [card-elements.ts:6417](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6417)

___

### height

• **height**: [*CardElementHeight*](../modules/card_elements.md#cardelementheight)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[height](card_elements.containerwithactions.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

___

### horizontalAlignment

• **horizontalAlignment**: [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[horizontalAlignment](card_elements.containerwithactions.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[id](card_elements.containerwithactions.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[maxVersion](card_elements.containerwithactions.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### minPixelHeight

• `Optional` **minPixelHeight**: *undefined* \| *number*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[minPixelHeight](card_elements.containerwithactions.md#minpixelheight)

Defined in: [card-elements.ts:5068](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5068)

___

### onAnchorClicked

• `Optional` **onAnchorClicked**: *undefined* \| (`element`: [*CardElement*](card_elements.cardelement.md), `anchor`: HTMLAnchorElement) => *boolean*

Defined in: [card-elements.ts:6550](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6550)

___

### onElementVisibilityChanged

• `Optional` **onElementVisibilityChanged**: *undefined* \| (`element`: [*CardElement*](card_elements.cardelement.md)) => *void*

Defined in: [card-elements.ts:6552](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6552)

___

### onExecuteAction

• `Optional` **onExecuteAction**: *undefined* \| (`action`: [*Action*](card_elements.action.md)) => *void*

Defined in: [card-elements.ts:6551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6551)

___

### onImageLoaded

• `Optional` **onImageLoaded**: *undefined* \| (`image`: [*Image*](card_elements.image.md)) => *void*

Defined in: [card-elements.ts:6553](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6553)

___

### onInlineCardExpanded

• `Optional` **onInlineCardExpanded**: *undefined* \| (`action`: [*ShowCardAction*](card_elements.showcardaction.md), `isExpanded`: *boolean*) => *void*

Defined in: [card-elements.ts:6554](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6554)

___

### onInputValueChanged

• `Optional` **onInputValueChanged**: *undefined* \| (`input`: [*Input*](card_elements.input.md)) => *void*

Defined in: [card-elements.ts:6555](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6555)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[onPreProcessPropertyValue](card_elements.containerwithactions.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### rtl

• `Optional` **rtl**: *undefined* \| *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[rtl](card_elements.containerwithactions.md#rtl)

Defined in: [card-elements.ts:5334](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5334)

___

### separator

• **separator**: *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[separator](card_elements.containerwithactions.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

___

### spacing

• **spacing**: [*Spacing*](../enums/enums.spacing.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[spacing](card_elements.containerwithactions.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

___

### speak

• `Optional` **speak**: *undefined* \| *string*

Defined in: [card-elements.ts:6420](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6420)

___

### version

• **version**: [*Version*](serialization.version.md)

Defined in: [card-elements.ts:6414](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6414)

___

### verticalContentAlignment

• **verticalContentAlignment**: [*VerticalAlignment*](../enums/enums.verticalalignment.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[verticalContentAlignment](card_elements.containerwithactions.md#verticalcontentalignment)

Defined in: [card-elements.ts:5331](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5331)

___

### $schemaProperty

▪ `Protected` `Readonly` `Static` **$schemaProperty**: [*CustomProperty*](serialization.customproperty.md)<string\>

Defined in: [card-elements.ts:6377](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6377)

___

### backgroundImageProperty

▪ `Readonly` `Static` **backgroundImageProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[backgroundImageProperty](card_elements.containerwithactions.md#backgroundimageproperty)

Defined in: [card-elements.ts:5318](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5318)

___

### bleedProperty

▪ `Readonly` `Static` **bleedProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[bleedProperty](card_elements.containerwithactions.md#bleedproperty)

Defined in: [card-elements.ts:5044](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5044)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[defaultMaxVersion](card_elements.containerwithactions.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### fallbackTextProperty

▪ `Readonly` `Static` **fallbackTextProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:6410](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6410)

___

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[heightProperty](card_elements.containerwithactions.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

___

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)\>

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[horizontalAlignmentProperty](card_elements.containerwithactions.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[idProperty](card_elements.containerwithactions.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[isVisibleProperty](card_elements.containerwithactions.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

___

### langProperty

▪ `Readonly` `Static` **langProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[langProperty](card_elements.containerwithactions.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

___

### minHeightProperty

▪ `Readonly` `Static` **minHeightProperty**: [*PixelSizeProperty*](serialization.pixelsizeproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[minHeightProperty](card_elements.containerwithactions.md#minheightproperty)

Defined in: [card-elements.ts:5045](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5045)

___

### onAnchorClicked

▪ `Optional` `Static` **onAnchorClicked**: *undefined* \| (`element`: [*CardElement*](card_elements.cardelement.md), `anchor`: HTMLAnchorElement) => *boolean*

Defined in: [card-elements.ts:6424](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6424)

___

### onElementVisibilityChanged

▪ `Optional` `Static` **onElementVisibilityChanged**: *undefined* \| (`element`: [*CardElement*](card_elements.cardelement.md)) => *void*

Defined in: [card-elements.ts:6426](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6426)

___

### onExecuteAction

▪ `Optional` `Static` **onExecuteAction**: *undefined* \| (`action`: [*Action*](card_elements.action.md)) => *void*

Defined in: [card-elements.ts:6425](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6425)

___

### onImageLoaded

▪ `Optional` `Static` **onImageLoaded**: *undefined* \| (`image`: [*Image*](card_elements.image.md)) => *void*

Defined in: [card-elements.ts:6427](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6427)

___

### onInlineCardExpanded

▪ `Optional` `Static` **onInlineCardExpanded**: *undefined* \| (`action`: [*ShowCardAction*](card_elements.showcardaction.md), `isExpanded`: *boolean*) => *void*

Defined in: [card-elements.ts:6428](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6428)

___

### onInputValueChanged

▪ `Optional` `Static` **onInputValueChanged**: *undefined* \| (`input`: [*Input*](card_elements.input.md)) => *void*

Defined in: [card-elements.ts:6429](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6429)

___

### onProcessMarkdown

▪ `Optional` `Static` **onProcessMarkdown**: *undefined* \| (`text`: *string*, `result`: [*IMarkdownProcessingResult*](../interfaces/card_elements.imarkdownprocessingresult.md)) => *void*

Defined in: [card-elements.ts:6430](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6430)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[onRegisterCustomProperties](card_elements.containerwithactions.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[requiresProperty](card_elements.containerwithactions.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### rtlProperty

▪ `Readonly` `Static` **rtlProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[rtlProperty](card_elements.containerwithactions.md#rtlproperty)

Defined in: [card-elements.ts:5323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5323)

___

### schemaUrl

▪ `Readonly` `Static` **schemaUrl**: *http://adaptivecards.io/schemas/adaptive-card.json*= "http://adaptivecards.io/schemas/adaptive-card.json"

Defined in: [card-elements.ts:6373](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6373)

___

### selectActionProperty

▪ `Readonly` `Static` **selectActionProperty**: [*ActionProperty*](card_elements.actionproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[selectActionProperty](card_elements.containerwithactions.md#selectactionproperty)

Defined in: [card-elements.ts:1840](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1840)

___

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[separatorProperty](card_elements.containerwithactions.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

___

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*Spacing*](../enums/enums.spacing.md)\>

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[spacingProperty](card_elements.containerwithactions.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

___

### speakProperty

▪ `Readonly` `Static` **speakProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:6411](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6411)

___

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[styleProperty](card_elements.containerwithactions.md#styleproperty)

Defined in: [card-elements.ts:5033](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5033)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[typeNameProperty](card_elements.containerwithactions.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

___

### versionProperty

▪ `Readonly` `Static` **versionProperty**: [*CustomProperty*](serialization.customproperty.md)<undefined \| [*Version*](serialization.version.md)\>

Defined in: [card-elements.ts:6387](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6387)

___

### verticalContentAlignmentProperty

▪ `Readonly` `Static` **verticalContentAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*VerticalAlignment*](../enums/enums.verticalalignment.md)\>

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md).[verticalContentAlignmentProperty](card_elements.containerwithactions.md#verticalcontentalignmentproperty)

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

Defined in: [card-elements.ts:6542](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6542)

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

### bypassVersionCheck

• `Protected`get **bypassVersionCheck**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:6538](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6538)

___

### defaultStyle

• `Protected`get **defaultStyle**(): *string*

**Returns:** *string*

Defined in: [card-elements.ts:323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L323)

___

### hasBackground

• `Protected`get **hasBackground**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:6546](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6546)

___

### hasExplicitStyle

• `Protected`get **hasExplicitStyle**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:5187](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5187)

___

### hasVisibleSeparator

• get **hasVisibleSeparator**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:6639](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6639)

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

Defined in: [card-elements.ts:6534](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6534)

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

___

### processMarkdown

• `Static`get **processMarkdown**(): (`text`: *string*) => *string*

**Returns:** *function*

Defined in: [card-elements.ts:6432](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6432)

• `Static`set **processMarkdown**(`value`: (`text`: *string*) => *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | (`text`: *string*) => *string* |

**Returns:** *void*

Defined in: [card-elements.ts:6436](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6436)

## Methods

### addAction

▸ **addAction**(`action`: [*Action*](card_elements.action.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`action` | [*Action*](card_elements.action.md) |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6323)

___

### addItem

▸ **addItem**(`item`: [*CardElement*](card_elements.cardelement.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5619](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5619)

___

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5072](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5072)

___

### applyBackground

▸ `Protected`**applyBackground**(): *void*

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5373](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5373)

___

### applyPadding

▸ `Protected`**applyPadding**(): *void*

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5092](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5092)

___

### asString

▸ **asString**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L333)

___

### clear

▸ **clear**(): *void*

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6327)

___

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

___

### getActionAt

▸ **getActionAt**(`index`: *number*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6296](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6296)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6305](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6305)

___

### getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6292](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6292)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6333)

___

### getBleed

▸ `Protected`**getBleed**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5175](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5175)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6522](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6522)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6478](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6478)

___

### getEffectivePadding

▸ **getEffectivePadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

___

### getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5226](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5226)

___

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

___

### getElementById

▸ **getElementById**(`id`: *string*): *undefined* \| [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:1996](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1996)

___

### getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5540](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5540)

___

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [*ActionType*](../modules/card_elements.md#actiontype)[]

**Returns:** [*ActionType*](../modules/card_elements.md#actiontype)[]

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

___

### getHasBackground

▸ `Protected`**getHasBackground**(): *boolean*

**Returns:** *boolean*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6518](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6518)

___

### getHasExpandedAction

▸ `Protected`**getHasExpandedAction**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

___

### getItemAt

▸ **getItemAt**(`index`: *number*): [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5536](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5536)

___

### getItemCount

▸ **getItemCount**(): *number*

**Returns:** *number*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5532](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5532)

___

### getItemsCollectionPropertyName

▸ `Protected`**getItemsCollectionPropertyName**(): *string*

**Returns:** *string*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6482](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6482)

___

### getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6559](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6559)

___

### getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5552](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5552)

___

### getPadding

▸ `Protected`**getPadding**(): *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

___

### getParentContainer

▸ **getParentContainer**(): *undefined* \| [*Container*](card_elements.container.md)

**Returns:** *undefined* \| [*Container*](card_elements.container.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6343](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6343)

___

### getRootElement

▸ **getRootElement**(): [*CardElement*](card_elements.cardelement.md)

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### indexOf

▸ **indexOf**(`cardElement`: [*CardElement*](card_elements.cardelement.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`cardElement` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *number*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6486](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6486)

___

### internalRender

▸ `Protected`**internalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6505)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6499](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6499)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6563](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6563)

___

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

___

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

___

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

___

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

___

### isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5195](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5195)

___

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6347](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6347)

___

### isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5603](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5603)

___

### isBottomElement

▸ **isBottomElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

___

### isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

___

### isDisplayed

▸ `Protected`**isDisplayed**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

___

### isElementAllowed

▸ `Protected`**isElementAllowed**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:1855](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1855)

___

### isFirstElement

▸ **isFirstElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5568](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5568)

___

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

___

### isLastElement

▸ **isLastElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6319](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6319)

___

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

___

### isRightMostElement

▸ **isRightMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

___

### isRtl

▸ **isRtl**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5592)

___

### isTopElement

▸ **isTopElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

___

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

___

### removeItem

▸ **removeItem**(`item`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`item` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5631](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5631)

___

### render

▸ **render**(`target?`: HTMLElement): *undefined* \| HTMLElement

#### Parameters:

Name | Type |
:------ | :------ |
`target?` | HTMLElement |

**Returns:** *undefined* \| HTMLElement

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6587](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6587)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### setBleed

▸ `Protected`**setBleed**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setPadding

▸ `Protected`**setPadding**(`value`: *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md) |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

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

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6635](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6635)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6530](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6530)

___

### supportsExcplitiHeight

▸ `Protected`**supportsExcplitiHeight**(): *boolean*

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5365](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5365)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

___

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: *number*): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`maxHeight` | *number* |

**Returns:** *boolean*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5454](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5454)

___

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): *void*

**Returns:** *void*

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:5493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5493)

___

### updateLayout

▸ **updateLayout**(`processChildren?`: *boolean*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processChildren` | *boolean* | true |

**Returns:** *void*

Overrides: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-elements.ts:6625](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6625)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [ContainerWithActions](card_elements.containerwithactions.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)

___

### applyMarkdown

▸ `Static`**applyMarkdown**(`text`: *string*): [*IMarkdownProcessingResult*](../interfaces/card_elements.imarkdownprocessingresult.md)

#### Parameters:

Name | Type |
:------ | :------ |
`text` | *string* |

**Returns:** [*IMarkdownProcessingResult*](../interfaces/card_elements.imarkdownprocessingresult.md)

Defined in: [card-elements.ts:6440](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6440)
