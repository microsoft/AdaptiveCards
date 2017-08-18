
# Instantiate card

```csharp
using AdaptiveCards;
```

## From object model

```csharp
var card = new AdaptiveCard();
card.Body.Add(new AdaptiveTextBlock());
```

## Parse card from JSON string

```csharp
var card = AdaptiveCard.FromJson(jsonString);
// TODO: Should this throw if malformed json?
```

### Validate parse errors

* Type casting errors (e.g., bool expected and we got a string)

```csharp
var result = card.Validate();
if(!result.IsValid) {
    var errors = result.Errors;
}
```

### Validate against Host Config
* Rule failures (e.g., maxActions set to 2, but card contained 3) 
* Unknown type encountered, so was dropped. (Should this happen at render time?)

```csharp
var result = card.Validate(customHostConfig);
```

# Render card

## Instantiate a renderer

```csharp
var renderer = new XamlCardRenderer();
```

## Set Host Config

```
renderer.HostConfig = myHostConfig;
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

## Render 

* What about images failing to download? 
* We need to support a scenario where we don't callback until the images are done

```csharp
var ui = renderer.Render(card);
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
}

card.SetRenderer("TextBlock", new new CoolTextBlockRenderer());
```

## Render a custom element

```csharp
card.SetRenderer("ProgressBar", new ProgressBarRenderer());
```

## Override markdown processing

```csharp
renderer.ProcessMarkdown = MarkdownHandler;

private string MarkdownHandler(string text) {
    // process markdown
}
```

## Custom properties on elements
