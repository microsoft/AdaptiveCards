We're excited to announce the beta release of our SDKs and the final v1.0 schema!

## Final v1.0 schema 
**NOTE:** Some of these are BREAKING CHANGES from v0.5

Many of these changes do have back-compat support in existing renderers, but as clients upgrade to v1.0 through the end of the year we will start to see less support for the pre-1.0 schema. 

1. Add flexibility by splitting `separation` into separate properties: `spacing` and `separator` #462
2. `Column.size` renamed to `Column.width` #552
3. Renamed all enums that had a default value of `normal` to `default` #630
4. `TextBlock` no longer has a `TIME()` formatting function #419
5. Removed `Action.Http`, planning to revist later. No hosts are currently supporting it. #618
6. Removed `speak` from elements, only exists at the `AdaptiveCard` level now
7. Update `Container` `style` to better guarantee appropriate background/text color combinations #472
8. Added `selectAction` to `ColumnSet` #344
9. Standardized input-value binding #652
10. `Input.Choice` removed `isSelected`, property. Use the `Input.ChoiceSet` `value` instead #652
	

# SDKs

| Platform | Install | Build | Known Issues |
|---|---|---|---|
| Android | [![Maven Central](https://img.shields.io/maven-central/v/io.adaptivecards/adaptivecards-android-arm.svg)](https://search.maven.org/#search%7Cga%7C1%7Ca%3A%22adaptivecards-android-arm%22) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/master/source/android) | [|
| HTML Client | [![npm install](https://img.shields.io/npm/v/microsoft-adaptivecards.svg)](https://www.npmjs.com/package/microsoft-adaptivecards) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/master/source/html)|Beta|
| iOS | [![CocoaPods](https://img.shields.io/cocoapods/v/AdaptiveCards.svg)](https://cocoapods.org/pods/AdaptiveCards) |[Source](https://github.com/Microsoft/AdaptiveCards/tree/master/source/ios) | ![Build status](https://img.shields.io/vso/build/Microsoft/8d47e068-03c8-4cdc-aa9b-fc6929290322/16990.svg)|
| .NET WPF | [![Nuget install](https://img.shields.io/nuget/v/Microsoft.AdaptiveCards.svg)](https://www.nuget.org/packages/Microsoft.AdaptiveCards/) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/master/source/dotnet)| Beta |
| UWP | [![Nuget install](https://img.shields.io/nuget/vpre/AdaptiveCards.UWP.Beta.svg)](https://www.nuget.org/packages/AdaptiveCards.UWP.Beta) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/master/source/uwp) | ![Build Status](https://img.shields.io/vso/build/Microsoft/8d47e068-03c8-4cdc-aa9b-fc6929290322/16850.svg) |
| .NET HTML | ![Nuget install](https://img.shields.io/nuget/v/AdaptiveCards.Html.svg)](https://www.nuget.org/packages/AdaptiveCards.Html/) | [Source](https://github.com/Microsoft/AdaptiveCards/tree/master/source/dotnet)