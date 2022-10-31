//
//  ACRInputLabelViewPrivate
//  ACRInputLabelViewPrivate.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//
//

#import "ACRInputLabelView.h"
#import "ACRView.h"
#import "BaseInputElement.h"
#import "SharedAdaptiveCard.h"

using namespace AdaptiveCards;

@interface ACRInputLabelView ()

- (instancetype)initInputLabelView:(ACRView *)rootView acoConfig:(ACOHostConfig *)acoConfig adaptiveInputElement:(const std::shared_ptr<BaseInputElement> &)inputBlck inputView:(UIView *)inputView accessibilityItem:(UIView *)accessibilityItem viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup dataSource:(NSObject<ACRIBaseInputHandler> *)dataSource;

@end
