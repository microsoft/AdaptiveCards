//
//  ACRViewController.h
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"
#import <AdaptiveCards/ACOWarning.h>
#import <AdaptiveCards/ACRActionDelegate.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACRViewController : UIViewController

- (instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame delegate:(id<ACRActionDelegate>)acrActionDelegate;
@end
