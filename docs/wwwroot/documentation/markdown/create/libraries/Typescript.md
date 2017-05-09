# Typescript libraries for creating cards
As we described in the Getting Started, an adaptive card is nothing more then a serialized JSON object of 
a card object model. To make it easy to manipulate the object model, we defined libraries which 
define a strongly-typed class hierarchy that makes it easy to serialize/deserialize JSON. <!-- make sure i didn't change the meaning of this last sentence-->

You can use any tooling you want to create the adaptive card JSON.

The **adaptive-cards** npm package defines a Typescript library for working with adaptive cards in Typescript.

## Install
```javascript
npm install adaptive-cards
```

## Example: create
```javascript
TODO
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
## Example: save 
```javascript
TODO
var json = JsonConvert.SerializeObject(card);
```

## Example: load
```
var card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
```


