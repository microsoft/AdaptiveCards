# What is HostOptions?
Host options is an shared configuration object which defines how an Adaptive Card Renderer generates UI.  
The goal is that properties which are platform agnostic can be shared among renderers. Furthermore, you should
get a great looking card without having to define lots of styles.

You  can further customize the look and feel of the card using ui framework level stylesheets.

# HostOptions

| Property | Type | default | Description |
|---|---|---|---|
| **fontFamily**| string | "Calibri" | defines comma delimited font-family to be used for card |
| **fontSize** | [FontSizeOptions](#fontsizeoptions) |  - | The font sizes to use for text. |
| **colors** | [ColorOptions](#coloroptions) | - | defines color pallette|
| **imageSize** | [ImageSizeOptions](#imagesizeoptions) | - | Defines the sizes for images |
| **supportsInteractivity** | bool | true| Does the host want to support interactivity like actions and inputs |
| **supportedActionTypes** | string[] | All | What action types does the app want to support
| **maxActions** | int | 5 | max number of actions that the app wants to support|
| **horizontalSeparation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between vertical elements| 
| **verticalSeparation** | [SeparationOptions](#separationoptions) | - | Defines spacing and color for separations between horizontal elements| 
| **adaptiveCard**| [AdaptiveCardOptions](#adaptivecardoptions) | - | Defines adaptive card options |
| **imageSet** | [ImageSetOptions](#imagesetoptions) | - | defines options for ImageSet element|
| **factSet** | [FactSetOptions](#factsetoptions) | - | defines options for FactSet element|
| **actions** | [ActionOptions](#actionoptions) | - | Defines options for Actions |


## AdaptiveCardOptions
Defines Card options

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor**| string | #FFFFFFFF | defines default color for the background in RGBa format #AARRGGBB|
| **Padding**| [BoundaryOptions](#boundaryoptions) | 8,8,8,8 | defines padding between card content and edge of card|


## SeparationOptions
Properties which control spacing and visual between elements

| Property | Type | default | Description |
|---|---|---|---|
| default| [SeparationOption](#separationoption) | {Spacing=10} |default separation |
| strong | [SeparationOption](#separationoption) | {Spacing=20, lineThickness=1, lineColor=#FF707070} |strong separation |

## SeparationOption
Properties which define spacing, line thickness and color for separating elements

| Property | Type | default | Description |
|---|---|---|---|
| spacing| int | - | spacing between elements|
| lineThickness|  int | - | thickness of visible line if desired|
| lineColor | string | - | color defined as RGBa value #AARRGGBB   |

## FontSizeOptions
Font sizes you desire

| Property | Type | default | Description |
|---|---|---|---|
| small | int | 10 | small font size|
| normal | int | 12 | normal font size|
| medium | int | 14 | medium font size|
| large | int | 17 | large font size|
| extraLarge | int | 20 | extraLarge font size|

## ColorOptions
ColorOptions defining the pallette for the card

| Property | Type | default | Description |
|---|---|---|---|
| default | [ColorOption](#coloroption) | #FF000000 | default color to use |
| accent | [ColorOption](#coloroption) | #FF0000FF | accent color to use |
| dark | [ColorOption](#coloroption) | #FF101010 | dark color to use |
| light  | [ColorOption](#coloroption) | #FFFFFFFF | light color to use |
| good   | [ColorOption](#coloroption) | #FF008000 | good color to use |
| warning  | [ColorOption](#coloroption) | #FFFFD700 | warning color to use |
| attention  | [ColorOption](#coloroption) | #FF8B0000 | attention color to use |

## ColorOption
Defines color and subtle version of color

| Property | Type | default | Description |
|---|---|---|---|
| normal | string | - | normal color to use (in #AARRGGBB)|
| subtle | string | - | subtle color to use (in #AARRGGBB)|

## ImageSizeOptions
Defines imageSize for the card

| Property | Type | default | Description |
|---|---|---|---|
| small | int | 60 | small image size|
| medium | int | 120 | medium image size|
| large  | int | 120 | large image size|

## ImageSetOptions
Default Image size for the imageset

| Property | Type | default | Description |
|---|---|---|---|
| imageSize | [ImageSize](#imagesize)| Medium | The default image size to use for an imageSet| 

## FactSetOptions
Defines how factSets should look

| Property | Type | default | Description |
|---|---|---|---|
| title | [TextOptions](#textoptions) | {  Weight = TextWeight.Bolder }| sets how text for fact title should look|
| value | [TextOptions](#textoptions) | { } | sets how text for fact title should look|
| spacing | int | 20 | spacing between fact and value |

## TextOptions
Defines text settings for things like FactSet Title.


| Property | Type | default | Description |
|---|---|---|---|
| size | TextSize | normal | desired size (small, normal, medium, large, extraLarge)  |
| weight | TextWeight | normal | desired weight (lighter, normal, bolder)  |
| color | TextColor | default | desired color from pallete |
| isSubtle | bool | false | should use subtle version of color |

## ActionOptions
Defines options for how actions should be rendered

| Property | Type | default | Description |
|---|---|---|---|
| ShowCard | [ShowCardOptions](#showcardoptions)| - | defines options for ShowCardAction|
| ActionsOrientation | Horizontal or Vertical | Horizontal | defines actions as horizontal vs vertical |
| ActionAlignment | Left or center or right | center | should actions be aligned left, centered or right |
| BackgroundColor | string | #FF5098FF | defines background for card when the showCard is shown inline|
| BorderColor  | string | #FF000000 | defines color of border for action button |
| BorderThickness  | int | 1 | Defnes thickness of border around the action|
| TextColor  | string | #FFFFFFFF | defines color of title for action button |
| FontWeight  | int  | #FFFFFFFF | defines color of title for action button |
| FontSize  | int  | 12 | defines size of the text on the action btton |
| Spacing | int | 8 | spacing between buttons in an actionSet|
| Padding | [BoundaryOptions](#boundaryoptions)| 4,4,4,4| The default padding around the title of the button |

## ShowCardActions
The options for showing a card action.

| Property | Type | default | Description |
|---|---|---|---|
| actionMode | inline or popup| Inline| defines whether showCard should popup or be displayed inline|
| backgroundColor | string | #FFF8F8F8"| defines inline slide-out background color |  
| autoPadding | bool | true| when inline will automatically expand padding to card boundary (it looks nice)|


## BoundaryOptions
Defines left,top, right and bottom int values

| Property | Type | default | Description |
|---|---|---|---|
| **left**| int | 0 | define left value |
| **right**| int | 0 | define right value |
| **top**| int | 0 | define top value |
| **bottom**| int | 0 | define bottom value |


# Sample theme

Here is a sample theme as json file

```javascript
{
  "fontFamily": "Calibri",
  "fontSize": {
    "small": 10,
    "normal": 12,
    "medium": 14,
    "large": 17,
    "extraLarge": 20
  },
  "supportsInteractivity": true,
  "supportedActionTypes": [
    "Action.OpenUrl",
    "Action.Submit",
    "Action.Http",
    "Action.ShowCard"
  ],
  "imageSize": {
    "small": 60,
    "medium": 120,
    "large": 180
  },
  "maxActions": 5,
  "verticalSeparation": {
    "default": {
      "spacing": 10,
      "lineThickness": 0,
      "lineColor": null
    },
    "strong": {
      "spacing": 20,
      "lineThickness": 1,
      "lineColor": "#FF707070"
    }
  },
  "horizontalSeparation": {
    "default": {
      "spacing": 10,
      "lineThickness": 0,
      "lineColor": null
    },
    "strong": {
      "spacing": 20,
      "lineThickness": 1,
      "lineColor": "#FF707070"
    }
  },
  "adaptiveCard": {
    "padding": {
      "left": 8,
      "top": 8,
      "right": 8,
      "bottom": 8
    },
    "backgroundColor": "#FFFFFF"
  },
  "colors": {
    "default": {
      "normal": "#FF000000",
      "subtle": "#b2000000"
    },
    "accent": {
      "normal": "#FF0000FF",
      "subtle": "#b20000FF"
    },
    "dark": {
      "normal": "#FF101010",
      "subtle": "#b2101010"
    },
    "light": {
      "normal": "#FFFFFFFF",
      "subtle": "#b2FFFFFF"
    },
    "good": {
      "normal": "#FF008000",
      "subtle": "#b2008000"
    },
    "warning": {
      "normal": "#FFFFD700",
      "subtle": "#b2FFD700"
    },
    "attention": {
      "normal": "#FF8B0000",
      "subtle": "#b28B0000"
    }
  },
  "imageSet": {
    "ImageSize": "medium"
  },
  "factSet": {
    "Title": {
      "weight": "bolder"
    },
    "Value": {},
    "Spacing": 20
  },
  "actions": {
    "showCard": {
      "actionMode": "inline",
      "backgroundColor": "#FFF8F8F8",
      "autoPadding": true
    },
    "actionsOrientation": "horizontal",
    "actionAlignment": "center",
    "backgroundColor": "#FF5098FF",
    "borderColor": "#FF000000",
    "textColor": "#FFFFFFFF",
    "borderThickness": 1,
    "fontWeight": 400,
    "fontSize": 12,
    "spacing": 8,
    "padding": {
      "left": 4,
      "top": 4,
      "right": 4,
      "bottom": 4
    }
  }
}

```
