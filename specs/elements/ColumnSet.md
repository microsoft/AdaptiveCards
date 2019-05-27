<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# ColumnSet

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **columns** | `Column[]` |  No | The array of `Columns` to divide the region into. | 1.0 |
| **selectAction** | `object` |  No | An Action that will be invoked when the `ColumnSet` is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **type** | `"ColumnSet"` | Yes | Must be `"ColumnSet"`. | 1.0 |
| **id** | `string` |  No | A unique identifier associated with the element. | 1.0 |
| **spacing** | `string` |  No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` |  No, default: `false` | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->


## Rendering

1. If `columns` is null or empty, render as a zero-height element.
1. Otherwise, render each valid column sequentially, from left to right. See the column widths section for determining widths.
1. The final height of each column is determined by the height of the tallest column.

### Column widths

To determine the width of each column...

1. When given the final width of the entire ColumnSet...
1. Subtract the widths of any columns with pixel widths specified.
1. Then, sequentially ask each auto-width column how much space they need, given the remaining available width, and subtract that width from the remaining width before asking the next auto-width column.
1. Then, distribute the remaining width across the stretch-width columns. If one column has a weight of 2 and another 1, then that column gets twice as much space as the other.
1. If at any point remaining space goes to 0 or lower, the rest of the columns get 0 width.