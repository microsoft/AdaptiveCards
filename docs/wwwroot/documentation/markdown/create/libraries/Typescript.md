# Typescript libraries for card creation
As we described in the Getting Started, an adaptive card is nothing more then a serialized JSON object of 
a card object model. To make it easy to manipulate the object model, we defined libraries which 
define a strongly-typed class hierarchy that makes it easy to serialize/deserialize JSON.

You can use any tooling you want to create the adaptive card JSON.

The **microsoft-adaptive-cards** npm package defines a typescript library  for working with adaptive cards in Typescript

## To install
```
npm install microsoft-adaptive-cards
```
There are interface definitions in `schema.d.ts` which describe the shape of the schema.

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
                    "url": "http://adaptivecards.io/api/cat"
                }
            ]
        }
    ]
};
```

There is also an object model for creating cards.

```typescript
let card :IAdaptiveCard =  new AdaptiveCard();
card.body.add(new TextBlock() 
{
    text = "hello world"
});
```