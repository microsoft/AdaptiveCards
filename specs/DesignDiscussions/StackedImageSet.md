# Stacked Images/Badging
### Problem 
In order to enable the Messenger widget, Meta is requesting the ability to stack images like so:
![img](assets/StackedImageSet/stackedImage.png)

This will enable them to show a chat as a group chat in the Messenger widget.
#### Key Features 
*	Stack a maximum of 2 images. The green status indicator would not be displayed.
*	The images will always be stacked diagonal as shown above.
*	The front overlapping image needs to have a border that is the same color as the background so that the stacking appears natural.

### Alternative Considered
Users can achieve a similar behavior by using background images
![img](assets/StackedImageSet/currentStackedImage.png)

In this example the image on the right is a regular image using `"style": "person"` and the bigger image is a circular background image with a transparent background. The issues here are that:
* It is difficult to place the regular image where it needs to be.
* The front image does not have a border

### Proposal
The review we had in the design discussion suggested we add 2 properties to [`ImageSet`](https://adaptivecards.io/explorer/ImageSet.html) for this. 
 
* `style`: "stacked" 
  * indicates that images are displayed in a stack
* `offset`: a number 
  * indicates the magnitude of offset in pixels. This is how far apart diagonally the images are at. Images are at tangent at 0. In other word, there will be no space between the images except the border.  Negative values moves images closer up to the image's diameter. Positive values move images farther and there is no limitation imposed by the spec, but will result in bad UI with extreme value.

|Capability|Priority|
|---|---|
|Allow users to stack at least 2 images	|p0
|The stacked image sets support "style": "person" so they are rounded|p0	
|The stacked images stack diagonally with the front image on the left	|p0
|The front image has a border that matches the background of the parent container for blending purposes	|p0
|The stacked images can stack from left to right	|p2
