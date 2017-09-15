//
//  ACRActionShowCardRenderer
//  ACRActionShowCardRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionShowCardRenderer.h"
#import "ACRButton.h"
#import "ACRShowCardTarget.h"
#import "ShowCardAction.h"

@implementation ACRActionShowCardRenderer

+ (ACRActionShowCardRenderer *)getInstance
{
    static ACRActionShowCardRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(UIViewController *)vc
                    inputs:(NSArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
{
    std::shared_ptr<ShowCardAction> action = std::dynamic_pointer_cast<ShowCardAction>(elem);
    
    NSString *title  = [NSString stringWithCString:action->GetTitle().c_str()
                                          encoding:NSUTF8StringEncoding];
    UIButton *button = [UIButton acr_renderButton:vc title:title andHostConfig:config];
    
    ACRShowCardTarget *target = [[ACRShowCardTarget alloc] initWithAdaptiveCard:action->GetCard()
                                                                         config:config
                                                                      superview:superview
                                                                             vc:vc];
    [button addTarget:target
               action:@selector(showCard:)
     forControlEvents:UIControlEventTouchUpInside];
    
    [superview addTarget:target];

    [superview addArrangedSubview:button];
    
    return button;
}
@end
