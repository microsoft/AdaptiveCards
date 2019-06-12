# Specs

## Updating specs

### Setup

For the best experience...

1. Install [Node.js](https://nodejs.org/en/)
1. Use Visual Studio Code
1. Install the [Run On Save extension by emeraldwalk](https://marketplace.visualstudio.com/items?itemName=emeraldwalk.RunOnSave)

### Updating the property table

The property table in the spec documents is **auto-generated**. Do NOT hand-edit it, as your changes will be lost!

Instead, open `schemas\adaptive-card.json` and update the **schema**. If you followed the instructions in [Setup](#setup), after you save your changes to the schema, the specs will be auto-updated in about 5-10 seconds.

![Spec auto-updating](assets/SpecAutoUpdate.gif)


### Re-naming an element

If you're re-naming an element type (not just a property, but an element that has its own spec file), here's the best way to do so (so that your changes are tracked as an update rather than delete and re-create).

1. Rename the file in `specs\elements`
1. Then, update the `schemas\adaptive-card.json`

This will ensure that the updates to the schema will be written to the existing spec, rather than creating a new spec file (and leaving your orphan file... it doesn't auto-delete).