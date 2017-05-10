# Future work
While we have made excellent progress defining adaptive cards, there is still lots of work to do. 

Our hope is that through active developer communities like botness, and great partners like Slack and Kik, we can create a great ecosystem of cross-platform cards.

Here are some future areas we plan to explore:

## Make cards reactive
Card layouts should be reactive to available space. Adaptive cards are adaptable to different devices, ux styles and and ui frameworks, but they are not reactive yet. Additional properties must be defined on elements which allow card producers to provide the necessary hints to the rendering libraries so that they can intelligently change the layout in a way which maintains the intent of the card.

### Some ideas 
* Add an **importance** property which annotates importance of content. Less important content can be dropped to fit available space
* Add **constraints** and **policy** properties describing how to react when constraints can't be met. 
  * Hide content or collapse content to smaller size.
  * Add a threshold that, when exceeded, changes `columnSet` to carousel of columns.

## New element types
* Audio - playable audio in card with transport controls
* Video - video player in card with transport controls 
* Maps - embed a map into a card with interactivity or fallback to bitmap
* *What elements do you want or need*?

## New rendering libraries
* React 
* React native
* *What frameworks do you want?*