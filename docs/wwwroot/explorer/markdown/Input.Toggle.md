Input.Toggle collects a selection between two values, with **value** representing the current selected toggle value (either value1 or value2).

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.ToggleChoice"**| true |   |
| **style** | [ChoiceInputStyle](#choiceinputstyle) | false | Style for choice | 
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or Http action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **title** | string | true | The title for the toggle |
| **valueOn** | string | false | The value to use when toggle is selected (default:true)| 
| **valueOff** | string | false  | The value to use when toggle is not selected (default:false)| 
| **value** | string | false  | The value current value (default:false) | 