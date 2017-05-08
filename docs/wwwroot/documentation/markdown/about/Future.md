# Future work
While we have made a ton of progress defining adaptive cards to this point, there is still lots of work to do. 

Our hope is that via active developer communities like botness, and great partners like Slack, and Kik we can create a great eco-system of cross platform cards.

Here are some future areas to explore:

## Making cards reactive
One of the areas we plan to explore is making card layout reactive to available space. Adaptive cards are adaptable to different devices, ux styles and and ui frameworks, but they are not reactive yet.  We
hope to define additional properties on elements which allow card producers to provide the necessary hints to the
rendering libraries so that they can intelligently change the layout in a way which maintains the intent of the card.

### Some ideas 
* add *importance* property which annotates importance of content, so we can drop less important content to fit available space
* Add *constraints* and *policy* property describing how to deal when constraints can't be met. For example:
  * Hide content or collapse content to smaller size
  * Add threshold where columnSet because carousel of columns
  * etc.

## New element types
* audio - ability to have playable audio in card with transport controls
* video - ability to have video player in card with transport controls 
* maps - ability to embed a map into a card with interactivity or fallback to bitmap
* *what elements do you want or need*?

## New rendering libraries
* react 
* react native
* *What frameworks do you want?*