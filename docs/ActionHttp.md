Action.Http represents the properties needed to do an Http request. All input properties are available for use via 
data binding.  Properties can be data bound to the Uri and Body properties, allowing you to send a request
to an arbitrary url.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"HttpAction"** |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **url** | string | true | url to use (can have binding information) |
| **method** | string | true | Http method (Example: POST) |
| **headers** | object | false | Object which represents headers Example: { "content-type":"application/json" }  |
| **body** | string | false | content to post (can have binding information) |
