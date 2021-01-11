<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Container

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Container"` | Yes | Must be `"Container"`. | 1.0 |
| **items** | `Element[]` | Yes | The card elements to render inside the `Container`. | 1.0 |
| **selectAction** | `ISelectAction` | No | An Action that will be invoked when the `Container` is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **style** | `ContainerStyle?` | No | Style hint for `Container`. | 1.0 |
| **verticalContentAlignment** | `VerticalContentAlignment` | No, default: `"top"` | Defines how the content should be aligned vertically within the container. | 1.1 |
| **bleed** | `boolean` | No | Determines whether the element should bleed through its parent's padding. | 1.2 |
| **backgroundImage** | `BackgroundImage`, `uri` | No | Specifies the background image. Acceptable formats are PNG, JPEG, and GIF | 1.2 |
| **minHeight** | `string` | No | Specifies the minimum height of the container in pixels, like `"80px"`. | 1.2 |

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


## items

The card elements to render inside the `Container`.

* **Type**: `Element[]`
* **Required**: Yes
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


## selectAction

An Action that will be invoked when the `Container` is tapped or selected. `Action.ShowCard` is not supported.

* **Type**: `ISelectAction`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.Submit`
  * `Action.ToggleVisibility`


## style

Style hint for `Container`.

* **Type**: `ContainerStyle?`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"emphasis"`
  * `"good"`: Added in version 1.2.
  * `"attention"`: Added in version 1.2.
  * `"warning"`: Added in version 1.2.
  * `"accent"`: Added in version 1.2.


## verticalContentAlignment

Defines how the content should be aligned vertically within the container.

* **Type**: `VerticalContentAlignment`
* **Version** : 1.1
* **Required**: No, default: `"top"`
* **Allowed values**:
  * `"top"`
  * `"center"`
  * `"bottom"`


## backgroundImage

Specifies the background image. Acceptable formats are PNG, JPEG, and GIF

* **Type**: `BackgroundImage`, `uri`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `BackgroundImage`
  * `uri`


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

1. Determine the padding...
	1. If 