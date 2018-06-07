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
#import "ACRRegistration.h"
#import "ACRRendererPrivate.h"
#import "ACRSeparator.h"
#import "ACRViewPrivate.h"
#import "ACRViewController.h"

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
    
    if(!body.empty()) {
        [rootView addTasksToConcurrentQueue:body];
        // addTasksToConcurrentQueue spawns concurrent tasks, this flag indicates that
        // all tasks have been added to work queues, and is needed for complete notification to work properly
        rootView.seenAllElements = YES;

        ACRContainerStyle style = ([config getHostConfig]->adaptiveCard.allowCustomStyle)? (ACRContainerStyle)adaptiveCard->GetStyle() : ACRDefault;
        style = (style == ACRNone)? ACRDefault : style;
        [verticalView setStyle:style];

        [ACRRenderer render:verticalView rootView:rootView inputs:inputs withCardElems:body andHostConfig:config];

        [[rootView card] setInputs:inputs];

        std::vector<std::shared_ptr<BaseActionElement>> actions = adaptiveCard->GetActions();
        if(!actions.empty()) {
            [rootView addActionsToConcurrentQueue:actions];
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
    UILayoutConstraintAxis axis = UILayoutConstraintAxisVertical;
    if(ActionsOrientation::Horizontal == [config getHostConfig]->actions.actionsOrientation){
        childview = [[ACRColumnSetView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height)];
        axis = UILayoutConstraintAxisHorizontal;
    }
    else{
        childview = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, superview.frame.size.width, superview.frame.size.height)];
    }

    ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] init];
    [superview addArrangedSubview:childview];

    for(const auto &elem:elems){
        ACRBaseActionElementRenderer *actionRenderer =
        [reg getActionRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if(actionRenderer == nil){
            NSLog(@"Unsupported card action type:%d\n", (int) elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];
        UIButton *button = [actionRenderer renderButton:rootView inputs:inputs superview:superview baseActionElement:acoElem hostConfig:config];
        [childview addArrangedSubview:button];
        [ACRSeparator renderSeparationWithFrame:CGRectMake(0,0,[config getHostConfig]->actions.buttonSpacing, [config getHostConfig]->actions.buttonSpacing)
                                      superview:childview axis:axis];
    }

    [childview adjustHuggingForLastElement];
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

    for(const auto &elem:elems)
    {
        [ACRSeparator renderSeparation:elem forSuperview:view withHostConfig:[config getHostConfig]];

        ACRBaseCardElementRenderer *renderer =
            [reg getRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if(renderer == nil)
        {
            NSLog(@"Unsupported card element type:%d\n", (int) elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];
        [renderer render:view rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:config];
    }

    return view;
}
@end
