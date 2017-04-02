
The TextBlock element allows for the inclusion of text, with various font sizes, weight and color, in Adaptive Cards.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"TextBlock"** |
| **text** | string | true |The actual text to display |
| **size** | [TextSize](#textsize) | false |The size of the text |
| **weight** | [TextWeight](#textweight) | false |The weight of the text |
| **color** | [TextColor](#textcolor) | false |The color of the text |
| **isSubtle** | boolean |false | Indicates whether the color of the text should be slightly toned down to appear less prominent |
| **wrap** | boolean | false | Indicates whether the text should be allowed to wrap |
| **maxLines** | number | false | When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use. |
| **horizontalAlignment** | [HorizontalAlignment](#horizontalalignment) | false |Specifies how the element should be aligned horizontally within its container. |

