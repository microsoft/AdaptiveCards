//
//  ACRActionSubmitRenderer
//  ACRActionSubmitRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionSubmitRenderer.h"
#import "ACRButton.h"
#import "ACRSubmitTarget.h"
#import "SubmitAction.h"

@implementation ACRActionSubmitRenderer

+ (ACRActionSubmitRenderer *)getInstance
{
    static ACRActionSubmitRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(UIViewController *)vc
                    inputs:(NSArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
{
    std::shared_ptr<SubmitAction> action = std::dynamic_pointer_cast<SubmitAction>(elem);
    
    NSString *title = [NSString stringWithCString:action->GetTitle().c_str()
                                        encoding:NSUTF8StringEncoding];
    UIButton *button = [UIButton acr_renderButton:vc title:title andHostConfig:config];

    NSString *data = [NSString stringWithCString:action->GetDataJson().c_str()
                                        encoding:NSUTF8StringEncoding];
    ACRSubmitTarget *target = [[ACRSubmitTarget alloc] initWithDataString:data
                                                                   inputs:inputs
                                                                       vc:vc];
                               
    [button addTarget:target action:@selector(submit:) forControlEvents:UIControlEventTouchUpInside];
    
    [superview addTarget:target];

    [superview addArrangedSubview:button];
    
    return button;
}
@end
