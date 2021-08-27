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
#import "ACRBaseActionElementRenderer.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRColumnView.h"
#import "ACRContentHoldingUIScrollView.h"
#import "ACRImageRenderer.h"
#import "ACRRegistration.h"
#import "ACRRendererPrivate.h"
#import "ACRSeparator.h"
#import "ACRUIImageView.h"
#import "ACRViewController.h"
#import "ACRViewPrivate.h"
#import "UtiliOS.h"

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
    result.warnings = view.warnings;
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
    result.warnings = ((ACRView *)viewcontroller.view).warnings;
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

    std::vector<std::shared_ptr<BaseActionElement>> actions = adaptiveCard->GetActions();

    if (!actions.empty()) {
        [rootView loadImagesForActionsAndCheckIfAllActionsHaveIconImages:actions hostconfig:config hash:iOSInternalIdHash(adaptiveCard->GetInternalId().Hash())];
    }

    // set context
    ACOAdaptiveCard *wrapperCard = [[ACOAdaptiveCard alloc] init];
    [wrapperCard setCard:adaptiveCard];

    [rootView.context pushCardContext:wrapperCard];

    verticalView.rtl = rootView.context.rtl;

    std::shared_ptr<BaseActionElement> selectAction = adaptiveCard->GetSelectAction();
    if (selectAction) {
        ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:selectAction];
        [verticalView configureForSelectAction:acoSelectAction rootView:rootView];
    }

    if (adaptiveCard->GetMinHeight() > 0) {
        NSLayoutConstraint *constraint =
            [NSLayoutConstraint constraintWithItem:rootView
                                         attribute:NSLayoutAttributeHeight
                                         relatedBy:NSLayoutRelationGreaterThanOrEqual
                                            toItem:nil
                                         attribute:NSLayoutAttributeNotAnAttribute
                                        multiplier:1
                                          constant:adaptiveCard->GetMinHeight()];
        constraint.priority = 999;
        constraint.active = YES;
    }

    auto backgroundImageProperties = adaptiveCard->GetBackgroundImage();
    if ((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
        ObserverActionBlock observerAction =
            ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseCardElement> const &elem, NSURL *url, ACRView *rootView) {
                UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                if (view) {
                    [view addObserver:rootView
                           forKeyPath:@"image"
                              options:NSKeyValueObservingOptionNew
                              context:backgroundImageProperties.get()];

                    // store the image view and card for easy retrieval in ACRView::observeValueForKeyPath
                    [rootView setImageView:key view:view];
                }
            };
        [rootView loadBackgroundImageAccordingToResourceResolverIF:backgroundImageProperties key:@"backgroundImage" observerAction:observerAction];
    }

    ACRContainerStyle style = ([config getHostConfig]->GetAdaptiveCard().allowCustomStyle) ? (ACRContainerStyle)adaptiveCard->GetStyle() : ACRDefault;
    style = (style == ACRNone) ? ACRDefault : style;
    [verticalView setStyle:style];

    [rootView addBaseCardElementListToConcurrentQueue:body registration:[ACRRegistration getInstance]];

    UIView *leadingBlankSpace = nil;
    if (adaptiveCard->GetVerticalContentAlignment() == VerticalContentAlignment::Center ||
        adaptiveCard->GetVerticalContentAlignment() == VerticalContentAlignment::Bottom) {
        leadingBlankSpace = [verticalView addPaddingSpace];
    }

    [ACRRenderer render:verticalView rootView:rootView inputs:inputs withCardElems:body andHostConfig:config];

    [[rootView card] setInputs:inputs];

    if (!actions.empty()) {
        [ACRSeparator renderActionsSeparator:verticalView hostConfig:[config getHostConfig]];

        // renders buttons and their associated actions
        ACOAdaptiveCard *card = [[ACOAdaptiveCard alloc] init];
        [card setCard:adaptiveCard];
        [ACRRenderer renderActions:rootView inputs:inputs superview:verticalView card:card hostConfig:config];
    }

    // renders background image for AdaptiveCard and an inner AdaptiveCard in a ShowCard
    renderBackgroundImage(backgroundImageProperties, verticalView, rootView);

    [rootView.context popCardContext:wrapperCard];

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
    ACOFeatureRegistration *featureReg = [ACOFeatureRegistration getInstance];

    UIView *prevStretchableElem = nil, *curStretchableElem = nil;

    auto firstelem = elems.begin();

    for (const auto &elem : elems) {
        ACRSeparator *separator = nil;
        if (*firstelem != elem && curStretchableElem) {
            separator = [ACRSeparator renderSeparation:elem
                                          forSuperview:view
                                        withHostConfig:[config getHostConfig]];
            configSeparatorVisibility(separator, elem);
        }

        ACRBaseCardElementRenderer *renderer =
            [reg getRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if (renderer == nil) {
            NSLog(@"Unsupported card element type:%d\n", (int)elem->GetElementType());
            continue;
        }

        [acoElem setElem:elem];

        @try {
            if ([acoElem meetsRequirements:featureReg] == NO) {
                @throw [ACOFallbackException fallbackException];
            }

            curStretchableElem = [renderer render:view rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:config];

            if (separator && !curStretchableElem) {
                [(ACRContentStackView *)view removeViewFromContentStackView:separator];
            }

            if (elem->GetHeight() == HeightType::Stretch && curStretchableElem) {
                // vertical stretch works in the following way:
                // an ui element that will be stretched will be contained in a new superview.
                // additional trailing view is added to the superview at the bottom
                // uistackview for ColumnSet will have distribution set to fill
                // this ensures all columns will have same height, thus making the space available for
                // stretch.
                // when a smaller column is expanded, the trailing views in its subviews will fill up the
                // space, by setting the heights of the superviews of the trailing views same as below,
                // filler space occupies the same space.
                if (prevStretchableElem) {
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

                if ([view isKindOfClass:[ACRColumnView class]]) {
                    ACRColumnView *columnView = (ACRColumnView *)view;
                    columnView.hasStretchableView = YES;
                }

                prevStretchableElem = curStretchableElem;
            }
        } @catch (ACOFallbackException *e) {
            handleFallbackException(e, view, rootView, inputs, elem, config);
        }
    }

    [view toggleVisibilityOfFirstView];

    return view;
}
@end
