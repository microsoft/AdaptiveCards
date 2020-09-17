[Adaptive Cards Javascript SDK](../README.md) › [AdaptiveAppletCard](adaptiveappletcard.md)

# Class: AdaptiveAppletCard

## Hierarchy

  ↳ [AdaptiveCard](adaptivecard.md)

  ↳ **AdaptiveAppletCard**

## Index

### Constructors

* [constructor](adaptiveappletcard.md#constructor)

### Properties

* [_parent](adaptiveappletcard.md#protected-optional-_parent)
* [_renderedElement](adaptiveappletcard.md#protected-optional-_renderedelement)
* [_selectAction](adaptiveappletcard.md#protected-optional-_selectaction)
* [allowVerticalOverflow](adaptiveappletcard.md#allowverticaloverflow)
* [customCssSelector](adaptiveappletcard.md#optional-customcssselector)
* [designMode](adaptiveappletcard.md#designmode)
* [fallbackText](adaptiveappletcard.md#optional-fallbacktext)
* [height](adaptiveappletcard.md#height)
* [horizontalAlignment](adaptiveappletcard.md#horizontalalignment)
* [id](adaptiveappletcard.md#optional-id)
* [maxVersion](adaptiveappletcard.md#maxversion)
* [minPixelHeight](adaptiveappletcard.md#optional-minpixelheight)
* [onAnchorClicked](adaptiveappletcard.md#optional-onanchorclicked)
* [onElementVisibilityChanged](adaptiveappletcard.md#optional-onelementvisibilitychanged)
* [onExecuteAction](adaptiveappletcard.md#optional-onexecuteaction)
* [onImageLoaded](adaptiveappletcard.md#optional-onimageloaded)
* [onInlineCardExpanded](adaptiveappletcard.md#optional-oninlinecardexpanded)
* [onInputValueChanged](adaptiveappletcard.md#optional-oninputvaluechanged)
* [onPreProcessPropertyValue](adaptiveappletcard.md#optional-onpreprocesspropertyvalue)
* [rtl](adaptiveappletcard.md#optional-rtl)
* [separator](adaptiveappletcard.md#separator)
* [spacing](adaptiveappletcard.md#spacing)
* [speak](adaptiveappletcard.md#optional-speak)
* [version](adaptiveappletcard.md#version)
* [verticalContentAlignment](adaptiveappletcard.md#verticalcontentalignment)
* [$schemaProperty](adaptiveappletcard.md#static-protected-schemaproperty)
* [backgroundImageProperty](adaptiveappletcard.md#static-backgroundimageproperty)
* [bleedProperty](adaptiveappletcard.md#static-bleedproperty)
* [fallbackTextProperty](adaptiveappletcard.md#static-fallbacktextproperty)
* [heightProperty](adaptiveappletcard.md#static-heightproperty)
* [horizontalAlignmentProperty](adaptiveappletcard.md#static-horizontalalignmentproperty)
* [idProperty](adaptiveappletcard.md#static-idproperty)
* [isVisibleProperty](adaptiveappletcard.md#static-isvisibleproperty)
* [langProperty](adaptiveappletcard.md#static-langproperty)
* [minHeightProperty](adaptiveappletcard.md#static-minheightproperty)
* [onAnchorClicked](adaptiveappletcard.md#static-optional-onanchorclicked)
* [onElementVisibilityChanged](adaptiveappletcard.md#static-optional-onelementvisibilitychanged)
* [onExecuteAction](adaptiveappletcard.md#static-optional-onexecuteaction)
* [onImageLoaded](adaptiveappletcard.md#static-optional-onimageloaded)
* [onInlineCardExpanded](adaptiveappletcard.md#static-optional-oninlinecardexpanded)
* [onInputValueChanged](adaptiveappletcard.md#static-optional-oninputvaluechanged)
* [onProcessMarkdown](adaptiveappletcard.md#static-optional-onprocessmarkdown)
* [onRegisterCustomProperties](adaptiveappletcard.md#static-optional-onregistercustomproperties)
* [refreshProperty](adaptiveappletcard.md#static-refreshproperty)
* [requiresProperty](adaptiveappletcard.md#static-requiresproperty)
* [rtlProperty](adaptiveappletcard.md#static-rtlproperty)
* [schemaUrl](adaptiveappletcard.md#static-schemaurl)
* [selectActionProperty](adaptiveappletcard.md#static-selectactionproperty)
* [separatorProperty](adaptiveappletcard.md#static-separatorproperty)
* [spacingProperty](adaptiveappletcard.md#static-spacingproperty)
* [speakProperty](adaptiveappletcard.md#static-speakproperty)
* [styleProperty](adaptiveappletcard.md#static-styleproperty)
* [typeNameProperty](adaptiveappletcard.md#static-typenameproperty)
* [versionProperty](adaptiveappletcard.md#static-versionproperty)
* [verticalContentAlignmentProperty](adaptiveappletcard.md#static-verticalcontentalignmentproperty)

### Accessors

* [allowCustomPadding](adaptiveappletcard.md#protected-allowcustompadding)
* [allowCustomStyle](adaptiveappletcard.md#protected-allowcustomstyle)
* [backgroundImage](adaptiveappletcard.md#backgroundimage)
* [bleed](adaptiveappletcard.md#bleed)
* [bypassVersionCheck](adaptiveappletcard.md#protected-bypassversioncheck)
* [defaultStyle](adaptiveappletcard.md#protected-defaultstyle)
* [hasBackground](adaptiveappletcard.md#protected-hasbackground)
* [hasExplicitStyle](adaptiveappletcard.md#protected-hasexplicitstyle)
* [hasVisibleSeparator](adaptiveappletcard.md#hasvisibleseparator)
* [hostConfig](adaptiveappletcard.md#hostconfig)
* [index](adaptiveappletcard.md#index)
* [isInline](adaptiveappletcard.md#isinline)
* [isInteractive](adaptiveappletcard.md#isinteractive)
* [isSelectable](adaptiveappletcard.md#protected-isselectable)
* [isStandalone](adaptiveappletcard.md#isstandalone)
* [isVisible](adaptiveappletcard.md#isvisible)
* [lang](adaptiveappletcard.md#lang)
* [padding](adaptiveappletcard.md#padding)
* [parent](adaptiveappletcard.md#parent)
* [refresh](adaptiveappletcard.md#refresh)
* [renderIfEmpty](adaptiveappletcard.md#protected-renderifempty)
* [renderedActionCount](adaptiveappletcard.md#protected-renderedactioncount)
* [renderedElement](adaptiveappletcard.md#renderedelement)
* [requires](adaptiveappletcard.md#requires)
* [selectAction](adaptiveappletcard.md#selectaction)
* [separatorElement](adaptiveappletcard.md#separatorelement)
* [separatorOrientation](adaptiveappletcard.md#protected-separatororientation)
* [style](adaptiveappletcard.md#style)
* [useDefaultSizing](adaptiveappletcard.md#protected-usedefaultsizing)
* [processMarkdown](adaptiveappletcard.md#static-processmarkdown)

### Methods

* [addAction](adaptiveappletcard.md#addaction)
* [addItem](adaptiveappletcard.md#additem)
* [adjustRenderedElementSize](adaptiveappletcard.md#protected-adjustrenderedelementsize)
* [applyBackground](adaptiveappletcard.md#protected-applybackground)
* [applyPadding](adaptiveappletcard.md#protected-applypadding)
* [asString](adaptiveappletcard.md#asstring)
* [clear](adaptiveappletcard.md#clear)
* [createPlaceholderElement](adaptiveappletcard.md#protected-createplaceholderelement)
* [getActionAt](adaptiveappletcard.md#getactionat)
* [getActionById](adaptiveappletcard.md#getactionbyid)
* [getActionCount](adaptiveappletcard.md#getactioncount)
* [getAllInputs](adaptiveappletcard.md#getallinputs)
* [getBleed](adaptiveappletcard.md#protected-getbleed)
* [getCustomProperty](adaptiveappletcard.md#getcustomproperty)
* [getDefaultPadding](adaptiveappletcard.md#protected-getdefaultpadding)
* [getEffectivePadding](adaptiveappletcard.md#geteffectivepadding)
* [getEffectiveStyle](adaptiveappletcard.md#geteffectivestyle)
* [getEffectiveStyleDefinition](adaptiveappletcard.md#geteffectivestyledefinition)
* [getElementById](adaptiveappletcard.md#getelementbyid)
* [getFirstVisibleRenderedItem](adaptiveappletcard.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](adaptiveappletcard.md#getforbiddenactiontypes)
* [getHasBackground](adaptiveappletcard.md#protected-gethasbackground)
* [getHasExpandedAction](adaptiveappletcard.md#protected-gethasexpandedaction)
* [getImmediateSurroundingPadding](adaptiveappletcard.md#getimmediatesurroundingpadding)
* [getItemAt](adaptiveappletcard.md#getitemat)
* [getItemCount](adaptiveappletcard.md#getitemcount)
* [getItemsCollectionPropertyName](adaptiveappletcard.md#protected-getitemscollectionpropertyname)
* [getJsonTypeName](adaptiveappletcard.md#getjsontypename)
* [getLastVisibleRenderedItem](adaptiveappletcard.md#getlastvisiblerendereditem)
* [getPadding](adaptiveappletcard.md#protected-getpadding)
* [getParentContainer](adaptiveappletcard.md#getparentcontainer)
* [getResourceInformation](adaptiveappletcard.md#getresourceinformation)
* [getRootElement](adaptiveappletcard.md#getrootelement)
* [getRootObject](adaptiveappletcard.md#getrootobject)
* [getSchema](adaptiveappletcard.md#getschema)
* [getSchemaKey](adaptiveappletcard.md#protected-getschemakey)
* [getValue](adaptiveappletcard.md#protected-getvalue)
* [hasAllDefaultValues](adaptiveappletcard.md#hasalldefaultvalues)
* [hasDefaultValue](adaptiveappletcard.md#hasdefaultvalue)
* [indexOf](adaptiveappletcard.md#indexof)
* [insertItemAfter](adaptiveappletcard.md#insertitemafter)
* [insertItemBefore](adaptiveappletcard.md#insertitembefore)
* [internalParse](adaptiveappletcard.md#protected-internalparse)
* [internalRender](adaptiveappletcard.md#protected-internalrender)
* [internalToJSON](adaptiveappletcard.md#protected-internaltojson)
* [internalValidateProperties](adaptiveappletcard.md#internalvalidateproperties)
* [isAtTheVeryBottom](adaptiveappletcard.md#isattheverybottom)
* [isAtTheVeryLeft](adaptiveappletcard.md#isattheveryleft)
* [isAtTheVeryRight](adaptiveappletcard.md#isattheveryright)
* [isAtTheVeryTop](adaptiveappletcard.md#isattheverytop)
* [isBleeding](adaptiveappletcard.md#isbleeding)
* [isBleedingAtBottom](adaptiveappletcard.md#isbleedingatbottom)
* [isBleedingAtTop](adaptiveappletcard.md#isbleedingattop)
* [isBottomElement](adaptiveappletcard.md#isbottomelement)
* [isDesignMode](adaptiveappletcard.md#isdesignmode)
* [isDisplayed](adaptiveappletcard.md#protected-isdisplayed)
* [isElementAllowed](adaptiveappletcard.md#protected-iselementallowed)
* [isFirstElement](adaptiveappletcard.md#isfirstelement)
* [isHiddenDueToOverflow](adaptiveappletcard.md#ishiddenduetooverflow)
* [isLastElement](adaptiveappletcard.md#islastelement)
* [isLeftMostElement](adaptiveappletcard.md#isleftmostelement)
* [isRightMostElement](adaptiveappletcard.md#isrightmostelement)
* [isRtl](adaptiveappletcard.md#isrtl)
* [isTopElement](adaptiveappletcard.md#istopelement)
* [overrideInternalRender](adaptiveappletcard.md#protected-overrideinternalrender)
* [parse](adaptiveappletcard.md#parse)
* [populateSchema](adaptiveappletcard.md#protected-populateschema)
* [preProcessPropertyValue](adaptiveappletcard.md#preprocesspropertyvalue)
* [remove](adaptiveappletcard.md#remove)
* [removeItem](adaptiveappletcard.md#removeitem)
* [render](adaptiveappletcard.md#render)
* [resetDefaultValues](adaptiveappletcard.md#resetdefaultvalues)
* [setBleed](adaptiveappletcard.md#protected-setbleed)
* [setCustomProperty](adaptiveappletcard.md#setcustomproperty)
* [setPadding](adaptiveappletcard.md#protected-setpadding)
* [setParent](adaptiveappletcard.md#setparent)
* [setShouldFallback](adaptiveappletcard.md#setshouldfallback)
* [setValue](adaptiveappletcard.md#protected-setvalue)
* [shouldFallback](adaptiveappletcard.md#shouldfallback)
* [shouldSerialize](adaptiveappletcard.md#protected-shouldserialize)
* [supportsExcplitiHeight](adaptiveappletcard.md#protected-supportsexcplitiheight)
* [toJSON](adaptiveappletcard.md#tojson)
* [truncateOverflow](adaptiveappletcard.md#protected-truncateoverflow)
* [undoOverflowTruncation](adaptiveappletcard.md#protected-undooverflowtruncation)
* [updateLayout](adaptiveappletcard.md#updatelayout)
* [validateProperties](adaptiveappletcard.md#validateproperties)
* [applyMarkdown](adaptiveappletcard.md#static-applymarkdown)

## Constructors

###  constructor

\+ **new AdaptiveAppletCard**(): *[AdaptiveAppletCard](adaptiveappletcard.md)*

*Inherited from [ContainerWithActions](containerwithactions.md).[constructor](containerwithactions.md#constructor)*

*Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Returns:** *[AdaptiveAppletCard](adaptiveappletcard.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

___

### `Protected` `Optional` _selectAction

• **_selectAction**? : *[Action](action.md)*

*Inherited from [CardElementContainer](cardelementcontainer.md).[_selectAction](cardelementcontainer.md#protected-optional-_selectaction)*

___

###  allowVerticalOverflow

• **allowVerticalOverflow**: *boolean* = false

*Inherited from [CardElementContainer](cardelementcontainer.md).[allowVerticalOverflow](cardelementcontainer.md#allowverticaloverflow)*

___

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

*Inherited from [CardElement](cardelement.md).[customCssSelector](cardelement.md#optional-customcssselector)*

___

###  designMode

• **designMode**: *boolean* = false

*Inherited from [AdaptiveCard](adaptivecard.md).[designMode](adaptivecard.md#designmode)*

___

### `Optional` fallbackText

• **fallbackText**? : *undefined | string*

*Inherited from [AdaptiveCard](adaptivecard.md).[fallbackText](adaptivecard.md#optional-fallbacktext)*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

*Inherited from [CardElement](cardelement.md).[height](cardelement.md#height)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

*Inherited from [CardElement](cardelement.md).[horizontalAlignment](cardelement.md#horizontalalignment)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

### `Optional` minPixelHeight

• **minPixelHeight**? : *undefined | number*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[minPixelHeight](stylablecardelementcontainer.md#optional-minpixelheight)*

___

### `Optional` onAnchorClicked

• **onAnchorClicked**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onAnchorClicked](adaptivecard.md#static-optional-onanchorclicked)*

___

### `Optional` onElementVisibilityChanged

• **onElementVisibilityChanged**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onElementVisibilityChanged](adaptivecard.md#static-optional-onelementvisibilitychanged)*

___

### `Optional` onExecuteAction

• **onExecuteAction**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onExecuteAction](adaptivecard.md#static-optional-onexecuteaction)*

___

### `Optional` onImageLoaded

• **onImageLoaded**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onImageLoaded](adaptivecard.md#static-optional-onimageloaded)*

___

### `Optional` onInlineCardExpanded

• **onInlineCardExpanded**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onInlineCardExpanded](adaptivecard.md#static-optional-oninlinecardexpanded)*

___

### `Optional` onInputValueChanged

• **onInputValueChanged**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onInputValueChanged](adaptivecard.md#static-optional-oninputvaluechanged)*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

___

### `Optional` rtl

• **rtl**? : *undefined | false | true*

*Inherited from [Container](container.md).[rtl](container.md#optional-rtl)*

___

###  separator

• **separator**: *boolean*

*Inherited from [CardElement](cardelement.md).[separator](cardelement.md#separator)*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

*Inherited from [CardElement](cardelement.md).[spacing](cardelement.md#spacing)*

___

### `Optional` speak

• **speak**? : *undefined | string*

*Inherited from [AdaptiveCard](adaptivecard.md).[speak](adaptivecard.md#optional-speak)*

___

###  version

• **version**: *[Version](version.md)*

*Inherited from [AdaptiveCard](adaptivecard.md).[version](adaptivecard.md#version)*

___

###  verticalContentAlignment

• **verticalContentAlignment**: *[VerticalAlignment](../enums/verticalalignment.md)* = Enums.VerticalAlignment.Top

*Inherited from [Container](container.md).[verticalContentAlignment](container.md#verticalcontentalignment)*

___

### `Static` `Protected` $schemaProperty

▪ **$schemaProperty**: *[CustomProperty](customproperty.md)‹string›* = new CustomProperty<string>(
        Versions.v1_0,
        "$schema",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            return AdaptiveCard.schemaUrl;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: Versions | undefined, context: BaseSerializationContext) => {
            context.serializeValue(target, property.name, AdaptiveCard.schemaUrl);
        })

*Inherited from [AdaptiveCard](adaptivecard.md).[$schemaProperty](adaptivecard.md#static-protected-schemaproperty)*

___

### `Static` backgroundImageProperty

▪ **backgroundImageProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_0,
        "backgroundImage",
        BackgroundImage)

*Inherited from [Container](container.md).[backgroundImageProperty](container.md#static-backgroundimageproperty)*

___

### `Static` bleedProperty

▪ **bleedProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "bleed", false)

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[bleedProperty](stylablecardelementcontainer.md#static-bleedproperty)*

___

### `Static` fallbackTextProperty

▪ **fallbackTextProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "fallbackText")

*Inherited from [AdaptiveCard](adaptivecard.md).[fallbackTextProperty](adaptivecard.md#static-fallbacktextproperty)*

___

### `Static` heightProperty

▪ **heightProperty**: *[ValueSetProperty](valuesetproperty.md)‹›* = new ValueSetProperty(
        Versions.v1_1,
        "height",
        [
            { value: "auto" },
            { value: "stretch" }
        ],
        "auto")

*Inherited from [CardElement](cardelement.md).[heightProperty](cardelement.md#static-heightproperty)*

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

*Inherited from [CardElement](cardelement.md).[horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)*

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

*Inherited from [CardElement](cardelement.md).[isVisibleProperty](cardelement.md#static-isvisibleproperty)*

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

*Inherited from [CardElement](cardelement.md).[langProperty](cardelement.md#static-langproperty)*

___

### `Static` minHeightProperty

▪ **minHeightProperty**: *[PixelSizeProperty](pixelsizeproperty.md)‹›* = new PixelSizeProperty(Versions.v1_2, "minHeight")

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[minHeightProperty](stylablecardelementcontainer.md#static-minheightproperty)*

___

### `Static` `Optional` onAnchorClicked

▪ **onAnchorClicked**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onAnchorClicked](adaptivecard.md#static-optional-onanchorclicked)*

___

### `Static` `Optional` onElementVisibilityChanged

▪ **onElementVisibilityChanged**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onElementVisibilityChanged](adaptivecard.md#static-optional-onelementvisibilitychanged)*

___

### `Static` `Optional` onExecuteAction

▪ **onExecuteAction**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onExecuteAction](adaptivecard.md#static-optional-onexecuteaction)*

___

### `Static` `Optional` onImageLoaded

▪ **onImageLoaded**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onImageLoaded](adaptivecard.md#static-optional-onimageloaded)*

___

### `Static` `Optional` onInlineCardExpanded

▪ **onInlineCardExpanded**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onInlineCardExpanded](adaptivecard.md#static-optional-oninlinecardexpanded)*

___

### `Static` `Optional` onInputValueChanged

▪ **onInputValueChanged**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onInputValueChanged](adaptivecard.md#static-optional-oninputvaluechanged)*

___

### `Static` `Optional` onProcessMarkdown

▪ **onProcessMarkdown**? : *undefined | function*

*Inherited from [AdaptiveCard](adaptivecard.md).[onProcessMarkdown](adaptivecard.md#static-optional-onprocessmarkdown)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

___

### `Static` refreshProperty

▪ **refreshProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(Versions.v1_0, "refresh", RefreshDefinition, true)

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        false,
        new HostCapabilities())

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

___

### `Static` rtlProperty

▪ **rtlProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "rtl")

*Inherited from [Container](container.md).[rtlProperty](container.md#static-rtlproperty)*

___

### `Static` schemaUrl

▪ **schemaUrl**: *"http://adaptivecards.io/schemas/adaptive-card.json"* = "http://adaptivecards.io/schemas/adaptive-card.json"

*Inherited from [AdaptiveCard](adaptivecard.md).[schemaUrl](adaptivecard.md#static-schemaurl)*

___

### `Static` selectActionProperty

▪ **selectActionProperty**: *[ActionProperty](actionproperty.md)‹›* = new ActionProperty(Versions.v1_1, "selectAction", [ "Action.ShowCard" ])

*Inherited from [CardElementContainer](cardelementcontainer.md).[selectActionProperty](cardelementcontainer.md#static-selectactionproperty)*

___

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

*Inherited from [CardElement](cardelement.md).[separatorProperty](cardelement.md#static-separatorproperty)*

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

*Inherited from [CardElement](cardelement.md).[spacingProperty](cardelement.md#static-spacingproperty)*

___

### `Static` speakProperty

▪ **speakProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "speak")

*Inherited from [AdaptiveCard](adaptivecard.md).[speakProperty](adaptivecard.md#static-speakproperty)*

___

### `Static` styleProperty

▪ **styleProperty**: *[ValueSetProperty](valuesetproperty.md)‹›* = new ValueSetProperty(
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

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[styleProperty](stylablecardelementcontainer.md#static-styleproperty)*

___

### `Static` typeNameProperty

▪ **typeNameProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(
        Versions.v1_0,
        "type",
        undefined,
        undefined,
        undefined,
        (sender: object) => {
            return (<CardObject>sender).getJsonTypeName()
        })

*Inherited from [CardObject](cardobject.md).[typeNameProperty](cardobject.md#static-typenameproperty)*

___

### `Static` versionProperty

▪ **versionProperty**: *[CustomProperty](customproperty.md)‹undefined | [Version](version.md)‹››* = new CustomProperty<Version | undefined>(
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

*Inherited from [AdaptiveCard](adaptivecard.md).[versionProperty](adaptivecard.md#static-versionproperty)*

___

### `Static` verticalContentAlignmentProperty

▪ **verticalContentAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[VerticalAlignment](../enums/verticalalignment.md)›* = new EnumProperty(Versions.v1_1, "verticalContentAlignment", Enums.VerticalAlignment, Enums.VerticalAlignment.Top)

*Inherited from [Container](container.md).[verticalContentAlignmentProperty](container.md#static-verticalcontentalignmentproperty)*

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

**Returns:** *boolean*

___

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[allowCustomStyle](adaptivecard.md#protected-allowcustomstyle)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[allowCustomStyle](stylablecardelementcontainer.md#protected-allowcustomstyle)*

**Returns:** *boolean*

___

###  backgroundImage

• **get backgroundImage**(): *[BackgroundImage](backgroundimage.md)*

*Inherited from [Container](container.md).[backgroundImage](container.md#backgroundimage)*

**Returns:** *[BackgroundImage](backgroundimage.md)*

___

###  bleed

• **get bleed**(): *boolean*

*Inherited from [Container](container.md).[bleed](container.md#bleed)*

**Returns:** *boolean*

• **set bleed**(`value`: boolean): *void*

*Inherited from [Container](container.md).[bleed](container.md#bleed)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` bypassVersionCheck

• **get bypassVersionCheck**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[bypassVersionCheck](adaptivecard.md#protected-bypassversioncheck)*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

**Returns:** *string*

___

### `Protected` hasBackground

• **get hasBackground**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[hasBackground](adaptivecard.md#protected-hasbackground)*

**Returns:** *boolean*

___

### `Protected` hasExplicitStyle

• **get hasExplicitStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[hasExplicitStyle](stylablecardelementcontainer.md#protected-hasexplicitstyle)*

**Returns:** *boolean*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[hasVisibleSeparator](adaptivecard.md#hasvisibleseparator)*

*Overrides [CardElement](cardelement.md).[hasVisibleSeparator](cardelement.md#hasvisibleseparator)*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Inherited from [CardElement](cardelement.md).[hostConfig](cardelement.md#hostconfig)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

*Inherited from [CardElement](cardelement.md).[index](cardelement.md#index)*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInline](cardelement.md#isinline)*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isInteractive](cardelement.md#isinteractive)*

**Returns:** *boolean*

___

### `Protected` isSelectable

• **get isSelectable**(): *boolean*

*Inherited from [Container](container.md).[isSelectable](container.md#protected-isselectable)*

*Overrides [CardElementContainer](cardelementcontainer.md).[isSelectable](cardelementcontainer.md#protected-isselectable)*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

*Inherited from [ContainerWithActions](containerwithactions.md).[isStandalone](containerwithactions.md#isstandalone)*

*Overrides [CardElement](cardelement.md).[isStandalone](cardelement.md#isstandalone)*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[isVisible](cardelement.md#isvisible)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

*Inherited from [CardElement](cardelement.md).[lang](cardelement.md#lang)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  padding

• **get padding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

*Inherited from [Container](container.md).[padding](container.md#padding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

• **set padding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): *void*

*Inherited from [Container](container.md).[padding](container.md#padding)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElement](cardelement.md).[parent](cardelement.md#parent)*

*Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  refresh

• **get refresh**(): *[RefreshDefinition](refreshdefinition.md) | undefined*

**Returns:** *[RefreshDefinition](refreshdefinition.md) | undefined*

• **set refresh**(`value`: [RefreshDefinition](refreshdefinition.md) | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [RefreshDefinition](refreshdefinition.md) &#124; undefined |

**Returns:** *void*

___

### `Protected` renderIfEmpty

• **get renderIfEmpty**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[renderIfEmpty](adaptivecard.md#protected-renderifempty)*

*Overrides [ContainerWithActions](containerwithactions.md).[renderIfEmpty](containerwithactions.md#protected-renderifempty)*

**Returns:** *boolean*

___

### `Protected` renderedActionCount

• **get renderedActionCount**(): *number*

*Inherited from [ContainerWithActions](containerwithactions.md).[renderedActionCount](containerwithactions.md#protected-renderedactioncount)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[renderedActionCount](stylablecardelementcontainer.md#protected-renderedactioncount)*

**Returns:** *number*

___

###  renderedElement

• **get renderedElement**(): *HTMLElement | undefined*

*Inherited from [CardObject](cardobject.md).[renderedElement](cardobject.md#renderedelement)*

**Returns:** *HTMLElement | undefined*

___

###  requires

• **get requires**(): *HostCapabilities*

*Inherited from [CardObject](cardobject.md).[requires](cardobject.md#requires)*

**Returns:** *HostCapabilities*

___

###  selectAction

• **get selectAction**(): *[Action](action.md) | undefined*

*Inherited from [Container](container.md).[selectAction](container.md#selectaction)*

**Returns:** *[Action](action.md) | undefined*

• **set selectAction**(`value`: [Action](action.md) | undefined): *void*

*Inherited from [Container](container.md).[selectAction](container.md#selectaction)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [Action](action.md) &#124; undefined |

**Returns:** *void*

___

###  separatorElement

• **get separatorElement**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[separatorElement](cardelement.md#separatorelement)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

*Inherited from [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

###  style

• **get style**(): *string | undefined*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)*

**Returns:** *string | undefined*

• **set style**(`value`: string | undefined): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[style](stylablecardelementcontainer.md#style)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

*Inherited from [CardElement](cardelement.md).[useDefaultSizing](cardelement.md#protected-usedefaultsizing)*

**Returns:** *boolean*

___

### `Static` processMarkdown

• **get processMarkdown**(): *function*

*Inherited from [AdaptiveCard](adaptivecard.md).[processMarkdown](adaptivecard.md#static-processmarkdown)*

**Returns:** *function*

▸ (`text`: string): *string*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

• **set processMarkdown**(`value`: function): *void*

*Inherited from [AdaptiveCard](adaptivecard.md).[processMarkdown](adaptivecard.md#static-processmarkdown)*

**Parameters:**

▪ **value**: *function*

▸ (`text`: string): *string*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

**Returns:** *void*

## Methods

###  addAction

▸ **addAction**(`action`: [Action](action.md)): *void*

*Inherited from [ContainerWithActions](containerwithactions.md).[addAction](containerwithactions.md#addaction)*

**Parameters:**

Name | Type |
------ | ------ |
`action` | [Action](action.md) |

**Returns:** *void*

___

###  addItem

▸ **addItem**(`item`: [CardElement](cardelement.md)): *void*

*Inherited from [Container](container.md).[addItem](container.md#additem)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |

**Returns:** *void*

___

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[adjustRenderedElementSize](stylablecardelementcontainer.md#protected-adjustrenderedelementsize)*

*Overrides [CardElement](cardelement.md).[adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyBackground

▸ **applyBackground**(): *void*

*Inherited from [Container](container.md).[applyBackground](container.md#protected-applybackground)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[applyBackground](stylablecardelementcontainer.md#protected-applybackground)*

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[applyPadding](stylablecardelementcontainer.md#protected-applypadding)*

*Overrides [CardElementContainer](cardelementcontainer.md).[applyPadding](cardelementcontainer.md#protected-applypadding)*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

*Inherited from [CardElement](cardelement.md).[asString](cardelement.md#asstring)*

**Returns:** *string | undefined*

___

###  clear

▸ **clear**(): *void*

*Inherited from [ContainerWithActions](containerwithactions.md).[clear](containerwithactions.md#clear)*

*Overrides [Container](container.md).[clear](container.md#clear)*

**Returns:** *void*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

*Inherited from [ContainerWithActions](containerwithactions.md).[getActionAt](containerwithactions.md#getactionat)*

*Overrides [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

*Inherited from [ContainerWithActions](containerwithactions.md).[getActionById](containerwithactions.md#getactionbyid)*

*Overrides [Container](container.md).[getActionById](container.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [ContainerWithActions](containerwithactions.md).[getActionCount](containerwithactions.md#getactioncount)*

*Overrides [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

*Inherited from [ContainerWithActions](containerwithactions.md).[getAllInputs](containerwithactions.md#getallinputs)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getAllInputs](cardelementcontainer.md#getallinputs)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

___

### `Protected` getBleed

▸ **getBleed**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getBleed](stylablecardelementcontainer.md#protected-getbleed)*

**Returns:** *boolean*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultPadding

▸ **getDefaultPadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [AdaptiveCard](adaptivecard.md).[getDefaultPadding](adaptivecard.md#protected-getdefaultpadding)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getDefaultPadding](stylablecardelementcontainer.md#protected-getdefaultpadding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectivePadding](cardelement.md#geteffectivepadding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getEffectiveStyle](stylablecardelementcontainer.md#geteffectivestyle)*

*Overrides [CardElement](cardelement.md).[getEffectiveStyle](cardelement.md#geteffectivestyle)*

**Returns:** *string*

___

###  getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

*Inherited from [CardElement](cardelement.md).[getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md) | undefined*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getElementById](cardelementcontainer.md#getelementbyid)*

*Overrides [CardElement](cardelement.md).[getElementById](cardelement.md#getelementbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getFirstVisibleRenderedItem

▸ **getFirstVisibleRenderedItem**(): *[CardElement](cardelement.md) | undefined*

*Inherited from [Container](container.md).[getFirstVisibleRenderedItem](container.md#getfirstvisiblerendereditem)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getFirstVisibleRenderedItem](cardelementcontainer.md#abstract-getfirstvisiblerendereditem)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *[ActionType](../README.md#actiontype)[]*

*Inherited from [CardElement](cardelement.md).[getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)*

**Returns:** *[ActionType](../README.md#actiontype)[]*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[getHasBackground](adaptivecard.md#protected-gethasbackground)*

*Overrides [Container](container.md).[getHasBackground](container.md#protected-gethasbackground)*

**Returns:** *boolean*

___

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): *boolean*

*Inherited from [ContainerWithActions](containerwithactions.md).[getHasExpandedAction](containerwithactions.md#protected-gethasexpandedaction)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasExpandedAction](stylablecardelementcontainer.md#protected-gethasexpandedaction)*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

*Inherited from [CardElement](cardelement.md).[getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`result` | [PaddingDefinition](paddingdefinition.md) | - |
`processTop` | boolean | true |
`processRight` | boolean | true |
`processBottom` | boolean | true |
`processLeft` | boolean | true |

**Returns:** *void*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[CardElement](cardelement.md)*

*Inherited from [Container](container.md).[getItemAt](container.md#getitemat)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemAt](cardelementcontainer.md#abstract-getitemat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[CardElement](cardelement.md)*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Inherited from [Container](container.md).[getItemCount](container.md#getitemcount)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getItemCount](cardelementcontainer.md#abstract-getitemcount)*

**Returns:** *number*

___

### `Protected` getItemsCollectionPropertyName

▸ **getItemsCollectionPropertyName**(): *string*

*Inherited from [AdaptiveCard](adaptivecard.md).[getItemsCollectionPropertyName](adaptivecard.md#protected-getitemscollectionpropertyname)*

*Overrides [Container](container.md).[getItemsCollectionPropertyName](container.md#protected-getitemscollectionpropertyname)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Inherited from [AdaptiveCard](adaptivecard.md).[getJsonTypeName](adaptivecard.md#getjsontypename)*

*Overrides [Container](container.md).[getJsonTypeName](container.md#getjsontypename)*

**Returns:** *string*

___

###  getLastVisibleRenderedItem

▸ **getLastVisibleRenderedItem**(): *[CardElement](cardelement.md) | undefined*

*Inherited from [Container](container.md).[getLastVisibleRenderedItem](container.md#getlastvisiblerendereditem)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getLastVisibleRenderedItem](cardelementcontainer.md#abstract-getlastvisiblerendereditem)*

**Returns:** *[CardElement](cardelement.md) | undefined*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getPadding](cardelement.md#protected-getpadding)*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getParentContainer](cardelement.md#getparentcontainer)*

**Returns:** *[Container](container.md) | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

*Inherited from [ContainerWithActions](containerwithactions.md).[getResourceInformation](containerwithactions.md#getresourceinformation)*

*Overrides [Container](container.md).[getResourceInformation](container.md#getresourceinformation)*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

*Inherited from [CardElement](cardelement.md).[getRootElement](cardelement.md#getrootelement)*

**Returns:** *[CardElement](cardelement.md)*

___

###  getRootObject

▸ **getRootObject**(): *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[getRootObject](cardobject.md#getrootobject)*

**Returns:** *[CardObject](cardobject.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

###  indexOf

▸ **indexOf**(`cardElement`: [CardElement](cardelement.md)): *number*

*Inherited from [Container](container.md).[indexOf](container.md#indexof)*

*Overrides [CardElement](cardelement.md).[indexOf](cardelement.md#indexof)*

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

___

###  insertItemAfter

▸ **insertItemAfter**(`item`: [CardElement](cardelement.md), `insertAfter`: [CardElement](cardelement.md)): *void*

*Inherited from [Container](container.md).[insertItemAfter](container.md#insertitemafter)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |
`insertAfter` | [CardElement](cardelement.md) |

**Returns:** *void*

___

###  insertItemBefore

▸ **insertItemBefore**(`item`: [CardElement](cardelement.md), `insertBefore`: [CardElement](cardelement.md)): *void*

*Inherited from [Container](container.md).[insertItemBefore](container.md#insertitembefore)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |
`insertBefore` | [CardElement](cardelement.md) |

**Returns:** *void*

___

### `Protected` internalParse

▸ **internalParse**(`source`: any, `context`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [AdaptiveCard](adaptivecard.md).[internalParse](adaptivecard.md#protected-internalparse)*

*Overrides [ContainerWithActions](containerwithactions.md).[internalParse](containerwithactions.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

*Inherited from [AdaptiveCard](adaptivecard.md).[internalRender](adaptivecard.md#protected-internalrender)*

*Overrides [ContainerWithActions](containerwithactions.md).[internalRender](containerwithactions.md#protected-internalrender)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [AdaptiveCard](adaptivecard.md).[internalToJSON](adaptivecard.md#protected-internaltojson)*

*Overrides [ContainerWithActions](containerwithactions.md).[internalToJSON](containerwithactions.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [AdaptiveCard](adaptivecard.md).[internalValidateProperties](adaptivecard.md#internalvalidateproperties)*

*Overrides [ContainerWithActions](containerwithactions.md).[internalValidateProperties](containerwithactions.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryBottom](cardelement.md#isattheverybottom)*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryLeft](cardelement.md#isattheveryleft)*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryRight](cardelement.md#isattheveryright)*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isAtTheVeryTop](cardelement.md#isattheverytop)*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[isBleeding](stylablecardelementcontainer.md#isbleeding)*

*Overrides [CardElement](cardelement.md).[isBleeding](cardelement.md#isbleeding)*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

*Inherited from [ContainerWithActions](containerwithactions.md).[isBleedingAtBottom](containerwithactions.md#isbleedingatbottom)*

*Overrides [Container](container.md).[isBleedingAtBottom](container.md#isbleedingatbottom)*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

*Inherited from [Container](container.md).[isBleedingAtTop](container.md#isbleedingattop)*

*Overrides [CardElement](cardelement.md).[isBleedingAtTop](cardelement.md#isbleedingattop)*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isBottomElement](cardelement.md#isbottomelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDesignMode](cardelement.md#isdesignmode)*

**Returns:** *boolean*

___

### `Protected` isDisplayed

▸ **isDisplayed**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isDisplayed](cardelement.md#protected-isdisplayed)*

**Returns:** *boolean*

___

### `Protected` isElementAllowed

▸ **isElementAllowed**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElementContainer](cardelementcontainer.md).[isElementAllowed](cardelementcontainer.md#protected-iselementallowed)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [Container](container.md).[isFirstElement](container.md#isfirstelement)*

*Overrides [CardElement](cardelement.md).[isFirstElement](cardelement.md#isfirstelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

*Inherited from [CardElement](cardelement.md).[isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [ContainerWithActions](containerwithactions.md).[isLastElement](containerwithactions.md#islastelement)*

*Overrides [Container](container.md).[isLastElement](container.md#islastelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isLeftMostElement](cardelement.md#isleftmostelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isRightMostElement](cardelement.md#isrightmostelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRtl

▸ **isRtl**(): *boolean*

*Inherited from [Container](container.md).[isRtl](container.md#isrtl)*

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

*Inherited from [CardElement](cardelement.md).[isTopElement](cardelement.md#istopelement)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

*Inherited from [CardElement](cardelement.md).[overrideInternalRender](cardelement.md#protected-overrideinternalrender)*

**Returns:** *HTMLElement | undefined*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [CardElement](cardelement.md).[parse](cardelement.md#parse)*

*Overrides [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [CardElementContainer](cardelementcontainer.md).[populateSchema](cardelementcontainer.md#protected-populateschema)*

*Overrides [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  preProcessPropertyValue

▸ **preProcessPropertyValue**(`property`: [PropertyDefinition](propertydefinition.md), `propertyValue?`: any): *any*

*Inherited from [CardObject](cardobject.md).[preProcessPropertyValue](cardobject.md#preprocesspropertyvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`propertyValue?` | any |

**Returns:** *any*

___

###  remove

▸ **remove**(): *boolean*

*Inherited from [CardElement](cardelement.md).[remove](cardelement.md#remove)*

**Returns:** *boolean*

___

###  removeItem

▸ **removeItem**(`item`: [CardElement](cardelement.md)): *boolean*

*Inherited from [Container](container.md).[removeItem](container.md#removeitem)*

*Overrides [CardElementContainer](cardelementcontainer.md).[removeItem](cardelementcontainer.md#abstract-removeitem)*

**Parameters:**

Name | Type |
------ | ------ |
`item` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  render

▸ **render**(`target?`: HTMLElement): *HTMLElement | undefined*

*Inherited from [AdaptiveCard](adaptivecard.md).[render](adaptivecard.md#render)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[render](stylablecardelementcontainer.md#render)*

**Parameters:**

Name | Type |
------ | ------ |
`target?` | HTMLElement |

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

**Returns:** *void*

___

### `Protected` setBleed

▸ **setBleed**(`value`: boolean): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[setBleed](stylablecardelementcontainer.md#protected-setbleed)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setPadding

▸ **setPadding**(`value`: [PaddingDefinition](paddingdefinition.md) | undefined): *void*

*Inherited from [CardElement](cardelement.md).[setPadding](cardelement.md#protected-setpadding)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [PaddingDefinition](paddingdefinition.md) &#124; undefined |

**Returns:** *void*

___

###  setParent

▸ **setParent**(`value`: [CardObject](cardobject.md) | undefined): *void*

*Inherited from [CardObject](cardobject.md).[setParent](cardobject.md#setparent)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [CardObject](cardobject.md) &#124; undefined |

**Returns:** *void*

___

###  setShouldFallback

▸ **setShouldFallback**(`value`: boolean): *void*

*Inherited from [CardObject](cardobject.md).[setShouldFallback](cardobject.md#setshouldfallback)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

###  shouldFallback

▸ **shouldFallback**(): *boolean*

*Inherited from [AdaptiveCard](adaptivecard.md).[shouldFallback](adaptivecard.md#shouldfallback)*

*Overrides [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)*

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

### `Protected` supportsExcplitiHeight

▸ **supportsExcplitiHeight**(): *boolean*

*Inherited from [Container](container.md).[supportsExcplitiHeight](container.md#protected-supportsexcplitiheight)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [AdaptiveCard](adaptivecard.md).[toJSON](adaptivecard.md#tojson)*

*Overrides [CardElement](cardelement.md).[toJSON](cardelement.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

*Inherited from [Container](container.md).[truncateOverflow](container.md#protected-truncateoverflow)*

*Overrides [CardElement](cardelement.md).[truncateOverflow](cardelement.md#protected-truncateoverflow)*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

*Inherited from [Container](container.md).[undoOverflowTruncation](container.md#protected-undooverflowtruncation)*

*Overrides [CardElement](cardelement.md).[undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

*Inherited from [AdaptiveCard](adaptivecard.md).[updateLayout](adaptivecard.md#updatelayout)*

*Overrides [CardElementContainer](cardelementcontainer.md).[updateLayout](cardelementcontainer.md#updatelayout)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processChildren` | boolean | true |

**Returns:** *void*

___

###  validateProperties

▸ **validateProperties**(): *[ValidationResults](validationresults.md)*

*Inherited from [CardObject](cardobject.md).[validateProperties](cardobject.md#validateproperties)*

**Returns:** *[ValidationResults](validationresults.md)*

___

### `Static` applyMarkdown

▸ **applyMarkdown**(`text`: string): *[IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)*

*Inherited from [AdaptiveCard](adaptivecard.md).[applyMarkdown](adaptivecard.md#static-applymarkdown)*

**Parameters:**

Name | Type |
------ | ------ |
`text` | string |

**Returns:** *[IMarkdownProcessingResult](../interfaces/imarkdownprocessingresult.md)*
