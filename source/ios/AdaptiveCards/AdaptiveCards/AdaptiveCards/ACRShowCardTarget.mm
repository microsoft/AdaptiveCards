//
//  ACRShowCardTarget
//  ACRShowCardTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRShowCardTarget.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRRendererPrivate.h"
#import "ACRViewPrivate.h"
#import "BaseActionElement.h"
#import "UtiliOS.h"
#import <UIKit/UIKit.h>

@implementation ACRShowCardTarget {
    std::shared_ptr<AdaptiveCards::AdaptiveCard> _adaptiveCard;
    ACOHostConfig *_config;
    __weak UIView<ACRIContentHoldingView> *_superview;
    __weak ACRView *_rootView;
    __weak ACRColumnView *_adcView;
    __weak UIButton *_button;
    ACOBaseActionElement *_actionElement;
}

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ShowCardAction> const &)showCardActionElement
                               config:(ACOHostConfig *)config
                             rootView:(ACRView *)rootView
                               button:(UIButton *)button
{
    self = [super init];
    if (self) {
        _adaptiveCard = showCardActionElement->GetCard();
        _config = config;
        _superview = nil;
        _rootView = rootView;
        _adcView = nil;
        _button = button;
        std::shared_ptr<ShowCardAction> showCardAction = std::make_shared<ShowCardAction>();
        showCardAction->SetCard(showCardActionElement->GetCard());
        _actionElement = [[ACOBaseActionElement alloc] initWithBaseActionElement:std::dynamic_pointer_cast<BaseActionElement>(showCardAction)];
    }
    return self;
}

- (void)createShowCard:(NSMutableArray *)inputs superview:(UIView<ACRIContentHoldingView> *)superview
{
    // configure padding using LayoutGuid
    unsigned int padding = [_config getHostConfig]->GetActions().showCard.inlineTopMargin;

    NSDictionary<NSString *, NSNumber *> *attributes =
        @{@"padding-top" : [NSNumber numberWithFloat:padding]};

    ACRColumnView *adcView = [[ACRColumnView alloc] initWithFrame:_rootView.frame
                                                       attributes:attributes];

    ACRColumnView *parentRenderedCard = [_rootView peekCurrentShowCard];

    [_rootView pushCurrentShowcard:adcView];

    [_rootView setParent:parentRenderedCard child:adcView];

    [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                  inputs:adcView.inputHandlers
                                 context:_rootView
                          containingView:adcView
                              hostconfig:_config];
    [_rootView popCurrentShowcard];

    ContainerStyle containerStyle = ([_config getHostConfig]->GetAdaptiveCard().allowCustomStyle) ? _adaptiveCard->GetStyle() : [_config getHostConfig]->GetActions().showCard.style;

    ACRContainerStyle style = (ACRContainerStyle)(containerStyle);

    if (style == ACRNone) {
        style = [superview style];
    }

    _adcView = adcView;
    _adcView.translatesAutoresizingMaskIntoConstraints = NO;

    CGFloat showCardPadding = [_config getHostConfig]->GetSpacing().paddingSpacing;

    _adcView.backgroundColor = UIColor.clearColor;

    if (@available(iOS 11.0, *)) {
        _adcView.directionalLayoutMargins = NSDirectionalEdgeInsetsMake(showCardPadding, -showCardPadding, -showCardPadding, -showCardPadding);
    } else {
        _adcView.layoutMargins = UIEdgeInsetsMake(showCardPadding, -showCardPadding, -showCardPadding, -showCardPadding);
    }

    UIView *backgroundView = [[UIView alloc] init];
    [adcView addSubview:backgroundView];
    backgroundView.translatesAutoresizingMaskIntoConstraints = NO;
    backgroundView.backgroundColor = [_config getBackgroundColorForContainerStyle:style];
    [adcView sendSubviewToBack:backgroundView];
    [backgroundView.leadingAnchor constraintEqualToAnchor:adcView.layoutMarginsGuide.leadingAnchor].active = YES;
    [backgroundView.trailingAnchor constraintEqualToAnchor:adcView.layoutMarginsGuide.trailingAnchor].active = YES;
    [backgroundView.topAnchor constraintEqualToAnchor:adcView.layoutMarginsGuide.topAnchor].active = YES;
    [backgroundView.bottomAnchor constraintEqualToAnchor:adcView.layoutMarginsGuide.bottomAnchor].active = YES;
    _adcView.hidden = YES;

    [superview addArrangedSubview:adcView];
    _superview = superview;
}

- (IBAction)toggleVisibilityOfShowCard
{

    BOOL isSelected = _button.selected;
    BOOL hidden = _adcView.hidden;
    [_superview hideAllShowCards];
    _adcView.hidden = (hidden == YES) ? NO : YES;

    // send candidate background image view, if the sent view is UIImageView and has UIImage in it
    // AdatpiveCard will configure the backgroun
    if (hidden) {
        if ([_adcView.subviews count] > 1) {
            NSMutableArray<NSLayoutConstraint *> *constraints = [[NSMutableArray alloc] init];
            renderBackgroundCoverMode(_adcView.subviews[1], _adcView.backgroundView, constraints, _adcView);
            [NSLayoutConstraint activateConstraints:constraints];
        }
    }
    _button.selected = !isSelected;

    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didChangeVisibility:isVisible:)]) {
        [_rootView.acrActionDelegate didChangeVisibility:_button isVisible:(!_adcView.hidden)];
    }

    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)] && _adcView.hidden == NO) {
        CGRect showCardFrame = _adcView.frame;
        showCardFrame.origin = [_adcView convertPoint:_adcView.frame.origin toView:nil];
        CGRect oldFrame = showCardFrame;
        oldFrame.size.height = 0;
        showCardFrame.size.height += [_config getHostConfig]->GetActions().showCard.inlineTopMargin;
        [_rootView.acrActionDelegate didChangeViewLayout:oldFrame newFrame:showCardFrame];
    }
    [_rootView.acrActionDelegate didFetchUserResponses:[_rootView card] action:_actionElement];
}

- (void)doSelectAction
{
    [self toggleVisibilityOfShowCard];
}

- (void)hideShowCard
{
    _adcView.hidden = YES;
    _button.selected = NO;

    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didChangeVisibility:isVisible:)]) {
        [_rootView.acrActionDelegate didChangeVisibility:_button isVisible:(!_adcView.hidden)];
    }
}

@end
