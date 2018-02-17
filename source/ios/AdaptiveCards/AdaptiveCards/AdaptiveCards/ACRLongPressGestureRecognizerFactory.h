//
//  ACRLongPressGestureRecognizerFactory
//  ACRLongPressGestureRecognizerFactory.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "BaseActionElement.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"
#import "HostConfig.h"

@interface ACRLongPressGestureRecognizerFactory:NSObject
/// instantiates a target for UITapGestureRecognizer object
/// and instantiate a tap gesture reconginizer with target, and return it
+ (UILongPressGestureRecognizer *)getLongPressGestureRecognizer:(UIView<ACRIContentHoldingView> *)viewGroup
                                             rootViewController:(UIViewController *)vc
                                                     targetView:(UIView *)view
                                                  actionElement:(std::shared_ptr<AdaptiveCards::BaseActionElement> const &)action
                                                         inputs:(NSMutableArray *)inputs
                                                     hostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
@end
