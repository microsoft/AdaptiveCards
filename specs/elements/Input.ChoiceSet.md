<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Input.ChoiceSet

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Input.ChoiceSet"` | Yes | Must be `"Input.ChoiceSet"`. | 1.0 |
| **choices** | `Input.Choice[]` | Yes | `Choice` options. | 1.0 |
| **id** | `string` | Yes | Unique identifier for the value. Used to identify collected input when the Submit action is performed. | 1.0 |
| **isMultiSelect** | `boolean` | No | Allow multiple choices to be selected. | 1.0 |
| **style** | `ChoiceInputStyle` | No |  | 1.0 |
| **value** | `string` | No | The initial choice (or set of choices) that should be selected. For multi-select, specify a comma-separated string of values. | 1.0 |
| **placeholder** | `string` | No | Description of the input desired. Only visible when no selection has been made, the `style` is `compact` and `isMultiSelect` is `false` | 1.0 |
| **wrap** | `boolean` | No | If `true`, allow text to wrap. Otherwise, text is clipped. | 1.2 |

**Inherited properties**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **errorMessage** | `string` | No | Error message to display when entered input is invalid | 1.3 |
| **isRequired** | `boolean` | No | Whether or not this input is required | 1.3 |
| **label** | `string` | No | Label for this input | 1.3 |
| **fallback** | `Element`, `FallbackOption` | No | Describes what to do when an unknown element is encountered or the requires of this or any children can't be met. | 1.2 |
| **height** | `BlockElementHeight` | No | Specifies the height of the element. | 1.1 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **isVisible** | `boolean` | No, default: `true` | If `false`, this item will be removed from the visual tree. | 1.2 |
| **requires** | `Dictionary<string>` | No | A series of key/value pairs indicating features that the item requires with corresponding minimum version. When a feature is missing or of insufficient version, fallback is triggered. | 1.2 |


## choices

`Choice` options.

* **Type**: `Input.Choice[]`
* **Required**: Yes
* **Allowed values**:
  * `Input.Choice`


## style

* **Type**: `ChoiceInputStyle`
* **Required**: No
* **Allowed values**:
  * `"compact"`
  * `"expanded"`


## fallback

Describes what to do when an unknown element is encountered or the requires of this or any children can't be met.

* **Type**: `Element`, `FallbackOption`
* **Version** : 1.2
* **Required**: No
* **Allowed values**:
  * `ActionSet`
  * `ColumnSet`
  * `Container`
  * `FactSet`
  * `Image`
  * `ImageSet`
  * `Input.ChoiceSet`
  * `Input.Date`
  * `Input.Number`
  * `Input.Text`
  * `Input.Time`
  * `Input.Toggle`
  * `Media`
  * `RichTextBlock`
  * `TextBlock`
  * `"drop"`: Causes this element to be dropped immediately when unknown elements are encountered. The unknown element doesn't bubble up any higher.


## height

Specifies the height of the element.

* **Type**: `BlockElementHeight`
* **Version** : 1.1
* **Required**: No
* **Allowed values**:
  * `"auto"`: The height of the container will be determined by the height of its contents.
  * `"stretch"`: The container will stretch its height to the available remaining height of the parent container.


## spacing

Controls the amount of spacing between this element and the preceding element.

* **Type**: `Spacing`
* **Required**: No
* **Allowed values**:
  * `"default"`
  * `"none"`
  * `"small"`
  * `"medium"`
  * `"large"`
  * `"extraLarge"`
  * `"padding"`
<!-- END AUTO-GENERATED -->

## Rendering

### Labels
The `label` property should be rendered above the input box if present. Clicking/tapping on the rendered label should put focus in the input box. 

The `color`, `isSubtle`, `size`, and `weight` properties provided in the host config under `"inputs":"label":"requiredInputs"` for inputs with `"isRequired":true`, and under `"inputs":"label":"optionalInputs"` for inputs with `"isRequired":false` should be respected. The spacing between the label and the input should be set to the value of `inputSpacing` specified in those same locations in host config.

### Accessibility
The `label` property should be set as the accessibility text for the choice set when present. If the `label` property is not present, the `placeholder` property should be used instead if present.

### Input Validation
 If the input has `"isRequired":true` the label of the input should be marked with the `"inputs":"label":"requiredInputs":"suffix"` value from the host config, or with a * by default. If a required input does not have a label, the suffix should not be used and a warning should be returned.
 
 The `isRequired` property should be validated for this input type. The input should be validated when the user activates a submit action on the card. 
 
 If the input does not pass validation, it should be outlined in the host's `attention` color, and the `errorMessage` should be displayed below the input in the host's `attention` color. If an error message is not present and `isRequired` is set, a warning should be returned.