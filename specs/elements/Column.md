<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Column

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **items** | `array[]` | Yes | The card elements to include in the `Column`. | 1.0 |
| **selectAction** | `object` |  No | An Action that will be invoked when the `Column` is tapped or selected. `Action.ShowCard` is not supported. | 1.1 |
| **style** | `string` |  No | Style hint for `Column`. | 1.0 |
| **width** | `string,number` |  No | The width of the column. Can be `"auto"`, `"stretch"`, a weighted number relative to other columns, or a string specifying pixel width (50px). NOTE: Pixel-sized columns were introduced in version 1.1 | 1.0 |
| **type** | `"Column"` |  No | Must be `"Column"`. | 1.0 |
| **id** | `string` |  No | A unique identifier associated with the element. | 1.0 |
| **spacing** | `string` |  No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` |  No, default: `false` | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering