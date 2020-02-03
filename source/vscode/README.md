# Adaptive Cards Viewer for Visual Studio Code

![extension](http://adaptivecards.io/content/vscode-extension.png)

## Usage 
When you are editing a .json file with a adaptive card $schema property you can view by using **Ctrl+Shift+V A**.

```javascript
{
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "0.5",
    "body": [

    ]
}
```


### Options
The following Visual Studio Code setting is available for the AdaptiveCards Viewer.  This can be set in `User Settings` or `Workspace Settings`.

```javascript
{

    // Open or not open the preview screen automatically
    "adaptivecardsviewer.enableautopreview": true,
}
```
