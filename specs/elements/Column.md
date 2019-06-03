<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Column

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `string` | Depends | Must be `"Column"`. | 1.0 |
| **items** | `BlockElement[]` | Yes | The card elements to render inside the `Column`. | 1.0 |
| **selectAction** | `ISelectAction` | No | An Action that will be invoked when the `Column` is tapped or selected. `Action.ShowCard` is not supported. | 1.0 |
| **style** | `ContainerStyle?` | No | Style hint for `Column`. | 1.0 |
| **verticalContentAlignment** | `VerticalContentAlignment` | No, default: top | Defines how the content should be aligned vertically within the column. | 1.0 |
| **bleed** | `boolean` | No | Determines whether the column should bleed through its parent's padding. | 1.0 |
| **backgroundImage** | `BackgroundImage` | No | Specifies the background image. | 1.0 |
| **width** | `string|number` | No | `"auto"`, `"stretch"`, or a number representing relative width of the column in the column group. | 1.0 |
| **id** | `string` | No | A unique identifier associated with the element. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
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