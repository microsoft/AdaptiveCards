# Adaptive Cards Xamarin iOS Sample #

This folder contains the [Xamarin](https://xamarin.com) sample app for [Adaptive Cards](https://adaptivecards/io) for iOS. This sample uses the BotConnection for retrieving the payloads.

### How do I fix this? ###

#### Couldn't install app: file not found ####
Xamarin has a [bug](https://forums.xamarin.com/discussion/103604/buildingproblem-after-update-to-ios-11) when building the project and installing it to a simulator where even if the app file is being generated correctly it is "not found". The current solution as stated in the referenced forum is 

> ... make sure you have tried some basic steps like deleting the bin and obj folders.  Also, clear the cache on the Mac just to be sure it's not related to that (delete ~/Users/Library/Caches/Xamarin/mtbs/builds). Make sure the Mac and Windows machines are up-to-date with the latest Stable versions of Xamarin.iOS and Xcode 9.
