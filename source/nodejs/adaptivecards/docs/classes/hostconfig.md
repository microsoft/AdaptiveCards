[Adaptive Cards Javascript SDK](../README.md) › [HostConfig](hostconfig.md)

# Class: HostConfig

## Hierarchy

* **HostConfig**

## Index

### Constructors

* [constructor](hostconfig.md#constructor)

### Properties

* [actions](hostconfig.md#readonly-actions)
* [adaptiveCard](hostconfig.md#readonly-adaptivecard)
* [alwaysAllowBleed](hostconfig.md#alwaysallowbleed)
* [choiceSetInputValueSeparator](hostconfig.md#choicesetinputvalueseparator)
* [containerStyles](hostconfig.md#readonly-containerstyles)
* [cssClassNamePrefix](hostconfig.md#optional-cssclassnameprefix)
* [factSet](hostconfig.md#readonly-factset)
* [fontTypes](hostconfig.md#optional-fonttypes)
* [hostCapabilities](hostconfig.md#readonly-hostcapabilities)
* [imageSet](hostconfig.md#readonly-imageset)
* [inputs](hostconfig.md#readonly-inputs)
* [lineHeights](hostconfig.md#optional-lineheights)
* [media](hostconfig.md#readonly-media)
* [supportsInteractivity](hostconfig.md#supportsinteractivity)

### Accessors

* [fontFamily](hostconfig.md#fontfamily)
* [fontSizes](hostconfig.md#fontsizes)
* [fontWeights](hostconfig.md#fontweights)

### Methods

* [getEffectiveSpacing](hostconfig.md#geteffectivespacing)
* [getFontTypeDefinition](hostconfig.md#getfonttypedefinition)
* [makeCssClassName](hostconfig.md#makecssclassname)
* [makeCssClassNames](hostconfig.md#makecssclassnames)
* [paddingDefinitionToSpacingDefinition](hostconfig.md#paddingdefinitiontospacingdefinition)

### Object literals

* [imageSizes](hostconfig.md#readonly-imagesizes)
* [separator](hostconfig.md#readonly-separator)
* [spacing](hostconfig.md#readonly-spacing)

## Constructors

###  constructor

\+ **new HostConfig**(`obj?`: any): *[HostConfig](hostconfig.md)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[HostConfig](hostconfig.md)*

## Properties

### `Readonly` actions

• **actions**: *[ActionsConfig](actionsconfig.md)* = new ActionsConfig()

___

### `Readonly` adaptiveCard

• **adaptiveCard**: *[AdaptiveCardConfig](adaptivecardconfig.md)* = new AdaptiveCardConfig()

___

###  alwaysAllowBleed

• **alwaysAllowBleed**: *boolean* = false

___

###  choiceSetInputValueSeparator

• **choiceSetInputValueSeparator**: *string* = ","

___

### `Readonly` containerStyles

• **containerStyles**: *[ContainerStyleSet](containerstyleset.md)* = new ContainerStyleSet()

___

### `Optional` cssClassNamePrefix

• **cssClassNamePrefix**? : *undefined | string*

___

### `Readonly` factSet

• **factSet**: *[FactSetConfig](factsetconfig.md)* = new FactSetConfig()

___

### `Optional` fontTypes

• **fontTypes**? : *[FontTypeSet](fonttypeset.md)*

___

### `Readonly` hostCapabilities

• **hostCapabilities**: *[HostCapabilities](hostcapabilities.md)‹›* = new HostCapabilities()

___

### `Readonly` imageSet

• **imageSet**: *[ImageSetConfig](imagesetconfig.md)* = new ImageSetConfig()

___

### `Readonly` inputs

• **inputs**: *[InputConfig](inputconfig.md)* = new InputConfig()

___

### `Optional` lineHeights

• **lineHeights**? : *[ILineHeightDefinitions](../interfaces/ilineheightdefinitions.md)*

___

### `Readonly` media

• **media**: *[MediaConfig](mediaconfig.md)* = new MediaConfig()

___

###  supportsInteractivity

• **supportsInteractivity**: *boolean* = true

## Accessors

###  fontFamily

• **get fontFamily**(): *string | undefined*

**Returns:** *string | undefined*

• **set fontFamily**(`value`: string | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  fontSizes

• **get fontSizes**(): *[IFontSizeDefinitions](../interfaces/ifontsizedefinitions.md)*

**Returns:** *[IFontSizeDefinitions](../interfaces/ifontsizedefinitions.md)*

___

###  fontWeights

• **get fontWeights**(): *[IFontWeightDefinitions](../interfaces/ifontweightdefinitions.md)*

**Returns:** *[IFontWeightDefinitions](../interfaces/ifontweightdefinitions.md)*

## Methods

###  getEffectiveSpacing

▸ **getEffectiveSpacing**(`spacing`: [Spacing](../enums/spacing.md)): *number*

**Parameters:**

Name | Type |
------ | ------ |
`spacing` | [Spacing](../enums/spacing.md) |

**Returns:** *number*

___

###  getFontTypeDefinition

▸ **getFontTypeDefinition**(`style?`: Enums.FontType): *[FontTypeDefinition](fonttypedefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`style?` | Enums.FontType |

**Returns:** *[FontTypeDefinition](fonttypedefinition.md)*

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

▸ **paddingDefinitionToSpacingDefinition**(`paddingDefinition`: [PaddingDefinition](paddingdefinition.md)): *[SpacingDefinition](spacingdefinition.md)*

**Parameters:**

Name | Type |
------ | ------ |
`paddingDefinition` | [PaddingDefinition](paddingdefinition.md) |

**Returns:** *[SpacingDefinition](spacingdefinition.md)*

## Object literals

### `Readonly` imageSizes

### ▪ **imageSizes**: *object*

###  large

• **large**: *number* = 160

###  medium

• **medium**: *number* = 80

###  small

• **small**: *number* = 40

___

### `Readonly` separator

### ▪ **separator**: *object*

###  lineColor

• **lineColor**: *string* = "#EEEEEE"

###  lineThickness

• **lineThickness**: *number* = 1

___

### `Readonly` spacing

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
