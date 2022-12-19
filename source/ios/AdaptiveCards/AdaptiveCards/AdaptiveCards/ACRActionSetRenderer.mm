//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRActionSetRenderer.h"
#import "ACOActionOverflowPrivate.h"
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

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ActionSet> actionSetElem = std::dynamic_pointer_cast<ActionSet>(elem);
    [[rootView card] setInputs:inputs];
    UIView *containingView = [self renderButtons:rootView
                                          inputs:(NSMutableArray *)inputs
                                       superview:viewGroup
                                           elems:actionSetElem->GetActions()
                                      hostConfig:acoConfig];
    configVisibility(containingView, elem);
    return containingView;
}

- (UIView *)renderButtons:(ACRView *)rootView
                   inputs:(NSMutableArray *)inputs
                superview:(UIView<ACRIContentHoldingView> *)superview
                     card:(ACOAdaptiveCard *)card
               hostConfig:(ACOHostConfig *)config
{
    std::vector<std::shared_ptr<BaseActionElement>> elems = [card card]->GetActions();
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

    UIStackView *childview = [[UIStackView alloc] init];

    configRtl(childview, rootView.context);

    childview.distribution = UIStackViewDistributionFillProportionally;
    AdaptiveCards::ActionsConfig adaptiveActionConfig = [config getHostConfig]->GetActions();

    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        childview.axis = UILayoutConstraintAxisHorizontal;
    } else {
        childview.axis = UILayoutConstraintAxisVertical;
        UIStackViewAlignment alignment;
        switch (adaptiveActionConfig.actionAlignment) {
            case ActionAlignment::Center:
                alignment = UIStackViewAlignmentCenter;
                break;
            case ActionAlignment::Left:
                alignment = UIStackViewAlignmentLeading;
                break;
            case ActionAlignment::Right:
                alignment = UIStackViewAlignmentTrailing;
                break;
            default:
                alignment = UIStackViewAlignmentFill;
        }
        childview.alignment = alignment;
    }

    // set width
    ACRContentHoldingUIScrollView *containingView = [[ACRContentHoldingUIScrollView alloc] init];

    configRtl(containingView, rootView.context);

    float accumulatedWidth = 0, accumulatedHeight = 0, spacing = adaptiveActionConfig.buttonSpacing,
          maxWidth = 0, maxHeight = 0;
    childview.spacing = spacing;
    containingView.spacing = spacing;
    childview.translatesAutoresizingMaskIntoConstraints = NO;

    if (elems.empty()) {
        return containingView;
    }

    std::vector<std::shared_ptr<BaseActionElement>> primary, secondary;
    partitionActions(elems, primary, secondary, adaptiveActionConfig.maxActions, rootView);

    NSUInteger stackIndex = [superview arrangedSubviewsCounts];
    NSUInteger accessibilityIndex = superview.accessibilityElements.count;

    std::size_t renderedBtnNum = primary.size();
    for (auto i = 0; i < primary.size(); i++) {
        const auto &elem = primary.at(i);
        ACRBaseActionElementRenderer *actionRenderer =
            [reg getActionRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if (actionRenderer == nil) {
            NSLog(@"Unsupported card action type:%d\n", (int)elem->GetElementType());
            continue;
        }

        ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] initWithBaseActionElement:elem];

        [self renderButtonForElem:acoElem
                   actionRenderer:actionRenderer
                        childview:childview
                       featureReg:featureReg
                         rootView:rootView
                           inputs:inputs
                        superview:superview
                       hostConfig:config
                 accumulatedWidth:accumulatedWidth
                accumulatedHeight:accumulatedHeight
                         maxWidth:maxWidth
                        maxHeight:maxHeight];
    }

    if (!secondary.empty()) {
        ++renderedBtnNum;

        ACRBaseActionElementRenderer *actionRenderer =
            [reg getActionRenderer:[ACOBaseActionElement getKey:(ACRActionType::ACROverflow)]];

        ACOBaseActionElement *overflow =
            [[ACOActionOverflow alloc] initWithBaseActionElements:secondary
                                                           atCard:rootView.card];

        [self renderButtonForElem:overflow
                   actionRenderer:actionRenderer
                        childview:childview
                       featureReg:featureReg
                         rootView:rootView
                           inputs:inputs
                        superview:superview
                       hostConfig:config
                 accumulatedWidth:accumulatedWidth
                accumulatedHeight:accumulatedHeight
                         maxWidth:maxWidth
                        maxHeight:maxHeight];
    }

    float contentWidth = accumulatedWidth;

    if (ActionsOrientation::Horizontal == adaptiveActionConfig.actionsOrientation) {
        contentWidth += (renderedBtnNum - 1) * spacing;
    } else {
        contentWidth = maxWidth;
    }

    [containingView addSubview:childview];

    containingView.contentview = childview;
    containingView.contentWidth = contentWidth;

    containingView.stretch = adaptiveActionConfig.actionAlignment == ActionAlignment::Stretch;

    [containingView preconfigreAutolayout];

    // let layout subview to configure correct constraints when the frame size is available
    [NSLayoutConstraint activateConstraints:containingView.nonStretchConstraints];

    // this step ensures that action set view is added before subviews added by show cards
    [superview insertArrangedSubview:containingView atIndex:stackIndex];

    NSMutableArray *mutableArray = [NSMutableArray arrayWithArray:superview.accessibilityElements];
    NSUInteger indexOffset = 0;
    for (UIView *childElement in childview.arrangedSubviews) {

        [mutableArray insertObject:childElement atIndex:accessibilityIndex + indexOffset];
        indexOffset++;
    }

    superview.accessibilityElements = [mutableArray copy];

    return containingView;
}

- (void)renderButtonForElem:(ACOBaseActionElement *)acoElem
             actionRenderer:(ACRBaseActionElementRenderer *)actionRenderer
                  childview:(UIStackView *)childview
                 featureReg:(ACOFeatureRegistration *)featureReg
                   rootView:(ACRView *)rootView
                     inputs:(NSMutableArray *)inputs
                  superview:(UIView<ACRIContentHoldingView> *)superview
                 hostConfig:(ACOHostConfig *)config
           accumulatedWidth:(float &)accumulatedWidth
          accumulatedHeight:(float &)accumulatedHeight
                   maxWidth:(float &)maxWidth
                  maxHeight:(float &)maxHeight
{
    NSUInteger numElem = [[childview arrangedSubviews] count];

    UIButton *button = nil;

    @try {
        if ([acoElem meetsRequirements:featureReg] == NO) {
            @throw [ACOFallbackException fallbackException];
        }
        button = [actionRenderer renderButton:rootView
                                       inputs:inputs
                                    superview:superview
                            baseActionElement:acoElem
                                   hostConfig:config];

        configRtl(button, rootView.context);

        [childview addArrangedSubview:button];
    } @catch (ACOFallbackException *exception) {
        handleActionFallbackException(exception, superview, rootView, inputs, acoElem, config,
                                      childview);
        NSUInteger count = [childview.arrangedSubviews count];
        if (count > numElem) {
            UIView *view = [childview.arrangedSubviews lastObject];
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
@end
