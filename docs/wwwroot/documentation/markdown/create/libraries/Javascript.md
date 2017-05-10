# Javascript
There is no Javascript library, but Javascript is already pretty good at manipulating JSON.

## Example: create
```javascript

var card = {
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
## Example: save 
```javascript
var json = JSON.stringify(card);
```

## Example: load
```javascript
var card = JSON.parse(json);
```

