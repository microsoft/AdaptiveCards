# UWP Library
This is a renderer which targets UWP native controls.

## Add a renderer

Coming Soon... 

## Create an instance of your renderer
The next step is to create an instance of the renderer library. 
```csharp
var renderer = new XamlCardRenderer();
```
## Render a card
Now you get a card from some source and you want to render it.  This is super easy:

```csharp
var uiCard = await renderer.RenderCardAsXamlAsync(card);
// add it to your ui
myGrid.Children.Add(uiCard);
```

## Example
Here is an example from the UWP renderer to give you a feel for how this works:

```csharp
var renderer = new XamlCardRenderer();
var uiCard = await renderer.RenderCardAsXamlAsync(_card);
myGrid.Children.Add(uiCard);
...
```

### HostConfig 

To customize the renderer you provide an instance of the HostConfig object. (See [Host Config Schema](/documentation/#display-hostconfigschema) for the full description.)

> The HostConfig object will be instantiated with defaults, so you can set just the properties you want to change.

Example:
```csharp
var hostOptions = new AdaptiveHostOptions() 
{
    FontSizes = {
        Small = 15,
        Normal = 20,
        Medium = 25,
        Large = 30,
        ExtraLarge= 40
    }
};
renderer.HostOptions = hostConfig;
```
When you pass it in to the UWPRenderer you are setting the default HostConfig to use for every card you render.

### Changing per element rendering
*Coming soon*

### UI Framework styling
*Coming soon*

## Resources
* [Libraries](/documentation/#display-libraries) 
* [Implementing a renderer](/documentation/#disply-implementingrenderer) 
* [Customizing a renderer](/documentation/#display-customizingrenderer) 


