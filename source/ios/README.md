# Adaptive Cards in iOS

To install:

please add the following to Podfile
pod 'AdaptiveCards'

if you already know cocoapods, you can skip ahead to creating sample section
you can learn more about AdaptiveCards pod  here https://cocoapods.org/?q=ADaptiveCArds
To learn more about cocoapods in general check here https://guides.cocoapods.org
To learn more about cocoapods installation check here https://guides.cocoapods.org/using/getting-started.html
To learn more about pod installation check here https://guides.cocoapods.org/using/the-podfile.html

at the terminal run:
$pod install
please note Podfile and Xcode project file have to be in the same directory
please remember to run pod repo update to get latest patches 

$open yourworkspace

Creating Sample App

Add following 
#import <AdaptiveCards/ACFramework.h>



Given following json NSString,
NSString *str = 
@"{\n\
      \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\n\
      \"type\": \"AdaptiveCard\",\n\
      \"version\": \"0.5\",\n\
      \"body\": [\n\
          {\n\
              \"type\": \"Container\",\n\
              \"items\": [\n\
                  {\n\
                      \"type\": \"TextBlock\",\n\
                      \"text\": \"Meow!\"\n\
                  },\n\
                  {\n\
                      \"type\": \"Image\",\n\
                      \"url\": \"http://adaptivecards.io/api/cat\"\n\
                  }\n\
              ],\n\
              \"selectAction\": {\n\
                  \"type\": \"Action.OpenUrl\",\n\
                  \"title\": \"cool link\",\n\
                  \"url\": \"https://www.youtube.com/watch?v=dQw4w9WgXcQ\"\n\
              }\n\
          }\n\
      ]\n\
  }";

AdaptiveCards renderer will return a ViewController

ACRViewController *vc = [[ACRViewController alloc] init:str withFrame:CGRectMake(20,10,100,200)];
[self.view addSubview:vc.view];

Please view sure to add exceptions for specific domains in info.plist or add following to info.plist 
<key>NSAppTransportSecurity</key>
    <dict>
     <key>NSAllowsArbitraryLoads</key>
     <true/>
    </dict>
for more information on NSAppTransportSecurity check here https://developer.apple.com/library/content/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW33

To Do:
1. HostConfig
2. API update
3. Select Action

