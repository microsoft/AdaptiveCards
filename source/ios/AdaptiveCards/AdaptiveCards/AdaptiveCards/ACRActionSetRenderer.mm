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

    UIView<ACRIContentHoldingView> *childview = nil;
    AdaptiveCards::ActionsConfig adaptiveActionConfig = [config getHostConfig] -> GetActions();
    NSDictionary<NSString *, NSNumber *> *attributes =
        @{@"spacing" : [NSNumber numberWithInt:adaptiveActionConfig.buttonSpacing],
          @"distribution" : [NSNumber numberWithInt:UIStackViewDistributionFillProportionally]};

    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        childview = [[ACRColumnSetView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height) attributes:attributes];
        ((ACRColumnSetView *)childview).isActionSet = YES;
    } else {
        childview = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height) attributes:attributes];
        ((ACRColumnView *)childview).isActionSet = YES;
    }

    ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] init];
    ACRContentHoldingUIScrollView *containingView = [[ACRContentHoldingUIScrollView alloc] init];
    [superview addArrangedSubview:containingView];
    float accumulatedWidth = 0, accumulatedHeight = 0, spacing = adaptiveActionConfig.buttonSpacing, maxWidth = 0, maxHeight = 0;
    if (elems.empty()) {
        return containingView;
    }

    unsigned long uMaxActionsToRender = MIN(adaptiveActionConfig.maxActions, elems.size());

    if (uMaxActionsToRender < elems.size()) {
        [rootView addWarnings:ACRWarningStatusCode::ACRMaxActionsExceeded mesage:@"Some actions were not rendered due to exceeding the maximum number of actions allowed"];
    }

    for (auto i = 0; i < uMaxActionsToRender; i++) {
        const auto &elem = elems.at(i);
        ACRBaseActionElementRenderer *actionRenderer =
            [reg getActionRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if (actionRenderer == nil) {
            NSLog(@"Unsupported card action type:%d\n", (int)elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];

        NSUInteger numElem = [childview subviewsCounts];

        UIButton *button = nil;

        @try {
            if ([acoElem meetsRequirements:featureReg] == NO) {
                @throw [ACOFallbackException fallbackException];
            }
            button = [actionRenderer renderButton:rootView inputs:inputs superview:superview baseActionElement:acoElem hostConfig:config];
            [childview addArrangedSubview:button];
        } @catch (ACOFallbackException *exception) {
            handleActionFallbackException(exception,
                                          superview,
                                          rootView,
                                          inputs,
                                          acoElem,
                                          config,
                                          childview);
            NSUInteger count = [childview subviewsCounts];
            if (count > numElem) {
                UIView *view = [childview getLastSubview];
                if (view && [view isKindOfClass:[UIButton class]]) {
                    button = (UIButton *)view;
                }
            }
        }

        accumulatedWidth += [button intrinsicContentSize].width;
        accumulatedHeight += [button intrinsicContentSize].height;
        maxWidth = MAX(maxWidth, [button intrinsicContentSize].width);
        maxHeight = MAX(maxHeight, [button intrinsicContentSize].height);
    }

    float contentWidth = accumulatedWidth, contentHeight = accumulatedHeight;
    [childview adjustHuggingForLastElement];
    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        contentWidth += (elems.size() - 1) * spacing;
        contentHeight = maxHeight;
    } else {
        contentHeight += (elems.size() - 1) * spacing;
        contentWidth = maxWidth;
    }
    childview.frame = CGRectMake(0, 0, contentWidth, contentHeight);
    containingView.frame = CGRectMake(0, 0, superview.frame.size.width, contentHeight);
    containingView.translatesAutoresizingMaskIntoConstraints = NO;
    [containingView addSubview:childview];
    [NSLayoutConstraint constraintWithItem:containingView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:childview attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:containingView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:childview attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:containingView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:childview attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:containingView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:childview attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
    NSLayoutConstraint *hConstraint = [NSLayoutConstraint constraintWithItem:childview attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:containingView attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0];
    NSLayoutConstraint *vConstraint = [NSLayoutConstraint constraintWithItem:childview attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:containingView attribute:NSLayoutAttributeHeight multiplier:1.0 constant:0];

    hConstraint.active = YES;
    vConstraint.active = YES;

    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        hConstraint.priority = UILayoutPriorityDefaultLow;
        if (contentWidth > superview.frame.size.width) {
            containingView.showsHorizontalScrollIndicator = YES;
        } else {
            if (adaptiveActionConfig.actionAlignment == ActionAlignment::Stretch) {
                [NSLayoutConstraint constraintWithItem:containingView
                                             attribute:NSLayoutAttributeWidth
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:childview
                                             attribute:NSLayoutAttributeWidth
                                            multiplier:1.0
                                              constant:0]
                    .active = YES;
            }
        }
    } else {
        vConstraint.priority = UILayoutPriorityDefaultLow;
    }
    return containingView;
}

@end
