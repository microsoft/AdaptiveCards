# Allowing actions to bypass input validation

Currently, Action.Submit always triggers input validation. In some cases, that isn't practical, like in the case of a acard with a "Cancel" button.

## ignoreInputValidation property
JS currently implements (although it is undocumented) an `Action.Submit.ignoreInputValidation` boolean property. When this property is set to true, clicking the button doesn't trigger input validation and the `onExecuteAction` event is always triggered.

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
            "ignoreInputValidation": true
        }
    ]
}
```