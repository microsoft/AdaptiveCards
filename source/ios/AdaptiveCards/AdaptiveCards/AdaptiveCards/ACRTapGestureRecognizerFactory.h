//
//  ACRTapGestureRecognizerFactory
//  ACRTapGestureRecognizerFactory.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "ACRIBaseCardElementRenderer.h"

@interface ACRTapGestureRecognizerFactory:NSObject
/// instantiates a target for UITapGestureRecognizer object
/// and instantiate a tap gesture reconginizer with target, and return it
+ (UITapGestureRecognizer *)getTapGestureRecognizer:(UIView<ACRIContentHoldingView> *)viewGroup
                                 rootViewController:(UIViewController *)vc
                                      actionElement:(std::shared_ptr<BaseActionElement> const &)action
                                             inputs:(NSMutableArray *)inputs
                                         hostConfig:(std::shared_ptr<HostConfig> const &)config;
@end
