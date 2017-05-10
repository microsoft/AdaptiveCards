# HTML Server Library
This is a .NET server side library for generating HTML markup to be sent to a client.

## Add a renderer
This is available as a nuget packages. 
```csharp
nuget install AdaptiveCards.Html
```
## Create an instance of your renderer
The next step is to create an instance of the renderer library. 
```csharp
HtmlRenderer htmlRrenderer = new HtmlRenderer(new HostConfig() { SupportsInteractivity = false });
```

## Hook up action callback
This library doesn't currently support interactive cards.

## Render a card
Acquire a card from a source and render it.

```csharp
var html = htmlRrenderer.RenderAdaptiveCard(card);
```

## Example
An example from the Xaml renderer.

```csharp
var hostConfig = new HostConfig() { ... };
HtmlRenderer renderer = new HtmlRenderer(new HostConfig() { SupportsInteractivity = false });
var result = renderer.RenderAdaptiveCard(card);
```

## Customization

### HostConfig 
To customize the renderer, provide an instance of the HostConfig object. See the [Host Config Schema](../HostConfigSchema.md) for a full description. Since the HostConfig object is instantiated with defaults, you only have to set the properties you want to change from the defaults.
Passing it to the renderer sets the default HostConfig to use for every card you render.

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

### Change per-element rendering
The HtmlRenderer has a registration mechanism which allows you to set a function that is called to perform the
rendering on a per-element basis.  It exposes a method called `SetRenderer<ElementT>(func);` 

To override the rendering of a `Input.Date` element:
```csharp
htmlRenderer.SetRenderer<DateInput>(RenderMyCustomeDate);
```
The new date renderer would look like this:
```csharp
protected static HtmlTag DateInputRender(TypedElement element, RenderContext context)
{
    DateInput input = (DateInput)element;
    ...
    return htmlTag;
}
```
### UI Framework styling
This framework annotates all HtmlTags it outputs with the following class names so that you can use CSS to customize further.

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

## Next steps

* [Implement a renderer](../ImplementingRenderer.md) 


