//
//  ACRActionOpenURLRenderer
//  ACRActionOpenURLRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRButton.h"
#import "ACRAggregateTarget.h"
#import "OpenUrlAction.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRIContentHoldingView.h"
@implementation ACRActionOpenURLRenderer

+ (ACRActionOpenURLRenderer *)getInstance
{
    static ACRActionOpenURLRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseActionElement> elem = [acoElem element];
    std::shared_ptr<OpenUrlAction> action = std::dynamic_pointer_cast<OpenUrlAction>(elem);

    NSString *title  = [NSString stringWithCString:action->GetTitle().c_str() encoding:NSUTF8StringEncoding];
    
    UIButton *button = [UIButton acr_renderButton:rootView title:title andHostConfig:config];

    ACRAggregateTarget *target = [[ACRAggregateTarget alloc] initWithActionElement:acoElem rootView:(ACRView *)rootView];

    [button addTarget:target action:@selector(send:) forControlEvents:UIControlEventTouchUpInside];

    [superview addTarget:target];

    return button;
}
@end
