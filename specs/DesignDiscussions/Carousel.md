# Carousel support for Adaptive Cards

## Original Proposal
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
  "body": 
    {
      "type": "Carousel",
      "timer": 5000,
      "pages":[
        {
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
          }
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

So here we have a sample carousel card. You'll probably notice the new `CarouselPage` element. It acts pretty similarly to a `Container`, but with some differences:
* No `style` (or at least, we don't have a reason to have `style` here yet)
* No `bleed`
* We don't allow every element type within a `CarouselPage`, only the subset we decide on (see following sections for more details)

Having this new element also has the advantage of allowing us to reuse it later should we decide to promote the idea of `Carousel` as a regular page element (a `Carousel` would be a collection of `CarouselPage`s in this regime.

This sample also has a page-wide `Action.Execute`. When the user clicks this action (rendered as a button below the ⚬●⚬⚬ control), the host will receive the standard callback. The `id` of the currently-visible page should be exposed as a property on the `Action` the callback provides (we may also want to provide positional properties as well, but I'm not sure if they're needed).

It's worth noting that we think we *should* allow `ActionSet` elements inside a `CarouselPage`, but they should be restricted to the same actions as the top level `actions` property.

Another thing to note is that this implies the existence of a special carousel card inside of an `Action.ShowCard`, which we think is probably okay, but we should talk it through a bit more. If we do allow it, input gathering should happen as it currently does -- namely, the parent card's inputs are supplied if the `Action.ShowCard` has an `Action.Submit` or `Action.Execute` invoked from within it.

## Disallowed Elements

In order to meet our schedule, we need to avoid some common pain points that would require extra dev/spec time that might not necessarily lead to a better card author or AC host experience. In particular, we believe that the following scenarios/experiences should be explicitly not supported for v1:

* Carousel
* ShowCard
* ToggleVisibility
* Input Elements
  * Input elements **should not** be allowed in carousels. Decisions about input gathering and validation are likely to be difficult to get right, tricky to code, and even trickier to retract later on. Should we choose to open this functionality up later, we certainly can.

## Supported Elements

All elements not mentioned above are allowed inside a carousel.

## Timer Property
* `"timer" : number`
  * when set, the number sets the duration before a Carousel page transitions to the next Carousel page.
  * while hovering, mouse click, and touch events, this auto transition is canceled.

## HostConfig Options
* Max number of `CarouselPage`s
* Minimum timer restriction
* Do we need host config theming? We're leaning towards leaving this for native styling via CSS.

## Updated Proposal 
There had been strong demand to adorn the Carousel with other AdaptiveCard elements as shown in the image below. 
Customers wanted to have an option that allow these decorative elements around the Carousel remain static when CarouselPage is changed.
Customers also wanted to have conditional layout template that can be switched between standard layout and layout with Carousel. 
Thus, we have relaxed the rule of treating Carousel as a special type of AdaptiveCard, and made Carousel as a regular AdaptiveCard element while all other rules remain intact.

![image](https://user-images.githubusercontent.com/4112696/183519757-156a18a9-73e7-47d9-8e00-ad84d0070f99.png)

Snippet of json of the above image
```json
"body": [
		{
			"type": "Container",
			"items": [
				{
					"type": "TextBlock",
					"text": "Photo Album",
					"size": "ExtraLarge",
					"style": "heading",
					"horizontalAlignment": "Center"
				},
				{
					"type": "TextBlock",
					"text": "Landscapes",
					"size": "Large",
					"horizontalAlignment": "Center"
				},
				{
					"type": "Carousel",
					"spacing": "Large",
					"pages": [
						{
							"type": "CarouselPage",
							"id": "firstPage",
```

## InitialPage Property
* `"initialPage" : number`
  * Set initial Carousel Page

## Open Issues

- [ ] Should custom elements (card elements **and** actions) be allowed in carousel? Controllable by custom element author?
- [ ] Should we rethink allowing carousel cards inside of an `Action.ShowCard`?
