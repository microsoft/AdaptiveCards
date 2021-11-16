[Adaptive Cards Javascript SDK](../README.md) / [host-config](../modules/host_config.md) / HostConfig

# Class: HostConfig

[host-config](../modules/host_config.md).HostConfig

## Table of contents

### Constructors

- [constructor](host_config.hostconfig.md#constructor)

### Properties

- [actions](host_config.hostconfig.md#actions)
- [adaptiveCard](host_config.hostconfig.md#adaptivecard)
- [alwaysAllowBleed](host_config.hostconfig.md#alwaysallowbleed)
- [choiceSetInputValueSeparator](host_config.hostconfig.md#choicesetinputvalueseparator)
- [containerStyles](host_config.hostconfig.md#containerstyles)
- [cssClassNamePrefix](host_config.hostconfig.md#cssclassnameprefix)
- [factSet](host_config.hostconfig.md#factset)
- [fontTypes](host_config.hostconfig.md#fonttypes)
- [hostCapabilities](host_config.hostconfig.md#hostcapabilities)
- [imageSet](host_config.hostconfig.md#imageset)
- [imageSizes](host_config.hostconfig.md#imagesizes)
- [inputs](host_config.hostconfig.md#inputs)
- [lineHeights](host_config.hostconfig.md#lineheights)
- [media](host_config.hostconfig.md#media)
- [separator](host_config.hostconfig.md#separator)
- [spacing](host_config.hostconfig.md#spacing)
- [supportsInteractivity](host_config.hostconfig.md#supportsinteractivity)

### Accessors

- [fontFamily](host_config.hostconfig.md#fontfamily)
- [fontSizes](host_config.hostconfig.md#fontsizes)
- [fontWeights](host_config.hostconfig.md#fontweights)

### Methods

- [getEffectiveSpacing](host_config.hostconfig.md#geteffectivespacing)
- [getFontTypeDefinition](host_config.hostconfig.md#getfonttypedefinition)
- [makeCssClassName](host_config.hostconfig.md#makecssclassname)
- [makeCssClassNames](host_config.hostconfig.md#makecssclassnames)
- [paddingDefinitionToSpacingDefinition](host_config.hostconfig.md#paddingdefinitiontospacingdefinition)

## Constructors

### constructor

\+ **new HostConfig**(`obj?`: _any_): [_HostConfig_](host_config.hostconfig.md)

#### Parameters:

| Name   | Type  |
| :----- | :---- |
| `obj?` | _any_ |

**Returns:** [_HostConfig_](host_config.hostconfig.md)

Defined in: [host-config.ts:591](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L591)

## Properties

### actions

• `Readonly` **actions**: [_ActionsConfig_](host_config.actionsconfig.md)

Defined in: [host-config.ts:584](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L584)

---

### adaptiveCard

• `Readonly` **adaptiveCard**: [_AdaptiveCardConfig_](host_config.adaptivecardconfig.md)

Defined in: [host-config.ts:585](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L585)

---

### alwaysAllowBleed

• **alwaysAllowBleed**: _boolean_= false

Defined in: [host-config.ts:591](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L591)

---

### choiceSetInputValueSeparator

• **choiceSetInputValueSeparator**: _string_= ","

Defined in: [host-config.ts:557](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L557)

---

### containerStyles

• `Readonly` **containerStyles**: [_ContainerStyleSet_](host_config.containerstyleset.md)

Defined in: [host-config.ts:582](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L582)

---

### cssClassNamePrefix

• `Optional` **cssClassNamePrefix**: _undefined_ \| _string_

Defined in: [host-config.ts:590](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L590)

---

### factSet

• `Readonly` **factSet**: [_FactSetConfig_](host_config.factsetconfig.md)

Defined in: [host-config.ts:588](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L588)

---

### fontTypes

• `Optional` **fontTypes**: _undefined_ \| [_FontTypeSet_](host_config.fonttypeset.md)

Defined in: [host-config.ts:560](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L560)

---

### hostCapabilities

• `Readonly` **hostCapabilities**: [_HostCapabilities_](host_capabilities.hostcapabilities.md)

Defined in: [host-config.ts:553](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L553)

---

### imageSet

• `Readonly` **imageSet**: [_ImageSetConfig_](host_config.imagesetconfig.md)

Defined in: [host-config.ts:586](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L586)

---

### imageSizes

• `Readonly` **imageSizes**: _object_

#### Type declaration:

| Name     | Type     |
| :------- | :------- |
| `large`  | _number_ |
| `medium` | _number_ |
| `small`  | _number_ |

Defined in: [host-config.ts:576](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L576)

---

### inputs

• `Readonly` **inputs**: [_InputConfig_](host_config.inputconfig.md)

Defined in: [host-config.ts:583](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L583)

---

### lineHeights

• `Optional` **lineHeights**: _undefined_ \| [_ILineHeightDefinitions_](../interfaces/host_config.ilineheightdefinitions.md)

Defined in: [host-config.ts:559](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L559)

---

### media

• `Readonly` **media**: [_MediaConfig_](host_config.mediaconfig.md)

Defined in: [host-config.ts:587](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L587)

---

### separator

• `Readonly` **separator**: _object_

#### Type declaration:

| Name            | Type     |
| :-------------- | :------- |
| `lineColor`     | _string_ |
| `lineThickness` | _number_ |

Defined in: [host-config.ts:571](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L571)

---

### spacing

• `Readonly` **spacing**: _object_

#### Type declaration:

| Name         | Type     |
| :----------- | :------- |
| `default`    | _number_ |
| `extraLarge` | _number_ |
| `large`      | _number_ |
| `medium`     | _number_ |
| `padding`    | _number_ |
| `small`      | _number_ |

Defined in: [host-config.ts:562](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L562)

---

### supportsInteractivity

• **supportsInteractivity**: _boolean_= true

Defined in: [host-config.ts:558](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L558)

## Accessors

### fontFamily

• get **fontFamily**(): _undefined_ \| _string_

**Returns:** _undefined_ \| _string_

Defined in: [host-config.ts:700](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L700)

• set **fontFamily**(`value`: _undefined_ \| _string_): _void_

#### Parameters:

| Name    | Type                    |
| :------ | :---------------------- |
| `value` | _undefined_ \| _string_ |

**Returns:** _void_

Defined in: [host-config.ts:704](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L704)

---

### fontSizes

• get **fontSizes**(): [_IFontSizeDefinitions_](../interfaces/host_config.ifontsizedefinitions.md)

**Returns:** [_IFontSizeDefinitions_](../interfaces/host_config.ifontsizedefinitions.md)

Defined in: [host-config.ts:708](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L708)

---

### fontWeights

• get **fontWeights**(): [_IFontWeightDefinitions_](../interfaces/host_config.ifontweightdefinitions.md)

**Returns:** [_IFontWeightDefinitions_](../interfaces/host_config.ifontweightdefinitions.md)

Defined in: [host-config.ts:712](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L712)

## Methods

### getEffectiveSpacing

▸ **getEffectiveSpacing**(`spacing`: [_Spacing_](../enums/enums.spacing.md)): _number_

#### Parameters:

| Name      | Type                                   |
| :-------- | :------------------------------------- |
| `spacing` | [_Spacing_](../enums/enums.spacing.md) |

**Returns:** _number_

Defined in: [host-config.ts:657](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L657)

---

### getFontTypeDefinition

▸ **getFontTypeDefinition**(`style?`: [_Default_](../enums/enums.fonttype.md#default) \| [_Monospace_](../enums/enums.fonttype.md#monospace)): [_FontTypeDefinition_](host_config.fonttypedefinition.md)

#### Parameters:

| Name     | Type                                                                                                   |
| :------- | :----------------------------------------------------------------------------------------------------- |
| `style?` | [_Default_](../enums/enums.fonttype.md#default) \| [_Monospace_](../enums/enums.fonttype.md#monospace) |

**Returns:** [_FontTypeDefinition_](host_config.fonttypedefinition.md)

Defined in: [host-config.ts:648](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L648)

---

### makeCssClassName

▸ **makeCssClassName**(...`classNames`: _string_[]): _string_

#### Parameters:

| Name            | Type       |
| :-------------- | :--------- |
| `...classNames` | _string_[] |

**Returns:** _string_

Defined in: [host-config.ts:694](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L694)

---

### makeCssClassNames

▸ **makeCssClassNames**(...`classNames`: _string_[]): _string_[]

#### Parameters:

| Name            | Type       |
| :-------------- | :--------- |
| `...classNames` | _string_[] |

**Returns:** _string_[]

Defined in: [host-config.ts:684](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L684)

---

### paddingDefinitionToSpacingDefinition

▸ **paddingDefinitionToSpacingDefinition**(`paddingDefinition`: [_PaddingDefinition_](shared.paddingdefinition.md)): [_SpacingDefinition_](shared.spacingdefinition.md)

#### Parameters:

| Name                | Type                                               |
| :------------------ | :------------------------------------------------- |
| `paddingDefinition` | [_PaddingDefinition_](shared.paddingdefinition.md) |

**Returns:** [_SpacingDefinition_](shared.spacingdefinition.md)

Defined in: [host-config.ts:676](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-config.ts#L676)
