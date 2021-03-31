[Adaptive Cards Javascript SDK](../README.md) › [CardElement](cardelement.md)

# Class: CardElement

## Hierarchy

  ↳ [CardObject](cardobject.md)

  ↳ **CardElement**

  ↳ [BaseTextBlock](basetextblock.md)

  ↳ [RichTextBlock](richtextblock.md)

  ↳ [FactSet](factset.md)

  ↳ [Image](image.md)

  ↳ [CardElementContainer](cardelementcontainer.md)

  ↳ [Media](media.md)

  ↳ [Input](input.md)

  ↳ [ActionSet](actionset.md)

## Index

### Constructors

* [constructor](cardelement.md#constructor)

### Properties

* [_parent](cardelement.md#protected-optional-_parent)
* [_renderedElement](cardelement.md#protected-optional-_renderedelement)
* [customCssSelector](cardelement.md#optional-customcssselector)
* [height](cardelement.md#height)
* [horizontalAlignment](cardelement.md#horizontalalignment)
* [id](cardelement.md#optional-id)
* [maxVersion](cardelement.md#maxversion)
* [onPreProcessPropertyValue](cardelement.md#optional-onpreprocesspropertyvalue)
* [separator](cardelement.md#separator)
* [spacing](cardelement.md#spacing)
* [heightProperty](cardelement.md#static-heightproperty)
* [horizontalAlignmentProperty](cardelement.md#static-horizontalalignmentproperty)
* [idProperty](cardelement.md#static-idproperty)
* [isVisibleProperty](cardelement.md#static-isvisibleproperty)
* [langProperty](cardelement.md#static-langproperty)
* [onRegisterCustomProperties](cardelement.md#static-optional-onregistercustomproperties)
* [requiresProperty](cardelement.md#static-requiresproperty)
* [separatorProperty](cardelement.md#static-separatorproperty)
* [spacingProperty](cardelement.md#static-spacingproperty)
* [typeNameProperty](cardelement.md#static-typenameproperty)

### Accessors

* [allowCustomPadding](cardelement.md#protected-allowcustompadding)
* [defaultStyle](cardelement.md#protected-defaultstyle)
* [hasVisibleSeparator](cardelement.md#hasvisibleseparator)
* [hostConfig](cardelement.md#hostconfig)
* [index](cardelement.md#index)
* [isInline](cardelement.md#isinline)
* [isInteractive](cardelement.md#isinteractive)
* [isStandalone](cardelement.md#isstandalone)
* [isVisible](cardelement.md#isvisible)
* [lang](cardelement.md#lang)
* [parent](cardelement.md#parent)
* [renderedElement](cardelement.md#renderedelement)
* [requires](cardelement.md#requires)
* [separatorElement](cardelement.md#separatorelement)
* [separatorOrientation](cardelement.md#protected-separatororientation)
* [useDefaultSizing](cardelement.md#protected-usedefaultsizing)

### Methods

* [adjustRenderedElementSize](cardelement.md#protected-adjustrenderedelementsize)
* [applyPadding](cardelement.md#protected-applypadding)
* [asString](cardelement.md#asstring)
* [createPlaceholderElement](cardelement.md#protected-createplaceholderelement)
* [getActionAt](cardelement.md#getactionat)
* [getActionById](cardelement.md#getactionbyid)
* [getActionCount](cardelement.md#getactioncount)
* [getAllInputs](cardelement.md#getallinputs)
* [getCustomProperty](cardelement.md#getcustomproperty)
* [getDefaultPadding](cardelement.md#protected-getdefaultpadding)
* [getEffectivePadding](cardelement.md#geteffectivepadding)
* [getEffectiveStyle](cardelement.md#geteffectivestyle)
* [getEffectiveStyleDefinition](cardelement.md#geteffectivestyledefinition)
* [getElementById](cardelement.md#getelementbyid)
* [getForbiddenActionTypes](cardelement.md#getforbiddenactiontypes)
* [getHasBackground](cardelement.md#protected-gethasbackground)
* [getImmediateSurroundingPadding](cardelement.md#getimmediatesurroundingpadding)
* [getJsonTypeName](cardelement.md#abstract-getjsontypename)
* [getPadding](cardelement.md#protected-getpadding)
* [getParentContainer](cardelement.md#getparentcontainer)
* [getResourceInformation](cardelement.md#getresourceinformation)
* [getRootElement](cardelement.md#getrootelement)
* [getRootObject](cardelement.md#getrootobject)
* [getSchema](cardelement.md#getschema)
* [getSchemaKey](cardelement.md#protected-getschemakey)
* [getValue](cardelement.md#protected-getvalue)
* [hasAllDefaultValues](cardelement.md#hasalldefaultvalues)
* [hasDefaultValue](cardelement.md#hasdefaultvalue)
* [indexOf](cardelement.md#indexof)
* [internalParse](cardelement.md#protected-internalparse)
* [internalRender](cardelement.md#protected-abstract-internalrender)
* [internalToJSON](cardelement.md#protected-internaltojson)
* [internalValidateProperties](cardelement.md#internalvalidateproperties)
* [isAtTheVeryBottom](cardelement.md#isattheverybottom)
* [isAtTheVeryLeft](cardelement.md#isattheveryleft)
* [isAtTheVeryRight](cardelement.md#isattheveryright)
* [isAtTheVeryTop](cardelement.md#isattheverytop)
* [isBleeding](cardelement.md#isbleeding)
* [isBleedingAtBottom](cardelement.md#isbleedingatbottom)
* [isBleedingAtTop](cardelement.md#isbleedingattop)
* [isBottomElement](cardelement.md#isbottomelement)
* [isDesignMode](cardelement.md#isdesignmode)
* [isDisplayed](cardelement.md#protected-isdisplayed)
* [isFirstElement](cardelement.md#isfirstelement)
* [isHiddenDueToOverflow](cardelement.md#ishiddenduetooverflow)
* [isLastElement](cardelement.md#islastelement)
* [isLeftMostElement](cardelement.md#isleftmostelement)
* [isRightMostElement](cardelement.md#isrightmostelement)
* [isTopElement](cardelement.md#istopelement)
* [overrideInternalRender](cardelement.md#protected-overrideinternalrender)
* [parse](cardelement.md#parse)
* [populateSchema](cardelement.md#protected-populateschema)
* [preProcessPropertyValue](cardelement.md#preprocesspropertyvalue)
* [remove](cardelement.md#remove)
* [render](cardelement.md#render)
* [resetDefaultValues](cardelement.md#resetdefaultvalues)
* [setCustomProperty](cardelement.md#setcustomproperty)
* [setPadding](cardelement.md#protected-setpadding)
* [setParent](cardelement.md#setparent)
* [setShouldFallback](cardelement.md#setshouldfallback)
* [setValue](cardelement.md#protected-setvalue)
* [shouldFallback](cardelement.md#shouldfallback)
* [shouldSerialize](cardelement.md#protected-shouldserialize)
* [toJSON](cardelement.md#tojson)
* [truncateOverflow](cardelement.md#protected-truncateoverflow)
* [undoOverflowTruncation](cardelement.md#protected-undooverflowtruncation)
* [updateLayout](cardelement.md#updatelayout)
* [validateProperties](cardelement.md#validateproperties)

## Constructors

###  constructor

\+ **new CardElement**(): *[CardElement](cardelement.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Returns:** *[CardElement](cardelement.md)*

## Properties

### `Protected` `Optional` _parent

• **_parent**? : *[CardObject](cardobject.md)*

*Inherited from [CardObject](cardobject.md).[_parent](cardobject.md#protected-optional-_parent)*

___

### `Protected` `Optional` _renderedElement

• **_renderedElement**? : *HTMLElement*

*Inherited from [CardObject](cardobject.md).[_renderedElement](cardobject.md#protected-optional-_renderedelement)*

___

### `Optional` customCssSelector

• **customCssSelector**? : *undefined | string*

___

###  height

• **height**: *[CardElementHeight](../README.md#cardelementheight)*

___

###  horizontalAlignment

• **horizontalAlignment**: *[HorizontalAlignment](../enums/horizontalalignment.md)*

___

### `Optional` id

• **id**? : *undefined | string*

*Inherited from [CardObject](cardobject.md).[id](cardobject.md#optional-id)*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

### `Optional` onPreProcessPropertyValue

• **onPreProcessPropertyValue**? : *undefined | function*

*Inherited from [CardObject](cardobject.md).[onPreProcessPropertyValue](cardobject.md#optional-onpreprocesspropertyvalue)*

___

###  separator

• **separator**: *boolean*

___

###  spacing

• **spacing**: *[Spacing](../enums/spacing.md)*

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

___

### `Static` horizontalAlignmentProperty

▪ **horizontalAlignmentProperty**: *[EnumProperty](enumproperty.md)‹[HorizontalAlignment](../enums/horizontalalignment.md)›* = new EnumProperty(
        Versions.v1_0,
        "horizontalAlignment",
        Enums.HorizontalAlignment,
        Enums.HorizontalAlignment.Left)

___

### `Static` idProperty

▪ **idProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "id")

*Inherited from [CardObject](cardobject.md).[idProperty](cardobject.md#static-idproperty)*

___

### `Static` isVisibleProperty

▪ **isVisibleProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_2, "isVisible", true)

___

### `Static` langProperty

▪ **langProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_1, "lang", true, /^[a-z]{2,3}$/ig)

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

### `Static` separatorProperty

▪ **separatorProperty**: *[BoolProperty](boolproperty.md)‹›* = new BoolProperty(Versions.v1_0, "separator", false)

___

### `Static` spacingProperty

▪ **spacingProperty**: *[EnumProperty](enumproperty.md)‹[Spacing](../enums/spacing.md)›* = new EnumProperty(
        Versions.v1_0,
        "spacing",
        Enums.Spacing,
        Enums.Spacing.Default)

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

## Accessors

### `Protected` allowCustomPadding

• **get allowCustomPadding**(): *boolean*

**Returns:** *boolean*

___

### `Protected` defaultStyle

• **get defaultStyle**(): *string*

**Returns:** *string*

___

###  hasVisibleSeparator

• **get hasVisibleSeparator**(): *boolean*

**Returns:** *boolean*

___

###  hostConfig

• **get hostConfig**(): *[HostConfig](hostconfig.md)*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Returns:** *[HostConfig](hostconfig.md)*

• **set hostConfig**(`value`: [HostConfig](hostconfig.md)): *void*

*Overrides [CardObject](cardobject.md).[hostConfig](cardobject.md#hostconfig)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | [HostConfig](hostconfig.md) |

**Returns:** *void*

___

###  index

• **get index**(): *number*

**Returns:** *number*

___

###  isInline

• **get isInline**(): *boolean*

**Returns:** *boolean*

___

###  isInteractive

• **get isInteractive**(): *boolean*

**Returns:** *boolean*

___

###  isStandalone

• **get isStandalone**(): *boolean*

**Returns:** *boolean*

___

###  isVisible

• **get isVisible**(): *boolean*

**Returns:** *boolean*

• **set isVisible**(`value`: boolean): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | boolean |

**Returns:** *void*

___

###  lang

• **get lang**(): *string | undefined*

**Returns:** *string | undefined*

• **set lang**(`value`: string | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  parent

• **get parent**(): *[CardElement](cardelement.md) | undefined*

*Overrides [CardObject](cardobject.md).[parent](cardobject.md#parent)*

**Returns:** *[CardElement](cardelement.md) | undefined*

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

###  separatorElement

• **get separatorElement**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

### `Protected` separatorOrientation

• **get separatorOrientation**(): *[Orientation](../enums/orientation.md)*

**Returns:** *[Orientation](../enums/orientation.md)*

___

### `Protected` useDefaultSizing

• **get useDefaultSizing**(): *boolean*

**Returns:** *boolean*

## Methods

### `Protected` adjustRenderedElementSize

▸ **adjustRenderedElementSize**(`renderedElement`: HTMLElement): *void*

**Parameters:**

Name | Type |
------ | ------ |
`renderedElement` | HTMLElement |

**Returns:** *void*

___

### `Protected` applyPadding

▸ **applyPadding**(): *void*

**Returns:** *void*

___

###  asString

▸ **asString**(): *string | undefined*

**Returns:** *string | undefined*

___

### `Protected` createPlaceholderElement

▸ **createPlaceholderElement**(): *HTMLElement*

**Returns:** *HTMLElement*

___

###  getActionAt

▸ **getActionAt**(`index`: number): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionById

▸ **getActionById**(`id`: string): *[Action](action.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[Action](action.md) | undefined*

___

###  getActionCount

▸ **getActionCount**(): *number*

**Returns:** *number*

___

###  getAllInputs

▸ **getAllInputs**(`processActions`: boolean): *[Input](input.md)[]*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`processActions` | boolean | true |

**Returns:** *[Input](input.md)[]*

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

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectivePadding

▸ **getEffectivePadding**(): *[PaddingDefinition](paddingdefinition.md)*

**Returns:** *[PaddingDefinition](paddingdefinition.md)*

___

###  getEffectiveStyle

▸ **getEffectiveStyle**(): *string*

**Returns:** *string*

___

###  getEffectiveStyleDefinition

▸ **getEffectiveStyleDefinition**(): *[ContainerStyleDefinition](containerstyledefinition.md)*

**Returns:** *[ContainerStyleDefinition](containerstyledefinition.md)*

___

###  getElementById

▸ **getElementById**(`id`: string): *[CardElement](cardelement.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`id` | string |

**Returns:** *[CardElement](cardelement.md) | undefined*

___

###  getForbiddenActionTypes

▸ **getForbiddenActionTypes**(): *[ActionType](../README.md#actiontype)[]*

**Returns:** *[ActionType](../README.md#actiontype)[]*

___

### `Protected` getHasBackground

▸ **getHasBackground**(): *boolean*

**Returns:** *boolean*

___

###  getImmediateSurroundingPadding

▸ **getImmediateSurroundingPadding**(`result`: [PaddingDefinition](paddingdefinition.md), `processTop`: boolean, `processRight`: boolean, `processBottom`: boolean, `processLeft`: boolean): *void*

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

### `Abstract` getJsonTypeName

▸ **getJsonTypeName**(): *string*

*Inherited from [CardObject](cardobject.md).[getJsonTypeName](cardobject.md#abstract-getjsontypename)*

**Returns:** *string*

___

### `Protected` getPadding

▸ **getPadding**(): *[PaddingDefinition](paddingdefinition.md) | undefined*

**Returns:** *[PaddingDefinition](paddingdefinition.md) | undefined*

___

###  getParentContainer

▸ **getParentContainer**(): *[Container](container.md) | undefined*

**Returns:** *[Container](container.md) | undefined*

___

###  getResourceInformation

▸ **getResourceInformation**(): *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

**Returns:** *[IResourceInformation](../interfaces/iresourceinformation.md)[]*

___

###  getRootElement

▸ **getRootElement**(): *[CardElement](cardelement.md)*

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

**Parameters:**

Name | Type |
------ | ------ |
`cardElement` | [CardElement](cardelement.md) |

**Returns:** *number*

___

### `Protected` internalParse

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` `Abstract` internalRender

▸ **internalRender**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  internalValidateProperties

▸ **internalValidateProperties**(`context`: [ValidationResults](validationresults.md)): *void*

*Inherited from [CardObject](cardobject.md).[internalValidateProperties](cardobject.md#internalvalidateproperties)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [ValidationResults](validationresults.md) |

**Returns:** *void*

___

###  isAtTheVeryBottom

▸ **isAtTheVeryBottom**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryLeft

▸ **isAtTheVeryLeft**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryRight

▸ **isAtTheVeryRight**(): *boolean*

**Returns:** *boolean*

___

###  isAtTheVeryTop

▸ **isAtTheVeryTop**(): *boolean*

**Returns:** *boolean*

___

###  isBleeding

▸ **isBleeding**(): *boolean*

**Returns:** *boolean*

___

###  isBleedingAtBottom

▸ **isBleedingAtBottom**(): *boolean*

**Returns:** *boolean*

___

###  isBleedingAtTop

▸ **isBleedingAtTop**(): *boolean*

**Returns:** *boolean*

___

###  isBottomElement

▸ **isBottomElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isDesignMode

▸ **isDesignMode**(): *boolean*

**Returns:** *boolean*

___

### `Protected` isDisplayed

▸ **isDisplayed**(): *boolean*

**Returns:** *boolean*

___

###  isFirstElement

▸ **isFirstElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isHiddenDueToOverflow

▸ **isHiddenDueToOverflow**(): *boolean*

**Returns:** *boolean*

___

###  isLastElement

▸ **isLastElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isLeftMostElement

▸ **isLeftMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isRightMostElement

▸ **isRightMostElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

###  isTopElement

▸ **isTopElement**(`element`: [CardElement](cardelement.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`element` | [CardElement](cardelement.md) |

**Returns:** *boolean*

___

### `Protected` overrideInternalRender

▸ **overrideInternalRender**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

###  parse

▸ **parse**(`source`: any, `context?`: [SerializationContext](serializationcontext.md)): *void*

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

*Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

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

**Returns:** *boolean*

___

###  render

▸ **render**(): *HTMLElement | undefined*

**Returns:** *HTMLElement | undefined*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

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

*Overrides [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [SerializationContext](serializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Overrides [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [SerializationContext](serializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*

___

### `Protected` truncateOverflow

▸ **truncateOverflow**(`maxHeight`: number): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`maxHeight` | number |

**Returns:** *boolean*

___

### `Protected` undoOverflowTruncation

▸ **undoOverflowTruncation**(): *void*

**Returns:** *void*

___

###  updateLayout

▸ **updateLayout**(`processChildren`: boolean): *void*

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
