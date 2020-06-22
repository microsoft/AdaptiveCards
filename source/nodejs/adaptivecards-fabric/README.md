# Adaptive Cards Fabric

This package "lights-up" the Adaptive Card renderer with [Office Fabric UI](https://developer.microsoft.com/en-us/fabric#/controls/web) input controls.

![Adaptive cards fabric animation](https://raw.githubusercontent.com/microsoft/AdaptiveCards/main/source/nodejs/adaptivecards-fabric/adaptivecards-fabric.gif)


## Extended Controls

| AdaptiveCard Element | Office Fabric UI Control |
|------------------------|--------------------------|
| Input.Date             |[DatePicker](https://developer.microsoft.com/en-us/fabric#/controls/web/datepicker)|
| Input.Number, Input.Text, Input.Time|[TextField](https://developer.microsoft.com/en-us/fabric#/controls/web/textfield)|
| Input.Toggle           |[Toggle](https://developer.microsoft.com/en-us/fabric#/controls/web/toggle)|
| Input.ChoiceSet (style:compact)|[Dropdown](https://developer.microsoft.com/en-us/fabric#/controls/web/dropdown)|
| Input.ChoiceSet (style:expanded, isMultiSelect:false)|[ChoiceGroup](https://developer.microsoft.com/en-us/fabric#/controls/web/choicegroup)|
| Input.ChoiceSet (style:expanded, isMultiSelect:true)|[Checkbox](https://developer.microsoft.com/en-us/fabric#/controls/web/checkbox)|
| Actions                |[Button](https://developer.microsoft.com/en-us/fabric#/controls/web/button)|

## Install

```console
npm install adaptivecards-fabric
```

**NOTE**: you must also install the necessary peer dependencies:

* adaptivecards
* office-ui-fabric-react
* react
* react-dom

## Usage

### Import the module

```js
// Import modules:
import * as AdaptiveCards from "adaptivecards";
import * as ACFabric from "adaptivecards-fabric";
```

### Render a card

```js
// Author a card
// In practice you'll probably get this from a service
// see http://adaptivecards.io/samples/ for inspiration
let card = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "Image",
            "url": "https://adaptivecards.io/content/adaptive-card-50.png"
        },
        {
            "type": "TextBlock",
            "text": "Hello **Adaptive Cards!**"
        }
    ],
    "actions": [
        {
            "type": "Action.OpenUrl",
            "title": "Learn more",
            "url": "https://adaptivecards.io"
        },
        {
            "type": "Action.OpenUrl",
            "title": "GitHub",
            "url": "https://github.com/Microsoft/AdaptiveCards"
        }
    ]
};

// Create an AdaptiveCard instance
let adaptiveCard = new AdaptiveCards.AdaptiveCard();

// Use Fabric controls when rendering Adaptive Cards
ACFabric.useFabricComponents();

// Set its hostConfig property unless you want to use the default Host Config
// Host Config defines the style and behavior of a card
adaptiveCard.hostConfig = new AdaptiveCards.HostConfig({
    fontFamily: "Segoe UI, Helvetica Neue, sans-serif"
    // More host config options
});

// Set the adaptive card's event handlers. onExecuteAction is invoked
// whenever an action is clicked in the card
adaptiveCard.onExecuteAction = function(action) { alert("Ow!"); }

// Parse the card payload
adaptiveCard.parse(card);

// Render the card to an HTML element:
let renderedCard = adaptiveCard.render();

// And finally insert it somewhere in your page:
document.body.appendChild(renderedCard);
```
