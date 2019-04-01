# Adaptive Cards JavaScript packages

This directory contains all the JS packages for adaptive cards:

* `adaptivecards` - The renderer library
* `adaptivecards-controls` - A controls library useful for the designer
* `adaptivecards-designer` - The drag-drop designer component
* `adaptivecards-designer-app` - The designer app that consumes the designer component
* `adaptivecards-site` - The generated website that is currently hosted at adaptivecards.io
* `adaptivecards-visualizer` - The classic card Visualizer

## Bootstrap the repo

We use lerna to manage package linking and building. 

1. `cd source/nodejs`
2. `npm install`
3. `npx lerna bootstrap`

## Build

`npx lerna run build`

## Start the Designer or Visualizer

1. `cd adaptivecards-designer` (or `adaptivecards-visualizer`)
2. `npm start`

# Start the documentation site (http://adaptivecards.io)

1. `cd adaptivecards-site`
2. `npm install hexo-cli -g`
3. `hexo generate`
4. `hexo server`
5. `Open up the browser to point to localhost:[portnumber] printed after the command above returns under "Hexo is running at".`

## Adding a new package

1. `npx lerna add <new-package> --scope=<install-target>`