# Adaptive Cards

Adaptive Cards are a new way for developers to exchange card content in a common and consistent way.

![adaptive-cards](http://adaptivecards.io/content/overview.jpg)

## Expressive cards, open framework, multiple platforms

Break outside the box of templated cards. Adaptive Cards let you describe your content as you see fit and deliver it beautifully wherever your customers are.

The simple open card format enables an ecosystem of shared tooling, seamless integration between producers and consumers, and native cross-platorm performance on any device.

## Get Started

### Check out the [full documenation](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/htmlclient) for more

## Install

### Node

```console
npm install adaptivecards --save
```

### CDN

```html
<script type="text/javascript" src="https://unpkg.com/adaptivecards/dist/adaptivecards.js"></script>
```

## Usage

### Import the module

```js
// import the module
import * as AdaptiveCards from "adaptivecards";

// or require it
var AdaptiveCards = require("adaptivecards");

// or use the global variable if loaded from CDN
AdaptiveCards.renderCard(...);
```

## Render a card

```js
// author a card
// in practice you'll probably get this from a service
// see http://adaptivecards.io/samples/ for inspiration
var card = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "Image",
            "url": "http://adaptivecards.io/content/adaptive-card-50.png"
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
            "url": "http://adaptivecards.io"
        },
        {
            "type": "Action.OpenUrl",
            "title": "GitHub",
            "url": "http://github.com/Microsoft/AdaptiveCards"
        }
    ]
};

// define your render options
var renderOptions = {

    // a Host Config defines the style and behavior of all cards
    hostConfig: {
        "fontFamily": "Segoe UI, Helvetica Nue, sans-serif"
    },

    // the action handler is invoked when actions are pressed
    onExecuteAction: function (action) { alert("Ow!"); },

    // For markdown support you need a third-party library
    // E.g., to use markdown-it include the script and add the following:
    // <!-- <script type="text/javascript" src="https://unpkg.com/markdown-it/dist/markdown-it.js"></script> -->
    //processMarkdown: function (text) { return markdownit().render(text); }
};


// render the card to HTML
var renderedCard = AdaptiveCards.renderCard(card, renderOptions);

// now put it somewhere!
document.body.appendChild(renderedCard);
```

## Webpack

If you don't want adaptivecards in your bundle, make sure the script is loaded and add the following the your `webpack.config.json`

```json
module.exports = {
  ...
  externals: [
    { adaptivecards: { var: "AdaptiveCards" } }
  ]
};
```


## Learn more at http://adaptivecards.io
* [Documentation](http://adaptivecards.io/documentation/)
* [Schema Explorer](http://adaptivecards.io/explorer/)
* [Sample Cards](http://adaptivecards.io/samples/)
* [Interactive visualizer](http://adaptivecards.io/visualizer/)