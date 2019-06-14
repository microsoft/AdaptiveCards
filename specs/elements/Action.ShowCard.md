<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Action.ShowCard

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Action.ShowCard"` | Yes | Must be `"Action.ShowCard"`. | 1.0 |
| **card** | `AdaptiveCard` | No | The Adaptive Card to show. | 1.0 |

**Inherited properties**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **title** | `string` | No | Label for button or link that represents this action. | 1.0 |
| **iconUrl** | `uri` | No | Optional icon to be shown on the action in conjunction with the title. Supports data URI in version 1.2+ | 1.1 |
| **style** | `ActionStyle` | No | Controls the style of an Action, which influences how the action is displayed, spoken, etc. | 1.2 |
| **fallback** | `Action`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## card

The Adaptive Card to show.

* **Type**: `AdaptiveCard`
* **Required**: No
* **Allowed values**:
  * `AdaptiveCard`


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

Only allowed inside an `ActionSet` or `card.actions`. If anywhere else, drop and trigger warning.

See `ActionSet` for rendering.