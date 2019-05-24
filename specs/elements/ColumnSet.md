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