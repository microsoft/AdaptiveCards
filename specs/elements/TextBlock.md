# TextBlock element

Displays text.

**Inherits from BaseElement.**

| Property | Type | Required | Description | Version |
|--|--|--|--|--|
| type | `"TextBlock"` | Yes | Must be `"TextBlock"`. | 1.0 |
| text | `string` | Yes | Text to display. | 1.0 |
| wrap | `boolean` | No, default `false` | If `true`, allow text to wrap. Otherwise, text is clipped. | 1.0 |
| maxLines | `number?` | No, default `null` | If set, specifies the maximum number of lines to display. | 1.0 |
| size | `TextSize` | No, default `default` | Controls size of the text. | 1.0 |
| weight | `TextWeight` | No, default `default` | Controls the weight of the text. | 1.0 |
| isSubtle | `boolean` | No, default `false` | If `true`, displays text slightly toned down to appear less prominent. | 1.0 |
| horizontalAlignment | `TextHorizontalAlignment` | No, default `left` | Controls the text alignment. | 1.0 |
| color | `Color` | No, default `default` | Controls the color of the text. | 1.0 |


# Rendering

1. Render the text, respecting all the properties.
	1. Color of the text
		1. Grab the correct foreground color from host config depending on `color`.
		1. If `isSubtle` is true, use the suble variant. Otherwise, use the normal variant.
	1. Weight of the text
		1. Grab the correct weight value from host config depending on `weight`.
	1. Size of the text
		1. Grab the correct font size from `hostConfig.fontSizes` depending on `size`.
	1. Text alignment
		1. Base the text alignment on the `horizontalAlignment` property. Be sure to set **text alignment** and not layout horizontal alignment. Big difference!