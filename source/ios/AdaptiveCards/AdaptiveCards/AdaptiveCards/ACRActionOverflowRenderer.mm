//
//  ACRActionOverflowRenderer
//  ACRActionOverflowRenderer.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRActionOverflowRenderer.h"
#import "ACOActionOverflow.h"
#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRButton.h"
#import "ACRIContentHoldingView.h"
#import "ACROverflowTarget.h"
#import "ACRView.h"
#import "UtiliOS.h"
#else
#import <AdaptiveCards/ACRActionOverflowRenderer.h>
#import <AdaptiveCards/ACOActionOverflow.h>
#import <AdaptiveCards/ACOAdaptiveCardPrivate.h>
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACRButton.h>
#import <AdaptiveCards/ACRIContentHoldingView.h>
#import <AdaptiveCards/ACROverflowTarget.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/UtiliOS.h>
#endif

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
    if (acoElem.type == ACRActionType::ACROverflow) {
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
            // to support Action.ShowCard in menu item action, this line is required
            [target setInputs:inputs superview:superview];
        }

        [button setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                forAxis:UILayoutConstraintAxisVertical];

        [button setContentCompressionResistancePriority:UILayoutPriorityRequired
                                                forAxis:UILayoutConstraintAxisHorizontal];

        BOOL shouldRender = YES;
        if ([rootView.acrActionDelegate
                respondsToSelector:@selector(onRenderOverflowAction:
                                                          forTarget:
                                                          isAtRootLevelActions:)]) {

            BOOL isAtRootLevelActions = ((ACOActionOverflow *)acoElem).isAtRootLevel;

            shouldRender =
                ![rootView.acrActionDelegate onRenderOverflowAction:(ACRButton *)button
                                                          forTarget:target
                                               isAtRootLevelActions:isAtRootLevelActions];
        }

        if (shouldRender) {
            return button;
        }
    }
    return nil;
}

@end
