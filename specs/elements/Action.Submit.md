<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Action.Submit

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Action.Submit"` | Yes | Must be `"Action.Submit"`. | 1.0 |
| **data** | `string`, `object` | No | Initial data that input fields will be combined with. These are essentially ‘hidden’ properties. | 1.0 |
| **inputs** | `string[]`, `ActionInputs` | No, default: `"All"` | None, All, or an array of ids for inputs (or containers of inputs) that should be submitted with this action and validated before allowing it. | 1.3 |

**Inherited properties**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **title** | `string` | No | Label for button or link that represents this action. | 1.0 |
| **iconUrl** | `uri` | No | Optional icon to be shown on the action in conjunction with the title. Supports data URI in version 1.2+ | 1.1 |
| **style** | `ActionStyle` | No | Controls the style of an Action, which influences how the action is displayed, spoken, etc. | 1.2 |
| **fallback** | `Action`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## inputs

None, All, or an array of ids for inputs (or containers of inputs) that should be submitted with this action and validated before allowing it.

* **Type**: `string[]`, `ActionInputs`
* **Version** : 1.3
* **Required**: No, default: `"All"`
* **Allowed values**:
  * `string`
  * `"All"`: All inputs will be validated and submitted for this Action.
  * `"None"`: None of the inputs will be validated or submitted for this Action.


## style

Controls the style of an Action, which influences how the action is displayed, spoken, etc.

* **Type**: `ActionStyle`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `"default"`: Action is displayed as normal
  * `"positive"`: Action is displayed with a positive style (typically the button becomes accent color)
  * `"destructive"`: Action is displayed with a destructive style (typically the button becomes red)


## fallback

Describes what to do when an unknown element is encountered or the requires of this or any children can't be met.

* **Type**: `Action`, `FallbackOption`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `Action.OpenUrl`
  * `Action.ShowCard`
  * `Action.Submit`
  * `Action.ToggleVisibility`
  * `"drop"`: Causes this element to be dropped immediately when unknown elements are encountered. The unknown element doesn't bubble up any higher.
<!-- END AUTO-GENERATED -->

## Rendering

See `ActionSet`.

When user invokes this action, invoke the `ActionInvoked` event, passing along this action, so that host can take the appropriate action.

The action button should be greyed out if any of the inputs referenced in `inputs` do not meet the requirements specified by the card author. These referenced inputs should be returned to the host when the submit action is invoked by the user.