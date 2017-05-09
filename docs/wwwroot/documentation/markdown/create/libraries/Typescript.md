# Typescript Libraries for creating cards
As we described in the getting started section, an adaptive card is nothing more then a serialized json object of 
a card object model.  To make it easy to manipulate the object model we have defined some libraries which 
define a strongly typed class hierarchy that is easy to serialize/deserialize json.

You can use any tooling that you want to create the adaptive card json.

The **adaptive-cards** npm package defines a typescript library  for working with adaptive cards in Typescript

## To install
```
npm install adaptive-cards
```

## Example creating 
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
## Example saving 
```javascript
TODO
var json = JsonConvert.SerializeObject(card);
```

## Example loading 
```
var card = JsonConvert.DeserializeObject<AdaptiveCard>(json);
```


