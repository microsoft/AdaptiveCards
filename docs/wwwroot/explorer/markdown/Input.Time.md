Input.Time collects text from the user in form of a time of day.

>NOTE: Clients may not be able to validate that the value of this is a valid time expression.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Input.Time"** | true | |
| **id** | string | true  | Id for the value (will be used to identify collected input when SUBMIT is clicked) |
| **isRequired** | bool | false | The input must have a value for it to be part of a Submit or Http action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **placeholder** | string | false | initial text descripting the input desired |
| **value** | string | false | The initial value for a field |
| **min** | string | false | Minimum time (Not all clients will be able to honor this)|
| **max** | string  | false | Maximum time (Not all clients will be able to honor this)|