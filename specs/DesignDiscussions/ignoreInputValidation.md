# Allowing an Action.Submit to list the inputs it's associated with

Currently, Action.Submit always triggers input validation and always collects the values of (mostly) all inputs in the card. In some cases, that isn't practical, like in the case of a acard with a "Cancel" button where no input should be validated and there is no need for any input value to be sent to the backedn service.

## associatedInputs property
We will add a new `associatedInputs` property to Action.Submit to allow card authors to specify which inputs should be validated and collected on a per-action basis.

| Property | Type | Required | Description |
| --- | --- | --- | --- |
| associatedInputs | string. Allowed values are "auto" (default) and "none" | No | If not specified or set to "auto", the behavior of Action.Submit remains the same as it currently is: inputs are validated (which inputs get validated is determined in a way [documented here](https://docs.microsoft.com/en-us/adaptive-cards/authoring-cards/input-validation)) and their values sent to the backend service via the "data" property. If set to "none", no input is validated and no value is passed to the backend service. |

Note: in a later release, `associatedInputs` may accept an array of strings representing the specific list of input Ids that need to be validated and whose values should be passed to the backend service. This spec will be updated if/when this change happens.

**Example card:**
```json
{
    "type": "AdaptiveCard",
    "version": "1.3",
    "body": [
        {
            "type": "Input.Text",
            "label": "You must type some text",
            "isRequired": true
        }
    ],
    "actions": [
        {
            "type": "Action.Submit",
            "title": "Submit"
        },
        {
            "type": "Action.Submit",
            "title": "Cancel",
            "associatedInputs": "none"
        }
    ]
}
```
