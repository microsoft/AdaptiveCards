# TOC

1. Install the SDK 
2. Get a card
- From object model
- Parse JSON
3. Render a card
- Instantiate a renderer
- Wire up action callback
- Retrieve input values
4. Basic customization
- HostConfig
- Native platform styling
5. Advanced customization
- Override element renderer
- Register custom element renderer
- Remove element renderer
- Extension properties on elements


1.1 NOTES:
1. Toggle visibility of elements


# Getting and using the SDK

* TODO: Should it be AdaptiveCards or Microsoft.AdaptiveCards?

```console
dotnet add package AdaptiveCards
```

```csharp
using AdaptiveCards; 
```

# Instantiate card

## From object model

```csharp
AdaptiveCard card = new AdaptiveCard();

card.Body.Add(new AdaptiveContainer());
card.Body.Add(new AdaptiveImage()); 
card.Body.Add(new AdaptiveTextBlock()); 
card.Actions.Add(new AdaptiveHttpAction());

// NAMING: Consensus in the room was to include the Adaptive prefix for object-model types
// Argument being we aren't describing "images" or "containers", they are "adaptive images" just like "adaptive cards" 
// Also seems highly likely that our other namespace would conflict with native UI stack and need to be aliased.
```

## Versioning

```csharp
public class AdaptiveSchemaVersion 
{
    int Major;
    int Minor;
    string ToString(); // "1.1"
}


AdaptiveVersion version = card.Version;

card.MinVersion = new AdaptiveVersion(major: 2, minor: 0);
card.FallbackText = "This card isn't supported. Please check your app for updates.";
```


## Parse from JSON string

```csharp

AdaptiveCardParseResult result = AdaptiveCard.FromJson(jsonString);
if (result.IsValid) {
    // Get card from result
    IList<ParseFailure> warnings = result.Warnings;
    AdaptiveCard card = result.Card;
} else {
    // Get errors?
    IList<ParseFailure> errors = result.Errors;
}
```


# Render card

## Instantiate a renderer

```csharp
// Create a default Host Config for now
AdaptiveHostConfig hostConfig = new AdaptiveHostConfig();

AdaptiveCardRenderer renderer = new AdaptiveCardRenderer(hostConfig);

// Get the schema version this renderer supports
AdaptiveSchemaVersion schemaVersion = renderer.SupportedSchemaVersion; // 1.0
```


## Render a Card

```csharp
RenderedAdaptiveCard renderedCard = await renderer.RenderCardAsync(card, cancellationToken: null);

// Validate the rendered card
if(!renderedCard.IsRenderedSuccessfully) {
    // TODO: FINISH THIS
    IList<string> warnings = renderedCard.Warnings;
    IList<string> errors = renderedCard.Errors;
    return;
}

// Prefetch images
// TODO: Should this be load assets? Like audio, and other media? I'm not sure if we want to group all those together, hmmm
await renderedCard.LoadImagesAsync(cancellationToken: null);

// Get the UI element
FrameworkElement ui = renderedCard.FrameworkElement;

// Just for fun, get the AdaptiveCard object model back out
AdaptiveCard originatingCard = renderedCard.OriginatingCard;
```


## Wire up Action events

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
        JObject inputs = card.UserInputs.AsJson(InputValueMode.RawString);

        // Serialize the JObject to a custom type 
        MyForm form = inputs.ToObject<MyForm>();
    }
    else if (action is typeof(ShowCardAction)) {
        scrollViewer.ScrollIntoView(card.FrameworkElement);
    }
}
```

## Host Config 

```csharp
// Parse a Host Config from JSON
HostConfigParseResult parseResult = AdaptiveHostConfig.FromJson(jsonString);

if (result.IsValid) {
    IList<ParseFailure> warnings = result.Warnings;
    AdaptiveHostConfig hostConfig = result.HostConfig;
} else {
    IList<ParseFailure> errors = result.Errors;
}

// Or set properties directly

// Maximum image size to download
hostConfig.MaxImageSize = "200"; // kB

// Maximum payload size before we throw on Render or Validate
hostConfig.MaxPayloadSize = "10"; // kB

// Assign the Host Config to the renderer
renderer.HostConfig = hostConfig;
```

## Native platform styling

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


# Extensibility

## Override an existing element

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

## Render a custom element

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

## Remove a renderer

```csharp
renderer.ElementRenderers.Remove("Action.Http");
```

## Additional properties on elements

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

```csharp
// DECISION: Typescript will support, others on backburner
// TODO: File issue not processing any text

renderer.ProcessMarkdown = MarkdownHandler;

private string MarkdownHandler(string text) {
    // process markdown
}
```


# IGNORE BELOW THIS FOR NOW


## Parsing and Validation

## This section is not complete

### Validate card against Host Config errors

```csharp
ValidationResult result = card.Validate(myHostConfig);
if (!result.IsValid) {
    IList<ValidationError> errors = result.Errors;
}
```

### Validate against Host Config

```csharp
ValidationResult result = card.Validate(myHostConfig);
```


public class ParseFailure  {
    string Message { get; }

    bool IsError { get; }

    //SchemaViolation
        //MissingCardType = 5,
        //CollectionCantBeEmpty = 1,
        //InvalidPropertyValue = 4,
        //PropertyCantBeNull = 6,
        //MissingVersion,
}


// Parse Errors
// 1. Is it even valid json?
// 2. Does it pass schema validation?

// Parse warnings
// Are there any?


public class RenderWarning
{
  RendererWarnings
        UnknownActionType = 8,
        UnknownElementType = 9,
            
    HostConfigWarnings
        InteractivityNotSupported = 3,
        TooManyActions = 7,    
}

public class RenderError
{
    UnsupportedCardVersion = 10,
    ElementTypeNotAllowed = 2, // TODO ASK DAVID: Do we need this?
}