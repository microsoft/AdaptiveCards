//
//  ACRButton
//  ACRButton.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"
#import "ACRView.h"

@interface UIButton(ACRButton)
+ (UIButton *)acr_renderButton:(ACRView *)view
                         title:(NSString *)title
                       iconUrl:(NSString *)iconUrl
                 andHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;

+ (UIImage *)scaleImage:(UIImage *)image toSize:(CGSize)newSize;
@end
