<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# TextBlock

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"TextBlock"` | Yes | Must be `"TextBlock"`. | 1.0 |
| **text** | `string` | Yes | Text to display. A subset of markdown is supported (https://aka.ms/ACTextFeatures) | 1.0 |
| **color** | `Colors` | No | Controls the color of `TextBlock` elements. | 1.0 |
| **fontType** | `FontType` | No | Type of font to use for rendering | 1.2 |
| **horizontalAlignment** | `HorizontalAlignment` | No | Controls the horizontal text alignment. | 1.0 |
| **isSubtle** | `boolean` | No | If `true`, displays text slightly toned down to appear less prominent. | 1.0 |
| **maxLines** | `number` | No | Specifies the maximum number of lines to display. | 1.0 |
| **size** | `FontSize` | No | Controls size of text. | 1.0 |
| **weight** | `FontWeight` | No | Controls the weight of `TextBlock` elements. | 1.0 |
| **wrap** | `boolean` | No | If `true`, allow text to wrap. Otherwise, text is clipped. | 1.0 |

**Inherited properties**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **fallback** | `Element`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **height** | `BlockElementHeight` | No | Specifies the height of the element. | 1.1 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **id** | `string` | No | A unique identifier associated with the item. | 1.0 |
| **isVisible** | `boolean` | No, default: `true` | If `false`, this item will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## color

Controls the color of `TextBlock` elements.

* **Type**: `Colors`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"dark"`
  * `"light"`
  * `"accent"`
  * `"good"`
  * `"warning"`
  * `"attention"`


## fontType

Type of font to use for rendering

* **Type**: `FontType`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"monospace"`


## horizontalAlignment

Controls the horizontal text alignment.

* **Type**: `HorizontalAlignment`
* **Required**: No
* **Allowed values**:
  * `"left"`
  * `"center"`
  * `"right"`


## size

Controls size of text.

* **Type**: `FontSize`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"small"`
  * `"medium"`
  * `"large"`
  * `"extraLarge"`


## weight

Controls the weight of `TextBlock` elements.

* **Type**: `FontWeight`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"lighter"`
  * `"bolder"`


## fallback

Describes what to do when an unknown element is encountered or the requires of this or any children can't be met.

* **Type**: `Element`, `FallbackOption`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `ActionSet`
  * `Column`
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


## height

Specifies the height of the element.

* **Type**: `BlockElementHeight`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `"auto"`: The height of the container will be determined by the height of its contents.
  * `"stretch"`: The container will stretch its height to the available remaining height of the parent container.


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