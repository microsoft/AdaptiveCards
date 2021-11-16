# Summary
Adaptive Cards does not natively support a way for card authors to display a list of cards in a carousel fashion. A carousel control that allows users to navigate between multiple adaptive cards is a highly requested feature from our community and would enable multiple cards sent in a single message for purposes like an image gallery, employee list etc. 

# Current Implementation by Bot Framework
Bot Framework has implemented a [carousel collection](https://docs.microsoft.com/en-us/microsoftteams/platform/task-modules-and-cards/cards/cards-reference) that is able to show a collection of Adaptive Cards in Teams and Bot Framework client.

![carousel-gif](https://user-images.githubusercontent.com/33772802/137048700-f237268d-2c80-464f-b688-77cbc17995d6.gif)

# In Scope
Capability | Priority
-- | --
Horizontal Carousel with centered arrows on the left and right of the card.| Must
Dots centered at the bottom of the card to indicate which page you are on and allow navigations. | Must
Arrows and dots need to be good touch targets and accessible(touch screens, Android, iOS, etc.). | Must
Automatic page navigation with time trigger | Should
Automatic page navigation with event-based push | Should
Page navigation timer should be ignored on hover | Should
Allow customizations such as vertical carousel, placement of arrows, custom styles for both arrows and dots at the bottom, different placement for dots | Could

# Not In Scope
- No animations on the carousel
- No nested carousels
- No actions on carousel
- No different background for each card in the carousel
- No support for media elements
- No input support

# Schema Implementation
```
{
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.6",
    "body": {
        "type": "Carousel",
        "timer": 5000,
        "pages": [
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
                        "type": "Image",
                        "url": "https://adaptivecards.io/content/cats/1.png",
                        "size": "medium"
                    }
                ]
        },
        {
            "type": "CarouselPage",
            "id": "theSecondCarouselPage",
            "items": [
                {
                    "type": "Image",
                    "url": "https://adaptivecards.io/content/cats/2.png",
                    "size": "medium"
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
                    "altText": "That's a cool cat!",
                    "size": "medium"
                }
            ]
        }
        ]
    },
    "actions": [
        {
            "type": "Action.OpenUrl",
            "url": "https://adaptivecards.io"
        }
    ]
}
```

![image](https://user-images.githubusercontent.com/33772802/137070357-bb6b5f10-e7b8-4575-bee1-a6023e69d371.png)
![image](https://user-images.githubusercontent.com/33772802/137070459-5514ad79-ebc6-4ea8-a30c-6158d676382b.png)

# Accessibility
## Navigation Interaction
The carousel control will be accessible via mouse, keyboard, and touch screen. The interactions will be as follows:
Navigation Interaction
- On mouse, hovering on the arrows will highlight them and clicking them will switch to the next/previous page.
- On keyboard hitting tab will change focus inside the carousel. When the arrows are focused, hitting spacebar or enter will switch to the next/previous page.
	- If you are currently tabbed into the left arrow the next tab will take you to the right arrow.
	- Left and right arrows on keyboard will not navigate through the carousel until we identify how this will work with inputs.
- On touchscreens either swiping on the list of items or tapping on the arrows will switch to the next/previous page.
- The dots at the bottom  of the carousel will allow navigation between the carousel. Clicking or tapping on the 3rd dot as an example will navigate to the 3rd page in the carousel. When keyboard focus is on dots at the bottom hitting spacebar will navigate to that specific card.
	- Clicking, tapping, hitting spacebar on the current card button will not do anything.

## Item Interaction
- Items within the carousel (I.e. images) will need to be accessible via touch, keyboard, and mouse.
- If the item within the carousel is focused upon tabbing within the card, hitting spacebar or enter will perform the action associated with the item. 
- If the item is tapped in a touchscreen, it will perform the action.
- If the item is clicked with mouse, it will perform the action.

## Narrator Interaction
- When the Narrator focus is on the card, regardless if the keyboard has the same focus, the narrator should be able to tell you which page you are currently on in the carousel.


# Fallback impact
If the host the card is rendered on does not support carousel, we should display a card with an error message stating that this experience is not supported on the current platform. 

If the host app supports carousel, but the implemnentation is incorrect we should only drop the non-supported carousel element and not the whole card. 
For example, if a user puts a text input element within one page of the carousel, we will not render the text input, but we will render the carousel and the pages that do have a correct implementation.

# Open Questions
- What happens if cards have different heights?
We should not allow cards to have different heights within the carousel. My proposal here would be to have a required property called `height` which would be the height in pixels of the carousel card. The card author would then be responsible for filling the space in this carousel container. They could leverage already existing properties like `maxLines` for `TextBlocks` and `height` on `Image` to fill the space appropriately. If the content in the carousel page extends over the height, we should clip that content. This would allow the carousel to maintain proper design guidance and a cohesive flow from page to page. 

Decision from design review: For initial carousel implementation we will require card authors to specify the height of their carousel container. As we expand this feature, we will evaluate the feasibility of making this property optional or `auto` and making the carousel height that of the largest card in the carousel.

- Will there be a limit of cards in the carousel?
    - Decision: Host will be responsible for determining limits.