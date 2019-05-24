<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Input.Text

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **id** | `string` | Yes | Unique identifier for the value. Used to identify collected input when the Submit action is performed. | 1.0 |
| **isMultiline** | `boolean` |  No, default: `false` | If `true`, allow multiple lines of input. | 1.0 |
| **maxLength** | `number` |  No | Hint of maximum length characters to collect (may be ignored by some clients). | 1.0 |
| **placeholder** | `string` |  No | Description of the input desired. Displayed when no text has been input. | 1.0 |
| **style** | `string` |  No, default: `"text"` | Style hint for `Input.Text`. | 1.0 |
| **inlineAction** | `object` |  No | The inline action for the input. Typically displayed to the right of the input. It is strongly recommended that an icon on the action (which will be displayed instead of the title of the action). | 1.2 |
| **type** | `"Input.Text"` | Yes | Must be `"Input.Text"`. | 1.0 |
| **value** | `string` |  No | The initial value for this field. | 1.0 |
| **spacing** | `string` |  No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` |  No, default: `false` | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering