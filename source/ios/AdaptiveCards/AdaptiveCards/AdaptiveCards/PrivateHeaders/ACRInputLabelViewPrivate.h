//
//  ACRInputLabelViewPrivate
//  ACRInputLabelViewPrivate.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRInputLabelView.h"
#import "ACRView.h"
#import "BaseInputElement.h"
#import "SharedAdaptiveCard.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRInputLabelView.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/BaseInputElement.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#endif

using namespace AdaptiveCards;

@interface ACRInputLabelView ()

- (instancetype)initInputLabelView:(ACRView *)rootView acoConfig:(ACOHostConfig *)acoConfig adaptiveInputElement:(const std::shared_ptr<BaseInputElement> &)inputBlck inputView:(UIView *)inputView accessibilityItem:(UIView *)accessibilityItem viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup dataSource:(NSObject<ACRIBaseInputHandler> *)dataSource;

@end
