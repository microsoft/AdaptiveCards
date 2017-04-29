# What is HostOptions?
Host options is an shared configuration object which defines how an Adaptive Card Renderer generates UI.  
The goal is that properties which are platform agnostic can be shared among renderers. Furthermore, you should
get a great looking card without having to define lots of styles.

You  can further customize the look and feel of the card using ui framework level stylesheets.

# HostOptions

| Property | Type | default | Description |
|---|---|---|---|
| **fontFamily**| string | "Calibri" | defines comma delimited font-family to be used for card |
| **fontSizes** | [FontSizeOptions](#fontsizeoptions) |  - | The font sizes to use for text. |
| **colors** | [ColorOptions](#coloroptions) | - | defines color pallette|
| **imageSizes** | [ImageSizeOptions](#imagesizeoptions) | - | Defines the sizes for images |
| **supportsInteractivity** | bool | true| Does the host want to support interactivity like actions and inputs |
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between vertical elements| 
| **adaptiveCard**| [AdaptiveCardOptions](#adaptivecardoptions) | - | Defines adaptive card options |
| **imageSet** | [ImageSetOptions](#imagesetoptions) | - | defines options for ImageSet element|
| **factSet** | [FactSetOptions](#factsetoptions) | - | defines options for FactSet element|
| **column** | [ColumnOptions](#columntoptions) | - | defines optionns for column element |
| **actions** | [ActionOptions](#actionoptions) | - | Defines options for Actions |


## AdaptiveCardOptions
Defines Card options

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor**| string | #FFFFFFFF | defines default color for the background in RGBa format #AARRGGBB|
| **adding**| [BoundaryOptions](#boundaryoptions) | 8,8,8,8 | defines padding between card content and edge of card|


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

## ImageSetOptions
Default Image size for the imageset

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesizeoptions)| Medium | The default image size to use for an imageSet| 

## FactSetOptions
Defines how factSets should look

| Property | Type | default | Description |
|---|---|---|---|
| **title** | [TextOptions](#textoptions) | {  Weight = TextWeight.Bolder }| sets how text for fact title should look|
| **value** | [TextOptions](#textoptions) | { } | sets how text for fact title should look|
| **spacing** | number | 20 | spacing between fact and value |

## ColumnOptions
Defines column options

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between colunns | 

## TextOptions
Defines text settings for things like FactSet Title.


| Property | Type | default | Description |
|---|---|---|---|
| **size** | TextSize | normal | desired size (small, normal, medium, large, extraLarge)  |
| **weight** | TextWeight | normal | desired weight (lighter, normal, bolder)  |
| **color** | TextColor | default | desired color from pallete |
| **maxLength** | number | default | desired color from pallete |
| **isSubtle** | bool | false | should use subtle version of color |

## ActionOptions
Defines options for how actions should be rendered

| Property | Type | default | Description |
|---|---|---|---|
| **showCard** | [ShowCardOptions](#showcardoptions)| - | defines options for ShowCardAction|
| **actionsOrientation** | Horizontal or Vertical | Horizontal | defines actions as horizontal vs vertical |
| **actionAlignment** | Left or center or right | center | should actions be aligned left, centered or right |
| **backgroundColor** | string | #FF5098FF | defines background for card when the showCard is shown inline|
| **borderColor**  | string | #FF000000 | defines color of border for action button |
| **borderThickness**  | number | 1 | Defnes thickness of border around the action|
| **maxActions** | number | 5 | max number of actions that the app wants to support|
| **textColor**  | string | #FFFFFFFF | defines color of title for action button |
| **fontWeight**  | number  | #FFFFFFFF | defines color of title for action button |
| **fontSize**  | number  | 12 | defines size of the text on the action btton |
| **spacing** | number | 8 | spacing between buttons in an actionSet|
| **padding** | [BoundaryOptions](#boundaryoptions)| 4,4,4,4| The default padding around the title of the button |

## ShowCardOptions
The options for showing a card action.

| Property | Type | default | Description |
|---|---|---|---|
| **actionMode** | inline or popup| Inline| defines whether showCard should popup or be displayed inline|
| **backgroundColor** | string | #FFF8F8F8"| defines inline slide-out background color |  
| **autoPadding** | bool | true| when inline will automatically expand padding to card boundary (it looks nice)|


## BoundaryOptions
Defines left,top, right and bottom number values

| Property | Type | default | Description |
|---|---|---|---|
| **left**| number | 0 | define left value |
| **right**| number | 0 | define right value |
| **top**| number | 0 | define top value |
| **bottom**| number | 0 | define bottom value |


# Sample theme
Go to [HostConfig.json](../samples/Themes/HostConfig.json) to see sample theme.
