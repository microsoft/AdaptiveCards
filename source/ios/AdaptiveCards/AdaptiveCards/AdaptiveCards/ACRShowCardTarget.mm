//
//  ACRShowCardTarget
//  ACRShowCardTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRShowCardTarget.h"
#import "ACRRendererPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRView.h"
#import "BaseActionElement.h"

@implementation ACRShowCardTarget
{
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
                           superview:(UIView<ACRIContentHoldingView> *)superview
                            rootView:(ACRView *)rootView
                               button:(UIButton *)button
{
    self = [super init];
    if(self)
    {
        _adaptiveCard = showCardActionElement->GetCard();
        _config = config;
        _superview = superview;
        _rootView = rootView;
        _adcView = nil;
        _button = button;
        std::shared_ptr<ShowCardAction> showCardAction = std::make_shared<ShowCardAction>();
        showCardAction->SetCard(showCardActionElement->GetCard());
        _actionElement = [[ACOBaseActionElement alloc]initWithBaseActionElement:std::dynamic_pointer_cast<BaseActionElement>(showCardAction)];
    }
    return self;
}

- (void)createShowCard:(NSMutableArray*)inputs
{
    [inputs setArray:[NSMutableArray arrayWithArray:[[_rootView card] getInputs]]];

    if (!inputs) {
        inputs = [[NSMutableArray alloc] init];
    }

    // configure padding using LayoutGuid
    unsigned int padding = [_config getHostConfig] ->GetActions().showCard.inlineTopMargin;

    NSDictionary<NSString *, NSNumber *> *attributes =
        @{ @"padding-top":[NSNumber numberWithFloat:padding] };

    ACRColumnView *adcView = [[ACRColumnView alloc] initWithFrame:_rootView.frame
        attributes:attributes];

    [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                  inputs:inputs
                                 context:_rootView
                          containingView:adcView
                              hostconfig:_config];

    [[_rootView card] setInputs:inputs];

    ContainerStyle containerStyle = ([_config getHostConfig]->GetAdaptiveCard().allowCustomStyle)? _adaptiveCard->GetStyle() : [_config getHostConfig]->GetActions().showCard.style;

    ACRContainerStyle style = (ACRContainerStyle)(containerStyle);

    if (style == ACRNone) {
        style = [_superview style];
    }

    _adcView = adcView;
    _adcView.translatesAutoresizingMaskIntoConstraints = NO;
    _adcView.backgroundColor = [_config getBackgroundColorForContainerStyle:style];

    [_superview addArrangedSubview:adcView];

    for (NSLayoutConstraint *constraint in adcView.widthconstraint) {
        constraint.active = NO;
    }

    for (NSLayoutConstraint *constraint in adcView.heightconstraint) {
        constraint.active = NO;
    }

    _adcView.hidden = YES;
}

- (IBAction)toggleVisibilityOfShowCard
{
    BOOL hidden = _adcView.hidden;
    [_superview hideAllShowCards];
    _adcView.hidden = (hidden == YES) ? NO : YES;

    for (NSLayoutConstraint *constraint in _adcView.widthconstraint) {
        constraint.active = hidden;
    }

    for (NSLayoutConstraint *constraint in _adcView.heightconstraint) {
        constraint.active = hidden;
    }

    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didChangeVisibility: isVisible:)])
    {
        [_rootView.acrActionDelegate didChangeVisibility:_button isVisible:(!_adcView.hidden)];
    }

    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)] && _adcView.hidden == NO){
        CGRect showCardFrame = _adcView.frame;
        showCardFrame.origin = [_adcView convertPoint:_adcView.frame.origin toView:nil];
        CGRect oldFrame = showCardFrame;
        oldFrame.size.height = 0;
        showCardFrame.size.height += [_config getHostConfig]->GetActions().showCard.inlineTopMargin;;
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

    for (NSLayoutConstraint *constraint in _adcView.widthconstraint) {
        constraint.active = NO;
    }

    for (NSLayoutConstraint *constraint in _adcView.heightconstraint) {
        constraint.active = NO;
    }

    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didChangeVisibility: isVisible:)])
    {
        [_rootView.acrActionDelegate didChangeVisibility:_button isVisible:(!_adcView.hidden)];
    }
}

@end
