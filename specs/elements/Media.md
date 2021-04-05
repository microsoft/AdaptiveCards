<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Media

**Introduced in version 1.1**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Media"` | Yes | Must be `"Media"`. | 1.1 |
| **sources** | `MediaSource[]` | Yes | Array of media sources to attempt to play. | 1.1 |
| **poster** | `uri` | No | URL of an image to display before playing. Supports data URI in version 1.2+ | 1.1 |
| **altText** | `string` | No | Alternate text describing the audio or video. | 1.1 |

### Inherited properties

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **fallback** | `Element`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **height** | `BlockElementHeight` | No | Specifies the height of the element. | 1.1 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.1 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.1 |
| **id** | `string` | No | A unique identifier associated with the item. | 1.1 |
| **isVisible** | `boolean` | No, default: `true` | If `false`, this item will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## sources

Array of media sources to attempt to play.

* **Type**: `MediaSource[]`
* **Required**: Yes
* **Allowed values**:
  * `MediaSource`


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

1. Iterate through the `sources` and find the first supported source. If there's no supported source present, engage fallback and stop.
1. If the `poster` is present...
	1. Display the `poster`
1. Else
	1. Display the default host poster
1. Upon user clicking the element, start playing the video and display media controls. Basic controls should include play/pause, a seek bar, volume/fullscreen.
1. Set the `altText` in accessibility properties.