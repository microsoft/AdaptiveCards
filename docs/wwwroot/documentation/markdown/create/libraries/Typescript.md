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
There are interface definitions in schema.d.ts which describe the shape of the schema

```typescript
let card :IAdaptiveCard = {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "Container",
            "items": [
                {
                    "type": "TextBlock",
                    "text": "Meow!"
                },
                {
                    "type": "Image",
                    "url": "http://adaptivecards-staging.azurewebsites.net/api/cat"
                }
            ]
        }
    ]
};
```

There is also an object model for creating cards which can be used

```typescript
let card :IAdaptiveCard =  new AdaptiveCard();
card.body.add(new TextBlock() 
{
    text = "hello world"
});

```

