//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//

#import "ACRBaseCardElementRenderer.h"
#import "ACRIContentHoldingView.h"

@interface ACRRegistration:NSObject 

+ (ACRRegistration *)getInstance;

- (ACRBaseCardElementRenderer *)getRenderer:(NSNumber *) cardElementType;

- (UIView<ACRIContentHoldingView> *)render:(UIView *)view
                             withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
                             andHostConfig:(std::shared_ptr<HostConfig> const &)config;

- (UIView<ACRIContentHoldingView> *)renderButton:(UIViewController *)vc
                                       superview:(UIView<ACRIContentHoldingView> *)superview
                                     actionElems:(std::vector<std::shared_ptr<BaseActionElement>> const &)elems
                                      hostConfig:(std::shared_ptr<HostConfig> const &)config;
@end
