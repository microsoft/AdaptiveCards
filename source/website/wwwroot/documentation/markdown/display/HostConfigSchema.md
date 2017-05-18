# What is HostConfig?
HostConfig is an shared configuration object which defines parameters controlling how an Adaptive Card Renderer generates UI.  

This allows properties which are platform agnostic to be shared among renderers on different platforms and devices. It also allows tooling to be created which gives you an idea of the look and feel that card would have for a given environment.
 
Examine [HostConfig.json](/samples/themes/hostconfig.json) to see a sample theme.

> ![NOTE] 
> You can customize the look and feel of the card further using the styling mechanisms appropriate to the UI framework 
> used to render the card.  For example, use CSS in HTML to change the look and behavior of action elements.

## HostConfig

| Property | Type | default | Description |
|---|---|---|---|
| **actions** | [ActionsConfig](#actionsconfig) | - | Defines configuration for actions in general|
| **actionAlignment** | [ActionAlignment](#actionalign) |  - |Controls how actions are horizontally positioned within their container | 
| **actionSetConfig** | [ActionSetConfig](#actionSetconfig) |  - |Defines ActionSet configuration  | 
| **actionOrientation** | [ActionOrientation](#actionorient) |  - |Controls how actions are oriented | 
| **adaptiveCard**| [AdaptiveCardConfig](#adaptivecardconfig) | - | Defines adaptive card configuration |
| **choiceSet**| [ChoiceSetConfig](#choicesetconfig) | - | Defines ChoiceSet configuration |
| **colors** | [ColorsConfig](#colorsconfig) | - | Defines color palette|
| **colorConfig** | [ColorConfig](#colorconfig) |  - |Defines color and subtle version of color | 
| **column** | [ColumnConfig](#columnconfig) | - | Defines configuration for Column element |
| **columnSet** | [ColumnSetConfig](#columnsetconfig) | - | Defines configuration for ColumnSet element |
| **container** | [ContainerConfig](#containerconfig) | - | Defines configuration for Container element |
| **containerStyleConfig** | [ContainerStyleConfig](#containerStyleconfig) |  - |Defines a style for a container | 
| **dateInput**| [DateInputConfig](#dateInputConfig) | - | Defines DateInput configuration |
| **image**| [ImageConfig](#imageconfig) | - | Defines Image configuration |
| **imageSet** | [ImageSetConfig](#imagesetconfig) | - | Defines configuration for ImageSet element|
| **imageSizes** | [ImageSizesConfig](#imagesizesconfig) | - | Defines the sizes for images |
| **factSet** | [FactSetConfig](#factsetconfig) | - | Defines configuration for FactSet element|
| **fontFamily**| string | "Calibri" | Defines comma delimited font-family to be used for card |
| **fontSizes** | [FontSizesConfig](#fontsizesconfig) |  - | Defines font sizes to use for text. |
| **numberInput**| [NumberInputConfig](#numberinputconfig) | - | Defines NumberInput configuration |
| **showActionMode** | [ShowActionMode](#showAction) | - | Controls how to show the card for a ShowActionCard  | 
| **showCardActionConfig** | [ShowCardActionConfig](#showCardconfig) |  - |The configuration for showing a card action.|
| **spacingDefinition** | [SpacingDefinition](#spaceDef) |  - |Defines left, top, right and bottom number values | 
| **strongSeparation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between vertical elements| 
| **supportsInteractivity** | bool | true| Does the host want to support interactivity like actions and inputs |
| **textBlock**| [TextBlockConfig](#textblockconfig) | - | Defines TextBlock configuration |
| **TextConfig** | [TextConfig](#textconfig) |  - |Defines text settings for things like FactSet Title. | 
| **textInput**| [TextInputConfig](#textinputconfig) | - | Defines TextInput configuration |
| **timeInput**| [TimeInputConfig](#timeinputconfig) | - | Defines TimeInput configuration |
| **toggleInput**| [ToggleInputConfig](#toggleinputconfig) | - | Defines ToggleInput configuration |


## ActionsConfig
<a name="actionsconfig"></a>Defines config for how actions should be rendered

| Property | Type | default | Description |
|---|---|---|---|
| **actionsOrientation** | [ActionsOrientation](#actionsorientation) | Horizontal | Defines actions as horizontal vs vertical |
| **actionAlignment** | [ActionAlignment](#actionalignment) | center | should actions be aligned left, centered, right or stretch |
| **buttonSpacing** | number | 8 | spacing between buttons in an actionSet|
| **maxActions** | number | 5 | max number of actions that the app wants to support|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines separation between actionSet and previous elements | 
| **showCard** | [ShowCardActionConfig](#showcardactionconfig)| - | Defines configuration for ShowCardAction|

### ActionAlignment
<a name="actionalign"></a>Controls how actions are horizontally positioned within their container

| Value | Meaning |
|---|---|
| **left** | actions should be aligned to the left |
| **center** | actions should be aligned center |
| **right** | actions should be aligned tot the right |
| **stretch** | actions should be be stretched to fit the width |

## ActionSetConfig
<a name="actionSetconfig"></a>Defines ActionSet configuration

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

### ActionOrientation
<a name="actionorient"></a>Controls how actions are oriented

| Value | Meaning |
|---|---|
| **horizontal** |actions should be laid out horizontally|
| **vertically** |actions should be laid out vertically|

## AdaptiveCardConfig
<a name="adaptivecardconfig"></a>Defines Card configuration

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor**| string | #FFFFFFFF | Defines default color for the background in RGBa format #AARRGGBB|
| **padding**| [SpacingDefinition](#spacingdefinition) | 8,8,8,8 | Defines padding between card content and edge of card|

## ChoiceSetConfig
<a name="choicesetconfig"></a>Defines configuration for ChoiceSet input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## ColorsConfig
<a name="colorsconfig"></a>Color configuration defines the palette for the card

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
<a name="colorconfig"></a>Defines color and subtle version of color

| Property | Type | default | Description |
|---|---|---|---|
| **normal** | string | - | normal color to use (in #AARRGGBB)|
| **subtle** | string | - | subtle color to use (in #AARRGGBB)|

## ColumnSetConfig
<a name="columnsetconfig"></a>Defines ColumnSet configuration

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## ColumnConfig
<a name="columnconfig"></a>Defines column configuration

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) |- | Defines spacing and color for separations between columns | 


## ContainerConfig
<a name="containerconfig"></a>Defines container configuration

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 
| **normal**| [ContainerStyleConfig](#containerstyleconfig)| - | Defines the normal style for a container |
| **emphasis**| [ContainerStyleConfig](#containerstyleconfig)| - | Defines an emphasized style for a container |

### ContainerStyleConfig
<a name="containerStyleconfig"></a>Defines a style for a container

| Property | Type | default | Description |
|---|---|---|---|
| **backgroundColor** | string | transparent | Defines background color for the container | 
| **borderColor** | string | transparent | Defines a border color for the container | 
| **borderThickness** | [SpacingDefinition](#spacingdefinition) | {0,0,0,0} | Defines a border thickness for the container | 
| **padding** | [SpacingDefinition](#spacingdefinition) | {0,0,0,0} | Defines background color for the container | 

## DateInputConfig
<a name="dateInputConfig"></a>Defines configuration for Date input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 


## ImageConfig
<a name="imageconfig"></a>Default Image configuration

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesize)| Auto | The default image size to use for an image| 
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## ImageSetConfig
<a name="imagesetconfig"></a>Default Image size for the imageset

| Property | Type | default | Description |
|---|---|---|---|
| **imageSize** | [ImageSize](#imagesize)| Medium | The default image size to use for an imageSet| 
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 


## ImageSizesConfig
<a name="imagesizesconfig"></a>Defines imageSize for the card

| Property | Type | default | Description |
|---|---|---|---|
| **small** | number | 60 | small image size|
| **medium** | number | 120 | medium image size|
| **large**  | number | 120 | large image size|

## FactSetConfig
<a name="factsetconfig"></a>Defines how factSets should look

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 
| **spacing** | number | 20 | spacing between fact and value |
| **title** | [TextConfig](#textconfig) | {  Weight = TextWeight.Bolder }| sets how text for fact title should look|
| **value** | [TextConfig](#textconfig) | { } | sets how text for fact value should look|

## FontSizesConfig
<a name="fontsizesconfig"></a>Defines font sizes 

| Property | Type | default | Description |
|---|---|---|---|
| **small** | number | 10 | small font size|
| **normal** | number | 12 | normal font size|
| **medium** | number | 14 | medium font size|
| **large** | number | 17 | large font size|
| **extraLarge** | number | 20 | extraLarge font size|

## NumberInputConfig
<a name="numberinputconfig"></a>Defines configuration for Number input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## TextBlockConfig
<a name="textblockconfig"></a>Defines configuration for TextBlock elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## TextConfig
<a name="textconfig"></a>Defines text settings for things like FactSet Title.

| Property | Type | default | Description |
|---|---|---|---|
| **size** | TextSize | normal | desired size (small, normal, medium, large, extraLarge)  |
| **weight** | TextWeight | normal | desired weight (lighter, normal, bolder)  |
| **color** | TextColor | default | desired color from palette |
| **wrap** | bool | false | can text be wrapped |
| **isSubtle** | bool | false | should use subtle version of color |

## TextInputConfig
<a name="textinputconfig"></a>Defines configuration for Text input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## TimeInputConfig
<a name="timeinputconfig"></a>Defines configuration for Time input elements

| Property | Type | default | Description |
|---|---|---|---|
| **separation** | [SeparationConfig](#separationconfig) | - | Defines spacing and color for separations between elements | 

## ToggleInputConfig
<a name="toggleinputconfig"></a>Defines configuration for Toggle input elements

| Property | Type | default | Description |
|---|---|---|---|

### SeparationConfig
<a name="SeparationConfig"></a>Properties which define spacing, line thickness and color for separating elements

| Property | Type | default | Description |
|---|---|---|---|
| **spacing**| number | - | spacing between elements|
| **lineThickness** |  number | - | thickness of visible line if desired|
| **lineColor** | string | - | color defined as RGBa value #AARRGGBB   |


## ShowCardActionConfig
<a name="showCardconfig"></a>The configuration for showing a card action.

| Property | Type | default | Description |
|---|---|---|---|
| **actionMode** | [ShowActionMode](#showactionmode) | InlineEdgeToEdge | Defines whether showCard should popup or be displayed inline or inline with background extended to container boundary|
| **backgroundColor** | string | #FFF8F8F8"| Defines inline slide-out background color |  
| **inlineTopMargin** | number | when in inline mode defines the space between action buttons and the inline card |
| **padding** | [SpacingDefinition]](#spacingdefinition) | {16,16,16,16} | The padding for the card when shown inline  |

## SpacingDefinition
<a name="spaceDef"></a>Defines left, top, right and bottom number values

| Property | Type | default | Description |
|---|---|---|---|
| **left**| number | 0 | define left value |
| **right**| number | 0 | define right value |
| **top**| number | 0 | define top value |
| **bottom**| number | 0 | define bottom value |

## ShowActionMode
<a name="showAction"></a>Controls how to show the card for a ShowActionCard 

| Value | Meaning |
|---|---|
| **InlineEdgeToEdge** | Show the card inline, but with background color extending to container boundaries |
| **Inline** | Show the card inline |
| **Popup** | Popup a window to show the card |



