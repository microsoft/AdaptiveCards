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
    __weak UIView *_adcView;
    ACOBaseActionElement *_actionElement;
}

- (instancetype)initWithActionElement:(std::shared_ptr<AdaptiveCards::ShowCardAction> const &)showCardActionElement
                              config:(ACOHostConfig *)config
                           superview:(UIView<ACRIContentHoldingView> *)superview
                            rootView:(ACRView *)rootView
{
    self = [super init];
    if(self)
    {
        _adaptiveCard = showCardActionElement->GetCard();
        _config = config;
        _superview = superview;
        _rootView = rootView;
        _adcView = nil;
        std::shared_ptr<ShowCardAction> showCardAction = std::make_shared<ShowCardAction>();
        showCardAction->SetCard(showCardActionElement->GetCard());
        _actionElement = [[ACOBaseActionElement alloc]initWithBaseActionElement:std::dynamic_pointer_cast<BaseActionElement>(showCardAction)];
    }
    return self;
}

- (void)createShowCard:(NSMutableArray*)inputs
{
    [inputs setArray:[NSMutableArray arrayWithArray:[[_rootView card] getInputs]]];
    if(!inputs){
        inputs = [[NSMutableArray alloc] init];
    }
    ACRColumnView *containingView = [[ACRColumnView alloc] initWithFrame:_rootView.frame];
    UIView *adcView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                                    inputs:inputs
                                                  context:_rootView
                                           containingView:containingView
                                                hostconfig:_config];
    [[_rootView card] setInputs:inputs];
    unsigned int padding = [_config getHostConfig] ->actions.showCard.inlineTopMargin;

        ACRContentHoldingUIView *wrappingView = [[ACRContentHoldingUIView alloc] init];
    [wrappingView addSubview:adcView];

    NSString *horString = [[NSString alloc] initWithFormat:@"H:|-0-[adcView]-0-|"];
    NSString *verString = [[NSString alloc] initWithFormat:@"V:|-%u-[adcView]-0-|",
                           padding];
    NSDictionary *dictionary = NSDictionaryOfVariableBindings(wrappingView, adcView);
    NSArray *horzConst = [NSLayoutConstraint constraintsWithVisualFormat:horString
                                                                 options:0
                                                                 metrics:nil
                                                                   views:dictionary];
    NSArray *vertConst = [NSLayoutConstraint constraintsWithVisualFormat:verString
                                                                 options:0
                                                                 metrics:nil
                                                                   views:dictionary];
    [wrappingView addConstraints:horzConst];
    [wrappingView addConstraints:vertConst];
    _adcView = wrappingView;

    ContainerStyle containerStyle = ([_config getHostConfig]->adaptiveCard.allowCustomStyle)? _adaptiveCard->GetStyle() : [_config getHostConfig]->actions.showCard.style;

    ACRContainerStyle style = (ACRContainerStyle)(containerStyle);

    long num = 0;

    if(style == ACRNone) {
        style = [_superview style];
    }

    if(style == ACREmphasis) {
        num = std::stoul([_config getHostConfig]->containerStyles.emphasisPalette.backgroundColor.substr(1), nullptr, 16);
    } else {
        num = std::stoul([_config getHostConfig]->containerStyles.defaultPalette.backgroundColor.substr(1), nullptr, 16);
    }

    wrappingView.translatesAutoresizingMaskIntoConstraints = NO;
    wrappingView.backgroundColor =
    [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                    green:((num & 0x0000FF00) >>  8) / 255.0
                     blue:((num & 0x000000FF)) / 255.0
                    alpha:((num & 0xFF000000) >> 24) / 255.0];

    [_superview addArrangedSubview:_adcView];
    _adcView.hidden = YES;
}

- (IBAction)toggleVisibilityOfShowCard
{
    BOOL hidden = _adcView.hidden;
    [_superview hideAllShowCards];
    _adcView.hidden = (hidden == YES)? NO: YES;
    [_rootView.acrActionDelegate didFetchUserResponses:[_rootView card] action:_actionElement];
}

- (void)doSelectAction
{
    [self toggleVisibilityOfShowCard];
}

- (void)hideShowCard
{
    _adcView.hidden = YES;
}

@end
