# .NET Libraries for card creation
As we described in the Getting Started, an adaptive card is nothing more then a serialized JSON object of 
a card object model. To make it easy to manipulate the object model, we defined libraries which 
define a strongly-typed class hierarchy that makes it easy to serialize/deserialize JSON. <!-- make sure i didn't change the meaning of this last sentence-->

You can use any tooling that you want to create the adaptive card JSON.

## .NET 
The **AdaptiveCards** nuget package defines a class hierarchy for working with adaptive cards in .NET

### To install
```csharp
nuget install AdaptiveCards 
```

### Example: create

```csharp
var card = new AdaptiveCard();
card.Body.Add(new TextBlock() 
{
    Text = "Hello",
    Size = TextSizes.ExtraLarge,
    Color = TextColor.Attention
});
card.Body.Add(new Image() 
{
    Url = "http://someUrl.com/example.png"
});
```
### Example: save using JSON.NET
```csharp
var json = JsonConvert.SerializeObject(card);
```

### Example: load using JSON.NET
```csharp
var card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
```

