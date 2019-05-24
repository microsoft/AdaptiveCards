<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Image

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **altText** | `string` |  No | Alternate text describing the image. | 1.0 |
| **backgroundColor** | `string` |  No | Applies a background to a transparent image. This property will respect the image style. | 1.1 |
| **height** | `string` |  No | The desired on-screen height of the image, ending in 'px'. E.g., 50px. This overrides the `size` property. | 1.1 |
| **horizontalAlignment** | `string` |  No, default: `"left"` | Controls how elements are horizontally positioned within their container. | 1.0 |
| **selectAction** | `object` |  No | An Action that will be invoked when the `Image` is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **size** | `string` |  No, default: `"auto"` | Controls the approximate size of the image. The physical dimensions will vary per host. Specify `"auto"` for true image dimension, or `"stretch"` to force it to fill the container. | 1.0 |
| **style** | `string` |  No | Controls how this `Image` is displayed. | 1.0 |
| **type** | `"Image"` | Yes | Must be `"Image"`. | 1.0 |
| **url** | `string` | Yes | The URL to the image. | 1.0 |
| **width** | `string` |  No | The desired on-screen width of the image, ending in 'px'. E.g., 50px. This overrides the `size` property. | 1.1 |
| **id** | `string` |  No | A unique identifier associated with the element. | 1.0 |
| **spacing** | `string` |  No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` |  No, default: `false` | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering

A host must perform a GET request on the `url` specified to obtain the image.

### Size and stretching behavior

1. If `width` and/or `height` is specified and valid...
	1. If both are specified and valid...
		1. Set the width/height as specified, and set the image's fill mode to stretch to fill (aspect ratio should distort if needed so that image fills exactly the width/height).
	1. Else...
		1. Set whichever dimension is specified, and set the image's fill mode to uniform to fill. Aspect ratio should be preserved. The unspecified dimension will be determined by the image's aspect ratio.
1. Else, use the `size` property...
	1. If `auto`...
		1. Preserve aspect ratio, do not scale up the image, but scale it down if it's too large to fit.
	1. If `stretch`...
		1. Preserve aspect ratio, set the image's width to stretch to its container's width. Image's height will be determined by the aspect ratio. The image can either scale up or down as needed.
	1. If `small`, `medium`, or `large`...
		1. Grab the corresponding pixel width value from `hostConfig.imageSizes`, and then render the image as if the `width` property was set to that pixel width.


### Style

1. If `style` is set to `person`, apply an ellipse clipping to the image. Assuming the image is square, it'll result in a circle. But if the source image isn't square, it'll result in an ellipse, which is fine.


### Background color

1. If `backgroundColor` is specified and valid, set the color as the background color of the image control. Any cropping applied with `style` should be applied on TOP of the background color (a.k.a. the background color should also be ellipse-cropped when `"style": "person"`).


### Horizontal alignment

1. Set the horizontal alignment as specified in `horizontalAlignment`.


### Select action

1. If `selectAction` is specified and valid, turn the image into a clickable image, and upon user clicking, invoke the `selectAction`. Note that `Action.ShowCard` is not supported (that would be considered invalid), and a warning should be issued if it's used here.