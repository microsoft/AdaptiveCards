# microsoft-adaptivecards-scss-to-json
Allows creation of HostConfig json via SCSS

## Installation
```
npm install microsoft-adaptivecards-scss-to-json
```

## Usage
Start with an SCSS file that contains a map (a structured variable) with the shape of Adaptive Cards Host Config. Your SCSS file can exist with your other stylesheets and be driven by your own variables or mixins. See [test.css](test.scss) for an example.

You can create a map in SCSS from JSON with the companion tool "microsoft-adaptivecards-json-to-scss".

### In node
```
var scss2json = require('microsoft-adaptivecards-scss-to-json');
var hostConfig = scss2json('./test.scss');  //any entry point to your SCSS
console.log(hostConfig);    //now a json object
```

### Command line
This will output formatted JSON to stdout:

```
ac-scss2json ./test.scss
```


#### Command line options
The `-exec` option will output executable JavaScript with `AdaptiveCards.setHostConfig()` to stdout:

```
 ac-scss2json ./test.scss -exec
```

