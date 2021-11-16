[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / TextBlock

# Class: TextBlock

[adaptivecards](../modules/adaptivecards.md).TextBlock

## Hierarchy

- [_BaseTextBlock_](card_elements.basetextblock.md)

  ↳ **TextBlock**

## Table of contents

### Constructors

- [constructor](adaptivecards.textblock.md#constructor)

### Properties

- [\_parent](adaptivecards.textblock.md#_parent)
- [\_renderedElement](adaptivecards.textblock.md#_renderedelement)
- [ariaHidden](adaptivecards.textblock.md#ariahidden)
- [color](adaptivecards.textblock.md#color)
- [customCssSelector](adaptivecards.textblock.md#customcssselector)
- [fontType](adaptivecards.textblock.md#fonttype)
- [forElementId](adaptivecards.textblock.md#forelementid)
- [height](adaptivecards.textblock.md#height)
- [horizontalAlignment](adaptivecards.textblock.md#horizontalalignment)
- [id](adaptivecards.textblock.md#id)
- [isSubtle](adaptivecards.textblock.md#issubtle)
- [maxLines](adaptivecards.textblock.md#maxlines)
- [maxVersion](adaptivecards.textblock.md#maxversion)
- [onPreProcessPropertyValue](adaptivecards.textblock.md#onpreprocesspropertyvalue)
- [selectAction](adaptivecards.textblock.md#selectaction)
- [separator](adaptivecards.textblock.md#separator)
- [size](adaptivecards.textblock.md#size)
- [spacing](adaptivecards.textblock.md#spacing)
- [useMarkdown](adaptivecards.textblock.md#usemarkdown)
- [weight](adaptivecards.textblock.md#weight)
- [wrap](adaptivecards.textblock.md#wrap)
- [colorProperty](adaptivecards.textblock.md#colorproperty)
- [defaultMaxVersion](adaptivecards.textblock.md#defaultmaxversion)
- [fontTypeProperty](adaptivecards.textblock.md#fonttypeproperty)
- [heightProperty](adaptivecards.textblock.md#heightproperty)
- [horizontalAlignmentProperty](adaptivecards.textblock.md#horizontalalignmentproperty)
- [idProperty](adaptivecards.textblock.md#idproperty)
- [isSubtleProperty](adaptivecards.textblock.md#issubtleproperty)
- [isVisibleProperty](adaptivecards.textblock.md#isvisibleproperty)
- [langProperty](adaptivecards.textblock.md#langproperty)
- [maxLinesProperty](adaptivecards.textblock.md#maxlinesproperty)
- [onRegisterCustomProperties](adaptivecards.textblock.md#onregistercustomproperties)
- [requiresProperty](adaptivecards.textblock.md#requiresproperty)
- [selectActionProperty](adaptivecards.textblock.md#selectactionproperty)
- [separatorProperty](adaptivecards.textblock.md#separatorproperty)
- [sizeProperty](adaptivecards.textblock.md#sizeproperty)
- [spacingProperty](adaptivecards.textblock.md#spacingproperty)
- [textProperty](adaptivecards.textblock.md#textproperty)
- [typeNameProperty](adaptivecards.textblock.md#typenameproperty)
- [weightProperty](adaptivecards.textblock.md#weightproperty)
- [wrapProperty](adaptivecards.textblock.md#wrapproperty)

### Accessors

- [allowCustomPadding](adaptivecards.textblock.md#allowcustompadding)
- [defaultStyle](adaptivecards.textblock.md#defaultstyle)
- [effectiveColor](adaptivecards.textblock.md#effectivecolor)
- [hasVisibleSeparator](adaptivecards.textblock.md#hasvisibleseparator)
- [hostConfig](adaptivecards.textblock.md#hostconfig)
- [index](adaptivecards.textblock.md#index)
- [isInline](adaptivecards.textblock.md#isinline)
- [isInteractive](adaptivecards.textblock.md#isinteractive)
- [isStandalone](adaptivecards.textblock.md#isstandalone)
- [isVisible](adaptivecards.textblock.md#isvisible)
- [lang](adaptivecards.textblock.md#lang)
- [parent](adaptivecards.textblock.md#parent)
- [renderedElement](adaptivecards.textblock.md#renderedelement)
- [requires](adaptivecards.textblock.md#requires)
- [separatorElement](adaptivecards.textblock.md#separatorelement)
- [separatorOrientation](adaptivecards.textblock.md#separatororientation)
- [text](adaptivecards.textblock.md#text)
- [useDefaultSizing](adaptivecards.textblock.md#usedefaultsizing)

### Methods

- [adjustRenderedElementSize](adaptivecards.textblock.md#adjustrenderedelementsize)
- [applyPadding](adaptivecards.textblock.md#applypadding)
- [applyStylesTo](adaptivecards.textblock.md#applystylesto)
- [asString](adaptivecards.textblock.md#asstring)
- [createPlaceholderElement](adaptivecards.textblock.md#createplaceholderelement)
- [getActionAt](adaptivecards.textblock.md#getactionat)
- [getActionById](adaptivecards.textblock.md#getactionbyid)
- [getActionCount](adaptivecards.textblock.md#getactioncount)
- [getAllInputs](adaptivecards.textblock.md#getallinputs)
- [getColorDefinition](adaptivecards.textblock.md#getcolordefinition)
- [getCustomProperty](adaptivecards.textblock.md#getcustomproperty)
- [getDefaultPadding](adaptivecards.textblock.md#getdefaultpadding)
- [getDefaultSerializationContext](adaptivecards.textblock.md#getdefaultserializationcontext)
- [getEffectivePadding](adaptivecards.textblock.md#geteffectivepadding)
- [getEffectiveStyle](adaptivecards.textblock.md#geteffectivestyle)
- [getEffectiveStyleDefinition](adaptivecards.textblock.md#geteffectivestyledefinition)
- [getElementById](adaptivecards.textblock.md#getelementbyid)
- [getFontSize](adaptivecards.textblock.md#getfontsize)
- [getForbiddenActionTypes](adaptivecards.textblock.md#getforbiddenactiontypes)
- [getHasBackground](adaptivecards.textblock.md#gethasbackground)
- [getImmediateSurroundingPadding](adaptivecards.textblock.md#getimmediatesurroundingpadding)
- [getJsonTypeName](adaptivecards.textblock.md#getjsontypename)
- [getPadding](adaptivecards.textblock.md#getpadding)
- [getParentContainer](adaptivecards.textblock.md#getparentcontainer)
- [getResourceInformation](adaptivecards.textblock.md#getresourceinformation)
- [getRootElement](adaptivecards.textblock.md#getrootelement)
- [getRootObject](adaptivecards.textblock.md#getrootobject)
- [getSchema](adaptivecards.textblock.md#getschema)
- [getSchemaKey](adaptivecards.textblock.md#getschemakey)
- [getValue](adaptivecards.textblock.md#getvalue)
- [hasAllDefaultValues](adaptivecards.textblock.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.textblock.md#hasdefaultvalue)
- [indexOf](adaptivecards.textblock.md#indexof)
- [init](adaptivecards.textblock.md#init)
- [internalParse](adaptivecards.textblock.md#internalparse)
- [internalRender](adaptivecards.textblock.md#internalrender)
- [internalToJSON](adaptivecards.textblock.md#internaltojson)
- [internalValidateProperties](adaptivecards.textblock.md#internalvalidateproperties)
- [isAtTheVeryBottom](adaptivecards.textblock.md#isattheverybottom)
- [isAtTheVeryLeft](adaptivecards.textblock.md#isattheveryleft)
- [isAtTheVeryRight](adaptivecards.textblock.md#isattheveryright)
- [isAtTheVeryTop](adaptivecards.textblock.md#isattheverytop)
- [isBleeding](adaptivecards.textblock.md#isbleeding)
- [isBleedingAtBottom](adaptivecards.textblock.md#isbleedingatbottom)
- [isBleedingAtTop](adaptivecards.textblock.md#isbleedingattop)
- [isBottomElement](adaptivecards.textblock.md#isbottomelement)
- [isDesignMode](adaptivecards.textblock.md#isdesignmode)
- [isDisplayed](adaptivecards.textblock.md#isdisplayed)
- [isFirstElement](adaptivecards.textblock.md#isfirstelement)
- [isHiddenDueToOverflow](adaptivecards.textblock.md#ishiddenduetooverflow)
- [isLastElement](adaptivecards.textblock.md#islastelement)
- [isLeftMostElement](adaptivecards.textblock.md#isleftmostelement)
- [isRightMostElement](adaptivecards.textblock.md#isrightmostelement)
- [isTopElement](adaptivecards.textblock.md#istopelement)
- [overrideInternalRender](adaptivecards.textblock.md#overrideinternalrender)
- [parse](adaptivecards.textblock.md#parse)
- [populateSchema](adaptivecards.textblock.md#populateschema)
- [preProcessPropertyValue](adaptivecards.textblock.md#preprocesspropertyvalue)
- [remove](adaptivecards.textblock.md#remove)
- [render](adaptivecards.textblock.md#render)
- [resetDefaultValues](adaptivecards.textblock.md#resetdefaultvalues)
- [setCustomProperty](adaptivecards.textblock.md#setcustomproperty)
- [setPadding](adaptivecards.textblock.md#setpadding)
- [setParent](adaptivecards.textblock.md#setparent)
- [setShouldFallback](adaptivecards.textblock.md#setshouldfallback)
- [setText](adaptivecards.textblock.md#settext)
- [setValue](adaptivecards.textblock.md#setvalue)
- [shouldFallback](adaptivecards.textblock.md#shouldfallback)
- [shouldSerialize](adaptivecards.textblock.md#shouldserialize)
- [toJSON](adaptivecards.textblock.md#tojson)
- [truncateOverflow](adaptivecards.textblock.md#truncateoverflow)
- [undoOverflowTruncation](adaptivecards.textblock.md#undooverflowtruncation)
- [updateLayout](adaptivecards.textblock.md#updatelayout)
- [validateProperties](adaptivecards.textblock.md#validateproperties)

## Constructors

### constructor

\+ **new TextBlock**(`text?`: _string_): [_TextBlock_](card_elements.textblock.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `text?` | _string_ |

**Returns:** [_TextBlock_](card_elements.textblock.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:744](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L744)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: _undefined_ \| [_CardObject_](card_object.cardobject.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[\_parent](card_elements.basetextblock.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

---

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: _undefined_ \| HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[\_renderedElement](card_elements.basetextblock.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

---

### ariaHidden

• **ariaHidden**: _boolean_= false

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[ariaHidden](card_elements.basetextblock.md#ariahidden)

Defined in: [card-elements.ts:744](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L744)

---

### color

• **color**: [_TextColor_](../enums/enums.textcolor.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[color](card_elements.basetextblock.md#color)

Defined in: [card-elements.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L684)

---

### customCssSelector

• `Optional` **customCssSelector**: _undefined_ \| _string_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[customCssSelector](card_elements.basetextblock.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

---

### fontType

• `Optional` **fontType**: _undefined_ \| [_Default_](../enums/enums.fonttype.md#default) \| [_Monospace_](../enums/enums.fonttype.md#monospace)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[fontType](card_elements.basetextblock.md#fonttype)

Defined in: [card-elements.ts:687](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L687)

---

### forElementId

• `Optional` **forElementId**: _undefined_ \| _string_

Defined in: [card-elements.ts:1069](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1069)

---

### height

• **height**: [_CardElementHeight_](../modules/card_elements.md#cardelementheight)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[height](card_elements.basetextblock.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

---

### horizontalAlignment

• **horizontalAlignment**: [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[horizontalAlignment](card_elements.basetextblock.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

---

### id

• `Optional` **id**: _undefined_ \| _string_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[id](card_elements.basetextblock.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

---

### isSubtle

• **isSubtle**: _boolean_= false

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[isSubtle](card_elements.basetextblock.md#issubtle)

Defined in: [card-elements.ts:690](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L690)

---

### maxLines

• `Optional` **maxLines**: _undefined_ \| _number_

Defined in: [card-elements.ts:834](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L834)

---

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[maxVersion](card_elements.basetextblock.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: _undefined_ \| (`sender`: [_CardObject_](card_object.cardobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_) => _any_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[onPreProcessPropertyValue](card_elements.basetextblock.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

---

### selectAction

• `Optional` **selectAction**: _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[selectAction](card_elements.basetextblock.md#selectaction)

Defined in: [card-elements.ts:702](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L702)

---

### separator

• **separator**: _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[separator](card_elements.basetextblock.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

---

### size

• **size**: [_TextSize_](../enums/enums.textsize.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[size](card_elements.basetextblock.md#size)

Defined in: [card-elements.ts:678](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L678)

---

### spacing

• **spacing**: [_Spacing_](../enums/enums.spacing.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[spacing](card_elements.basetextblock.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

---

### useMarkdown

• **useMarkdown**: _boolean_= true

Defined in: [card-elements.ts:1068](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1068)

---

### weight

• **weight**: [_TextWeight_](../enums/enums.textweight.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[weight](card_elements.basetextblock.md#weight)

Defined in: [card-elements.ts:681](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L681)

---

### wrap

• **wrap**: _boolean_= false

Defined in: [card-elements.ts:831](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L831)

---

### colorProperty

▪ `Readonly` `Static` **colorProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_TextColor_](../enums/enums.textcolor.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[colorProperty](card_elements.basetextblock.md#colorproperty)

Defined in: [card-elements.ts:654](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L654)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[defaultMaxVersion](card_elements.basetextblock.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### fontTypeProperty

▪ `Readonly` `Static` **fontTypeProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_FontType_](../enums/enums.fonttype.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[fontTypeProperty](card_elements.basetextblock.md#fonttypeproperty)

Defined in: [card-elements.ts:663](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L663)

---

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [_ValueSetProperty_](serialization.valuesetproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[heightProperty](card_elements.basetextblock.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

---

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[horizontalAlignmentProperty](card_elements.basetextblock.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

---

### idProperty

▪ `Readonly` `Static` **idProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[idProperty](card_elements.basetextblock.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

---

### isSubtleProperty

▪ `Readonly` `Static` **isSubtleProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[isSubtleProperty](card_elements.basetextblock.md#issubtleproperty)

Defined in: [card-elements.ts:659](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L659)

---

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[isVisibleProperty](card_elements.basetextblock.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

---

### langProperty

▪ `Readonly` `Static` **langProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[langProperty](card_elements.basetextblock.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

---

### maxLinesProperty

▪ `Readonly` `Static` **maxLinesProperty**: [_NumProperty_](serialization.numproperty.md)

Defined in: [card-elements.ts:828](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L828)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[onRegisterCustomProperties](card_elements.basetextblock.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[requiresProperty](card_elements.basetextblock.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

---

### selectActionProperty

▪ `Readonly` `Static` **selectActionProperty**: [_ActionProperty_](card_elements.actionproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[selectActionProperty](card_elements.basetextblock.md#selectactionproperty)

Defined in: [card-elements.ts:667](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L667)

---

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[separatorProperty](card_elements.basetextblock.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

---

### sizeProperty

▪ `Readonly` `Static` **sizeProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_TextSize_](../enums/enums.textsize.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[sizeProperty](card_elements.basetextblock.md#sizeproperty)

Defined in: [card-elements.ts:644](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L644)

---

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_Spacing_](../enums/enums.spacing.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[spacingProperty](card_elements.basetextblock.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

---

### textProperty

▪ `Readonly` `Static` **textProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[textProperty](card_elements.basetextblock.md#textproperty)

Defined in: [card-elements.ts:640](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L640)

---

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[typeNameProperty](card_elements.basetextblock.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

---

### weightProperty

▪ `Readonly` `Static` **weightProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_TextWeight_](../enums/enums.textweight.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[weightProperty](card_elements.basetextblock.md#weightproperty)

Defined in: [card-elements.ts:649](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L649)

---

### wrapProperty

▪ `Readonly` `Static` **wrapProperty**: [_BoolProperty_](serialization.boolproperty.md)

Defined in: [card-elements.ts:827](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L827)

## Accessors

### allowCustomPadding

• `Protected`get **allowCustomPadding**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:315](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L315)

---

### defaultStyle

• `Protected`get **defaultStyle**(): _string_

**Returns:** _string_

Defined in: [card-elements.ts:323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L323)

---

### effectiveColor

• get **effectiveColor**(): [_TextColor_](../enums/enums.textcolor.md)

**Returns:** [_TextColor_](../enums/enums.textcolor.md)

Defined in: [card-elements.ts:819](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L819)

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

### parent

• get **parent**(): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Defined in: [card-elements.ts:609](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L609)

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

### text

• get **text**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [card-elements.ts:693](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L693)

• set **text**(`value`: _undefined_ \| _string_): _void_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `value` | _undefined_ \| _string_ |

**Returns:** _void_

Defined in: [card-elements.ts:697](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L697)

---

### useDefaultSizing

• `Protected`get **useDefaultSizing**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L311)

## Methods

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): _void_

#### Parameters:

| Name              | Type        |
| :---------------- | :---------- |
| `renderedElement` | HTMLElement |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L236)

---

### applyPadding

▸ `Protected`**applyPadding**(): _void_

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L255)

---

### applyStylesTo

▸ **applyStylesTo**(`targetElement`: HTMLElement): _void_

#### Parameters:

| Name            | Type        |
| :-------------- | :---------- |
| `targetElement` | HTMLElement |

**Returns:** _void_

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1071](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1071)

---

### asString

▸ **asString**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:761](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L761)

---

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

---

### getActionAt

▸ **getActionAt**(`index`: _number_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L412)

---

### getActionById

▸ **getActionById**(`id`: _string_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:547](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L547)

---

### getActionCount

▸ **getActionCount**(): _number_

**Returns:** _number_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:408](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L408)

---

### getAllInputs

▸ **getAllInputs**(`processActions?`: _boolean_): [_Input_](card_elements.input.md)[]

#### Parameters:

| Name             | Type      | Default value |
| :--------------- | :-------- | :------------ |
| `processActions` | _boolean_ | true          |

**Returns:** [_Input_](card_elements.input.md)[]

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:535](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L535)

---

### getColorDefinition

▸ `Protected`**getColorDefinition**(`colorSet`: [_ColorSetDefinition_](host_config.colorsetdefinition.md), `color`: [_TextColor_](../enums/enums.textcolor.md)): [_TextColorDefinition_](host_config.textcolordefinition.md)

#### Parameters:

| Name       | Type                                                      |
| :--------- | :-------------------------------------------------------- |
| `colorSet` | [_ColorSetDefinition_](host_config.colorsetdefinition.md) |
| `color`    | [_TextColor_](../enums/enums.textcolor.md)                |

**Returns:** [_TextColorDefinition_](host_config.textcolordefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:721](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L721)

---

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:291](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L291)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

---

### getEffectivePadding

▸ **getEffectivePadding**(): [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

---

### getEffectiveStyle

▸ **getEffectiveStyle**(): _string_

**Returns:** _string_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:341](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L341)

---

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

**Returns:** [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

---

### getElementById

▸ **getElementById**(`id`: _string_): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:543](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L543)

---

### getFontSize

▸ `Protected`**getFontSize**(`fontType`: [_FontTypeDefinition_](host_config.fonttypedefinition.md)): _number_

#### Parameters:

| Name       | Type                                                      |
| :--------- | :-------------------------------------------------------- |
| `fontType` | [_FontTypeDefinition_](host_config.fonttypedefinition.md) |

**Returns:** _number_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:706](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L706)

---

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [_ActionType_](../modules/card_elements.md#actiontype)[]

**Returns:** [_ActionType_](../modules/card_elements.md#actiontype)[]

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

---

### getHasBackground

▸ `Protected`**getHasBackground**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:295](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L295)

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

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

**Returns:** _string_

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1119](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1119)

---

### getPadding

▸ `Protected`**getPadding**(): _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

---

### getParentContainer

▸ **getParentContainer**(): _undefined_ \| [_Container_](card_elements.container.md)

**Returns:** _undefined_ \| [_Container_](card_elements.container.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

---

### getResourceInformation

▸ **getResourceInformation**(): [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:539](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L539)

---

### getRootElement

▸ **getRootElement**(): [_CardElement_](card_elements.cardelement.md)

**Returns:** [_CardElement_](card_elements.cardelement.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

---

### getRootObject

▸ **getRootObject**(): [_CardObject_](card_object.cardobject.md)

**Returns:** [_CardObject_](card_object.cardobject.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected`**getSchemaKey**(): _string_

**Returns:** _string_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### indexOf

▸ **indexOf**(`cardElement`: [_CardElement_](card_elements.cardelement.md)): _number_

#### Parameters:

| Name          | Type                                          |
| :------------ | :-------------------------------------------- |
| `cardElement` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _number_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:455](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L455)

---

### init

▸ **init**(`textDefinition`: [_BaseTextDefinition_](host_config.basetextdefinition.md)): _void_

#### Parameters:

| Name             | Type                                                      |
| :--------------- | :-------------------------------------------------------- |
| `textDefinition` | [_BaseTextDefinition_](host_config.basetextdefinition.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:754](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L754)

---

### internalParse

▸ `Protected`**internalParse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

---

### internalRender

▸ `Protected`**internalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:880](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L880)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [_ValidationResults_](card_object.validationresults.md)): _void_

#### Parameters:

| Name      | Type                                                    |
| :-------- | :------------------------------------------------------ |
| `context` | [_ValidationResults_](card_object.validationresults.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L113)

---

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

---

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

---

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

---

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

---

### isBleeding

▸ **isBleeding**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:337](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L337)

---

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L493)

---

### isBleedingAtTop

▸ **isBleedingAtTop**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:489](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L489)

---

### isBottomElement

▸ **isBottomElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

---

### isDesignMode

▸ **isDesignMode**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

---

### isDisplayed

▸ `Protected`**isDisplayed**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

---

### isFirstElement

▸ **isFirstElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:465](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L465)

---

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

---

### isLastElement

▸ **isLastElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L469)

---

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

---

### isRightMostElement

▸ **isRightMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

---

### isTopElement

▸ **isTopElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

---

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

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

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:669](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L669)

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `propertyValue?`: _any_): _any_

#### Parameters:

| Name             | Type                                                        |
| :--------------- | :---------------------------------------------------------- |
| `property`       | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `propertyValue?` | _any_                                                       |

**Returns:** _any_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

---

### remove

▸ **remove**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

---

### render

▸ **render**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:424](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L424)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

---

### setCustomProperty

▸ **setCustomProperty**(`name`: _string_, `value`: _any_): _void_

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `name`  | _string_ |
| `value` | _any_    |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setPadding

▸ `Protected`**setPadding**(`value`: _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)): _void_

#### Parameters:

| Name    | Type                                                              |
| :------ | :---------------------------------------------------------------- |
| `value` | _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

---

### setParent

▸ **setParent**(`value`: _undefined_ \| [_CardObject_](card_object.cardobject.md)): _void_

#### Parameters:

| Name    | Type                                                     |
| :------ | :------------------------------------------------------- |
| `value` | _undefined_ \| [_CardObject_](card_object.cardobject.md) |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

---

### setShouldFallback

▸ **setShouldFallback**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:95](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L95)

---

### setText

▸ `Protected`**setText**(`value`: _string_): _void_

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `value` | _string_ |

**Returns:** _void_

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:874](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L874)

---

### setValue

▸ `Protected`**setValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_): _void_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `value`    | _any_                                                       |

**Returns:** _void_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_SerializationContext_](card_elements.serializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _boolean_

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

---

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: _number_): _boolean_

#### Parameters:

| Name        | Type     |
| :---------- | :------- |
| `maxHeight` | _number_ |

**Returns:** _boolean_

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1050](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1050)

---

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): _void_

**Returns:** _void_

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1058](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1058)

---

### updateLayout

▸ **updateLayout**(`processChildren?`: _boolean_): _void_

#### Parameters:

| Name              | Type      | Default value |
| :---------------- | :-------- | :------------ |
| `processChildren` | _boolean_ | false         |

**Returns:** _void_

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1123](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1123)

---

### validateProperties

▸ **validateProperties**(): [_ValidationResults_](card_object.validationresults.md)

**Returns:** [_ValidationResults_](card_object.validationresults.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
