<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# TextBlock

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **color** | `string` |  No | Controls the color of `TextBlock` elements. | 1.0 |
| **fontType** | `string` |  No | Type of font to use for rendering | 1.0 |
| **horizontalAlignment** | `string` |  No, default: `"left"` | Controls how elements are horizontally positioned within their container. | 1.0 |
| **isSubtle** | `boolean` |  No, default: `false` | If `true`, displays text slightly toned down to appear less prominent. | 1.0 |
| **maxLines** | `number` |  No | Specifies the maximum number of lines to display. | 1.0 |
| **size** | `string` |  No | Controls size of text. | 1.0 |
| **text** | `string` | Yes | Text to display. | 1.0 |
| **type** | `"TextBlock"` | Yes | Must be `"TextBlock"`. | 1.0 |
| **weight** | `string` |  No | Controls the weight of `TextBlock` elements. | 1.0 |
| **wrap** | `boolean` |  No, default: `false` | If `true`, allow text to wrap. Otherwise, text is clipped. | 1.0 |
| **id** | `string` |  No | A unique identifier associated with the element. | 1.0 |
| **spacing** | `string` |  No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` |  No, default: `false` | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering

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