//
//  ACRActionOpenURLRenderer
//  ACRActionOpenURLRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRButton.h"
#import "ACROpenURLTarget.h"
#import "OpenUrlAction.h"

@implementation ACRActionOpenURLRenderer

+ (ACRActionOpenURLRenderer *)getInstance
{
    static ACRActionOpenURLRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(UIViewController *)vc
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
{
    std::shared_ptr<OpenUrlAction> action = std::dynamic_pointer_cast<OpenUrlAction>(elem);
    
    NSString *title  = [NSString stringWithCString:action->GetTitle().c_str()
                                          encoding:NSUTF8StringEncoding];
    UIButton *button = [UIButton acr_renderButton:vc title:title andHostConfig:config];
    NSString *urlStr = [NSString stringWithCString:action->GetUrl().c_str()
                                          encoding:[NSString defaultCStringEncoding]];
    NSURL *url = [NSURL URLWithString:urlStr];
    
    ACROpenURLTarget *target = [[ACROpenURLTarget alloc] initWithURL:url viewController:vc];
    [button addTarget:target action:@selector(openURL) forControlEvents:UIControlEventTouchUpInside];
    [superview addTarget:target];

    [superview addArrangedSubview:button];
    
    return button;
}
@end
