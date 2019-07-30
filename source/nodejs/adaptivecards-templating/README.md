# Adaptive Card Data Binding and Templating Engine for JavaScript (Preview)

This library implements a JSON-to-JSON templating/data-binding engine. While it is designed to be used with Adaptive Cards, it is not dependent on Adaptive Cards and can therefore be used in many contexts and applications.

For more information about the data binding language implemented by this library, [please refer to GitHub](https://github.com/microsoft/AdaptiveCards/issues/2448)

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

<!-- Option 2: load a specific version (e.g, 0.1.0-alpha1) -->
<script src="https://unpkg.com/adaptivecards@0.1.0-alpha1/dist/adaptivecards-templating.min.js"></script>
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
            "text": "Hello {name}!"
        }
    ]
};

// Create a Template instamce from the template payload
var template = new ACData.Template(templatePayload);

// Create a data binding context, and set its $root property to the
// data object to bind the template to
var context = new ACData.EvaluationContext();
context.$root = {
    "name": "Adaptive Cards"
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

### Built-in functions

This library provides a set of built-in functions for use in data binding expressions. Note that any function parameter can itself be an expression.

#### substr
Extracts a substring from a string.

```typescript
substr(s: string, index: number, count: number)
```

|Parameter|Description|
|---|---|
|s|The input string|
|index|The index (zero based) where to start the extraction|
|count|The number of characters to extract|

#### JSON.parse
Converts a string representing JSON data into an object to make it possible to access its individual properties within an expression.

```typescript
JSON.parse(input: string)
```

|Parameter|Description|
|---|---|
|input|The input string. Must be a valid JSON payload.|

#### if
Returns a value that depends on whether a condition evaluates to true or false.

```typescript
if(condition: boolean, ifTrue: any, ifFalse: any)
```

|Parameter|Description|
|---|---|
|condition|The condition to evaluate.|
|ifTrue|The value to return if the condition evaluates to true.|
|ifFalse|The value to return if the condition evaluates to false.|

#### toUpper
Converts a string to its upper case representation.

```typescript
toUpper(input: string)
```

|Parameter|Description|
|---|---|
|input|The string to convert.|

#### toLower
Converts a string to its lower case representation.

```typescript
toLower(input: string)
```

|Parameter|Description|
|---|---|
|input|The string to convert.|

#### Date.format
Formats an ISO 8601 date/time string into a human redable date.

```typescript
Date.format(input: string, format: "long" | "short" | "compact")
```

|Parameter|Description|
|---|---|
|input|The string to format.|
|format|The format to use. Must be "short", "long" or "compact". Defaults to "compact"|

#### Time.format
Formats an ISO 8601 date/time string into a human redable time.

```typescript
Time.format(input: string)
```

|Parameter|Description|
|---|---|
|input|The string to format.|

### Custom functions
Applications can add support for custom functions by registering them with the engine. Custom functions open up additional possibilities and scenarios. To register a custom function:

```typescript
var template = new ACData.Template(templatePayload);

// Create a data binding context, and set its $root property to the
// data object to bind the template to
var context = new ACData.EvaluationContext();
context.$root = {
    "name": "Adaptive Cards"
};

// Register a custom "add" function that adds two numbers
context.registerFunction(
    "add",
    (a, b) => {
        if (typeof a === "number" && typeof b === "number") {
            return a + b
        }
        else {
            return undefined;
        }
    }
)

// "Expand" the template - this generates the final Adaptive Card,
// ready to render
var card = template.expand(context);

// Render the card
var adaptiveCard = new AdaptiveCards.AdaptiveCard();
adaptiveCard.parse(card);

document.getElementById('exampleDiv').appendChild(adaptiveCard.render());
```
