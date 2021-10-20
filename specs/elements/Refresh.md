<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Refresh

**Introduced in version 1.4**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **action** | `Action.Execute` | No | The action to be executed to refresh the card. Clients can run this refresh action automatically or can provide an affordance for users to trigger it manually. | 1.4 |
| **userIds** | `string[]` | No | A list of user Ids informing the client for which users should the refresh action should be run automatically. Some clients will not run the refresh action automatically unless this property is specified. Some clients may ignore this property and always run the refresh action automatically. | 1.4 |


## action

The action to be executed to refresh the card. Clients can run this refresh action automatically or can provide an affordance for users to trigger it manually.

* **Type**: `Action.Execute`
* **Required**: No
* **Allowed values**:
  * `Action.Execute`
<!-- END AUTO-GENERATED -->

## Rendering