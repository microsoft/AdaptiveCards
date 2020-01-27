# Adaptive Cards in iOS

## Cocoapods Resources
To learn more about AdaptiveCards pod  here https://cocoapods.org/?q=ADaptiveCArds
To learn more about cocoapods in general check here https://guides.cocoapods.org
To learn more about cocoapods installation check here https://guides.cocoapods.org/using/getting-started.html
To learn more about pod integration with xcode projects check here https://guides.cocoapods.org/using/using-cocoapods.html


## Adding AdaptiveCards Pod

Podfile
```
pod 'AdaptiveCards'
```
Terminal
```
$pod install
```

Please note Podfile and Xcode project file have to be in the same directory
Please remember to run pod repo update to get latest patches 


## Example Code in Objective-C, Swift

### Step 1 

ViewController.h
```
#import <UIKit/UIKit.h>
#import <AdaptiveCards/ACFramework.h>
@interface ViewController : UIViewController<ACRActionDelegate>


@end
```

ViewController.m
```
#import "ViewController.h"
#import <SafariServices/SafariServices.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    NSString *jsonStr = @"{ \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"Image\", \"url\": \"http://adaptivecards.io/content/adaptive-card-50.png\", \"horizontalAlignment\":\"center\" }, { \"type\": \"TextBlock\", \"horizontalAlignment\":\"center\", \"text\": \"Hello **Adaptive Cards!**\" } ], \"actions\": [ { \"type\": \"Action.OpenUrl\", \"title\": \"Learn more\", \"url\": \"http://adaptivecards.io\" }, { \"type\": \"Action.OpenUrl\", \"title\": \"GitHub\", \"url\": \"http://github.com/Microsoft/AdaptiveCards\" } ] }";
    ACRRenderResult *renderResult;
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:jsonStr];
    // Patch for issue 3741 [https://github.com/microsoft/AdaptiveCards/issues/3741]
    ACOHostConfig *_config = [[ACOHostConfig alloc] init];
    if(cardParseResult.isValid){
        renderResult = [ACRRenderer render:cardParseResult.card config:_config widthConstraint:335];
    }

    if(renderResult.succeeded)
    {
        ACRView *ad = renderResult.view;
        ad.acrActionDelegate = self;
        
        UIView *view = self.view;
        view.autoresizingMask |= UIViewAutoresizingFlexibleHeight;
        [self.view addSubview:ad];
        ad.translatesAutoresizingMaskIntoConstraints = NO;
        
        [NSLayoutConstraint constraintWithItem:ad attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;

        [NSLayoutConstraint constraintWithItem:ad attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:view attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:3].active = YES;
    }
}

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action
{
    if(action.type == ACROpenUrl){
        NSURL *url = [NSURL URLWithString:[action url]];
        SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:url];
        [self presentViewController:svc animated:YES completion:nil];
    }
}

@end
```

### Step 2 
Allow Image Downloading

Please be sure to add exceptions for specific domains to info.plist or add the following to info.plist 
```
<key>NSAppTransportSecurity</key>
    <dict>
     <key>NSAllowsArbitraryLoads</key>
     <true/>
    </dict>
```
For more information on NSAppTransportSecurity plese check here https://developer.apple.com/library/content/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW33

### Step 3
Add SafariServices.framework for openning web pages
project file -> Targets -> Linked Frameworks and Libraries -> add

## Example Code in Swift: Bridging Header

### Step 1 
Add AdaptiveCards pod to Podfile
Create and add a bridge header 
Helpful guide: https://mycodetips.com/ios/manually-adding-swift-bridging-header-1290.html


### Step 2 
ViewController.swft

```
import UIKit
import SafariServices

class ViewController: UIViewController, ACRActionDelegate{

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let jsonStr = "{ \"type\": \"AdaptiveCard\", \"version\": \"1.0\", \"body\": [ { \"type\": \"Image\", \"url\": \"http://adaptivecards.io/content/adaptive-card-50.png\", \"horizontalAlignment\":\"center\" }, { \"type\": \"TextBlock\", \"horizontalAlignment\":\"center\", \"text\": \"Hello **Adaptive Cards!**\" } ], \"actions\": [ { \"type\": \"Action.OpenUrl\", \"title\": \"Learn more\", \"url\": \"http://adaptivecards.io\" }, { \"type\": \"Action.OpenUrl\", \"title\": \"GitHub\", \"url\": \"http://github.com/Microsoft/AdaptiveCards\" } ] }";

        let cardParseResult = ACOAdaptiveCard.fromJson(jsonStr);
        if((cardParseResult?.isValid)!){
            // Patch for issue 3741 [https://github.com/microsoft/AdaptiveCards/issues/3741]
            let _config = ACOHostConfig();
            let renderResult = ACRRenderer.render(cardParseResult!.card, config: _config, widthConstraint: 335);

            if(renderResult?.succeeded ?? false)
            {
                let ad = renderResult?.view;
                ad!.acrActionDelegate = (self as ACRActionDelegate);
                self.view.autoresizingMask = [.flexibleHeight];
                self.view.addSubview(ad!);
                ad!.translatesAutoresizingMaskIntoConstraints = false;
    
                NSLayoutConstraint(item: ad!, attribute: .centerX, relatedBy: .equal, toItem: view, attribute: .centerX, multiplier: 1.0, constant: 0).isActive = true;
                NSLayoutConstraint(item: ad!, attribute: .centerY, relatedBy: .equal, toItem: view, attribute: .centerY, multiplier: 1.0, constant: 3).isActive = true;
            }
        }
    }
    
    func didFetchUserResponses(_ card: ACOAdaptiveCard, action: ACOBaseActionElement)
    {
        if(action.type == ACRActionType.openUrl){
            let url = URL.init(string:action.url());
            let svc = SFSafariViewController.init(url: url!);
            self.present(svc, animated: true, completion: nil);
        }
    }

}
```
### Step 3 
Allow Image Downloading

Please be sure to add exceptions for specific domains to info.plist or add the following to info.plist 
```
<key>NSAppTransportSecurity</key>
    <dict>
     <key>NSAllowsArbitraryLoads</key>
     <true/>
    </dict>
 ```
For more information on NSAppTransportSecurity plese check here https://developer.apple.com/library/content/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW33

### Step 4
Add SafariServices.framework for openning web pages
project file -> Targets -> Linked Frameworks and Libraries -> add

