# Input.Rating Design Specification
### Author/Editor: Brook Tamir

## ABSTRACT 
This design note covers the Rating Control that will be implemented in a future version of Adaptive Cards.

## 1. SPEC LINK
https://github.com/microsoft/AdaptiveCards/blob/specs/3054-2/specs/elements/Input.Rating.md

## 2. DEPENDENCIES

### 2.1 CHOICESET
One of the two options for this feature’s implementation depends on ChoiceSet.

## 3. MAJOR DECISIONS
> Note: For card authors, the rating control will be a separate control named “Input.Rating”. This is about the implementation, not what the authors see.

### 3.1 Implementation Option 1: Extending Input.ChoiceSet

This would make the implementation simpler, but could potentially lead to issues if there are changes in either ChoiceSet or the Rating Control in the future due to (somewhat) tighter coupling. However, it's not clear whether this is likely to cause any issues.

[in progress]

| Pros | Cons |
| ---- | ---- | 
| Ease of implementation (depending on platform) | Tighter coupling |
| [Pro] | [Con] |
| [Pro] | [Con] |

### 3.2 Implementation Option 2: Making a Brand New Control
This would ensure 

[in progress]

| Pros | Cons |
| ---- | ---- | 
| Looser coupling | [Con] |
| [Pro] | [Con] |
| [Pro] | [Con] |

## 4. BACKWARDS COMPATIBILITY CONCERNS/FALLBACK
### 4.1 Backwards Compatibility
Sending cards with Input.Rating to previous versions of the renderers will result in the rating control being rendered as a standard Input.ChoiceSet.
No breaking changes to existing features or APIs are introduced with this feature.

## 5. OBJECT MODEL
| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `"Input.Rating"` | Yes | Must be `"Input.Rating"`. | 1.0 |
| **iconSelected** | `uri` | No | Url to selected icon, defaults to star | 1.0 |
| **iconUnselected** | `uri` | No | Url to unselected icon, defaults to star | 1.0 |
| **maxValue** | `number` | No | How many icons show up, defaults to 5 | 1.0 |

## 6. PLATFORM SPECIFIC DETAILS
### 6.1 UWP
XAML (and therefore UWP) has a native rating control that has all our required functionality.
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
Each platform should render the [in progress]

## 8. TELEMETRY EVENTS
- AuthorCard
- RenderCard
- SubmitButtonClicked

## 9. TESTING
### 9.1 SAMPLES
- A simple 5-star rating case will be added under v1.3\Elements with the naming Input.Rating.json. This will demonstrate the (assumed) most common use case of sending a 1-5 star rating through an Action.Submit button.
- A full test file incorporating all edge cases:
	- all combinations of default and non-default number of ratings, rating icons, and hover rating icons
	- examples with only 1-2 rating choices
	- examples with many rating choices (enough to overfill the allotted space)

### 9.2 SHARED MODEL
Add the json samples to the shared model unit tests.

### 9.3 UWP
Add coverage of the json samples to the UWP test app.
