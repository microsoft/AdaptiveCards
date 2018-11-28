## React-Native Adaptive-Cards

##  Adaptive Card
* Collection of `elements` and `actions`
* Element is the basic `building block` of card
* Element can be a `standalone` component OR can be a `container` that in turn holds collection of cards
* Main responsibilities of an element are,
  * **P**arsing
  * **R**endering
* `HostConfig` takes care of applying `default styles`. Custom styles (if any) can also be passed via HostConfig instance
* `Actions` area contains one or more action buttons



This project is for React-Native implementation of Adaptive cards based on https://github.com/Microsoft/AdaptiveCards.
A Quick overview of the folder structure.
* Components 
* Utils
* Styles


## src/components
This directory will contain mostly functional components.
The index.js file manages what is exported from that directory and it is the only thing we require from outside of that directory.

## src/utils
This directory takes care of keepin the Configuration out of the Code. 
This will hold anything that is used in multiple places throughout our app in one place.

## src/styles
This directory holds the global styles that will be used and applied across the components and app.
The purpose is that we will reuse a lot of the same styling(like Container, Themes,etc....).
 
## src/components/actions
This directory holds the collection of action buttons.

## src/components/containers
This directory holds the container elements, a superset of elements which also takes care of layout.

## src/components/elements
This directory holds all the static individual elements that will be used inside the containers

## src/components/inputs/
This directory holds all the input elements that will be used inside the containers

 


