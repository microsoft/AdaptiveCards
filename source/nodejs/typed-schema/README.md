# Getting started

In a terminal, `cd` to this directory (which the readme is in)

For the first time (or whenever modifying package.json), run `npm install`

## Building

1. Make sure you've run `npm install` for the first time and whenever you modify package.json or change branches
1. `npm run build`


## Testing

1. Make sure you've built first
1. `npm run test`
1. Alternatively, you can run `npm run build-and-test`


## Generating schema for typed schema

1. Make sure you've built first
1. `npm run generate-schema`


## Generating schema for Adaptive Cards

1. Make sure you've built first
1. `npm run generate-adaptive-schema`
1. That outputs to `schemas/adaptive-card.json`, which the site will use as `current`


## Publishing new Adaptive Card schema

1. First follow instructions to generate the schema
1. Then create a new folder under schemas for the version. For example, if updating the 1.2.0 schema, create a folder in `schemas/1.2.1` (the last number is the revision, in case we happen to need to publish updates to a schema version). Then copy the generated schema into that folder and commit changes!