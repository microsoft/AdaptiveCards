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
| **wrap** | `boolean` | No | If `true`, allow text to wrap. Otherwise, text is clipped. | 1.2 |

**Inherited properties**

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **isRequired** | `boolean` | No | Specifies whether the input requires a value. | 1.3 |
| **errorMessage** | `string` | No | Specifies the text that will be displayed if validation failed. This is optional but strongly recommended. If not provided, there will be NO error message displayed (the field will simply be visually highlighted as invalid). | 1.3 |
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

### Input validation

#### Determining if input is valid...

- If no value has been selected
	- If `"isRequired": false`
		- Valid!
	- Else
		- Invalid!
- Else if there's a value selected...
	- Valid!


#### Visual states for compact

Note that these comps are just examples. Each platform should mimick whatever style the platform has for representing these concepts.

##### Initial state with required cue

![Required cue](assets/Inputs/Input.ChoiceSet/Compact/InitialRequiredCue.png)

##### Invalid state without error message

Note that in this case, highlighting the box is enough since there's a visual difference (there wasn't a box before).

![Invalid without error](assets/Inputs/Input.ChoiceSet/Compact/InvalidWithoutError.png)

##### Invalid state with error message

Same as above except error message appears beneath like the other examples.


#### Visual states for expanded

##### Initial state with required cue

![Required cue](assets/Inputs/Input.ChoiceSet/Expanded/InitialWithRequiredCue.png)

##### Invalid state without error message

Note that in this case, highlighting the box is enough since there's a visual difference (there wasn't a box before).

![Invalid without error](assets/Inputs/Input.ChoiceSet/Expanded/InvalidWithoutError.png)

##### Invalid state with error message

Same as above except error message appears beneath like the other examples.


#### Visual states for multi-select expanded

See Input.Toggle, same idea