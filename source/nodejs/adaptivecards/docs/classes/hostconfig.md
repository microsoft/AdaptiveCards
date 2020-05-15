[Adaptive Cards Javascript SDK](../README.md) › [HostConfig](hostconfig.md)

# Class: HostConfig

## Hierarchy

* **HostConfig**

## Index

### Constructors

* [constructor](hostconfig.md#constructor)

### Properties

* [actions](hostconfig.md#actions)
* [adaptiveCard](hostconfig.md#adaptivecard)
* [alwaysAllowBleed](hostconfig.md#alwaysallowbleed)
* [choiceSetInputValueSeparator](hostconfig.md#choicesetinputvalueseparator)
* [containerStyles](hostconfig.md#containerstyles)
* [cssClassNamePrefix](hostconfig.md#optional-cssclassnameprefix)
* [factSet](hostconfig.md#factset)
* [fontTypes](hostconfig.md#optional-fonttypes)
* [hostCapabilities](hostconfig.md#hostcapabilities)
* [imageSet](hostconfig.md#imageset)
* [lineHeights](hostconfig.md#optional-lineheights)
* [media](hostconfig.md#media)
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

* [imageSizes](hostconfig.md#imagesizes)
* [separator](hostconfig.md#separator)
* [spacing](hostconfig.md#spacing)

## Constructors

###  constructor

\+ **new HostConfig**(`obj?`: any): *[HostConfig](hostconfig.md)*

*Defined in [host-config.ts:526](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L526)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[HostConfig](hostconfig.md)*

## Properties

###  actions

• **actions**: *[ActionsConfig](actionsconfig.md)* = new ActionsConfig()

*Defined in [host-config.ts:519](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L519)*

___

###  adaptiveCard

• **adaptiveCard**: *[AdaptiveCardConfig](adaptivecardconfig.md)* = new AdaptiveCardConfig()

*Defined in [host-config.ts:520](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L520)*

___

###  alwaysAllowBleed

• **alwaysAllowBleed**: *boolean* = false

*Defined in [host-config.ts:526](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L526)*

___

###  choiceSetInputValueSeparator

• **choiceSetInputValueSeparator**: *string* = ","

*Defined in [host-config.ts:493](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L493)*

___

###  containerStyles

• **containerStyles**: *[ContainerStyleSet](containerstyleset.md)* = new ContainerStyleSet()

*Defined in [host-config.ts:518](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L518)*

___

### `Optional` cssClassNamePrefix

• **cssClassNamePrefix**? : *undefined | string*

*Defined in [host-config.ts:525](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L525)*

___

###  factSet

• **factSet**: *[FactSetConfig](factsetconfig.md)* = new FactSetConfig()

*Defined in [host-config.ts:523](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L523)*

___

### `Optional` fontTypes

• **fontTypes**? : *[FontTypeSet](fonttypeset.md)*

*Defined in [host-config.ts:496](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L496)*

___

###  hostCapabilities

• **hostCapabilities**: *HostCapabilities‹›* = new HostCapabilities()

*Defined in [host-config.ts:489](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L489)*

___

###  imageSet

• **imageSet**: *[ImageSetConfig](imagesetconfig.md)* = new ImageSetConfig()

*Defined in [host-config.ts:521](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L521)*

___

### `Optional` lineHeights

• **lineHeights**? : *[ILineHeightDefinitions](../interfaces/ilineheightdefinitions.md)*

*Defined in [host-config.ts:495](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L495)*

___

###  media

• **media**: *[MediaConfig](mediaconfig.md)* = new MediaConfig()

*Defined in [host-config.ts:522](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L522)*

___

###  supportsInteractivity

• **supportsInteractivity**: *boolean* = true

*Defined in [host-config.ts:494](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L494)*

## Accessors

###  fontFamily

• **get fontFamily**(): *string | undefined*

*Defined in [host-config.ts:634](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L634)*

**Returns:** *string | undefined*

• **set fontFamily**(`value`: string | undefined): *void*

*Defined in [host-config.ts:638](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L638)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string &#124; undefined |

**Returns:** *void*

___

###  fontSizes

• **get fontSizes**(): *[IFontSizeDefinitions](../interfaces/ifontsizedefinitions.md)*

*Defined in [host-config.ts:642](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L642)*

**Returns:** *[IFontSizeDefinitions](../interfaces/ifontsizedefinitions.md)*

___

###  fontWeights

• **get fontWeights**(): *[IFontWeightDefinitions](../interfaces/ifontweightdefinitions.md)*

*Defined in [host-config.ts:646](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L646)*

**Returns:** *[IFontWeightDefinitions](../interfaces/ifontweightdefinitions.md)*

## Methods

###  getEffectiveSpacing

▸ **getEffectiveSpacing**(`spacing`: [Spacing](../enums/spacing.md)): *number*

*Defined in [host-config.ts:591](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L591)*

**Parameters:**

Name | Type |
------ | ------ |
`spacing` | [Spacing](../enums/spacing.md) |

**Returns:** *number*

___

###  getFontTypeDefinition

▸ **getFontTypeDefinition**(`style?`: Enums.FontType): *[FontTypeDefinition](fonttypedefinition.md)*

*Defined in [host-config.ts:582](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L582)*

**Parameters:**

Name | Type |
------ | ------ |
`style?` | Enums.FontType |

**Returns:** *[FontTypeDefinition](fonttypedefinition.md)*

___

###  makeCssClassName

▸ **makeCssClassName**(...`classNames`: string[]): *string*

*Defined in [host-config.ts:628](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L628)*

**Parameters:**

Name | Type |
------ | ------ |
`...classNames` | string[] |

**Returns:** *string*

___

###  makeCssClassNames

▸ **makeCssClassNames**(...`classNames`: string[]): *string[]*

*Defined in [host-config.ts:618](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L618)*

**Parameters:**

Name | Type |
------ | ------ |
`...classNames` | string[] |

**Returns:** *string[]*

___

###  paddingDefinitionToSpacingDefinition

▸ **paddingDefinitionToSpacingDefinition**(`paddingDefinition`: [PaddingDefinition](paddingdefinition.md)): *[SpacingDefinition](spacingdefinition.md)*

*Defined in [host-config.ts:610](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L610)*

**Parameters:**

Name | Type |
------ | ------ |
`paddingDefinition` | [PaddingDefinition](paddingdefinition.md) |

**Returns:** *[SpacingDefinition](spacingdefinition.md)*

## Object literals

###  imageSizes

### ▪ **imageSizes**: *object*

*Defined in [host-config.ts:512](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L512)*

###  large

• **large**: *number* = 160

*Defined in [host-config.ts:515](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L515)*

###  medium

• **medium**: *number* = 80

*Defined in [host-config.ts:514](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L514)*

###  small

• **small**: *number* = 40

*Defined in [host-config.ts:513](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L513)*

___

###  separator

### ▪ **separator**: *object*

*Defined in [host-config.ts:507](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L507)*

###  lineColor

• **lineColor**: *string* = "#EEEEEE"

*Defined in [host-config.ts:509](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L509)*

###  lineThickness

• **lineThickness**: *number* = 1

*Defined in [host-config.ts:508](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L508)*

___

###  spacing

### ▪ **spacing**: *object*

*Defined in [host-config.ts:498](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L498)*

###  default

• **default**: *number* = 8

*Defined in [host-config.ts:500](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L500)*

###  extraLarge

• **extraLarge**: *number* = 40

*Defined in [host-config.ts:503](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L503)*

###  large

• **large**: *number* = 30

*Defined in [host-config.ts:502](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L502)*

###  medium

• **medium**: *number* = 20

*Defined in [host-config.ts:501](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L501)*

###  padding

• **padding**: *number* = 15

*Defined in [host-config.ts:504](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L504)*

###  small

• **small**: *number* = 3

*Defined in [host-config.ts:499](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/host-config.ts#L499)*
