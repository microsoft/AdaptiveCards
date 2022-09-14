# Carousel support for Adaptive Cards

To help drive the discussion and requirements around the carousel element, @rebecch and I sat down to go over how to meet our goals with a narrow but expandable set of schema changes. 

We propose that carousels are a special type of Adaptive Card rather than an element. This greatly simplifies the design from both a schema perspective and a rendering perspective. In particular:
* **We don't have to worry about nesting carousel elements.**
  * It's unclear how we could have a rational display of *N* nested carousels.
* **We don't have to worry about the interplay of carousel with elements that have layout implications.**
  * We don't have to think about `bleed`
  * We don't have to worry about how container styles or rtl apply
* **We can ignore `Action.ToggleVisibility`.**

## Spec By Example

It's probably best to lead with a proposed sample carousel card...

```json
{
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "type": "AdaptiveCard",
  "version": "1.6",
  "TBD": {
    "type": "carousel",
    "timer": "5000ms",
    "someOtherCarouselProperty": true
  },
  "body": [
    {
      "type": "CarouselPage",
      "id": "firstCarouselPage",
      "selectAction": {
        "type": "Action.OpenUrl",
        "title": "Click for more information about the first carousel page!",
        "url": "https://adaptivecards.io/"
      },
      "items": [
        {
          "type": "TextBlock",
          "weight": "bolder",
          "size": "large",
          "text": "This is the first carousel page, and it's *awesome*!"
        },
        {
          "type": "Container",
          "items": [
              {}
          ]
        }
      ]
    },
    {
      "type": "CarouselPage",
      "id": "theSecondCarouselPage",
      "items": [
        {
          "type": "TextBlock",
          "text": "Welcome to page 2!"
        }
      ]
    },
    {
      "type": "CarouselPage",
      "id": "last-carousel-page",
      "items": [
        {
          "type": "Image",
          "url": "https://adaptivecards.io/content/cats/3.png",
          "altText": "That's a cool cat!"
        }
      ]
    }
  ],
  "actions": [
    {
      "type": "Action.Execute",
      "verb": "actOnPage",
      "title": "Do action with page!"
    }
  ]
}
```

So here we have a sample carousel card. You'll probably notice the ominously-named `TBD` property right away -- we haven't come up with a name for it yet. At any rate, this property is an object containing a `type` property describing what type of card this is. Other properties in this object can be provided to configure behaviors of this type of card (in this example, the timer to use for automatically flipping through the items in a carousel).

You'll probably also notice the new `CarouselPage` element. It acts pretty similarly to a `Container`, but with some differences:
* No `style` (or at least, we don't have a reason to have `style` here yet)
* No `bleed`
* We don't allow every element type within a `CarouselPage`, only the subset we decide on (see following sections for more details)

Having this new element also has the advantage of allowing us to reuse it later should we decide to promote the idea of `Carousel` as a regular page element (a `Carousel` would be a collection of `CarouselPage`s in this regime, though we'd need to decide how to reconcile `TBD` against per-`Carousel` settings).

This sample also has a page-wide `Action.Execute`. When the user clicks this action (rendered as a button below the ⚬●⚬⚬ control), the host will receive the standard callback. The `id` of the currently-visible page should be exposed as a property on the `Action` the callback provides (we may also want to provide positional properties as well, but I'm not sure if they're needed).

It's worth noting that we think we *should* allow `ActionSet` elements inside a `CarouselPage`, but they should be restricted to the same actions as the toplevel `actions` property.

Another thing to note is that this implies the existence of a special carousel card inside of an `Action.ShowCard`, which we think is probably okay, but we should talk it through a bit more. If we do allow it, input gathering should happen as it currently does -- namely, the parent card's inputs are supplied if the `Action.ShowCard` has an `Action.Submit` or `Action.Execute` invoked from within it.

## Disallowed Elements

In order to meet our schedule, we need to avoid some common pain points that would require extra dev/spec time that might not necessarily lead to a better card author or AC host experience. In particular, we believe that the following scenarios/experiences should be explicitly not supported for v1:

* ShowCard
* ToggleVisibility
* Input Elements
  * Input elements **should not** be allowed in carousels. Decisions about input gathering and validation are likely to be difficult to get right, tricky to code, and even trickier to retract later on. Should we choose to open this functionality up later, we certainly can.

## Supported Elements

All elements not mentioned above are allowed inside a carousel.

## Header
![image](https://user-images.githubusercontent.com/4112696/183519757-156a18a9-73e7-47d9-8e00-ad84d0070f99.png)

Header is an optional property whose value is an array of TextBlocks. Header is positioned above the carousel page, and the position of the text is static.
When carousel page transitions to a new page, the text shall remain. Each subsequent `TextBlock` is laid below a previous `TextBlock` as `TextBlock`s in `body` of `AdaptiveCards` would be rendered.


Header can be used for purely decorative purpose as well as a11y header.
Author of card can designate a TextBlock in the array to be a11y header by setting its `style` property to `heading`. 
Renderers shall apply a11y heading role according to their respective a11y options. 

Header supports an implied type. The implied type of `header` is `TextBlock`.
As a result, author can shortcircuits specifying the type. When this happens, renderers shall assume the type `TextBlock` and renders the content accordingly.
Implied type shall be remained `TextBlock` even when additional types are added to the list of supported types in the future.
```
{
    "type": "Carousel",
    "header": [
        {
            "text": "cat picture",
            "isSubtle": true,
            "size": "small"
        },
        {
            "text": "Top Cat Picture",
            "weight": "bolder",
            "style": "heading,
            "size": "large"
        },
        {
            "text": "Washington",
            "isSubtle": true
        }
    ],
    "pages": 
    ...
}
```

## Spacing
Controls the amount of spacing between `header` and carousel page. Same enumeration value of AdaptiveCard element property `Spacing` is applied.
`spacing` has no effect if either of header and spacing is missing.

## HostConfig Options

* Max number of `CarouselPage`s
* Minimum timer restriction
* Do we need host config theming? We're leaning towards leaving this for native styling via CSS.

## Open Issues

- [ ] Should custom elements (card elements **and** actions) be allowed in carousel? Controllable by custom element author?
- [ ] Should we rethink allowing carousel cards inside of an `Action.ShowCard`?
