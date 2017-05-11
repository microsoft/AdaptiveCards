Input.Text collects text from the user

| Property | Type | Required | Description |
|---|---|---|---|
| **type**|  **"Input.Text"**| true | |
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or Http action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **value** | string | false | The initial value for a field |
| **placeholder** | string | false | initial text descripting the input desired |
| **style**| [TextInputStyle](#textinputstyle) | false | Hint of style of input, if client doesn't support the style it will become simple text input |
| **isMultiline** | bool | false | true to collect multiple lines of text (default is false) |
| **maxLength** | number | false | hint of maximum length characters to collect *(may be ignored by some clients)* |
| **isMultiline** | boolean | false | Do you want to allow multiple lines of input |