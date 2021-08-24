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

### Usage

Basic usage:

```js
<AdaptiveCard
    payload={card}
/>
```

Non-interactible:

```js
<AdaptiveCardView
    payload={card}
    style={{ pointerEvents: 'none' }}
/>
```
