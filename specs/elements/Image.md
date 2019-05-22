# Image element

Displays an image.

**Inherits from BaseElement**.

| Property | Type | Required | Description | Version |
|--|--|--|--|--|
| type | `"Image"` | Yes | Must be `Image` | 1.0 |
| url | `string` | Yes | The URL to the image | 1.0 |
| altText | `string` | No, default `null` | Alternate text describing the image | 1.0 |
| selectAction | `Action` | No, default `null` | An action invoked when the image is tapped or selected. | 1.1 |
| size | `ImageSize` | No, default `"auto"` | Controls the approximate size of the image. Physical dimensions will vary per host. Specify `"auto"` to prevent the image from scaling up (but will scale down to fit), or `"stretch"` to scale the image so that its width fits its container. All options will preserve aspect ratio. | 1.0 |
| width | `string` | No, default `null` | The desired width of the image, ending in 'px'. Ex: `50px`. If specified, `size` property will be ignored. | 1.1 |
| height | `string` | No, default `null` | The desired height of the image | 1.1 |
| style | `ImageStyle` | No, default `default` | Controls the style of the image. | 1.0 |
| backgroundColor | `string` | No, default `null` | Applies a background to the image. Only relevant to transparent images. Valid formats are #AARRGGBB and #RRGGBB (upper or lower case). | 1.1 |
| horizontalAlignment | `HorizontalAlignment` | No, default `"left"` | Controls how the image is horizontally positioned within the parent container. | 1.0 |

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