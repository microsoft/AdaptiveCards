<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Table

**Introduced in version 1.5**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Table"` | Yes | Must be `"Table"`. | 1.5 |
| **columns** | `TableColumnDefinition[]` | No | Defines the number of columns in the table, their sizes, and more. | 1.5 |
| **rows** | `TableRow[]` | No | Defines the rows of the table. | 1.5 |
| **firstRowAsHeader** | `boolean` | No, default: `true` | Specifies whether the first row of the table should be treated as a header row, and be announced as such by accessibility software. | 1.5 |
| **showGridLines** | `boolean` | No, default: `true` | Specifies whether grid lines should be displayed. | 1.5 |
| **gridStyle** | `ContainerStyle?` | No, default: `"default"` | Defines the style of the grid. This property currently only controls the grid's color. | 1.5 |
| **horizontalCellContentAlignment** | `HorizontalAlignment?` | No | Controls how the content of all cells is horizontally aligned by default. When not specified, horizontal alignment is defined on a per-cell basis. | 1.5 |
| **verticalCellContentAlignment** | `VerticalAlignment?` | No | Controls how the content of all cells is vertically aligned by default. When not specified, vertical alignment is defined on a per-cell basis. | 1.5 |

### Inherited properties

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **fallback** | `Element`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **height** | `BlockElementHeight` | No | Specifies the height of the element. | 1.1 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.5 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.5 |
| **id** | `string` | No | A unique identifier associated with the item. | 1.5 |
| **isVisible** | `boolean` | No, default: `true` | If `false`, this item will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## columns

Defines the number of columns in the table, their sizes, and more.

* **Type**: `TableColumnDefinition[]`
* **Required**: No
* **Allowed values**:
  * `TableColumnDefinition`


## rows

Defines the rows of the table.

* **Type**: `TableRow[]`
* **Required**: No
* **Allowed values**:
  * `TableRow`


## gridStyle

Defines the style of the grid. This property currently only controls the grid's color.

* **Type**: `ContainerStyle?`
* **Required**: No, default: `"default"`
* **Allowed values**:
  * `"default"`
  * `"emphasis"`
  * `"good"`: Added in version 1.2.
  * `"attention"`: Added in version 1.2.
  * `"warning"`: Added in version 1.2.
  * `"accent"`: Added in version 1.2.


## horizontalCellContentAlignment

Controls how the content of all cells is horizontally aligned by default. When not specified, horizontal alignment is defined on a per-cell basis.

* **Type**: `HorizontalAlignment?`
* **Required**: No
* **Allowed values**:
  * `"left"`
  * `"center"`
  * `"right"`


## verticalCellContentAlignment

Controls how the content of all cells is vertically aligned by default. When not specified, vertical alignment is defined on a per-cell basis.

* **Type**: `VerticalAlignment?`
* **Required**: No
* **Allowed values**:
  * `"top"`
  * `"center"`
  * `"bottom"`


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
  * `Table`
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