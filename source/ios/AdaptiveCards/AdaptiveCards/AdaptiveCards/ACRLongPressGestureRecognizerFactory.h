//
//  ACRLongPressGestureRecognizerFactory
//  ACRLongPressGestureRecognizerFactory.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import "BaseActionElement.h"
#import "ACRView.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"
#import "ACRLongPressGestureRecognizerEventHandler.h"

@interface ACRLongPressGestureRecognizerFactory:NSObject
/// instantiates a target for UITapGestureRecognizer object
/// and instantiate a tap gesture reconginizer with target, and return it
+ (void)addLongPressGestureRecognizerToUIView:(UIView<ACRIContentHoldingView> *)viewGroup
                                                               rootView:(ACRView *)rootView
                                                          recipientView:(UIView *)receipientView
                                                          actionElement:(std::shared_ptr<AdaptiveCards::BaseActionElement> const &)action
                                                             hostConfig:(ACOHostConfig *)config;

+ (UILongPressGestureRecognizer *)getGestureRecognizer:(UIView<ACRIContentHoldingView> *)viewGroup
                                                target:(NSObject<ACRSelectActionDelegate> *)target;
@end
