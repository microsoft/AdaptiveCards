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
#import "ACOHostConfigPrivate.h"
#import "ACOBaseActionElementPrivate.h"

@implementation ACRActionShowCardRenderer

+ (ACRActionShowCardRenderer *)getInstance
{
    static ACRActionShowCardRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton* )renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseActionElement> elem = [acoElem element];
    std::shared_ptr<ShowCardAction> action = std::dynamic_pointer_cast<ShowCardAction>(elem);

    NSString *title  = [NSString stringWithCString:action->GetTitle().c_str() encoding:NSUTF8StringEncoding];
    
    UIButton *button = [UIButton rootView:rootView baseActionElement:acoElem title:title andHostConfig:acoConfig];

    ACRShowCardTarget *target = [[ACRShowCardTarget alloc] initWithActionElement:action
                                                                          config:acoConfig
                                                                       superview:superview
                                                                        rootView:rootView];
    [button addTarget:target action:@selector(toggleVisibilityOfShowCard) forControlEvents:UIControlEventTouchUpInside];

    [superview addTarget:target];

    [target createShowCard:inputs];

    [button setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    
    [button setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];

    return button;
}
@end
