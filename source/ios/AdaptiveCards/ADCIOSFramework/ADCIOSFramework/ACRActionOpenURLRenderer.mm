//
//  ACRActionOpenURLRenderer
//  ACRActionOpenURLRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionOpenURLRenderer.h"
#import "OpenUrlAction.h"

@implementation ACRActionOpenURLRenderer

+ (ACRActionOpenURLRenderer *)getInstance
{
    static ACRActionOpenURLRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(UIViewController *)vc 
                 superview:(UIView *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
{
    std::shared_ptr<OpenUrlAction> action = std::dynamic_pointer_cast<OpenUrlAction>(elem);
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    NSString *title  = [NSString stringWithCString:action->GetTitle().c_str() 
                                          encoding:NSUTF8StringEncoding];
    [button setTitle:title forState:UIControlStateNormal];
    [button setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    [button setBackgroundColor:[UIColor colorWithRed:0.0 green:122.0/255.0 blue:1.0 alpha:1.0]];
    CGSize contentSize = [button.titleLabel intrinsicContentSize];
    button.frame = CGRectMake(0, 0, contentSize.width, contentSize.height);

    [superview addSubview:button];
    
    return button;
}
@end
