# Adaptive Cards

Adaptive Cards are a new way for developers to exchange card content in a common and consistent way.

![adaptive-cards](http://adaptivecards.io/content/overview.jpg)

## Expressive cards, open framework, multiple platforms

Break outside the box of templated cards. Adaptive Cards let you describe your content as you see fit and deliver it beautifully wherever your customers are.

The simple open card format enables an ecosystem of shared tooling, seamless integration between producers and consumers, and native cross-platform performance on any device.

## Get Started

### Check out the [full documentation](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/htmlclient) for more

## Install

### Node

```console
npm install adaptivecards --save
```

### CDN

```html
<script src="https://unpkg.com/adaptivecards/dist/adaptivecards.js"></script>
```

## Breaking changes

|In version|Change description|
|--|--|
|Version 1.0|The standalone `renderCard()` helper function was removed as it was redundant with the class methods. Please use `adaptiveCard.render()` as described below.|
|All versions > 1.1|The `processMarkdown` event handler has been removed. Setting it will throw an exception that will halt your code. This is by design. Please update your code and set the `onProcessMarkdown(text, result)` event handler instead (see example below.)|

## Usage

### Import the module

```js
// Import the module:
import * as AdaptiveCards from "adaptivecards";

// Or require it:
var AdaptiveCards = require("adaptivecards");

// If you referenced the library from CDN, the global AdaptiveCards variable is already
// defined and can be used directly:
var adaptiveCard = new AdaptiveCards.AdaptiveCard();
```

### Render a card

```js
// Author a card
// In practice you'll probably get this from a service
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

// Create an AdaptiveCard instance
var adaptiveCard = new AdaptiveCards.AdaptiveCard();

// Set its hostConfig property unless you want to use the default Host Config
// Host Config defines the style and behavior of a card
adaptiveCard.hostConfig = new AdaptiveCards.HostConfig({
    fontFamily: "Segoe UI, Helvetica Neue, sans-serif"
    // More host config options
});

// Set the adaptive card's event handlers. onExecuteAction is invoked
// whenever an action is clicked in the card
adaptiveCard.onExecuteAction = function(action) { alert("Ow!"); }

// Markdown is supported via a third-party library. By default, Markdown-It will be used if it is
// loaded. To load Markdown-It, include this <script> tag in your HTML page:
//
//     <script type="text/javascript" src="https://unpkg.com/markdown-it/dist/markdown-it.js"></script>
//
// To provide your own Markdown processor and replace the default one, implement the onProcessMarkdown
// event handler:
//
//     AdaptiveCards.onProcessMarkdown = function(text, result) {
//        result.outputHtml = <your Markdown processing logic>;
//        result.didProcess = true;
//     }
//
// Do set result.didProcess to true, otherwise the library will consider the input text was not
// processed and will therefore be treated as plain text.
//
// IMPORTANT NOTE: When you provide your own Markdown processing logic, you are responsible for
// making sure the output HTML is safe. For example, you are responsible for removing <script>;
// failure to do so will make your application susceptible to script injection attacks. Note that
// most third-partyt Markdown libraries, such as Markdown-It, have HTML sanitation built-in.

// Parse the card payload
adaptiveCard.parse(card);

// Render the card to an HTML element:
var renderedCard = adaptiveCard.render();

// And finally insert it somewhere in your page:
document.body.appendChild(renderedCard);
```

## Webpack

If you don't want adaptivecards in your bundle, make sure the script is loaded and add the following the your `webpack.config.json`

```js
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
