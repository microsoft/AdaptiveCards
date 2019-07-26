# Input.Rating Design Specification
### Author/Editor: Brook Tamir

## ABSTRACT 
This design note covers the Rating Control that will be implemented in a future version of Adaptive Cards.

## 1. SPEC LINK
https://github.com/microsoft/AdaptiveCards/blob/specs/3054-2/specs/elements/Input.Rating.md

## 2. DEPENDENCIES

### 2.1 CHOICESET
This feature’s implementation may depend on ChoiceSet, depending on the platform.

## 3. MAJOR DECISIONS
> Note: For card authors, the rating control will be a separate control named “Input.Rating”. This is about the implementation, not what the authors see.
It makes sense to extend ChoiceSet to implement Input.Rating in the JavaScript renderer, but that decision will vary depending on platform.

## 4. BACKWARDS COMPATIBILITY CONCERNS/FALLBACK
### 4.1 Backwards Compatibility
No breaking changes to existing features or APIs are introduced with this feature.
### 4.2 Fallback
On version 1.2 of the renderer, the `fallback` will be respected if provided by the card author. A potential default fallback is out of scope.

## 5. OBJECT MODEL
| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Input.Rating"` | Yes | Must be `"Input.Rating"`. | 1.3 |
| **iconSelected** | `uri` | No | Url to selected icon, defaults to star | 1.3 |
| **iconUnselected** | `uri` | No | Url to unselected icon, defaults to star | 1.3 |
| **maxValue** | `number` | No | How many icons show up, defaults to 5 | 1.3 |

## 6. PLATFORM SPECIFIC DETAILS
### 6.1 UWP
XAML (and therefore UWP) has a native rating control that has all our required functionality. To demo, install "XAML Controls Gallery" from the Windows Store and search "RatingControl". The documentation explains how to disable the growth animation that doesn't match our specifications: https://docs.microsoft.com/en-us/windows/uwp/design/controls-and-patterns/rating#additional-functionality
### 6.2 .NET WPF
We will leverage .NET WPF’s native rating control.
### 6.3 .NET HTML
There’s no native HTML rating control, so we may have to implement some of the interactivity in JavaScript.
### 6.4 Android
We will leverage Android’s native rating control.
### 6.5 iOS
There is no native iOS rating control, so we will have to implement it ourselves.
### 6.6 JavaScript
There’s no native JavaScript rating control, so we will have to implement it ourselves.

## 7. RENDERING DETAILS
Each platform should render the Rating input as it would any other input. Rating inputs are allowed anywhere in the card that other inputs are allowed.

## 8. TELEMETRY EVENTS

| Event | Priority | Notes |
| ----- | -------- | ----- |
| **AuthorCard** | P2 | Some hesitations from the team about plausible use cases
| **RenderCard** | P0 | [Essential] |
| **SubmitButtonClicked** | P0 | [Essential] |

## 9. TESTING/SAMPLES
### 9.1 SAMPLES
- v1.3\Elements\\**Input.Rating.json**

A simple 5-star rating case will be added under v1.3\Elements with the naming Input.Rating.json. This will demonstrate the (assumed) most common use case of sending a 1-5 star rating through an Action.Submit button.
```
{ 
  "type": "AdaptiveCard",
  "body": [ 
  	{ 
    	"type": "Input.Rating", 
    	"id": "userRatingSimpleDemo"
      } 
    } 
  ], 
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "version": "1.3" 
} 
```
- v1.3\Elements\\**Input.Rating.maxValue.json**

A simple 5-star rating case will be added under v1.3\Elements with the naming Input.Rating.json. This will demonstrate the (assumed) most common use case of sending a 1-5 star rating through an Action.Submit button.
```
{ 
  "type": "AdaptiveCard",
  "body": [ 
  	{ 
    	"type": "Input.Rating", 
    	"id": "userRatingMaxValue",
		"maxValue": 10
      } 
    } 
  ], 
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "version": "1.3" 
}
```
- v1.3\Elements\\**Input.Rating.iconUnselected.json**

A simple 5-star rating case will be added under v1.3\Elements with the naming Input.Rating.json. This will demonstrate the (assumed) most common use case of sending a 1-5 star rating through an Action.Submit button.
```
{ 
  "type": "AdaptiveCard",
  "body": [ 
  	{ 
    	"type": "Input.Rating", 
    	"id": "userRatingIconUnselected",
		"iconUnselected": http://img-prod-cms-rt-microsoft-com.akamaized.net/cms/api/am/imageFileData/RE2qVsJ?ver=3f74
      } 
    } 
  ], 
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "version": "1.3" 
} 
```

- v1.3\Elements\\**Input.Rating.iconSelected.json**

A simple 5-star rating case will be added under v1.3\Elements with the naming Input.Rating.json. This will demonstrate the (assumed) most common use case of sending a 1-5 star rating through an Action.Submit button.
```
{ 
  "type": "AdaptiveCard",
  "body": [ 
  	{ 
    	"type": "Input.Rating", 
    	"id": "userRatingIconSelected",
		"iconSelected": http://img-prod-cms-rt-microsoft-com.akamaized.net/cms/api/am/imageFileData/RE2r0Th?ver=5b7d
      } 
    } 
  ], 
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "version": "1.3" 
} 
```
- v1.3\Test\\**Input.Rating.json**

A full test file incorporating all edge cases:
	- all combinations of default and non-default number of ratings, rating icons(iconUnselected), and hover rating icons (iconSelected)
	- examples with only 1-2 rating choices
	- examples with many rating choices (enough to overfill the allotted space)
```
{ 
  "type": "AdaptiveCard", 
  "body": [ 
    { 
      "type": "Input.Rating", 
      "id": "userRatingIconsTest",
      "iconSelected": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
      "iconUnselected": "https://pbs.twimg.com/profile_images/988775660163252226/XpgonN0X_400x400.jpg"
    },
	{ 
      "type": "Input.Rating", 
      "id": "userRatingMaxValueTest10",
      "maxValue": 10
    },
	{ 
      "type": "Input.Rating", 
      "id": "userRatingMaxValueTest1",
      "maxValue": 1,
      "iconSelected": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
    },
	{ 
      "type": "Input.Rating", 
      "id": "userRatingMaxValueTest2",
      "maxValue": 2,
      "iconUnselected": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
    },
	{ 
      "type": "Input.Rating", 
      "id": "userRatingMaxValueTest20",
      "maxValue": 20,
      "iconUnselected": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
    },
	{ 
      "type": "Input.Rating", 
      "id": "userRatingMaxValueTestNegative1",
      "maxValue": -1,
      "iconSelected": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
      "iconUnselected": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
    }
  ],
  "$schema": "http://adaptivecards.io/schemas/adaptive-card.json", 
  "version": "1.3" 
} 
```

### 9.2 SHARED MODEL
Add the json samples to the shared model unit tests.

### 9.3 UWP
Add coverage of the json samples to the UWP test app.

## 10. SEQUENCE DIAGRAM
<img src="https://i.imgur.com/N3KT9oW.png"  width="600" height="auto">
