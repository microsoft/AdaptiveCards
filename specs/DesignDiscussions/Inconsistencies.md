# Inconsistencies in Adaptive Cards platforms

## Motivation

### Goals

* Provide a platform for experiences that allows card authors to write a card once and be confident that the card will be rendered with fidelity and is equally interactable on all devices
* Make it easy for developers to understand how extending Adaptive Cards impacts consistency
* Make it possible for third party developers to implement compliant and behaviorally consistent renderers for new platforms
* Structure code and processes such that inconsistencies are very likely to be found before they are shipped

### Non-Goals

* Provide pixel-perfect rendering across all platforms
* Provide identical behaviors in all situations across all platforms
* Make it impossible for developers to make a consistency mistake
* Full coverage of iOS-specific difficulties, which are covered in a separate spec (contact @paulcam206 for link since it's internal content).

### Some context

Adaptive Cards is currently available on these platforms:

* [UWP](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/uwp/getting-started) (Available in all WinRT-projected languages; renders using XAML)
* .Net (Available in all .Net languages; renders using [HTML](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/net-html/getting-started) or [WPF](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/net-wpf/getting-started))
* [Android](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/android/getting-started) (Java; renders using native Android platform)
* [iOS](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/ios/getting-started) (ObjC; renders using native iOS platform)
* [Javascript](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/javascript/getting-started) (renders using HTML/JS/CSS)
* [ReactNative](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/react-native/getting-started) (community renderer)
* Flutter (community renderer)

This list of platforms represents at least 7 distinct implementations of Adaptive Cards at the rendering level. At each decision point along the way during implementation, the Adaptive Cards developer (i.e. someone writing code to parse or render Adaptive Cards) risks implementing behavior that diverges from intended behavior. One of the biggest selling points for Adaptive Cards is our ability to render across our supported platforms in a way that at once feels native to the supported platform while also having a look and feel that's representative of the card author's intent. Indeed, portability is one of our [core goals](https://docs.microsoft.com/en-us/adaptive-cards/#goals). Each time an inconsistency sneaks into the platform, it risks introducing costs to our partners. These costs have real consequences for the adoption of Adaptive Cards in the market:

* Existing customers are less likely to adopt new versions of Adaptive Cards, even if they want the newer features (see slow adoption of newer versions by Teams)
* Potential new customers might be scared to adopt Adaptive Cards altogether if there's a consistency or stability problem (perceived or real), since cross-platform capabilities are central to our value proposition
* When existing customers *do* adopt new versions, they may end up having to spend extra time testing new versions and then deal with new bugs when *their* customers complain

Issues that impact Microsoft partners are tracked with labels in our repo:

* [Teams Mobile](https://github.com/microsoft/AdaptiveCards/labels/Msft-TeamsMobile)
* [Teams Integration](https://github.com/microsoft/AdaptiveCards/labels/MsftTeams-Integration)

In order to maintain our [pledge of cross-platform capability](https://docs.microsoft.com/adaptive-cards/resources/principles), and in order to support all of our partners and customers, we **must** take a strong stance against the introduction of inconsistencies in Adaptive Cards. 

By default, every feature and quirk should have identical behavior across all of our platforms. There will be times, of course, where platform-specific differences may make sense. However, these differences must be intentional. They need to be discussed and documented. To further reduce the likelihood of divergent implementations, we should share code whenever possible.

## Types of inconsistencies

### Parsing

Parsing Adaptive Cards poses an interesting problem for us. Since we're a JSON-based format, our Typescript renderer natively supports parsing. One can directly interact with the structure of a card's format natively, there's not really any "parsing" involved. Sure, we build up a higher-order abstraction on top of this format, but the nuts-and-bolts of *actually reading* the JSON text and interpreting it into a usable data structure is done transparently under the hood. In contrast, our .NET offering uses the Newtonsoft.JSON parsing library which offers a specialized databinding model. In shared model platforms, we use a library called `jsoncpp` to handle the parsing details. This structure immediately evokes the types of issues one might expect to arise:

* Differences in encoding handling (autodetecting UTF-8 or dealing with OS-specific line endings `\r`, `\r\n`, and `\n`)
* Features that are easy to implement on one platform might be quite difficult to implement on another. This can sometimes lead to compromised implementations that end up shipping without being brought to spec, or sometimes features that just don't get implemented across all platforms (!!)
  * This can also present a form of schedule risk because if it so happens that the last platform ends up being the hardest, you can end up with more work than calendar
* Type coercion in Javascript can cause it to be more permissive than other platforms leading to some constructs like `maxlines: "2"` being valid in JS, but invalid in, say, UWP (if JS code isn't carefully written -- we do, of course, author in Typescript, but we do also have to keep these problems in mind)
* Distinct implementations means that defaults can vary by platform (e.g. whether the `TextBlock` `wrap` property defaults to `true` if not specified)
* Differing choices made by devs at implementation time can lead to divergent behaviors (e.g. whether an invalid property value is silently dropped vs. emitting a warning vs. failing to parse the card)
* Supporting libraries and platform affordances available to us can ease or speed up implementation, but can also be the source of inconsistencies (e.g. differences in how a dev constructs .NET's `DateTime`, UWP's `DateTime`, C++'s `std::chrono::time_point`, and Javascript's `Date` -- instantiating each object with, for example, a string, can vary in permissivity)
  * Indeed, we've had a few issues arise from differences between a hand-rolled solution and a pre-rolled solution (e.g. date/time handling (#1915) and support for markdown (#1984))

### Rendering

Rendering presents another avenue by which inconsistencies can sneak into Adaptive Cards. Some of these problems can be pretty tricky to solve.

* Multiple implementations means that "gotcha" scenarios might not always be covered or may be covered inconsistently (e.g. what happens when you combine `maxLines`, markdown lists, and `wrap: true`?)
* Platform-provided controls can vary widely in their behaviors and support. Even if divergent behavior is caught during implementation, it may be difficult or tricky to solve completely

## Proposals

* (P0) Change processes to prevent new inconsistencies from ever happening:
  * Motivation: Inconsistencies are caught before they ship
  * Tasks: 
    * New bugs automatically filed with `inconsistency` tag, which is only removed once it's determined that the issue is *not* a consistency issue
    * We can't ship if an `inconsistency`-tagged bug hasn't been resolved for this release
    * Features that need implementation across all platforms are merged to a single branch and PR'd/tested for inconsistencies before being allowed to merge upstream
      * Each feature is championed by a single dev or PM, who owns the feature from conception to first ship
      * Champion creates a branch off of `master` (or whichever main branch is appropriate), naming it `feature/featureName` (let's call this the "feature branch")
      * The champion is responsible for keeping the feature branch up to date with respect to `master` (or main branch)
      * Workflow:
        1. People working on the feature create a new branch off of the feature branch (let's call it the "working branch")
        1. When feature work in a working branch is completed, it is PR'd to the feature branch
        1. **The first PR to feature branch must include robust test cards that not only exercise the "golden path" for a feature, but every reasonable corner case. This PR must also include schema docs.**
        1. Subsequent PRs to the feature branch follow standard review procedures before being merged
        1. When all work is completed and merged to the feature branch, a PR is issued against `master`. In this PR, a final test pass and code review are performed. 
          * Consider creating a checklist that needs to be completed prior to merge.
        1. When the PR is clean, the feature is ready to ship, so it's merged into `master`.
* (P1) Provide a new tool that allows easy testing of card payloads across all renderers:
  * Motivation: Allows for the easy directed testing of feature consistency
  * Tasks: 
    * If shipped for public use, this could be a nice addition to the designer to allow card authors to preview their cards in a variety of renderers
    * Could be used in tests for per-platform visual verification
    * Per-platform accessibility trees could also be generated by this tool to allow for cross-plat verification
* (P1) Make strong decisions around defaults, required properties, and parser/renderer behaviors: 
  * Motivation: When these decisions are fully documented, it's easier for a line-level dev to choose correct behavior, meaning that it's more intuitive as to what the correct behavior should be.
  * Tasks: 
    * Document decisions publicly & in code as appropriate
    * Blog about decisions & philosophy
    * Review current behavior and make breaking changes as needed
* (P1) Inconsistency-focused bug bash
  * Motivation: There are certainly more inconsistencies that have yet to be found. It's better to deal with them all at once if possible.
  * Tasks: 
    * Ensure test cards cover scenarios
* (P2) Reduce code duplication:
  * Motivation: Fewer implementations means fewer inconsistencies
  * Tasks:
    * Experiment with the shared model as Javascript (e.g. via [emscripten](https://emscripten.org/))
    * Move .NET from using Newtonsoft.JSON to using the shared model via P/Invoke (Note that this will have impacts on partners. It's likely that this move will only make sense if Javascript is also using the shared model)
* (P2) Parsing/rendering documentation update pass -- leave no ambiguity
  * Motivation: Makes it easier for third parties to be consistent
* (P2) Blog posts about inconsistencies, how we're addressing them, and how to avoid them when implementing custom parsing/rendering or implementing an entirely new stack (makes it easier for third parties to be consistent)
  * Motivation: Better visibility for third parties

## Specific bugs

[List of inconsistency bugs](https://github.com/microsoft/AdaptiveCards/issues?utf8=%E2%9C%93&q=is%3Aissue+label%3AInconsistency+):

### Control behaviors, rendering, and layout
* [608](https://github.com/microsoft/AdaptiveCards/issues/608) - Fact.Title wraps when Value is long
* [2445](https://github.com/microsoft/AdaptiveCards/issues/2445) - Inconsistency around placeholder support for Input.ChoiceSet
* [2782](https://github.com/microsoft/AdaptiveCards/issues/2782) - Padding mismatch between TS and other renderers with container style
* [2785](https://github.com/microsoft/AdaptiveCards/issues/2785) - [minHeight] Container with only background image without minHeight property is rendered inconsistently today
* [2843](https://github.com/microsoft/AdaptiveCards/issues/2843) - Inconsistency In Size When Rendering DataURI Image
* [2845](https://github.com/microsoft/AdaptiveCards/issues/2845) - DataURI Image As Background Image has Inconsistent Rendering 
* [2849](https://github.com/microsoft/AdaptiveCards/issues/2849) - [.NET] Low resolution images in an image set don't stretch as they do on other platforms
* [2851](https://github.com/microsoft/AdaptiveCards/issues/2851) - [iOS][UWP] Showcard behavior inconsistency
* [2871](https://github.com/microsoft/AdaptiveCards/issues/2871) - GIF support
* [2938](https://github.com/microsoft/AdaptiveCards/issues/2938) - [UWP] Choice set placeholder text is not shown
* [3042](https://github.com/microsoft/AdaptiveCards/issues/3042) - Emphasis container inside emphasis container provides inconsistent results
* [3175](https://github.com/microsoft/AdaptiveCards/issues/3175) - [Android] Media Control Doesn't Autohide
* [3200](https://github.com/microsoft/AdaptiveCards/issues/3200) - Inconsistency in show card collapse behavior
* [3254](https://github.com/microsoft/AdaptiveCards/issues/3254) - [UWP] Spacing/separator are ignored on Image
* [3362](https://github.com/microsoft/AdaptiveCards/issues/3362) - [iOS][Consistency] [RichText submit action lacks visual cue]
* [3416](https://github.com/microsoft/AdaptiveCards/issues/3416) - adaptive card button not wrapping the text
* [3516](https://github.com/microsoft/AdaptiveCards/issues/3516) - [Consistency] [Horizontal Scroll Bar in ActionSet]
* [3572](https://github.com/microsoft/AdaptiveCards/issues/3572) - [Web][Avatars] Person avatars are not always circular
* [3605](https://github.com/microsoft/AdaptiveCards/issues/3605) - [Android][Rendering Discrepancy between Android and web] [For Choice sets with compact style, when no option is explicitly pre-selected, first option gets pre-selected]

### Parsing, encoding, text handling, markdown, and text rendering
* [641](https://github.com/microsoft/AdaptiveCards/issues/641) - Finalize behavior for empty textblocks
* [910](https://github.com/microsoft/AdaptiveCards/issues/910) - JavaScript library does not natively support markdown, and third-party libs are too permissive
* [945](https://github.com/microsoft/AdaptiveCards/issues/945) - Action.Submit "data" property as string
* [1915](https://github.com/microsoft/AdaptiveCards/issues/1915) - [Parser] .NET accepts different formats for DateTime
* [1984](https://github.com/microsoft/AdaptiveCards/issues/1984) - Markdown text inconsistencies
* [2175](https://github.com/microsoft/AdaptiveCards/issues/2175) - Visualizer/NodeJS doesn't enforce required "text" property on TextBlock
* [2788](https://github.com/microsoft/AdaptiveCards/issues/2788) - Version handling inconsistency
* [2842](https://github.com/microsoft/AdaptiveCards/issues/2842) - [UWP][iOS] \r Creates new lines
* [2881](https://github.com/microsoft/AdaptiveCards/issues/2881) - Support long data URIs
* [3010](https://github.com/microsoft/AdaptiveCards/issues/3010) - [UWP JS] Spacing at the begining of a value in a factSet
* [3014](https://github.com/microsoft/AdaptiveCards/issues/3014) - [UWP] Long words don't wrap
* [3016](https://github.com/microsoft/AdaptiveCards/issues/3016) - [JS][Android] Newlines not working in JS, Android in textblock
* [3021](https://github.com/microsoft/AdaptiveCards/issues/3021) - Not all renderers support fallback on Column
* [3287](https://github.com/microsoft/AdaptiveCards/issues/3287) - Should Input.Number value accept a string?
* [3337](https://github.com/microsoft/AdaptiveCards/issues/3337) - [UWP] Mixing lists and links in markdown breaks rendering
* [3348](https://github.com/microsoft/AdaptiveCards/issues/3348) - [Shared] Markdown doesn't respect Unicode space
* [3420](https://github.com/microsoft/AdaptiveCards/issues/3420) - [UWP][Fallback Requires] Requirement comparison is case sensitive
* [3490](https://github.com/microsoft/AdaptiveCards/issues/3490) - Version parsing is not handled consistently between renderers
* [3531](https://github.com/microsoft/AdaptiveCards/issues/3531) - [Android] Newline Character ("\n") inside TextBlock not rendered
* [3573](https://github.com/microsoft/AdaptiveCards/issues/3573) - [.NET C#][Input.ChoiceSet] [adaptive card dropdown title with double quotes rendering issue]

### Missing functionality
* [271](https://github.com/microsoft/AdaptiveCards/issues/271) - Support custom fonts in Host Config on Android
* [3099](https://github.com/microsoft/AdaptiveCards/issues/3099) - Play button configuration of Media Config in adaptive host config is not getting use
* [3198](https://github.com/microsoft/AdaptiveCards/issues/3198) - Add placeholder to Input.ChoiceSet
* [3461](https://github.com/microsoft/AdaptiveCards/issues/3461) - [Shared] ActionSet::m_orientation unused
* [3482](https://github.com/microsoft/AdaptiveCards/issues/3482) - Add actions.allowTitleToWrap to non JS platforms

### Defaults/error behaviors
* [2111](https://github.com/microsoft/AdaptiveCards/issues/2111) - Discrepancies between different renderers
* [2779](https://github.com/microsoft/AdaptiveCards/issues/2779) - [UWP] Card throws warning in UWP but not other renderers
* [2855](https://github.com/microsoft/AdaptiveCards/issues/2855) - [UWP] Inconsistent warning about inlines type
* [2946](https://github.com/microsoft/AdaptiveCards/issues/2946) - Data URI behavior for invalid images
* [3011](https://github.com/microsoft/AdaptiveCards/issues/3011) - Open URL behavior when url not set
* [3031](https://github.com/microsoft/AdaptiveCards/issues/3031) - Column.width default value is inconsistent (auto on JS vs stretch on the rest)
* [3154](https://github.com/microsoft/AdaptiveCards/issues/3154) - Consistent behavior around required properties and schema errors
* [3224](https://github.com/microsoft/AdaptiveCards/issues/3224) - [Shared model] There is no consistency for on and off values in Input.Toggle
* [3303](https://github.com/microsoft/AdaptiveCards/issues/3303) - Consistency Issue: missing URL openURL action still renders
* [3364](https://github.com/microsoft/AdaptiveCards/issues/3364) - [JavaScript] actionAligment doesn't default to stretch
* [3365](https://github.com/microsoft/AdaptiveCards/issues/3365) - [.NET WPF] testVarientHostConfig returns an error

<<<<<<< HEAD
## Mobile Inconsistecies

### Abstract

This design spec categorized inconsistency bugs by their broader underlining causes. Mobile refers to Android and iOS. iOS and Android has a common JSON parser component that is also shared by UWP. If the problem is appears in the mobile platform, it may also appear in UWP.

#### Inconsistency Categories

1. [Gap in the Design](#gap-in-the-design)
 * Design does not cover all possible scenarios
5. [Gap in the User Knowledge](#gap-in-the-user-knowledge)
 * Users misunderstood features
 * Users general unfamiliarity to platforms
7. [Differences in Parsing](#differences-in-parsing)
 * Handling of invalid values are different across platforms
 * JS renderer, for example, is more lenient toward invalid values whereas UWP will not produce a card when it sees an invalid values in the card
6. [Differences in Platforms](#difference-in-platforms)
 * Platform A doesn't support feature x
 * It's not feasible to support the feature due to performances
8. [Differences in handling invalid values in Rendering](#differences-in-handling-invalid-values-in-rendering)
 * Shared models would not render an element if the element contains bad values
 * JS renderers renders portion of the element if it's possible
1. [Bug or Implementation Issue](#bug)
 * Renderers do not implement features as specified by the spec
1. Native Styling
 * Desktop (JS) provides well accepted and understood way of customizing UI components
 * Android / iOS generally lack customization
 * This state may be reflection of different philosophy, Internet (JS) vs fractured wall gardens of Android and iOS. 
2. Markdown
 * Desktop (JS) and mobile (Android / iOS) use different markdown engines; and they behave differently

### Results
 

|[Gap in The Design](#gap-in-the-design)|[Gap in the User Knowledge](#gap-in-user-knowledge)|
|:-------------------------------------:| ------------------------------------------------- | 
|    4                                  |                                                   |                                       
|                                       |                                                   |

#### Gap In the Design
We haven't specified behaviors for user scenarios.

* https://github.com/microsoft/AdaptiveCards/issues/4483
 The spec has not specified what happens when buttons overflow the avaiable width. In iOS, Button is streched as much as its content width, then horizontal scroll is enabled. Android wraps contents inside the button. 

![iOS](https://user-images.githubusercontent.com/4774656/83798129-c384d880-a671-11ea-9402-51f5f4bdfa20.png "iOS") ![Android](https://user-images.githubusercontent.com/4774656/83798099-b536bc80-a671-11ea-83f8-a4b7b3935866.png "Android")


* https://github.com/microsoft/AdaptiveCards/issues/3885

 Compact Style Input.ChoiceSet with multi select disabled does not support place holder text in our original spec, but as other input supports placeholder text, it's logical for the Input.ChoiceSet to have the placeholder text.
"Select an Option" is the placeholder text in the example below.


![JS](https://user-images.githubusercontent.com/60354515/77798800-93c9bb00-7099-11ea-92ea-29c37ef3800e.PNG "JS") ![iOS](https://user-images.githubusercontent.com/60354515/77798810-99270580-7099-11ea-8539-b192a10a7d48.png "iOS")

* https://github.com/microsoft/AdaptiveCards/issues/4531

 SelectActions in TextRun of RichTextBlock have different styles for iOS and JS renderers.  The spec hasn't specified the sytle for the selectAction. 
![JS](https://user-images.githubusercontent.com/8917620/89295530-c9e9fd80-d67e-11ea-9f72-b44bb20f8d9c.png) ![iOS](https://user-images.githubusercontent.com/8917620/89295553-cf474800-d67e-11ea-85d2-fac8b5070502.png)

* https://github.com/microsoft/AdaptiveCards/issues/3362

 This is the simmilar issue to 4531, the difference is 3362 raises an issue of the lack of the style that indicates the SelectAction whereas in 4531, raised an issue of incosistent styles. This shows that the importance of the process where we take time to re-spec and address the shortcoming in the spec.

#### Differences in Parsing

 There are several differences in parsing between renderers.

*Fixed*

* https://github.com/microsoft/AdaptiveCards/issues/4043 

  Different renders render images with "auto" size in ImageSet differently

* https://github.com/microsoft/AdaptiveCards/issues/3702
  Given a TextBlock with "text" that has zero length string such as "", some renderers render a TextBlock with the empty text while others doesn't render the TextBlock

*Open Issues*

* https://github.com/microsoft/AdaptiveCards/issues/3949

 Mobile won't parse a card if titles are missing in FactSet while JS will parse & render a card with empty title.

* https://github.com/microsoft/AdaptiveCards/issues/4478

 Mobile won't parse a card if TextBlock doesn't have text in it.

#### Solution
- AdaptiveCards parsers will stop parsing only when continuing the parsing is not possible.

 - Malformed payload (e.g. invalid json, not an adaptivecard, etc.)

  In such case, the parsers shall raise a parse error to host app

- bad or incorrect values for given AdaptiveCards properties shall raise parse warnings to host app, and continue parsing 

-  Host app can choose whether to attempt rendering or not, despite parse warnings

#### Application
- Trying the solution to the fixed issues

 [#4043](https://github.com/microsoft/AdaptiveCards/issues/4043), parsers should parse successfully since the payload was valid althouth the size property had invalid and unsupported value that was "auto"

 [#3702](https://github.com/microsoft/AdaptiveCards/issues/3702), parsers should parse successfully since the payload was valid. TextBlock's text was missing, and parsers should produce warnings.

- Interpolation

 [#3949](https://github.com/microsoft/AdaptiveCards/issues/3949), parser should parse, and produce warning if the title is required property 

 [#4478](https://github.com/microsoft/AdaptiveCards/issues/4478), parser should parse, and should produce warning since text is required property

#### Differences in handling invalid values in Rendering
Renders handle an invalid or out of spec values for an AdaptiveCards property diverges. This inconsistency often associated with differences in parsing. 

*Fixed Issues*

* https://github.com/microsoft/AdaptiveCards/issues/4043 

  Different renders render images with "auto" size in ImageSet differently

*  https://github.com/microsoft/AdaptiveCards/issues/3702

 JS renderer drops TextBlock with zero length text. iOS & Android render the TextBlock

*Open Issues*

* https://github.com/microsoft/AdaptiveCards/issues/3949

 Mobile won't parse a card if titles are missing in FactSet while JS will parse & render a card with empty title.

* https://github.com/microsoft/AdaptiveCards/issues/4478

 Mobile won't parse a card if TextBlock doesn't have text in it.

#### Solution
With our decision made for closing the inconistency in parsing, renderesr will see invalid values for a AdaptiveCards property. 
It's essential that renderers have unified ways of handling the invalid values.
If the payload contained the invalid values, the prased card will have warnings according to our decision made for closing parsing gap.

If host app chose not to render, we stop here

If host app chooses to continue, we make a "best-effort" render, as described below

 `Render Error` - cannot render element, will skip
 
 `Render Warning` - bad value, but will try to render element uisng default values

* No renderer found for given `type` 
 - trigger `AdaptiveCards` fallback
 - This is the only trigger for the fallback
 - If fallback defined, raise `Render Warning`, attempt to render fallback
 - If no fallback, raise `Render Error`

* Required property
 - Property is not given, is null, is empty, or has invalid value
 - Raise `Render Error`, skip element

* Optional property (all such properties should have a default)
 - Property is not given or is null
  - No error, use the default value, render element

 - Property has invalid value (e.g. invalid enum, invalid URI, etc.)
  - `Raise Render Warning`, use default value, render element

 - Property is empty (e.g. "", [])
  - enums, handle this like an invalid value
  - For other types, handle this like not given/null

#### Application
- Trying the solution to the fixed issues

 [#4043](https://github.com/microsoft/AdaptiveCards/issues/4043), ImageSet element has invalid enum "auto", renders shall raise `Render Warning`, and render the ImageSet with default value for the size

 [#3702](https://github.com/microsoft/AdaptiveCards/issues/3702), TextBlock has the empty value for the required property, "text", render should raise `Render Error` and skip the element

- Interpolation

 [#3949](https://github.com/microsoft/AdaptiveCards/issues/3949), must decide if titles or values are required or optional properties

 [#4478](https://github.com/microsoft/AdaptiveCards/issues/4478), A TextBlock doesn't have required property text, render should raise `Render Error` and skip the element

#### Gap in the User Knowledge
Users were not familiar with AdaptiveCards and its schema
* https://github.com/microsoft/AdaptiveCards/issues/4483

 Users were not aware of the existance of the "wrap" property in the TextBlock. When the text was clipped, they were surprised.

 If a text wrap property is set true as default value, people does not need to learn about the existence of the wrap property. 
* https://github.com/microsoft/AdaptiveCards/issues/3855

 Users set "auto" for both columns. One column has text in it. The other column has the button. With auto and auto, the text's long width end up taking all the width. We can improve our implementation such that a column won't get pushed out. However, as it can be shown in the issue, even with the improved implementation, the card will end up looking bad. The right values for the columns should have been stretch for the text and auto for the button, such that the column with the text will shrank and the column with the button maintain its width. 

* Possible solution to narrow the gap in the user knowledge is that we do our do diligence and provide the most sensible default values. Text Wrap property makes the perfect sense as the default value since users rarely want the texts in their cards are clipped. For the issue 3855, we could provide "stretch" as a width for stretch for the column, and all else "auto".

* Users want to customize the buttons' look. They were able to customize background and radius of buttons in the desktop (JS), but users were not able to achieve the look they want using what we offered.

* AdaptiveCards schema allows Buttons to have icons such as chevrons. Users claimed that iOS / Android can't have chevron.

* UI interaction model are different in platforms and have their own peculiarities. The behavior described in the slide is standard behavior of iOS as provided by UIKit. Customers want to be able to change the background color of the picker view. 

* iOS & Android support  only subset of the Markdowns while JS renderers supports the Markdown fully 

 Handling of new lines are different from platform to platforms.
	
#### Solution
There are varying degree of support for native styling. Android, for example, doesn't support native styling. iOS's native styling support is not as extensive as CSS in JS. We can better document the process, but also supporting the styles as shareable extensions can reduce the pressure on our team as we can provide a solution as a form of extension and share it.
	

#### Differences in Platform
Platform has various degree of what works and what doesn't work.

https://github.com/microsoft/AdaptiveCards/issues/4015
	• Font weight is not supported on Android. Font weight was not formally supported via an API in the old platform


#### Bug
It's a bug on our end. We didn't implement features to our design specifications. In the picture below, When date is selected, the date picker view doesn't close on its own.  


https://github.com/microsoft/AdaptiveCards/issues/4687
	• Background Image is squashed.
https://github.com/microsoft/AdaptiveCards/issues/4484
	• Not all inputs honor placeholder text.
=======
>>>>>>> b98f56f73d9aae0ace4cc63bf2d944959c7b4298
