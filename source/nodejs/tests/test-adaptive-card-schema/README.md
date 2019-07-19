# Getting started

In a terminal, `cd` to this directory (which the readme is in)

For the first time (or whenever modifying package.json), run `npm install`

## Building

1. Make sure you've run `npm install` for the first time and whenever you modify package.json or change branches
1. `npm run build`


## Testing

1. Make sure you've built first
1. Make sure you've also generated the Adaptive schema first, see `ac-typed-schema` for instructions
1. `npm run test`
1. Alternatively, you can run `npm run build-and-test`