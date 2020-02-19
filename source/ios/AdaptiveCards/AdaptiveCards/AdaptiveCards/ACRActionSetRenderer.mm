//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRActionSetRenderer.h"
#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRBaseActionElementRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRColumnView.h"
#import "ACRContentHoldingUIScrollView.h"
#import "ACRIContentHoldingView.h"
#import "ACRRegistration.h"
#import "ACRRenderer.h"
#import "ActionSet.h"
#import "UtiliOS.h"

@implementation ACRActionSetRenderer

+ (ACRCardElementType)elemType
{
    return ACRActionSet;
}

+ (ACRActionSetRenderer *)getInstance
{
    static ACRActionSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup rootView:(ACRView *)rootView inputs:(NSArray *)inputs baseCardElement:(ACOBaseCardElement *)acoElem hostConfig:(ACOHostConfig *)acoConfig
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ActionSet> actionSetElem = std::dynamic_pointer_cast<ActionSet>(elem);
    return [self renderButtons:rootView inputs:(NSMutableArray *)inputs superview:viewGroup elems:actionSetElem->GetActions() hostConfig:acoConfig];
}

- (UIView *)renderButtons:(ACRView *)rootView
                   inputs:(NSMutableArray *)inputs
                superview:(UIView<ACRIContentHoldingView> *)superview
                     card:(ACOAdaptiveCard *)card
               hostConfig:(ACOHostConfig *)config
{
    std::vector<std::shared_ptr<BaseActionElement>> elems = [card card] -> GetActions();
    return [self renderButtons:rootView
                        inputs:inputs
                     superview:superview
                         elems:elems
                    hostConfig:config];
}

- (UIView *)renderButtons:(ACRView *)rootView
                   inputs:(NSMutableArray *)inputs
                superview:(UIView<ACRIContentHoldingView> *)superview
                    elems:(const std::vector<std::shared_ptr<BaseActionElement>> &)elems
               hostConfig:(ACOHostConfig *)config
{
    ACRRegistration *reg = [ACRRegistration getInstance];
    ACOFeatureRegistration *featureReg = [ACOFeatureRegistration getInstance];

    ACRContentStackView *contentview = nil;
    AdaptiveCards::ActionsConfig adaptiveActionConfig = [config getHostConfig] -> GetActions();
    NSDictionary<NSString *, NSNumber *> *attributes =
        @{@"spacing" : [NSNumber numberWithInt:adaptiveActionConfig.buttonSpacing],
          @"distribution" : [NSNumber numberWithInt:UIStackViewDistributionFillProportionally]};

    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        contentview = [[ACRColumnSetView alloc] initWithFrame:CGRectZero attributes:attributes];
        ((ACRColumnSetView *)contentview).isActionSet = YES;
    } else {
        contentview = [[ACRColumnView alloc] initWithFrame:CGRectZero attributes:attributes];
        ((ACRColumnView *)contentview).isActionSet = YES;
    }

    ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] init];
    ACRContentHoldingUIScrollView *scrollview = [[ACRContentHoldingUIScrollView alloc] init];
    float spacing = adaptiveActionConfig.buttonSpacing;
    if (elems.empty()) {
        return scrollview;
    }

    unsigned long uMaxActionsToRender = MIN(adaptiveActionConfig.maxActions, elems.size());

    if (uMaxActionsToRender < elems.size()) {
        [rootView addWarnings:ACRWarningStatusCode::ACRMaxActionsExceeded mesage:@"Some actions were not rendered due to exceeding the maximum number of actions allowed"];
    }

    [superview addArrangedSubview:scrollview];
    for (auto i = 0; i < uMaxActionsToRender; i++) {
        const auto &elem = elems.at(i);
        ACRBaseActionElementRenderer *actionRenderer =
            [reg getActionRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if (actionRenderer == nil) {
            NSLog(@"Unsupported card action type:%d\n", (int)elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];

        NSUInteger numElem = [contentview subviewsCounts];

        UIButton *button = nil;

        @try {
            if ([acoElem meetsRequirements:featureReg] == NO) {
                @throw [ACOFallbackException fallbackException];
            }
            button = [actionRenderer renderButton:rootView inputs:inputs superview:superview baseActionElement:acoElem hostConfig:config];
            [contentview addArrangedSubview:button];
        } @catch (ACOFallbackException *exception) {
            handleActionFallbackException(exception,
                                          superview,
                                          rootView,
                                          inputs,
                                          acoElem,
                                          config,
                                          contentview);
            NSUInteger count = [contentview subviewsCounts];
            if (count > numElem) {
                UIView *view = [contentview getLastSubview];
                if (view && [view isKindOfClass:[UIButton class]]) {
                    button = (UIButton *)view;
                }
            }
        }
    }

    [contentview adjustHuggingForLastElement];

    CGSize spacingSize = CGSizeMake(0, 0);
    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        spacingSize.width = (elems.size() - 1) * spacing;
    } else {
        spacingSize.height = (elems.size() - 1) * spacing;
    }

    [contentview increaseIntrinsicContentSizeBySize:spacingSize];

    CGSize contentviewIntrinsicContentSize = [contentview intrinsicContentSize];
    scrollview.translatesAutoresizingMaskIntoConstraints = NO;
    [scrollview addSubview:contentview];
    scrollview.contentSize = contentviewIntrinsicContentSize;
    [(ACRContentStackView *)superview increaseIntrinsicContentSizeBySize:[scrollview intrinsicContentSize]];

    [NSLayoutConstraint constraintWithItem:scrollview attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:contentview attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:scrollview attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:contentview attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
    NSLayoutConstraint *hConstraint = [NSLayoutConstraint constraintWithItem:contentview attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:scrollview attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0];
    NSLayoutConstraint *vConstraint = [NSLayoutConstraint constraintWithItem:contentview attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:scrollview attribute:NSLayoutAttributeHeight multiplier:1.0 constant:0];

    hConstraint.active = YES;
    vConstraint.active = YES;

    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        hConstraint.priority = UILayoutPriorityDefaultLow;
        if (adaptiveActionConfig.actionAlignment == ActionAlignment::Stretch) {
            [NSLayoutConstraint constraintWithItem:scrollview
                                         attribute:NSLayoutAttributeWidth
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:contentview
                                         attribute:NSLayoutAttributeWidth
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
        }
    } else {
        vConstraint.priority = UILayoutPriorityDefaultLow;
    }
    return scrollview;
}

@end
