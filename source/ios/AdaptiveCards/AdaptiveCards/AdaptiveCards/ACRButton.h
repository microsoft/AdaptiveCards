//
//  ACRButton
//  ACRButton.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface UIButton(ACRButton)
+ (UIButton *)acr_renderButton:(UIView *)view
                         title:(NSString *)title
                 andHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
@end
