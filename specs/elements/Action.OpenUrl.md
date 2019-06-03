<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Action.OpenUrl

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `string` | Depends | Must be `"Action.OpenUrl"`. | 1.0 |
| **url** | `uri` | Yes | The URL to open. | 1.0 |
| **title** | `string` | No | Label for button or link that represents this action. | 1.0 |
| **iconUrl** | `uri` | No | Optional icon to be shown on the action in conjunction with the title. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering

See `ActionSet`.

When user invokes this action, invoke the `ActionInvoked` event, passing along this action, so that host can take the appropriate action.