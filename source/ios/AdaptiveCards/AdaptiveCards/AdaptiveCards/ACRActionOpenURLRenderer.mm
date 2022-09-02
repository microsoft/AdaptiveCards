//
//  ACRActionOpenURLRenderer
//  ACRActionOpenURLRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRActionOpenURLRenderer.h>
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/ACRBaseActionElementRenderer.h>
#import <AdaptiveCards/ACRButton.h>
#import <AdaptiveCards/ACRIContentHoldingView.h>
#import <AdaptiveCards/OpenUrlAction.h>
#import <AdaptiveCards/UtiliOS.h>

@implementation ACRActionOpenURLRenderer

+ (ACRActionOpenURLRenderer *)getInstance
{
    static ACRActionOpenURLRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton *)renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<BaseActionElement> elem = [acoElem element];
    std::shared_ptr<OpenUrlAction> action = std::dynamic_pointer_cast<OpenUrlAction>(elem);

    NSString *title = [NSString stringWithCString:action->GetTitle().c_str() encoding:NSUTF8StringEncoding];

    UIButton *button = [ACRButton rootView:rootView baseActionElement:acoElem title:title andHostConfig:acoConfig];

    ACRAggregateTarget *target;
    if (ACRRenderingStatus::ACROk == buildTargetForButton([rootView getActionsTargetBuilderDirector], acoElem, button, &target)) {
        [superview addTarget:target];
    }

    button.accessibilityTraits |= UIAccessibilityTraitLink;
    button.accessibilityTraits &= ~UIAccessibilityTraitButton;

    [button setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

    [button setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];

    return button;
}
@end
