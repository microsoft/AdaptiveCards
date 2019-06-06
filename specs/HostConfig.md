# Host config

## AdaptiveCardConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**allowCustomStyle**|`boolean`| No, default: `true`|Controls whether custom styling is allowed|1.0
|**supportsInteractivity**|`boolean`| No, default: `true`|Control whether interactive `Action`s are allowed to be invoke|1.0
|**imageBaseUrl**|`string`| No|Base URL to be used when loading resources|1.0
|**fontFamily**|`string`| No, default: `"Calibri"`|Font face to use when rendering text|1.0
|**actions**|`object`| No|Options for `Action`s|1.0
|**adaptiveCard**|`object`| No|Toplevel options for `AdaptiveCards`|1.0
|**containerStyles**|`object`| No|Controls styling for default and emphasis containers|1.0
|**imageSizes**|`object`| No|Controls `Image` sizes|1.0
|**imageSet**|`object`| No|Controls how `ImageSet`s are displayed|1.0
|**factSet**|`object`| No|Controls the display of `FactSet`s|1.0
|**fontSizes**|`object`| No|Controls font size metrics for different text styles|1.0
|**fontWeights**|`object`| No|Controls font weight metrics|1.0
|**spacing**|`object`| No|Controls how elements are to be laid out|1.0
|**separator**|`object`| No|Controls how separators are displayed|1.0
|**media**|`object`| No|Controls the display and behavior of `Media` elements|1.1



## ActionsConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**actionsOrientation**|`string`| No, default: `"horizontal"`|Controls how buttons are laid out|1.0
|**actionAlignment**|`string`| No, default: `"stretch"`|Control layout of buttons|1.0
|**buttonSpacing**|`integer`| No, default: `10`|Controls how much spacing to use between buttons|1.0
|**maxActions**|`integer`| No, default: `5`|Controls how many actions are allowed in total|1.0
|**spacing**|`string`| No, default: `"default"`|Controls overall spacing of action element|1.0
|**showCard**|`object`| No|Controls behavior and styling of `Action.ShowCard`|1.0
|**iconPlacement**|`string`| No, default: `"aboveTitle"`|Controls where to place the action icon|1.0
|**iconSize**|`integer`| No, default: `30`|Controls size of action icon|1.0



## ContainerStylesConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**default**|`object`| No|Default container style|1.0
|**emphasis**|`object`| No|Container style to use for emphasis|1.0



## FactSetConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**title**|`object`| No, default: `{"weight":"bolder","size":"default","color":"default","isSubtle":false,"wrap":true,"maxWidth":150}`|Parameters controlling the display of text|1.0
|**value**|`object`| No, default: `{"weight":"default","size":"default","color":"default","isSubtle":false,"wrap":true,"maxWidth":0}`|Parameters controlling the display of text|1.0
|**spacing**|`integer`| No, default: `10`|&nbsp;|1.0



## FontSizesConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**small**|`integer`| No, default: `10`|Small font size|1.0
|**default**|`integer`| No, default: `12`|Default font size|1.0
|**medium**|`integer`| No, default: `14`|Medium font size|1.0
|**large**|`integer`| No, default: `17`|Large font size|1.0
|**extraLarge**|`integer`| No, default: `20`|Extra large font size|1.0



## FontWeightsConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**lighter**|`integer`| No, default: `200`|&nbsp;|1.0
|**default**|`integer`| No, default: `400`|&nbsp;|1.0
|**bolder**|`integer`| No, default: `800`|&nbsp;|1.0



## ForegroundColorsConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**default**|`object`| No, default: `{"default":"#FF000000","subtle":"#B2000000"}`|&nbsp;|1.0
|**accent**|`object`| No, default: `{"default":"#FF0000FF","subtle":"#B20000FF"}`|&nbsp;|1.0
|**dark**|`object`| No, default: `{"default":"#FF101010","subtle":"#B2101010"}`|&nbsp;|1.0
|**light**|`object`| No, default: `{"default":"#FFFFFFFF","subtle":"#B2FFFFFF"}`|&nbsp;|1.0
|**good**|`object`| No, default: `{"default":"#FF008000","subtle":"#B2008000"}`|&nbsp;|1.0
|**warning**|`object`| No, default: `{"default":"#FFFFD700","subtle":"#B2FFD700"}`|&nbsp;|1.0
|**attention**|`object`| No, default: `{"default":"#FF8B0000","subtle":"#B28B0000"}`|&nbsp;|1.0



## ImageSetConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**imageSize**|`string`| No, default: `"auto"`|Controls individual image sizing|1.0
|**maxImageHeight**|`integer`| No, default: `100`|Constrain image height to this value|1.0



## ImageSizesConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**small**|`integer`| No, default: `80`|Small image size value|1.0
|**medium**|`integer`| No, default: `120`|Medium image size value|1.0
|**large**|`integer`| No, default: `180`|Large image size value|1.0



## MediaConfig#### Introduced in version 1.1

|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**defaultPoster**|`string`| No|URI to image to display when play button hasn't been invoked|1.1
|**playButton**|`string`| No|Image to display as play button|1.1
|**allowInlinePlayback**|`boolean`| No, default: `true`|Whether to display media inline or invoke externally|1.1



## SeparatorConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**lineThickness**|`integer`| No, default: `1`|Thickness of separator line|1.0
|**lineColor**|`string,null`| No, default: `#B2000000`|Color to use when drawing separator line|1.0



## ShowCardConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**actionMode**|`string`| No, default: `"inline"`|Controls how the card is displayed|1.0
|**style**|`object`| No, default: `emphasis`|Controls styling of a container|1.0
|**inlineTopMargin**|`integer`| No, default: `16`|Amount of margin to use when displaying the card|1.0



## SpacingsConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**small**|`integer`| No, default: `3`|Small spacing value|1.0
|**default**|`integer`| No, default: `8`|Default spacing value|1.0
|**medium**|`integer`| No, default: `20`|Medium spacing value|1.0
|**large**|`integer`| No, default: `30`|Large spacing value|1.0
|**extraLarge**|`integer`| No, default: `40`|Extra large spacing value|1.0
|**padding**|`integer`| No, default: `20`|Padding value|1.0



## TextBlockConfig|Property|Type|Required|Description|Version|
|--------|----|--------|-----------|-------|
|**size**|`string`| No, default: `"default"`|Font size to use when a card doesn't specify|1.0
|**weight**|`string`| No, default: `"normal"`|Font weight to use when a card doesn't specify|1.0
|**color**|`string`| No, default: `"default"`|Font color to use when a card doesn't specify|1.0
|**isSubtle**|`boolean`| No, default: `false`|Should text be subtle if a card doesn't specify|1.0
|**wrap**|`boolean`| No, default: `true`|Should text wrap if a card doesn't specify|1.0
|**maxWidth**|`integer`| No, default: `0`|Maximum width to use if a card doesn't specify|1.0

