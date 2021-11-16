[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / ColumnSet

# Class: ColumnSet

[card-elements](../modules/card_elements.md).ColumnSet

## Hierarchy

- [_StylableCardElementContainer_](card_elements.stylablecardelementcontainer.md)

  ↳ **ColumnSet**

## Table of contents

### Constructors

- [constructor](card_elements.columnset.md#constructor)

### Properties

- [\_parent](card_elements.columnset.md#_parent)
- [\_renderedElement](card_elements.columnset.md#_renderedelement)
- [\_selectAction](card_elements.columnset.md#_selectaction)
- [allowVerticalOverflow](card_elements.columnset.md#allowverticaloverflow)
- [customCssSelector](card_elements.columnset.md#customcssselector)
- [height](card_elements.columnset.md#height)
- [horizontalAlignment](card_elements.columnset.md#horizontalalignment)
- [id](card_elements.columnset.md#id)
- [maxVersion](card_elements.columnset.md#maxversion)
- [minPixelHeight](card_elements.columnset.md#minpixelheight)
- [onPreProcessPropertyValue](card_elements.columnset.md#onpreprocesspropertyvalue)
- [separator](card_elements.columnset.md#separator)
- [spacing](card_elements.columnset.md#spacing)
- [bleedProperty](card_elements.columnset.md#bleedproperty)
- [defaultMaxVersion](card_elements.columnset.md#defaultmaxversion)
- [heightProperty](card_elements.columnset.md#heightproperty)
- [horizontalAlignmentProperty](card_elements.columnset.md#horizontalalignmentproperty)
- [idProperty](card_elements.columnset.md#idproperty)
- [isVisibleProperty](card_elements.columnset.md#isvisibleproperty)
- [langProperty](card_elements.columnset.md#langproperty)
- [minHeightProperty](card_elements.columnset.md#minheightproperty)
- [onRegisterCustomProperties](card_elements.columnset.md#onregistercustomproperties)
- [requiresProperty](card_elements.columnset.md#requiresproperty)
- [selectActionProperty](card_elements.columnset.md#selectactionproperty)
- [separatorProperty](card_elements.columnset.md#separatorproperty)
- [spacingProperty](card_elements.columnset.md#spacingproperty)
- [styleProperty](card_elements.columnset.md#styleproperty)
- [typeNameProperty](card_elements.columnset.md#typenameproperty)

### Accessors

- [allowCustomPadding](card_elements.columnset.md#allowcustompadding)
- [allowCustomStyle](card_elements.columnset.md#allowcustomstyle)
- [bleed](card_elements.columnset.md#bleed)
- [defaultStyle](card_elements.columnset.md#defaultstyle)
- [hasExplicitStyle](card_elements.columnset.md#hasexplicitstyle)
- [hasVisibleSeparator](card_elements.columnset.md#hasvisibleseparator)
- [hostConfig](card_elements.columnset.md#hostconfig)
- [index](card_elements.columnset.md#index)
- [isInline](card_elements.columnset.md#isinline)
- [isInteractive](card_elements.columnset.md#isinteractive)
- [isSelectable](card_elements.columnset.md#isselectable)
- [isStandalone](card_elements.columnset.md#isstandalone)
- [isVisible](card_elements.columnset.md#isvisible)
- [lang](card_elements.columnset.md#lang)
- [padding](card_elements.columnset.md#padding)
- [parent](card_elements.columnset.md#parent)
- [renderedActionCount](card_elements.columnset.md#renderedactioncount)
- [renderedElement](card_elements.columnset.md#renderedelement)
- [requires](card_elements.columnset.md#requires)
- [selectAction](card_elements.columnset.md#selectaction)
- [separatorElement](card_elements.columnset.md#separatorelement)
- [separatorOrientation](card_elements.columnset.md#separatororientation)
- [style](card_elements.columnset.md#style)
- [useDefaultSizing](card_elements.columnset.md#usedefaultsizing)

### Methods

- [addColumn](card_elements.columnset.md#addcolumn)
- [adjustRenderedElementSize](card_elements.columnset.md#adjustrenderedelementsize)
- [applyBackground](card_elements.columnset.md#applybackground)
- [applyPadding](card_elements.columnset.md#applypadding)
- [asString](card_elements.columnset.md#asstring)
- [createPlaceholderElement](card_elements.columnset.md#createplaceholderelement)
- [getActionAt](card_elements.columnset.md#getactionat)
- [getActionById](card_elements.columnset.md#getactionbyid)
- [getActionCount](card_elements.columnset.md#getactioncount)
- [getAllInputs](card_elements.columnset.md#getallinputs)
- [getBleed](card_elements.columnset.md#getbleed)
- [getColumnAt](card_elements.columnset.md#getcolumnat)
- [getCustomProperty](card_elements.columnset.md#getcustomproperty)
- [getDefaultPadding](card_elements.columnset.md#getdefaultpadding)
- [getDefaultSerializationContext](card_elements.columnset.md#getdefaultserializationcontext)
- [getEffectivePadding](card_elements.columnset.md#geteffectivepadding)
- [getEffectiveStyle](card_elements.columnset.md#geteffectivestyle)
- [getEffectiveStyleDefinition](card_elements.columnset.md#geteffectivestyledefinition)
- [getElementById](card_elements.columnset.md#getelementbyid)
- [getFirstVisibleRenderedItem](card_elements.columnset.md#getfirstvisiblerendereditem)
- [getForbiddenActionTypes](card_elements.columnset.md#getforbiddenactiontypes)
- [getHasBackground](card_elements.columnset.md#gethasbackground)
- [getHasExpandedAction](card_elements.columnset.md#gethasexpandedaction)
- [getImmediateSurroundingPadding](card_elements.columnset.md#getimmediatesurroundingpadding)
- [getItemAt](card_elements.columnset.md#getitemat)
- [getItemCount](card_elements.columnset.md#getitemcount)
- [getJsonTypeName](card_elements.columnset.md#getjsontypename)
- [getLastVisibleRenderedItem](card_elements.columnset.md#getlastvisiblerendereditem)
- [getPadding](card_elements.columnset.md#getpadding)
- [getParentContainer](card_elements.columnset.md#getparentcontainer)
- [getResourceInformation](card_elements.columnset.md#getresourceinformation)
- [getRootElement](card_elements.columnset.md#getrootelement)
- [getRootObject](card_elements.columnset.md#getrootobject)
- [getSchema](card_elements.columnset.md#getschema)
- [getSchemaKey](card_elements.columnset.md#getschemakey)
- [getValue](card_elements.columnset.md#getvalue)
- [hasAllDefaultValues](card_elements.columnset.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.columnset.md#hasdefaultvalue)
- [indexOf](card_elements.columnset.md#indexof)
- [internalParse](card_elements.columnset.md#internalparse)
- [internalRender](card_elements.columnset.md#internalrender)
- [internalToJSON](card_elements.columnset.md#internaltojson)
- [internalValidateProperties](card_elements.columnset.md#internalvalidateproperties)
- [isAtTheVeryBottom](card_elements.columnset.md#isattheverybottom)
- [isAtTheVeryLeft](card_elements.columnset.md#isattheveryleft)
- [isAtTheVeryRight](card_elements.columnset.md#isattheveryright)
- [isAtTheVeryTop](card_elements.columnset.md#isattheverytop)
- [isBleeding](card_elements.columnset.md#isbleeding)
- [isBleedingAtBottom](card_elements.columnset.md#isbleedingatbottom)
- [isBleedingAtTop](card_elements.columnset.md#isbleedingattop)
- [isBottomElement](card_elements.columnset.md#isbottomelement)
- [isDesignMode](card_elements.columnset.md#isdesignmode)
- [isDisplayed](card_elements.columnset.md#isdisplayed)
- [isElementAllowed](card_elements.columnset.md#iselementallowed)
- [isFirstElement](card_elements.columnset.md#isfirstelement)
- [isHiddenDueToOverflow](card_elements.columnset.md#ishiddenduetooverflow)
- [isLastElement](card_elements.columnset.md#islastelement)
- [isLeftMostElement](card_elements.columnset.md#isleftmostelement)
- [isRightMostElement](card_elements.columnset.md#isrightmostelement)
- [isTopElement](card_elements.columnset.md#istopelement)
- [overrideInternalRender](card_elements.columnset.md#overrideinternalrender)
- [parse](card_elements.columnset.md#parse)
- [populateSchema](card_elements.columnset.md#populateschema)
- [preProcessPropertyValue](card_elements.columnset.md#preprocesspropertyvalue)
- [remove](card_elements.columnset.md#remove)
- [removeItem](card_elements.columnset.md#removeitem)
- [render](card_elements.columnset.md#render)
- [resetDefaultValues](card_elements.columnset.md#resetdefaultvalues)
- [setBleed](card_elements.columnset.md#setbleed)
- [setCustomProperty](card_elements.columnset.md#setcustomproperty)
- [setPadding](card_elements.columnset.md#setpadding)
- [setParent](card_elements.columnset.md#setparent)
- [setShouldFallback](card_elements.columnset.md#setshouldfallback)
- [setValue](card_elements.columnset.md#setvalue)
- [shouldFallback](card_elements.columnset.md#shouldfallback)
- [shouldSerialize](card_elements.columnset.md#shouldserialize)
- [toJSON](card_elements.columnset.md#tojson)
- [truncateOverflow](card_elements.columnset.md#truncateoverflow)
- [undoOverflowTruncation](card_elements.columnset.md#undooverflowtruncation)
- [updateLayout](card_elements.columnset.md#updatelayout)
- [validateProperties](card_elements.columnset.md#validateproperties)

## Constructors

### constructor

\+ **new ColumnSet**(): [_ColumnSet_](card_elements.columnset.md)

**Returns:** [_ColumnSet_](card_elements.columnset.md)

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

### bleed

• get **bleed**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:6138](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6138)

• set **bleed**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Defined in: [card-elements.ts:6142](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6142)

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

Defined in: [card-elements.ts:5947](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5947)

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

Defined in: [card-elements.ts:6146](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6146)

• set **padding**(`value`: _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)): _void_

#### Parameters:

| Name    | Type                                                              |
| :------ | :---------------------------------------------------------------- |
| `value` | _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md) |

**Returns:** _void_

Defined in: [card-elements.ts:6150](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6150)

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

Defined in: [card-elements.ts:6154](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6154)

• set **selectAction**(`value`: _undefined_ \| [_Action_](card_elements.action.md)): _void_

#### Parameters:

| Name    | Type                                               |
| :------ | :------------------------------------------------- |
| `value` | _undefined_ \| [_Action_](card_elements.action.md) |

**Returns:** _void_

Defined in: [card-elements.ts:6158](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6158)

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

### addColumn

▸ **addColumn**(`column`: [_Column_](card_elements.column.md)): _void_

#### Parameters:

| Name     | Type                                |
| :------- | :---------------------------------- |
| `column` | [_Column_](card_elements.column.md) |

**Returns:** _void_

Defined in: [card-elements.ts:6075](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6075)

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

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5080](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5080)

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

Defined in: [card-elements.ts:6124](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6124)

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

### getColumnAt

▸ **getColumnAt**(`index`: _number_): [_Column_](card_elements.column.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_Column_](card_elements.column.md)

Defined in: [card-elements.ts:6040](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6040)

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

Defined in: [card-elements.ts:6022](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6022)

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

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5144](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5144)

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

Defined in: [card-elements.ts:6044](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6044)

---

### getItemCount

▸ **getItemCount**(): _number_

**Returns:** _number_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6018](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6018)

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

**Returns:** _string_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6048](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6048)

---

### getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6031](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6031)

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

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:1986](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1986)

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

Defined in: [card-elements.ts:6104](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6104)

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

Defined in: [card-elements.ts:5951](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5951)

---

### internalRender

▸ `Protected`**internalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5867](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5867)

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

Defined in: [card-elements.ts:5970](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5970)

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [_ValidationResults_](card_object.validationresults.md)): _void_

#### Parameters:

| Name      | Type                                                    |
| :-------- | :------------------------------------------------------ |
| `context` | [_ValidationResults_](card_object.validationresults.md) |

**Returns:** _void_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6052](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6052)

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

Defined in: [card-elements.ts:6002](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6002)

---

### isBleedingAtTop

▸ **isBleedingAtTop**(): _boolean_

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5986](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5986)

---

### isBottomElement

▸ **isBottomElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6120](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6120)

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

Defined in: [card-elements.ts:5976](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5976)

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

Inherited from: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L469)

---

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6108](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6108)

---

### isRightMostElement

▸ **isRightMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6112](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6112)

---

### isTopElement

▸ **isTopElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:6116](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6116)

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

Defined in: [card-elements.ts:6086](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L6086)

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

Defined in: [card-elements.ts:5933](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5933)

---

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): _void_

**Returns:** _void_

Overrides: [StylableCardElementContainer](card_elements.stylablecardelementcontainer.md)

Defined in: [card-elements.ts:5941](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L5941)

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
