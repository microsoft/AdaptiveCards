# Types of cards

Below are a few common types of cards and their associated payloads.

> WDG DESIGN: Please help me create representative comps of these paylods in various windows experiences :)

1. News Article (Zuckerberg)
2. Bing Answer (Justin Trudeau)
3. Location (Starbucks)
4. Stock quote (S&P 500)
5. Video


# News Article

* Skype: https://app.zeplin.io/project/598cec21ff7f3d2b30d629a2/screen/5996293c707db5fe3a26a61a

```json
{
    "type": "AdaptiveCard",
    "version": "vNext",
    "attribution": {
        "logo": "http://bing.com/logo.png",
        "text": "Bing"
    },
    "category": "Business Insider",
    "title": "Here's how the CEOs on Fortune's '40 Under 40' list are doing leading the something or other",
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

# Bing Answer

* "Who is Justin Trudeau?"
* Skype: https://app.zeplin.io/project/598cec21ff7f3d2b30d629a2/screen/599620e26486e43b0e085739

```json
{
    "type": "AdaptiveCard",
    "version": "vNext",
    "attribution": {
        "logo": "http://bing.com/logo.png",
        "text": "Bing"
    },
    "title": "Justin Trudeau",
    "body": [
        {
            "type": "TextBlock",
            "text": "Prime Minister • Canada"
        },
        {
            "type": "TextBlock",
            "wrap": true,
            "text": "Born December 25, 1971 is a Canadian politician. He is the 23rd and current Prime Minister of Canada and leader of the Liberal Party"
        }
    ],
    "images": {
        "card": {
            "url": "http://findimage",
            "displayPreference": [ "vertical", "thumbnail" ]
        }
    }
}
```

# Starbucks

* Skype: https://app.zeplin.io/project/598cec21ff7f3d2b30d629a2/screen/599620e3388b2323e5bea88f

```json
{
    "type": "AdaptiveCard",
    "version": "vNext",
    "attribution": {
        "logo": "http://bing.com/logo.png",
        "text": "Bing"
    },
    "category": {
        "text": "Coffee Houses - $$",
        "selectAction": {} 
    },
    "title": "Starbucks",
    "body": [
        {
            "type": "TextBlock",
            "text": "4 stars Yelp (312)"
        },
        {
            "type": "TextBlock",
            "wrap": true,
            "text": "Born December 25, 1971 is a Canadian politician. He is the 23rd and current Prime Minister of Canada and leader of the Liberal Party"
        }
    ],
    "images": {
        "card": {
            "url": "http://findimage",
            "displayPreference": [ "vertical", "thumbnail" ]
        }
    }
}
```


# Stock quote

* TODO: does this card have a title or should it just be a body of TextBlocks?
* Skype: https://app.zeplin.io/project/598cec21ff7f3d2b30d629a2/screen/59972ca4e8176a3f7dd8ad53

```json
{
    "type": "AdaptiveCard",
    "version": "vNext",
    "attribution": {
        "logo": "http://bing.com/logo.png",
        "text": "Bing"
    },
    "category": {
        "text": "S&P 500 • S&P 500 Index",
        "selectAction": {},
    },       
    "title": "August 18, 2017",
    "body": [
        {
            "type": "TextBlock",
            "text": "2,293.08",
            "size": "extraLarge"
        },
        {
            "type": "TextBlock",
            "text": "▲ 0.52 (0.0235)",
            "size": "small",
            "color": "accent"
        }
    ]
}
```

# Weather



# Video

* TODO: Finish this schema
* See: https://docs.microsoft.com/en-us/dotnet/api/microsoft.bot.connector.videocard?view=botbuilder-3.8
* Skype: https://app.zeplin.io/project/598cec21ff7f3d2b30d629a2/screen/5997335a132b75ab89ef147e

```json
{
    "type": "AdaptiveCard",
    "version": "vNext",
    "media": {
        "contentType": "video",
        "url": "http://pig.avi"
    },
    "title": "Deep Sea Diver",
    "body": "Deep Sea Diver performs 'You Go Running' live during KEXP's Hood to Hood. The band is touring Ireland for the summer"
}
```