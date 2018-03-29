//
//  ACRActionSubmitRenderer
//  ACRActionSubmitRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseActionElementRenderer.h"
#import "ACRActionSubmitRenderer.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRButton.h"
#import "ACRAggregateTarget.h"
#import "SubmitAction.h"

@implementation ACRActionSubmitRenderer

+ (ACRActionSubmitRenderer *)getInstance
{
    static ACRActionSubmitRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(ACRView *)view
                    inputs:(NSArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseActionElement> elem = [acoElem element];
    std::shared_ptr<SubmitAction> action = std::dynamic_pointer_cast<SubmitAction>(elem);

    NSString *title = [NSString stringWithCString:action->GetTitle().c_str()
                                        encoding:NSUTF8StringEncoding];
    UIButton *button = [UIButton acr_renderButton:view title:title andHostConfig:config];

    ACRAggregateTarget *target = [[ACRAggregateTarget alloc] initWithActionElement:acoElem rootView:(ACRView*)view];

    [button addTarget:target action:@selector(send:) forControlEvents:UIControlEventTouchUpInside];

    [superview addTarget:target];

    [superview addArrangedSubview:button];

    return button;
}
@end
