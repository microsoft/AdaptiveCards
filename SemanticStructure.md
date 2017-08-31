# Justin Timberlake said it best

> I'm bringing semantics back
> You other cards don't know how to act


## Why?

Adaptive Cards 1.0 does a fantastic job addressing the long-tail of completely custom cards that developers asked for.

That said, it isn't super easy or staight-forward to create common every-day cards. Nor is it possible to author a card that automatically adapts to multiple surfaces that vary significantly in their rendering bounds.

> IMPORTANT: Before I go on, I want to stress that everything here is purely additive and optional. For developers who want to custom draw their own body, Adaptive Cards will remain the leader in this space. 

* **Portability** - more structure means a card can be delivered to hosts with very different display limitations/dimensions
* **Approachability** - a simple card like sharing a news article is now very straight-forward
* **Interoperable** - this attributes make Adaptive Cards completely interchangable with OpenGraph/Twitter/Messenger templates
* **Intelligence** - semantic information gives us a bit more ability to reason over the content


# Schema additions


## Attribution

### Seen in
* Skype 
* Windows (Timeline, Notifications, NTP)

### Payload 
```json
{
    "type": "AdaptiveCard",
    "attribution": {
        "logo": {
            "url": "http://"
        },
        "text": "Cortana",
        "selectAction": {}
    }
```

### Host Config
```json
 // todo
```

### Renderer Requirements
* TODO: Where does it go in the card? How can hosts change it?


## Timestamp

### Seen in
* Skype? 
* Notifications

### Payload
* TODO: Can bot developers provide/override this?

```json
{
    "type": "AdaptiveCard",
    "timestamp": "1 hour ago"
}
```

### Host Config
```json
{
    "adaptiveCard": {
        "timestamp": {} // TextBlockConfig
    }
}
```

### Renderer Requirements
// todo



## Title/Subtitle

### Seen in
* Skype
* Windows (Timeline, Notifications, NTP)

### Payload
```json
{
    "type": "AdaptiveCard",
    "title": "Mother's day floral shop",
    "subtitle": "Treat your mother well"
}
```

### Host Config
```json
{
    "adaptiveCard": {
        "title": { // TextBlockConfig
            "wrap": true,
            "maxLines": 3
        }
    }
}
```

### Renderer Requirements
* Extract the strings and insert TextBlocks at the top of the `body` with the appropriate host config styles applied.


## Category

### Seen in
* Skype
* Windows (Timeline, Notifications, NTP)

### Payload
```json
{
    "type": "AdaptiveCard",
    "category": {
        "text": "Home & Garden",
        "selectAction": {}
    }
}
```

### Host Config
```json
{
    "adaptiveCard": {
        "category": { // TextBlockConfig
            "casing": "default|upper|lower",
            "underline": true
        } 
    }
}
```

### Renderer Requirements
* Host Config TextBlockConfig needs 2 additional properties given the current mocks (upper case and underline)
* TODO: Is this the first thing in the card? Action Center will need to remove this entirely, but they could walk the object model and do that

## Images

This feature defines the three types of images commonly seen in Cards and groups them together into a single object. 

> NOTE: this proposal is a **breaking change** from 0.5 and would **remove** the `backgroundImage` property on `AdaptiveCard` and move it into the proposed object

* **Background image** - a specialized type of image that covers the entire background of the card
* **Profile image** - a specialized type of image on the left side of a card typically showing a contact or person who generated the card, e.g., an IM or email from a contact 
* **Card image** - this is the generic image associated with a card, commonly seen in videos, articles, music, places, etc

![Images](https://bxqbjg.dm2301.livefilestore.com/y4pn86HWEvQrEFJTgehRMuFS32jkU3AYBiLcmE2IQypmbwB22Y6yL9v1xxuXDExclHG2_K3Xb-E1xMxGn9OMEaqjfOlaPbQ8TtHw749zL3mftNAUOmSZW3x0rqfCEXTizBgOecm2PydLq42Im-dKpzoImAVf3ewPW4Ld_0qVlu0QFFRrmbytEigBcw0_z_FWdZa/card-images.png?psid=1)

### Seen in
* Skype
* Windows (Timeline, Notifications, NTP)

### Payload
```json
{
    "type": "AdaptiveCard",
    "images": {
        "background": { // "type": "BackgroundImage"
            "url": "http://",
            "overlay": "dark",
            "opacity": 0.7
        },
        "profile": { // "type": "Image"
            "url": "http://",
            "style": "person"
        },
        "card": { // "type": "CardImage"
            "url": "",
            "displayPreference": [
                "vertical",
                "horizontal",
                "thumbnail",
                "full" // aka background
            ]
        }
    }
}
```

### DisplayPreference

 Preference | Requirement
 --- | --- 
vertical | X
horizontal | Y
thumbnail | Z
full | A

### Host Config
```json
{
    "adaptiveCard": {
        "images": {
           "background": { // new BackgroundImageConfig
               "isSupported": true,
               "opacity": 0.7,
               "overlay": "dark"
           },
            "profile": {}, // ImageConfig
            "card": { // new CardImageConfig
                "displayPreference": [ // omit ones they don't want to support, even if developer provides them
                    "vertical",
                    "horizontal",
                    "thumbnail",
                    "full"
                ]
            }
        } 
    }
}
```

### Renderer Requirements
* Images 
* FUTURE: Image analysis to find best placement and crop

## AdaptiveCard SelectAction
This property makes the entire card a touch target.

### Payload
```json
{
    "type": "AdaptiveCard",
    "selectAction": {}
}
```

## Secondary/Overflow actions

```json
{
    "type": "AdaptiveCard",
    "actions": [
        {
            "type": "Action.Submit",
            "title": "Snooze",
            "placement": [ "actionBar", "overflow" ]
        },
        {
            "type": "Action.Submit",
            "title": "Remind me later",
            "placement": [ "overflow" ]
        }
    ]
}
```


## String shortcuts for common payloads

We can make it easier/less verbose for common operations.

### Payload
```json
{
    "type": "AdaptiveCard",
    "body": "The quick fox was fast I think",
    //      ^ creates a TextBlock and sets the text property
    "images": {
        "card": "http://" 
        //      ^ creates an Image and sets the url property
    }
}
```

### Renderer Requirements
* If `body` is a string, insert a default `TextBlock` and set the `text` to the string value
* If an `Image` is a string create an `Image` and set the `url` to the string value

## All together

```json
{
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "vNext",
    "timestamp": "1 hour ago",
    "attribution": {
        "logo": {
            "url": "http://"
        },
        "text": "Cortana",
        "selectAction": {}
    },
    "title": "Mother's day floral shop",
    "subtitle": "This past Mother's Day, esteemed florist",
    "category": {
        "text": "Home & Garden",
        "selectAction": {},
        "extensions": {
            "Microsoft.Windows.Notification.Id": "MyHeaderId"
        }
    },
    "images": {
        "background": { // "type": "BackgroundImage"
            "url": "http://",
            "overlay": "dark",
            "opacity": 0.7
        },
        "profile": { // "type": "Image"
            "url": "http://",
            "style": "person"
        },
        "card": { // "type": "CardImage"
            "url": "",
            "displayPreference": [
                "vertical",
                "horizontal",
                "thumbnail",
                "full"
            ],
            "crop": "center"
        }
    },
    "body": "Hello World",
    "selectAction": {},
    "actions": [
        {
            "type": "Action.Submit",
            "title": "Snooze",
            "placement": [ "commandBar", "overflow" ]
        },
        {
            "type": "Action.Submit",
            "title": "Remind me later",
            "placement": [ "overflow" ]
        }
    ]
}
```