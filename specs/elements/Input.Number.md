<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Input.Number

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Input.Number"` | Yes | Must be `"Input.Number"`. | 1.0 |
| **max** | `number` | No | Hint of maximum value (may be ignored by some clients). | 1.0 |
| **min** | `number` | No | Hint of minimum value (may be ignored by some clients). | 1.0 |
| **placeholder** | `string` | No | Description of the input desired. Displayed when no selection has been made. | 1.0 |
| **value** | `number` | No | Initial value for this field. | 1.0 |
| **id** | `string` | Yes | Unique identifier for the value. Used to identify collected input when the Submit action is performed. | 1.0 |
| **fallback** | `BlockElement, FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **height** | `BlockElementHeight` | No | Specifies the height of the element. | 1.1 |
| **isVisible** | `boolean` | No, default: true | If `false`, this element will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the element requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering