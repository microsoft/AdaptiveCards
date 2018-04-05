//
//  ACRButton
//  ACRButton.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRButton.h"

@implementation UIButton(ACRButton)
-(instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    return self;
}
+ (UIButton* )acr_renderButton:(UIView *)view
                         title:(NSString *)title
                 andHostConfig:(std::shared_ptr<AdaptiveCards::HostConfig> const &)config;
{
    NSBundle* bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    UIButton *button = [bundle loadNibNamed:@"ACRButton" owner:view options:nil][0];
#if 0
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
#endif
    [button setTitle:title forState:UIControlStateNormal];
    //[button setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    /*[button setBackgroundColor:[UIColor colorWithRed:0.0
                                               green:122.0/255.0
                                                blue:1.0
                                               alpha:1.0]];*/

    CGSize contentSize = [button.titleLabel intrinsicContentSize];
    button.frame = CGRectMake(0, 0, contentSize.width, contentSize.height);
    button.contentEdgeInsets = UIEdgeInsetsMake(5,5,5,5);
    return button;
}
@end
