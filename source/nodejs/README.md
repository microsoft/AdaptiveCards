# Adaptive Cards JavaScript packages

This directory contains all the JS packages for adaptive cards:

* `adaptivecards` - The renderer library
* `adaptivecards-controls` - A controls library useful for the designer
* `adaptivecards-templating` - A JSON-to-JSON templating and data binding library for use with Adaptive Cards
* `adaptivecards-designer` - The drag-drop designer component
* `adaptivecards-designer-app` - The designer app that consumes the designer component
* `adaptivecards-site` - The generated website that is currently hosted at adaptivecards.io
* `adaptivecards-react` - React.js library

Removed JS packages:
* `adaptivecards-fabric` - A set of Fabric UI extensions for the Adaptive Cards JS renderer. This package has been deprecated. Please migrate to [`adaptivecards-fluentui`](https://www.npmjs.com/package/adaptivecards-fluentui). The source code is available in [21.09](https://github.com/microsoft/AdaptiveCards/releases/tag/21.09) or before releases.

## Bootstrap the repo

We use lerna to manage package linking and building. 

1. `cd source/nodejs`
2. `npm install`
3. `npx lerna bootstrap`

## Build

`npx lerna run build`

## Start the Designer

1. `cd adaptivecards-designer`
2. `npm start`
3. OR to test preview features: `npm run start:preview`

## Start the documentation site (http://adaptivecards.io)

1. `cd adaptivecards-site`
2. `npx lerna run release`
3. `npm start`
4. Open up the browser to point to: `localhost:[portnumber]` printed after the command above returns under "Hexo is running at".

## Adding a new package

1. `npx lerna add <new-package> --scope=<install-target>`

## Testing

The JS Renderer currently supports the following type of testing:

| Type | Project | Location |
| --- | --- | --- |
| Unit tests | adaptivecards/\_\_tests\_\_ | [Location](./adaptivecards/src/__tests__/)
| Unit tests | unit-tests | [Location](./tests/unit-tests) |
| UI tests | ui-tests | [Location](./tests/ui-tests) |

### To run adaptivecards/\_\_tests\_\_
1. `cd adaptivecards`
2. Build the project: `npm run build`
3. `npm test`

### To run unit-tests:
1. `cd tests/unit-tests`
2. `npm run build-and-test`

### To run ui tests
Pre-requisite 1: adaptivecards-ui-testapp must be executing

0.1 `cd adaptivecards-ui-testapp`

0.2 `npm run build`

0.3 `npm run start`

Pre-requisite 2: Web drivers must be installed, if working with edge it can be downloaded from [here](https://developer.microsoft.com/en-us/microsoft-edge/tools/webdriver/) 

1. `cd tests/ui-tests`
2. `npm run build`
3. `npm run test`