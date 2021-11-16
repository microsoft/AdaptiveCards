[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / TextBlock

# Class: TextBlock

[card-elements](../modules/card_elements.md).TextBlock

## Hierarchy

* [*BaseTextBlock*](card_elements.basetextblock.md)

  ↳ **TextBlock**

## Table of contents

### Constructors

- [constructor](card_elements.textblock.md#constructor)

### Properties

- [\_parent](card_elements.textblock.md#_parent)
- [\_renderedElement](card_elements.textblock.md#_renderedelement)
- [ariaHidden](card_elements.textblock.md#ariahidden)
- [color](card_elements.textblock.md#color)
- [customCssSelector](card_elements.textblock.md#customcssselector)
- [fontType](card_elements.textblock.md#fonttype)
- [forElementId](card_elements.textblock.md#forelementid)
- [height](card_elements.textblock.md#height)
- [horizontalAlignment](card_elements.textblock.md#horizontalalignment)
- [id](card_elements.textblock.md#id)
- [isSubtle](card_elements.textblock.md#issubtle)
- [maxLines](card_elements.textblock.md#maxlines)
- [maxVersion](card_elements.textblock.md#maxversion)
- [onPreProcessPropertyValue](card_elements.textblock.md#onpreprocesspropertyvalue)
- [selectAction](card_elements.textblock.md#selectaction)
- [separator](card_elements.textblock.md#separator)
- [size](card_elements.textblock.md#size)
- [spacing](card_elements.textblock.md#spacing)
- [useMarkdown](card_elements.textblock.md#usemarkdown)
- [weight](card_elements.textblock.md#weight)
- [wrap](card_elements.textblock.md#wrap)
- [colorProperty](card_elements.textblock.md#colorproperty)
- [defaultMaxVersion](card_elements.textblock.md#defaultmaxversion)
- [fontTypeProperty](card_elements.textblock.md#fonttypeproperty)
- [heightProperty](card_elements.textblock.md#heightproperty)
- [horizontalAlignmentProperty](card_elements.textblock.md#horizontalalignmentproperty)
- [idProperty](card_elements.textblock.md#idproperty)
- [isSubtleProperty](card_elements.textblock.md#issubtleproperty)
- [isVisibleProperty](card_elements.textblock.md#isvisibleproperty)
- [langProperty](card_elements.textblock.md#langproperty)
- [maxLinesProperty](card_elements.textblock.md#maxlinesproperty)
- [onRegisterCustomProperties](card_elements.textblock.md#onregistercustomproperties)
- [requiresProperty](card_elements.textblock.md#requiresproperty)
- [selectActionProperty](card_elements.textblock.md#selectactionproperty)
- [separatorProperty](card_elements.textblock.md#separatorproperty)
- [sizeProperty](card_elements.textblock.md#sizeproperty)
- [spacingProperty](card_elements.textblock.md#spacingproperty)
- [textProperty](card_elements.textblock.md#textproperty)
- [typeNameProperty](card_elements.textblock.md#typenameproperty)
- [weightProperty](card_elements.textblock.md#weightproperty)
- [wrapProperty](card_elements.textblock.md#wrapproperty)

### Accessors

- [allowCustomPadding](card_elements.textblock.md#allowcustompadding)
- [defaultStyle](card_elements.textblock.md#defaultstyle)
- [effectiveColor](card_elements.textblock.md#effectivecolor)
- [hasVisibleSeparator](card_elements.textblock.md#hasvisibleseparator)
- [hostConfig](card_elements.textblock.md#hostconfig)
- [index](card_elements.textblock.md#index)
- [isInline](card_elements.textblock.md#isinline)
- [isInteractive](card_elements.textblock.md#isinteractive)
- [isStandalone](card_elements.textblock.md#isstandalone)
- [isVisible](card_elements.textblock.md#isvisible)
- [lang](card_elements.textblock.md#lang)
- [parent](card_elements.textblock.md#parent)
- [renderedElement](card_elements.textblock.md#renderedelement)
- [requires](card_elements.textblock.md#requires)
- [separatorElement](card_elements.textblock.md#separatorelement)
- [separatorOrientation](card_elements.textblock.md#separatororientation)
- [text](card_elements.textblock.md#text)
- [useDefaultSizing](card_elements.textblock.md#usedefaultsizing)

### Methods

- [adjustRenderedElementSize](card_elements.textblock.md#adjustrenderedelementsize)
- [applyPadding](card_elements.textblock.md#applypadding)
- [applyStylesTo](card_elements.textblock.md#applystylesto)
- [asString](card_elements.textblock.md#asstring)
- [createPlaceholderElement](card_elements.textblock.md#createplaceholderelement)
- [getActionAt](card_elements.textblock.md#getactionat)
- [getActionById](card_elements.textblock.md#getactionbyid)
- [getActionCount](card_elements.textblock.md#getactioncount)
- [getAllInputs](card_elements.textblock.md#getallinputs)
- [getColorDefinition](card_elements.textblock.md#getcolordefinition)
- [getCustomProperty](card_elements.textblock.md#getcustomproperty)
- [getDefaultPadding](card_elements.textblock.md#getdefaultpadding)
- [getDefaultSerializationContext](card_elements.textblock.md#getdefaultserializationcontext)
- [getEffectivePadding](card_elements.textblock.md#geteffectivepadding)
- [getEffectiveStyle](card_elements.textblock.md#geteffectivestyle)
- [getEffectiveStyleDefinition](card_elements.textblock.md#geteffectivestyledefinition)
- [getElementById](card_elements.textblock.md#getelementbyid)
- [getFontSize](card_elements.textblock.md#getfontsize)
- [getForbiddenActionTypes](card_elements.textblock.md#getforbiddenactiontypes)
- [getHasBackground](card_elements.textblock.md#gethasbackground)
- [getImmediateSurroundingPadding](card_elements.textblock.md#getimmediatesurroundingpadding)
- [getJsonTypeName](card_elements.textblock.md#getjsontypename)
- [getPadding](card_elements.textblock.md#getpadding)
- [getParentContainer](card_elements.textblock.md#getparentcontainer)
- [getResourceInformation](card_elements.textblock.md#getresourceinformation)
- [getRootElement](card_elements.textblock.md#getrootelement)
- [getRootObject](card_elements.textblock.md#getrootobject)
- [getSchema](card_elements.textblock.md#getschema)
- [getSchemaKey](card_elements.textblock.md#getschemakey)
- [getValue](card_elements.textblock.md#getvalue)
- [hasAllDefaultValues](card_elements.textblock.md#hasalldefaultvalues)
- [hasDefaultValue](card_elements.textblock.md#hasdefaultvalue)
- [indexOf](card_elements.textblock.md#indexof)
- [init](card_elements.textblock.md#init)
- [internalParse](card_elements.textblock.md#internalparse)
- [internalRender](card_elements.textblock.md#internalrender)
- [internalToJSON](card_elements.textblock.md#internaltojson)
- [internalValidateProperties](card_elements.textblock.md#internalvalidateproperties)
- [isAtTheVeryBottom](card_elements.textblock.md#isattheverybottom)
- [isAtTheVeryLeft](card_elements.textblock.md#isattheveryleft)
- [isAtTheVeryRight](card_elements.textblock.md#isattheveryright)
- [isAtTheVeryTop](card_elements.textblock.md#isattheverytop)
- [isBleeding](card_elements.textblock.md#isbleeding)
- [isBleedingAtBottom](card_elements.textblock.md#isbleedingatbottom)
- [isBleedingAtTop](card_elements.textblock.md#isbleedingattop)
- [isBottomElement](card_elements.textblock.md#isbottomelement)
- [isDesignMode](card_elements.textblock.md#isdesignmode)
- [isDisplayed](card_elements.textblock.md#isdisplayed)
- [isFirstElement](card_elements.textblock.md#isfirstelement)
- [isHiddenDueToOverflow](card_elements.textblock.md#ishiddenduetooverflow)
- [isLastElement](card_elements.textblock.md#islastelement)
- [isLeftMostElement](card_elements.textblock.md#isleftmostelement)
- [isRightMostElement](card_elements.textblock.md#isrightmostelement)
- [isTopElement](card_elements.textblock.md#istopelement)
- [overrideInternalRender](card_elements.textblock.md#overrideinternalrender)
- [parse](card_elements.textblock.md#parse)
- [populateSchema](card_elements.textblock.md#populateschema)
- [preProcessPropertyValue](card_elements.textblock.md#preprocesspropertyvalue)
- [remove](card_elements.textblock.md#remove)
- [render](card_elements.textblock.md#render)
- [resetDefaultValues](card_elements.textblock.md#resetdefaultvalues)
- [setCustomProperty](card_elements.textblock.md#setcustomproperty)
- [setPadding](card_elements.textblock.md#setpadding)
- [setParent](card_elements.textblock.md#setparent)
- [setShouldFallback](card_elements.textblock.md#setshouldfallback)
- [setText](card_elements.textblock.md#settext)
- [setValue](card_elements.textblock.md#setvalue)
- [shouldFallback](card_elements.textblock.md#shouldfallback)
- [shouldSerialize](card_elements.textblock.md#shouldserialize)
- [toJSON](card_elements.textblock.md#tojson)
- [truncateOverflow](card_elements.textblock.md#truncateoverflow)
- [undoOverflowTruncation](card_elements.textblock.md#undooverflowtruncation)
- [updateLayout](card_elements.textblock.md#updatelayout)
- [validateProperties](card_elements.textblock.md#validateproperties)

## Constructors

### constructor

\+ **new TextBlock**(`text?`: *string*): [*TextBlock*](card_elements.textblock.md)

#### Parameters:

Name | Type |
:------ | :------ |
`text?` | *string* |

**Returns:** [*TextBlock*](card_elements.textblock.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:744](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L744)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[_parent](card_elements.basetextblock.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[_renderedElement](card_elements.basetextblock.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### ariaHidden

• **ariaHidden**: *boolean*= false

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[ariaHidden](card_elements.basetextblock.md#ariahidden)

Defined in: [card-elements.ts:744](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L744)

___

### color

• **color**: [*TextColor*](../enums/enums.textcolor.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[color](card_elements.basetextblock.md#color)

Defined in: [card-elements.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L684)

___

### customCssSelector

• `Optional` **customCssSelector**: *undefined* \| *string*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[customCssSelector](card_elements.basetextblock.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

___

### fontType

• `Optional` **fontType**: *undefined* \| [*Default*](../enums/enums.fonttype.md#default) \| [*Monospace*](../enums/enums.fonttype.md#monospace)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[fontType](card_elements.basetextblock.md#fonttype)

Defined in: [card-elements.ts:687](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L687)

___

### forElementId

• `Optional` **forElementId**: *undefined* \| *string*

Defined in: [card-elements.ts:1069](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1069)

___

### height

• **height**: [*CardElementHeight*](../modules/card_elements.md#cardelementheight)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[height](card_elements.basetextblock.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

___

### horizontalAlignment

• **horizontalAlignment**: [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[horizontalAlignment](card_elements.basetextblock.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[id](card_elements.basetextblock.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### isSubtle

• **isSubtle**: *boolean*= false

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[isSubtle](card_elements.basetextblock.md#issubtle)

Defined in: [card-elements.ts:690](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L690)

___

### maxLines

• `Optional` **maxLines**: *undefined* \| *number*

Defined in: [card-elements.ts:834](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L834)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[maxVersion](card_elements.basetextblock.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[onPreProcessPropertyValue](card_elements.basetextblock.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### selectAction

• `Optional` **selectAction**: *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[selectAction](card_elements.basetextblock.md#selectaction)

Defined in: [card-elements.ts:702](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L702)

___

### separator

• **separator**: *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[separator](card_elements.basetextblock.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

___

### size

• **size**: [*TextSize*](../enums/enums.textsize.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[size](card_elements.basetextblock.md#size)

Defined in: [card-elements.ts:678](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L678)

___

### spacing

• **spacing**: [*Spacing*](../enums/enums.spacing.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[spacing](card_elements.basetextblock.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

___

### useMarkdown

• **useMarkdown**: *boolean*= true

Defined in: [card-elements.ts:1068](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1068)

___

### weight

• **weight**: [*TextWeight*](../enums/enums.textweight.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[weight](card_elements.basetextblock.md#weight)

Defined in: [card-elements.ts:681](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L681)

___

### wrap

• **wrap**: *boolean*= false

Defined in: [card-elements.ts:831](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L831)

___

### colorProperty

▪ `Readonly` `Static` **colorProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*TextColor*](../enums/enums.textcolor.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[colorProperty](card_elements.basetextblock.md#colorproperty)

Defined in: [card-elements.ts:654](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L654)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[defaultMaxVersion](card_elements.basetextblock.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### fontTypeProperty

▪ `Readonly` `Static` **fontTypeProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*FontType*](../enums/enums.fonttype.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[fontTypeProperty](card_elements.basetextblock.md#fonttypeproperty)

Defined in: [card-elements.ts:663](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L663)

___

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[heightProperty](card_elements.basetextblock.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

___

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[horizontalAlignmentProperty](card_elements.basetextblock.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[idProperty](card_elements.basetextblock.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### isSubtleProperty

▪ `Readonly` `Static` **isSubtleProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[isSubtleProperty](card_elements.basetextblock.md#issubtleproperty)

Defined in: [card-elements.ts:659](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L659)

___

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[isVisibleProperty](card_elements.basetextblock.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

___

### langProperty

▪ `Readonly` `Static` **langProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[langProperty](card_elements.basetextblock.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

___

### maxLinesProperty

▪ `Readonly` `Static` **maxLinesProperty**: [*NumProperty*](serialization.numproperty.md)

Defined in: [card-elements.ts:828](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L828)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[onRegisterCustomProperties](card_elements.basetextblock.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[requiresProperty](card_elements.basetextblock.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### selectActionProperty

▪ `Readonly` `Static` **selectActionProperty**: [*ActionProperty*](card_elements.actionproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[selectActionProperty](card_elements.basetextblock.md#selectactionproperty)

Defined in: [card-elements.ts:667](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L667)

___

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[separatorProperty](card_elements.basetextblock.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

___

### sizeProperty

▪ `Readonly` `Static` **sizeProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*TextSize*](../enums/enums.textsize.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[sizeProperty](card_elements.basetextblock.md#sizeproperty)

Defined in: [card-elements.ts:644](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L644)

___

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*Spacing*](../enums/enums.spacing.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[spacingProperty](card_elements.basetextblock.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

___

### textProperty

▪ `Readonly` `Static` **textProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[textProperty](card_elements.basetextblock.md#textproperty)

Defined in: [card-elements.ts:640](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L640)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[typeNameProperty](card_elements.basetextblock.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

___

### weightProperty

▪ `Readonly` `Static` **weightProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*TextWeight*](../enums/enums.textweight.md)\>

Inherited from: [BaseTextBlock](card_elements.basetextblock.md).[weightProperty](card_elements.basetextblock.md#weightproperty)

Defined in: [card-elements.ts:649](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L649)

___

### wrapProperty

▪ `Readonly` `Static` **wrapProperty**: [*BoolProperty*](serialization.boolproperty.md)

Defined in: [card-elements.ts:827](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L827)

## Accessors

### allowCustomPadding

• `Protected`get **allowCustomPadding**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:315](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L315)

___

### defaultStyle

• `Protected`get **defaultStyle**(): *string*

**Returns:** *string*

Defined in: [card-elements.ts:323](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L323)

___

### effectiveColor

• get **effectiveColor**(): [*TextColor*](../enums/enums.textcolor.md)

**Returns:** [*TextColor*](../enums/enums.textcolor.md)

Defined in: [card-elements.ts:819](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L819)

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

### parent

• get **parent**(): *undefined* \| [*CardElement*](card_elements.cardelement.md)

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Defined in: [card-elements.ts:609](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L609)

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

### text

• get **text**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [card-elements.ts:693](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L693)

• set **text**(`value`: *undefined* \| *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| *string* |

**Returns:** *void*

Defined in: [card-elements.ts:697](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L697)

___

### useDefaultSizing

• `Protected`get **useDefaultSizing**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L311)

## Methods

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L236)

___

### applyPadding

▸ `Protected`**applyPadding**(): *void*

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L255)

___

### applyStylesTo

▸ **applyStylesTo**(`targetElement`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`targetElement` | HTMLElement |

**Returns:** *void*

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1071](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1071)

___

### asString

▸ **asString**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:761](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L761)

___

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

___

### getActionAt

▸ **getActionAt**(`index`: *number*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L412)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:547](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L547)

___

### getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:408](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L408)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:535](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L535)

___

### getColorDefinition

▸ `Protected`**getColorDefinition**(`colorSet`: [*ColorSetDefinition*](host_config.colorsetdefinition.md), `color`: [*TextColor*](../enums/enums.textcolor.md)): [*TextColorDefinition*](host_config.textcolordefinition.md)

#### Parameters:

Name | Type |
:------ | :------ |
`colorSet` | [*ColorSetDefinition*](host_config.colorsetdefinition.md) |
`color` | [*TextColor*](../enums/enums.textcolor.md) |

**Returns:** [*TextColorDefinition*](host_config.textcolordefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:721](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L721)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:291](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L291)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

___

### getEffectivePadding

▸ **getEffectivePadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

___

### getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:341](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L341)

___

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

___

### getElementById

▸ **getElementById**(`id`: *string*): *undefined* \| [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:543](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L543)

___

### getFontSize

▸ `Protected`**getFontSize**(`fontType`: [*FontTypeDefinition*](host_config.fonttypedefinition.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`fontType` | [*FontTypeDefinition*](host_config.fonttypedefinition.md) |

**Returns:** *number*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:706](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L706)

___

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [*ActionType*](../modules/card_elements.md#actiontype)[]

**Returns:** [*ActionType*](../modules/card_elements.md#actiontype)[]

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

___

### getHasBackground

▸ `Protected`**getHasBackground**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:295](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L295)

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

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

___

### getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1119](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1119)

___

### getPadding

▸ `Protected`**getPadding**(): *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

___

### getParentContainer

▸ **getParentContainer**(): *undefined* \| [*Container*](card_elements.container.md)

**Returns:** *undefined* \| [*Container*](card_elements.container.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:539](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L539)

___

### getRootElement

▸ **getRootElement**(): [*CardElement*](card_elements.cardelement.md)

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### indexOf

▸ **indexOf**(`cardElement`: [*CardElement*](card_elements.cardelement.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`cardElement` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *number*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:455](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L455)

___

### init

▸ **init**(`textDefinition`: [*BaseTextDefinition*](host_config.basetextdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`textDefinition` | [*BaseTextDefinition*](host_config.basetextdefinition.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:754](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L754)

___

### internalParse

▸ `Protected`**internalParse**(`source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

___

### internalRender

▸ `Protected`**internalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:880](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L880)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L113)

___

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

___

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

___

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

___

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

___

### isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:337](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L337)

___

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L493)

___

### isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:489](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L489)

___

### isBottomElement

▸ **isBottomElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

___

### isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

___

### isDisplayed

▸ `Protected`**isDisplayed**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

___

### isFirstElement

▸ **isFirstElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:465](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L465)

___

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

___

### isLastElement

▸ **isLastElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L469)

___

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

___

### isRightMostElement

▸ **isRightMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

___

### isTopElement

▸ **isTopElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

___

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

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

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:669](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L669)

___

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `propertyValue?`: *any*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`propertyValue?` | *any* |

**Returns:** *any*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

___

### render

▸ **render**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:424](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L424)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### setCustomProperty

▸ **setCustomProperty**(`name`: *string*, `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`value` | *any* |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setPadding

▸ `Protected`**setPadding**(`value`: *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:95](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L95)

___

### setText

▸ `Protected`**setText**(`value`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *string* |

**Returns:** *void*

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:874](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L874)

___

### setValue

▸ `Protected`**setValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`value` | *any* |

**Returns:** *void*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

___

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: *number*): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`maxHeight` | *number* |

**Returns:** *boolean*

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1050](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1050)

___

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): *void*

**Returns:** *void*

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1058](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1058)

___

### updateLayout

▸ **updateLayout**(`processChildren?`: *boolean*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processChildren` | *boolean* | false |

**Returns:** *void*

Overrides: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-elements.ts:1123](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L1123)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [BaseTextBlock](card_elements.basetextblock.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)
