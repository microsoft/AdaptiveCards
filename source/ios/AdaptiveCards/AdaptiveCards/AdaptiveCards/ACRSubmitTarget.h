//
//  ACRSubmitTarget
//  ACRSubmitTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"

@interface ACRSubmitTarget:NSObject<ACRSelectActionDelegate>

- (instancetype)initWithDataString:(NSString *)data
                            inputs:(NSArray *)inputs
                                vc:(UIViewController *)vc;

- (IBAction)submit:(UIButton *)sender;

@end
