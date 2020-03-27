[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [HostConfig](_host_config_.hostconfig.md)

# Class: HostConfig

## Hierarchy

* **HostConfig**

## Index

### Constructors

* [constructor](_host_config_.hostconfig.md#constructor)

### Properties

* [actions](_host_config_.hostconfig.md#actions)
* [adaptiveCard](_host_config_.hostconfig.md#adaptivecard)
* [alwaysAllowBleed](_host_config_.hostconfig.md#alwaysallowbleed)
* [choiceSetInputValueSeparator](_host_config_.hostconfig.md#choicesetinputvalueseparator)
* [containerStyles](_host_config_.hostconfig.md#containerstyles)
* [cssClassNamePrefix](_host_config_.hostconfig.md#cssclassnameprefix)
* [factSet](_host_config_.hostconfig.md#factset)
* [fontTypes](_host_config_.hostconfig.md#fonttypes)
* [hostCapabilities](_host_config_.hostconfig.md#hostcapabilities)
* [imageSet](_host_config_.hostconfig.md#imageset)
* [lineHeights](_host_config_.hostconfig.md#optional-lineheights)
* [media](_host_config_.hostconfig.md#media)
* [supportsInteractivity](_host_config_.hostconfig.md#supportsinteractivity)

### Accessors

* [fontFamily](_host_config_.hostconfig.md#fontfamily)
* [fontSizes](_host_config_.hostconfig.md#fontsizes)
* [fontWeights](_host_config_.hostconfig.md#fontweights)

### Methods

* [getEffectiveSpacing](_host_config_.hostconfig.md#geteffectivespacing)
* [getFontTypeDefinition](_host_config_.hostconfig.md#getfonttypedefinition)
* [makeCssClassName](_host_config_.hostconfig.md#makecssclassname)
* [makeCssClassNames](_host_config_.hostconfig.md#makecssclassnames)
* [paddingDefinitionToSpacingDefinition](_host_config_.hostconfig.md#paddingdefinitiontospacingdefinition)

### Object literals

* [imageSizes](_host_config_.hostconfig.md#imagesizes)
* [separator](_host_config_.hostconfig.md#separator)
* [spacing](_host_config_.hostconfig.md#spacing)

## Constructors

###  constructor

\+ **new HostConfig**(`obj?`: any): *[HostConfig](_host_config_.hostconfig.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[HostConfig](_host_config_.hostconfig.md)*

## Properties

###  actions

• **actions**: *[ActionsConfig](_host_config_.actionsconfig.md)* = new ActionsConfig()

___

###  adaptiveCard

• **adaptiveCard**: *[AdaptiveCardConfig](_host_config_.adaptivecardconfig.md)* = new AdaptiveCardConfig()

___

###  alwaysAllowBleed

• **alwaysAllowBleed**: *boolean* = false

___

###  choiceSetInputValueSeparator

• **choiceSetInputValueSeparator**: *string* = ","

___

###  containerStyles

• **containerStyles**: *[ContainerStyleSet](_host_config_.containerstyleset.md)* = new ContainerStyleSet()

___

###  cssClassNamePrefix

• **cssClassNamePrefix**: *string* = null

___

###  factSet

• **factSet**: *[FactSetConfig](_host_config_.factsetconfig.md)* = new FactSetConfig()

___

###  fontTypes

• **fontTypes**: *[FontTypeSet](_host_config_.fonttypeset.md)* = null

___

###  hostCapabilities

• **hostCapabilities**: *[HostCapabilities](_host_config_.hostcapabilities.md)‹›* = new HostCapabilities()

___

###  imageSet

• **imageSet**: *[ImageSetConfig](_host_config_.imagesetconfig.md)* = new ImageSetConfig()

___

### `Optional` lineHeights

• **lineHeights**? : *[ILineHeightDefinitions](../interfaces/_host_config_.ilineheightdefinitions.md)*

___

###  media

• **media**: *[MediaConfig](_host_config_.mediaconfig.md)* = new MediaConfig()

___

###  supportsInteractivity

• **supportsInteractivity**: *boolean* = true

## Accessors

###  fontFamily

• **get fontFamily**(): *string*

**Returns:** *string*

• **set fontFamily**(`value`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  fontSizes

• **get fontSizes**(): *[IFontSizeDefinitions](../interfaces/_host_config_.ifontsizedefinitions.md)*

**Returns:** *[IFontSizeDefinitions](../interfaces/_host_config_.ifontsizedefinitions.md)*

___

###  fontWeights

• **get fontWeights**(): *[IFontWeightDefinitions](../interfaces/_host_config_.ifontweightdefinitions.md)*

**Returns:** *[IFontWeightDefinitions](../interfaces/_host_config_.ifontweightdefinitions.md)*

## Methods

###  getEffectiveSpacing

▸ **getEffectiveSpacing**(`spacing`: [Spacing](../enums/_enums_.spacing.md)): *number*

**Parameters:**

Name | Type |
------ | ------ |
`spacing` | [Spacing](../enums/_enums_.spacing.md) |

**Returns:** *number*

___

###  getFontTypeDefinition

▸ **getFontTypeDefinition**(`style?`: [FontType](../enums/_enums_.fonttype.md)): *[FontTypeDefinition](_host_config_.fonttypedefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`style?` | [FontType](../enums/_enums_.fonttype.md) |

**Returns:** *[FontTypeDefinition](_host_config_.fonttypedefinition.md)*

___

###  makeCssClassName

▸ **makeCssClassName**(...`classNames`: string[]): *string*

**Parameters:**

Name | Type |
------ | ------ |
`...classNames` | string[] |

**Returns:** *string*

___

###  makeCssClassNames

▸ **makeCssClassNames**(...`classNames`: string[]): *string[]*

**Parameters:**

Name | Type |
------ | ------ |
`...classNames` | string[] |

**Returns:** *string[]*

___

###  paddingDefinitionToSpacingDefinition

▸ **paddingDefinitionToSpacingDefinition**(`paddingDefinition`: [PaddingDefinition](_shared_.paddingdefinition.md)): *[SpacingDefinition](_shared_.spacingdefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`paddingDefinition` | [PaddingDefinition](_shared_.paddingdefinition.md) |

**Returns:** *[SpacingDefinition](_shared_.spacingdefinition.md)*

## Object literals

###  imageSizes

### ▪ **imageSizes**: *object*

###  large

• **large**: *number* = 160

###  medium

• **medium**: *number* = 80

###  small

• **small**: *number* = 40

___

###  separator

### ▪ **separator**: *object*

###  lineColor

• **lineColor**: *string* = "#EEEEEE"

###  lineThickness

• **lineThickness**: *number* = 1

___

###  spacing

### ▪ **spacing**: *object*

###  default

• **default**: *number* = 8

###  extraLarge

• **extraLarge**: *number* = 40

###  large

• **large**: *number* = 30

###  medium

• **medium**: *number* = 20

###  padding

• **padding**: *number* = 15

###  small

• **small**: *number* = 3
