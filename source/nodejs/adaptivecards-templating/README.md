# Adaptive Card Templating for JavaScript

This library implements a JSON-to-JSON templating/data-binding engine. While it is designed to be used with Adaptive Cards, it is not dependent on Adaptive Cards and can therefore be used in many contexts and applications.

[Learn more about Adaptive Card Templating](https://aka.ms/actemplating)

## Install and import the module

### Node

```console
npm install adaptivecards-templating --save
```

```js
// Import the module:
import * as ACData from "adaptivecards-templating";

// OR require it:
var ACData = require("adaptivecards-templating");
```

### CDN

The unpkg.com CDN makes it easy to load the script in an  browser. 

The latest release will keep you up to date with features and fixes, but may have breaking changes over time. For maximum stability you should use a specific version.

* `adaptivecards-templating.js` - non-minified, useful for dev
* `adaptivecards-templating.min.js` - minified version, best for production

```html
<!-- Option 1: always load the latest release -->
<script src="https://unpkg.com/adaptivecards-templating/dist/adaptivecards-templating.min.js"></script>

<!-- Option 2: load a specific version (e.g, 1.0-rc1) -->
<script src="https://unpkg.com/adaptivecards-templating@<VERSION>/dist/adaptivecards-templating.min.js"></script>
```

Once the library is loaded, the global `ACData` variable is defined and ready to be used.

## Usage

### Hello World example

Here is a simplistic "Hello World" example on how to use the library to generate an Adaptive Card using a template bound to a data object. Note this example requires the [adaptivecards](https://www.npmjs.com/package/adaptivecards) package.

```typescript
import * as ACData from "adaptivecards-templating";
import * as AdaptiveCards from "adaptivecards";

// Define a template payload
var templatePayload = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "Hello ${name}!"
        }
    ]
};

// Create a Template instance from the template payload
var template = new ACData.Template(templatePayload);

// Create a data binding context, and set its $root property to the
// data object to bind the template to
var context: ACData.IEvaluationContext = {
    $root = {
        "name": "Adaptive Cards"
    }
};

// "Expand" the template - this generates the final Adaptive Card,
// ready to render
var card = template.expand(context);

// Render the card
var adaptiveCard = new AdaptiveCards.AdaptiveCard();
adaptiveCard.parse(card);

document.getElementById('exampleDiv').appendChild(adaptiveCard.render());
```

This example is implemented in the **example.html** file.

### Functions

#### Built-in functions

For a list of and documentation on built-in functions, please refer to the [AdaptiveExpressions documentation](https://aka.ms/adaptive-expressions).

#### Custom functions

```typescript
// Coming soon...
```