# Adaptive Cards in iOS

To install:

please add the following to Podfile
pod 'AdaptiveCards'

if you already know cocoapods, you can skip ahead to creating sample app section
you can learn more about AdaptiveCards pod  here https://cocoapods.org/?q=ADaptiveCArds
To learn more about cocoapods in general check here https://guides.cocoapods.org
To learn more about cocoapods installation check here https://guides.cocoapods.org/using/getting-started.html
To learn more about pod installation check here https://guides.cocoapods.org/using/the-podfile.html

at the terminal run:
$pod install
please note Podfile and Xcode project file have to be in the same directory
please remember to run pod repo update to get latest patches 


AdaptiveCards renderer will return a ViewController

[self.view addSubview:vc.view];

Please be sure to add exceptions for specific domains to info.plist or add the following to info.plist 
<key>NSAppTransportSecurity</key>
    <dict>
     <key>NSAllowsArbitraryLoads</key>
     <true/>
    </dict>
for more information on NSAppTransportSecurity plese check here https://developer.apple.com/library/content/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW33

To Do:
1. Select Action
