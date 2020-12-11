<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Image

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Image"` | Yes | Must be `"Image"`. | 1.0 |
| **url** | `uri` | Yes | The URL to the image. Supports data URI in version 1.2+ | 1.0 |
| **altText** | `string` | No | Alternate text describing the image. | 1.0 |
| **backgroundColor** | `string` | No | Applies a background to a transparent image. This property will respect the image style. | 1.1 |
| **height** | `string`, `BlockElementHeight` | No, default: `"auto"` | The desired height of the image. If specified as a pixel value, ending in 'px', E.g., 50px, the image will distort to fit that exact height. This overrides the `size` property. | 1.1 |
| **horizontalAlignment** | `HorizontalAlignment` | No | Controls how this element is horizontally positioned within its parent. | 1.0 |
| **selectAction** | `ISelectAction` | No | An Action that will be invoked when the `Image` is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **size** | `ImageSize` | No | Controls the approximate size of the image. The physical dimensions will vary per host. | 1.0 |
| **style** | `ImageStyle` | No | Controls how this `Image` is displayed. | 1.0 |
| **width** | `string` | No | The desired on-screen width of the image, ending in 'px'. E.g., 50px. This overrides the `size` property. | 1.1 |

### Inherited properties

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **fallback** | `Element`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **id** | `string` | No | A unique identifier associated with the item. | 1.0 |
| **isVisible** | `boolean` | No, default: `true` | If `false`, this item will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## height

The desired height of the image. If specified as a pixel value, ending in 'px', E.g., 50px, the image will distort to fit that exact height. This overrides the `size` property.

* **Type**: `string`, `BlockElementHeight`
* **Version** : 1.1
* **Required**: No, default: `"auto"`
* **Allowed values**:
  * `string`
  * `"auto"`: The height of the container will be determined by the height of its contents.
  * `"stretch"`: The container will stretch its height to the available remaining height of the parent container.


## horizontalAlignment

Controls how this element is horizontally positioned within its parent.

* **Type**: `HorizontalAlignment`
* **Required**: No
* **Allowed values**:
  * `"left"`
  * `"center"`
  * `"right"`


## selectAction

An Action that will be invoked when the `Image` is tapped or selected. `Action.ShowCard` is not supported.

* **Type**: `ISelectAction`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.Submit`
  * `Action.ToggleVisibility`


## size

Controls the approximate size of the image. The physical dimensions will vary per host.

* **Type**: `ImageSize`
* **Required**: No
* **Allowed values**:
  * `"auto"`: Image will scale down to fit if needed, but will not scale up to fill the area.
  * `"stretch"`: Image with both scale down and up to fit as needed.
  * `"small"`: Image is displayed with a fixed small width, where the width is determined by the host.
  * `"medium"`: Image is displayed with a fixed medium width, where the width is determined by the host.
  * `"large"`: Image is displayed with a fixed large width, where the width is determined by the host.


## style

Controls how this `Image` is displayed.

* **Type**: `ImageStyle`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"person"`


## fallback

Describes what to do when an unknown element is encountered or the requires of this or any children can't be met.

* **Type**: `Element`, `FallbackOption`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `ActionSet`
  * `ColumnSet`
  * `Container`
  * `FactSet`
  * `Image`
  * `ImageSet`
  * `Input.ChoiceSet`
  * `Input.Date`
  * `Input.Number`
  * `Input.Text`
  * `Input.Time`
  * `Input.Toggle`
  * `Media`
  * `RichTextBlock`
  * `TextBlock`
  * `"drop"`: Causes this element to be dropped immediately when unknown elements are encountered. The unknown element doesn't bubble up any higher.


## spacing

Controls the amount of spacing between this element and the preceding element.

* **Type**: `Spacing`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"none"`
  * `"small"`
  * `"medium"`
  * `"large"`
  * `"extraLarge"`
  * `"padding"`
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