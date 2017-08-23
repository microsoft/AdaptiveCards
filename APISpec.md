# Getting the SDK

* TODO: Should it just be AdaptiveCards?

```console
nuget install Microsoft.AdaptiveCards
```

# Instantiate card

```csharp
// Should be same as library name
using Microsoft.AdaptiveCards; 
```

## From object model

```csharp
AdaptiveCard card = new AdaptiveCard();

card.Body.Add(new AdaptiveContainer());
card.Body.Add(new AdaptiveTextBlock()); 
card.Actions.Add(new AdaptiveHttpAction());

// TODO: Adaptive prefix? We need to evaluate chance of conflict with other namespaces. Is it likely that a class would use AdapativeCards and System.UI.Xaml at the same time?

```

## Versioning

```csharp

public class AdaptiveVersion 
{
    int Major; Minor; Patch;
    string ToString();
}

// Version automatically provided by object model/renderer
AdaptiveVersion version = card.Version;

card.MinVersionRequired = new AdaptiveVersion(major: 2, minor: 0, patch: 0);
card.FallbackText = "Please update your app to see this card";
```


## Parse from JSON string

```csharp
// TODO: Should this be an enum or an interface? TypeScript currently has as enum
public class ParseError  {
    string Message;

    SchemaValidationError;
        //MissingCardType = 5,
        //CollectionCantBeEmpty = 1,
        //InvalidPropertyValue = 4,
        //PropertyCantBeNull = 6,
        //MissingVersion,

}

        
    Renderer Errors
        UnsupportedCardVersion = 10,
        ElementTypeNotAllowed = 2, // TODO: Do we need this?

  

public class ValidationWarning
{
  RendererWarnings
        UnknownActionType = 8,
        UnknownElementType = 9,
            
    HostConfigWarnings
        InteractivityNotSupported = 3,
        TooManyActions = 7,    
}

// Parse Errors
// 1. Is it even valid json?
// 2. Does it pass schema validation?

// Warnings
// 1. Does it violate host config?
// 2. Unknown element 

ParseResult result = AdaptiveCard.FromJson(jsonString);
if (result.IsValid) {
    // Get card from result
    AdaptiveCard card = result.Card;

} // else errors




ParseResult result = AdaptiveCard.FromJson(jsonString);
if (result.IsValid) {
    // Any warnings?
    IList<ValidationFailure> warnings = result.Warnings;
}
else {
    IList<ValidationFailure> errors = result.Errors;
}
```

### Validate card against Host Config errors

* Type casting errors (e.g., bool expected and we got a string)

```csharp
ValidationResult result = card.Validate();
if (!result.IsValid) {
    IList<ValidationError> errors = result.Errors;
}
```

### Validate against Host Config

```csharp
ValidationResult result = card.Validate(myHostConfig);
```

# Render card

## Instantiate a renderer

```csharp
XamlCardRenderer renderer = new XamlCardRenderer();

// Get the schema version this renderer supports
string schemaVersion = renderer.SupportedSchemaVersion;
```

## Host Config

```csharp
AdaptiveHostConfig hostConfig = new AdaptiveHostConfig();

// ... or parse
// Change to if 
try {
    AdaptiveHostConfig hostConfig = AdaptiveHostConfig.FromJson(jsonString);
}
catch (ParseException e) {
    // we throw here since it's assumed you created the host config, and it should never be expected to fail
}

// We should provide a reasonable default if this property isn't set
renderer.HostConfig = hostConfig;
```

### Host Config options

```csharp
// Maximum image size to download
hostConfig.MaxImageSize = "200"; // kB

// Maximum payload size before we throw on Render or Validate
hostConfig.MaxPayloadSize = "10"; // kB

// TODO: more thorough review of these options is necessary
// https://github.com/Microsoft/AdaptiveCards/blob/master/samples/Themes/bing.json
```

## Wire up Action events

```csharp

renderer.OnAction += ActionHander;

private void ActionHandler(object sender, ActionEventArgs e) {
    AdaptiveCard card = e.Card;
    if(e.Action is AdaptiveOpenUrlAction) {
        // open URL
    }
    ...
}
```

## Inputs

```csharp
private void ActionHandler(object sender, ActionEventArgs e) {
    if(e.Action is SubmitAction) {
        e.Inputs[""] =  // TODO: FInish
    }
    ...
}
```


## Generate UI tree

```csharp
// Render and let the UI stack download images 
// This means a card could be added to the app and then images load causing re-layout
RenderResult result = await renderer.RenderAsync(card, cancellationToken: null);

if(result.SuccessfullyRendererd) {
    UIElement ui = result.UIElement;
}
else {
    // timed out
    // images failed to load
    // TODO: what else?
}
```

### Prefetch images
Prefetch images and don't return until they are finished

```csharp
RenderResult result = await renderer.RenderAsync(card, prefetchImages: true, cancellationToken: null);

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

renderer.ElementRenderers["TextBlock"] = new CoolTextBlockRenderer());
```

## Render a custom element

```csharp
public class ProgressBarRenderer : IElementRenderer
{
    UIElement Render() {
        ...
    }

    void Parse(object?) {

    }
}

renderer.ElementRenderers["ProgressBar"] = new ProgressBarRenderer());
```

## Remove a renderer
```csharp
renderer.ElementRenderers.Remove("HttpAction");
```

## Override markdown processing

```csharp
renderer.ProcessMarkdown = MarkdownHandler;

private string MarkdownHandler(string text) {
    // process markdown
}
```

## Custom properties on elements


```json
{
    "type": "TextBlock",
    "flashing": true,
    "extensions": {
        "flashing": true
    }
}
```

# Next steps

* API reviiew on each platform
* Any missing items/features of a specific renderer not accounted for?