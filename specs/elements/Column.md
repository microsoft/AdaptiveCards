<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Column

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **items** | `Element[]` | No | The card elements to render inside the `Column`. | 1.0 |
| **backgroundImage** | `BackgroundImage`, `uri` | No | Specifies the background image. Acceptable formats are PNG, JPEG, and GIF | 1.2 |
| **bleed** | `boolean` | No | Determines whether the column should bleed through its parent's padding. | 1.2 |
| **fallback** | `Column`, `FallbackOption` | No | Describes what to do when an unknown item is encountered or the requires of this or any children can't be met. | 1.2 |
| **minHeight** | `string` | No | Specifies the minimum height of the column in pixels, like `"80px"`. | 1.2 |
| **separator** | `boolean` | No | When `true`, draw a separating line between this column and the previous column. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this column and the preceding column. | 1.0 |
| **selectAction** | `ISelectAction` | No | An Action that will be invoked when the `Column` is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **style** | `ContainerStyle?` | No | Style hint for `Column`. | 1.0 |
| **verticalContentAlignment** | `VerticalContentAlignment` | No, default: `"top"` | Defines how the content should be aligned vertically within the column. | 1.1 |
| **width** | `string`, `number` | No | `"auto"`, `"stretch"`, a number representing relative width of the column in the column group, or in version 1.1 and higher, a specific pixel width, like `"50px"`. | 1.0 |


## items

The card elements to render inside the `Column`.

* **Type**: `Element[]`
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


## backgroundImage

Specifies the background image. Acceptable formats are PNG, JPEG, and GIF

* **Type**: `BackgroundImage`, `uri`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `BackgroundImage`
  * `uri`


## fallback

Describes what to do when an unknown item is encountered or the requires of this or any children can't be met.

* **Type**: `Column`, `FallbackOption`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `Column`
  * `"drop"`: Causes this element to be dropped immediately when unknown elements are encountered. The unknown element doesn't bubble up any higher.


## spacing

Controls the amount of spacing between this column and the preceding column.

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


## selectAction

An Action that will be invoked when the `Column` is tapped or selected. `Action.ShowCard` is not supported.

* **Type**: `ISelectAction`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.Submit`
  * `Action.ToggleVisibility`


## style

Style hint for `Column`.

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

Defines how the content should be aligned vertically within the column.

* **Type**: `VerticalContentAlignment`
* **Version** : 1.1
* **Required**: No, default: `"top"`
* **Allowed values**:
  * `"top"`
  * `"center"`
  * `"bottom"`
<!-- END AUTO-GENERATED -->

## Rendering

Render the column itself just like a `Container`.

### Column widths

#### Fixed pixel width

The width is assigned by a specific author-specificied width. These colums are first in terms of priority of getting space allocated.

#### Auto

The width is determined by the content inside the column, but limited by the total remaining space. These columns are second in terms of priority of getting space allocated.

![img](assets/Column/Width.Auto.PNG)

#### Stretch / weighted number

These columns distribute the final remaining space according to their weighted number. If simply set to `stretch`, assign a weight of `1`. These colums are last in terms of priority of getting space allocated.