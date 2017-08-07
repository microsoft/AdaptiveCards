//
//  ACRActionHttpRenderer
//  ACRActionHttpRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionHttpRenderer.h"
#import "ACRButton.h"
#import "ACRHttpTarget.h"
#import "HttpAction.h"

@implementation ACRActionHttpRenderer

+ (ACRActionHttpRenderer *)getInstance
{
    static ACRActionHttpRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(UIViewController *)vc
                    inputs:(NSArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(std::shared_ptr<BaseActionElement> const &)elem
             andHostConfig:(std::shared_ptr<HostConfig> const &)config;
{
    std::shared_ptr<HttpAction> action = std::dynamic_pointer_cast<HttpAction>(elem);
    
    NSString *title = [NSString stringWithCString:action->GetTitle().c_str()
                                        encoding:NSUTF8StringEncoding];
    UIButton *button = [UIButton acr_renderButton:vc title:title andHostConfig:config];
    
    ACRHttpTarget *target = [[ACRHttpTarget alloc] initWithHttpAction:action inputs:inputs vc:vc];
    
    [button addTarget:target action:@selector(create:) forControlEvents:UIControlEventTouchUpInside];
    
    [superview addTarget:target];

    [superview addArrangedSubview:button];
    
    return button;
}
@end
