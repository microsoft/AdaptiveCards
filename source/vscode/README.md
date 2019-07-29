# Adaptive Cards Viewer for Visual Studio Code

![extension](https://adaptivecards.io/content/vscode-extension.png)

## Usage 
When you are editing a .json file with a adaptive card $schema property you can view by using **Ctrl+Shift+V A**.

```javascript
{
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [

    ]
}
```


## Changes
* 2.0 
** Rewrote to use vscode webViews (loadHtml is deprecated)
** changed to always use latest published renderer 

* 1.x
** First version, used hardwired prerelease 0.5 
