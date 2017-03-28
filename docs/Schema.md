# Table of Contents

[Cards](#cards)
* [AdaptiveCard](#adaptivecard) - top level card

[CardElements](#CardElements) 
* [TextBlock](#textblock) - display text
* [Image](#image) - display an image
* [Input.Text](#inputtext) - get text input from user
* [Input.Date](#inputdate) - get date input from user
* [Input.Time](#inputtime) - get time input from user
* [Input.Number](#inputnumber) - get number input from user
* [Input.Toggle](#inputtoggle) - get user to select betweeen two options
* [Input.ChoiceSet](#inputchoiceset) - display set of choices to the user 
    * [Choice](#choice) - choice object

[Containers](#containers) 
* [Container](#container) - container of items
* [ColumnSet](#columnset) -  container of columns
    * [Column](#column) - container of items with column properties
* [ImageSet](#imageset) - container of Images
* [FactSet](#factset) - container of facts
    * [Fact](#fact) - fact object

[Actions](#actions)
* [Action.Http](#actionhttp) - defines action which collects input and does raw HTTP call to arbitrary Http endpoint
* [Action.OpenUrl](#actionopenurl) - defines action which opens a url either in external browser or embedded browser
* [Action.ShowCard](#actionshowcard) - defines action which shows a card to the user
* [Action.Submit](#actionsubmit) - defines action which collects input and sends via client appropriate mechanism (it's up to client)

# Cards

## AdaptiveCard
AdaptiveCard is top level object which represents a card 

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"AdaptiveCard"** |
| **body** | [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **actions** |[Action](#action)[]| false | Actions |
| **version** | string| false | version of schema that this card was authored |
| **minVersion** | string|false| if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not supported are safe to ignore|
| **fallbackText** | string|false| if a client is not able to show the card, show fallbackText to the user. This can be in markdown format. |

# Card Element

A card element is a visual element to add to a container.  Shared properties 

> NOTE: You cannot create an CardElement directly, only the derived types.

| Property | Type |  Required |Description |
|---|---|---|---|
| **separation** | [SeparationStyle](#separationstyle) | none | visually separate this element from preiovus element |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false |  Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |

## Image 

*Extends [CardElement](#CardElement)*

The Image element allows for the inclusion of images in an Adaptive Card.

| Property | Type | Required |Description |
|---|---|---|---|
| **type**| string | true | **"Image"** |
| **url** | string | true | The URL to the image. |
| **style** | [ImageStyle](#imagestyle) | false | The style in which the image is displayed. |
| **selectAction** | [Action](#action) | false | Action to perform for a selection for this image, (this allows image to act as an action) |
| **size** | [ImageSize](#imagesize) | false | Specifies the suggested size of the image. |
| **altText** | string  | false | Alternate text for the image for accessibility |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | false |Specifies how the element should be aligned horizontally within its container. |

## TextBlock 
*Extends [CardElement](#CardElement)*

The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"TextBlock"** |
| **text** | string | true |The actual text to display |
| **size** | [TextSize](#textsize) | false |The size of the text |
| **weight** | [TextWeight](#textweight) | false |The weight of the text |
| **color** | [TextColor](#textcolor) | false |The color of the text |
| **isSubtle** | boolean |false | Indicates whether the color of the text should be slightly toned down to appear less prominent |
| **wrap** | boolean | false | Indicates whether the text should be allowed to wrap |
| **maxLines** | number | false | When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use. |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | false |Specifies how the element should be aligned horizontally within its container. |

### Formatting Functions

When sending TextBlock items with date or time information you need to be able to translate the date or time to the
recipients timezone using their locale.  This is a task which is almost always way easier for the client to do then
for the sender.  To make it easy for clients to do this we have the ability to invoke a DATE() and TIME() function
inside text of the textblock.

These functions can be invoked anywhere in the text of a text block like this:

    "Your order was shipped {{DATE(2017-02-13T20:46:30Z, Long)}} and will arrive at {{TIME(2017-02-13T20:00:00Z, Short)}}" 

#### Date Formatting Function

The DATE function is passed an ISO-8601 formatted date-time record (example: 2017-02-13T20:46:30Z), and an optional hint expressing
how you would like the date to be formatted for the user in the text string.

The format is expressed as a binding clause like this:

    {{DATE(..iso-8601.., Short|Long)}}

Example for (en-us):

    {{DATE(2017-02-13T20:46:30Z, Short)}} => 2/13/2017
    {{DATE(2017-02-13T20:46:30Z, Long)}} => Monday, February 13, 2017

> NOTE: The hint part of the function is optional and can be omitted like this:

    {{DATE(2017-02-13T20:46:30z)}}


#### Time Formatting Function

The TIME function is passed an ISO-8601 formatted date-time record (example: 2017-02-13T20:46:30Z), and an optional hint expressing
how you would like the time to be formatted for the user in the text string.

The format is expressed as a binding clause like this:

    {{TIME(..iso-8601.., Short|Long)}}

Example for (en-us):

    {{TIME(2017-02-13T20:46:30Z, Short)}} => 8:46 PM
    {{TIME(2017-02-13T20:46:30Z, Long)}} => 8:46:30 PM

> NOTE: The hint part of the function is optional and can be omitted like this:

    {{TIME(2017-02-13T20:46:30z)}}


## Input
*Extends [CardElement](#CardElement)*

Input has shared properties for input to collect information from a user. 

>NOTE: You cannot add an Input directly, only the derived types.

| Property | Type | Required | Description |
|---|---|---|---|
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **value** | string | false | The initial value for a field |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or Http action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |

### Input.Text
*Extends [Input](#input)*

Input.Text collects text from the user

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Input.Text"** |
| **placeholder** | string | false | initial text descripting the input desired |
| **style**| [TextInputStyle](#textinputstyle) | false | Hint of style of input, if client doesn't support the style it will become simple text input || **isMultiline** | bool | false | true to collect multiple lines of text (default is false)|
| **maxLength** | number | false | hint of maximum length characters to collect *(may be ignored by some clients)* |
| **isMultiline** | boolean | false | Do you want to allow multiple lines of input |

### Input.Date
*Extends [Input](#input)*

Input.Date collects text from the user in form of a date. 

>NOTE: Clients may not be able to validate that the value of this is a valid date.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Input.Date"** |
| **placeholder** | string | false | initial text descripting the input desired |
| **min** | string | false | Minimum date in ISO-8601 format (Not all clients will be able to honor this)|
| **max** | string  | false | Maximum date in ISO-8601 format (Not all clients will be able to honor this)|

### Input.Time
*Extends [Input](#input)*

Input.Time collects text from the user in form of a time of day.

>NOTE: Clients may not be able to validate that the value of this is a valid time expression.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Input.Time"** |
| **placeholder** | string | false | initial text descripting the input desired |
| **min** | string | false | Minimum time (Not all clients will be able to honor this)|
| **max** | string  | false | Maximum time (Not all clients will be able to honor this)|

### Input.Number
*Extends [Input](#input)*

Input.Number collects text from the user with a bias towards a number. 

>NOTE: Value collected may not be valid depending on the capabilities of the client.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Input.Number"** |
| **placeholder** | string | false | initial text descripting the input desired |
| **min** | number | false | Minimum number (Not all clients will be able to honor this)|
| **max** | number | false | Maximum number (Not all clients will be able to honor this)|

### Input.Toggle
*Extends [Input](#input)*

Input.Toggle collects a selection between two values, with **value** representing the current selected toggle value (either value1 or value2).

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true |  **"Input.ToggleChoice"** || **style** | [ChoiceInputStyle](#choiceinputstyle) | false | Style for choice | 
| **title** | string | true | The title for the toggle |
| **valueOn** | string | false | The value to use when toggle is selected (default:true)| 
| **valueOff** | string | false  | The value to use when toggle is not selected (default:false)| 
| **value** | string | false  | The value current value (default:false) | 

### Input.ChoiceSet
*Extends [Input](#input)*

Shows an array of choices the to the user.

* If **isMultiSelect** is false, then the result will be the single selected choice value
* If **isMultiSelect** is true, then the result will be an array of the selected choice values 
(non-selected choices will be omitted).

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true |  **"Input.ChoiceSet"** || **style** | [ChoiceInputStyle](#choiceinputstyle) | false | Style for choice | 
| **style**| [ChoiceSetStyle](#choicesetstyle) | false | Hint of style of input |
| **isMultiSelect** | boolean | false | allow multiple choices to be selected (Default=false)|
| **choices** | Choice[] | true | the choice options |

#### Choice
Represents a single Choice

| Property | Type | Required | Description |
|---|---|---|---|
| **title** | string | true  | The title label for a choice|
| **value** | string | true  | the raw value for the choice|
| **isSelected** | bool |  false |is the choice selected |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |

# Containers

## Container 
*Extends [CardElement](#cardelement)*

A  Container is a CardElement which contains a list of CardElements that are logically grouped.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Container"** |
| **items** |  [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **actions** | [Action](#action)[] | false | Actions associated with this container |
| **selectAction** | [Action](#action) | false | Action to perform for a tap on this container, (this allows entire container to act as an action) |

## ColumnSet 
*Extends [CardElement](#CardElement)*

The column Set element adds the ability to have a set of Column objects.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ColumnSet"** |
| **columns** | [Column](#column)[] | true | array of columns (each a container of items)  |

## Column
**Extends [Container](#container)**

A Column is a container which contains a list of CardElements that are logically grouped.

| Property | Type | Required |  Description |
|---|---|---|---|
| **type**| string | true |  **"Column"** |
| **size** | string | false | "auto", "stretch", or a number representing relative width of the column in the column Set (Default:Auto)|


## ImageSet 
*Extends [CardElement](#CardElement)*

The ImageSet allows for the inclusion of a collection images like a photoSet.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ImageSet"** |
| **images**| [Image](#image)[] | true | Array of Image objects |
| **imageSize** | [ImageSize](#imagesize) | false | Specifies the suggested size of the images in the Set. |

## FactSet 
*Extends [CardElement](#CardElement)*

The FactSet element makes it simple to display a series of "facts" (e.g. name/value pairs) in a tabular form.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"FactSet"** |
| **facts** | [Fact](#fact)[] | true| The facts to be displayed. |

### Fact 
Represents one "fact" in a [FactSet](#factset) element.

| Property | Type | Required | Description |
|---|---|---|---|
| **title** | string | true | The fact's title. |
| **value** | string | true |The fact's value. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |


# Actions
Actions define clickable targets that do something.

## Action

## Action.Http
*Extends [Action](#action)*

Action.Http represents the properties needed to do an Http request. All input properties are available for use via 
data binding.  Properties can be data bound to the Uri and Body properties, allowing you to send a request
to an arbitrary url.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"HttpAction"** |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **url** | string | true | url to use (can have binding information) |
| **method** | string | true | Http method (Example: POST) |
| **headers** | object | false | Object which represents headers Example: { "content-type":"application/json" }  |
| **body** | string | false | content to post (can have binding information) |

## Action.OpenUrl
*Extends [Action](#action)*

When Action.OpenUrl is invoked it will show the given url, either by launching it to an external web browser or showing in-situ 
with embedded web browser

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Action.OpenUrl"** |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **url** | string | true | Default (browser) url to use  |

## Action.ShowCard
*Extends [Action](#action)*

Action.ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **Action.ShowCard"** |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **card** | [Container](#container) | true |inline container  defining the card to be shown when this action is invoked. It is up to client to decide how to show this inline card. |

## Action.Submit
*Extends [Action](#action)*

Action.Submit gathers up input fields, merges with optional data field and generates event to 
client asking for data to be submitted.  It is up to the client to determine how that data is processed.
For example: With BotFramework bots the client would send an activity through the messaging medium to the bot.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Action.Submit"** |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **data** | object | false | initial data that input fields will be combined with.  This is essentially 'hidden' properties |

# Enumerations
The following enumerations are used by various element types.

## ImageSize
Controls the horizontal size (width) of element.  

| Value | Meaning |
|---|---|
| **auto** | The width of the element is optimally chosen depending on the space available in the element's container |
| **stretch** | The width of the element adjusts to match that of its container |
| **small** | Small width |
| **medium** | Medium width |
| **large** | Large width |

## HorizontalAlignment
Controls how items are horizontally positioned within their container.

| Value | Meaning |
|---|---|
| **left** | The element is left aligned |
| **center** | The element is centered inside its container |
| **right** | The element is right aligned |

## SeparationStyle
Controls how items are rendered relative to previous element.

| Value | Meaning |
|---|---|
| **default** | The element is spaced relative to previous element using default style|
| **none** | The element is tightly associated with previous element |
| **strong** | The element is strongly and visually disassociated with previous element |

## TextSize
Controls the size of TextBlock items.

| Value | Meaning |
|---|---|
| **small** | The smallest text size |
| **normal** | The default text size |
| **medium** | Slightly larger than normal |
| **large** | Slightly larger than medium |
| **extraLarge** | The maximum text size |

## TextWeight
Controls the weight of TextBlock items.

| Value | Meaning |
|---|---|
| **lighter** | Lighter text (thinner stroke) |
| **normal** | The default text weight |
| **bolder** | Bolder text (wider stroke) |

## TextColor
Controls the color of TextBlock items.

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
Controls the way Image items are displayed.

| Value | Meaning |
|---|---|
| **normal** | The image is displayed within a rectangle. |
| **person** | The image is cropped to a circle, a common way to represent people photos. |

## TextInputStyle
Style hint for [TextInput](#textinput).

| Value | Meaning |
|---|---|
| **text** | Input is a plain text (Default if not specified)|
| **tel** | Input is a telephone number and the client may use this information to provide optimized keyboard input for the user.|
| **url** | Input is a url and the client may use this information to provide optimized keyboard input for the user.|
| **email** | Input is a email and the client may use this information to provide optimized keyboard input for the user.|

## ChoiceSetStyle
Style hint for [Input.ChoiceSet](#input.choiceset).

| Value | Meaning |
|---|---|
| **compact** | choices are preffered to be compactly displayed. Example: ComboBox ) |
| **expanded** | choices are preferred to be displayed for easy input. Example: Checkbox or Radio buttons) |

