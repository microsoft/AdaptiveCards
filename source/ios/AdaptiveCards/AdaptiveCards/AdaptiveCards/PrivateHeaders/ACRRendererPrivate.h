//
//  ACRRendererPrivate
//  ACRRendererPrivate.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRBaseCardElementRenderer.h"
#import "ACRIContentHoldingView.h"
#import "ACRRenderer.h"
#import "BackgroundImage.h"
#import "HostConfig.h"
#import "SharedAdaptiveCard.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRBaseCardElementRenderer.h>
#import <AdaptiveCards/ACRIContentHoldingView.h>
#import <AdaptiveCards/ACRRenderer.h>
#import <AdaptiveCards/BackgroundImage.h>
#import <AdaptiveCards/HostConfig.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#endif
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@interface ACRRenderer ()

+ (UIView *)renderWithAdaptiveCards:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard
                             inputs:(NSMutableArray *)inputs
                            context:(ACRView *)rootView
                     containingView:(ACRColumnView *)guideFrame
                         hostconfig:(ACOHostConfig *)config;

+ (UIView<ACRIContentHoldingView> *)render:(UIView *)view
                                  rootView:(ACRView *)rootView
                                    inputs:(NSMutableArray *)inputs
                             withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
                             andHostConfig:(ACOHostConfig *)config;

@end
