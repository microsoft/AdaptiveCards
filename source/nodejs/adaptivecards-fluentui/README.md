# Adaptive Cards Fluent UI controls

This package "lights-up" the Adaptive Card renderer with [Microsoft's Fluent UI controls](https://developer.microsoft.com/en-us/fluentui#/).

![Adaptive cards fluent animation](https://raw.githubusercontent.com/microsoft/AdaptiveCards/main/source/nodejs/adaptivecards-fluent/adaptivecards-fluent.gif)


## Extended Controls

| AdaptiveCard Element                                  | Fluent UI Control                                                                     |
| ----------------------------------------------------- | ------------------------------------------------------------------------------------- |
| Input.Date                                            | [DatePicker](https://developer.microsoft.com/en-us/fluentui#/controls/web/datepicker)   |
| Input.Number, Input.Text, Input.Time                  | [TextField](https://developer.microsoft.com/en-us/fluentui#/controls/web/textfield)     |
| Input.Toggle                                          | [Toggle](https://developer.microsoft.com/en-us/fluentui#/controls/web/toggle)           |
| Input.ChoiceSet (style:compact)                       | [Dropdown](https://developer.microsoft.com/en-us/fluentui#/controls/web/dropdown)       |
| Input.ChoiceSet (style:expanded, isMultiSelect:false) | [ChoiceGroup](https://developer.microsoft.com/en-us/fluentui#/controls/web/choicegroup) |
| Input.ChoiceSet (style:expanded, isMultiSelect:true)  | [Checkbox](https://developer.microsoft.com/en-us/fluentui#/controls/web/checkbox)       |
| Actions                                               | [Button](https://developer.microsoft.com/en-us/fluentui#/controls/web/button)           |

## Install

```console
npm install adaptivecards-fluentui
```

**IMPORTANT**: you must also install the necessary peer dependencies:

* adaptivecards
* @fluentui/react
* react
* react-dom

## Usage

### Import the module

```js
// Import modules:
import * as AdaptiveCards from "adaptivecards";
import * as ACFluentUI from "adaptivecards-fluentui";
```

### Render a card

```js
// Author a card
// In practice you'll probably get this from a service
// see http://adaptivecards.io/samples/ for inspiration
let card = {
    "type": "AdaptiveCard",
    "version": "1.3",
    "body": [
        {
            "type": "Image",
            "url": "https://adaptivecards.io/content/adaptive-card-50.png"
        },
        {
            "type": "TextBlock",
            "text": "Hello **Adaptive Cards!**"
        },
		{
			"type": "Input.Text",
			"placeholder": "Enter your name",
			"label": "Name",
			"isRequired": false,
			"style": "text",
			"id": "Name"
		}
    ],
    "actions": [
        {
            "type": "Action.OpenUrl",
            "title": "Learn more",
            "url": "https://adaptivecards.io"
        },
        {
            "type": "Action.Submit",
            "title": "Submit"
        }
    ]
};

// Create an AdaptiveCard instance
let adaptiveCard = new AdaptiveCards.AdaptiveCard();

// Use Fluent UI controls when rendering Adaptive Cards
ACFluentUI.useFluentUI();

// Set its hostConfig property unless you want to use the default Host Config
// Host Config defines the style and behavior of a card
adaptiveCard.hostConfig = new AdaptiveCards.HostConfig({
    fontFamily: "Segoe UI, Helvetica Neue, sans-serif"
    // More host config options
});

// Set the adaptive card's event handlers. onExecuteAction is invoked
// whenever an action is clicked in the card
adaptiveCard.onExecuteAction = function (action) {
	var message = "Action executed\n";
	message += "    Title: " + action.title + "\n";

	if (action instanceof AdaptiveCards.OpenUrlAction) {
		message += "    Type: OpenUrl\n";
		message += "    Url: " + action.url + "\n";
	}
	else if (action instanceof AdaptiveCards.SubmitAction) {
		message += "    Type: Submit\n";
		message += "    Data: " + JSON.stringify(action.data);
	}
	else {
		message += "    Type: <unknown>";
	}

	alert(message);
}

// Parse the card payload
adaptiveCard.parse(card);

// Render the card to an HTML element:
let renderedCard = adaptiveCard.render();

// And finally insert it somewhere in your page:
document.body.appendChild(renderedCard);
```
