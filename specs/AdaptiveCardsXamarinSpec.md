# AdaptiveCards Xamarin Renderer

## Proposal Link

The current issues that track the development of Native Xamarin renderer packages are:
* [#3626](https://github.com/microsoft/AdaptiveCards/issues/3626)
* [#3627](https://github.com/microsoft/AdaptiveCards/issues/3627) 

Adaptive Cards rendering libraries for Xamarin and Xamarin.Forms have been some of the most requested features by our consumers, some of the consumers have filed feedback for the development in this packages and it is currently tracked [here](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/c/28-xamarin-and-xamarin-forms-sdks?utm_medium=social&utm_source=portal_share). This feature has also been requested during conferences where the Adaptive Cards developers have a closer contact with developers and external consumers. 

## Dependencies
This project depends entirely on the Android and iOS renderer and their API's. This project is a Xamarin bindings library so the only new code to be included are the xamarin transformations for the underlying renderers. For generating the bindings, Xamarin requires the generated binaries (aar file for Android and framework file for iOS) to be included.

### What is a bindings library

A bindings library is an assembly that wraps the native library (Objective-C/Java code) with C# wrappers so platform specific code can be invoked via C# calls. Xamarin.Android implements bindings by using Managed Callable Wrappers (MCW) which are a JNI bridge that are used when managed code needs to invoke Java code. In the case of iOS, to bind a library an API definition file is needed; this is merely a C# source file that contains C# interfaces that have been annotated with a handful of attributes that help drive the binding. The API definition is merely the contract that will be used to generate the API.

## Architecture

As can be seen in the diagram below, the Android and iOS bindings libraries make use our existing iOS/Android renderer libraries that already contain projected code from the shared C++ object model. The bindings also make use of the native APIs for both platforms yielding a C# library for every platform that can be consumed by any Xamarin platform.

![image](assets/XamarinArchitecture.png)

Something to consider is that Native Xamarin is designed to share the logic and services inside an application but the UI is independent for every platform which allows us to have three different object models.  

## Feature Priority

The priorities among the APIs to be ported into Xamarin for the pre-release version were decided by selecting which APIs would be the bare minimum for a consumer of the Xamarin package to be able to render a card would be P0 as well as any APIs that were part of a feature (such as featureRegistration). 

For P1, the tasks were decided using the same features asked for P1 in the [Xamarin.Forms github issue](https://github.com/microsoft/AdaptiveCards/issues/3255) which states that custom rendering for actions and elements would be P1. 

Finally, P2 would be any task that enhances the developer experience but are not required for using Adaptive Cards and P3 would be any APIs that may not be used by most consumers or are specific to only one platform.

## Rendering

### UWP

For Xamarin rendering UWP doesn't require any changes as the rendering and API's are done in C#. The current renderer we provide must only be referenced as is or included as a nuget package.

### Android

Android bindings are mostly done in the Metadata.xml file which defines the contract between C# and Java. This file can contain renames for packages, change of return types and parameter types and names as well as removing classes or including extra classes.

``` xml
<metadata>
  <attr path="/api/package[@name='io.adaptivecards']" name="managedName">AdaptiveCards.Rendering.Xamarin.Android</attr>

  <!-- Updates Get methods to return java.lang.Object instead of the actual type -->
  <attr path="/api/package[@name='io.adaptivecards.objectmodel']/class[@name='BaseActionElementVector']/ method[@name='get']" name="managedReturn">Java.Lang.Object</attr>

  <!-- Updates DoInBackground method's parameter and return types -->
  <attr path="/api/package[@name='io.adaptivecards.renderer']/class[@name='BackgroundImageLoaderAsync']/ method[@name='doInBackground']" name="managedReturn">Java.Lang.Object</attr>

  <add-node path="/api/package[@name='io.adaptivecards.renderer']">
    <class abstract="false" deprecated="not deprecated" final="false" name="MediaLoaderAsync" static="true" visibility="public" extends="java.lang.Object"/>
  </add-node>
</metadata>
```

#### APIs to be included in Xamarin.Android

| Priority | API Name | Android API |
| --- | --- | --- |
| P0 | Parsing | ```ParseResult DeserializeFromString(String, String)``` | 
| P0 | Parsing | ```ParseResult DeserializeFromString(String, String, ParseContext)``` | 
| P0 | Rendering | ```RenderedAdaptiveCard render(Context, FragmentManager, AdaptiveCard, HostConfig, ICardActionHandler)``` |
| P0 | Rendering | ```RenderedAdaptiveCard render(Context, FragmentManager, AdaptiveCard, HostConfig)``` |
| P0 | Feature Registration | ```void registerFeatureRegistration(FeatureRegistration)``` | 
| P0 | Feature Registration | ```FeatureRegistration getFeatureRegistration()``` |
| P1 | Custom Element | ```void registerRenderer(string, IBaseCardElementRenderer)``` |
| P1 | Custom Element | ```IBaseCardElementRenderer(string)``` |
| P1 | Custom Action | ```void registerActionRenderer(string, IBaseActionElementRenderer)``` |
| P1 | Custom Action | ```IBaseActionElementRenderer getActionRenderer(string)``` |
| P2 | Parsing | ```ParseResult Deserialize(JsonValue, String, ParseContext)``` |
| P2 | Parsing | ```ParseResult DeserializeFromFile(String, String)``` |
| P2 | Parsing | ```ParseResult DeserializeFromFile(String, String, ParseContext)``` |
| P2 | Custom Action Layout | ```void registerActionLayoutRenderer(IActionLayoutRenderer)``` |
| P2 | Custom Action Layout | ```IActionLayoutRenderer getActionLayoutRenderer()``` |
| P2 | Resource Resolvers | ```void registerResourceResolver(string, IResourceResolver)``` |
| P2 | Resource Resolvers | ```IResourceResolver getResourceResolver(string)``` |
| P2 | Resource Information | ```RemoteResourceInformationVector GetResourceInformation()``` |
| P3 | Media Loading | ```IOnlineMediaLoader getOnlineMediaLoader()``` |
| P3 | Media Loading | ```void registerOnlineMediaLoader(IOnlineMediaLoader)``` |
| P3 | Input Watcher | ```void setInputWatcher(IInputWatcher)``` |
| P3 | Input Watcher | ```IInputWatcher getInputWatcher()``` |
| P3 | Custom Fonts | ```void registerCustomTypeface(string, Typeface)``` |
| P3 | Resource Resolvers | ```void registerOnlineImageLoader(IOnlineImageLoader)``` – deprecated |
| P3 | Resource Resolvers | ```IOnlineImageLoader getOnlineImageLoader()``` - deprecated |

### iOS

iOS bindings are done with an API definition file and a Structs class where structs and enums are re-defined. In the API definition all methods and classes to be made public are included while the Structs file contains enumerations.

#### ApiDefinitions
``` C#
// @interface ACOBaseActionElement : NSObject
[BaseType(typeof(NSObject))]
interface ACOBaseActionElement
{
    // @property ACRActionType type;
    [Export("type", ArgumentSemantic.Assign)]
    ACRActionType Type { get; set; }

    // -(NSString *)title;
    [Export("title")]
    string Title { get; }

    // -(NSString *)elementId;
    [Export("elementId")]
    string ElementId { get; }

    // -(NSString *)url;
    [Export("url")]
    string Url { get; }

    // -(NSString *)data;
    [Export("data")]
    string Data { get; }

    // -(NSData *)additionalProperty;
    [Export("additionalProperty")]
    NSData AdditionalProperty { get; }
}
```

#### Structs
``` C#
[Native]
public enum ACRActionType : long
{
	ShowCard = 1,
	Submit,
	OpenUrl
}
```

### APIs to be included in Xamarin.iOS

| Priority | API Name | iOS API | 
| --- | --- | --- |
| P0 | Parsing | ```(ACOAdaptiveCardParseResult*) fromJson: (NSString*)``` |
| P0 | Rendering | ```(ACRRenderResult*) render:(ACOAdaptiveCard*) config:(ACOHostConfig) widthConstraint:(float)``` |
| P0 | Rendering | ```(ACRRenderResult*) render:(ACOAdaptiveCard*) config:(ACOHostConfig) widthConstraint:(float) delegate:(id<ACRActionDelegate>)``` |
| P0 | Rendering | ```(ACRRenderResult*) renderAsViewController:(ACOAdaptiveCard*) config:(ACOHostConfig) frame:(CGRect) delegate:(id<ACRActionDelegate>)``` |
| P0 | Feature Registration | ```(void) addFeature: (NSString*) featureVersion: (NSString*)``` |
| P0 | Feature Registration | ```(NSString*) removeFeature: (NSString*)``` |
| P0 | Feature Registration | ```(NSString*) getFeatureVersion: (NSString*)``` |
| P1 | Custom Element | ```(void) setBaseCardElementRenderer: (ACRBaseCardElementRenderer*)cardElementType: (ACRCardElementType)``` |
| P1 | Custom Element | ```(void) setCustomElementParser: (NSObject<ACOIBaseCardElementParser>)``` |
| P1 | Custom Element | ```(void) setCustomElementParser: (NSObject<ACOIBaseCardElementParser>) key: (NSString*)``` |
| P1 | Custom Element | ```(void) setCustomElementRenderer: (ACRBaseCardElementRenderer*) key:(NSString *)``` |
| P1 | Custom Element | ```(NSObject<ACOIBaseCardElementParser>*) getCustomElementParser: (NSString*)``` |
| P1 | Custom Element | ```(ACRBaseCardElementRenderer*) getRenderer: (NSNumber *)``` |
| P1 | Custom Action | ```(void) setActionRenderer: (ACRBaseActionElementRenderer) cardElementType: (NSNumber*)``` |
| P1 | Custom Action | ```(ACRBaseActionElementRenderer*) getActionRenderer: (NSNumber*)``` |
| P2 | Custom Action Set | ```(void) setActionSetRenderer: (id<ACRIBaseActionSetRenderer>)``` |
| P2 | Custom Action Set | ```(id<ACRIBaseActionSetRenderer>) getActionSetRenderer``` |
| P2 | Resource Resolvers | ```(void) setResourceResolver: (NSObject<ACOIResourceResolver>) scheme: (NSString*)``` |
| P2 | Resource Resolvers | ```(NSObject<ACOIResourceResolver>) getResourceResolverForScheme: (NSString*)``` |
| P2 | Resource Information | ```(NSArray<ACORemoteResourceInformation>*) remoteResourceInformation``` | 

## Breaking changes

No breaking changes should be introduced as the native platforms' code is only consumed and projected into C#. We had a concern over introducing one due to having to rename the C++ umbrella header for runnning the Sharpie application, but the change can be reverted:

> ... A general rule is that as long as the class and selector names are unchanged, you can do whatever you need to get sharpie to get it parse. Renaming headers, moving headers around, and then revert it once you get a solid parse. In the end the binding stack does not interact with headers once sharpie is done. We the class and selector names during runtime. 

## Test Plan

For the alpha and pre-release versions the testing will be performed manually, there's currently one sample application for Xamarin Android and one for Xamarin iOS. 

After the pre release version is published, unit tests are going to be started to be developed starting by covering the most basic scenarios and usages of APIs, and just as the sample application, one version will be made for Xamarin.Android and one will be made for Xamarin.iOS.

## Release plan

### Artifacts

The artifacts to be released with this library will be:
1. Source code for Xamarin bindings in the github repository
1. Source code for Xamarin.Android and Xamarin.iOS sample applications in repository
1. Xamarin.Android nuget package
1. Xamarin.iOS nuget package

Other products to be generated but will not be shipped in any store are:
1. Xamarin.Android sample application
1. Xamarin.iOS sample application

### Continuous Integration and Release

To be able to release the previously mentioned nuget packages build definitions must be created. The current system we use (Azure Deployment Pipelines) for building the other packages allow us to build Xamarin.Android and Xamarin.iOS packages.

Android and iOS build artifacts are required to perform the build process, for Android aar files are needed while iOS require a framework file to perform the bindings.

#### Pre-requisites

The Xamarin packages require native libraries to be built beforehand, as we can't upload binaries into the repository, then the Android and iOS build definitions must be updated to copy the generated binaries into the xamarin projects folder. 

#### Build definitions

At least four build pipelines will be needed for this project, 2 pipelines for Continuous integration and 2 pipelines for the release. The pipelines for the release will be similar to the UWP and WPF pipelines that generate nuget packages and build against a visual studio solution/project.

## Identified Tasks

For the alpha version all P0 APIs should be done and tested while P1, P2 and P3 tasks should be finished and tested for the first complete release. 

| Task | Expected cost in days |
| --- | --- |
| Update to Xamarin.Android Bindings for P0 | 2 |
| Update to Xamarin Android Sample Application | 3 |
| Creation of CI and release pipelines for Android | 4 |
| Update to Xamarin.iOS Bindings for P0 | 3 |
| Update to Xamarin iOS Sample Application | 4 |
| Update for iOS build script | 3 |
| Creation of CI and release pipelines for iOS | 4 |
| Total Cost | 23 |

## Open issues

### Accesibility
Accesibility support depends entirely on the underlying platform specific libraries as this binding libraries only wrap the Adaptive Cards APIs.

### Reliability of CI builds
Making changes to platform specific libraries would probably generate a build break for the Xamarin bindings libraries which would require updating them or adding them to the bindings. On the other hand, the time CI builds take will increase as this libraries must be built on top of Android and iOS libraries.

### Package naming
Currently the naming convention for AdaptiveCards packages are medium sized (e.g. AdaptiveCards.Rendering.Html.Core), as Xamarin builds on top of other platforms, these namings internally become large enough to overpass the character limit so errors tend to appear during development which make it harder (Xamarin also doesn't spew enough information to be easily solved).

## References

1. [Binding a Java Library](https://docs.microsoft.com/en-us/xamarin/android/platform/binding-java-library/)
1. [Overview of Objective-C Bindings](https://docs.microsoft.com/en-us/xamarin/cross-platform/macios/binding/overview)