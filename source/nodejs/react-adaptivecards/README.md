# React.js Adaptive Cards component

## Install and import the module

### Node

```console
npm install react react-adaptivecards --save
```

```js
// Import the module:
import * as AdaptiveCard from "react-adaptivecards";

// OR require it:
var AdaptiveCard = require("react-adaptivecards");
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