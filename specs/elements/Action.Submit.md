<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Action.Submit

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Action.Submit"` | Yes | Must be `"Action.Submit"`. | 1.0 |
| **data** | `string`, `object` | No | Initial data that input fields will be combined with. These are essentially ‘hidden’ properties. | 1.0 |
| **associatedInputs** | `AssociatedInputs` | No, default: `"auto"` | Controls which inputs are associated with the submit action. | 1.3 |

### Inherited properties

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **title** | `string` | No | Label for button or link that represents this action. | 1.0 |
| **iconUrl** | `uri` | No | Optional icon to be shown on the action in conjunction with the title. Supports data URI in version 1.2+ | 1.1 |
| **id** | `string` | No | A unique identifier associated with this Action. | 1.0 |
| **style** | `ActionStyle` | No | Controls the style of an Action, which influences how the action is displayed, spoken, etc. | 1.2 |
| **fallback** | `Action`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **tooltip** | `string` | No | Defines text that should be displayed to the end user as they hover the mouse over the action, and read when using narration software. | 1.5 |
| **isEnabled** | `boolean` | No, default: `true` | Determines whether the action should be enabled. | 1.5 |
| **mode** | `ActionMode` | No, default: `"primary"` | Determines whether the action should be displayed as a button or in the overflow menu. | 1.5 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## associatedInputs

Controls which inputs are associated with the submit action.

* **Type**: `AssociatedInputs`
* **Version** : 1.3
* **Required**: No, default: `"auto"`
* **Allowed values**:
  * `"Auto"`: Inputs on the current card and any parent cards will be validated and submitted for this Action.
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
  * `Action.Execute`
  * `Action.OpenUrl`
  * `Action.ShowCard`
  * `Action.Submit`
  * `Action.ToggleVisibility`
  * `"drop"`: Causes this element to be dropped immediately when unknown elements are encountered. The unknown element doesn't bubble up any higher.


## mode

Determines whether the action should be displayed as a button or in the overflow menu.

* **Type**: `ActionMode`
* **Version** : 1.5
* **Required**: No, default: `"primary"`
* **Allowed values**:
  * `"primary"`: Action is displayed as a button.
  * `"secondary"`: Action is placed in an overflow menu (typically a popup menu under a `...` button).
<!-- END AUTO-GENERATED -->

## Rendering

See `ActionSet`.

When user invokes this action, invoke the `ActionInvoked` event, passing along this action, so that host can take the appropriate action.