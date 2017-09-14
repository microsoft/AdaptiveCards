# Justin Timberlake said it best

> I'm bringing semantics back
>
> You other cards don't know how to act


## Why?

Adaptive Cards 1.0 does a fantastic job addressing the long-tail of completely custom cards that developers asked for.

That said, it isn't super easy or staight-forward to create every-day cards with some text and an image or two. 

Nor is it possible to author a card that automatically adapts to multiple surfaces. 

![cards in windows](https://tg9blq.dm2301.livefilestore.com/y4phy89csvKi5yZnhOSVXReEEw3JJP7gMB_buOedrwYNe5J_V6ypfPsm_V6oOkP1JFpr-1vR1OWJcCVsWfftFYLjswu3gFfzOpUNIGrTz-0VCdIy1h8wKRaze-5Tsgow7oJ0kg_HwYo4wO8n3nDJwAK0J8CRhhMqyvomYsqw7hcBSLIcLyEmcw74jr94yvJVvVK7CmRxU1tQcccNVkv85KBVw/semantic-cards-windows.png?psid=1)

The **experience owners** above have their own visual identity and visual constraints -- and should be able to render adaptive cards in the best way for them. Similarly, **card authors** should be able to write a single card payload that truly adapts to the host experience. 

## Benefits of more semantics

* **Portability** - more structure means a card can be interpreted by hosts with very different visual limitations/constraints
* **Approachability** - common cards with some text and an image shouldn't _require_ complex structures like ColumnSet
* **Interoperable** - semantic attributes make Adaptive Cards completely interchangable with OpenGraph/Twitter cards
* **Intelligence** - semantic information gives us a bit more ability to reason over the content

> IMPORTANT: Before I go on, I want to stress that everything here is purely additive and optional. For developers who want to custom draw their own body, Adaptive Cards will remain the leader in this space. 



# Schema additions

This proposal expands on what it means to be a "card". Today we've defined a card as a free-form "body" and some "actions". 

Based on feedback from host apps, card authors, and industry analysis, we've identified a few additional top-level attributes to AdaptiveCard.

## Attribution
Card content that is attributed to a third-party. E.g., Bing, Twitter, etc. It also provides a `selectAction` to make the element invokable.

![attribution](https://tg9blq.dm2301.livefilestore.com/y4pHnuywgNAjpw7vgxPSVMMLFIfeKg0cbJhN_rVv4nu08omRAs_ORs8aY1OCrmBELIPeqOqhiiCHbmOEFHaZTCV6690w_omd5uKITCri0GroQ44h7J82qw6vQ5qIQuLLwqrm7XHn6ENEge2O3qlDvdkvTwO5VdweZpL2Zp4BYVsFY56NILh8LxgMTXByOCLSLZtwhZ2sA4sEwmYCw2cCteybw/card-attribution.jpg?psid=1)

### Payload 
```json
{
    "type": "AdaptiveCard",
    "attribution": {
        "logo": {
            "url": "http://bing.com/logo"
        },
        "text": "Bing",
        "selectAction": {}
    }
}
```

### Host Config
```json
 // todo
```

### Renderer Requirements
* TODO: Where does it go in the card? How can hosts change it?


## Title/Subtitle
Cards often (but not always) have a title as an entry point to the content. By standardizing these properties we allow hosts to describe their title visual properties making it very easy for a card to port around and retain visual consistency within the host.

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
            "textWeight": "bolder",
            "wrap": true,
            "maxLines": 2
        },
        "subtitle": { // TextBlockConfig
            "wrap": true,
            "maxLines": 3
        }
    }
}
```

### Renderer Requirements
* Extract the strings and insert TextBlocks at the top of the `body` with the appropriate host config styles applied.


## Category
Cards occasionally fall into a particular category, usually with a specific UI treatment and a touch target.

![category](https://tg9blq.dm2301.livefilestore.com/y4py0WlIrGyNmgC-eyQLjEzA19y4kXqoEVLLuJlqD8gWc6S5QsTuUeQS2s6_kRE1b7SHGxISI6j4vqBY7rHeDLUGE8tri35zbt0tX9v2BSdwQbBvCuDWuty3dT9-jnf3ld9TKE5Y9NfmCECC8HXRtpHvm3latAvsOmh0ObJytDsFdeDMe17MKgYC6FV5HVbba2YaDgIobxmMQ8hm2TgYoAI2g/card-category.jpg?psid=1)

For feeds of cards, like Action Center, this information can be used to group cards together. E.g., Outlook notifications can be grouped by email accounts.

### Seen in
* Skype
* Windows (Notifications, NTP)

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

Cards can be broadly considered to have three types of images. 

### Background image
A specialized type of image that covers the entire background of the card.

![bg](https://tg9blq.dm2301.livefilestore.com/y4pClxjM6TozOjzqkEaFtrVobVW_X5N40pf02AetSLH_PCajarWTXPXRRhNmA0srUPOS9E0ZZHBFDRwA8UkiKCqyz7Be7LWU3G_5wCXS6KNumi9EZnnPdtVSa4yC8g45_yStufHX25CZh4vs9ZVIawyTeDHvQQpfZM5gqnp-E_am88LIZyIBdYh_oyzun-dlFkQQ4mRIHjLSqGId07eSpRAgg/card-weather.jpg?psid=1)

> NOTE: the proposals below are a **breaking change** from 0.5 and would **remove** the `backgroundImage` property on `AdaptiveCard` and move it into a more robust object.

**OPTION 1**

```json
{
    "type": "AdaptiveCard",
    "images": {
        "background": {
            "url": "http://",
            "overlay": "light|dark",
            "opacity": 0.7
        }
    }
}
```

**OPTION 2**
This optional more naturally enables background color, and also aligns closer to the concept of backgrounds for `Columns`/`Containers`.

```json
{
    "type": "AdaptiveCard",
    "background": {
        "color": "",
        "image": {
            "url": "",
            "overlay": "light|dark",
            "opacity": 0.7
        }
    }
}
```


### Profile image

A specialized type of image usually on the left side of the card, typically showing a contact or person who generated the card, e.g., an IM or email from a contact 

![profile](https://tg9blq.dm2301.livefilestore.com/y4po6WND489AUw6l-Twoay730f5bR1RKBqudzNQ9kN7-DLzdz16nO6NjO47og-X9L2ncwIcEK2pdDTVQFZ87LIJVULXtkbxhg9RyzGiVrD35pDFf7oigKZyMeCRPugiBP46iSoRkvnElA1d0cOmRL04uvPPGiCxp8xO76APAEuV8UB9C9TwwtbRS5Yt9V2_Xi1WhD44KMG4AhbaOPt0CqP9jQ/card-profileimage.png?psid=1)

```json
{
    "type": "AdaptiveCard",
    "images": {
        "profile": {
            "url": "http://",
            "style": "person"
        }
    }
}
```

### Card image
The "hero" image associated with the card content. Host apps are free to use this image however they wish: 
* full width at the top of the card
* vertically along the right side
* a small thumbnail
* inline with the content
* or even as the background (like Timeline)

Card authors can influence the placement using the `displayPreference` property. 

![images](https://tg9blq.dm2301.livefilestore.com/y4plSLQJ5lL5BaiDXMDeov5ru32ODMPa5gvNAx75vtMoqBByMsVC5yjsKpYPlO-hI4yaFbmICOBfMCWcCHgSmsFUe8SddIjITKMFIHkwkA5CehNUcltx7h1JpfwxteiFafUrmmwlPaxbM27xsvYLHO-SgrhvHPD_wPpGcyH_90AUgwGZZDalkjB-hCWoudaOaauJoGR_jY8SFXfCspI4zg4kQ/card-images.jpg?psid=1)

```json
{
    "type": "AdaptiveCard",
    "images": {
        "card": { 
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

#### DisplayPreference
Many images are best suited for a particular aspect ratio, so a card author should be able to explicitly restrict or influence where the image appears. 

**Removing** an option from the array explicitly removes support for the aspect ratio. E.g., if a developer _only_ wants the image displayed horizontally they would set `displayPreference: [ "horizontal" ]`

> FUTURE: In the future we could use image analysis to find best placement and crop


Preference | Requirement
--- | --- 
vertical | X
horizontal | Y
thumbnail | Z
full | A

#### Renderer requirements

* The card image causes the `body` content to reflow based on where it's placed

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

## Timestamp
This one I'm not entirely convinced on, but happy to take feedback from folks. 

### Seen in
* Skype
* Notifications

### Payload
* TODO: Can bot developers provide/override this?

```json
{
    "type": "AdaptiveCard",
    "timestamp": "2016-12-13T20:45:00Z"
}
```

### Host Config
```json
{
    "adaptiveCard": {
        "timestamp": {
            "format": "friendly|explicit" // "1 hour ago"
        } // TimestampConfig, based on TextBlockConfig
    }
}
```

### Renderer Requirements
* TODO


## SelectAction
This property makes the entire card a touch target.

### Payload
```json
{
    "type": "AdaptiveCard",
    "selectAction": {}
}
```

## Secondary actions


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
* If an `Image` is a string, create an `Image` and set the `url` to the string value

## All together

```json
{
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "vNext",
    "timestamp": "2016-12-13T20:45:00Z",
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

# `Extensions` alternative


An alternative to the proposal below would be to take some of the concepts and group them into an `extensions` or `metadata` array. One advantage of this design would allow hosts to pick-and-choose what pieces of a card are applicable to them, including adding new "parts".

```json
{
    "type": "AdaptiveCard",
    "version": "vNext",
    "extensions": [
        {
            "type": "Attribution",
            "logo": "",
            "text": "Bing"
        },
        {
            "type": "Category",
            "text": "Politics",
            "selectAction": {}
        },
        {
            // Showing a custom Category with additional data, some spec issues here with this concept
            // Should it have a different name than Category?
            "@context": "http://google.com/cards/now",
            "type": "Category",
            "text": "Bing",
            "subtext": "",
            "image": ""
        },
        {
            "@context": "http://microsoft.com/windows/notifications",
            "type": "Audio",
            "src": "",
            "loop": "twice"
        },
    ],
    "metadata": [
        {
            "@context": "http://schema.org",
            "@type": "LocalBusiness",
            "name": "Microsoft",
            "address": {
                "@type": "Address",
                "line1": "1 Microsoft Way"
            }
        }
    ],
    "title": {
        "text": "Here's how the CEOs on Fortune's '40 Under 40' list are doing leading the something or other",

        "extensions": [ // element extensions. Pretty verbose. Maybe extensions only exist at the card level?
            {
                "@context": "http://microsoft.com/windows/notifications",
                "@type": "ToastText",
                "maxLines": 2,
                "wrap": true
            }
        ],

        "microsoft.notification.maxLines": 3, // and we use additionalProperties at element level?
        "microsoft.notification.wrap": true, 

        "microsoft.notification": { // or this form of additional property?
            "maxLines": 3,
            "wrap": true
        }
    },
    "body": "Fortune released its annual '40 Under 40' list of the most influential people under the age of 40, which includes Mark Zuckerberg.",
    "images": {
        "card": {
            "url": "http://findimage",
            "displayPreference": [ "vertical", "thumbnail" ]
        }
    },
    "actions": [
        {
            "type": "Action.Submit",
            "title": "Action One"
        }
    ]
}
```
