When Action.OpenUrl is invoked it will show the given url, either by launching it to an external web browser or showing in-situ 
with embedded web browser

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **"Action.OpenUrl"**| true |  |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **url** | string | true | Default (browser) url to use  |