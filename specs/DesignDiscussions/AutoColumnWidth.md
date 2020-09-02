# Defining the auto size

## Column Width values and behaviours

Since the first release of AC the column has had multiple ways of defining the width each column may have, the current options for defining the width are:
* ```"Auto"```
* ```"Stretch"```
* Specific size in pixels (i.e. ```"65px"```)
* Ratio (i.e ```0.5```, ```300```)

The "specific size in pixels" and "ratio" column width options have the most inferrable behaviours and should be as follows: 
* Specific size in pixels: The column should have the same size as specified in pixels


* Ratio: Each column is given a portion of the width defined by the sum of all the weights (Follow up, are there inconsistencies when combining with other column widths?). This can be visually explained using the following diagram

![img](assets/Auto/RatioColumnSet.PNG)

As can be seen in the previous diagram, ```A``` has a width of ```30```, ```B``` has a width of ```60``` and ```C``` of ```10```, the sum of all ratios is ```100```. From the available width of ```400```, each column gets a width in pixels directly proportional to the ratio of the column but inversely proportional to the sum weight.

![img](assets/Auto/RatioCalculation.PNG)

After defining the two most explicit behaviours we still have two more behaviours to explain, ```Auto``` and ```Stretch``` whose behaviour is closely linked

* ```auto```: The column should use as much space as needed but not more. This behaviour can be understood with the ActivityUpdate card in our scenarios folder, as can be seen in the card, the image is located inside a column with ```auto``` width, this forces the view to only use as much space as the image needs.

![img](assets/Auto/ActivityUpdate.PNG)

* ```stretch```: this value behaves the counterpart to ```auto```, where auto wants to only use as much space as needed, ```stretch``` wants to use the space it needs plus the empty space after rendering all other columns, if there are more than one column with stretch, then all columns with stretch end up with the same width.

To provide a clearer insight we will use the ActivityUpdate card to help us with the visual representation:

By changing the image column width to ```stretch``` (and the right column to ```auto```) we can see that the column now occupies all the empty space there is 

![img](assets/Auto/ActivityUpdateStretchAuto.PNG)

By having both column widths as ```stretch``` we can see that both columns now have the same size, the empty space is not divided evenly.

![img](assets/Auto/ActivityUpdateStretchStretch.PNG)

## Consistency issue

The previously explained behaviours are not consistent accross platforms when rendering, this spec will focus on the ```auto``` behaviour as it was raised in the [#3855](https://github.com/microsoft/AdaptiveCards/issues/3855) issue. 

While all platforms share the same basic behaviour for ```auto``` as they all provide the column with as much space as it needs, this rule ends up with some unwanted side effects when the column contents are too big, for example, let's consider the following card 

> NOTE: This is an abridged version of the adaptive card included in the linked issue [#3855](https://github.com/microsoft/AdaptiveCards/issues/3855)

```json
{
   "type":"ColumnSet",
   "columns":[
      {
         "type":"Column",
         "width":"auto",
         "items":[
            {
               "text":"**Peter Parker - R-00069 Part time hero**",
               "type":"TextBlock"
            },
            {
               "text":"Spider-Man is a fictional superhero created by writer-editor Stan Lee and writer-artist Steve Ditko.",
               "type":"TextBlock"
            }
         ]                     
      },
      {
         "type":"Column",
         "width":"auto",
         "items":[
            {
               "type":"ActionSet",
               "actions":[
                  {
                     "type":"Action.Submit",
                     "title":"Request feedback"
                  }
               ]
            }
         ]
      }
   ]
}
```

This card provides a simple scenario where the card author places a ```Column``` containing a ```TextBlock``` element with long text and another ```Column``` with an ```ActionSet``` element with a single action. This card is rendered in the designer as follows:

![img](assets/Auto/javascript.PNG)

The left column wraps the text to allow the right column to have some space to render. While this behaviour seems natural, it is not followed by all platforms as can be seen below:

| Platform | |
| --- | --- |
| UWP ❌ | ![img](assets/Auto/uwp.gif) |
| Android ❌ | ![img](assets/Auto/android.PNG) |
| iOS ✔ | ![img](assets/Auto/iOS.PNG) |
| .NET WPF ❌ | ![img](assets/Auto/wpf.gif) |

For the UWP, Android and WPF platforms the behaviour seems to be similar, the ```TextBlock``` element is big enough to push the ```ActionSet``` out of the screen, while this behaviour complies with the rule we defined for ```auto``` (provide as much space as needed for its contents) it doesn't behave as the designer does which will provide a bad user experience.

## Proposed solution

Due to the limitations of the currently used native controls, some changes would have to be performed on the measuring and layouting methods of the affected platforms to provide the a behaviour as similar as possible to the JavaScript renderer. 

The JavaScript renderer would be considered as our source of truth for three main reasons: 
1. Any card author would most probably be using the designer, so the mobile platforms should try to have a similar behaviour
2. Due to the html/javascript/css rendering being performed on a web browser we won't be able to modify the rendering behaviour 
3. It looks better and provides a better user experience than the Android and UWP renderers   

### So what is the behaviour for auto in JS?

When a column has a width of ```auto``` the renderer creates an ```ac-container``` view setting ```flex: 0 1 auto```. This value sets the following behaviour

> It makes the flex item inflexible when there is some free space left, but allows it to shrink to its minimum when there is not enough space. The alignment abilities or auto margins can be used to align flex items along the main axis. [(Source)](https://css-tricks.com/almanac/properties/f/flex/#:~:text=flex%3A%200%20auto%3B%20This%20is%20the%20same%20as,its%20minimum%20when%20there%20is%20not%20enough%20space.)

In the previous snippet, the main axis refers to the horizontal axis

As there are three values passed down to ```flex```, let's explain each of them in order:
1. flex-grow (```0```): Specifies how much of the remaining space in the flex container is given to the item
2. flex-shrink (```1```): Sets the flex shrink factor of a flex item. If the size of all flex items is larger than the flex container, items shrink to fit according to this value. The shrink is relative to other shrinking elements, so in our case the value should not matter, just that it shrinks.
3. flex-basis (```auto```): A flex-basis value set to auto sizes the element according to its size property (which can itself be the keyword auto, which sizes the element based on its contents).

### Proposed fix

By understanding how the flex-shrink property works the following algorithm can be proposed to fix the current measure and layout behaviour:

```
function measure:
    Pass in: size (width, height)
    for each Column in ColumnSet
        if width is pixel width
            set fixed pixel width
            add column width to unmodifiable width
        end
        if width is stretch
            measure Column as if width is auto
            add column width to stretch width
            increase stretch counter
        end
        if width is auto
            measure Column
        end 
    
        add column width to total width
    end 

    if total width > width:
        decrease ratio = (width - unmodifiable width) / (totalWidth - unmodifiable width)
        for each Column in ColumnSet
            if width is stretch or auto
                measure Column with measuredColumn * decrease ration
            end
        end
    else if total width < width:
        stretch column width = (stretch width + total width - width) / stretch counter
        
        for each Column in ColumnSet
            if width is stretch
                measure Column with stretch column width
            end
        end
    end
```

By just examining this algorithm we may be able to find that it lacks two simple cases:
* What happens if the pixel specified width(s) are bigger or equal than the column width? Should we also decrease the proportion of the column widths or should we always honour those values?
* What happens to ratio width? Can we consider that ratio width should not be mixed with other types of column widths as it's a relative concept?