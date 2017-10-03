
# Getting and using the SDK

```console
dotnet add package AdaptiveCards
```

```csharp
using AdaptiveCards; 
```

## Instantiate card

### From object model

```csharp
AdaptiveCard card = new AdaptiveCard();

card.Body.Add(new AdaptiveContainer());
card.Body.Add(new AdaptiveImage()); 
card.Body.Add(new AdaptiveTextBlock()); 
card.Actions.Add(new AdaptiveHttpAction());

// NAMING: Use best judgement per platform. If naming collisions are likely, e.g., another Image type will exist, consider prefixing model types and enums with "Adaptive": AdaptiveImage vs Image
```

### Parse JSON

```csharp
AdaptiveCardParseResult result = AdaptiveCard.FromJson(jsonString);

if (result.Card != null)
{
    // Get card from result
    AdaptiveCard card = result.Card;
}
else
{
    // Failed parsing
    
    // FUTURE
    IEnumerable<ParseResult> errors = result.Errors;
    IEnumerable<ParseResult> warnings = result.Warnings;
}
```

### Versioning

```csharp
public class AdaptiveSchemaVersion 
{
    int Major;
    int Minor;
    string ToString(); // "1.1"
    
    public AdaptiveSchemaVersion(int major, int minor);
}


AdaptiveSchemaVersion version = card.Version;

card.MinVersion = new AdaptiveSchemaVersion(major: 2, minor: 0);
card.FallbackText = "This card isn't supported. Please check your app for updates.";
```


## Render card

### Instantiate a renderer

```csharp
// Create a default renderer
AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

// Or use a custom host config
renderer = new AdaptiveCardRenderer(hostConfig);

// Get the schema version this renderer supports
AdaptiveSchemaVersion schemaVersion = renderer.SupportedSchemaVersion; // 1.0
```


### Render a Card

```csharp
RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);

// Validate the rendered card
if (renderedCard.FrameworkElement == null)
{
    // Failed rendering
    
    // FUTURE
    IEnumerable<string> errors = renderedCard.Errors;
    IEnumerable<string> warnings = renderedCard.Warnings;
    return;
}


// FUTURE: Wait for images to load
// TODO: Should this be load assets? Like audio, and other media? I'm not sure if we want to group all those together, hmmm
await renderedCard.WaitForImagesAsync();

// Get the UI element
FrameworkElement ui = renderedCard.FrameworkElement;

// Just for fun, get the AdaptiveCard object model back out
AdaptiveCard originatingCard = renderedCard.OriginatingCard;
```


### Wire up Action events

```csharp
// Handle the events when a user taps on an Action
renderedCard.OnAction += ActionHandler;

private void ActionHandler(object sender, AdaptiveActionEventArgs e) {
     // What card was tapped
    RenderedAdaptiveCard card = e.RenderedCard;

    // What Action was tapped
    AdaptiveActionBase action = e.Action;
    
    if(action is typeof(OpenUrlAction)) {
        // open URL
    }
    else if(action is typeof(SubmitAction)) {
        
        SubmitAction submitAction = (SubmitAction)action;

        // Get the data, which could be a string or object
        JObject data = submitAction.Data;

        // Get the user inputs as a JSON object
        // Note: we DO NOT do any input validation, be prepared to parse the data gracefully
        // RawString is outlined here https://github.com/Microsoft/AdaptiveCards/issues/652
        JObject inputs = e.RenderedCard.UserInputs.AsJson(InputValueMode.RawString);

        // Serialize the JObject to a custom type 
        MyForm form = inputs.ToObject<MyForm>();
    }
    else if (action is typeof(ShowCardAction)) {
        scrollViewer.ScrollIntoView(card.FrameworkElement);
    }
}
```

### Host Config 

