# Enumerations
The following enumerations are used by various element types.
## Spacing
Controls the amount of space between elements.

| Value | Meaning |
|---|---|
| **none** | No spacing |
| extraNarrow | Minimum amount of spacing |
| **narrow** | Smaller amount of spacing |
| **normal** | Standard amount of spacing |
| **wide** | Larger amount of spacing |
## Size
Controls the horizontal size (width) of element.

| Value | Meaning |
|---|---|
| **auto** | The width of the element is optimally chosen depending on the space available in the element's container |
| **small** | Small width |
| **medium** | Medium width |
| **large** | Large width |
| **stretch** | The width of the element adjusts to match that of its container |
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

## Color
Controls the color of various elements.

| Value | Meaning |
|---|---|
| **default** | The default color for the element (can be different depending on the element type) |
| **accent** | The accent color |

## TextContrast
Controls whether text should be displayed dark-on-light or light-on-dark.

| Value | Meaning |
|---|---|
| **darkOnLight** | Text is displayed using a dark shade. Use this contrast when displaying text over a light background. |
| **lightOnDark** | Text is displayed using a light shade. Use this contrast when displaying text over a dark background. |

## PictureStyle
Controls the way Picture elements are displayed.

| Value | Meaning |
|---|---|
| **normal** | The picture is displayed within a rectangle. |
| **person** | The picture is cropped to a circle, a common way to represent people photos. |
# Element types
## CardElement
CardElement is the base type for all elements that can be used to define an Adaptive Card.

| Property | Type | Description |
|---|---|---|
| **topSpacing** | [Spacing](#spacing) | Specifies the amount of space that should separate this element from the one that precedes it. |
| **size** | [Size](#size) | Specifies the horizontal size of the element. |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | Specifies how the element should be aligned horizontally within its container. |
## Container
The Container element contains a list of elements that are logically grouped.

| Property | Type | Description |
|---|---|---|
| **backgroundImageUrl** | string | The URL of an image to be used to fill the background of the container. The image is strached horizontally so it fills the entire available width of the container, and its original aspect ratio is maintained. |
| **backgroundColor** | string | The color of the container's background. This can be any color, and must be expressed in the RGB format with each color component expressed as a 2 digit hexadecimal number. Example: FFFFFF for white, 000000 for black, and 8C8C8C for a shade of gray. |
| **textContrast** | [TextContrast](#textcontrast) | Specifies whether text in this container should be light-on-dark or dark-on-light. When using light images of background colors, text will likely have to displayed dark-on-light for improved legibility. Similarly, text will have to be displayed light-on-dark against dark backgrounds. |
| **padding** | [Size](#size) | Specifies the amount of padding along the edges of the container. |
| **items** | array of [CardElement](#cardelement) | The elements that are to be displayed in this container. |
## TextBlock
**Extends [CardElement](#cardelement)**
The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.

| Property | Type | Description |
|---|---|---|
| **textSize** | [TextSize](#textsize) | The size of the text |
| **textWeight** | [TextWeight](#textweight) | The weight of the text |
| **textColor** | [Color](#color) | The color of the text |
| **isSubtle** | boolean | Indicates whether the color of the text should be slightly toned down to appear less prominent |
| **text** | string | The actual text to display |

## Picture
**Extends [CardElement](#cardelement)**
The Picture element allows for the inclusion of pictures in an Adaptive Card.

| Property | Type | Description |
|---|---|---|
| **url** | The URL to the picture. |
| **style** | [PictureStyle](#picturestyle) | The style in which the picture is displayed. |

## Separator
**Extends [CardElement](#cardelement)**
The Separator element allows for the inclusion of a horizontal separator in an Adaptive Card.

Separator doesn't have additional properties.

## FactGroup
**Extends [CardElement](#cardelement)**
The FactGroup element makes it simple to display a series of "facts" (e.g. name/value pairs) in a tabular form.

| Property | Type | Description |
|---|---|---|
| **items** | array of [Fact](#fact object) | The facts to be displayed. |

### Fact object
Represents one "fact" in a [FactGroup](#factgroup) element.

| Property | Type | Description |
|---|---|---|
| **name** | string | The fact's name. |
| **value** | string | The fact's value. |
