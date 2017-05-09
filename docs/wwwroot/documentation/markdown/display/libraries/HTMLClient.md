# HTML Client Library
This is a HTML renderer which works in the browser agains the DOM.

## Add a renderer
This is available as a NPM package. 
```
npm install adaptive-cards
```

## Create an instance of your renderer
The next step is to create an instance of the renderer library. 
```javascript
var ajaxRenderer = new AdaptiveCards.AdaptiveCard();
```

## Hook up action callback
To hook up action events you register an onExecuteAction callback

```javascript
AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
    ...
};
```

## Render a card
To render a card, you instantiate an AdaptiveCard, parse the card object and call render() to get a HtmlElement that can be inserted
into a div.

```javascript
function renderCard(targetDiv, cardObject) {
    var htmlElement = new AdaptiveCards.AdaptiveCard()
        .parse(cardObject)
        .render();
    var div = document.getElementById(targetDiv).appendChild(htmlElement);
}
```

## Example
Here is an example from the ajax renderer to give you a feel for how this works:

```javascript
var adaptiveCard = new AdaptiveCards.AdaptiveCard();
adaptiveCard.parse(card);
var renderedCard = adaptiveCard.render();
var div = document.getElementById(targetDiv).appendChild(renderedCard);
...
AdaptiveCards.AdaptiveCard.onExecuteAction = function (action) {
    var message = "Action executed\n";
    message += "    Title: " + action.title + "\n";

    if (action instanceof AdaptiveCards.OpenUrlAction) {
        message += "    Type: OpenUrl\n";
        message += "    Url: " + action.url + "\n";
    }
    else if (action instanceof AdaptiveCards.SubmitAction) {
        message += "    Type: Submit";
        message += "    Data: " + JSON.stringify(action.data);
    }
    else if (action instanceof AdaptiveCards.HttpAction) {
        var httpAction = action;
        message += "    Type: Http\n";
        message += "    Url: " + httpAction.url + "\n";
        message += "    Method: " + httpAction.method + "\n";
        message += "    Headers:\n";

        for (var i = 0; i < httpAction.headers.length; i++) {
            message += "        " + httpAction.headers[i].name + ": " + httpAction.headers[i].value + "\n";
        }
        message += "    Body: " + httpAction.body + "\n";
    }
    else {
        message += "    Type: <unknown>";
    }

    alert(message);
}
```

## Customization

