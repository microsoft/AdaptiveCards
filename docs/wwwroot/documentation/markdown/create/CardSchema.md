# Table of Contents

Cards
* [AdaptiveCard](#adaptivecard) - top level card

Input Elements
* [TextBlock](#textblock) - display text
* [Image](#image) - display an image
* [Input.Text](#input-text) - get text input from user
* [Input.Date](#input-date) - get date input from user
* [Input.Time](#input-time) - get time input from user
* [Input.Number](#input-number) - get number input from user
* [Input.Toggle](#input-toggle) - get user to select between two options
* [Input.ChoiceSet](#input-choiceset) - display set of choices to the user 
    * [Choice](#choice) - choice object

Containers
* [Container](#container) - container of items
* [ColumnSet](#columnset) -  container of columns
    * [Column](#column) - container of items with column properties
* [ImageSet](#imageset) - container of Images
* [FactSet](#factset) - container of facts
    * [Fact](#fact) - fact object

Actions
* [Action.Http](#action-http) - defines action which collects input and does raw HTTP call to arbitrary HTTP endpoint
* [Action.OpenUrl](#action-openurl) - defines action which opens a url either in external browser or embedded browser
* [Action.ShowCard](#action-showcard) - defines action which shows a card to the user
* [Action.Submit](#action-submit) - defines action which collects input and sends via client appropriate mechanism (it's up to client)

Enumerations
* [ImageSize](#imagesize) - Controls the horizontal size (width) of element.  
* [HorizontalAlignment](#HorizontalAlignment) - Controls how items are horizontally positioned within their container.
* [SeparationStyle](#SeparationStyle) - Controls how items are rendered relative to the previous element.
* [TextSize](#TextSize) - Controls the size of TextBlock items.
* [TextWeight](#TextWeight) - Controls the weight of TextBlock items.
* [TextColor](#TextColor) - Controls the color of TextBlock items.
* [ImageStyle](#ImageStyle) - Controls the way Image items are displayed.
* [ContainerStyle](#ContainerStyle) - Indicates the style of container desired.
* [TextInputStyle](#TextInputStyle) - Style hint for [Input.text](#input-text).
* [ChoiceSetStyle](#ChoiceSetStyle) - Style hint for [Input.ChoiceSet](#input-choiceset).

# Cards

## AdaptiveCard
<a name="adaptivecard"></a>AdaptiveCard is the top level object, which represents a card.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"AdaptiveCard"** | true |  |
| **body** | [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **actions** |[Action](#action)[]| false | Actions |
| **version** | string| false | version of schema that this card was authored |
| **minVersion** | string|false| if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not supported are safe to ignore|
| **fallbackText** | string|false| if a client is not able to show the card, show fallbackText to the user. This can be in markdown format. |

## Image 
<a name="image"></a>
The Image element allows for the inclusion of images in an Adaptive Card.

| Property | Type | Required |Description |
|---|---|---|---|
| **type**| **"Image"** | true |  |
| **url** | string | true | The URL to the image. |
| **style** | [ImageStyle](#imagestyle) | false | The style in which the image is displayed. |
| **selectAction** | [Action](#action) | false | Action to perform for a selection for this image, (this allows image to act as an action) |
| **size** | [ImageSize](#imagesize) | false | Specifies the suggested size of the image. |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |
| **altText** | string  | false | Alternate text for the image for accessibility. |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | false |Specifies how the element should be aligned horizontally within its container. |

## TextBlock 
<a name="textblock"></a>The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"TextBlock"** | true |  |
| **text** | string | true |The actual text to display |
| **size** | [TextSize](#textsize) | false |The size of the text |
| **weight** | [TextWeight](#textweight) | false |The weight of the text |
| **color** | [TextColor](#textcolor) | false |The color of the text |
| **isSubtle** | boolean |false | Indicates whether the color of the text should be slightly toned down to appear less prominent |
| **wrap** | boolean | false | Indicates whether the text should be allowed to wrap |
| **maxLines** | number | false | When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use. |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | false |Specifies how the element should be aligned horizontally within its container. |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |


## Input Elements
Input elements give you the ability to show input controls to the uer.

### Input Text
<a name="input-text"></a>Input.Text collects text from the user.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.Text"** | true |  |
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or HTTP action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **value** | string | false | The initial value for a field |
| **placeholder** | string | false | initial text descripting the input desired |
| **style**| [TextInputStyle](#textinputstyle) | false | Hint of style of input, if client doesn't support the style it will become simple text input |
| **isMultiline** | bool | false | true to collect multiple lines of text (default is false)|
| **maxLength** | number | false | hint of maximum length characters to collect *(may be ignored by some clients)* |
| **isMultiline** | boolean | false | Do you want to allow multiple lines of input |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

### Input Date
<a name="input-date"></a>Input.Date collects text from the user in form of a date. 

> [!NOTE]
> Not all clients may be able to validate that this value is a valid date.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.Date"**  | true | |
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or HTTP action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **value** | string | false | The initial value for a field |
| **placeholder** | string | false | initial text descripting the input desired |
| **min** | string | false | Minimum date in ISO-8601 format (Not all clients will be able to honor this)|
| **max** | string  | false | Maximum date in ISO-8601 format (Not all clients will be able to honor this)|
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

### Input Time
<a name="input-time"></a>Input.Time collects text from the user in form of a time of day.

> [!NOTE]
> Clients may not be able to validate that this value is a valid time expression.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.Time"** | true |  |
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or HTTP action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **placeholder** | string | false | initial text descripting the input desired |
| **value** | string | false | The initial value for a field |
| **min** | string | false | Minimum time (Not all clients will be able to honor this)|
| **max** | string  | false | Maximum time (Not all clients will be able to honor this)|
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

### Input Number
<a name="input-number"></a>Input.Number collects text from the user with a bias towards a number. 

> [!NOTE]
> Value collected may not be valid depending on the capabilities of the client.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.Number"** | true |  |
| **id** | string | true  | ID for the value. This will be used to identify collected input when SUBMIT is clicked. |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or HTTP action. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **placeholder** | string | false | Initial text describing the input desired |
| **value** | number | false | The initial value for a field |
| **min** | number | false | Minimum number (Not all clients will be able to honor this)|
| **max** | number | false | Maximum number (Not all clients will be able to honor this)|
| **separation** | [SeparationStyle](#separationstyle) | none | Visually separates this element from the previous element. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment |

### Input Toggle
<a name="input-toggle"></a>Input.Toggle collects a selection between two values, with **value** representing the current selected toggle value (either value1 or value2).

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.Toggle"** | true |   |
| **style** | [ChoiceInputStyle](#choiceinputstyle) | false | Style for choice.| 
| **id** | string | true  | Id for the value. This will be used to identify collected input when SUBMIT is clicked. |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or HTTP action. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **title** | string | true | The title for the toggle |
| **valueOn** | string | false | The value to use when toggle is selected (default:true)| 
| **valueOff** | string | false  | The value to use when toggle is not selected (default:false)| 
| **value** | string | false  | The value current value (default:false) | 
| **separation** | [SeparationStyle](#separationstyle) | none | Visually separate this element from previous element. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment |

### Input ChoiceSet
<a name="input-choiceset"></a>*Extends [CardElement](#CardElement)*

Shows an array of choices the to the user.

* If **isMultiSelect** is false, then the result will be the single selected choice value.
* If **isMultiSelect** is true, then the result will be an array of the selected choice values. Non-selected choices will be omitted.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.ChoiceSet"** | true |   |
| **style** | [ChoiceInputStyle](#choiceinputstyle) | false | Style for choice. | 
| **id** | string | true  | ID for the value. This will be used to identify collected input when SUBMIT is clicked. |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or HTTP action. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is simple text or SSML fragment. |
| **style**| [ChoiceSetStyle](#choicesetstyle) | false | Hint of style of input. |
| **isMultiSelect** | boolean | false | Allow multiple choices to be selected (Default=false)|
| **choices** | Choice[] | true | The choice options |
| **separation** | [SeparationStyle](#separationstyle) | none | Visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

#### Choice
<a name="choice"></a>Represents a single choice in a ChoiceSet.

| Property | Type | Required | Description |
|---|---|---|---|
| **title** | string | true  | The title label for a choice|
| **value** | string | true  | The raw value for the choice|
| **isSelected** | bool |  false | Is the choice selected |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |

# Containers

## Container 
<a name="container"></a>A Container is a CardElement which contains a list of CardElements that are logically grouped.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Container"**| true |  |
| **items** |  [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **actions** | [Action](#action)[] | false | Actions associated with this container. |
| **selectAction** | [Action](#action) | false | Action to perform for a tap on this container. This allows the entire container to act as an action. |
| **style** | normal, emphasis | normal | A container can group elements together in a normal or emphasized style. |
| **separation** | [SeparationStyle](#separationstyle) | none | Visually separates this element from the previous element. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |


## ColumnSet 
<a name="columnset"></a>The ColumnSet element adds the ability to have a set of Column objects.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"ColumnSet"**  | true | |
| **columns** | [Column](#column)[] | true | array of columns (each a container of items)  |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

## Column
<a name="column"></a>A Column is a container which contains a list of CardElements that are logically grouped.

| Property | Type | Required |  Description |
|---|---|---|---|
| **type**|  **"Column"** | true |  |
| **size** | string | false | "auto", "stretch", or a number representing relative width of the column in the column Set (Default:Auto)|
| **items** |  [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **selectAction** | [Action](#action) | false | Action to perform for a tap on this container, (this allows entire container to act as an action) |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

## ImageSet 
<a name="imageset"></a>The ImageSet allows for the inclusion of a collection images like a photoSet.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"ImageSet"** | true |  |
| **images**| [Image](#image)[] | true | Array of Image objects |
| **imageSize** | [ImageSize](#imagesize) | false | Specifies the suggested size of the images in the Set. |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

## FactSet 
<a name="factset"></a>The FactSet element makes it simple to display a series of "facts" (e.g. name/value pairs) in a tabular form.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**|  **"FactSet"** | true | |
| **facts** | [Fact](#fact)[] | true| The facts to be displayed. |
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from previous element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |Specifies what should be spoken for this entire element. This is a simple text or SSML fragment. |

### Fact 
<a name="fact"></a>Represents one "fact" in a [FactSet](#factset) element.

| Property | Type | Required | Description |
|---|---|---|---|
| **title** | string | true | The fact's title. |
| **value** | string | true |The fact's value. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element. This is simple text or SSML fragment. |

# Actions
Actions define clickable targets that do something.

## Action Http
<a name="action-http"></a>Action.Http represents the properties needed to perform an HTTP request. All input properties are available for use via data binding.  Properties can be data bound to the `url` and `body` properties, allowing you to send a request to an arbitrary URL.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Action.Http"** | true |  |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **url** | string | true | url to use (can have binding information) |
| **method** | string | true | HTTP method (Example: POST) |
| **headers** | object | false | Object which represents headers Example: { "content-type":"application/json" }  |
| **body** | string | false | content to post (can have binding information) |

## Action OpenUrl
<a name="action-openurl"></a>When Action.OpenUrl is invoked it will show the given url, either by launching it to an external web browser or showing in-situ with embedded web browser.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Action.OpenUrl"** | true |  |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **url** | string | true | Default (browser) url to use  |

## Action ShowCard
<a name="showcard"></a>Action.ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **Action.ShowCard"** | true |  |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **card** | [Container](#container) | true |inline container  defining the card to be shown when this action is invoked. It is up to client to decide how to show this inline card. |

## Action Submit
<a name="action-submit"></a>Action.Submit gathers up input fields, merges with optional data field and generates event to client asking for data to be submitted.  It is up to the client to determine how that data is processed. For example: With BotFramework bots the client would send an activity through the messaging medium to the bot.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Action.Submit"** | true |  |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment. |
| **data** | object | false | initial data that input fields will be combined with.  This is essentially 'hidden' properties |

# Enumerations
The following enumerations are used by various element types.

## ImageSize
<a name="imagesize"></a>Controls the horizontal size (width) of element.  

| Value | Meaning |
|---|---|
| **auto** | The width of the element is optimally chosen depending on the space available in the element's container |
| **stretch** | The width of the element adjusts to match that of its container |
| **small** | Small width |
| **medium** | Medium width |
| **large** | Large width |

## HorizontalAlignment
<a name="HorizontalAlignment"></a>Controls how items are horizontally positioned within their container.

| Value | Meaning |
|---|---|
| **left** | The element is left aligned |
| **center** | The element is centered inside its container |
| **right** | The element is right aligned |

## SeparationStyle
<a name="SeparationStyle"></a>Controls how items are rendered relative to previous element.

| Value | Meaning |
|---|---|
| **default** | The element is spaced relative to previous element using default style|
| **none** | The element is tightly associated with previous element |
| **strong** | The element is strongly and visually disassociated with previous element |

## TextSize
<a name="TextSize"></a>Controls the size of  [TextBlock](#textblock) items.

| Value | Meaning |
|---|---|
| **small** | The smallest text size |
| **normal** | The default text size |
| **medium** | Slightly larger than normal |
| **large** | Slightly larger than medium |
| **extraLarge** | The maximum text size |

## TextWeight
<a name="TextWeight"></a>Controls the weight of [TextBlock](#textblock) items.

| Value | Meaning |
|---|---|
| **lighter** | Lighter text (thinner stroke) |
| **normal** | The default text weight |
| **bolder** | Bolder text (wider stroke) |

## TextColor
<a name="TextColor"></a>Controls the color of [TextBlock](#textblock) items.

| Value | Meaning |
|---|---|
| **default** | The default color, which guarantees appropriate contrast. |
| **dark** | Forces text to be rendered in a dark color that is suitable when displayed over a light background. |
| **light** | Forces text to be rendered in a light color that is suitable when displayed over a dark background. |
| **accent** | The accent color. |
| **good** | Good (such as green) |
| **warning** | Warning (such as yellow) |
| **attention** | Highlight as needing attechment (such as red)|

## ImageStyle
<a name="ImageStyle"></a>Controls the way Image items are displayed.

| Value | Meaning |
|---|---|
| **normal** | The image is displayed within a rectangle. |
| **person** | The image is cropped to a circle, a common way to represent people photos. |

## ContainerStyle
<a name="ContainerStyle"></a>Indicates the style of container desired.

| Value | Meaning |
|---|---|
| **normal** | The container is just a grouping of elements. |
| **emphasis** | The container as a grouping of elements could be emphasized. |


## TextInputStyle
<a name="TextInputStyle"></a>Style hint for [Input.text](#input-text).

| Value | Meaning |
|---|---|
| **text** | Input is a plain text (Default if not specified)|
| **tel** | Input is a telephone number and the client may use this information to provide optimized keyboard input for the user.|
| **url** | Input is a url and the client may use this information to provide optimized keyboard input for the user.|
| **email** | Input is a email and the client may use this information to provide optimized keyboard input for the user.|

## ChoiceSetStyle
<a name="ChoiceSetStyle"></a>Style hint for [Input.ChoiceSet](#input-choiceset).

| Value | Meaning |
|---|---|
| **compact** | choices are preffered to be compactly displayed. Example: ComboBox ) |
| **expanded** | choices are preferred to be displayed for easy input. Example: Checkbox or Radio buttons) |