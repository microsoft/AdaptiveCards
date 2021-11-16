[Adaptive Cards Javascript SDK](../README.md) › [AdaptiveCard](adaptivecard.md)

# Class: AdaptiveCard

## Hierarchy

↳ [ContainerWithActions](containerwithactions.md)

↳ **AdaptiveCard**

↳ [InlineAdaptiveCard](inlineadaptivecard.md)

## Index

### Constructors

- [constructor](adaptivecard.md#constructor)

### Properties

- [\_parent](adaptivecard.md#protected-optional-_parent)
- [\_renderedElement](adaptivecard.md#protected-optional-_renderedelement)
- [\_selectAction](adaptivecard.md#protected-optional-_selectaction)
- [allowVerticalOverflow](adaptivecard.md#allowverticaloverflow)
- [customCssSelector](adaptivecard.md#optional-customcssselector)
- [designMode](adaptivecard.md#designmode)
- [fallbackText](adaptivecard.md#optional-fallbacktext)
- [height](adaptivecard.md#height)
- [horizontalAlignment](adaptivecard.md#horizontalalignment)
- [id](adaptivecard.md#optional-id)
- [maxVersion](adaptivecard.md#maxversion)
- [minPixelHeight](adaptivecard.md#optional-minpixelheight)
- [onAnchorClicked](adaptivecard.md#optional-onanchorclicked)
- [onElementVisibilityChanged](adaptivecard.md#optional-onelementvisibilitychanged)
- [onExecuteAction](adaptivecard.md#optional-onexecuteaction)
- [onImageLoaded](adaptivecard.md#optional-onimageloaded)
- [onInlineCardExpanded](adaptivecard.md#optional-oninlinecardexpanded)
- [onInputValueChanged](adaptivecard.md#optional-oninputvaluechanged)
- [onPreProcessPropertyValue](adaptivecard.md#optional-onpreprocesspropertyvalue)
- [rtl](adaptivecard.md#optional-rtl)
- [separator](adaptivecard.md#separator)
- [spacing](adaptivecard.md#spacing)
- [speak](adaptivecard.md#optional-speak)
- [version](adaptivecard.md#version)
- [verticalContentAlignment](adaptivecard.md#verticalcontentalignment)
- [$schemaProperty](adaptivecard.md#static-protected-readonly-schemaproperty)
- [backgroundImageProperty](adaptivecard.md#static-readonly-backgroundimageproperty)
- [bleedProperty](adaptivecard.md#static-readonly-bleedproperty)
- [fallbackTextProperty](adaptivecard.md#static-readonly-fallbacktextproperty)
- [heightProperty](adaptivecard.md#static-readonly-heightproperty)
- [horizontalAlignmentProperty](adaptivecard.md#static-readonly-horizontalalignmentproperty)
- [idProperty](adaptivecard.md#static-readonly-idproperty)
- [isVisibleProperty](adaptivecard.md#static-readonly-isvisibleproperty)
- [langProperty](adaptivecard.md#static-readonly-langproperty)
- [minHeightProperty](adaptivecard.md#static-readonly-minheightproperty)
- [onAnchorClicked](adaptivecard.md#static-optional-onanchorclicked)
- [onElementVisibilityChanged](adaptivecard.md#static-optional-onelementvisibilitychanged)
- [onExecuteAction](adaptivecard.md#static-optional-onexecuteaction)
- [onImageLoaded](adaptivecard.md#static-optional-onimageloaded)
- [onInlineCardExpanded](adaptivecard.md#static-optional-oninlinecardexpanded)
- [onInputValueChanged](adaptivecard.md#static-optional-oninputvaluechanged)
- [onProcessMarkdown](adaptivecard.md#static-optional-onprocessmarkdown)
- [onRegisterCustomProperties](adaptivecard.md#static-optional-onregistercustomproperties)
- [requiresProperty](adaptivecard.md#static-readonly-requiresproperty)
- [rtlProperty](adaptivecard.md#static-readonly-rtlproperty)
- [schemaUrl](adaptivecard.md#static-readonly-schemaurl)
- [selectActionProperty](adaptivecard.md#static-readonly-selectactionproperty)
- [separatorProperty](adaptivecard.md#static-readonly-separatorproperty)
- [spacingProperty](adaptivecard.md#static-readonly-spacingproperty)
- [speakProperty](adaptivecard.md#static-readonly-speakproperty)
- [styleProperty](adaptivecard.md#static-readonly-styleproperty)
- [typeNameProperty](adaptivecard.md#static-readonly-typenameproperty)
- [versionProperty](adaptivecard.md#static-readonly-versionproperty)
- [verticalContentAlignmentProperty](adaptivecard.md#static-readonly-verticalcontentalignmentproperty)

### Accessors

- [allowCustomPadding](adaptivecard.md#protected-allowcustompadding)
- [allowCustomStyle](adaptivecard.md#protected-allowcustomstyle)
- [backgroundImage](adaptivecard.md#backgroundimage)
- [bleed](adaptivecard.md#bleed)
- [bypassVersionCheck](adaptivecard.md#protected-bypassversioncheck)
- [defaultStyle](adaptivecard.md#protected-defaultstyle)
- [hasBackground](adaptivecard.md#protected-hasbackground)
- [hasExplicitStyle](adaptivecard.md#protected-hasexplicitstyle)
- [hasVisibleSeparator](adaptivecard.md#hasvisibleseparator)
- [hostConfig](adaptivecard.md#hostconfig)
- [index](adaptivecard.md#index)
- [isInline](adaptivecard.md#isinline)
- [isInteractive](adaptivecard.md#isinteractive)
- [isSelectable](adaptivecard.md#protected-isselectable)
- [isStandalone](adaptivecard.md#isstandalone)
- [isVisible](adaptivecard.md#isvisible)
- [lang](adaptivecard.md#lang)
- [padding](adaptivecard.md#padding)
- [parent](adaptivecard.md#parent)
- [renderIfEmpty](adaptivecard.md#protected-renderifempty)
- [renderedActionCount](adaptivecard.md#protected-renderedactioncount)
- [renderedElement](adaptivecard.md#renderedelement)
- [requires](adaptivecard.md#requires)
- [selectAction](adaptivecard.md#selectaction)
- [separatorElement](adaptivecard.md#separatorelement)
- [separatorOrientation](adaptivecard.md#protected-separatororientation)
- [style](adaptivecard.md#style)
- [useDefaultSizing](adaptivecard.md#protected-usedefaultsizing)
- [processMarkdown](adaptivecard.md#static-processmarkdown)

### Methods

- [addAction](adaptivecard.md#addaction)
- [addItem](adaptivecard.md#additem)
- [adjustRenderedElementSize](adaptivecard.md#protected-adjustrenderedelementsize)
- [applyBackground](adaptivecard.md#protected-applybackground)
- [applyPadding](adaptivecard.md#protected-applypadding)
- [asString](adaptivecard.md#asstring)
- [clear](adaptivecard.md#clear)
- [createPlaceholderElement](adaptivecard.md#protected-createplaceholderelement)
- [getActionAt](adaptivecard.md#getactionat)
- [getActionById](adaptivecard.md#getactionbyid)
- [getActionCount](adaptivecard.md#getactioncount)
- [getAllInputs](adaptivecard.md#getallinputs)
- [getBleed](adaptivecard.md#protected-getbleed)
- [getCustomProperty](adaptivecard.md#getcustomproperty)
- [getDefaultPadding](adaptivecard.md#protected-getdefaultpadding)
- [getDefaultSerializationContext](adaptivecard.md#protected-getdefaultserializationcontext)
- [getEffectivePadding](adaptivecard.md#geteffectivepadding)
- [getEffectiveStyle](adaptivecard.md#geteffectivestyle)
- [getEffectiveStyleDefinition](adaptivecard.md#geteffectivestyledefinition)
- [getElementById](adaptivecard.md#getelementbyid)
- [getFirstVisibleRenderedItem](adaptivecard.md#getfirstvisiblerendereditem)
- [getForbiddenActionTypes](adaptivecard.md#getforbiddenactiontypes)
- [getHasBackground](adaptivecard.md#protected-gethasbackground)
- [getHasExpandedAction](adaptivecard.md#protected-gethasexpandedaction)
- [getImmediateSurroundingPadding](adaptivecard.md#getimmediatesurroundingpadding)
- [getItemAt](adaptivecard.md#getitemat)
- [getItemCount](adaptivecard.md#getitemcount)
- [getItemsCollectionPropertyName](adaptivecard.md#protected-getitemscollectionpropertyname)
- [getJsonTypeName](adaptivecard.md#getjsontypename)
- [getLastVisibleRenderedItem](adaptivecard.md#getlastvisiblerendereditem)
- [getPadding](adaptivecard.md#protected-getpadding)
- [getParentContainer](adaptivecard.md#getparentcontainer)
- [getResourceInformation](adaptivecard.md#getresourceinformation)
- [getRootElement](adaptivecard.md#getrootelement)
- [getRootObject](adaptivecard.md#getrootobject)
- [getSchema](adaptivecard.md#getschema)
- [getSchemaKey](adaptivecard.md#protected-getschemakey)
- [getValue](adaptivecard.md#protected-getvalue)
- [hasAllDefaultValues](adaptivecard.md#hasalldefaultvalues)
- [hasDefaultValue](adaptivecard.md#hasdefaultvalue)
- [indexOf](adaptivecard.md#indexof)
- [insertItemAfter](adaptivecard.md#insertitemafter)
- [insertItemBefore](adaptivecard.md#insertitembefore)
- [internalParse](adaptivecard.md#protected-internalparse)
- [internalRender](adaptivecard.md#protected-internalrender)
- [internalToJSON](adaptivecard.md#protected-internaltojson)
- [internalValidateProperties](adaptivecard.md#internalvalidateproperties)
- [isAtTheVeryBottom](adaptivecard.md#isattheverybottom)
- [isAtTheVeryLeft](adaptivecard.md#isattheveryleft)
- [isAtTheVeryRight](adaptivecard.md#isattheveryright)
- [isAtTheVeryTop](adaptivecard.md#isattheverytop)
- [isBleeding](adaptivecard.md#isbleeding)
- [isBleedingAtBottom](adaptivecard.md#isbleedingatbottom)
- [isBleedingAtTop](adaptivecard.md#isbleedingattop)
- [isBottomElement](adaptivecard.md#isbottomelement)
- [isDesignMode](adaptivecard.md#isdesignmode)
- [isDisplayed](adaptivecard.md#protected-isdisplayed)
- [isElementAllowed](adaptivecard.md#protected-iselementallowed)
- [isFirstElement](adaptivecard.md#isfirstelement)
- [isHiddenDueToOverflow](adaptivecard.md#ishiddenduetooverflow)
- [isLastElement](adaptivecard.md#islastelement)
- [isLeftMostElement](adaptivecard.md#isleftmostelement)
- [isRightMostElement](adaptivecard.md#isrightmostelement)
- [isRtl](adaptivecard.md#isrtl)
- [isTopElement](adaptivecard.md#istopelement)
- [overrideInternalRender](adaptivecard.md#protected-overrideinternalrender)
- [parse](adaptivecard.md#parse)
- [populateSchema](adaptivecard.md#protected-populateschema)
- [preProcessPropertyValue](adaptivecard.md#preprocesspropertyvalue)
- [remove](adaptivecard.md#remove)
- [removeItem](adaptivecard.md#removeitem)
- [render](adaptivecard.md#render)
- [resetDefaultValues](adaptivecard.md#resetdefaultvalues)
- [setBleed](adaptivecard.md#protected-setbleed)
- [setCustomProperty](adaptivecard.md#setcustomproperty)
- [setPadding](adaptivecard.md#protected-setpadding)
- [setParent](adaptivecard.md#setparent)
- [setShouldFallback](adaptivecard.md#setshouldfallback)
- [setValue](adaptivecard.md#protected-setvalue)
- [shouldFallback](adaptivecard.md#shouldfallback)
- [shouldSerialize](adaptivecard.md#protected-shouldserialize)
- [supportsExcplitiHeight](adaptivecard.md#protected-supportsexcplitiheight)
- [toJSON](adaptivecard.md#tojson)
- [truncateOverflow](adaptivecard.md#protected-truncateoverflow)
- [undoOverflowTruncation](adaptivecard.md#protected-undooverflowtruncation)
- [updateLayout](adaptivecard.md#updatelayout)
- [validateProperties](adaptivecard.md#validateproperties)
- [applyMarkdown](adaptivecard.md#static-applymarkdown)

## Constructors

### constructor

\+ **new AdaptiveCard**(): _[AdaptiveCard](adaptivecard.md)_

_Inherited from [ContainerWithActions](containerwithactions.md).[constructor](containerwithactions.md#constructor)_

_Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)_

**Returns:** _[AdaptiveCard](adaptivecard.md)_

## Properties

### `Protected` `Optional` \_parent

• **\_parent**? : _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[\_parent](cardobject.md#protected-optional-_parent)_

---

### `Protected` `Optional` \_renderedElement

• **\_renderedElement**? : _HTMLElement_

_Inherited from [CardObject](cardobject.md).[\_renderedElement](cardobject.md#protected-optional-_renderedelement)_

---

### `Protected` `Optional` \_selectAction

• **\_selectAction**? : _[Action](action.md)_

_Inherited from [CardElementContainer](cardelementcontainer.md).[\_selectAction](cardelementcontainer.md#protected-optional-_selectaction)_

---

### allowVerticalOverflow

• **allowVerticalOverflow**: _boolean_ = false

_Inherited from [CardElementContainer](cardelementcontainer.md).[allowVerticalOverflow](cardelementcontainer.md#allowverticaloverflow)_

---

### `Optional` customCssSelector

• **customCssSelector**? : _undefined | string_

_Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)_

---

### designMode

• **designMode**: _boolean_ = false

---

### `Optional` fallbackText

• **fallbackText**? : _undefined | string_

---

### height

• **height**: _[CardElementHeight](../README.md#cardelementheight)_

_Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)_

---

### horizontalAlignment

• **horizontalAlignment**: _[HorizontalAlignment](../enums/horizontalalignment.md)_

_Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)_

---

### `Optional` id

• **id**? : _undefined | string_

_Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)_

---

### maxVersion

• **maxVersion**: _[Version](version.md)_ = Versions.v1_3

_Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)_

---

### `Optional` minPixelHeight

• **minPixelHeight**? : _undefined | number_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[minPixelHeight](stylablecardelementcontainer.md#optional-minpixelheight)_

---

### `Optional` onAnchorClicked

• **onAnchorClicked**? : _undefined | function_

---

### `Optional` onElementVisibilityChanged

• **onElementVisibilityChanged**? : _undefined | function_

---

### `Optional` onExecuteAction

• **onExecuteAction**? : _undefined | function_

---

### `Optional` onImageLoaded

• **onImageLoaded**? : _undefined | function_

---

### `Optional` onInlineCardExpanded

• **onInlineCardExpanded**? : _undefined | function_

---

### `Optional` onInputValueChanged

• **onInputValueChanged**? : _undefined | function_

---

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : _undefined | function_

_Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)_

---

### `Optional` rtl

• **rtl**? : _undefined | false | true_

_Inherited from [Container](container.md).[rtl](container.md#optional-rtl)_

---

### separator

• **separator**: _boolean_

_Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)_

---

### spacing

• **spacing**: _[Spacing](../enums/spacing.md)_

_Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)_

---

### `Optional` speak

• **speak**? : _undefined | string_

---

### version

• **version**: _[Version](version.md)_

---

### verticalContentAlignment

• **verticalContentAlignment**: _[VerticalAlignment](../enums/verticalalignment.md)_ = Enums.VerticalAlignment.Top

_Inherited from [Container](container.md).[verticalContentAlignment](container.md#verticalcontentalignment)_

---

### `Static` `Protected` `Readonly` $schemaProperty

▪ **$schemaProperty**: _[CustomProperty](customproperty.md)‹string›_ = new CustomProperty<string>(
Versions.v1_0,
"$schema",
(sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
return AdaptiveCard.schemaUrl;
},
(sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: Versions | undefined, context: BaseSerializationContext) => {
context.serializeValue(target, property.name, AdaptiveCard.schemaUrl);
})

---

### `Static` `Readonly` backgroundImageProperty

▪ **backgroundImageProperty**: _[SerializableObjectProperty](serializableobjectproperty.md)‹›_ = new SerializableObjectProperty(
Versions.v1_0,
"backgroundImage",
BackgroundImage)

_Inherited from [Container](container.md).[backgroundImageProperty](container.md#static-readonly-backgroundimageproperty)_

---

### `Static` `Readonly` bleedProperty

▪ **bleedProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "bleed", false)

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[bleedProperty](stylablecardelementcontainer.md#static-readonly-bleedproperty)_

---

### `Static` `Readonly` fallbackTextProperty

▪ **fallbackTextProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "fallbackText")

---

### `Static` `Readonly` heightProperty

▪ **heightProperty**: _[ValueSetProperty](valuesetproperty.md)‹›_ = new ValueSetProperty(
Versions.v1_1,
"height",
[
{ value: "auto" },
{ value: "stretch" }
],
"auto")

_Inherited from [CardElement](cardelement.md).[heightProperty](cardelement.md#static-readonly-heightproperty)_

---

### `Static` `Readonly` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: _[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›_ = new EnumProperty(
Versions.v1_0,
"horizontalAlignment",
Enums.HorizontalAlignment,
Enums.HorizontalAlignment.Left)

_Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-readonly-horizontalalignmentproperty)_

---

### `Static` `Readonly` idProperty

▪ **idProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "id")

_Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-readonly-idproperty)_

---

### `Static` `Readonly` isVisibleProperty

▪ **isVisibleProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_2, "isVisible", true)

_Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-readonly-isvisibleproperty)_

---

### `Static` `Readonly` langProperty

▪ **langProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

_Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-readonly-langproperty)_

---

### `Static` `Readonly` minHeightProperty

▪ **minHeightProperty**: _[PixelSizeProperty](pixelsizeproperty.md)‹›_ = new PixelSizeProperty(Versions.v1_2, "minHeight")

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[minHeightProperty](stylablecardelementcontainer.md#static-readonly-minheightproperty)_

---

### `Static` `Optional` onAnchorClicked

▪ **onAnchorClicked**? : _undefined | function_

---

### `Static` `Optional` onElementVisibilityChanged

▪ **onElementVisibilityChanged**? : _undefined | function_

---

### `Static` `Optional` onExecuteAction

▪ **onExecuteAction**? : _undefined | function_

---

### `Static` `Optional` onImageLoaded

▪ **onImageLoaded**? : _undefined | function_

---

### `Static` `Optional` onInlineCardExpanded

▪ **onInlineCardExpanded**? : _undefined | function_

---

### `Static` `Optional` onInputValueChanged

▪ **onInputValueChanged**? : _undefined | function_

---

### `Static` `Optional` onProcessMarkdown

▪ **onProcessMarkdown**? : _undefined | function_

---

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : _undefined | function_

_Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)_

---

### `Static` `Readonly` requiresProperty

▪ **requiresProperty**: _[SerializableObjectProperty](serializableobjectproperty.md)‹›_ = new SerializableObjectProperty(
Versions.v1_2,
"requires",
HostCapabilities,
false,
new HostCapabilities())

_Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-readonly-requiresproperty)_

---

### `Static` `Readonly` rtlProperty

▪ **rtlProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_0, "rtl")

_Inherited from [Container](container.md).[rtlProperty](container.md#static-readonly-rtlproperty)_

---

### `Static` `Readonly` schemaUrl

▪ **schemaUrl**: _"http://adaptivecards.io/schemas/adaptive-card.json"_ = "http://adaptivecards.io/schemas/adaptive-card.json"

---

### `Static` `Readonly` selectActionProperty

▪ **selectActionProperty**: _[ActionProperty](actionproperty.md)‹›_ = new ActionProperty(Versions.v1_1, "selectAction", [ "Action.ShowCard" ])

_Inherited from [CardElementContainer](cardelementcontainer.md).[selectActionProperty](cardelementcontainer.md#static-readonly-selectactionproperty)_

---

### `Static` `Readonly` separatorProperty

▪ **separatorProperty**: _[BoolProperty](boolproperty.md)‹›_ = new BoolProperty(Versions.v1_0, "separator", false)

_Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-readonly-separatorproperty)_

---

### `Static` `Readonly` spacingProperty

▪ **spacingProperty**: _[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›_ = new EnumProperty(
Versions.v1_0,
"spacing",
Enums.Spacing,
Enums.Spacing.Default)

_Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-readonly-spacingproperty)_

---

### `Static` `Readonly` speakProperty

▪ **speakProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(Versions.v1_0, "speak")

---

### `Static` `Readonly` styleProperty

▪ **styleProperty**: _[ValueSetProperty](valuesetproperty.md)‹›_ = new ValueSetProperty(
Versions.v1_0,
"style",
[
{ value: Enums.ContainerStyle.Default },
{ value: Enums.ContainerStyle.Emphasis },
{ targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Accent },
{ targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Good },
{ targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Attention },
{ targetVersion: Versions.v1_2, value: Enums.ContainerStyle.Warning }
])

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[styleProperty](stylablecardelementcontainer.md#static-readonly-styleproperty)_

---

### `Static` `Readonly` typeNameProperty

▪ **typeNameProperty**: _[StringProperty](stringproperty.md)‹›_ = new StringProperty(
Versions.v1_0,
"type",
undefined,
undefined,
undefined,
(sender: object) => {
return (<CardObject>sender).getJsonTypeName()
})

_Inherited from [CardObject](cardobject.md).[typeNameProperty](cardobject.md#static-readonly-typenameproperty)_

---

### `Static` `Readonly` versionProperty

▪ **versionProperty**: _[CustomProperty](customproperty.md)‹undefined | [Version](version.md)‹››_ = new CustomProperty<Version | undefined>(
Versions.v1_0,
"version",
(sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
let version = Version.parse(source[property.name], context);

            if (version === undefined) {
                version = Versions.latest;

                context.logParseEvent(
                    sender,
                    Enums.ValidationEvent.InvalidPropertyValue,
                    Strings.errors.invalidCardVersion(version.toString()));
            }

            return version;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: Versions | undefined, context: BaseSerializationContext) => {
            if (value !== undefined) {
                context.serializeValue(target, property.name, value.toString());
            }
        },
        Versions.v1_0)

---

### `Static` `Readonly` verticalContentAlignmentProperty

▪ **verticalContentAlignmentProperty**: _[EnumProperty](enumproperty.md)‹[VerticalAlignment](../enums/verticalalignment.md)›_ = new EnumProperty(Versions.v1_1, "verticalContentAlignment", Enums.VerticalAlignment, Enums.VerticalAlignment.Top)

_Inherited from [Container](container.md).[verticalContentAlignmentProperty](container.md#static-readonly-verticalcontentalignmentproperty)_

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): _boolean_

_Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)_

**Returns:** _boolean_

---

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): _boolean_

_Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[allowCustomStyle](stylablecardelementcontainer.md#protected-allowcustomstyle)_

**Returns:** _boolean_

---

### backgroundImage

• **get backgroundImage**(): _[BackgroundImage](backgroundimage.md)_

_Inherited from [Container](container.md).[backgroundImage](container.md#backgroundimage)_

**Returns:** _[BackgroundImage](backgroundimage.md)_

---

### bleed

• **get bleed**(): _boolean_

_Inherited from [Container](container.md).[bleed](container.md#bleed)_

**Returns:** _boolean_

• **set bleed**(`value`: boolean): _void_

_Inherited from [Container](container.md).[bleed](container.md#bleed)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### `Protected` bypassVersionCheck

• **get bypassVersionCheck**(): _boolean_

**Returns:** _boolean_

---

### `Protected` defaultStyle

• **get defaultStyle**(): _string_

_Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)_

**Returns:** _string_

---

### `Protected` hasBackground

• **get hasBackground**(): _boolean_

**Returns:** _boolean_

---

### `Protected` hasExplicitStyle

• **get hasExplicitStyle**(): _boolean_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[hasExplicitStyle](stylablecardelementcontainer.md#protected-hasexplicitstyle)_

**Returns:** _boolean_

---

### hasVisibleSeparator

• **get hasVisibleSeparator**(): _boolean_

_Overrides [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)_

**Returns:** _boolean_

---

### hostConfig

• **get hostConfig**(): _[HostConfig](hostconfig.md)_

_Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)_

_Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)_

**Returns:** _[HostConfig](hostconfig.md)_

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): _void_

_Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)_

_Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)_

**Parameters:**

| Name    | Type                        |
| ------- | --------------------------- |
| `value` | [HostConfig](hostconfig.md) |

**Returns:** _void_

---

### index

• **get index**(): _number_

_Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)_

**Returns:** _number_

---

### isInline

• **get isInline**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)_

**Returns:** _boolean_

---

### isInteractive

• **get isInteractive**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)_

**Returns:** _boolean_

---

### `Protected` isSelectable

• **get isSelectable**(): _boolean_

_Inherited from [Container](container.md).[isSelectable](container.md#protected-isselectable)_

_Overrides [CardElementContainer](cardelementcontainer.md).[isSelectable](cardelementcontainer.md#protected-isselectable)_

**Returns:** _boolean_

---

### isStandalone

• **get isStandalone**(): _boolean_

_Inherited from [ContainerWithActions](containerwithactions.md).[isStandalone](containerwithactions.md#isstandalone)_

_Overrides [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)_

**Returns:** _boolean_

---

### isVisible

• **get isVisible**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)_

**Returns:** _boolean_

• **set isVisible**(`value`: boolean): _void_

_Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### lang

• **get lang**(): _string | undefined_

_Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)_

**Returns:** _string | undefined_

• **set lang**(`value`: string | undefined): _void_

_Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)_

**Parameters:**

| Name    | Type                    |
| ------- | ----------------------- |
| `value` | string &#124; undefined |

**Returns:** _void_

---

### padding

• **get padding**(): _[PaddingDefinition](paddingdefinition.md) | undefined_

_Inherited from [Container](container.md).[padding](container.md#padding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md) | undefined_

• **set padding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): _void_

_Inherited from [Container](container.md).[padding](container.md#padding)_

**Parameters:**

| Name    | Type                                                       |
| ------- | ---------------------------------------------------------- |
| `value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** _void_

---

### parent

• **get parent**(): _[CardElement](cardelement.md) | undefined_

_Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)_

_Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)_

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### `Protected` renderIfEmpty

• **get renderIfEmpty**(): _boolean_

_Overrides [ContainerWithActions](containerwithactions.md).[renderIfEmpty](containerwithactions.md#protected-renderifempty)_

**Returns:** _boolean_

---

### `Protected` renderedActionCount

• **get renderedActionCount**(): _number_

_Inherited from [ContainerWithActions](containerwithactions.md).[renderedActionCount](containerwithactions.md#protected-renderedactioncount)_

_Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[renderedActionCount](stylablecardelementcontainer.md#protected-renderedactioncount)_

**Returns:** _number_

---

### renderedElement

• **get renderedElement**(): _HTMLElement | undefined_

_Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)_

**Returns:** _HTMLElement | undefined_

---

### requires

• **get requires**(): _[HostCapabilities](hostcapabilities.md)_

_Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)_

**Returns:** _[HostCapabilities](hostcapabilities.md)_

---

### selectAction

• **get selectAction**(): _[Action](action.md) | undefined_

_Inherited from [Container](container.md).[selectAction](container.md#selectaction)_

**Returns:** _[Action](action.md) | undefined_

• **set selectAction**(`value`: [Action](action.md) | undefined): _void_

_Inherited from [Container](container.md).[selectAction](container.md#selectaction)_

**Parameters:**

| Name    | Type                                 |
| ------- | ------------------------------------ |
| `value` | [Action](action.md) &#124; undefined |

**Returns:** _void_

---

### separatorElement

• **get separatorElement**(): _HTMLElement | undefined_

_Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)_

**Returns:** _HTMLElement | undefined_

---

### `Protected` separatorOrientation

• **get separatorOrientation**(): _[Orientation](../enums/orientation.md)_

_Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)_

**Returns:** _[Orientation](../enums/orientation.md)_

---

### style

• **get style**(): _string | undefined_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)_

**Returns:** _string | undefined_

• **set style**(`value`: string | undefined): _void_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)_

**Parameters:**

| Name    | Type                    |
| ------- | ----------------------- |
| `value` | string &#124; undefined |

**Returns:** _void_

---

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): _boolean_

_Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)_

**Returns:** _boolean_

---

### `Static` processMarkdown

• **get processMarkdown**(): _function_

**Returns:** _function_

▸ (`text`: string): _string_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `text` | string |

• **set processMarkdown**(`value`: function): _void_

**Parameters:**

▪ **value**: _function_

▸ (`text`: string): _string_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `text` | string |

**Returns:** _void_

## Methods

### addAction

▸ **addAction**(`action`: [Action](action.md)): _void_

_Inherited from [ContainerWithActions](containerwithactions.md).[addAction](containerwithactions.md#addaction)_

**Parameters:**

| Name     | Type                |
| -------- | ------------------- |
| `action` | [Action](action.md) |

**Returns:** _void_

---

### addItem

▸ **addItem**(`item`: [CardElement](cardelement.md)): _void_

_Inherited from [Container](container.md).[addItem](container.md#additem)_

**Parameters:**

| Name   | Type                          |
| ------ | ----------------------------- |
| `item` | [CardElement](cardelement.md) |

**Returns:** _void_

---

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): _void_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[adjustRenderedElementSize](stylablecardelementcontainer.md#protected-adjustrenderedelementsize)_

_Overrides [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)_

**Parameters:**

| Name              | Type        |
| ----------------- | ----------- |
| `renderedElement` | HTMLElement |

**Returns:** _void_

---

### `Protected` applyBackground

▸ **applyBackground**(): _void_

_Inherited from [Container](container.md).[applyBackground](container.md#protected-applybackground)_

_Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[applyBackground](stylablecardelementcontainer.md#protected-applybackground)_

**Returns:** _void_

---

### `Protected` applyPadding

▸ **applyPadding**(): _void_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[applyPadding](stylablecardelementcontainer.md#protected-applypadding)_

_Overrides [CardElementContainer](cardelementcontainer.md).[applyPadding](cardelementcontainer.md#protected-applypadding)_

**Returns:** _void_

---

### asString

▸ **asString**(): _string | undefined_

_Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)_

**Returns:** _string | undefined_

---

### clear

▸ **clear**(): _void_

_Inherited from [ContainerWithActions](containerwithactions.md).[clear](containerwithactions.md#clear)_

_Overrides [Container](container.md).[clear](container.md#clear)_

**Returns:** _void_

---

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): _HTMLElement_

_Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)_

**Returns:** _HTMLElement_

---

### getActionAt

▸ **getActionAt**(`index`: number): _[Action](action.md) | undefined_

_Inherited from [ContainerWithActions](containerwithactions.md).[getActionAt](containerwithactions.md#getactionat)_

_Overrides [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `index` | number |

**Returns:** _[Action](action.md) | undefined_

---

### getActionById

▸ **getActionById**(`id`: string): _[Action](action.md) | undefined_

_Inherited from [ContainerWithActions](containerwithactions.md).[getActionById](containerwithactions.md#getactionbyid)_

_Overrides [Container](container.md).[getActionById](container.md#getactionbyid)_

**Parameters:**

| Name | Type   |
| ---- | ------ |
| `id` | string |

**Returns:** _[Action](action.md) | undefined_

---

### getActionCount

▸ **getActionCount**(): _number_

_Inherited from [ContainerWithActions](containerwithactions.md).[getActionCount](containerwithactions.md#getactioncount)_

_Overrides [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)_

**Returns:** _number_

---

### getAllInputs

▸ **getAllInputs**(`processActions`: boolean): _[Input](input.md)[]_

_Inherited from [ContainerWithActions](containerwithactions.md).[getAllInputs](containerwithactions.md#getallinputs)_

_Overrides [CardElementContainer](cardelementcontainer.md).[getAllInputs](cardelementcontainer.md#getallinputs)_

**Parameters:**

| Name             | Type    | Default |
| ---------------- | ------- | ------- |
| `processActions` | boolean | true    |

**Returns:** _[Input](input.md)[]_

---

### `Protected` getBleed

▸ **getBleed**(): _boolean_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getBleed](stylablecardelementcontainer.md#protected-getbleed)_

**Returns:** _boolean_

---

### getCustomProperty

▸ **getCustomProperty**(`name`: string): _any_

_Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `name` | string |

**Returns:** _any_

---

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): _[PaddingDefinition](paddingdefinition.md)_

_Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getDefaultPadding](stylablecardelementcontainer.md#protected-getdefaultpadding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md)_

---

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): _[BaseSerializationContext](baseserializationcontext.md)_

_Overrides [CardElement](cardelement.md).[getDefaultSerializationContext](cardelement.md#protected-getdefaultserializationcontext)_

**Returns:** _[BaseSerializationContext](baseserializationcontext.md)_

---

### getEffectivePadding

▸ **getEffectivePadding**(): _[PaddingDefinition](paddingdefinition.md)_

_Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md)_

---

### getEffectiveStyle

▸ **getEffectiveStyle**(): _string_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getEffectiveStyle](stylablecardelementcontainer.md#geteffectivestyle)_

_Overrides [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)_

**Returns:** _string_

---

### getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): _[ContainerStyleDefinition](containerstyledefinition.md)_

_Inherited from [CardElement](cardelement.md).[getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)_

**Returns:** _[ContainerStyleDefinition](containerstyledefinition.md)_

---

### getElementById

▸ **getElementById**(`id`: string): _[CardElement](cardelement.md) | undefined_

_Inherited from [CardElementContainer](cardelementcontainer.md).[getElementById](cardelementcontainer.md#getelementbyid)_

_Overrides [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)_

**Parameters:**

| Name | Type   |
| ---- | ------ |
| `id` | string |

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): _[CardElement](cardelement.md) | undefined_

_Inherited from [Container](container.md).[getFirstVisibleRenderedItem](container.md#getfirstvisiblerendereditem)_

_Overrides [CardElementContainer](cardelementcontainer.md).[getFirstVisibleRenderedItem](cardelementcontainer.md#abstract-getfirstvisiblerendereditem)_

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): _[ActionType](../README.md#actiontype)[]_

_Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)_

**Returns:** _[ActionType](../README.md#actiontype)[]_

---

### `Protected` getHasBackground

▸ **getHasBackground**(): _boolean_

_Overrides [Container](container.md).[getHasBackground](container.md#protected-gethasbackground)_

**Returns:** _boolean_

---

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): _boolean_

_Inherited from [ContainerWithActions](containerwithactions.md).[getHasExpandedAction](containerwithactions.md#protected-gethasexpandedaction)_

_Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasExpandedAction](stylablecardelementcontainer.md#protected-gethasexpandedaction)_

**Returns:** _boolean_

---

### getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): _void_

_Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)_

**Parameters:**

| Name            | Type                                      | Default |
| --------------- | ----------------------------------------- | ------- |
| `result`        | [PaddingDefinition](paddingdefinition.md) | -       |
| `processTop`    | boolean                                   | true    |
| `processRight`  | boolean                                   | true    |
| `processBottom` | boolean                                   | true    |
| `processLeft`   | boolean                                   | true    |

**Returns:** _void_

---

### getItemAt

▸ **getItemAt**(`index`: number): _[CardElement](cardelement.md)_

_Inherited from [Container](container.md).[getItemAt](container.md#getitemat)_

_Overrides [CardElementContainer](cardelementcontainer.md).[getItemAt](cardelementcontainer.md#abstract-getitemat)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `index` | number |

**Returns:** _[CardElement](cardelement.md)_

---

### getItemCount

▸ **getItemCount**(): _number_

_Inherited from [Container](container.md).[getItemCount](container.md#getitemcount)_

_Overrides [CardElementContainer](cardelementcontainer.md).[getItemCount](cardelementcontainer.md#abstract-getitemcount)_

**Returns:** _number_

---

### `Protected` getItemsCollectionPropertyName

▸ **getItemsCollectionPropertyName**(): _string_

_Overrides [Container](container.md).[getItemsCollectionPropertyName](container.md#protected-getitemscollectionpropertyname)_

**Returns:** _string_

---

### getJsonTypeName

▸ **getJsonTypeName**(): _string_

_Overrides [Container](container.md).[getJsonTypeName](container.md#getjsontypename)_

**Returns:** _string_

---

### getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): _[CardElement](cardelement.md) | undefined_

_Inherited from [Container](container.md).[getLastVisibleRenderedItem](container.md#getlastvisiblerendereditem)_

_Overrides [CardElementContainer](cardelementcontainer.md).[getLastVisibleRenderedItem](cardelementcontainer.md#abstract-getlastvisiblerendereditem)_

**Returns:** _[CardElement](cardelement.md) | undefined_

---

### `Protected` getPadding

▸ **getPadding**(): _[PaddingDefinition](paddingdefinition.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)_

**Returns:** _[PaddingDefinition](paddingdefinition.md) | undefined_

---

### getParentContainer

▸ **getParentContainer**(): _[Container](container.md) | undefined_

_Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)_

**Returns:** _[Container](container.md) | undefined_

---

### getResourceInformation

▸ **getResourceInformation**(): _[IResourceInformation](../interfaces/iresourceinformation.md)[]_

_Inherited from [ContainerWithActions](containerwithactions.md).[getResourceInformation](containerwithactions.md#getresourceinformation)_

_Overrides [Container](container.md).[getResourceInformation](container.md#getresourceinformation)_

**Returns:** _[IResourceInformation](../interfaces/iresourceinformation.md)[]_

---

### getRootElement

▸ **getRootElement**(): _[CardElement](cardelement.md)_

_Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)_

**Returns:** _[CardElement](cardelement.md)_

---

### getRootObject

▸ **getRootObject**(): _[CardObject](cardobject.md)_

_Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)_

**Returns:** _[CardObject](cardobject.md)_

---

### getSchema

▸ **getSchema**(): _[SerializableObjectSchema](serializableobjectschema.md)_

_Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)_

**Returns:** _[SerializableObjectSchema](serializableobjectschema.md)_

---

### `Protected` getSchemaKey

▸ **getSchemaKey**(): _string_

_Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)_

_Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)_

**Returns:** _string_

---

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): _any_

_Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _any_

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)_

**Returns:** _boolean_

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** _boolean_

---

### indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): _number_

_Inherited from [Container](container.md).[indexOf](container.md#indexof)_

_Overrides [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)_

**Parameters:**

| Name          | Type                          |
| ------------- | ----------------------------- |
| `cardElement` | [CardElement](cardelement.md) |

**Returns:** _number_

---

### insertItemAfter

▸ **insertItemAfter**(`item`: [CardElement](cardelement.md), `insertAfter`: [CardElement](cardelement.md)): _void_

_Inherited from [Container](container.md).[insertItemAfter](container.md#insertitemafter)_

**Parameters:**

| Name          | Type                          |
| ------------- | ----------------------------- |
| `item`        | [CardElement](cardelement.md) |
| `insertAfter` | [CardElement](cardelement.md) |

**Returns:** _void_

---

### insertItemBefore

▸ **insertItemBefore**(`item`: [CardElement](cardelement.md), `insertBefore`: [CardElement](cardelement.md)): _void_

_Inherited from [Container](container.md).[insertItemBefore](container.md#insertitembefore)_

**Parameters:**

| Name           | Type                          |
| -------------- | ----------------------------- |
| `item`         | [CardElement](cardelement.md) |
| `insertBefore` | [CardElement](cardelement.md) |

**Returns:** _void_

---

### `Protected` internalParse

▸ **internalParse**(`source`: any, `context`: [SerializationContext](serializationcontext.md)): _void_

_Overrides [ContainerWithActions](containerwithactions.md).[internalParse](containerwithactions.md#protected-internalparse)_

**Parameters:**

| Name      | Type                                            |
| --------- | ----------------------------------------------- |
| `source`  | any                                             |
| `context` | [SerializationContext](serializationcontext.md) |

**Returns:** _void_

---

### `Protected` internalRender

▸ **internalRender**(): _HTMLElement | undefined_

_Overrides [ContainerWithActions](containerwithactions.md).[internalRender](containerwithactions.md#protected-internalrender)_

**Returns:** _HTMLElement | undefined_

---

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): _void_

_Overrides [ContainerWithActions](containerwithactions.md).[internalToJSON](containerwithactions.md#protected-internaltojson)_

**Parameters:**

| Name      | Type                                            |
| --------- | ----------------------------------------------- |
| `target`  | [PropertyBag](../README.md#propertybag)         |
| `context` | [SerializationContext](serializationcontext.md) |

**Returns:** _void_

---

### internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): _void_

_Overrides [ContainerWithActions](containerwithactions.md).[internalValidateProperties](containerwithactions.md#internalvalidateproperties)_

**Parameters:**

| Name      | Type                                      |
| --------- | ----------------------------------------- |
| `context` | [ValidationResults](validationresults.md) |

**Returns:** _void_

---

### isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)_

**Returns:** _boolean_

---

### isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)_

**Returns:** _boolean_

---

### isAtTheVeryRight

▸ **isAtTheVeryRight**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)_

**Returns:** _boolean_

---

### isAtTheVeryTop

▸ **isAtTheVeryTop**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)_

**Returns:** _boolean_

---

### isBleeding

▸ **isBleeding**(): _boolean_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[isBleeding](stylablecardelementcontainer.md#isbleeding)_

_Overrides [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)_

**Returns:** _boolean_

---

### isBleedingAtBottom

▸ **isBleedingAtBottom**(): _boolean_

_Inherited from [ContainerWithActions](containerwithactions.md).[isBleedingAtBottom](containerwithactions.md#isbleedingatbottom)_

_Overrides [Container](container.md).[isBleedingAtBottom](container.md#isbleedingatbottom)_

**Returns:** _boolean_

---

### isBleedingAtTop

▸ **isBleedingAtTop**(): _boolean_

_Inherited from [Container](container.md).[isBleedingAtTop](container.md#isbleedingattop)_

_Overrides [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)_

**Returns:** _boolean_

---

### isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isDesignMode

▸ **isDesignMode**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)_

**Returns:** _boolean_

---

### `Protected` isDisplayed

▸ **isDisplayed**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isDisplayed](cardelement.md#protected-isdisplayed)_

**Returns:** _boolean_

---

### `Protected` isElementAllowed

▸ **isElementAllowed**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElementContainer](cardelementcontainer.md).[isElementAllowed](cardelementcontainer.md#protected-iselementallowed)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [Container](container.md).[isFirstElement](container.md#isfirstelement)_

_Overrides [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): _boolean_

_Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)_

**Returns:** _boolean_

---

### isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [ContainerWithActions](containerwithactions.md).[isLastElement](containerwithactions.md#islastelement)_

_Overrides [Container](container.md).[isLastElement](container.md#islastelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### isRtl

▸ **isRtl**(): _boolean_

_Inherited from [Container](container.md).[isRtl](container.md#isrtl)_

**Returns:** _boolean_

---

### isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): _boolean_

_Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)_

**Parameters:**

| Name      | Type                          |
| --------- | ----------------------------- |
| `element` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): _HTMLElement | undefined_

_Inherited from [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)_

**Returns:** _HTMLElement | undefined_

---

### parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): _void_

_Inherited from [CardElement](cardelement.md).[parse](cardelement.md#parse)_

_Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)_

**Parameters:**

| Name       | Type                                            |
| ---------- | ----------------------------------------------- |
| `source`   | any                                             |
| `context?` | [SerializationContext](serializationcontext.md) |

**Returns:** _void_

---

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): _void_

_Inherited from [CardElementContainer](cardelementcontainer.md).[populateSchema](cardelementcontainer.md#protected-populateschema)_

_Overrides [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)_

**Parameters:**

| Name     | Type                                                    |
| -------- | ------------------------------------------------------- |
| `schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** _void_

---

### preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): _any_

_Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)_

**Parameters:**

| Name             | Type                                        |
| ---------------- | ------------------------------------------- |
| `property`       | [PropertyDefinition](propertydefinition.md) |
| `propertyValue?` | any                                         |

**Returns:** _any_

---

### remove

▸ **remove**(): _boolean_

_Inherited from [CardElement](cardelement.md).[remove](cardelement.md#remove)_

**Returns:** _boolean_

---

### removeItem

▸ **removeItem**(`item`: [CardElement](cardelement.md)): _boolean_

_Inherited from [Container](container.md).[removeItem](container.md#removeitem)_

_Overrides [CardElementContainer](cardelementcontainer.md).[removeItem](cardelementcontainer.md#abstract-removeitem)_

**Parameters:**

| Name   | Type                          |
| ------ | ----------------------------- |
| `item` | [CardElement](cardelement.md) |

**Returns:** _boolean_

---

### render

▸ **render**(`target?`: HTMLElement): _HTMLElement | undefined_

_Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[render](stylablecardelementcontainer.md#render)_

**Parameters:**

| Name      | Type        |
| --------- | ----------- |
| `target?` | HTMLElement |

**Returns:** _HTMLElement | undefined_

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

_Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)_

**Returns:** _void_

---

### `Protected` setBleed

▸ **setBleed**(`value`: boolean): _void_

_Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[setBleed](stylablecardelementcontainer.md#protected-setbleed)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): _void_

_Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)_

**Parameters:**

| Name    | Type   |
| ------- | ------ |
| `name`  | string |
| `value` | any    |

**Returns:** _void_

---

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): _void_

_Inherited from [CardElement](cardelement.md).[setPadding](cardelement.md#protected-setpadding)_

**Parameters:**

| Name    | Type                                                       |
| ------- | ---------------------------------------------------------- |
| `value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** _void_

---

### setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): _void_

_Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)_

**Parameters:**

| Name    | Type                                         |
| ------- | -------------------------------------------- |
| `value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** _void_

---

### setShouldFallback

▸ **setShouldFallback**(`value`: boolean): _void_

_Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)_

**Parameters:**

| Name    | Type    |
| ------- | ------- |
| `value` | boolean |

**Returns:** _void_

---

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): _void_

_Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)_

**Parameters:**

| Name       | Type                                        |
| ---------- | ------------------------------------------- |
| `property` | [PropertyDefinition](propertydefinition.md) |
| `value`    | any                                         |

**Returns:** _void_

---

### shouldFallback

▸ **shouldFallback**(): _boolean_

_Overrides [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)_

**Returns:** _boolean_

---

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): _boolean_

_Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)_

**Parameters:**

| Name      | Type                                                    |
| --------- | ------------------------------------------------------- |
| `context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _boolean_

---

### `Protected` supportsExcplitiHeight

▸ **supportsExcplitiHeight**(): _boolean_

_Inherited from [Container](container.md).[supportsExcplitiHeight](container.md#protected-supportsexcplitiheight)_

**Returns:** _boolean_

---

### toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): _[PropertyBag](../README.md#propertybag) | undefined_

_Inherited from [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)_

**Parameters:**

| Name       | Type                                                    |
| ---------- | ------------------------------------------------------- |
| `context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** _[PropertyBag](../README.md#propertybag) | undefined_

---

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): _boolean_

_Inherited from [Container](container.md).[truncateOverflow](container.md#protected-truncateoverflow)_

_Overrides [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)_

**Parameters:**

| Name        | Type   |
| ----------- | ------ |
| `maxHeight` | number |

**Returns:** _boolean_

---

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): _void_

_Inherited from [Container](container.md).[undoOverflowTruncation](container.md#protected-undooverflowtruncation)_

_Overrides [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)_

**Returns:** _void_

---

### updateLayout

▸ **updateLayout**(`processChildren`: boolean): _void_

_Overrides [CardElementContainer](cardelementcontainer.md).[updateLayout](cardelementcontainer.md#updatelayout)_

**Parameters:**

| Name              | Type    | Default |
| ----------------- | ------- | ------- |
| `processChildren` | boolean | true    |

**Returns:** _void_

---

### validateProperties

▸ **validateProperties**(): _[ValidationResults](validationresults.md)_

_Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)_

**Returns:** _[ValidationResults](validationresults.md)_

---

### `Static` applyMarkdown

▸ **applyMarkdown**(`text`: string): _[IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)_

**Parameters:**

| Name   | Type   |
| ------ | ------ |
| `text` | string |

**Returns:** _[IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)_
