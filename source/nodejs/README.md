# Install and Build

This folder contains the HTML Renderer and the Visualizer tool.

They are built independently, so to make local testing easier, you can use `npm link` below

## To build the HTML Renderer

1. `cd adaptivecards`
1. `npm install`
1. `npm link` (allows the visualizer to take a local symlink dep to this package)
1. `npm run build` (or `npm run watch`)

## To build the Visualizer tool

1. `cd ../adaptivecards-visualizer`
1. `npm install`
1. (Optional) To use the local package of adaptivecards, run `npm link adaptivecards` (creates the symlink to the renderer). Otherwise, you can skip this step since the latest public release is already installed.
1. `npm run build`

## To start a local web server
1. `npm start`





# NOT WORKING YET
1. `npm install -g npm-workspace`
1. `npm-workspace install`
1. `cd visualizer`
1. `npm run build`
1. `npm start`
