# Adaptive Cards Xamarin Bindings #

This folder contains the [Xamarin](https://xamarin.com) bindings for [Adaptive Cards](https://adaptivecards/io) for iOS. These bindings enable you to build C# Xamarin applications leveraging the native implementation of Adaptive Cards.

### Contents ###
#### Where is AdaptiveCards.framework ####
AdaptiveCards.framework.zip is the output of building the AdaptiveCards library in iOS, this file is needed to compile the Xamarin project so currently the way to include it to the project is compiling the AdaptiveCards iOS library and then copy the file to the expected path