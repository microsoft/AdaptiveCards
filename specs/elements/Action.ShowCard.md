<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Action.ShowCard

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `string` | Yes | Must be `"Action.ShowCard"`. | 1.0 |
| **title** | `string` |  No | Label for button or link that represents this action. | 1.0 |
| **iconUrl** | `string` |  No | Optional icon URL to be shown on the action in conjunction with the title. Supports data URI in version 1.2+ | 1.1 |
| **card** | `object` | Yes | Root element in an Adaptive Card. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering

Only allowed inside an `ActionSet` or `card.actions`. If anywhere else, drop and trigger warning.

Render as a normal button. When clicked, see `ActionSet` for how to render the show card.