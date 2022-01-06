//
//  ACRInputLabelViewPrivate
//  ACRInputLabelViewPrivate.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//
//

#import <AdaptiveCards/ACRInputLabelView.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/BaseInputElement.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>

using namespace AdaptiveCards;

@interface ACRInputLabelView ()

- (instancetype)initInputLabelView:(ACRView *)rootView acoConfig:(ACOHostConfig *)acoConfig adptiveInputElement:(const std::shared_ptr<BaseInputElement> &)inputBlck inputView:(UIView *)inputView accessibilityItem:(UIView *)accessibilityItem viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup dataSource:(NSObject<ACRIBaseInputHandler> *)dataSource;

@end
