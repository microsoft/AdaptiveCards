[Adaptive Cards Javascript SDK](../README.md) / [adaptivecards](../modules/adaptivecards.md) / ToggleInput

# Class: ToggleInput

[adaptivecards](../modules/adaptivecards.md).ToggleInput

## Hierarchy

* [*Input*](card_elements.input.md)

  ↳ **ToggleInput**

## Table of contents

### Constructors

- [constructor](adaptivecards.toggleinput.md#constructor)

### Properties

- [\_parent](adaptivecards.toggleinput.md#_parent)
- [\_renderedElement](adaptivecards.toggleinput.md#_renderedelement)
- [customCssSelector](adaptivecards.toggleinput.md#customcssselector)
- [defaultValue](adaptivecards.toggleinput.md#defaultvalue)
- [errorMessage](adaptivecards.toggleinput.md#errormessage)
- [height](adaptivecards.toggleinput.md#height)
- [horizontalAlignment](adaptivecards.toggleinput.md#horizontalalignment)
- [id](adaptivecards.toggleinput.md#id)
- [isRequired](adaptivecards.toggleinput.md#isrequired)
- [label](adaptivecards.toggleinput.md#label)
- [labelledBy](adaptivecards.toggleinput.md#labelledby)
- [maxVersion](adaptivecards.toggleinput.md#maxversion)
- [onPreProcessPropertyValue](adaptivecards.toggleinput.md#onpreprocesspropertyvalue)
- [onValueChanged](adaptivecards.toggleinput.md#onvaluechanged)
- [separator](adaptivecards.toggleinput.md#separator)
- [spacing](adaptivecards.toggleinput.md#spacing)
- [title](adaptivecards.toggleinput.md#title)
- [valueOff](adaptivecards.toggleinput.md#valueoff)
- [valueOn](adaptivecards.toggleinput.md#valueon)
- [wrap](adaptivecards.toggleinput.md#wrap)
- [defaultMaxVersion](adaptivecards.toggleinput.md#defaultmaxversion)
- [errorMessageProperty](adaptivecards.toggleinput.md#errormessageproperty)
- [heightProperty](adaptivecards.toggleinput.md#heightproperty)
- [horizontalAlignmentProperty](adaptivecards.toggleinput.md#horizontalalignmentproperty)
- [idProperty](adaptivecards.toggleinput.md#idproperty)
- [isRequiredProperty](adaptivecards.toggleinput.md#isrequiredproperty)
- [isVisibleProperty](adaptivecards.toggleinput.md#isvisibleproperty)
- [labelProperty](adaptivecards.toggleinput.md#labelproperty)
- [langProperty](adaptivecards.toggleinput.md#langproperty)
- [onRegisterCustomProperties](adaptivecards.toggleinput.md#onregistercustomproperties)
- [requiresProperty](adaptivecards.toggleinput.md#requiresproperty)
- [separatorProperty](adaptivecards.toggleinput.md#separatorproperty)
- [spacingProperty](adaptivecards.toggleinput.md#spacingproperty)
- [titleProperty](adaptivecards.toggleinput.md#titleproperty)
- [typeNameProperty](adaptivecards.toggleinput.md#typenameproperty)
- [valueOffProperty](adaptivecards.toggleinput.md#valueoffproperty)
- [valueOnProperty](adaptivecards.toggleinput.md#valueonproperty)
- [valueProperty](adaptivecards.toggleinput.md#valueproperty)
- [wrapProperty](adaptivecards.toggleinput.md#wrapproperty)

### Accessors

- [allowCustomPadding](adaptivecards.toggleinput.md#allowcustompadding)
- [defaultStyle](adaptivecards.toggleinput.md#defaultstyle)
- [hasVisibleSeparator](adaptivecards.toggleinput.md#hasvisibleseparator)
- [hostConfig](adaptivecards.toggleinput.md#hostconfig)
- [index](adaptivecards.toggleinput.md#index)
- [inputControlContainerElement](adaptivecards.toggleinput.md#inputcontrolcontainerelement)
- [isInline](adaptivecards.toggleinput.md#isinline)
- [isInteractive](adaptivecards.toggleinput.md#isinteractive)
- [isNullable](adaptivecards.toggleinput.md#isnullable)
- [isStandalone](adaptivecards.toggleinput.md#isstandalone)
- [isVisible](adaptivecards.toggleinput.md#isvisible)
- [lang](adaptivecards.toggleinput.md#lang)
- [parent](adaptivecards.toggleinput.md#parent)
- [renderedElement](adaptivecards.toggleinput.md#renderedelement)
- [renderedInputControlElement](adaptivecards.toggleinput.md#renderedinputcontrolelement)
- [requires](adaptivecards.toggleinput.md#requires)
- [separatorElement](adaptivecards.toggleinput.md#separatorelement)
- [separatorOrientation](adaptivecards.toggleinput.md#separatororientation)
- [useDefaultSizing](adaptivecards.toggleinput.md#usedefaultsizing)
- [value](adaptivecards.toggleinput.md#value)

### Methods

- [adjustRenderedElementSize](adaptivecards.toggleinput.md#adjustrenderedelementsize)
- [applyPadding](adaptivecards.toggleinput.md#applypadding)
- [asString](adaptivecards.toggleinput.md#asstring)
- [createPlaceholderElement](adaptivecards.toggleinput.md#createplaceholderelement)
- [focus](adaptivecards.toggleinput.md#focus)
- [getActionAt](adaptivecards.toggleinput.md#getactionat)
- [getActionById](adaptivecards.toggleinput.md#getactionbyid)
- [getActionCount](adaptivecards.toggleinput.md#getactioncount)
- [getAllInputs](adaptivecards.toggleinput.md#getallinputs)
- [getAllLabelIds](adaptivecards.toggleinput.md#getalllabelids)
- [getCustomProperty](adaptivecards.toggleinput.md#getcustomproperty)
- [getDefaultPadding](adaptivecards.toggleinput.md#getdefaultpadding)
- [getDefaultSerializationContext](adaptivecards.toggleinput.md#getdefaultserializationcontext)
- [getEffectivePadding](adaptivecards.toggleinput.md#geteffectivepadding)
- [getEffectiveStyle](adaptivecards.toggleinput.md#geteffectivestyle)
- [getEffectiveStyleDefinition](adaptivecards.toggleinput.md#geteffectivestyledefinition)
- [getElementById](adaptivecards.toggleinput.md#getelementbyid)
- [getForbiddenActionTypes](adaptivecards.toggleinput.md#getforbiddenactiontypes)
- [getHasBackground](adaptivecards.toggleinput.md#gethasbackground)
- [getImmediateSurroundingPadding](adaptivecards.toggleinput.md#getimmediatesurroundingpadding)
- [getJsonTypeName](adaptivecards.toggleinput.md#getjsontypename)
- [getPadding](adaptivecards.toggleinput.md#getpadding)
- [getParentContainer](adaptivecards.toggleinput.md#getparentcontainer)
- [getResourceInformation](adaptivecards.toggleinput.md#getresourceinformation)
- [getRootElement](adaptivecards.toggleinput.md#getrootelement)
- [getRootObject](adaptivecards.toggleinput.md#getrootobject)
- [getSchema](adaptivecards.toggleinput.md#getschema)
- [getSchemaKey](adaptivecards.toggleinput.md#getschemakey)
- [getValue](adaptivecards.toggleinput.md#getvalue)
- [hasAllDefaultValues](adaptivecards.toggleinput.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecards.toggleinput.md#hasdefaultvalue)
- [indexOf](adaptivecards.toggleinput.md#indexof)
- [internalParse](adaptivecards.toggleinput.md#internalparse)
- [internalRender](adaptivecards.toggleinput.md#internalrender)
- [internalToJSON](adaptivecards.toggleinput.md#internaltojson)
- [internalValidateProperties](adaptivecards.toggleinput.md#internalvalidateproperties)
- [isAtTheVeryBottom](adaptivecards.toggleinput.md#isattheverybottom)
- [isAtTheVeryLeft](adaptivecards.toggleinput.md#isattheveryleft)
- [isAtTheVeryRight](adaptivecards.toggleinput.md#isattheveryright)
- [isAtTheVeryTop](adaptivecards.toggleinput.md#isattheverytop)
- [isBleeding](adaptivecards.toggleinput.md#isbleeding)
- [isBleedingAtBottom](adaptivecards.toggleinput.md#isbleedingatbottom)
- [isBleedingAtTop](adaptivecards.toggleinput.md#isbleedingattop)
- [isBottomElement](adaptivecards.toggleinput.md#isbottomelement)
- [isDesignMode](adaptivecards.toggleinput.md#isdesignmode)
- [isDisplayed](adaptivecards.toggleinput.md#isdisplayed)
- [isFirstElement](adaptivecards.toggleinput.md#isfirstelement)
- [isHiddenDueToOverflow](adaptivecards.toggleinput.md#ishiddenduetooverflow)
- [isLastElement](adaptivecards.toggleinput.md#islastelement)
- [isLeftMostElement](adaptivecards.toggleinput.md#isleftmostelement)
- [isRightMostElement](adaptivecards.toggleinput.md#isrightmostelement)
- [isSet](adaptivecards.toggleinput.md#isset)
- [isTopElement](adaptivecards.toggleinput.md#istopelement)
- [isValid](adaptivecards.toggleinput.md#isvalid)
- [overrideInternalRender](adaptivecards.toggleinput.md#overrideinternalrender)
- [parse](adaptivecards.toggleinput.md#parse)
- [populateSchema](adaptivecards.toggleinput.md#populateschema)
- [preProcessPropertyValue](adaptivecards.toggleinput.md#preprocesspropertyvalue)
- [remove](adaptivecards.toggleinput.md#remove)
- [render](adaptivecards.toggleinput.md#render)
- [resetDefaultValues](adaptivecards.toggleinput.md#resetdefaultvalues)
- [resetValidationFailureCue](adaptivecards.toggleinput.md#resetvalidationfailurecue)
- [setCustomProperty](adaptivecards.toggleinput.md#setcustomproperty)
- [setPadding](adaptivecards.toggleinput.md#setpadding)
- [setParent](adaptivecards.toggleinput.md#setparent)
- [setShouldFallback](adaptivecards.toggleinput.md#setshouldfallback)
- [setValue](adaptivecards.toggleinput.md#setvalue)
- [shouldFallback](adaptivecards.toggleinput.md#shouldfallback)
- [shouldSerialize](adaptivecards.toggleinput.md#shouldserialize)
- [showValidationErrorMessage](adaptivecards.toggleinput.md#showvalidationerrormessage)
- [toJSON](adaptivecards.toggleinput.md#tojson)
- [truncateOverflow](adaptivecards.toggleinput.md#truncateoverflow)
- [undoOverflowTruncation](adaptivecards.toggleinput.md#undooverflowtruncation)
- [updateInputControlAriaLabelledBy](adaptivecards.toggleinput.md#updateinputcontrolarialabelledby)
- [updateLayout](adaptivecards.toggleinput.md#updatelayout)
- [validateProperties](adaptivecards.toggleinput.md#validateproperties)
- [validateValue](adaptivecards.toggleinput.md#validatevalue)
- [valueChanged](adaptivecards.toggleinput.md#valuechanged)

## Constructors

### constructor

\+ **new ToggleInput**(): [*ToggleInput*](card_elements.toggleinput.md)

**Returns:** [*ToggleInput*](card_elements.toggleinput.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### \_parent

• `Protected` `Optional` **\_parent**: *undefined* \| [*CardObject*](card_object.cardobject.md)

Inherited from: [Input](card_elements.input.md).[_parent](card_elements.input.md#_parent)

Defined in: [card-object.ts:64](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L64)

___

### \_renderedElement

• `Protected` `Optional` **\_renderedElement**: *undefined* \| HTMLElement

Inherited from: [Input](card_elements.input.md).[_renderedElement](card_elements.input.md#_renderedelement)

Defined in: [card-object.ts:65](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L65)

___

### customCssSelector

• `Optional` **customCssSelector**: *undefined* \| *string*

Inherited from: [Input](card_elements.input.md).[customCssSelector](card_elements.input.md#customcssselector)

Defined in: [card-elements.ts:327](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L327)

___

### defaultValue

• `Optional` **defaultValue**: *undefined* \| *string*

Defined in: [card-elements.ts:2868](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2868)

___

### errorMessage

• `Optional` **errorMessage**: *undefined* \| *string*

Inherited from: [Input](card_elements.input.md).[errorMessage](card_elements.input.md#errormessage)

Defined in: [card-elements.ts:2431](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2431)

___

### height

• **height**: [*CardElementHeight*](../modules/card_elements.md#cardelementheight)

Inherited from: [Input](card_elements.input.md).[height](card_elements.input.md#height)

Defined in: [card-elements.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L53)

___

### horizontalAlignment

• **horizontalAlignment**: [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)

Inherited from: [Input](card_elements.input.md).[horizontalAlignment](card_elements.input.md#horizontalalignment)

Defined in: [card-elements.ts:44](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L44)

___

### id

• `Optional` **id**: *undefined* \| *string*

Inherited from: [Input](card_elements.input.md).[id](card_elements.input.md#id)

Defined in: [card-object.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L53)

___

### isRequired

• **isRequired**: *boolean*

Inherited from: [Input](card_elements.input.md).[isRequired](card_elements.input.md#isrequired)

Defined in: [card-elements.ts:2428](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2428)

___

### label

• `Optional` **label**: *undefined* \| *string*

Inherited from: [Input](card_elements.input.md).[label](card_elements.input.md#label)

Defined in: [card-elements.ts:2425](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2425)

___

### labelledBy

• `Optional` **labelledBy**: *undefined* \| *string*

Inherited from: [Input](card_elements.input.md).[labelledBy](card_elements.input.md#labelledby)

Defined in: [card-elements.ts:2610](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2610)

___

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [Input](card_elements.input.md).[maxVersion](card_elements.input.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### onPreProcessPropertyValue

• `Optional` **onPreProcessPropertyValue**: *undefined* \| (`sender`: [*CardObject*](card_object.cardobject.md), `property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*) => *any*

Inherited from: [Input](card_elements.input.md).[onPreProcessPropertyValue](card_elements.input.md#onpreprocesspropertyvalue)

Defined in: [card-object.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L67)

___

### onValueChanged

• **onValueChanged**: (`sender`: [*Input*](card_elements.input.md)) => *void*

#### Type declaration:

▸ (`sender`: [*Input*](card_elements.input.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*Input*](card_elements.input.md) |

**Returns:** *void*

Defined in: [card-elements.ts:2608](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2608)

Inherited from: [Input](card_elements.input.md).[onValueChanged](card_elements.input.md#onvaluechanged)

Defined in: [card-elements.ts:2608](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2608)

___

### separator

• **separator**: *boolean*

Inherited from: [Input](card_elements.input.md).[separator](card_elements.input.md#separator)

Defined in: [card-elements.ts:50](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L50)

___

### spacing

• **spacing**: [*Spacing*](../enums/enums.spacing.md)

Inherited from: [Input](card_elements.input.md).[spacing](card_elements.input.md#spacing)

Defined in: [card-elements.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L47)

___

### title

• `Optional` **title**: *undefined* \| *string*

Defined in: [card-elements.ts:2871](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2871)

___

### valueOff

• **valueOff**: *string*= "false"

Defined in: [card-elements.ts:2877](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2877)

___

### valueOn

• **valueOn**: *string*= "true"

Defined in: [card-elements.ts:2874](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2874)

___

### wrap

• **wrap**: *boolean*= false

Defined in: [card-elements.ts:2880](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2880)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [Input](card_elements.input.md).[defaultMaxVersion](card_elements.input.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### errorMessageProperty

▪ `Readonly` `Static` **errorMessageProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Input](card_elements.input.md).[errorMessageProperty](card_elements.input.md#errormessageproperty)

Defined in: [card-elements.ts:2422](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2422)

___

### heightProperty

▪ `Readonly` `Static` **heightProperty**: [*ValueSetProperty*](serialization.valuesetproperty.md)

Inherited from: [Input](card_elements.input.md).[heightProperty](card_elements.input.md#heightproperty)

Defined in: [card-elements.ts:24](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L24)

___

### horizontalAlignmentProperty

▪ `Readonly` `Static` **horizontalAlignmentProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*HorizontalAlignment*](../enums/enums.horizontalalignment.md)\>

Inherited from: [Input](card_elements.input.md).[horizontalAlignmentProperty](card_elements.input.md#horizontalalignmentproperty)

Defined in: [card-elements.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L32)

___

### idProperty

▪ `Readonly` `Static` **idProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Input](card_elements.input.md).[idProperty](card_elements.input.md#idproperty)

Defined in: [card-object.ts:41](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L41)

___

### isRequiredProperty

▪ `Readonly` `Static` **isRequiredProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Input](card_elements.input.md).[isRequiredProperty](card_elements.input.md#isrequiredproperty)

Defined in: [card-elements.ts:2421](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2421)

___

### isVisibleProperty

▪ `Readonly` `Static` **isVisibleProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Input](card_elements.input.md).[isVisibleProperty](card_elements.input.md#isvisibleproperty)

Defined in: [card-elements.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L22)

___

### labelProperty

▪ `Readonly` `Static` **labelProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Input](card_elements.input.md).[labelProperty](card_elements.input.md#labelproperty)

Defined in: [card-elements.ts:2420](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2420)

___

### langProperty

▪ `Readonly` `Static` **langProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Input](card_elements.input.md).[langProperty](card_elements.input.md#langproperty)

Defined in: [card-elements.ts:21](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L21)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [Input](card_elements.input.md).[onRegisterCustomProperties](card_elements.input.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

___

### requiresProperty

▪ `Readonly` `Static` **requiresProperty**: [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

Inherited from: [Input](card_elements.input.md).[requiresProperty](card_elements.input.md#requiresproperty)

Defined in: [card-object.ts:42](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L42)

___

### separatorProperty

▪ `Readonly` `Static` **separatorProperty**: [*BoolProperty*](serialization.boolproperty.md)

Inherited from: [Input](card_elements.input.md).[separatorProperty](card_elements.input.md#separatorproperty)

Defined in: [card-elements.ts:23](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L23)

___

### spacingProperty

▪ `Readonly` `Static` **spacingProperty**: [*EnumProperty*](serialization.enumproperty.md)<*typeof* [*Spacing*](../enums/enums.spacing.md)\>

Inherited from: [Input](card_elements.input.md).[spacingProperty](card_elements.input.md#spacingproperty)

Defined in: [card-elements.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L37)

___

### titleProperty

▪ `Readonly` `Static` **titleProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:2862](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2862)

___

### typeNameProperty

▪ `Readonly` `Static` **typeNameProperty**: [*StringProperty*](serialization.stringproperty.md)

Inherited from: [Input](card_elements.input.md).[typeNameProperty](card_elements.input.md#typenameproperty)

Defined in: [card-object.ts:32](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L32)

___

### valueOffProperty

▪ `Readonly` `Static` **valueOffProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:2864](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2864)

___

### valueOnProperty

▪ `Readonly` `Static` **valueOnProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:2863](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2863)

___

### valueProperty

▪ `Readonly` `Static` **valueProperty**: [*StringProperty*](serialization.stringproperty.md)

Defined in: [card-elements.ts:2861](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2861)

___

### wrapProperty

▪ `Readonly` `Static` **wrapProperty**: [*BoolProperty*](serialization.boolproperty.md)

Defined in: [card-elements.ts:2865](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2865)

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

### inputControlContainerElement

• `Protected`get **inputControlContainerElement**(): HTMLElement

**Returns:** HTMLElement

Defined in: [card-elements.ts:2488](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2488)

___

### isInline

• get **isInline**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:592](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L592)

___

### isInteractive

• get **isInteractive**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:2671](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2671)

___

### isNullable

• `Protected`get **isNullable**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:2966](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2966)

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

### renderedInputControlElement

• `Protected`get **renderedInputControlElement**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Defined in: [card-elements.ts:2484](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2484)

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

### useDefaultSizing

• `Protected`get **useDefaultSizing**(): *boolean*

**Returns:** *boolean*

Defined in: [card-elements.ts:311](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L311)

___

### value

• get **value**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Defined in: [card-elements.ts:2988](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2988)

## Methods

### adjustRenderedElementSize

▸ `Protected`**adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:236](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L236)

___

### applyPadding

▸ `Protected`**applyPadding**(): *void*

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:255](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L255)

___

### asString

▸ **asString**(): *undefined* \| *string*

**Returns:** *undefined* \| *string*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:333](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L333)

___

### createPlaceholderElement

▸ `Protected`**createPlaceholderElement**(): HTMLElement

**Returns:** HTMLElement

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:221](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L221)

___

### focus

▸ **focus**(): *void*

**Returns:** *void*

Overrides: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2974)

___

### getActionAt

▸ **getActionAt**(`index`: *number*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:412](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L412)

___

### getActionById

▸ **getActionById**(`id`: *string*): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:547](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L547)

___

### getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:408](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L408)

___

### getAllInputs

▸ **getAllInputs**(`processActions?`: *boolean*): [*Input*](card_elements.input.md)[]

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processActions` | *boolean* | true |

**Returns:** [*Input*](card_elements.input.md)[]

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2665](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2665)

___

### getAllLabelIds

▸ `Protected`**getAllLabelIds**(): *string*[]

**Returns:** *string*[]

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2441](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2441)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultPadding

▸ `Protected`**getDefaultPadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:291](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L291)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:217](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L217)

___

### getEffectivePadding

▸ **getEffectivePadding**(): [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:551](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L551)

___

### getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:341](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L341)

___

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

**Returns:** [*ContainerStyleDefinition*](host_config.containerstyledefinition.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:349](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L349)

___

### getElementById

▸ **getElementById**(`id`: *string*): *undefined* \| [*CardElement*](card_elements.cardelement.md)

#### Parameters:

Name | Type |
:------ | :------ |
`id` | *string* |

**Returns:** *undefined* \| [*CardElement*](card_elements.cardelement.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:543](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L543)

___

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): [*ActionType*](../modules/card_elements.md#actiontype)[]

**Returns:** [*ActionType*](../modules/card_elements.md#actiontype)[]

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:353](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L353)

___

### getHasBackground

▸ `Protected`**getHasBackground**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

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

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:357](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L357)

___

### getJsonTypeName

▸ **getJsonTypeName**(): *string*

**Returns:** *string*

Overrides: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2970](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2970)

___

### getPadding

▸ `Protected`**getPadding**(): *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

**Returns:** *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:299](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L299)

___

### getParentContainer

▸ **getParentContainer**(): *undefined* \| [*Container*](card_elements.container.md)

**Returns:** *undefined* \| [*Container*](card_elements.container.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:521](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L521)

___

### getResourceInformation

▸ **getResourceInformation**(): [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

**Returns:** [*IResourceInformation*](../interfaces/shared.iresourceinformation.md)[]

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:539](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L539)

___

### getRootElement

▸ **getRootElement**(): [*CardElement*](card_elements.cardelement.md)

**Returns:** [*CardElement*](card_elements.cardelement.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:517](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L517)

___

### getRootObject

▸ **getRootObject**(): [*CardObject*](card_object.cardobject.md)

**Returns:** [*CardObject*](card_object.cardobject.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-object.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L103)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-object.ts:48](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L48)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### indexOf

▸ **indexOf**(`cardElement`: [*CardElement*](card_elements.cardelement.md)): *number*

#### Parameters:

Name | Type |
:------ | :------ |
`cardElement` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *number*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:455](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L455)

___

### internalParse

▸ `Protected`**internalParse**(`source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:839](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L839)

___

### internalRender

▸ `Protected`**internalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Overrides: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2904](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2904)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:876](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L876)

___

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [*ValidationResults*](card_object.validationresults.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*ValidationResults*](card_object.validationresults.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2624](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2624)

___

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:485](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L485)

___

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:473](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L473)

___

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:477](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L477)

___

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:481](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L481)

___

### isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:337](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L337)

___

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:493](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L493)

___

### isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:489](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L489)

___

### isBottomElement

▸ **isBottomElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:509](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L509)

___

### isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:459](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L459)

___

### isDisplayed

▸ `Protected`**isDisplayed**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:245](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L245)

___

### isFirstElement

▸ **isFirstElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:465](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L465)

___

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:513](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L513)

___

### isLastElement

▸ **isLastElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:469](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L469)

___

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:497](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L497)

___

### isRightMostElement

▸ **isRightMostElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:501](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L501)

___

### isSet

▸ **isSet**(): *boolean*

**Returns:** *boolean*

Overrides: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2980](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2980)

___

### isTopElement

▸ **isTopElement**(`element`: [*CardElement*](card_elements.cardelement.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`element` | [*CardElement*](card_elements.cardelement.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:505](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L505)

___

### isValid

▸ **isValid**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2620](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2620)

___

### overrideInternalRender

▸ `Protected`**overrideInternalRender**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2492](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2492)

___

### parse

▸ **parse**(`source`: *any*, `context?`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *any* |
`context?` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:329](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L329)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

___

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `propertyValue?`: *any*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`propertyValue?` | *any* |

**Returns:** *any*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-object.ts:73](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L73)

___

### remove

▸ **remove**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:416](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L416)

___

### render

▸ **render**(): *undefined* \| HTMLElement

**Returns:** *undefined* \| HTMLElement

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:424](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L424)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### resetValidationFailureCue

▸ `Protected`**resetValidationFailureCue**(): *void*

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2575](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2575)

___

### setCustomProperty

▸ **setCustomProperty**(`name`: *string*, `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`value` | *any* |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setPadding

▸ `Protected`**setPadding**(`value`: *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*PaddingDefinition*](shared.paddingdefinition.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:303](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L303)

___

### setParent

▸ **setParent**(`value`: *undefined* \| [*CardObject*](card_object.cardobject.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *undefined* \| [*CardObject*](card_object.cardobject.md) |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-object.ts:91](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L91)

___

### setShouldFallback

▸ **setShouldFallback**(`value`: *boolean*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`value` | *boolean* |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

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

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldFallback

▸ **shouldFallback**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-object.ts:99](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L99)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*SerializationContext*](card_elements.serializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:307](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L307)

___

### showValidationErrorMessage

▸ `Protected`**showValidationErrorMessage**(): *void*

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2589](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2589)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [Input](card_elements.input.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)

___

### truncateOverflow

▸ `Protected`**truncateOverflow**(`maxHeight`: *number*): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`maxHeight` | *number* |

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:279](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L279)

___

### undoOverflowTruncation

▸ `Protected`**undoOverflowTruncation**(): *void*

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:289](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L289)

___

### updateInputControlAriaLabelledBy

▸ `Protected`**updateInputControlAriaLabelledBy**(): *void*

**Returns:** *void*

Overrides: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2887](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2887)

___

### updateLayout

▸ **updateLayout**(`processChildren?`: *boolean*): *void*

#### Parameters:

Name | Type | Default value |
:------ | :------ | :------ |
`processChildren` | *boolean* | true |

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:450](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L450)

___

### validateProperties

▸ **validateProperties**(): [*ValidationResults*](card_object.validationresults.md)

**Returns:** [*ValidationResults*](card_object.validationresults.md)

Inherited from: [Input](card_elements.input.md)

Defined in: [card-object.ts:131](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-object.ts#L131)

___

### validateValue

▸ **validateValue**(): *boolean*

**Returns:** *boolean*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2651](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2651)

___

### valueChanged

▸ `Protected`**valueChanged**(): *void*

**Returns:** *void*

Inherited from: [Input](card_elements.input.md)

Defined in: [card-elements.ts:2563](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L2563)
