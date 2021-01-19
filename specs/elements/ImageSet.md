<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# ImageSet

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"ImageSet"` | Yes | Must be `"ImageSet"`. | 1.0 |
| **images** | `Image[]` | Yes | The array of `Image` elements to show. | 1.0 |
| **imageSize** | `ImageSize` | No, default: `"medium"` | Controls the approximate size of each image. The physical dimensions will vary per host. Auto and stretch are not supported for ImageSet. The size will default to medium if those values are set. | 1.0 |

### Inherited properties

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **fallback** | `Element`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **height** | `BlockElementHeight` | No | Specifies the height of the element. | 1.1 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **id** | `string` | No | A unique identifier associated with the item. | 1.0 |
| **isVisible** | `boolean` | No, default: `true` | If `false`, this item will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## images

The array of `Image` elements to show.

* **Type**: `Image[]`
* **Required**: Yes
* **Allowed values**:
  * `Image`


## imageSize

Controls the approximate size of each image. The physical dimensions will vary per host. Auto and stretch are not supported for ImageSet. The size will default to medium if those values are set.

* **Type**: `ImageSize`
* **Required**: No, default: `"medium"`
* **Allowed values**:
  * `"auto"`: Image will scale down to fit if needed, but will not scale up to fill the area.
  * `"stretch"`: Image with both scale down and up to fit as needed.
  * `"small"`: Image is displayed with a fixed small width, where the width is determined by the host.
  * `"medium"`: Image is displayed with a fixed medium width, where the width is determined by the host.
  * `"large"`: Image is displayed with a fixed large width, where the width is determined by the host.


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