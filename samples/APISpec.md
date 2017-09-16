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
nuget install AdaptiveCards
```

```csharp
// Should be same as library name
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
    int Major; Minor;
    string ToString();
}

// Version automatically provided by object model/renderer
AdaptiveVersion version = card.Version;

card.MinVersion = new AdaptiveVersion(major: 2, minor: 0);
card.FallbackText = "This card isn't supported. Please check your app for updates.";
```


## Parse from JSON string

```csharp
// TODO: Should this be an enum or class? TypeScript currently has as enum
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

ParseResult result = AdaptiveCard.FromJson(jsonString);
if (result.IsValid) {
    // Get card from result
    IList<ParseFailure> warnings = result.Warnings;
    AdaptiveCard card = result.Card;
} else {
    // Get errors?
    IList<ParseFailure> errors = result.Errors;
}
```

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

# Render card

## Instantiate a renderer

```csharp
AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();

// Get the schema version this renderer supports
string schemaVersion = renderer.SupportedSchemaVersion;
```



## Host Config
* TODO: What should the defaults be? Should they all share it? Should we embed a common hostConfig.json file in the binaries?
* TODO: I think HostConfig needs to be versioned as well for parsing?

```csharp
AdaptiveHostConfig hostConfig = new AdaptiveHostConfig();

// ... or parse
ParseResult<AdaptiveHostConfig> parseResult = AdaptiveHostConfig.FromJson(jsonString);

// We should provide a reasonable default if this property isn't set
renderer.HostConfig = hostConfig;
```

### Host Config options

*  TODO: Finalize all Host Config options
* Host Config will be the first run, set properties directly


```csharp
// Maximum image size to download
hostConfig.MaxImageSize = "200"; // kB

// Maximum payload size before we throw on Render or Validate
hostConfig.MaxPayloadSize = "10"; // kB

// TODO: more thorough review of these options is necessary
// https://github.com/Microsoft/AdaptiveCards/blob/master/samples/Themes/bing.json
```

## Native platform styling

```csharp
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


## Wire up Action events

1. DAN NOTES: Event even if we have a default action like showcard, considerations for inline vs popup
1. Ability to renfered the UI element 

```csharp

renderer.OnAction += ActionHander;

private void ActionHandler(object sender, ActionEventArgs e) {
    // What card was tapped
    // TODO: File issue to make sure we can get the card instance in UWP
    AdaptiveCard card = e.Card;

    if(e.Action is typeof(AdaptiveOpenUrlAction)) {
        // open URL
    }
    ...
}
```

### Option 2 (per Andrew's thread)

* In this model OpenUrl and ShowCard are implemented by default, and other actions would only show up if explicitly supported. We should show warnings for any actions we dropped. 

```c#
public class WindowsForegroundAction : IAdaptiveAction {
    string TypeName => "WindowsAction.Foreground";

    Action<Card> OnInvoke = (card) => ...; // activate app
}

renderer.RegisterAction<WindowsForegroundAction>((e) => {
    // activate app
})

```

## Inputs

// TODO: Document the fact that we do no input validation

```csharp
private void ActionHandler(object sender, ActionEventArgs e) {
    if(e.Action is typeof(SubmitAction) {
        
        // Includes data and all inputs    
        MyForm form = JsonConvert.DeserializeObject<MyForm>(e.UserInputs.AsJson());

    }
    ...
}
```

### Input data binding

* TODO: Move this to implementation spec
https://github.com/Microsoft/AdaptiveCards/issues/390

**Payload**

```json
"body": [
    {
        "type": "Input.Text",
        "id": "myTextInput"
    },
     {
        "type": "Input.Number",
        "id": "myNumberInput"
    }
],
"actions": [
    {
        "type": "Action.Submit",
        "data": { 
            "myCustomData": "5"
        }
    }
]


**Callback JSON**

```json
{
    "myCustomData": "5",
    "myTextInput": "Hello Input.Text",
    "myNumberInput": 5
}
```


## Generate UI tree

```csharp
// Render and let the UI stack download images 
// This means a card could be added to the app and then images load causing re-layout
RenderResult result = await renderer.RenderAsync(card, cancellationToken: null);

// TODO: Andrew suggested we move the action here to allow a customizable handler based on the type of card
result.OnAction((e) => {

});

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

RenderResult result = renderer.Render(card);
result.Errors
result.Warnings 

if(result.Suceeded) {
    FrameworkElement ui = result.FrameworkElement;
}
else {
    
    // host config warnings
    // images failed to load/timeout
    // TODO: what else?
}
```

### Prefetch images
Prefetch images and don't return until they are finished

// Custom Image resolver https://github.com/Microsoft/AdaptiveCards/issues/138

* DECISION: UWP will beta with prefetch true only, others will be best effort. False we will try to add during polish false for perf improvements. 
* ImageResolver will be part of 1.1 API

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
    static const TypeName = "ProgressBar";

    UIElement Render() {
        ...
    }

    void Parse(object?) {

    }
}

renderer.ElementRenderers[ProgressBarRenderer.TypeName] = new ProgressBarRenderer());
```

## Remove a renderer

```csharp
renderer.ElementRenderers.Remove("Action.Http");
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


## Custom properties on elements

* Should Host Config allow hosts to declare their custom extensions? We could build tooling around it if so

```json
{
    "type": "TextBlock",
    "flashing": true,
    "extensions": {
        "flashing": true
    }
}
```
