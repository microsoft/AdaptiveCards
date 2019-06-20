<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Input.Choice

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **value** | `string` | Yes | The raw value for the choice. **NOTE:** do not use a `,` in the value, since a `ChoiceSet` with `isMultiSelect` set to `true` returns a comma-delimited string of choice values. | 1.0 |
| **title** | `string` | No | Text to display. If style property of corresponding `Input.ChoiceSet` is `rating`, then this text will be hidden from view. | 1.0 |
| **iconSelected** | `uri` | No | The URL to the image of the selected/hovered icon. If no icon is provided, then the corresponding icon from the previous `Input.Choice` will be used. | 1.3 |
| **iconUnselected** | `uri` | No | The URL to the image of the unselected/unhovered icon. If no icon is provided, then the corresponding icon from the previous `Input.Choice` will be used. | 1.3 |
<!-- END AUTO-GENERATED -->

## Rendering