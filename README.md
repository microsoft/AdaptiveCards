# Adaptive Cards

![logo](assets/adaptive-card-200.png)

[Adaptive Cards](https://adaptivecards.io) are a new way for developers to exchange content in a common and consistent way. Get started today by putting Adaptive Cards into Microsoft Teams, Outlook Actionable Messages, Cortana Skills, or Windows Timeline -- or render cards inside your own apps by using our SDKs.

## Dive in

* [Documentation](https://adaptivecards.io/documentation/)
* [Roadmap](https://portal.productboard.com/adaptivecards/1-adaptive-cards-features/tabs/5-launched)
* [Schema Explorer](https://adaptivecards.io/explorer/)
* [Sample Cards](https://adaptivecards.io/samples/)
* [Designer](https://adaptivecards.io/designer/)

## Install and Build

Adaptive Cards are designed to render anywhere that your users are. The following native platform renderers are under development right now.

PS: Latest Build Status is against `main` branch.

|Platform|Latest Release|Source|Docs|Latest Build Status|
|---|---|---|---|---|
| JavaScript | [![npm install](https://img.shields.io/npm/v/adaptivecards.svg)](https://www.npmjs.com/package/adaptivecards) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/nodejs/adaptivecards)| [Docs](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/htmlclient) | ![Build Status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/20564/main.svg) |
| .NET | [![Nuget install](https://img.shields.io/nuget/vpre/AdaptiveCards.svg)](https://www.nuget.org/packages/AdaptiveCards) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/dotnet)| [Docs](https://docs.microsoft.com/en-us/adaptive-cards/create/libraries/net) | ![Build status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/20596/main.svg) |
| .NET WPF | [![Nuget install](https://img.shields.io/nuget/vpre/AdaptiveCards.Rendering.Wpf.svg)](https://www.nuget.org/packages/AdaptiveCards.Rendering.Wpf) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/dotnet)| [Docs](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/net-wpf) | ![Build status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/20596/main.svg) |
| .NET HTML | [![Nuget install](https://img.shields.io/nuget/vpre/AdaptiveCards.Rendering.Html.svg)](https://www.nuget.org/packages/AdaptiveCards.Rendering.Html) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/dotnet) | [Docs](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/net-html) | ![Build status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/20596/main.svg) |
| Windows UWP | [![Nuget install](https://img.shields.io/nuget/vpre/AdaptiveCards.Rendering.Uwp.svg)](https://www.nuget.org/packages/AdaptiveCards.Rendering.Uwp) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/uwp) | [Docs](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/uwp) | ![Build Status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/20583/main.svg) |
| Android | [![Maven Central](https://img.shields.io/maven-central/v/io.adaptivecards/adaptivecards-android.svg)](https://search.maven.org/#search%7Cga%7C1%7Ca%3A%22adaptivecards-android%22) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/android) | [Docs](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/android) | ![Build status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/37913/main.svg)
| iOS | [![CocoaPods](https://img.shields.io/cocoapods/v/AdaptiveCards.svg)](https://cocoapods.org/pods/AdaptiveCards) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/ios) | [Docs](https://docs.microsoft.com/en-us/adaptive-cards/display/libraries/ios) |  ![Build status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/37917/main.svg) |
| Card Designer | [![npm install](https://img.shields.io/npm/v/adaptivecards-designer.svg)](https://www.npmjs.com/package/adaptivecards-designer) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/nodejs/adaptivecards-designer)| [Docs](https://www.npmjs.com/package/adaptivecards-designer) | ![Build Status](https://img.shields.io/azure-devops/build/Microsoft/56cf629e-8f3a-4412-acbc-bf69366c552c/20564/main.svg) |

#### End User License Agreement for our binary packages
Consumption of the AdaptiveCards binary packages are subject to the Microsoft EULA (End User License Agreement). Please see the relevant terms as listed below:
- [UWP/.NET](https://github.com/microsoft/AdaptiveCards/blob/main/source/EULA-Windows.txt)
- [Android/iOS](https://github.com/microsoft/AdaptiveCards/blob/main/source/EULA-Non-Windows.txt)

NOTE: All of the source code, itself, made available in this repo as well as our NPM packages, continue to be governed by the open source [MIT license](https://github.com/microsoft/AdaptiveCards/blob/main/LICENSE).
### Community SDKs

The following SDKs are lovingly maintained by the Adaptive Cards community. Their contributions are sincerely appreciated! 🎉

|Platform|Install|Build|Docs|Status|Maintainer|
|---|---|---|---|---|---|
| ReactNative | [![npm install](https://img.shields.io/npm/v/adaptivecards-reactnative.svg)](https://www.npmjs.com/package/adaptivecards-reactnative) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/community/reactnative)| [Docs](https://github.com/Microsoft/AdaptiveCards/blob/main/source/community/reactnative/README.md) | [![react-native-build](https://github.com/microsoft/AdaptiveCards/workflows/react-native-build/badge.svg)](https://dev.azure.com/microsoft/AdaptiveCards/_build/latest?definitionId=38416) | [Imaginea](https://github.com/Microsoft/AdaptiveCards/blob/main/source/community/reactnative/Contributors.md)
| Pic2Card | | [Source](https://github.com/Microsoft/AdaptiveCards/tree/main/source/pic2card) | [Docs](https://github.com/Microsoft/AdaptiveCards/blob/main/source/pic2card/README.md) | ![pic2card-build](https://github.com/Microsoft/AdaptiveCards/workflows/pic2card-build/badge.svg) | [Imaginea](https://github.com/Microsoft/AdaptiveCards/blob/main/source/community/reactnative/Contributors.md)
| Vue.js | [![npm install](https://img.shields.io/npm/v/adaptivecards-vue.svg)](https://www.npmjs.com/package/adaptivecards-vue) | [Source](https://github.com/DeeJayTC/adaptivecards-vue)| [Docs](https://github.com/DeeJayTC/adaptivecards-vue/blob/master/README.md) | OK | [Tim Cadenbach](https://github.com/DeeJayTC)



## Contribute

There are many ways to [contribute](https://github.com/Microsoft/AdaptiveCards/blob/main/.github/CONTRIBUTING.md) to Adaptive Cards.
* [Submit bugs](https://github.com/Microsoft/AdaptiveCards/issues) and help us verify fixes as they are checked in.
* Review the [source code changes](https://github.com/Microsoft/AdaptiveCards/pulls).
* Engage with Adaptive Cards users and developers on [StackOverflow](http://stackoverflow.com/questions/tagged/adaptive-cards). 
* Join the [#adaptivecards](https://twitter.com/hashtag/adaptivecards?f=tweets&vertical=default) discussion on Twitter.
* [Contribute bug fixes](https://github.com/Microsoft/AdaptiveCards/blob/main/.github/CONTRIBUTING.md).

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see 
the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.
