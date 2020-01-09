# Inconsistencies in Adaptive Cards platforms

## Motivation

### Goals

* Provide a platform for experiences that allows card authors to write a card once and be confident that the card works everywhere
* Make it easy for developers to understand how extending Adaptive Cards impacts consistency
* Make it possible for third party developers to implement compliant and behaviorally consistent renderers for new platforms
* Structure code and processes such that inconsistencies are very likely to be found before they are shipped

### Non-Goals

* Provide pixel-perfect rendering across all platforms
* Provide identical behaviors in all situations across all platforms
* Make it impossible for developers to make a consistency mistake

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
    * Require that first accepted commits of a new feature include robust test cards that not only exercise the "golden path" for a feature, but every conceivable corner case relevant to 
      * Perhaps a checklist that needs to be completed prior to merge?
* (P1) Provide a new tool that allows easy testing of card payloads across all renderers:
  * Motivation: Allows for the easy directed testing of feature consistency
  * Tasks: 
    * If shipped for public use, this could be a nice addition to the designer to allow card authors to preview their cards in a variety of renderers
    * Could be used in tests for per-platform visual verification
    * Per-platform accessibility trees could also be generated by this tool to allow for cross-plat verification
* (P1) Make hard decisions around defaults, required properties, and parser/renderer behaviors: 
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

