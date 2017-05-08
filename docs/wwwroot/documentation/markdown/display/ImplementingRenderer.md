# Implementing a Renderer

The following guidance describes how each of our renderers are implemented, and how to follow the same concepts to implement a renderer on any UI platform.

## Versioning
Your renderer should implement a particular version of the schema. If you encounter a `minRequiredVersion` property in the `AdaptiveCard` that is higher than your supported version, you should render the `fallbackText` instead.

## Rendering CardElements

An AdaptiveCard consists of a `body` and `actions`

The `body` is a collection of `CardElement`s that you will enumerate and render. Each element is a "block level" element and should take up the width of it's container.

Each `CardElement` from the  [Schema](../Schema.md)

### TextBlock

A TextBlock will should take up a single line unless the `wrap` property is `true`

### Inputs

Inputs should render with the highest fidelity possible. For example, an `Input.Date` would ideally offer a date picker to a user, but if this isn't possible on your UI stack then you should always fallback to rendering a standard text input box.

## Styling

TODO: List the styles that should be supported on each platform

## Actions

* Action.Submit
* Action.Http
* Action.ShowCard
* Action.OpenUrl

## Events

A Renderer should expose certain events to allow the container app to handle as they see fit.

### ActionExecuted
Raise this event when an action is tapped. You should pass along the properties that the action contained.

## Data binding
For a submit action you should gather all inputs on the card and retrieve their values.

Regex to get input values `/\{{2}([a-z0-9_$@]+).value\}{2}/gi;`

### RenderUnknownType
Raise this event when an unknown `type` is encountered, allowing the host to handle the event and return UI as they see fit.


# Rendering unknown elements
A renderer should be ready to handle unknown types, and continue processing the rest of the payload. 
