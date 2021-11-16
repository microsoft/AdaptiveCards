[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / Container

# Class: Container

[card-elements](../modules/card_elements.md).Container

## Hierarchy

- [_StylableCardElementContainer_](card_elements.stylablecardelementcontainer.md)

  ↳ **Container**

  ↳↳ [_Column_](card_elements.column.md)

  ↳↳ [_ContainerWithActions_](card_elements.containerwithactions.md)

  ↳↳ [_Column_](adaptivecards.column.md)

  ↳↳ [_ContainerWithActions_](adaptivecards.containerwithactions.md)

## Table of contents

### Constructors

- [constructor](card_elements.container.md#constructor)

### Properties

- [\_parent](card_elements.container.md#_parent)
- [\_renderedElement](card_elements.container.md#_renderedelement)
- [\_selectAction](card_elements.container.md#_selectaction)
- [allowVerticalOverflow](card_elements.container.md#allowverticaloverflow)
- [customCssSelector](card_elements.container.md#customcssselector)
- [height](card_elements.container.md#height)
- [horizontalAlignment](card_elements.container.md#horizontalalignment)
- [id](card_elements.container.md#id)
- [maxVersion](card_elements.container.md#maxversion)
- [minPixelHeight](card_elements.container.md#minpixelheight)
- [onPreProcessPropertyValue](card_elements.container.md#onpreprocesspropertyvalue)
- [rtl](card_elements.container.md#rtl)
- [separator](card_elements.container.md#separator)
- [spacing](card_elements.container.md#spacing)
- [verticalContentAlignment](card_elements.container.md#verticalcontentalignment)
- [backgroundImageProperty](card_elements.container.md#backgroundimageproperty)
- [bleedProperty](card_elements.container.md#bleedproperty)
- [defaultMaxVersion](card_elements.container.md#defaultmaxversion)
- [heightProperty](card_elements.container.md#heightproperty)
- [horizontalAlignmentProperty](card_elements.container.md#horizontalalignmentproperty)
- [idProperty](card_elements.container.md#idproperty)
- [isVisibleProperty](card_elements.container.md#isvisibleproperty)
- [langProperty](card_elements.container.md#langproperty)
- [minHeightProperty](card_elements.container.md#minheightproperty)
- [onRegisterCustomProperties](card_elements.container.md#onregistercustomproperties)
- [requiresProperty](card_elements.container.md#requiresproperty)
- [rtlProperty](card_elements.container.md#rtlproperty)
- [selectActionProperty](card_elements.container.md#selectactionproperty)
- [separatorProperty](card_elements.container.md#separatorproperty)
- [spacingProperty](card_elements.container.md#spacingproperty)
- [styleProperty](card_elements.container.md#styleproperty)
- [typeNameProperty](card_elements.container.md#typenameproperty)
- [verticalContentAlignmentProperty](card_elements.container.md#verticalcontentalignmentproperty)

### Accessors

- [allowCustomPadding](card_elements.container.md#allowcustompadding)
- [allowCustomStyle](card_elements.container.md#allowcustomstyle)
- [backgroundImage](card_elements.container.md#backgroundimage)
- [bleed](card_elements.container.md#bleed)
- [defaultStyle](card_elements.container.md#defaultstyle)
- [hasExplicitStyle](card_elements.container.md#hasexplicitstyle)
- [hasVisibleSeparator](card_elements.container.md#hasvisibleseparator)
- [hostConfig](card_elements.container.md#hostconfig)
- [index](card_elements.container.md#index)
- [isInline](card_elements.container.md#isinline)
- [isInteractive](card_elements.container.md#isinteractive)
- [isSelectable](card_elements.container.md#isselectable)
- [isStandalone](card_elements.container.md#isstandalone)
- [isVisible](card_elements.container.md#isvisible)
- [lang](card_elements.container.md#lang)
- [padding](card_elements.container.md#padding)
- [parent](card_elements.container.md#parent)
- [renderedActionCount](card_elements.container.md#renderedactioncount)
- [renderedElement](card_elements.container.md#renderedelement)
- [requires](card_elements.container.md#requires)
- [selectAction](card_elements.container.md#selectaction)
- [separatorElement](card_elements.container.md#separatorelement)
- [separatorOrientation](card_elements.container.md#separatororientation)
- [style](card_elements.container.md#style)
- [useDefaultSizing](card_elements.container.md#usedefaultsizing)

### Methods

- [addItem](card_elements.container.md#additem)
- [adjustRenderedElementSize](card_elements.container.md#adjustrenderedelementsize)
- [applyBackground](card_elements.container.md#applybackground)
- [applyPadding](card_elements.container.md#applypadding)
- [asString](card_elements.container.md#asstring)
- [clear](card_elements.container.md#clear)
- [createPlaceholderElement](card_elements.container.md#createplaceholderelement)
- [getActionAt](card_elements.container.md#getactionat)
- [getActionById](card_elements.container.md#getactionbyid)
- [getActionCount](card_elements.container.md#getactioncount)
- [getAllInputs](card_elements.container.md#getallinputs)
- [getBleed](card_elements.container.md#getbleed)
- [getCustomProperty](card_elements.container.md#getcustomproperty)
- [getDefaultPadding](card_elements.container.md#getdefaultpadding)
- [getDefaultSerializationContext](card_elements.container.md#getdefaultserializationcontext)
- [getEffectivePadding](card_elements.container.md#geteffectivepadding)
- [getEffectiveStyle](card_elements.container.md#geteffectivestyle)
- [getEffectiveStyleDefinition](card_elements.container.md#geteffectivestyledefinition)
- [getElementById](card_elements.container.md#getelementbyid)
- [getFirstVisibleRenderedItem](card_elements.container.md#getfirstvisiblerendereditem)
- [getForbiddenActionTypes](card_elements.container.md#getforbiddenactiontypes)
- [getHasBackground](card_elements.container.md#gethasbackground)
- [getHasExpandedAction](card_elements.container.md#gethasexpandedaction)
- [getImmediateSurroundingPadding](card_elements.container.md#getimmediatesurroundingpadding)
- [getItemAt](card_elements.container.md#getitemat)
- [getItemCount](card_elements.container.md#getitemcount)
- [getItemsCollectionPropertyName](card_elements.container.md#getitemscollectionpropertyname)
- [getJsonTypeName](card_elements.container.md#getjsontypename)
- [getLastVisibleRenderedItem](card_elements.container.md#getlastvisiblerendereditem)
- [getPadding](card_elements.container.md#getpadding)
- [getParentContainer](card_elements.container.md#getparentcontainer)
- [getResourceInformation](card_elements.container.md#getresourceinformation)
- [getRootElement](card_elements.container.md#getrootelement)
- [getRootObject](card_elements.container.md#getrootobject)
- [getSchema](card_elements.container.md#getschema)
- [getSchemaKey](card_elements.container.md#getschemakey)
- [getValue](card_elements.container.md#getvalue)
- [hasAllDefaultValues](card_elements.container.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.container.md#hasdefaultvalue)
- [indexOf](card_elements.container.md#indexof)
- [insertItemAfter](card_elements.container.md#insertitemafter)
- [insertItemBefore](card_elements.container.md#insertitembefore)
- [internalParse](card_elements.container.md#internalparse)
- [internalRender](card_elements.container.md#internalrender)
- [internalToJSON](card_elements.container.md#internaltojson)
- [internalValidateProperties](card_elements.container.md#internalvalidateproperties)
- [isAtTheVeryBottom](card_elements.container.md#isattheverybottom)
- [isAtTheVeryLeft](card_elements.container.md#isattheveryleft)
- [isAtTheVeryRight](card_elements.container.md#isattheveryright)
- [isAtTheVeryTop](card_elements.container.md#isattheverytop)
- [isBleeding](card_elements.container.md#isbleeding)
- [isBleedingAtBottom](card_elements.container.md#isbleedingatbottom)
- [isBleedingAtTop](card_elements.container.md#isbleedingattop)
- [isBottomElement](card_elements.container.md#isbottomelement)
- [isDesignMode](card_elements.container.md#isdesignmode)
- [isDisplayed](card_elements.container.md#isdisplayed)
- [isElementAllowed](card_elements.container.md#iselementallowed)
- [isFirstElement](card_elements.container.md#isfirstelement)
- [isHiddenDueToOverflow](card_elements.container.md#ishiddenduetooverflow)
- [isLastElement](card_elements.container.md#islastelement)
- [isLeftMostElement](card_elements.container.md#isleftmostelement)
- [isRightMostElement](card_elements.container.md#isrightmostelement)
- [isRtl](card_elements.container.md#isrtl)
- [isTopElement](card_elements.container.md#istopelement)
- [overrideInternalRender](card_elements.container.md#overrideinternalrender)
- [parse](card_elements.container.md#parse)
- [populateSchema](card_elements.container.md#populateschema)
- [preProcessPropertyValue](card_elements.container.md#preprocesspropertyvalue)
- [remove](card_elements.container.md#remove)
- [removeItem](card_elements.container.md#removeitem)
- [render](card_elements.container.md#render)
- [resetDefaultValues](card_elements.container.md#resetdefaultvalues)
- [setBleed](card_elements.container.md#setbleed)
- [setCustomProperty](card_elements.container.md#setcustomproperty)
- [setPadding](card_elements.container.md#setpadding)
- [setParent](card_elements.container.md#setparent)
- [setShouldFallback](card_elements.container.md#setshouldfallback)
- [setValue](card_elements.container.md#setvalue)
- [shouldFallback](card_elements.container.md#shouldfallback)
- [shouldSerialize](card_elements.container.md#shouldserialize)
- [supportsExcplitiHeight](card_elements.container.md#supportsexcplitiheight)
- [toJSON](card_elements.container.md#tojson)
- [truncateOverflow](card_elements.container.md#truncateoverflow)
- [undoOverflowTruncation](card_elements.container.md#undooverflowtruncation)
- [updateLayout](card_elements.container.md#updatelayout)
- [validateProperties](card_elements.container.md#validateproperties)

## Constructors

### constructor

\+ **new Container**(): [_Container_](card_elements.container.md)

**Returns:** [_Container_](card_elements.container.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: _undefined_ \| [_CardObject_](card_object.cardobject.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[\_parent](card_elements.stylablecardelementcontainer.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

---

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: _undefined_ \| HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[\_renderedElement](card_elements.stylablecardelementcontainer.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

---

### \_selectAction

• `Protected` `Optional` **\_selectAction**: _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[\_selectAction](card_elements.stylablecardelementcontainer.md#_selectaction)

Defined in: [card-elements.ts:1851](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1851)

---

### allowVerticalOverflow

• **allowVerticalOverflow**: _boolean_= false

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[allowVerticalOverflow](card_elements.stylablecardelementcontainer.md#allowverticaloverflow)

Defined in: [card-elements.ts:1891](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1891)

---

### customCssSelector

• `Optional` **customCssSelector**: _undefined_ \| _string_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[customCssSelector](card_elements.stylablecardelementcontainer.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

---

### height

• **height**: [_CardElementHeight_](../modules/card_elements.md#cardelementheight)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[height](card_elements.stylablecardelementcontainer.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

---

### horizontalAlignment

• **horizontalAlignment**: [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[horizontalAlignment](card_elements.stylablecardelementcontainer.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

---

### id

• `Optional` **id**: _undefined_ \| _string_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[id](card_elements.stylablecardelementcontainer.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

---

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[maxVersion](card_elements.stylablecardelementcontainer.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### minPixelHeight

• `Optional` **minPixelHeight**: _undefined_ \| _number_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[minPixelHeight](card_elements.stylablecardelementcontainer.md#minpixelheight)

Defined in: [card-elements.ts:5068](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5068)

---

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: _undefined_ \| (`sender`: [_CardObject_](card_object.cardobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_) => _any_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[onPreProcessPropertyValue](card_elements.stylablecardelementcontainer.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

---

### rtl

• `Optional` **rtl**: _undefined_ \| _boolean_

Defined in: [card-elements.ts:5334](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5334)

---

### separator

• **separator**: _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[separator](card_elements.stylablecardelementcontainer.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

---

### spacing

• **spacing**: [_Spacing_](../enums/enums.spacing.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[spacing](card_elements.stylablecardelementcontainer.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

---

### verticalContentAlignment

• **verticalContentAlignment**: [_VerticalAlignment_](../enums/enums.verticalalignment.md)

Defined in: [card-elements.ts:5331](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5331)

---

### backgroundImageProperty

▪ `Readonly` `Static` **backgroundImageProperty**: [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

Defined in: [card-elements.ts:5318](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5318)

---

### bleedProperty

▪ `Readonly` `Static` **bleedProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[bleedProperty](card_elements.stylablecardelementcontainer.md#bleedproperty)

Defined in: [card-elements.ts:5044](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5044)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[defaultMaxVersion](card_elements.stylablecardelementcontainer.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [_ValueSetProperty_](serialization.valuesetproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[heightProperty](card_elements.stylablecardelementcontainer.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

---

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)\>

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[horizontalAlignmentProperty](card_elements.stylablecardelementcontainer.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

---

### idProperty

▪ `Readonly` `Static` **idProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[idProperty](card_elements.stylablecardelementcontainer.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

---

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[isVisibleProperty](card_elements.stylablecardelementcontainer.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

---

### langProperty

▪ `Readonly` `Static` **langProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[langProperty](card_elements.stylablecardelementcontainer.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

---

### minHeightProperty

▪ `Readonly` `Static` **minHeightProperty**: [_PixelSizeProperty_](serialization.pixelsizeproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[minHeightProperty](card_elements.stylablecardelementcontainer.md#minheightproperty)

Defined in: [card-elements.ts:5045](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5045)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[onRegisterCustomProperties](card_elements.stylablecardelementcontainer.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[requiresProperty](card_elements.stylablecardelementcontainer.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

---

### rtlProperty

▪ `Readonly` `Static` **rtlProperty**: [_BoolProperty_](serialization.boolproperty.md)

Defined in: [card-elements.ts:5323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5323)

---

### selectActionProperty

▪ `Readonly` `Static` **selectActionProperty**: [_ActionProperty_](card_elements.actionproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[selectActionProperty](card_elements.stylablecardelementcontainer.md#selectactionproperty)

Defined in: [card-elements.ts:1840](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1840)

---

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[separatorProperty](card_elements.stylablecardelementcontainer.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

---

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_Spacing_](../enums/enums.spacing.md)\>

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[spacingProperty](card_elements.stylablecardelementcontainer.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

---

### styleProperty

▪ `Readonly` `Static` **styleProperty**: [_ValueSetProperty_](serialization.valuesetproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[styleProperty](card_elements.stylablecardelementcontainer.md#styleproperty)

Defined in: [card-elements.ts:5033](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5033)

---

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md).[typeNameProperty](card_elements.stylablecardelementcontainer.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

---

### verticalContentAlignmentProperty

▪ `Readonly` `Static` **verticalContentAlignmentProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_VerticalAlignment_](../enums/enums.verticalalignment.md)\>

Defined in: [card-elements.ts:5322](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5322)

## Accessors

### allowCustomPadding

• `Protected`get **allowCustomPadding**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:315](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L315)

---

### allowCustomStyle

• `Protected`get **allowCustomStyle**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5191](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5191)

---

### backgroundImage

• get **backgroundImage**(): [_BackgroundImage_](card_elements.backgroundimage.md)

**Returns:** [_BackgroundImage_](card_elements.backgroundimage.md)

Defined in: [card-elements.ts:5326](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5326)

---

### bleed

• get **bleed**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5705](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5705)

• set **bleed**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Defined in: [card-elements.ts:5709](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5709)

---

### defaultStyle

• `Protected`get **defaultStyle**(): _string_

**Returns:** _string_

Defined in: [card-elements.ts:323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L323)

---

### hasExplicitStyle

• `Protected`get **hasExplicitStyle**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5187](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5187)

---

### hasVisibleSeparator

• get **hasVisibleSeparator**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:596](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L596)

---

### hostConfig

• get **hostConfig**(): [_HostConfig_](host_config.hostconfig.md)

**Returns:** [_HostConfig_](host_config.hostconfig.md)

Defined in: [card-elements.ts:557](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L557)

• set **hostConfig**(`value`: [_HostConfig_](host_config.hostconfig.md)): _void_

#### Parameters:

| Name    | Type                                      |
| :------ | :---------------------------------------- |
| `value` | [_HostConfig_](host_config.hostconfig.md) |

**Returns:** _void_

Defined in: [card-elements.ts:571](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L571)

---

### index

• get **index**(): _number_

**Returns:** _number_

Defined in: [card-elements.ts:575](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L575)

---

### isInline

• get **isInline**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L592)

---

### isInteractive

• get **isInteractive**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:584](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L584)

---

### isSelectable

• `Protected`get **isSelectable**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5528](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5528)

---

### isStandalone

• get **isStandalone**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:588](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L588)

---

### isVisible

• get **isVisible**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:77](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L77)

• set **isVisible**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Defined in: [card-elements.ts:81](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L81)

---

### lang

• get **lang**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [card-elements.ts:56](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L56)

• set **lang**(`value`: _undefined_ \| _string_): _void_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `value` | _undefined_ \| _string_ |

**Returns:** _void_

Defined in: [card-elements.ts:72](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L72)

---

### padding

• get **padding**(): _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

Defined in: [card-elements.ts:5689](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5689)

• set **padding**(`value`: _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)): _void_

#### Parameters:

| Name    | Type                                                              |
| :------ | :---------------------------------------------------------------- |
| `value` | _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md) |

**Returns:** _void_

Defined in: [card-elements.ts:5693](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5693)

---

### parent

• get **parent**(): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Defined in: [card-elements.ts:609](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L609)

---

### renderedActionCount

• `Protected`get **renderedActionCount**(): _number_

**Returns:** _number_

Defined in: [card-elements.ts:5183](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5183)

---

### renderedElement

• get **renderedElement**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Defined in: [card-object.ts:143](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L143)

---

### requires

• get **requires**(): [_HostCapabilities_](host_capabilities.hostcapabilities.md)

**Returns:** [_HostCapabilities_](host_capabilities.hostcapabilities.md)

Defined in: [card-object.ts:56](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L56)

---

### selectAction

• get **selectAction**(): _undefined_ \| [_Action_](card_elements.action.md)

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Defined in: [card-elements.ts:5697](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5697)

• set **selectAction**(`value`: _undefined_ \| [_Action_](card_elements.action.md)): _void_

#### Parameters:

| Name    | Type                                               |
| :------ | :------------------------------------------------- |
| `value` | _undefined_ \| [_Action_](card_elements.action.md) |

**Returns:** _void_

Defined in: [card-elements.ts:5701](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5701)

---

### separatorElement

• get **separatorElement**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Defined in: [card-elements.ts:605](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L605)

---

### separatorOrientation

• `Protected`get **separatorOrientation**(): [_Orientation_](../enums/enums.orientation.md)

**Returns:** [_Orientation_](../enums/enums.orientation.md)

Defined in: [card-elements.ts:319](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L319)

---

### style

• get **style**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [card-elements.ts:5048](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5048)

• set **style**(`value`: _undefined_ \| _string_): _void_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `value` | _undefined_ \| _string_ |

**Returns:** _void_

Defined in: [card-elements.ts:5060](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5060)

---

### useDefaultSizing

• `Protected`get **useDefaultSizing**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L311)

## Methods

### addItem

▸ **addItem**(`item`: [_CardElement_](card_elements.cardelement.md)): _void_

#### Parameters:

| Name   | Type                                          |
| :----- | :-------------------------------------------- |
| `item` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _void_

Defined in: [card-elements.ts:5619](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5619)

---

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): _void_

#### Parameters:

| Name              | Type        |
| :---------------- | :---------- |
| `renderedElement` | HTMLElement |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5072](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5072)

---

### applyBackground

▸ `Protected`**applyBackground**(): _void_

**Returns:** _void_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5373](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5373)

---

### applyPadding

▸ `Protected`**applyPadding**(): _void_

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5092](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5092)

---

### asString

▸ **asString**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L333)

---

### clear

▸ **clear**(): _void_

**Returns:** _void_

Defined in: [card-elements.ts:5647](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5647)

---

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

---

### getActionAt

▸ **getActionAt**(`index`: _number_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L412)

---

### getActionById

▸ **getActionById**(`id`: _string_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5667](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5667)

---

### getActionCount

▸ **getActionCount**(): _number_

**Returns:** _number_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:408](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L408)

---

### getAllInputs

▸ **getAllInputs**(`processActions?`: _boolean_): [_Input_](card_elements.input.md)[]

#### Parameters:

| Name             | Type      | Default value |
| :--------------- | :-------- | :------------ |
| `processActions` | _boolean_ | true          |

**Returns:** [_Input_](card_elements.input.md)[]

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1976](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1976)

---

### getBleed

▸ `Protected`**getBleed**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5175](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5175)

---

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5162](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5162)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

---

### getEffectivePadding

▸ **getEffectivePadding**(): [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

---

### getEffectiveStyle

▸ **getEffectiveStyle**(): _string_

**Returns:** _string_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5226](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5226)

---

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

**Returns:** [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

---

### getElementById

▸ **getElementById**(`id`: _string_): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1996](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1996)

---

### getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5540](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5540)

---

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [_ActionType_](../modules/card_elements.md#actiontype)[]

**Returns:** [_ActionType_](../modules/card_elements.md#actiontype)[]

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

---

### getHasBackground

▸ `Protected`**getHasBackground**(): _boolean_

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5499](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5499)

---

### getHasExpandedAction

▸ `Protected`**getHasExpandedAction**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5171](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5171)

---

### getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [_PaddingDefinition_](shared.paddingdefinition.md), `processTop?`: _boolean_, `processRight?`: _boolean_, `processBottom?`: _boolean_, `processLeft?`: _boolean_): _void_

#### Parameters:

| Name            | Type                                               | Default value |
| :-------------- | :------------------------------------------------- | :------------ |
| `result`        | [_PaddingDefinition_](shared.paddingdefinition.md) | -             |
| `processTop`    | _boolean_                                          | true          |
| `processRight`  | _boolean_                                          | true          |
| `processBottom` | _boolean_                                          | true          |
| `processLeft`   | _boolean_                                          | true          |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

---

### getItemAt

▸ **getItemAt**(`index`: _number_): [_CardElement_](card_elements.cardelement.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_CardElement_](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5536](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5536)

---

### getItemCount

▸ **getItemCount**(): _number_

**Returns:** _number_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5532](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5532)

---

### getItemsCollectionPropertyName

▸ `Protected`**getItemsCollectionPropertyName**(): _string_

**Returns:** _string_

Defined in: [card-elements.ts:5369](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5369)

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

**Returns:** _string_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5564](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5564)

---

### getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5552](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5552)

---

### getPadding

▸ `Protected`**getPadding**(): _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

---

### getParentContainer

▸ **getParentContainer**(): _undefined_ \| [_Container_](card_elements.container.md)

**Returns:** _undefined_ \| [_Container_](card_elements.container.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

---

### getResourceInformation

▸ **getResourceInformation**(): [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5652](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5652)

---

### getRootElement

▸ **getRootElement**(): [_CardElement_](card_elements.cardelement.md)

**Returns:** [_CardElement_](card_elements.cardelement.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

---

### getRootObject

▸ **getRootObject**(): [_CardObject_](card_object.cardobject.md)

**Returns:** [_CardObject_](card_object.cardobject.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected`**getSchemaKey**(): _string_

**Returns:** _string_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### indexOf

▸ **indexOf**(`cardElement`: [_CardElement_](card_elements.cardelement.md)): _number_

#### Parameters:

| Name          | Type                                          |
| :------------ | :-------------------------------------------- |
| `cardElement` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _number_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5615](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5615)

---

### insertItemAfter

▸ **insertItemAfter**(`item`: [_CardElement_](card_elements.cardelement.md), `insertAfter`: [_CardElement_](card_elements.cardelement.md)): _void_

#### Parameters:

| Name          | Type                                          |
| :------------ | :-------------------------------------------- |
| `item`        | [_CardElement_](card_elements.cardelement.md) |
| `insertAfter` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _void_

Defined in: [card-elements.ts:5627](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5627)

---

### insertItemBefore

▸ **insertItemBefore**(`item`: [_CardElement_](card_elements.cardelement.md), `insertBefore`: [_CardElement_](card_elements.cardelement.md)): _void_

#### Parameters:

| Name           | Type                                          |
| :------------- | :-------------------------------------------- |
| `item`         | [_CardElement_](card_elements.cardelement.md) |
| `insertBefore` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _void_

Defined in: [card-elements.ts:5623](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5623)

---

### internalParse

▸ `Protected`**internalParse**(`source`: _any_, `context`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `source`  | _any_                                                           |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5503](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5503)

---

### internalRender

▸ `Protected`**internalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5381](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5381)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)        |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5522](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5522)

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [_ValidationResults_](card_object.validationresults.md)): _void_

#### Parameters:

| Name      | Type                                                    |
| :-------- | :------------------------------------------------------ |
| `context` | [_ValidationResults_](card_object.validationresults.md) |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5199](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5199)

---

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

---

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

---

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

---

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

---

### isBleeding

▸ **isBleeding**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5195](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5195)

---

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): _boolean_

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5609](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5609)

---

### isBleedingAtTop

▸ **isBleedingAtTop**(): _boolean_

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5603](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5603)

---

### isBottomElement

▸ **isBottomElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

---

### isDesignMode

▸ **isDesignMode**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

---

### isDisplayed

▸ `Protected`**isDisplayed**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

---

### isElementAllowed

▸ `Protected`**isElementAllowed**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1855](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1855)

---

### isFirstElement

▸ **isFirstElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5568](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5568)

---

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

---

### isLastElement

▸ **isLastElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5580](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5580)

---

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

---

### isRightMostElement

▸ **isRightMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

---

### isRtl

▸ **isRtl**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5592)

---

### isTopElement

▸ **isTopElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

---

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:251](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L251)

---

### parse

▸ **parse**(`source`: _any_, `context?`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                            |
| :--------- | :-------------------------------------------------------------- |
| `source`   | _any_                                                           |
| `context?` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1842](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1842)

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `propertyValue?`: _any_): _any_

#### Parameters:

| Name             | Type                                                        |
| :--------------- | :---------------------------------------------------------- |
| `property`       | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `propertyValue?` | _any_                                                       |

**Returns:** _any_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

---

### remove

▸ **remove**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

---

### removeItem

▸ **removeItem**(`item`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name   | Type                                          |
| :----- | :-------------------------------------------- |
| `item` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5631](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5631)

---

### render

▸ **render**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5216](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5216)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

---

### setBleed

▸ `Protected`**setBleed**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5179](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5179)

---

### setCustomProperty

▸ **setCustomProperty**(`name`: _string_, `value`: _any_): _void_

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `name`  | _string_ |
| `value` | _any_    |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setPadding

▸ `Protected`**setPadding**(`value`: _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)): _void_

#### Parameters:

| Name    | Type                                                              |
| :------ | :---------------------------------------------------------------- |
| `value` | _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md) |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

---

### setParent

▸ **setParent**(`value`: _undefined_ \| [_CardObject_](card_object.cardobject.md)): _void_

#### Parameters:

| Name    | Type                                                     |
| :------ | :------------------------------------------------------- |
| `value` | _undefined_ \| [_CardObject_](card_object.cardobject.md) |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

---

### setShouldFallback

▸ **setShouldFallback**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:95](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L95)

---

### setValue

▸ `Protected`**setValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_): _void_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `value`    | _any_                                                       |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_SerializationContext_](card_elements.serializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _boolean_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

---

### supportsExcplitiHeight

▸ `Protected`**supportsExcplitiHeight**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:5365](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5365)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

---

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: _number_): _boolean_

#### Parameters:

| Name        | Type     |
| :---------- | :------- |
| `maxHeight` | _number_ |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5454](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5454)

---

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): _void_

**Returns:** _void_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5493)

---

### updateLayout

▸ **updateLayout**(`processChildren?`: _boolean_): _void_

#### Parameters:

| Name              | Type      | Default value |
| :---------------- | :-------- | :------------ |
| `processChildren` | _boolean_ | true          |

**Returns:** _void_

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1966](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1966)

---

### validateProperties

▸ **validateProperties**(): [_ValidationResults_](card_object.validationresults.md)

**Returns:** [_ValidationResults_](card_object.validationresults.md)

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
