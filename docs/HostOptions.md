# What is HostOptions?
Host options is an shared configuration object which Defines how an Adaptive Card Renderer generates UI.  
The goal is that properties which are platform agnostic can be shared among renderers. Furthermore, you should
get a great looking card without having to define lots of styles.

You  can further customize the look and feel of the card using the styling mechanisms appropriate to the ui framework used
to render the card.

# HostOptions

| Property | Type | default | Description |
|---|---|---|---|
| **adaptiveCard**| [AdaptiveCardOptions](#adaptivecardoptions) | - | Defines adaptive card options |
| **actionSet** | [ActionSetOptions](#actionsetoptions) | - | Defines options for Actionset element|
| **colors** | [ColorOptions](#coloroptions) | - | Defines color pallette|l
| **column** | [ColumnOptions](#columnoptions) | - | Defines options for Column element |
| **columnSet** | [ColumnSetOptions](#columnsetoptions) | - | Defines options for ColumnSet element |
| **container** | [ContainerOptions](#containeroptions) | - | Defines options for Container element |
| **actions** | [ActionOptions](#actionoptions) | - | Defines options for Actions |
| **image**| [ImageOptions](#imageoptions) | - | Defines Image  options |
| **imageSet** | [ImageSetOptions](#imagesetoptions) | - | Defines options for ImageSet element|
| **imageSizes** | [ImageSizeOptions](#imagesizeoptions) | - | Defines the sizes for images |
| **inputs** | [InputOptions](#inputoptions) | - | Defines options for Input elements |
| **factSet** | [FactSetOptions](#factsetoptions) | - | Defines options for FactSet element|
| **fontFamily**| string | "Calibri" | Defines comma delimited font-family to be used for card |
| **fontSizes** | [FontSizeOptions](#fontsizeoptions) |  - | Defines font sizes to use for text. |
| **supportsInteractivity** | bool | true| Does the host want to support interactivity like actions and inputs |
| **strongSeparation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between vertical elements| 
| **textBlock**| [TextBlockOptions](#textblockoptions) | - | Defines TextBlock options |

## AdaptiveCardOptions
Defines Card options

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor**| string | #FFFFFFFF | Defines default color for the background in RGBa format #AARRGGBB|
| **padding**| [SpacingDefinition](#spacingdefinition) | 8,8,8,8 | Defines padding between card content and edge of card|


## SeparationOptions
Properties which control spacing and visual between elements

| Property | Type | default | Description |
|---|---|---|---|
| **default** | [SeparationOption](#separationoption) | {Spacing=10} |default separation |
| **strong** | [SeparationOption](#separationoption) | {Spacing=20, lineThickness=1, lineColor=#FF707070} |strong separation |

## SeparationOption
Properties which define spacing, line thickness and color for separating elements

| Property | Type | default | Description |
|---|---|---|---|
| **spacing**| number | - | spacing between elements|
| **lineThickness** |  number | - | thickness of visible line if desired|
| **lineColor** | string | - | color defined as RGBa value #AARRGGBB   |

## FontSizeOptions
Font sizes you desire

| Property | Type | default | Description |
|---|---|---|---|
| **small** | number | 10 | small font size|
| **normal** | number | 12 | normal font size|
| **medium** | number | 14 | medium font size|
| **large** | number | 17 | large font size|
| **extraLarge** | number | 20 | extraLarge font size|

## ColorOptions
ColorOptions defining the pallette for the card

| Property | Type | default | Description |
|---|---|---|---|
| **default** | [ColorOption](#coloroption) | #FF000000 | default color to use |
| **accent** | [ColorOption](#coloroption) | #FF0000FF | accent color to use |
| **dark** | [ColorOption](#coloroption) | #FF101010 | dark color to use |
| **light**  | [ColorOption](#coloroption) | #FFFFFFFF | light color to use |
| **good**   | [ColorOption](#coloroption) | #FF008000 | good color to use |
| **warning**  | [ColorOption](#coloroption) | #FFFFD700 | warning color to use |
| **attention**  | [ColorOption](#coloroption) | #FF8B0000 | attention color to use |

## ColorOption
Defines color and subtle version of color

| Property | Type | default | Description |
|---|---|---|---|
| **normal** | string | - | normal color to use (in #AARRGGBB)|
| **subtle** | string | - | subtle color to use (in #AARRGGBB)|

## ImageSizeOptions
Defines imageSize for the card

| Property | Type | default | Description |
|---|---|---|---|
| **small** | number | 60 | small image size|
| **medium** | number | 120 | medium image size|
| **large**  | number | 120 | large image size|

## ImageOptions
Default Image options

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesize)| Auto | The default image size to use for an image| 
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 

## ImageSetOptions
Default Image size for the imageset

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesizeoptions)| Medium | The default image size to use for an imageSet| 
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 

## FactSetOptions
Defines how factSets should look

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 
| **spacing** | number | 20 | spacing between fact and value |
| **title** | [TextOptions](#textoptions) | {  Weight = TextWeight.Bolder }| sets how text for fact title should look|
| **value** | [TextOptions](#textoptions) | { } | sets how text for fact value should look|

## ContainerOptions
Defines container options

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 
| **normal**| [ContainerStyleOptions](#containerstyleoptions)| - | Defines the normal style for a container |
| **emphasis**| [ContainerStyleOptions](#containerstyleoptions)| - | Defines an emphasized style for a container |

### ContainerStyleOptions
Defines a style for a container

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor** | string | transparent | Defines background color for the container | 
| **padding** | [SpacingDefinition](#spacingdefinition) | transparent | Defines background color for the container | 
| **borderColor** | string | transparent | Defines a border color for the container | 
| **borderThickness** | [SpacingDefinition](#spacingdefinition) | {1,1,1,1} | Defines a border thickness for the container | 

## ColumnOptions
Defines column options

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between columns | 

## ColumnSetOptions
Defines ColumnSet options

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 

## TextBlockOptions
Defines options for TextBlock elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 


## InputOptions
Defines options for input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 


## ActionSetOptions
Defines ActionSet options

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between elements | 

## TextOptions
Defines text settings for things like FactSet Title.

| Property | Type | default | Description |
|---|---|---|---|
| **size** | TextSize | normal | desired size (small, normal, medium, large, extraLarge)  |
| **weight** | TextWeight | normal | desired weight (lighter, normal, bolder)  |
| **color** | TextColor | default | desired color from pallete |
| **wrap** | bool | false | can text be wrapped |
| **isSubtle** | bool | false | should use subtle version of color |

## ActionOptions
Defines options for how actions should be rendered

| Property | Type | default | Description |
|---|---|---|---|
| **showCard** | [ShowCardOptions](#showcardoptions)| - | Defines options for ShowCardAction|
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

## ShowCardOptions
The options for showing a card action.

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


# Sample theme
Go to [HostConfig.json](../samples/Themes/HostConfig.json) to see sample theme.
