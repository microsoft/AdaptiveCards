# microsoft-adaptivecards-json-to-scss
Allows creation of an SCSS map (a structured variable) via JSON

## Installation
```
npm install microsoft-adaptivecards-json-to-scss
```

## Usage
Start with a JSON variable of Adaptive Cards Host Config. See [the default](https://github.com/Microsoft/AdaptiveCards/blob/main/source/html/renderer/src/card-elements.ts#L2525) for an example.

```
var json2scss = require('microsoft-adaptivecards-json-to-scss');

var hostConfig = {
    supportsInteractivity: true,
    strongSeparation: {
        spacing: 40,
        lineThickness: 1,
        lineColor: "#EEEEEE"
    },
    fontFamily: "Segoe UI",
    .
    .
    .
};

var scss = json2scss(config);

console.log(scss);  //now a structured SCSS variable (a map)
```