### HostConfig 
To customize the renderer you provide an instance of the HostConfig object. (See [Host Config Schema](/documentation/#display-hostconfigschema) for the full description.)

Example:
```javascript
AdaptiveCards.setHostConfig({
    "supportsInteractivity": true,
    "strongSeparation": {
        "spacing": 10,
        "lineThickness": 1,
        "lineColor": "#EEEEEE"
    },
    "fontFamily": "Segoe UI",
    "fontSizes": {
        "small": 12,
        "normal": 14,
        "medium": 17,
        "large": 21,
        "extraLarge": 26
    },
    "fontWeights": {
        "lighter": 200,
        "normal": 400,
        "bolder": 600
    },
    "colors": {
        "dark": {
            "normal": "#333333",
            "subtle": "#EE333333"
        },
        "light": {
            "normal": "#FFFFFF",
            "subtle": "#88FFFFFF"
        },
        "accent": {
            "normal": "#2E89FC",
            "subtle": "#882E89FC"
        },
        "attention": {
            "normal": "#5D60B3",
            "subtle": "#DD5D60B3"
        },
        "good": {
            "normal": "#00a000",
            "subtle": "#DD00a000"
        },
        "warning": {
            "normal": "#c00000",
            "subtle": "#DDc00000"
        }
    },
    "imageSizes": {
        "small": 40,
        "medium": 80,
        "large": 160
    },
    "actions": {
        "maxActions": 5,
        "separation": {
            "spacing": 10
        },
        "buttonSpacing": 20,
        "stretch": false,
        "showCard": {
            "actionMode": "inlineEdgeToEdge",
            "inlineCardSpacing": 16,
            "backgroundColor": "#08000000",
            "padding": {
                "top": 16,
                "right": 16,
                "bottom": 16,
                "left": 16
            }
        },
        "actionsOrientation": "horizontal",
        "actionAlignment": "left"
    },
    "adaptiveCard": {
        "backgroundColor": "#fafafa",
        "padding": {
            "left": 10,
            "top": 10,
            "right": 10,
            "bottom": 10
        }
    },
    "container": {
        "separation": {
            "spacing": 10
        },
        "normal": {},
        "emphasis": {
            "backgroundColor": "#cccccc",
            "borderColor": "#aaaaaa",
            "borderThickness": {
                "top": 1,
                "right": 1,
                "bottom": 1,
                "left": 1
            },
            "padding": {
                "top": 10,
                "right": 10,
                "bottom": 10,
                "left": 10
            }
        }
    },
    "textBlock": {
        "color": "dark",
        "separations": {
            "small": {
                "spacing": 10
            },
            "normal": {
                "spacing": 10
            },
            "medium": {
                "spacing": 10
            },
            "large": {
                "spacing": 10
            },
            "extraLarge": {
                "spacing": 10
            }
        }
    },
    "image": {
        "size": "medium",
        "separation": {
            "spacing": 10
        }
    },
    "imageSet": {
        "imageSize": "medium",
        "separation": {
            "spacing": 10
        }
    },
    "factSet": {
        "separation": {
            "spacing": 10
        },
        "title": {
            "color": "dark",
            "size": "normal",
            "isSubtle": false,
            "weight": "bolder"
        },
        "value": {
            "color": "dark",
            "size": "normal",
            "isSubtle": false,
            "weight": "normal"
        },
        "spacing": 10
    },
    "input": {
        "separation": {
            "spacing": 10
        }
    },
    "columnSet": {
        "separation": {
            "spacing": 10
        }
    },
    "column": {
        "separation": {
            "spacing": 10
        }
    }
});
```

When you register it you are setting the global host config for all rendering actions you perform with the library.

### Changing per element rendering
The ajax renderer has a callback registry for actions (AdaptiveCard.actionTypeRegistry) and elements(AdaptiveCard.elementTypeRegistry) which all you to set a function which is called to perform the
rendering on a per element basis.

AdaptiveCard.elementTypeRegistry

Let's say you want to override the rendering of a Input.Date element.  You would do something like this:
```javascript
AdaptiveCard.elementTypeRegistry.registerType("Input.Date", () => { return new DateInput(); }); 
```

And to override an action
```javascript
AdaptiveCard.actionTypeRegistry.registerType("Action.OpenUrl", () => { return new OpenUrlAction(); });  
```

### UI Framework styling
You can further style using standard CSS to change the behavior of the HTML.

style names that are used for each element.  

| style | use |
|---|---|
| ac-container | containers |
| ac-selectable  | things which are selectable |
| ac-image | image |
| .ac-pushButton | actions rendered like buttons |
|.ac-linkButton  | actions rendered like links |
|.ac-input | input controls|
|.ac-textInput| text input |
|.ac-multiline | multiline text input |
| .ac-numberInput | number input|
| .ac-dateInput | date input|
| .ac-timeInput | time input |
| .ac-multichoiceInput | multichoice input|

Here is a sample CSS which styles content for Tems style
```css
.ac-image.ac-selectable {
  cursor: pointer;
}

.ac-container.ac-selectable {
  padding: 5px;
}

.ac-container.ac-selectable:hover {
  background-color: rgba(0, 0, 0, 0.1);
}

.ac-container.ac-selectable:active {
  background-color: rgba(0, 0, 0, 0.15);
}

.ac-pushButton {
  font-family: "Segoe UI", sans-serif;
  font-size: 14px;
  font-weight: 600;
  overflow: hidden;
  text-overflow: ellipsis;
  border: none;
  padding: 4px 10px 5px 10px;
  text-align: center;
  vertical-align: middle;
  cursor: default;
  background-color: #0078D7;
  color: white;
  -webkit-user-select: none;
     -moz-user-select: none;
      -ms-user-select: none;
          user-select: none;
}

.ac-pushButton:hover {
  background-color: #005A9E;
}

.ac-pushButton:active {
  background-color: #004D84;
}

.ac-linkButton {
  font-family: "Segoe UI", sans-serif;
  font-size: 14px;
  font-weight: 600;
  overflow: hidden;
  text-overflow: ellipsis;
  cursor: default;
  border: 2px solid #5D60B3;
  padding: 4px 10px 5px 10px;
  color: #5D60B3;
  background-color: white;
  -webkit-user-select: none;
     -moz-user-select: none;
      -ms-user-select: none;
          user-select: none;
}

.ac-linkButton:hover {
  background-color: #5D60B3;
  color: white;
}

.ac-linkButton:active {
  background-color: #4F5399;
  color: white;
}

/*
    Other styles that can be specified:
        .ac-linkButton.ac-expanded
        .ac-linkButton.ac-expanded:hover
        .ac-linkButton.ac-expanded:active
    */
.ac-linkButton {
  text-align: center;
  vertical-align: middle;
}

.ac-input {
  font-family: "Segoe UI", sans-serif;
  font-size: 14px;
  color: black;
}

.ac-input.ac-textInput {
  height: 30px;
  resize: none;
}

.ac-input.ac-textInput.ac-multiline {
  height: 72px;
}

.ac-input.ac-textInput, .ac-input.ac-numberInput, .ac-input.ac-dateInput, .ac-input.ac-timeInput, .ac-input.ac-multichoiceInput {
  border: 1px solid #DDDDDD;
  padding: 4px 8px 4px 8px;
}
```

## Resources
* [Libraries](/documentation/#display-libraries) 
* [Implementing a renderer](/documentation/#disply-implementingrenderer) 
* [Customizing a renderer](/documentation/#display-customizingrenderer) 


