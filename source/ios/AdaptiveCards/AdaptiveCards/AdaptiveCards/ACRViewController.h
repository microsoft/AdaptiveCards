//
//  ACRViewController.h
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"
#import "ACOWarning.h"
#import "ACRActionDelegate.h"
#else
#import <AdaptiveCards/ACOAdaptiveCard.h>
#import <AdaptiveCards/ACOHostConfig.h>
#import <AdaptiveCards/ACOWarning.h>
#import <AdaptiveCards/ACRActionDelegate.h>
#endif
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACRViewController : UIViewController

- (instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame delegate:(id<ACRActionDelegate>)acrActionDelegate;
@end
