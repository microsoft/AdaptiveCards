# Javascript
There is no javascript library, but for completeness 

## Example creating 
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
                    "url": "http://adaptivecards-staging.azurewebsites.net/api/cat"
                }
            ]
        }
    ]
};
```
## Example saving 
```javascript
var json = JSON.stringify(card);
```

## Example loading 
```javascript
var card = JSON.parse(json);
```

