//
//  ACRRendererPrivate
//  ACRRendererPrivate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRBaseCardElementRenderer.h"
#import "ACRIContentHoldingView.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"
#import "ACRRenderer.h"

using namespace AdaptiveCards;

@interface ACRRenderer()

+ (UIView *)renderWithAdaptiveCards:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard
                             inputs:(NSMutableArray *)inputs
                           rootView:(ACRView *)rootView
                         guideFrame:(CGRect)guideFrame
                         hostconfig:(ACOHostConfig *)config;

+ (UIView<ACRIContentHoldingView> *)render:(UIView *)view
                                  rootView:(ACRView *)rootView
                                    inputs:(NSMutableArray *)inputs
                             withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
                             andHostConfig:(ACOHostConfig *)config;

+ (UIView<ACRIContentHoldingView> *)renderButton:(ACRView *)rootView
                                          inputs:(NSMutableArray *)inputs
                                       superview:(UIView<ACRIContentHoldingView> *)superview
                                     actionElems:(std::vector<std::shared_ptr<BaseActionElement>> const &)elems
                                      hostConfig:(ACOHostConfig *)config;
@end
