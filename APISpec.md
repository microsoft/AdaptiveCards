# Getting the SDK


```console
nuget install Microsoft.AdaptiveCards
// TODO: or AdaptiveCards?
```


# Instantiate card

```csharp
// Should be same as library name
using Microsoft.AdaptiveCards; 
```

## From object model

```csharp
AdaptiveCard card = new AdaptiveCard("1.0");

card.Body.Add(new AdaptiveTextBlock()); 
// TODO: Adaptive prefix? We need to evaluate chance of conflict with other namespaces. Is it likely that a class would use AdapativeCards and System.UI.Xaml at the same time?

card.Actions.Add(new ActionHttp());
// TODO: HttpAction?
```

## Versioning

```csharp
// TODO: Should this be required and part of the ctor?
// TODO: Should this be a string?
card.Version = "2.1"; 
card.MinVersionRequired = "2.0";
card.FallbackText = "Please update your app to see this card";
```


## Parse from JSON string

```csharp
// TODO: Should this be an enum or an interface? TypeScript currently has as enum
public enum ValidationError {
    ActionTypeNotAllowed = 0,
    CollectionCantBeEmpty = 1,
    ElementTypeNotAllowed = 2,
    InteractivityNotAllowed = 3,
    InvalidPropertyValue = 4,
    MissingCardType = 5,
    PropertyCantBeNull = 6,
    TooManyActions = 7,
    UnknownActionType = 8,
    UnknownElementType = 9,
    UnsupportedCardVersion = 10,
    MissingVersion,

}

ParseValidationResult result = AdaptiveCard.FromJson(jsonString);
if (result.IsValid) {
     // Get card from result
    AdaptiveCard card = result.Card;   
}
else {
    IList<ValidationError> errors = result.Errors;
}
```

### Validate card against Host Config errors

* Type casting errors (e.g., bool expected and we got a string)

```csharp
ParseValidationResult result = card.Validate();
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
    if(e.Action is OpenUrlAction) {
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
public class CoolTextBlockRenderer : TextBlockRenderer
{
    override UIElement Render()
    {
        ...
    }

    override void Parse(object?)  // TODO: what gets passed here?
    {
        ...
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


# Next steps

* API reviiew on each platform
* Any missing items/features of a specific renderer not accounted for?