# HTML Server Library
This is a .NET server side library for generating HTML markup to be sent to a client.

## Add a renderer
This is available as a nuget packages. 
```
nuget install Microsoft.AdaptiveCards.Html
```
## Create an instance of your renderer
The next step is to create an instance of the renderer library. 
```csharp
HtmlRenderer htmlRrenderer = new HtmlRenderer(new HostConfig() { SupportsInteractivity = false });
```

## Hook up action callback
> At the moment, this library doesn't suport interactive cards.

## Render a card
Now you get a card from some source and you want to render it.  This is super easy:

```csharp
var html = htmlRrenderer.RenderAdaptiveCard(card);
```

## Example
Here is an example from the Xaml renderer to give you a feel for how this works:

```csharp
var hostConfig = new HostConfig() { ... };
HtmlRenderer renderer = new HtmlRenderer(new HostConfig() { SupportsInteractivity = false });
var result = renderer.RenderAdaptiveCard(card);
```

## Customization

### HostConfig 
To customize the renderer you provide an instance of the HostConfig object. (See [Host Config Schema](/documentation/#display-hostconfigschema) for the full description.)

> The HostConfig object will be instantiated with defaults, so you can set just the properties you want to change.

Example:
```csharp
var hostConfig = new HostConfig() 
{
    FontSizes = {
        Small = 15,
        Normal =20,
        Medium = 25,
        Large = 30,
        ExtraLarge= 40
    }
};
```

When you pass it in to the XamlRenderer you are setting the default HostConfig to use for every card you render.

### Changing per element rendering
The HtmlRenderer has a registration mechanism which allows you to set a function which is called to perform the
rendering on a per element basis.  It exposes a method called SetRenderer<ElementT>(func); 

Let's say you want to override the rendering of a Input.Date element.  You would do something like this:
```csharp
htmlRenderer.SetRenderer<DateInput>(RenderMyCustomeDate);
```

And the new date renderer would look like this:
```csharp
protected static HtmlTag DateInputRender(TypedElement element, RenderContext context)
{
    DateInput input = (DateInput)element;
    ...
    return htmlTag;
}
```


### UI Framework styling
This framework annotates all HtmlTags it outputs with the following class names so that you can use CSS to customize

| Element | Style names used|
|---|---|
| AdaptiveCard | ac-adaptivecard | 
| Action.Http | - |
| Action.OpenUrl  | -|
| Action.ShowCard | -|
| Action.Submit  | -  |
| ActionSet | ac-actionset |
| Column | ac-column |
| ColumnSet | ac-columnset |
| Container | ac-container|
| Input.ChoiceSet | - |
| Input.Date | - |
| Input.Number | - |
| Input.Text | - |
| Input.Time | - |
| Input.Toggle| - |
| Image  | ac-image |
| ImageSet  | ac-imageset |
| FactSet | ac-factset, ac-facttitle, ac.factvalue|
| TextBlock  | ac-textblock |

## Resources
* [Libraries](/documentation/#display-libraries) 
* [Implementing a renderer](/documentation/#disply-implementingrenderer) 
* [Customizing a renderer](/documentation/#display-customizingrenderer) 


