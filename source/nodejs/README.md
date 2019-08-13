# Adaptive Cards JavaScript packages

This directory contains all the JS packages for adaptive cards:

* `adaptivecards` - The renderer library
* `adaptivecards-controls` - A controls library useful for the designer
* `adaptivecards-fabric` - A set of Fabric UI extensions for the Adaptive Cards JS renderer
* `adaptivecards-templating` - A JSON-to-JSON templating and data binding library for use with Adaptive Cards
* `adaptivecards-designer` - The drag-drop designer component
* `adaptivecards-designer-app` - The designer app that consumes the designer component
* `adaptivecards-site` - The generated website that is currently hosted at adaptivecards.io
* `adaptivecards-visualizer` - The classic card Visualizer

## Bootstrap the repo

We use lerna to manage package linking and building. 

1. `cd source/nodejs`
2. `npm install`
3. `npx lerna bootstrap`

## Initialize Telemetry

We use Microsoft 1DS as our telemetry provider.

This is 1DS documentation:
https://msasg.visualstudio.com/Shared%20Data/_git/1DS.JavaScript?path=%2Fskus%2FanalyticsWeb%2FREADME.md&version=GBmaster&fullScreen=true

1. `cd source/nodejs/adaptivecards`
2. `npm install -g vsts-npm-auth --registry https://registry.npmjs.com --always-auth false`
3. `vsts-npm-auth -config .npmrc`
4. `npm install @ms/1ds-analytics-web-js@2.0.4`


## Build

1. `cd source/nodejs`
2. `npx lerna run build`

## Start the Designer

1. `cd adaptivecards-designer`
2. `npm start`
3. OR to test preview features: `npm run start:preview`

# Start the documentation site (http://adaptivecards.io)

1. `cd adaptivecards-site`
2. `npx lerna run release`
3. `npm install hexo-cli -g`
5. `npm start`
6. Open up the browser to point to: `localhost:[portnumber]` printed after the command above returns under "Hexo is running at".

## Adding a new package

1. `npx lerna add <new-package> --scope=<install-target>`
