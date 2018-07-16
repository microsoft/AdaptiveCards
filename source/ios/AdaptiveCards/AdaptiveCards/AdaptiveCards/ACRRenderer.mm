//
//  ACRRenderer.mm
//  ACRRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRBaseActionElementRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRColumnView.h"
#import "ACRImageRenderer.h"
#import "ACRRegistration.h"
#import "ACRRendererPrivate.h"
#import "ACRSeparator.h"
#import "ACRViewPrivate.h"
#import "ACRViewController.h"
#import "ACRContentHoldingUIScrollView.h"

using namespace AdaptiveCards;

@implementation ACRRenderer

- (instancetype)init
{
    self = [super init];
    return self;
}

// This interface is exposed to outside, and returns ACRRenderResult object
// This object contains a viewController instance which defer rendering adaptiveCard until viewDidLoad is called.
+ (ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width
{
    ACRRenderResult *result = [[ACRRenderResult alloc] init];
    // Initializes ACRView instance with HostConfig and AdaptiveCard
    // ACRViewController does not render adaptiveCard until viewDidLoad calls render
    ACRView *view = [[ACRView alloc] init:card hostconfig:config widthConstraint:width];
    result.view = view;
    result.succeeded = YES;
    return result;
}

// This interface is exposed to outside, and returns ACRRenderResult object
// This object contains a viewController instance which defer rendering adaptiveCard until viewDidLoad is called.
+ (ACRRenderResult *)renderAsViewController:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config frame:(CGRect)frame delegate:(id<ACRActionDelegate>)acrActionDelegate
{
    ACRRenderResult *result = [[ACRRenderResult alloc] init];
    // Initializes ACRView instance with HostConfig and AdaptiveCard
    // ACRView does not render adaptiveCard until viewDidLoad calls render
    ACRViewController *viewcontroller = [[ACRViewController alloc] init:card hostconfig:config frame:frame delegate:acrActionDelegate];
    result.viewcontroller = viewcontroller;
    result.succeeded = YES;
    return result;
}

// transforms (i.e. renders) an adaptiveCard to a new UIView instance
+ (UIView *)renderWithAdaptiveCards:(std::shared_ptr<AdaptiveCard> const &)adaptiveCard
                             inputs:(NSMutableArray *)inputs
                            context:(ACRView *)rootView
                     containingView:(ACRColumnView *)containingView
                         hostconfig:(ACOHostConfig *)config
{
    std::vector<std::shared_ptr<BaseCardElement>> body = adaptiveCard->GetBody();
    ACRColumnView *verticalView = containingView;

    if(![[ACRRegistration getInstance] isElementRendererOverriden:[ACRImageRenderer elemType]]){
        [rootView loadImage:adaptiveCard->GetBackgroundImage()];
    }
    if(!body.empty()) {
        ACRContainerStyle style = ([config getHostConfig]->adaptiveCard.allowCustomStyle)? (ACRContainerStyle)adaptiveCard->GetStyle() : ACRDefault;
        style = (style == ACRNone)? ACRDefault : style;
        [verticalView setStyle:style];

        [rootView addTasksToConcurrentQueue:body];

        std::vector<std::shared_ptr<BaseActionElement>> actions = adaptiveCard->GetActions();

        if(!actions.empty()) {
            [rootView loadImagesForActionsAndCheckIfAllActionsHaveIconImages:actions hostconfig:config];
        }

        [rootView waitForAsyncTasksToFinish];

        [ACRRenderer render:verticalView rootView:rootView inputs:inputs withCardElems:body andHostConfig:config];

        [[rootView card] setInputs:inputs];

        if(!actions.empty()) {
            [ACRSeparator renderActionsSeparator:verticalView hostConfig:[config getHostConfig]];

            // renders buttons and their associated actions
            [ACRRenderer renderButton:rootView inputs:inputs superview:verticalView actionElems:actions hostConfig:config];
        }
        [verticalView adjustHuggingForLastElement];
    }

    return verticalView;
}

+ (UIView<ACRIContentHoldingView> *)renderButton:(ACRView *)rootView
                                          inputs:(NSMutableArray *)inputs
                                       superview:(UIView<ACRIContentHoldingView> *)superview
                                     actionElems:(std::vector<std::shared_ptr<BaseActionElement>> const &)elems
                                      hostConfig:(ACOHostConfig *)config
{
    ACRRegistration *reg = [ACRRegistration getInstance];
    UIView<ACRIContentHoldingView> *childview = nil;
    NSDictionary<NSString *, NSNumber*> *attributes =
        @{@"spacing":[NSNumber numberWithInt:[config getHostConfig]->actions.buttonSpacing],
          @"distribution":[NSNumber numberWithInt:UIStackViewDistributionFillProportionally] };

    if(ActionsOrientation::Horizontal == [config getHostConfig]->actions.actionsOrientation){
        childview = [[ACRColumnSetView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height) attributes:attributes];
    }
    else{
        childview = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height) attributes:attributes];
    }

    ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] init];
    ACRContentHoldingUIScrollView *containingView = [[ACRContentHoldingUIScrollView alloc] init];
    [superview addArrangedSubview:containingView];
    float accumulatedWidth = 0, accumulatedHeight = 0, spacing = [config getHostConfig]->actions.buttonSpacing, maxWidth = 0, maxHeight = 0;
    for(const auto &elem:elems){
        ACRBaseActionElementRenderer *actionRenderer =
        [reg getActionRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if(actionRenderer == nil){
            NSLog(@"Unsupported card action type:%d\n", (int) elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];
        UIButton *button = [actionRenderer renderButton:rootView inputs:inputs superview:superview baseActionElement:acoElem hostConfig:config];

        accumulatedWidth += [button intrinsicContentSize].width;
        accumulatedHeight += [button intrinsicContentSize].height;
        maxWidth = MAX(maxWidth, [button intrinsicContentSize].width);
        maxHeight = MAX(maxHeight, [button intrinsicContentSize].height);

        [childview addArrangedSubview:button];
    }

    float contentWidth = accumulatedWidth, contentHeight = accumulatedHeight;
    [childview adjustHuggingForLastElement];
    if(ActionsOrientation::Horizontal == [config getHostConfig]->actions.actionsOrientation){
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

    if(ActionsOrientation::Horizontal == [config getHostConfig]->actions.actionsOrientation){
        hConstraint.priority = UILayoutPriorityDefaultLow;
        if(contentWidth > superview.frame.size.width){
            containingView.showsHorizontalScrollIndicator = YES;
        } else
        {
            if([config getHostConfig]->actions.actionAlignment == ActionAlignment::Stretch){
                [NSLayoutConstraint constraintWithItem:containingView attribute:NSLayoutAttributeWidth
                                             relatedBy:NSLayoutRelationEqual toItem:childview
                                             attribute:NSLayoutAttributeWidth multiplier:1.0 constant:0].active = YES;
            }
        }
    } else {
        vConstraint.priority = UILayoutPriorityDefaultLow;
    }
    return childview;
}

+ (UIView *)render:(UIView<ACRIContentHoldingView> *)view
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
     withCardElems:(std::vector<std::shared_ptr<BaseCardElement>> const &)elems
     andHostConfig:(ACOHostConfig *)config
{
    ACRRegistration *reg = [ACRRegistration getInstance];
    ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] init];

    UIView *prevStretchableElem = nil, *curStretchableElem = nil;

    auto firstelem = elems.begin();
    for(const auto &elem:elems)
    {
        if(*firstelem != elem){
            [ACRSeparator renderSeparation:elem forSuperview:view withHostConfig:[config getHostConfig]];
        }

        ACRBaseCardElementRenderer *renderer =
            [reg getRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if(renderer == nil)
        {
            NSLog(@"Unsupported card element type:%d\n", (int) elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];

        curStretchableElem = [renderer render:view rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:config];

        if(elem->GetHeight() == HeightType::Stretch){
            if(prevStretchableElem){
                NSLayoutConstraint *heightConstraint = [NSLayoutConstraint constraintWithItem:curStretchableElem
                                             attribute:NSLayoutAttributeHeight
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:prevStretchableElem
                                             attribute:NSLayoutAttributeHeight
                                            multiplier:1
                                              constant:0];
                heightConstraint.priority = UILayoutPriorityDefaultLow;
                heightConstraint.active = YES;
            }

            if([view isKindOfClass:[ACRColumnView class]]){
                ACRColumnView *columnView = (ACRColumnView*)view;
                columnView.hasStretchableView = YES;
            }

            prevStretchableElem = curStretchableElem;
        }
    }

    return view;
}
@end
