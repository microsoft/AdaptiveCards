Input.Number collects text from the user with a bias towards a number. 

>NOTE: Value collected may not be valid depending on the capabilities of the client.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Input.Number"** |
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or Http action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **placeholder** | string | false | initial text descripting the input desired |
| **value** | number | false | The initial value for a field |
| **min** | number | false | Minimum number (Not all clients will be able to honor this)|
| **max** | number | false | Maximum number (Not all clients will be able to honor this)|
