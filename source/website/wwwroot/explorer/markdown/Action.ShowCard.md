Action.ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| **Action.ShowCard"** | true | |
| **title** | string | true | Label for button or link that represents this action |
| **speak** | [Speak](/Microsoft/AdaptiveCards/blob/master/docs/SpeechAndAdvancedCustomization.md) | false | Specifies what should be spoken for this entire element.  This is simple text or SSML fragment |
| **card** | [Container](#container) | true |inline container  defining the card to be shown when this action is invoked. It is up to client to decide how to show this inline card. |