[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / Media

# Class: Media

[card-elements](../modules/card_elements.md).Media

## Hierarchy

- [_CardElement_](card_elements.cardelement.md)

  ↳ **Media**

## Table of contents

### Constructors

- [constructor](card_elements.media.md#constructor)

### Properties

- [\_parent](card_elements.media.md#_parent)
- [\_renderedElement](card_elements.media.md#_renderedelement)
- [altText](card_elements.media.md#alttext)
- [customCssSelector](card_elements.media.md#customcssselector)
- [height](card_elements.media.md#height)
- [horizontalAlignment](card_elements.media.md#horizontalalignment)
- [id](card_elements.media.md#id)
- [maxVersion](card_elements.media.md#maxversion)
- [onPreProcessPropertyValue](card_elements.media.md#onpreprocesspropertyvalue)
- [poster](card_elements.media.md#poster)
- [separator](card_elements.media.md#separator)
- [sources](card_elements.media.md#sources)
- [spacing](card_elements.media.md#spacing)
- [altTextProperty](card_elements.media.md#alttextproperty)
- [defaultMaxVersion](card_elements.media.md#defaultmaxversion)
- [heightProperty](card_elements.media.md#heightproperty)
- [horizontalAlignmentProperty](card_elements.media.md#horizontalalignmentproperty)
- [idProperty](card_elements.media.md#idproperty)
- [isVisibleProperty](card_elements.media.md#isvisibleproperty)
- [langProperty](card_elements.media.md#langproperty)
- [onPlay](card_elements.media.md#onplay)
- [onRegisterCustomProperties](card_elements.media.md#onregistercustomproperties)
- [posterProperty](card_elements.media.md#posterproperty)
- [requiresProperty](card_elements.media.md#requiresproperty)
- [separatorProperty](card_elements.media.md#separatorproperty)
- [sourcesProperty](card_elements.media.md#sourcesproperty)
- [spacingProperty](card_elements.media.md#spacingproperty)
- [supportedMediaTypes](card_elements.media.md#supportedmediatypes)
- [typeNameProperty](card_elements.media.md#typenameproperty)

### Accessors

- [allowCustomPadding](card_elements.media.md#allowcustompadding)
- [defaultStyle](card_elements.media.md#defaultstyle)
- [hasVisibleSeparator](card_elements.media.md#hasvisibleseparator)
- [hostConfig](card_elements.media.md#hostconfig)
- [index](card_elements.media.md#index)
- [isInline](card_elements.media.md#isinline)
- [isInteractive](card_elements.media.md#isinteractive)
- [isStandalone](card_elements.media.md#isstandalone)
- [isVisible](card_elements.media.md#isvisible)
- [lang](card_elements.media.md#lang)
- [parent](card_elements.media.md#parent)
- [renderedElement](card_elements.media.md#renderedelement)
- [requires](card_elements.media.md#requires)
- [selectedMediaType](card_elements.media.md#selectedmediatype)
- [separatorElement](card_elements.media.md#separatorelement)
- [separatorOrientation](card_elements.media.md#separatororientation)
- [useDefaultSizing](card_elements.media.md#usedefaultsizing)

### Methods

- [adjustRenderedElementSize](card_elements.media.md#adjustrenderedelementsize)
- [applyPadding](card_elements.media.md#applypadding)
- [asString](card_elements.media.md#asstring)
- [createPlaceholderElement](card_elements.media.md#createplaceholderelement)
- [getActionAt](card_elements.media.md#getactionat)
- [getActionById](card_elements.media.md#getactionbyid)
- [getActionCount](card_elements.media.md#getactioncount)
- [getAllInputs](card_elements.media.md#getallinputs)
- [getCustomProperty](card_elements.media.md#getcustomproperty)
- [getDefaultPadding](card_elements.media.md#getdefaultpadding)
- [getDefaultSerializationContext](card_elements.media.md#getdefaultserializationcontext)
- [getEffectivePadding](card_elements.media.md#geteffectivepadding)
- [getEffectiveStyle](card_elements.media.md#geteffectivestyle)
- [getEffectiveStyleDefinition](card_elements.media.md#geteffectivestyledefinition)
- [getElementById](card_elements.media.md#getelementbyid)
- [getForbiddenActionTypes](card_elements.media.md#getforbiddenactiontypes)
- [getHasBackground](card_elements.media.md#gethasbackground)
- [getImmediateSurroundingPadding](card_elements.media.md#getimmediatesurroundingpadding)
- [getJsonTypeName](card_elements.media.md#getjsontypename)
- [getPadding](card_elements.media.md#getpadding)
- [getParentContainer](card_elements.media.md#getparentcontainer)
- [getResourceInformation](card_elements.media.md#getresourceinformation)
- [getRootElement](card_elements.media.md#getrootelement)
- [getRootObject](card_elements.media.md#getrootobject)
- [getSchema](card_elements.media.md#getschema)
- [getSchemaKey](card_elements.media.md#getschemakey)
- [getValue](card_elements.media.md#getvalue)
- [hasAllDefaultValues](card_elements.media.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.media.md#hasdefaultvalue)
- [indexOf](card_elements.media.md#indexof)
- [internalParse](card_elements.media.md#internalparse)
- [internalRender](card_elements.media.md#internalrender)
- [internalToJSON](card_elements.media.md#internaltojson)
- [internalValidateProperties](card_elements.media.md#internalvalidateproperties)
- [isAtTheVeryBottom](card_elements.media.md#isattheverybottom)
- [isAtTheVeryLeft](card_elements.media.md#isattheveryleft)
- [isAtTheVeryRight](card_elements.media.md#isattheveryright)
- [isAtTheVeryTop](card_elements.media.md#isattheverytop)
- [isBleeding](card_elements.media.md#isbleeding)
- [isBleedingAtBottom](card_elements.media.md#isbleedingatbottom)
- [isBleedingAtTop](card_elements.media.md#isbleedingattop)
- [isBottomElement](card_elements.media.md#isbottomelement)
- [isDesignMode](card_elements.media.md#isdesignmode)
- [isDisplayed](card_elements.media.md#isdisplayed)
- [isFirstElement](card_elements.media.md#isfirstelement)
- [isHiddenDueToOverflow](card_elements.media.md#ishiddenduetooverflow)
- [isLastElement](card_elements.media.md#islastelement)
- [isLeftMostElement](card_elements.media.md#isleftmostelement)
- [isRightMostElement](card_elements.media.md#isrightmostelement)
- [isTopElement](card_elements.media.md#istopelement)
- [overrideInternalRender](card_elements.media.md#overrideinternalrender)
- [parse](card_elements.media.md#parse)
- [populateSchema](card_elements.media.md#populateschema)
- [preProcessPropertyValue](card_elements.media.md#preprocesspropertyvalue)
- [remove](card_elements.media.md#remove)
- [render](card_elements.media.md#render)
- [resetDefaultValues](card_elements.media.md#resetdefaultvalues)
- [setCustomProperty](card_elements.media.md#setcustomproperty)
- [setPadding](card_elements.media.md#setpadding)
- [setParent](card_elements.media.md#setparent)
- [setShouldFallback](card_elements.media.md#setshouldfallback)
- [setValue](card_elements.media.md#setvalue)
- [shouldFallback](card_elements.media.md#shouldfallback)
- [shouldSerialize](card_elements.media.md#shouldserialize)
- [toJSON](card_elements.media.md#tojson)
- [truncateOverflow](card_elements.media.md#truncateoverflow)
- [undoOverflowTruncation](card_elements.media.md#undooverflowtruncation)
- [updateLayout](card_elements.media.md#updatelayout)
- [validateProperties](card_elements.media.md#validateproperties)

## Constructors

### constructor

\+ **new Media**(): [_Media_](card_elements.media.md)

**Returns:** [_Media_](card_elements.media.md)

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

### altText

• `Optional` **altText**: _undefined_ \| _string_

Defined in: [card-elements.ts:2183](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2183)

---

### customCssSelector

• `Optional` **customCssSelector**: _undefined_ \| _string_

Inherited from: [CardElement](card_elements.cardelement.md).[customCssSelector](card_elements.cardelement.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

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

### poster

• `Optional` **poster**: _undefined_ \| _string_

Defined in: [card-elements.ts:2180](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2180)

---

### separator

• **separator**: _boolean_

Inherited from: [CardElement](card_elements.cardelement.md).[separator](card_elements.cardelement.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

---

### sources

• **sources**: [_MediaSource_](card_elements.mediasource.md)[]

Defined in: [card-elements.ts:2177](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2177)

---

### spacing

• **spacing**: [_Spacing_](../enums/enums.spacing.md)

Inherited from: [CardElement](card_elements.cardelement.md).[spacing](card_elements.cardelement.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

---

### altTextProperty

▪ `Readonly` `Static` **altTextProperty**: [_StringProperty_](serialization.stringproperty.md)

Defined in: [card-elements.ts:2174](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2174)

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

### onPlay

▪ `Optional` `Static` **onPlay**: _undefined_ \| (`sender`: [_Media_](card_elements.media.md)) => _void_

Defined in: [card-elements.ts:2383](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2383)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [CardElement](card_elements.cardelement.md).[onRegisterCustomProperties](card_elements.cardelement.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

---

### posterProperty

▪ `Readonly` `Static` **posterProperty**: [_StringProperty_](serialization.stringproperty.md)

Defined in: [card-elements.ts:2173](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2173)

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

### sourcesProperty

▪ `Readonly` `Static` **sourcesProperty**: [_SerializableObjectCollectionProperty_](serialization.serializableobjectcollectionproperty.md)

Defined in: [card-elements.ts:2172](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2172)

---

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [_EnumProperty_](serialization.enumproperty.md)<_typeof_ [_Spacing_](../enums/enums.spacing.md)\>

Inherited from: [CardElement](card_elements.cardelement.md).[spacingProperty](card_elements.cardelement.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

---

### supportedMediaTypes

▪ `Readonly` `Static` **supportedMediaTypes**: _string_[]

Defined in: [card-elements.ts:2187](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2187)

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

### selectedMediaType

• get **selectedMediaType**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [card-elements.ts:2412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2412)

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

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L333)

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

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

**Returns:** _string_

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:2385](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2385)

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

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:2389](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2389)

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

▸ `Protected`**internalParse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

---

### internalRender

▸ `Protected`**internalRender**(): _undefined_ \| HTMLElement

**Returns:** _undefined_ \| HTMLElement

Overrides: [CardElement](card_elements.cardelement.md)

Defined in: [card-elements.ts:2372](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2372)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [CardElement](card_elements.cardelement.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

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
