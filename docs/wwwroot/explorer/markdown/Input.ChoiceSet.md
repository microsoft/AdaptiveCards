Shows an array of choices the to the user.

* If **isMultiSelect** is false, then the result will be the single selected choice value
* If **isMultiSelect** is true, then the result will be an array of the selected choice values 
(non-selected choices will be omitted).

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true |  **"Input.ChoiceSet"** || **style** | [ChoiceInputStyle](#choiceinputstyle) | false | Style for choice | 
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or Http action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **style**| [ChoiceSetStyle](#choicesetstyle) | false | Hint of style of input |
| **isMultiSelect** | boolean | false | allow multiple choices to be selected (Default=false)|
| **choices** | Choice[] | true | the choice options |

#### Choice
Represents a single Choice

| Property | Type | Required | Description |
|---|---|---|---|
| **title** | string | true  | The title label for a choice|
| **value** | string | true  | the raw value for the choice|
| **isSelected** | bool |  false |is the choice selected |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
