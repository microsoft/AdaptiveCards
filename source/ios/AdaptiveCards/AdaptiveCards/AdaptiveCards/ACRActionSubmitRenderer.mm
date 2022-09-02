//
//  ACRActionSubmitRenderer
//  ACRActionSubmitRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRActionSubmitRenderer.h>
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#import <AdaptiveCards/ACRButton.h>
#import <AdaptiveCards/SubmitAction.h>
#import <AdaptiveCards/UtiliOS.h>

@implementation ACRActionSubmitRenderer

+ (ACRActionSubmitRenderer *)getInstance
{
    static ACRActionSubmitRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton *)renderButton:(ACRView *)view
                    inputs:(NSArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseActionElement> elem = [acoElem element];
    std::shared_ptr<SubmitAction> action = std::dynamic_pointer_cast<SubmitAction>(elem);

    NSString *title = [NSString stringWithCString:action->GetTitle().c_str() encoding:NSUTF8StringEncoding];

    UIButton *button = [ACRButton rootView:view baseActionElement:acoElem title:title andHostConfig:acoConfig];

    ACRAggregateTarget *target;
    if (ACRRenderingStatus::ACROk == buildTargetForButton([view getActionsTargetBuilderDirector], acoElem, button, &target)) {
        [superview addTarget:target];
    }

    [button setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

    [button setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];

    return button;
}
@end
