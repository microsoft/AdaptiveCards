//
//  ACRActionOverflowRenderer
//  ACRActionOverflowRenderer.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRActionOverflowRenderer.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRView.h"
#import "ACRIContentHoldingView.h"
#import "ACOActionOverflow.h"
#import "ACRButton.h"
#import "ACROverflowTarget.h"
#import "ACOAdaptiveCardPrivate.h"
#import "UtiliOS.h"

@implementation ACRActionOverflowRenderer

+ (ACRActionOverflowRenderer *)getInstance
{
    static ACRActionOverflowRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIButton *)renderButton:(ACRView *)rootView
                    inputs:(NSMutableArray *)inputs
                 superview:(UIView<ACRIContentHoldingView> *)superview
         baseActionElement:(ACOBaseActionElement *)acoElem
                hostConfig:(ACOHostConfig *)acoConfig;
{
    if ([acoElem isKindOfClass:[ACOActionOverflow class]]) {
        NSString *title = @"...";
        UIButton *button = [ACRButton rootView:rootView
                             baseActionElement:acoElem
                                         title:title
                                 andHostConfig:acoConfig];

        ACROverflowTarget *target;
        ACRTargetBuilderDirector *director = [rootView getActionsTargetBuilderDirector];
        ACRRenderingStatus status = buildTargetForButton(director, acoElem, button, &target);
        if (ACRRenderingStatus::ACROk == status) {
            [superview addTarget:target];
            [target setInputs:inputs superview:superview];
        }
        
        button.accessibilityTraits |= UIAccessibilityTraitLink;

        [button setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                forAxis:UILayoutConstraintAxisVertical];

        [button setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                forAxis:UILayoutConstraintAxisHorizontal];

        BOOL shouldRender = YES;
        if ([rootView.acrActionDelegate
             respondsToSelector:@selector(shouldRenderOverflowActionButton:
                                          forTarget:
                                          isAtRootLevelActions:)]) {
            BOOL isAtRootLevelActions = [self isAtRootLevelActions:(ACOActionOverflow*)acoElem
                                                              card:rootView.card];
            shouldRender =
                [rootView.acrActionDelegate shouldRenderOverflowActionButton:(ACRButton*)button
                                                                   forTarget:target
                                                        isAtRootLevelActions:isAtRootLevelActions];
        }

        if (shouldRender) {
            return button;
        }
    }
    return nil;
}

- (BOOL) isAtRootLevelActions:(ACOActionOverflow*) acoElem
                         card:(ACOAdaptiveCard*) card
{
    auto& rootActions = card.card->GetActions();
    for (ACOBaseActionElement* action in acoElem.menuActions) {
        auto it = std::find(std::begin(rootActions),
                            std::end(rootActions),
                            action.element);
        if (it != std::end(rootActions)) {
            return YES;
        }
    }
    return NO;
}
@end
