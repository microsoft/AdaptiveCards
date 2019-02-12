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
#import "ACRLongPressGestureRecognizerFactory.h"
#import "ACRUIImageView.h"

using namespace AdaptiveCards;

@implementation ACRRenderer

- (instancetype)init
{
    self = [super init];
    return self;
}

// This interface is exposed to outside, and returns ACRRenderResult object
// This object contains a viewController instance which defer rendering adaptiveCard until viewDidLoad is called.
+ (ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width delegate:(id<ACRActionDelegate>)acrActionDelegate
{
    ACRRenderResult *result = [[ACRRenderResult alloc] init];
    // Initializes ACRView instance with HostConfig and AdaptiveCard
    // ACRViewController does not render adaptiveCard until viewDidLoad calls render
    ACRView *view = [[ACRView alloc] init:card hostconfig:config widthConstraint:width delegate:acrActionDelegate];
    result.view = view;
    result.succeeded = YES;
    return result;
}

// This interface is exposed to outside, and returns ACRRenderResult object
// This object contains a viewController instance which defer rendering adaptiveCard until viewDidLoad is called.
+ (ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width
{
    return [ACRRenderer render:card config:config widthConstraint:width delegate:nil];
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

    std::shared_ptr<BaseActionElement> selectAction = adaptiveCard->GetSelectAction();
    if(selectAction) {
        // instantiate and add tap gesture recognizer
        [ACRLongPressGestureRecognizerFactory addLongPressGestureRecognizerToUIView:verticalView
                                                                           rootView:rootView
                                                                      recipientView:verticalView
                                                                      actionElement:selectAction
                                                                         hostConfig:config];
    }

    auto backgroundImageProperties = adaptiveCard->GetBackgroundImage();
    if((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
        ObserverActionBlock observerAction =
        ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView* rootView) {
            UIImageView *view = [imageResourceResolver resolveBackgroundImageViewResource:url hasStretch:(backgroundImageProperties->GetMode() == BackgroundImageMode::Stretch)];
            [rootView setImageView:key view:view];
            if(view) {
                [view addObserver:rootView forKeyPath:@"image"
                          options:NSKeyValueObservingOptionNew
                          context:nil];
            }
        };
        [rootView
            loadBackgroundImageAccordingToResourceResolverIF:adaptiveCard->GetBackgroundImage()
            key:nil observerAction:observerAction];
    }

    if(![config getHostConfig]->GetMedia().playButton.empty()) {
        ObserverActionBlock observerAction =
        ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView* rootView) {
            UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
            [rootView setImageView:key view:view];
            if(view) {
                [view addObserver:rootView forKeyPath:@"image"
                          options:NSKeyValueObservingOptionNew
                          context:nil];
            }
        };
        [rootView
            loadImageAccordingToResourceResolverIFFromString:[config getHostConfig]->GetMedia().playButton
            key:@"playIconImage" observerAction:observerAction];
    }

    ACRContainerStyle style = ([config getHostConfig]->GetAdaptiveCard().allowCustomStyle)? (ACRContainerStyle)adaptiveCard->GetStyle() : ACRDefault;
    style = (style == ACRNone)? ACRDefault : style;
    [verticalView setStyle:style];

    [rootView addTasksToConcurrentQueue:body];

    std::vector<std::shared_ptr<BaseActionElement>> actions = adaptiveCard->GetActions();

    if(!actions.empty()) {
        [rootView loadImagesForActionsAndCheckIfAllActionsHaveIconImages:actions hostconfig:config];
    }

    [rootView waitForAsyncTasksToFinish];

    UIView *leadingBlankSpace = nil, *trailingBlankSpace = nil;
    if(adaptiveCard->GetVerticalContentAlignment() == VerticalContentAlignment::Center ||
       adaptiveCard->GetVerticalContentAlignment() == VerticalContentAlignment::Bottom){
        leadingBlankSpace = [verticalView addPaddingSpace];
    }

    [ACRRenderer render:verticalView rootView:rootView inputs:inputs withCardElems:body andHostConfig:config];

    // Dont add the trailing space if the vertical content alignment is top/default
    if((adaptiveCard->GetVerticalContentAlignment() == VerticalContentAlignment::Center) ||
       (adaptiveCard->GetVerticalContentAlignment() == VerticalContentAlignment::Top &&
        !(verticalView.hasStretchableView))){
        trailingBlankSpace = [verticalView addPaddingSpace];
    }

    [[rootView card] setInputs:inputs];

    if(!actions.empty()) {
        [ACRSeparator renderActionsSeparator:verticalView hostConfig:[config getHostConfig]];

        // renders buttons and their associated actions
        ACOAdaptiveCard *card = [[ACOAdaptiveCard alloc] init];
        [card setCard:adaptiveCard];
        [ACRRenderer renderActions:rootView inputs:inputs superview:verticalView card:card hostConfig:config];
    }
    [verticalView adjustHuggingForLastElement];

    return verticalView;
}

+ (UIView *)renderActions:(ACRView *)rootView
                  inputs:(NSMutableArray *)inputs
               superview:(UIView<ACRIContentHoldingView> *)superview
                    card:(ACOAdaptiveCard *)card
               hostConfig:(ACOHostConfig *)config
{
    ACRRegistration *reg = [ACRRegistration getInstance];
    return [[reg getActionSetRenderer] renderButtons:rootView inputs:inputs superview:superview card:card hostConfig:config];
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
