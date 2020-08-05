[Adaptive Cards Javascript SDK](../README.md) › [Column](column.md)

# Class: Column

## Hierarchy

  ↳ [Container](container.md)

  ↳ **Column**

## Index

### Constructors

* [constructor](column.md#constructor)

### Properties

* [_parent](column.md#protected-optional-_parent)
* [_renderedElement](column.md#protected-optional-_renderedelement)
* [_selectAction](column.md#protected-optional-_selectaction)
* [allowVerticalOverflow](column.md#allowverticaloverflow)
* [customCssSelector](column.md#optional-customcssselector)
* [height](column.md#height)
* [horizontalAlignment](column.md#horizontalalignment)
* [id](column.md#optional-id)
* [maxVersion](column.md#maxversion)
* [minPixelHeight](column.md#optional-minpixelheight)
* [onPreProcessPropertyValue](column.md#optional-onpreprocesspropertyvalue)
* [rtl](column.md#optional-rtl)
* [separator](column.md#separator)
* [spacing](column.md#spacing)
* [verticalContentAlignment](column.md#verticalcontentalignment)
* [width](column.md#width)
* [backgroundImageProperty](column.md#static-backgroundimageproperty)
* [bleedProperty](column.md#static-bleedproperty)
* [heightProperty](column.md#static-heightproperty)
* [horizontalAlignmentProperty](column.md#static-horizontalalignmentproperty)
* [idProperty](column.md#static-idproperty)
* [isVisibleProperty](column.md#static-isvisibleproperty)
* [langProperty](column.md#static-langproperty)
* [minHeightProperty](column.md#static-minheightproperty)
* [onRegisterCustomProperties](column.md#static-optional-onregistercustomproperties)
* [requiresProperty](column.md#static-requiresproperty)
* [rtlProperty](column.md#static-rtlproperty)
* [selectActionProperty](column.md#static-selectactionproperty)
* [separatorProperty](column.md#static-separatorproperty)
* [spacingProperty](column.md#static-spacingproperty)
* [styleProperty](column.md#static-styleproperty)
* [typeNameProperty](column.md#static-typenameproperty)
* [verticalContentAlignmentProperty](column.md#static-verticalcontentalignmentproperty)
* [widthProperty](column.md#static-widthproperty)

### Accessors

* [allowCustomPadding](column.md#protected-allowcustompadding)
* [allowCustomStyle](column.md#protected-allowcustomstyle)
* [backgroundImage](column.md#backgroundimage)
* [bleed](column.md#bleed)
* [defaultStyle](column.md#protected-defaultstyle)
* [hasExplicitStyle](column.md#protected-hasexplicitstyle)
* [hasVisibleSeparator](column.md#hasvisibleseparator)
* [hostConfig](column.md#hostconfig)
* [index](column.md#index)
* [isInline](column.md#isinline)
* [isInteractive](column.md#isinteractive)
* [isSelectable](column.md#protected-isselectable)
* [isStandalone](column.md#isstandalone)
* [isVisible](column.md#isvisible)
* [lang](column.md#lang)
* [padding](column.md#padding)
* [parent](column.md#parent)
* [renderedActionCount](column.md#protected-renderedactioncount)
* [renderedElement](column.md#renderedelement)
* [requires](column.md#requires)
* [selectAction](column.md#selectaction)
* [separatorElement](column.md#separatorelement)
* [separatorOrientation](column.md#protected-separatororientation)
* [style](column.md#style)
* [useDefaultSizing](column.md#protected-usedefaultsizing)

### Methods

* [addItem](column.md#additem)
* [adjustRenderedElementSize](column.md#protected-adjustrenderedelementsize)
* [applyBackground](column.md#protected-applybackground)
* [applyPadding](column.md#protected-applypadding)
* [asString](column.md#asstring)
* [clear](column.md#clear)
* [createPlaceholderElement](column.md#protected-createplaceholderelement)
* [getActionAt](column.md#getactionat)
* [getActionById](column.md#getactionbyid)
* [getActionCount](column.md#getactioncount)
* [getAllInputs](column.md#getallinputs)
* [getBleed](column.md#protected-getbleed)
* [getCustomProperty](column.md#getcustomproperty)
* [getDefaultPadding](column.md#protected-getdefaultpadding)
* [getEffectivePadding](column.md#geteffectivepadding)
* [getEffectiveStyle](column.md#geteffectivestyle)
* [getEffectiveStyleDefinition](column.md#geteffectivestyledefinition)
* [getElementById](column.md#getelementbyid)
* [getFirstVisibleRenderedItem](column.md#getfirstvisiblerendereditem)
* [getForbiddenActionTypes](column.md#getforbiddenactiontypes)
* [getHasBackground](column.md#protected-gethasbackground)
* [getHasExpandedAction](column.md#protected-gethasexpandedaction)
* [getImmediateSurroundingPadding](column.md#getimmediatesurroundingpadding)
* [getItemAt](column.md#getitemat)
* [getItemCount](column.md#getitemcount)
* [getItemsCollectionPropertyName](column.md#protected-getitemscollectionpropertyname)
* [getJsonTypeName](column.md#getjsontypename)
* [getLastVisibleRenderedItem](column.md#getlastvisiblerendereditem)
* [getPadding](column.md#protected-getpadding)
* [getParentContainer](column.md#getparentcontainer)
* [getResourceInformation](column.md#getresourceinformation)
* [getRootElement](column.md#getrootelement)
* [getRootObject](column.md#getrootobject)
* [getSchema](column.md#getschema)
* [getSchemaKey](column.md#protected-getschemakey)
* [getValue](column.md#protected-getvalue)
* [hasAllDefaultValues](column.md#hasalldefaultvalues)
* [hasDefaultValue](column.md#hasdefaultvalue)
* [indexOf](column.md#indexof)
* [insertItemAfter](column.md#insertitemafter)
* [insertItemBefore](column.md#insertitembefore)
* [internalParse](column.md#protected-internalparse)
* [internalRender](column.md#protected-internalrender)
* [internalToJSON](column.md#protected-internaltojson)
* [internalValidateProperties](column.md#internalvalidateproperties)
* [isAtTheVeryBottom](column.md#isattheverybottom)
* [isAtTheVeryLeft](column.md#isattheveryleft)
* [isAtTheVeryRight](column.md#isattheveryright)
* [isAtTheVeryTop](column.md#isattheverytop)
* [isBleeding](column.md#isbleeding)
* [isBleedingAtBottom](column.md#isbleedingatbottom)
* [isBleedingAtTop](column.md#isbleedingattop)
* [isBottomElement](column.md#isbottomelement)
* [isDesignMode](column.md#isdesignmode)
* [isDisplayed](column.md#protected-isdisplayed)
* [isElementAllowed](column.md#protected-iselementallowed)
* [isFirstElement](column.md#isfirstelement)
* [isHiddenDueToOverflow](column.md#ishiddenduetooverflow)
* [isLastElement](column.md#islastelement)
* [isLeftMostElement](column.md#isleftmostelement)
* [isRightMostElement](column.md#isrightmostelement)
* [isRtl](column.md#isrtl)
* [isTopElement](column.md#istopelement)
* [overrideInternalRender](column.md#protected-overrideinternalrender)
* [parse](column.md#parse)
* [populateSchema](column.md#protected-populateschema)
* [preProcessPropertyValue](column.md#preprocesspropertyvalue)
* [remove](column.md#remove)
* [removeItem](column.md#removeitem)
* [render](column.md#render)
* [resetDefaultValues](column.md#resetdefaultvalues)
* [setBleed](column.md#protected-setbleed)
* [setCustomProperty](column.md#setcustomproperty)
* [setPadding](column.md#protected-setpadding)
* [setParent](column.md#setparent)
* [setShouldFallback](column.md#setshouldfallback)
* [setValue](column.md#protected-setvalue)
* [shouldFallback](column.md#shouldfallback)
* [shouldSerialize](column.md#protected-shouldserialize)
* [supportsExcplitiHeight](column.md#protected-supportsexcplitiheight)
* [toJSON](column.md#tojson)
* [truncateOverflow](column.md#protected-truncateoverflow)
* [undoOverflowTruncation](column.md#protected-undooverflowtruncation)
* [updateLayout](column.md#updatelayout)
* [validateProperties](column.md#validateproperties)

## Constructors

###  constructor

\+ **new Column**(`width`: [ColumnWidth](../README.md#columnwidth)): *[Column](column.md)*

*Overrides [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`width` | [ColumnWidth](../README.md#columnwidth) | "stretch" |

**Returns:** *[Column](column.md)*

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

###  verticalContentAlignment

• **verticalContentAlignment**: *[VerticalAlignment](../enums/verticalalignment.md)* = Enums.VerticalAlignment.Top

*Inherited from [Container](container.md).[verticalContentAlignment](container.md#verticalcontentalignment)*

___

###  width

• **width**: *[ColumnWidth](../README.md#columnwidth)* = "stretch"

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

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

___

### `Static` requiresProperty

▪ **requiresProperty**: *[SerializableObjectProperty](serializableobjectproperty.md)‹›* = new SerializableObjectProperty(
        Versions.v1_2,
        "requires",
        HostCapabilities,
        new HostCapabilities())

*Inherited from [CardObject](cardobject.md).[requiresProperty](cardobject.md#static-requiresproperty)*

___

### `Static` rtlProperty

▪ **rtlProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "rtl")

*Inherited from [Container](container.md).[rtlProperty](container.md#static-rtlproperty)*

___

### `Static` selectActionProperty

▪ **selectActionProperty**: *[ActionProperty](actionproperty.md)‹›* = new ActionProperty(Versions.v1_0, "selectAction", [ "Action.ShowCard" ])

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

### `Static` verticalContentAlignmentProperty

▪ **verticalContentAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[VerticalAlignment](../enums/verticalalignment.md)›* = new EnumProperty(Versions.v1_1, "verticalContentAlignment", Enums.VerticalAlignment, Enums.VerticalAlignment.Top)

*Inherited from [Container](container.md).[verticalContentAlignmentProperty](container.md#static-verticalcontentalignmentproperty)*

___

### `Static` widthProperty

▪ **widthProperty**: *[CustomProperty](customproperty.md)‹"auto" | "stretch" | [SizeAndUnit](sizeandunit.md)‹››* = new CustomProperty<ColumnWidth>(
        Versions.v1_0,
        "width",
        (sender: SerializableObject, property: PropertyDefinition, source: PropertyBag, context: BaseSerializationContext) => {
            let result: ColumnWidth = property.defaultValue;
            let value = source[property.name];
            let invalidWidth = false;

            if (typeof value === "number" && !isNaN(value)) {
                result = new SizeAndUnit(value, Enums.SizeUnit.Weight);
            }
            else if (value === "auto" || value === "stretch") {
                result = value;
            }
            else if (typeof value === "string") {
                try {
                    result = SizeAndUnit.parse(value);

                    if (result.unit === Enums.SizeUnit.Pixel && property.targetVersion.compareTo(context.targetVersion) > 0) {
                        invalidWidth = true;
                    }
                }
                catch (e) {
                    invalidWidth = true;
                }
            }
            else {
                invalidWidth = true;
            }

            if (invalidWidth) {
                context.logParseEvent(
                    sender,
                    Enums.ValidationEvent.InvalidPropertyValue,
                    Strings.errors.invalidColumnWidth(value));

                result = "auto";
            }

            return result;
        },
        (sender: SerializableObject, property: PropertyDefinition, target: PropertyBag, value: ColumnWidth, context: BaseSerializationContext) => {
            if (value instanceof SizeAndUnit) {
                if (value.unit === Enums.SizeUnit.Pixel) {
                    context.serializeValue(target, "width", value.physicalSize + "px");
                }
                else {
                    context.serializeNumber(target, "width", value.physicalSize);
                }
            }
            else {
                context.serializeValue(target, "width", value);
            }
        },
        "stretch")

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

*Inherited from [CardElement](cardelement.md).[allowCustomPadding](cardelement.md#protected-allowcustompadding)*

**Returns:** *boolean*

___

### `Protected` allowCustomStyle

• **get allowCustomStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[allowCustomStyle](stylablecardelementcontainer.md#protected-allowcustomstyle)*

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

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

*Inherited from [CardElement](cardelement.md).[defaultStyle](cardelement.md#protected-defaultstyle)*

**Returns:** *string*

___

### `Protected` hasExplicitStyle

• **get hasExplicitStyle**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[hasExplicitStyle](stylablecardelementcontainer.md#protected-hasexplicitstyle)*

**Returns:** *boolean*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

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

### `Protected` renderedActionCount

• **get renderedActionCount**(): *number*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[renderedActionCount](stylablecardelementcontainer.md#protected-renderedactioncount)*

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

*Overrides [CardElement](cardelement.md).[separatorOrientation](cardelement.md#protected-separatororientation)*

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

## Methods

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

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[adjustRenderedElementSize](stylablecardelementcontainer.md#protected-adjustrenderedelementsize)*

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

*Inherited from [Container](container.md).[clear](container.md#clear)*

**Returns:** *void*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

*Inherited from [CardElement](cardelement.md).[createPlaceholderElement](cardelement.md#protected-createplaceholderelement)*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

*Inherited from [CardElement](cardelement.md).[getActionAt](cardelement.md#getactionat)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

*Inherited from [Container](container.md).[getActionById](container.md#getactionbyid)*

*Overrides [CardElement](cardelement.md).[getActionById](cardelement.md#getactionbyid)*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionCount

▸ **getActionCount**(): *number*

*Inherited from [CardElement](cardelement.md).[getActionCount](cardelement.md#getactioncount)*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

*Inherited from [CardElementContainer](cardelementcontainer.md).[getAllInputs](cardelementcontainer.md#getallinputs)*

*Overrides [CardElement](cardelement.md).[getAllInputs](cardelement.md#getallinputs)*

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

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getDefaultPadding](stylablecardelementcontainer.md#protected-getdefaultpadding)*

*Overrides [CardElement](cardelement.md).[getDefaultPadding](cardelement.md#protected-getdefaultpadding)*

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

*Inherited from [Container](container.md).[getHasBackground](container.md#protected-gethasbackground)*

*Overrides [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasBackground](stylablecardelementcontainer.md#protected-gethasbackground)*

**Returns:** *boolean*

___

### `Protected` getHasExpandedAction

▸ **getHasExpandedAction**(): *boolean*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[getHasExpandedAction](stylablecardelementcontainer.md#protected-gethasexpandedaction)*

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

*Inherited from [Container](container.md).[getItemsCollectionPropertyName](container.md#protected-getitemscollectionpropertyname)*

**Returns:** *string*

___

###  getJsonTypeName

▸ **getJsonTypeName**(): *string*

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

*Inherited from [Container](container.md).[getResourceInformation](container.md#getresourceinformation)*

*Overrides [CardElementContainer](cardelementcontainer.md).[getResourceInformation](cardelementcontainer.md#getresourceinformation)*

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

*Inherited from [CardObject](cardobject.md).[getSchemaKey](cardobject.md#protected-getschemakey)*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

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

*Inherited from [Container](container.md).[internalParse](container.md#protected-internalparse)*

*Overrides [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

*Inherited from [Container](container.md).[internalRender](container.md#protected-internalrender)*

*Overrides [CardElement](cardelement.md).[internalRender](cardelement.md#protected-abstract-internalrender)*

**Returns:** *HTMLElement | undefined*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): *void*

*Inherited from [Container](container.md).[internalToJSON](container.md#protected-internaltojson)*

*Overrides [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[internalValidateProperties](stylablecardelementcontainer.md#internalvalidateproperties)*

*Overrides [CardElementContainer](cardelementcontainer.md).[internalValidateProperties](cardelementcontainer.md#internalvalidateproperties)*

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

*Inherited from [Container](container.md).[isBleedingAtBottom](container.md#isbleedingatbottom)*

*Overrides [CardElement](cardelement.md).[isBleedingAtBottom](cardelement.md#isbleedingatbottom)*

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

*Inherited from [Container](container.md).[isLastElement](container.md#islastelement)*

*Overrides [CardElement](cardelement.md).[isLastElement](cardelement.md#islastelement)*

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

▸ **render**(): *HTMLElement | undefined*

*Inherited from [StylableCardElementContainer](stylablecardelementcontainer.md).[render](stylablecardelementcontainer.md#render)*

*Overrides [CardElementContainer](cardelementcontainer.md).[render](cardelementcontainer.md#render)*

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

*Inherited from [CardObject](cardobject.md).[shouldFallback](cardobject.md#shouldfallback)*

**Returns:** *boolean*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [SerializationContext](serializationcontext.md)): *boolean*

*Overrides [CardElement](cardelement.md).[shouldSerialize](cardelement.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *boolean*

___

### `Protected` supportsExcplitiHeight

▸ **supportsExcplitiHeight**(): *boolean*

*Inherited from [Container](container.md).[supportsExcplitiHeight](container.md#protected-supportsexcplitiheight)*

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [CardElement](cardelement.md).[toJSON](cardelement.md#tojson)*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

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

*Inherited from [CardElementContainer](cardelementcontainer.md).[updateLayout](cardelementcontainer.md#updatelayout)*

*Overrides [CardElement](cardelement.md).[updateLayout](cardelement.md#updatelayout)*

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
