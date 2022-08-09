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

## HostConfig Options

* Max number of `CarouselPage`s
* Minimum timer restriction
* Do we need host config theming? We're leaning towards leaving this for native styling via CSS.

## Open Issues

- [ ] Should custom elements (card elements **and** actions) be allowed in carousel? Controllable by custom element author?
- [ ] Should we rethink allowing carousel cards inside of an `Action.ShowCard`?

# Header with Per Line Text Style
Supporting different text styling such as different fonts per line of text is not a must for this feature but we have to consider it as customers may request for it in the future.

![image](https://user-images.githubusercontent.com/4112696/183519757-156a18a9-73e7-47d9-8e00-ad84d0070f99.png)


In order to make the current implementation future proof such that it won't require us investing in this area repeatedly, there are four options we can consider. 
   
**option 1**: Use TextBlock and defer implementing line specific styling until it's asked as it's not required.

**option 2a**: Use RichTextBlock, and add `style` option to RichTextBlock's TextRun as we did for TextBlock.

**option 2b**: Use RichTextBlock, and have Carousel renderer to set header a11y role to the inlines.

**option 3**: Use Container and leave it to Card author to update a11y role header using TextBlock.  

###  Example of  proposed new schema of 2a
```json
"header": 
{
      "type": "RichTextBlock",
      "inlines": [
        "This is the first inline. ",
        {
          "type": "TextRun",
          "text": "We support colors,",
          "color": "good",
          "style": "header"
        }
    ]
}
```

## option 1: 
### pro: 
Easy to implement and ready to ship.
### cons:
Could force users to change their old payload.
## option 2a:
### pro:
Meets all of the requirement and fairly easy to implement
### con:
Must implement for all of the renders at some point; verification and publishing patches for them
## option 2b:
### pro:
Same pro of option2a + doesn't have to implement for all of the renderers since a11y role is implemented at the carousel renderer.
### cons:
All of TextRuns in RichTextBlock get the a11y header role; there isn't way to designate a specific TextRun to be a a11y header.
## option 3:
### pro:
Gives the author the most options to implement their design vision
### con:
We have to clearly communicate that `Container` has to be a parent element to users.
Can be cumbersome to use if user just wants to have a simple text based header.
Issues of enforcing forbidden items. Should we enforce the same policy of Carousel to it?
Will the policy diverge in the future, and if so, how do we keep track and maintain it?

# Spacing
This feature applies to spacing between header and carousel.

## option 1
Have users to specify spacing by using new line characters such as '\n' and '\r'.

## option 2
Make use of spacing property in Carousel