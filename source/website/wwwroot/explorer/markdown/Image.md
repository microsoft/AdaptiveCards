The Image element allows for the inclusion of images in an Adaptive Card.

| Property | Type | Required |Description |
|---|---|---|---|
| **type**| **"Image"** | true | |
| **url** | string | true | The URL to the image. |
| **style** | [ImageStyle](#imagestyle) | false | The style in which the image is displayed. |
| **selectAction** | [Action](#action) | false | Action to perform for a selection for this image, (this allows image to act as an action) |
| **size** | [ImageSize](#imagesize) | false | Specifies the suggested size of the image. |
| **altText** | string  | false | Alternate text for the image for accessibility |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | false |Specifies how the element should be aligned horizontally within its container. |
