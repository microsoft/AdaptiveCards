# React.js Adaptive Cards component

## Install and import the module

### Node

```console
npm install react adaptivecards-react --save
```

```js
// Import the module:
import * as AdaptiveCard from "adaptivecards-react";

// OR require it:
var AdaptiveCard = require("adaptivecards-react");
```

```tsx
import { AdaptiveCard } from "adaptivecards-react";
```

### Usage

- Basic usage:

```js
var card = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "Here is a ninja cat"
        },
        {
            "type": "TextBlock",
            "text": "Here is another ninja cat"
        },
        {
            "type": "Image",
            "url": "http://adaptivecards.io/content/cats/1.png"
        }
    ]
};

var hostConfig = {
    fontFamily: "Segoe UI, Helvetica Neue, sans-serif"
};

<AdaptiveCard payload={card} hostConfig={hostConfig} />
```


- react [context](https://reactjs.org/docs/context.html):

Context provides a way to pass data through the component tree without having to pass props down manually at every level.

```js
import {ProvidesHostConfigContext, AdaptiveCardUsingHostConfigContext } from "adaptivecards-react";

      <ProvidesHostConfigContext hostConfig={hostConfig} >
        <...>
            <AdaptiveCardUsingHostConfigContext payload={card}/>
        </...>    
      </ProvidesHostConfigContext>
```
