//
//  ACRButton
//  ACRButton.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRButton.h"

@implementation UIButton(ACRButton)
+ (UIButton* )acr_renderButton:(UIViewController *)vc
                         title:(NSString *)title
                 andHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    [button setTitle:title forState:UIControlStateNormal];
    [button setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    [button setBackgroundColor:[UIColor colorWithRed:0.0
                                               green:122.0/255.0
                                                blue:1.0
                                               alpha:1.0]];
    
    CGSize contentSize = [button.titleLabel intrinsicContentSize];    
    button.frame = CGRectMake(0, 0, contentSize.width , contentSize.height);
    return button;
}
@end
