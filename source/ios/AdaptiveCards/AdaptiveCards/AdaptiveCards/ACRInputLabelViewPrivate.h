//
//  ACRInputLabelViewPrivate
//  ACRInputLabelViewPrivate.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//
//

#import "ACRInputLabelView.h"
#import "BaseInputElement.h"
#import "SharedAdaptiveCard.h"

using namespace AdaptiveCards;

@interface ACRInputLabelView()

- (instancetype)initInputLabelView:(ACOHostConfig *)acoConfig adptiveInputElement:(const std::shared_ptr<BaseInputElement> &)inputBlck inputView:(UIView *)inputView viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup dataSource:(NSObject<ACRIBaseInputHandler> *)dataSource;

@end
