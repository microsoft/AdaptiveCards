# What is HostConfig?
Host config is an shared configuration object which defines parameters controlling how an Adaptive Card Renderer generates UI.  

This allows properties which are platform agnostic to be shared among renderers on different platoforms and devices. It also allows tooling to be created which gives you an idea of the look and feel that card would have for a given environment.

> NOTE: You  can further customize the look and feel of the card using the styling mechanisms appropriate to the ui framework used
to render the card.  For example: use CSS in HTML to change the look and behavior of action elements.

# HostConfig

| Property | Type | default | Description |
|---|---|---|---|
| **adaptiveCard**| [AdaptiveCardConfig](#adaptivecardconfig) | - | Defines adaptive card config |
| **actionSet** | [ActionSetConfig](#actionsetconfig) | - | Defines config for Actionset element|
| **colors** | [ColorsConfig](#colorsconfig) | - | Defines color pallette|
| **column** | [ColumnConfig](#columnconfig) | - | Defines config for Column element |
| **columnSet** | [ColumnSetConfig](#columnsetconfig) | - | Defines config for ColumnSet element |
| **container** | [ContainerConfig](#containerconfig) | - | Defines config for Container element |
| **actions** | [ActionConfig](#actionconfig) | - | Defines config for Actions |
| **image**| [ImageConfig](#imageconfig) | - | Defines Image  config |
| **imageSet** | [ImageSetConfig](#imagesetconfig) | - | Defines config for ImageSet element|
| **imageSizes** | [ImageSizesConfig](#imagesizesconfig) | - | Defines the sizes for images |
| **inputs** | [InputConfig](#inputconfig) | - | Defines config for Input elements |
| **factSet** | [FactSetConfig](#factsetconfig) | - | Defines config for FactSet element|
| **fontFamily**| string | "Calibri" | Defines comma delimited font-family to be used for card |
| **fontSizes** | [FontSizesConfig](#fontsizesconfig) |  - | Defines font sizes to use for text. |
| **supportsInteractivity** | bool | true| Does the host want to support interactivity like actions and inputs |
| **strongSeparation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between vertical elements| 
| **textBlock**| [TextBlockConfig](#textblockconfig) | - | Defines TextBlock config |

## AdaptiveCardConfig
Defines Card config

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor**| string | #FFFFFFFF | Defines default color for the background in RGBa format #AARRGGBB|
| **padding**| [SpacingDefinition](#spacingdefinition) | 8,8,8,8 | Defines padding between card content and edge of card|


## FontSizesConfig
Font sizes you desire

| Property | Type | default | Description |
|---|---|---|---|
| **small** | number | 10 | small font size|
| **normal** | number | 12 | normal font size|
| **medium** | number | 14 | medium font size|
| **large** | number | 17 | large font size|
| **extraLarge** | number | 20 | extraLarge font size|

## ColorsConfig
ColorConfig defining the pallette for the card

| Property | Type | default | Description |
|---|---|---|---|
| **default** | [ColorConfig](#colorconfig) | #FF000000 | default color to use |
| **accent** | [ColorConfig](#colorconfig) | #FF0000FF | accent color to use |
| **dark** | [ColorConfig](#colorconfig) | #FF101010 | dark color to use |
| **light**  | [ColorConfig](#colorconfig) | #FFFFFFFF | light color to use |
| **good**   | [ColorConfig](#colorconfig) | #FF008000 | good color to use |
| **warning**  | [ColorConfig](#colorconfig) | #FFFFD700 | warning color to use |
| **attention**  | [ColorConfig](#colorconfig) | #FF8B0000 | attention color to use |

## ColorConfig
Defines color and subtle version of color

| Property | Type | default | Description |
|---|---|---|---|
| **normal** | string | - | normal color to use (in #AARRGGBB)|
| **subtle** | string | - | subtle color to use (in #AARRGGBB)|

## ImageSizesConfig
Defines imageSize for the card

| Property | Type | default | Description |
|---|---|---|---|
| **small** | number | 60 | small image size|
| **medium** | number | 120 | medium image size|
| **large**  | number | 120 | large image size|

## ImageConfig
Default Image config

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesize)| Auto | The default image size to use for an image| 
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## ImageSetConfig
Default Image size for the imageset

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesizeconfig)| Medium | The default image size to use for an imageSet| 
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## FactSetConfig
Defines how factSets should look

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 
| **spacing** | number | 20 | spacing between fact and value |
| **title** | [TextConfig](#textconfig) | {  Weight = TextWeight.Bolder }| sets how text for fact title should look|
| **value** | [TextConfig](#textconfig) | { } | sets how text for fact value should look|

## ContainerConfig
Defines container config

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 
| **normal**| [ContainerStyleConfig](#containerstyleconfig)| - | Defines the normal style for a container |
| **emphasis**| [ContainerStyleConfig](#containerstyleconfig)| - | Defines an emphasized style for a container |

### ContainerStyleConfig
Defines a style for a container

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor** | string | transparent | Defines background color for the container | 
| **borderColor** | string | transparent | Defines a border color for the container | 
| **borderThickness** | [SpacingDefinition](#spacingdefinition) | {0,0,0,0} | Defines a border thickness for the container | 
| **padding** | [SpacingDefinition](#spacingdefinition) | {0,0,0,0} | Defines background color for the container | 

## ColumnConfig
Defines column config

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) |- | Defines spacing and color for separations between columns | 

## ColumnSetConfig
Defines ColumnSet config

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## TextBlockConfig
Defines config for TextBlock elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 


## InputConfig
Defines config for input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 


## ActionSetConfig
Defines ActionSet config

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## TextConfig
Defines text settings for things like FactSet Title.

| Property | Type | default | Description |
|---|---|---|---|
| **size** | TextSize | normal | desired size (small, normal, medium, large, extraLarge)  |
| **weight** | TextWeight | normal | desired weight (lighter, normal, bolder)  |
| **color** | TextColor | default | desired color from pallete |
| **wrap** | bool | false | can text be wrapped |
| **isSubtle** | bool | false | should use subtle version of color |

## ActionConfig
Defines config for how actions should be rendered

| Property | Type | default | Description |
|---|---|---|---|
| **showCard** | [ShowCardConfig](#showcardconfig)| - | Defines config for ShowCardAction|
| **actionsOrientation** | Horizontal or Vertical | Horizontal | Defines actions as horizontal vs vertical |
| **actionAlignment** | Left or center or right | center | should actions be aligned left, centered or right |
| **backgroundColor** | string | #FF5098FF | Defines background for card when the showCard is shown inline|
| **borderColor**  | string | #FF000000 | Defines color of border for action button |
| **borderThickness**  | number | 1 | Defnes thickness of border around the action|
| **maxActions** | number | 5 | max number of actions that the app wants to support|
| **textColor**  | string | #FFFFFFFF | Defines color of title for action button |
| **fontWeight**  | number  | #FFFFFFFF | Defines color of title for action button |
| **fontSize**  | number  | 12 | Defines size of the text on the action btton |
| **spacing** | number | 8 | spacing between buttons in an actionSet|
| **padding** | [SpacingDefinition](#spacingdefinition)| 4,4,4,4| The default padding around the title of the button |

## ShowCardConfig
The config for showing a card action.

| Property | Type | default | Description |
|---|---|---|---|
| **actionMode** | inline or popup| Inline| Defines whether showCard should popup or be displayed inline|
| **backgroundColor** | string | #FFF8F8F8"| Defines inline slide-out background color |  
| **autoPadding** | bool | true| when inline will automatically expand padding to card boundary (it looks nice)|

## SpacingDefinition
Defines left,top, right and bottom number values

| Property | Type | default | Description |
|---|---|---|---|
| **left**| number | 0 | define left value |
| **right**| number | 0 | define right value |
| **top**| number | 0 | define top value |
| **bottom**| number | 0 | define bottom value |

### SeparationConfig
Properties which define spacing, line thickness and color for separating elements

| Property | Type | default | Description |
|---|---|---|---|
| **spacing**| number | - | spacing between elements|
| **lineThickness** |  number | - | thickness of visible line if desired|
| **lineColor** | string | - | color defined as RGBa value #AARRGGBB   |


# Sample theme
Go to [HostConfig.json](../samples/Themes/HostConfig.json) to see sample theme.
