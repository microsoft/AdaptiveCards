# microsoft-adaptivecards-scss-to-json
Allows creation of HostConfig json via SCSS

## Installation
```
npm install microsoft-adaptivecards-scss-to-json
```

## Usage
Start with an SCSS file that contains a map (a structured variable) with the shape of Adaptive Cards Host Config. Your SCSS file can exist with your other stylesheets and be driven by your own variables or mixins. See [sample.scss](https://github.com/Microsoft/AdaptiveCards/blob/master/source/tools/hostConfig/scss-to-json/sample.scss) for an example.

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
ac-scss2json ./sample.scss
```


#### Command line options

##### Executable JavaScript

The `--exec` option will output executable JavaScript with `AdaptiveCards.setHostConfig()` to stdout:

```
 ac-scss2json ./sample.scss --exec
```

##### JSON embedded in CSS content

The `--css` option will output CSS containing the JSON in CSS content to stdout:

```
 ac-scss2json ./sample.scss --css
```

The `--css-append <filename>` option will append CSS containing the JSON in CSS content to an existing file:

```
 ac-scss2json ./sample.scss --css-append yourExistingFile.css
```

##### Example: reading JSON from the CSS content at runtime in the browser

```
var element = document.createElement('a');  //any element tagname will work
element.id = 'ac-hostConfig';
var style = window.getComputedStyle(element);
var content = style.content;
var json = content.slice(1, -1).replace(/\\"/g, '"');
var hostConfig = JSON.parse(json);
AdaptiveCards.setHostConfig(hostConfig);
```