```csharp
// Parse a Host Config from JSON
HostConfigParseResult result = AdaptiveHostConfig.FromJson(jsonString);

if (result.HostConfig != null)
{
    AdaptiveHostConfig hostConfig = result.HostConfig;
}
else
{
    // Failed parsing
    
    // FUTURE
    IEnumerable<ParseResult> errors = result.Errors;
    IEnumerable<ParseResult> warnings = result.Warnings;
}

// Or set properties directly

// Maximum image size to download
hostConfig.MaxImageSize = "200"; // kB

// Maximum payload size before we throw on Render or Validate
hostConfig.MaxPayloadSize = "10"; // kB

// Assign the Host Config to the renderer
renderer.HostConfig = hostConfig;
```

### Native platform styling

A Host App can apply native platform style for when Host Config isn't robust enough.

```csharp
// Provide a custom resource dictionary to the Renderer
renderer.ResourceDictionary = myResourceDictionary;
```

An example XAML ResourceDictionary

```xml
<ResourceDictionary>
    <Style x:Key="Adaptive.Action.Tap" TargetType="Button">
        <Style.Triggers>
            <Trigger Property="IsMouseOver" Value="True">
                <Setter Property="Cursor" Value="Hand" />
            </Trigger>
            <EventTrigger RoutedEvent="UIElement.MouseEnter">
                <BeginStoryboard>
                    <Storyboard>
                        <DoubleAnimation Duration="0:0:0.2" Storyboard.TargetProperty="Opacity" To="0.7" />
                    </Storyboard>
                </BeginStoryboard>
            </EventTrigger>
            <EventTrigger RoutedEvent="UIElement.MouseLeave">
                <BeginStoryboard>
                    <Storyboard>
                        <DoubleAnimation Duration="0:0:0.2" Storyboard.TargetProperty="Opacity" To="1.0" />
                    </Storyboard>
                </BeginStoryboard>
            </EventTrigger>

        </Style.Triggers>
        <Setter Property="Template">
            <Setter.Value>
                <ControlTemplate TargetType="Button">
                    <Border Background="Transparent">
                        <ContentPresenter/>
                    </Border>
                </ControlTemplate>
            </Setter.Value>
        </Setter>
    </Style>
</ResourceDictionary>
```


## Extensibility

### Override an existing element

```csharp
public class CoolTextBlockRenderer : IRenderer {

    UIElement Render(AdaptiveUnknownElement element)
    {
        string type = element.Type; // CoolTextBlock

        dynamic d = JObject.Parse(element.Json);
        AdaptiveTextBlock t1 = JsonConvert.DeserializeObject<AdaptiveTextBlock>(d.title);
        AdaptiveTextBlock t2 = JsonConvert.DeserializeObject<AdaptiveTextBlock>(d.subtitle);

        var tbRenderer = new TextBlockRenderer();
        TextBlock t = (TextBlock)tbRendererv.Render(t1);
        
        // ...modify the XAML TextBlock

        return t;
    }
}

renderer.ElementRenderers.Set("TextBlock", new CoolTextBlockRenderer());
```

### Render a custom element

```csharp
public class ProgressBarRenderer : IElementRenderer
{
    static const TypeName = "ProgressBar";

    UIElement Render() {
        ...
    }

    void Parse(object?) {

    }
}

renderer.ElementRenderers.Set(ProgressBarRenderer.TypeName, new ProgressBarRenderer());
```

### Remove a renderer

```csharp
renderer.ElementRenderers.Remove("Action.Http");
```

### Additional properties on elements

* Should Host Config allow hosts to declare their custom extensions? We could build tooling around it if so
https://github.com/Microsoft/AdaptiveCards/issues/234

```json
{
    "type": "Image",
    "src": "http://",
    "-blur": true
}
```

```csharp
string blurStr = image.AdditionalProperties["-blur"];
if(blurStr != null {
   bool blur = bool.Parse(blurStr);
}
```

## Override markdown processing

* TODO: This is NOT final yet

```csharp
// DECISION: Typescript will support, others on backburner
// TODO: File issue not processing any text

renderer.ProcessMarkdown = MarkdownHandler;

private string MarkdownHandler(string text) {
    // process markdown
}
```
