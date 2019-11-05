# AdaptiveCards Xamarin Renderer

## Proposal Link

There is no open issue for a Xamarin.Native package so I'm placing the Xamarin.Forms issue for now 
https://github.com/microsoft/AdaptiveCards/issues/3255

## Dependencies
This project depends entirely on the Android and iOS renderer and their API's. This project is a Xamarin bindings library so the only new code to be included are the xamarin transformations for the underlying renderers. For generating the bindings, Xamarin requires the generated binaries (aar file for Android and framework file for iOS) to be included.

### What is a bindings library

A bindings library is an assembly that wraps the native library with C# wrappers so native code can be invoked via C# calls. Xamarin.Android implements bindings by using Managed Callable Wrappers (MCW) which are a JNI bridge that are used when managed code needs to invoke Java code. In the case of iOS, to bind a library an API definition file is needed; this is merely a C# source file that contains C# interfaces that have been annotated with a handful of attributes that help drive the binding. The API definition is merely the contract that will be used to generate the API.

## Architecture

As can be seen in the diagram below, the Android and iOS bindings libraries make use of the Java and Objective-C code that is already projected from the shared C++ code. The bindings also make use of the native APIs for both platforms yielding a C# library for every platform that can be consumed by any Xamarin platform.

[image](assets/XamarinArchitecture.png)

Something to consider is that Native Xamarin is designed to share the logic and services inside an application but the UI is independent for every platform which allows us to have three different object models.  

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

#### APIs to be included in Xamarin

| API Name | Android API |  Priority |
| --- | --- | --- |
| Rendering | RenderedAdaptiveCard render(Context, FragmentManager, AdaptiveCard, ICardActionHandler) | P0 |
| Rendering | RenderedAdaptiveCard render(Context, FragmentManager, AdaptiveCard, HostConfig) | P0 |
| Custom Element | void registerRenderer(string, IBaseCardElementRenderer) | P1 |
| Custom Element | IBaseCardElementRenderer(string) | P1 |
| Custom Action | void registerActionRenderer(string, IBaseActionElementRenderer) | P1 |
| Custom Action | IBaseActionElementRenderer getActionRenderer(string) | P1 |
| Custom Action Layout | void registerActionLayoutRenderer(IActionLayoutRenderer) | P2 |
| Custom Action Layout | IActionLayoutRenderer getActionLayoutRenderer() | P2 | 
| Resource Resolvers | void registerOnlineImageLoader(IOnlineImageLoader) – deprecated | P3 |
| Resource Resolvers | IOnlineImageLoader getOnlineImageLoader() - deprecated | P3 |
| Resource Resolvers | void registerResourceResolver(string, IResourceResolver) | P2 |
| Resource Resolvers | IResourceResolver getResourceResolver(string) | P2 |
| Media Loading | IOnlineMediaLoader getOnlineMediaLoader() | P3 |
| Media Loading | void registerOnlineMediaLoader(IOnlineMediaLoader) | P3 |
| Feature Registration | void registerFeatureRegistration(FeatureRegistration) | P0 |
| Feature Registration | FeatureRegistration getFeatureRegistration() | P0 |
| Input Watcher | void setInputWatcher(IInputWatcher) | P3 |
| Input Watcher | IInputWatcher getInputWatcher() | P3 |
| Custom Fonts | void registerCustomTypeface(string, Typeface) | P3 |

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

### APIs to be included in Xamarin

| API Name | iOS API | Priority |
| --- | --- | --- |
| Rendering | (ACRRenderResult*) render:(ACOAdaptiveCard*) config:(ACOHostConfig) widthConstraint:(float) | P0 |
| Rendering | (ACRRenderResult*) render:(ACOAdaptiveCard*) config:(ACOHostConfig) widthConstraint:(float) delegate:(id<ACRActionDelegate>) | P0 |
| Rendering | (ACRRenderResult*) renderAsViewController:(ACOAdaptiveCard*) config:(ACOHostConfig) frame:(CGRect) delegate:(id<ACRActionDelegate>) | P0 |
| Custom Element | (void) setBaseCardElementRenderer: (ACRBaseCardElementRenderer*)cardElementType: (ACRCardElementType) | P1 |
| Custom Element | (void) setCustomElementParser: (NSObject<ACOIBaseCardElementParser>) | P1 |
| Custom Element | (void) setCustomElementParser: (NSObject<ACOIBaseCardElementParser>) key: (NSString*) | P1 |
| Custom Element | (void) setCustomElementRenderer: (ACRBaseCardElementRenderer*) key:(NSString *) | P1 |
| Custom Element | (NSObject<ACOIBaseCardElementParser>*) getCursorElementParser: (NSString*) | P1 |
| Custom Element | (ACRBaseCardElementRenderer*) getRenderer: (NSNumber *) | P1 |
| Custom Action | (void) setActionRenderer: (ACRBaseActionElementRenderer) cardElementType: (NSNumber*) | P1 |
| Custom Action | (ACRBaseActionElementRenderer*) getActionRenderer: (NSNumber*) | P1 |
| Custom Action Set | (void) setActionSetRenderer: (id<ACRIBaseActionSetRenderer>) | P2 |
| Custom Action Set | (id<ACRIBaseActionSetRenderer>) getActionSetRenderer | P2 | 
| Resource Resolvers | (void) setResourceResolver: (NSObject<ACOIResourceResolver>) scheme: (NSString*) | P2 |
| Resource Resolvers | (NSObject<ACOIResourceResolver>) getResourceResolverForScheme: (NSString*) | P2 |
| Feature Registration | (void) addFeature: (NSString*) featureVersion: (NSString*) | P0 | 
| Feature Registration | (NSString*) removeFeature: (NSString*) | P0 |
| Feature Registration | (NSString*) getFeatureVersion: (NSString*) | P0 |

## Breaking changes

There is one big breaking change to be introduced in the iOS platform due to the Xamarin bindings having a direct relationship with the name of the library, which requires changing the library name from ACFramework to AdaptiveCards.

Besides that, no breaking changes should be introduced as the native platforms' code is only consumed and projected into C#.

## Test Plan

For the alpha and pre-release versions the testing will be performed manually

## Release plan

### Artifacts

The artifacts to be released with this library will be:
1. Source code for Xamarin bindings in the github repository
1. Xamarin.Android nuget package
1. Xamarin.iOS nuget package

### Continuous Integration and Release

To be able to release the previously mentioned nuget packages build definitions must be created. The current system we use for building the other packages allow us to build Xamarin.Android and Xamarin.iOS packages

#### Pre-requisites

The Xamarin packages require native libraries to be built beforehand, as we can't upload binaries into the repository, then the Android and iOS build definitions must be updated to copy the generated binaries into the xamarin projects folder. 

#### Build definitions

At least four build pipelines will be needed for this project, 2 pipelines for Continuous integration and 2 pipelines for the release. The pipelines for the release will be similar to the UWP and WPF pipelines that generate nuget packages and build against a visual studio solution/project.

## Remaining Tasks

For the alpha version all P0 and P1 APIs should be done while P2 and P3 tasks must be done for the first complete release. 

## Open issues

Currently the naming convention for AdaptiveCards packages are medium sized, as Xamarin builds on top of other platforms, these namings internally become large enough to overpass the character limit so errors tend to appear during development which make it harder (Xamarin also doesn't spew enough information to be easily solved).