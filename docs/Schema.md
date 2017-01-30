# CardElements
## CardElement
CardElement is the base type for all elements that can be used to define an Adaptive Card.

| Property | Type | Description |
|---|---|---|
| **size** | [Size](#size) | Specifies the horizontal size of the element. |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | Specifies how the element should be aligned horizontally within its container. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | (Optional) Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |

## TextBlock 
*Extends [CardElement](#cardelement)*

The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.

| Property | Type | Description |
|---|---|---|
| **textSize** | [TextSize](#textsize) | The size of the text |
| **textWeight** | [TextWeight](#textweight) | The weight of the text |
| **textColor** | [TextColor](#textcolor) | The color of the text |
| **isSubtle** | boolean | Indicates whether the color of the text should be slightly toned down to appear less prominent |
| **text** | string | The actual text to display |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | (Optional) Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |

## Image 
*Extends [CardElement](#cardelement)*

The Image element allows for the inclusion of images in an Adaptive Card.

| Property | Type | Description |
|---|---|---|
| **url** | The URL to the image. |
| **style** | [ImageStyle](#imagestyle) | The style in which the image is displayed. |

## ImageGallery 
*Extends [CardElement](#cardelement)*

The ImageGallery allows for the inclusion of a collection images like a photogallery.

| Property | Type | Description |
|---|---|---|
| **size** | [Size](#size) | Specifies the horizontal size of each image in the gallery. |

## Separator 
*Extends [CardElement](#cardelement)*

The Separator element allows for the inclusion of a horizontal separator in an Adaptive Card.

Separator doesn't have additional properties.

## FactGroup 
*Extends [CardElement](#cardelement)*

The FactGroup element makes it simple to display a se  ries of "facts" (e.g. name/value pairs) in a tabular form.

| Property | Type | Description |
|---|---|---|
| **items** | array of [Fact](#fact object) | The facts to be displayed. |

### Fact object
Represents one "fact" in a [FactGroup](#factgroup) element.

| Property | Type | Description |
|---|---|---|
| **name** | string | The fact's name. |
| **value** | string | The fact's value. |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | (Optional) Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |

## ColumnGroup 
*Extends [CardElement](#cardelement)*

The column group element adds the ability to have a set of coulmn objects.

## Container 
*Extends [CardElement](#cardelement)*
The Container is a CardElement which contains a list of CardElements that are logically grouped.

| Property | Type | Description |
|---|---|---|
| **backgroundImageUrl** | string | The URL of an image to be used to fill the background of the container. The image is strached horizontally so it fills the entire available width of the container, and its original aspect ratio is maintained. |
| **backgroundColor** | string | The color of the container's background. This can be any color, and must be expressed in the RGB format with each color component expressed as a 2 digit hexadecimal number. Example: FFFFFF for white, 000000 for black, and 8C8C8C for a shade of gray. |
| **items** | array of [CardElement](#cardelement) | The elements that are to be displayed in this container. |

## Column
**Extends [Container](#container)**

A Column is a container which contains a list of cardElements that are logically grouped.

| Property | Type | Description |
|---|---|---|
| **weight** | string | The weight to apply to this column |

# Enumerations
The following enumerations are used by various element types.

## Size
Controls the horizontal size (width) of element.  

| Value | Meaning |
|---|---|
| **auto** | The width of the element is optimally chosen depending on the space available in the element's container |
| **stretch** | The width of the element adjusts to match that of its container |
| **small** | Small width |
| **medium** | Medium width |
| **large** | Large width |

## HorizontalAlignment
Controls how elements are horizontally positioned within their container.

| Value | Meaning |
|---|---|
| **left** | The element is left aligned |
| **center** | The element is centered inside its container |
| **right** | The element is right aligned |

## TextSize
Controls the size of TextBlock elements.

| Value | Meaning |
|---|---|
| **small** | The smallest text size |
| **normal** | The default text size |
| **medium** | Slightly larger than normal |
| **large** | Slightly larger than medium |
| **extraLarge** | The maximum text size |

## TextWeight
Controls the weight of TextBlock elements.

| Value | Meaning |
|---|---|
| **lighter** | Lighter text (thinner stroke) |
| **normal** | The default text weight |
| **bolder** | Bolder text (wider stroke) |

## TextColor
Controls the color of TextBlock elements.

| Value | Meaning |
|---|---|
| **default** | The default color, which guarantees appropriate contrast. |
| **dark** | Forces text to be rendered in a dark color that is suitable when displayed over a light background. |
| **light** | Forces text to be rendered in a light color that is suitable when displayed over a dark background. |
| **accent** | The accent color. |
| **good** | Good (such as green) |
| **warning** | Warning (such as yellow) |
| **Attention** | Highlight as needing attechment (such as red)|

## ImageStyle
Controls the way Image elements are displayed.

| Value | Meaning |
|---|---|
| **normal** | The image is displayed within a rectangle. |
| **person** | The image is cropped to a circle, a common way to represent people photos. |
