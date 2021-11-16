[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / RichTextBlock

# Class: RichTextBlock

[adaptivecards](../modules/adaptivecards.md).RichTextBlock

## Hierarchy

- [_CardElement_](card_elements.cardelement.md)

  ↳ **RichTextBlock**

## Table of contents

### Constructors

- [constructor](adaptivecards.richtextblock.md#constructor)

### Properties

- [\_parent](adaptivecards.richtextblock.md#_parent)
- [\_renderedElement](adaptivecards.richtextblock.md#_renderedelement)
- [customCssSelector](adaptivecards.richtextblock.md#customcssselector)
- [forElementId](adaptivecards.richtextblock.md#forelementid)
- [height](adaptivecards.richtextblock.md#height)
- [horizontalAlignment](adaptivecards.richtextblock.md#horizontalalignment)
- [id](adaptivecards.richtextblock.md#id)
- [maxVersion](adaptivecards.richtextblock.md#maxversion)
- [onPreProcessPropertyValue](adaptivecards.richtextblock.md#onpreprocesspropertyvalue)
- [separator](adaptivecards.richtextblock.md#separator)
- [spacing](adaptivecards.richtextblock.md#spacing)
- [defaultMaxVersion](adaptivecards.richtextblock.md#defaultmaxversion)
- [heightProperty](adaptivecards.richtextblock.md#heightproperty)
- [horizontalAlignmentProperty](adaptivecards.richtextblock.md#horizontalalignmentproperty)
- [idProperty](adaptivecards.richtextblock.md#idproperty)
- [isVisibleProperty](adaptivecards.richtextblock.md#isvisibleproperty)
- [langProperty](adaptivecards.richtextblock.md#langproperty)
- [onRegisterCustomProperties](adaptivecards.richtextblock.md#onregistercustomproperties)
- [requiresProperty](adaptivecards.richtextblock.md#requiresproperty)
- [separatorProperty](adaptivecards.richtextblock.md#separatorproperty)
- [spacingProperty](adaptivecards.richtextblock.md#spacingproperty)
- [typeNameProperty](adaptivecards.richtextblock.md#typenameproperty)

### Accessors

- [allowCustomPadding](adaptivecards.richtextblock.md#allowcustompadding)
- [defaultStyle](adaptivecards.richtextblock.md#defaultstyle)
- [hasVisibleSeparator](adaptivecards.richtextblock.md#hasvisibleseparator)
- [hostConfig](adaptivecards.richtextblock.md#hostconfig)
- [index](adaptivecards.richtextblock.md#index)
- [isInline](adaptivecards.richtextblock.md#isinline)
- [isInteractive](adaptivecards.richtextblock.md#isinteractive)
- [isStandalone](adaptivecards.richtextblock.md#isstandalone)
- [isVisible](adaptivecards.richtextblock.md#isvisible)
- [lang](adaptivecards.richtextblock.md#lang)
- [parent](adaptivecards.richtextblock.md#parent)
- [renderedElement](adaptivecards.richtextblock.md#renderedelement)
- [requires](adaptivecards.richtextblock.md#requires)
- [separatorElement](adaptivecards.richtextblock.md#separatorelement)
- [separatorOrientation](adaptivecards.richtextblock.md#separatororientation)
- [useDefaultSizing](adaptivecards.richtextblock.md#usedefaultsizing)

### Methods

- [addInline](adaptivecards.richtextblock.md#addinline)
- [adjustRenderedElementSize](adaptivecards.richtextblock.md#adjustrenderedelementsize)
- [applyPadding](adaptivecards.richtextblock.md#applypadding)
- [asString](adaptivecards.richtextblock.md#asstring)
- [createPlaceholderElement](adaptivecards.richtextblock.md#createplaceholderelement)
- [getActionAt](adaptivecards.richtextblock.md#getactionat)
- [getActionById](adaptivecards.richtextblock.md#getactionbyid)
- [getActionCount](adaptivecards.richtextblock.md#getactioncount)
- [getAllInputs](adaptivecards.richtextblock.md#getallinputs)
- [getCustomProperty](adaptivecards.richtextblock.md#getcustomproperty)
- [getDefaultPadding](adaptivecards.richtextblock.md#getdefaultpadding)
- [getDefaultSerializationContext](adaptivecards.richtextblock.md#getdefaultserializationcontext)
- [getEffectivePadding](adaptivecards.richtextblock.md#geteffectivepadding)
- [getEffectiveStyle](adaptivecards.richtextblock.md#geteffectivestyle)
- [getEffectiveStyleDefinition](adaptivecards.richtextblock.md#geteffectivestyledefinition)
- [getElementById](adaptivecards.richtextblock.md#getelementbyid)
- [getForbiddenActionTypes](adaptivecards.richtextblock.md#getforbiddenactiontypes)
- [getHasBackground](adaptivecards.richtextblock.md#gethasbackground)
- [getImmediateSurroundingPadding](adaptivecards.richtextblock.md#getimmediatesurroundingpadding)
- [getInlineAt](adaptivecards.richtextblock.md#getinlineat)
- [getInlineCount](adaptivecards.richtextblock.md#getinlinecount)
- [getJsonTypeName](adaptivecards.richtextblock.md#getjsontypename)
- [getPadding](adaptivecards.richtextblock.md#getpadding)
- [getParentContainer](adaptivecards.richtextblock.md#getparentcontainer)
- [getResourceInformation](adaptivecards.richtextblock.md#getresourceinformation)
- [getRootElement](adaptivecards.richtextblock.md#getrootelement)
- [getRootObject](adaptivecards.richtextblock.md#getrootobject)
- [getSchema](adaptivecards.richtextblock.md#getschema)
- [getSchemaKey](adaptivecards.richtextblock.md#getschemakey)
- [getValue](adaptivecards.richtextblock.md#getvalue)
- [hasAllDefaultValues](adaptivecards.richtextblock.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.richtextblock.md#hasdefaultvalue)
- [indexOf](adaptivecards.richtextblock.md#indexof)
- [internalParse](adaptivecards.richtextblock.md#internalparse)
- [internalRender](adaptivecards.richtextblock.md#internalrender)
- [internalToJSON](adaptivecards.richtextblock.md#internaltojson)
- [internalValidateProperties](adaptivecards.richtextblock.md#internalvalidateproperties)
- [isAtTheVeryBottom](adaptivecards.richtextblock.md#isattheverybottom)
- [isAtTheVeryLeft](adaptivecards.richtextblock.md#isattheveryleft)
- [isAtTheVeryRight](adaptivecards.richtextblock.md#isattheveryright)
- [isAtTheVeryTop](adaptivecards.richtextblock.md#isattheverytop)
- [isBleeding](adaptivecards.richtextblock.md#isbleeding)
- [isBleedingAtBottom](adaptivecards.richtextblock.md#isbleedingatbottom)
- [isBleedingAtTop](adaptivecards.richtextblock.md#isbleedingattop)
- [isBottomElement](adaptivecards.richtextblock.md#isbottomelement)
- [isDesignMode](adaptivecards.richtextblock.md#isdesignmode)
- [isDisplayed](adaptivecards.richtextblock.md#isdisplayed)
- [isFirstElement](adaptivecards.richtextblock.md#isfirstelement)
- [isHiddenDueToOverflow](adaptivecards.richtextblock.md#ishiddenduetooverflow)
- [isLastElement](adaptivecards.richtextblock.md#islastelement)
- [isLeftMostElement](adaptivecards.richtextblock.md#isleftmostelement)
- [isRightMostElement](adaptivecards.richtextblock.md#isrightmostelement)
- [isTopElement](adaptivecards.richtextblock.md#istopelement)
- [overrideInternalRender](adaptivecards.richtextblock.md#overrideinternalrender)
- [parse](adaptivecards.richtextblock.md#parse)
- [populateSchema](adaptivecards.richtextblock.md#populateschema)
- [preProcessPropertyValue](adaptivecards.richtextblock.md#preprocesspropertyvalue)
- [remove](adaptivecards.richtextblock.md#remove)
- [removeInline](adaptivecards.richtextblock.md#removeinline)
- [render](adaptivecards.richtextblock.md#render)
- [resetDefaultValues](adaptivecards.richtextblock.md#resetdefaultvalues)
- [setCustomProperty](adaptivecards.richtextblock.md#setcustomproperty)
- [setPadding](adaptivecards.richtextblock.md#setpadding)
- [setParent](adaptivecards.richtextblock.md#setparent)
- [setShouldFallback](adaptivecards.richtextblock.md#setshouldfallback)
- [setValue](adaptivecards.richtextblock.md#setvalue)
- [shouldFallback](adaptivecards.richtextblock.md#shouldfallback)
- [shouldSerialize](adaptivecards.richtextblock.md#shouldserialize)
- [toJSON](adaptivecards.richtextblock.md#tojson)
- [truncateOverflow](adaptivecards.richtextblock.md#truncateoverflow)
- [undoOverflowTruncation](adaptivecards.richtextblock.md#undooverflowtruncation)
- [updateLayout](adaptivecards.richtextblock.md#updatelayout)
- [validateProperties](adaptivecards.richtextblock.md#validateproperties)

## Constructors

### constructor

\+ **new RichTextBlock**(): [_RichTextBlock_](card_elements.richtextblock.md)

**Returns:** [_RichTextBlock_](card_elements.richtextblock.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: _undefined_ \| [_CardObject_](card_object.cardobject.md)

Inherited from: [CardElement](card_elements.cardelement.md).[\_parent](card_elements.cardelement.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

---

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: _undefined_ \| HTMLElement

Inherited from: [CardElement](card_elements.cardelement.md).[\_renderedElement](card_elements.cardelement.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

---

### customCssSelector

• `Optional` **customCssSelector**: _undefined_ \| _string_

Inherited from: [CardElement](card_elements.cardelement.md).[customCssSelector](card_elements.cardelement.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

---

### forElementId

• `Optional` **forElementId**: _undefined_ \| _string_

Defined in: [card-elements.ts:1363](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1363)

---

### height

• **height**: [_CardElementHeight_](../modules/card_elements.md#cardelementheight)

Inherited from: [CardElement](card_elements.cardelement.md).[height](card_elements.cardelement.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

---

### horizontalAlignment

• **horizontalAlignment**: [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)

Inherited from: [CardElement](card_elements.cardelement.md).[horizontalAlignment](card_elements.cardelement.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

---

### id

• `Optional` **id**: _undefined_ \| _string_

Inherited from: [CardElement](card_elements.cardelement.md).[id](card_elements.cardelement.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

---

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [CardElement](card_elements.cardelement.md).[maxVersion](card_elements.cardelement.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: _undefined_ \| (`sender`: [_CardObject_](card_object.cardobject.md), `property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_) => _any_

Inherited from: [CardElement](card_elements.cardelement.md).[onPreProcessPropertyValue](card_elements.cardelement.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

---

### separator

• **separator**: _boolean_

Inherited from: [CardElement](card_elements.cardelement.md).[separator](card_elements.cardelement.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

---

### spacing

• **spacing**: [_Spacing_](../enums/enums.spacing.md)

Inherited from: [CardElement](card_elements.cardelement.md).[spacing](card_elements.cardelement.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [CardElement](card_elements.cardelement.md).[defaultMaxVersion](card_elements.cardelement.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [_ValueSetProperty_](serialization.valuesetproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[heightProperty](card_elements.cardelement.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

---

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_HorizontalAlignment_](../enums/enums.horizontalalignment.md)\>

Inherited from: [CardElement](card_elements.cardelement.md).[horizontalAlignmentProperty](card_elements.cardelement.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

---

### idProperty

▪ `Readonly` `Static` **idProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[idProperty](card_elements.cardelement.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

---

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[isVisibleProperty](card_elements.cardelement.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

---

### langProperty

▪ `Readonly` `Static` **langProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[langProperty](card_elements.cardelement.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [CardElement](card_elements.cardelement.md).[onRegisterCustomProperties](card_elements.cardelement.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [_SerializableObjectProperty_](serialization.serializableobjectproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[requiresProperty](card_elements.cardelement.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

---

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [_BoolProperty_](serialization.boolproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[separatorProperty](card_elements.cardelement.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

---

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_Spacing_](../enums/enums.spacing.md)\>

Inherited from: [CardElement](card_elements.cardelement.md).[spacingProperty](card_elements.cardelement.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

---

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [_StringProperty_](serialization.stringproperty.md)

Inherited from: [CardElement](card_elements.cardelement.md).[typeNameProperty](card_elements.cardelement.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

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

### useDefaultSizing

• `Protected`get **useDefaultSizing**(): _boolean_

**Returns:** _boolean_

Defined in: [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L311)

## Methods

### addInline

▸ **addInline**(`inline`: _string_ \| [_CardElement_](card_elements.cardelement.md)): _void_

#### Parameters:

| Name     | Type                                                      |
| :------- | :-------------------------------------------------------- |
| `inline` | _string_ \| [_CardElement_](card_elements.cardelement.md) |

**Returns:** _void_

Defined in: [card-elements.ts:1392](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1392)

---

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): _void_

#### Parameters:

| Name              | Type        |
| :---------------- | :---------- |
| `renderedElement` | HTMLElement |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L236)

---

### applyPadding

▸ `Protected`**applyPadding**(): _void_

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L255)

---

### asString

▸ **asString**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:1365](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1365)

---

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

---

### getActionAt

▸ **getActionAt**(`index`: _number_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L412)

---

### getActionById

▸ **getActionById**(`id`: _string_): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:547](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L547)

---

### getActionCount

▸ **getActionCount**(): _number_

**Returns:** _number_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:408](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L408)

---

### getAllInputs

▸ **getAllInputs**(`processActions?`: _boolean_): [_Input_](card_elements.input.md)[]

#### Parameters:

| Name             | Type      | Default value |
| :--------------- | :-------- | :------------ |
| `processActions` | _boolean_ | true          |

**Returns:** [_Input_](card_elements.input.md)[]

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:535](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L535)

---

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:291](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L291)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

---

### getEffectivePadding

▸ **getEffectivePadding**(): [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

---

### getEffectiveStyle

▸ **getEffectiveStyle**(): _string_

**Returns:** _string_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:341](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L341)

---

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

**Returns:** [_ContainerStyleDefinition_](host_config.containerstyledefinition.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

---

### getElementById

▸ **getElementById**(`id`: _string_): _undefined_ \| [_CardElement_](card_elements.cardelement.md)

#### Parameters:

| Name | Type     |
| :--- | :------- |
| `id` | _string_ |

**Returns:** _undefined_ \| [_CardElement_](card_elements.cardelement.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:543](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L543)

---

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [_ActionType_](../modules/card_elements.md#actiontype)[]

**Returns:** [_ActionType_](../modules/card_elements.md#actiontype)[]

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

---

### getHasBackground

▸ `Protected`**getHasBackground**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

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

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

---

### getInlineAt

▸ **getInlineAt**(`index`: _number_): [_CardElement_](card_elements.cardelement.md)

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `index` | _number_ |

**Returns:** [_CardElement_](card_elements.cardelement.md)

Defined in: [card-elements.ts:1383](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1383)

---

### getInlineCount

▸ **getInlineCount**(): _number_

**Returns:** _number_

Defined in: [card-elements.ts:1379](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1379)

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

**Returns:** _string_

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:1375](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1375)

---

### getPadding

▸ `Protected`**getPadding**(): _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

**Returns:** _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

---

### getParentContainer

▸ **getParentContainer**(): _undefined_ \| [_Container_](card_elements.container.md)

**Returns:** _undefined_ \| [_Container_](card_elements.container.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

---

### getResourceInformation

▸ **getResourceInformation**(): [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [_IResourceInformation_](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:539](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L539)

---

### getRootElement

▸ **getRootElement**(): [_CardElement_](card_elements.cardelement.md)

**Returns:** [_CardElement_](card_elements.cardelement.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

---

### getRootObject

▸ **getRootObject**(): [_CardObject_](card_object.cardobject.md)

**Returns:** [_CardObject_](card_object.cardobject.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected`**getSchemaKey**(): _string_

**Returns:** _string_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### indexOf

▸ **indexOf**(`cardElement`: [_CardElement_](card_elements.cardelement.md)): _number_

#### Parameters:

| Name          | Type                                          |
| :------------ | :-------------------------------------------- |
| `cardElement` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _number_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:455](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L455)

---

### internalParse

▸ `Protected`**internalParse**(`source`: _any_, `context`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `source`  | _any_                                                           |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:1271](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1271)

---

### internalRender

▸ `Protected`**internalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:1312](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1312)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)        |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:1298](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1298)

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [_ValidationResults_](card_object.validationresults.md)): _void_

#### Parameters:

| Name      | Type                                                    |
| :-------- | :------------------------------------------------------ |
| `context` | [_ValidationResults_](card_object.validationresults.md) |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L113)

---

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

---

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

---

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

---

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

---

### isBleeding

▸ **isBleeding**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:337](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L337)

---

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L493)

---

### isBleedingAtTop

▸ **isBleedingAtTop**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:489](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L489)

---

### isBottomElement

▸ **isBottomElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

---

### isDesignMode

▸ **isDesignMode**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

---

### isDisplayed

▸ `Protected`**isDisplayed**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

---

### isFirstElement

▸ **isFirstElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:465](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L465)

---

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

---

### isLastElement

▸ **isLastElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L469)

---

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

---

### isRightMostElement

▸ **isRightMostElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

---

### isTopElement

▸ **isTopElement**(`element`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name      | Type                                          |
| :-------- | :-------------------------------------------- |
| `element` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

---

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Inherited from: [CardElement](card_elements.cardelement.md)

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

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `propertyValue?`: _any_): _any_

#### Parameters:

| Name             | Type                                                        |
| :--------------- | :---------------------------------------------------------- |
| `property`       | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `propertyValue?` | _any_                                                       |

**Returns:** _any_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

---

### remove

▸ **remove**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

---

### removeInline

▸ **removeInline**(`inline`: [_CardElement_](card_elements.cardelement.md)): _boolean_

#### Parameters:

| Name     | Type                                          |
| :------- | :-------------------------------------------- |
| `inline` | [_CardElement_](card_elements.cardelement.md) |

**Returns:** _boolean_

Defined in: [card-elements.ts:1401](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1401)

---

### render

▸ **render**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:424](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L424)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

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

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setPadding

▸ `Protected`**setPadding**(`value`: _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md)): _void_

#### Parameters:

| Name    | Type                                                              |
| :------ | :---------------------------------------------------------------- |
| `value` | _undefined_ \| [_PaddingDefinition_](shared.paddingdefinition.md) |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

---

### setParent

▸ **setParent**(`value`: _undefined_ \| [_CardObject_](card_object.cardobject.md)): _void_

#### Parameters:

| Name    | Type                                                     |
| :------ | :------------------------------------------------------- |
| `value` | _undefined_ \| [_CardObject_](card_object.cardobject.md) |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

---

### setShouldFallback

▸ **setShouldFallback**(`value`: _boolean_): _void_

#### Parameters:

| Name    | Type      |
| :------ | :-------- |
| `value` | _boolean_ |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

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

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_SerializationContext_](card_elements.serializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

---

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: _number_): _boolean_

#### Parameters:

| Name        | Type     |
| :---------- | :------- |
| `maxHeight` | _number_ |

**Returns:** _boolean_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:279](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L279)

---

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): _void_

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:289](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L289)

---

### updateLayout

▸ **updateLayout**(`processChildren?`: _boolean_): _void_

#### Parameters:

| Name              | Type      | Default value |
| :---------------- | :-------- | :------------ |
| `processChildren` | _boolean_ | true          |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:450](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L450)

---

### validateProperties

▸ **validateProperties**(): [_ValidationResults_](card_object.validationresults.md)

**Returns:** [_ValidationResults_](card_object.validationresults.md)

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
