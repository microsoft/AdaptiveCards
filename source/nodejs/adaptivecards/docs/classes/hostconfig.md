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
* [cssClassNamePrefix](hostconfig.md#cssclassnameprefix)
* [factSet](hostconfig.md#factset)
* [fontTypes](hostconfig.md#fonttypes)
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

*Defined in [host-config.ts:657](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L657)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[HostConfig](hostconfig.md)*

## Properties

###  actions

• **actions**: *[ActionsConfig](actionsconfig.md)* = new ActionsConfig()

*Defined in [host-config.ts:650](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L650)*

___

###  adaptiveCard

• **adaptiveCard**: *[AdaptiveCardConfig](adaptivecardconfig.md)* = new AdaptiveCardConfig()

*Defined in [host-config.ts:651](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L651)*

___

###  alwaysAllowBleed

• **alwaysAllowBleed**: *boolean* = false

*Defined in [host-config.ts:657](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L657)*

___

###  choiceSetInputValueSeparator

• **choiceSetInputValueSeparator**: *string* = ","

*Defined in [host-config.ts:624](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L624)*

___

###  containerStyles

• **containerStyles**: *[ContainerStyleSet](containerstyleset.md)* = new ContainerStyleSet()

*Defined in [host-config.ts:649](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L649)*

___

###  cssClassNamePrefix

• **cssClassNamePrefix**: *string* = null

*Defined in [host-config.ts:656](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L656)*

___

###  factSet

• **factSet**: *[FactSetConfig](factsetconfig.md)* = new FactSetConfig()

*Defined in [host-config.ts:654](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L654)*

___

###  fontTypes

• **fontTypes**: *[FontTypeSet](fonttypeset.md)* = null

*Defined in [host-config.ts:627](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L627)*

___

###  hostCapabilities

• **hostCapabilities**: *[HostCapabilities](hostcapabilities.md)‹›* = new HostCapabilities()

*Defined in [host-config.ts:620](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L620)*

___

###  imageSet

• **imageSet**: *[ImageSetConfig](imagesetconfig.md)* = new ImageSetConfig()

*Defined in [host-config.ts:652](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L652)*

___

### `Optional` lineHeights

• **lineHeights**? : *[ILineHeightDefinitions](../interfaces/ilineheightdefinitions.md)*

*Defined in [host-config.ts:626](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L626)*

___

###  media

• **media**: *[MediaConfig](mediaconfig.md)* = new MediaConfig()

*Defined in [host-config.ts:653](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L653)*

___

###  supportsInteractivity

• **supportsInteractivity**: *boolean* = true

*Defined in [host-config.ts:625](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L625)*

## Accessors

###  fontFamily

• **get fontFamily**(): *string*

*Defined in [host-config.ts:765](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L765)*

**Returns:** *string*

• **set fontFamily**(`value`: string): *void*

*Defined in [host-config.ts:769](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L769)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | string |

**Returns:** *void*

___

###  fontSizes

• **get fontSizes**(): *[IFontSizeDefinitions](../interfaces/ifontsizedefinitions.md)*

*Defined in [host-config.ts:773](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L773)*

**Returns:** *[IFontSizeDefinitions](../interfaces/ifontsizedefinitions.md)*

___

###  fontWeights

• **get fontWeights**(): *[IFontWeightDefinitions](../interfaces/ifontweightdefinitions.md)*

*Defined in [host-config.ts:777](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L777)*

**Returns:** *[IFontWeightDefinitions](../interfaces/ifontweightdefinitions.md)*

## Methods

###  getEffectiveSpacing

▸ **getEffectiveSpacing**(`spacing`: [Spacing](../enums/spacing.md)): *number*

*Defined in [host-config.ts:722](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L722)*

**Parameters:**

Name | Type |
------ | ------ |
`spacing` | [Spacing](../enums/spacing.md) |

**Returns:** *number*

___

###  getFontTypeDefinition

▸ **getFontTypeDefinition**(`style?`: [FontType](../enums/fonttype.md)): *[FontTypeDefinition](fonttypedefinition.md)*

*Defined in [host-config.ts:713](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L713)*

**Parameters:**

Name | Type |
------ | ------ |
`style?` | [FontType](../enums/fonttype.md) |

**Returns:** *[FontTypeDefinition](fonttypedefinition.md)*

___

###  makeCssClassName

▸ **makeCssClassName**(...`classNames`: string[]): *string*

*Defined in [host-config.ts:759](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L759)*

**Parameters:**

Name | Type |
------ | ------ |
`...classNames` | string[] |

**Returns:** *string*

___

###  makeCssClassNames

▸ **makeCssClassNames**(...`classNames`: string[]): *string[]*

*Defined in [host-config.ts:749](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L749)*

**Parameters:**

Name | Type |
------ | ------ |
`...classNames` | string[] |

**Returns:** *string[]*

___

###  paddingDefinitionToSpacingDefinition

▸ **paddingDefinitionToSpacingDefinition**(`paddingDefinition`: [PaddingDefinition](paddingdefinition.md)): *[SpacingDefinition](spacingdefinition.md)*

*Defined in [host-config.ts:741](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L741)*

**Parameters:**

Name | Type |
------ | ------ |
`paddingDefinition` | [PaddingDefinition](paddingdefinition.md) |

**Returns:** *[SpacingDefinition](spacingdefinition.md)*

## Object literals

###  imageSizes

### ▪ **imageSizes**: *object*

*Defined in [host-config.ts:643](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L643)*

###  large

• **large**: *number* = 160

*Defined in [host-config.ts:646](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L646)*

###  medium

• **medium**: *number* = 80

*Defined in [host-config.ts:645](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L645)*

###  small

• **small**: *number* = 40

*Defined in [host-config.ts:644](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L644)*

___

###  separator

### ▪ **separator**: *object*

*Defined in [host-config.ts:638](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L638)*

###  lineColor

• **lineColor**: *string* = "#EEEEEE"

*Defined in [host-config.ts:640](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L640)*

###  lineThickness

• **lineThickness**: *number* = 1

*Defined in [host-config.ts:639](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L639)*

___

###  spacing

### ▪ **spacing**: *object*

*Defined in [host-config.ts:629](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L629)*

###  default

• **default**: *number* = 8

*Defined in [host-config.ts:631](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L631)*

###  extraLarge

• **extraLarge**: *number* = 40

*Defined in [host-config.ts:634](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L634)*

###  large

• **large**: *number* = 30

*Defined in [host-config.ts:633](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L633)*

###  medium

• **medium**: *number* = 20

*Defined in [host-config.ts:632](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L632)*

###  padding

• **padding**: *number* = 15

*Defined in [host-config.ts:635](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L635)*

###  small

• **small**: *number* = 3

*Defined in [host-config.ts:630](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L630)*
