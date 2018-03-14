//
//  ACRShowCardTarget
//  ACRShowCardTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SafariServices/SafariServices.h>
#import "ACRShowCardTarget.h"
#import "ACRRendererPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRViewController.h"

@implementation ACRShowCardTarget
{
    std::shared_ptr<AdaptiveCards::AdaptiveCard> _adaptiveCard;
    ACOHostConfig *_config;
    __weak UIView<ACRIContentHoldingView> *_superview;
    __weak UIViewController *_vc;
    __weak UIView *_adcView;
}

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard
                              config:(ACOHostConfig *)config
                           superview:(UIView<ACRIContentHoldingView> *)superview
                                  vc:(UIViewController *)vc
{
    self = [super init];
    if(self)
    {
        _adaptiveCard = adaptiveCard;
        _config = config;
        _superview = superview;
        _vc = vc;
        _adcView = nil;
    }
    return self;
}

- (void)createShowCard
{
    NSMutableArray *inputs = [[NSMutableArray alloc] init];
    UIView *adcView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                                    inputs:inputs
                                            viewController:_vc
                                                guideFrame:_superview.frame
                                                hostconfig:_config];

    [[(ACRViewController *)_vc card] appendInputs:inputs];

    unsigned int padding = 0;

    switch ([_config getHostConfig] ->actions.spacing)
    {
        case Spacing::ExtraLarge:
            padding = [_config getHostConfig]->spacing.extraLargeSpacing;
            break;
        case Spacing::Large:
            padding = [_config getHostConfig]->spacing.largeSpacing;
            break;
        case Spacing::Medium:
            padding = [_config getHostConfig]->spacing.mediumSpacing;
            break;
        case Spacing::Small:
            padding = [_config getHostConfig]->spacing.smallSpacing;
            break;
        case Spacing::Default:
            padding =  [_config getHostConfig]->spacing.defaultSpacing;
            break;
        default:
            break;
    }
    ACRContentHoldingUIView *wrappingView = [[ACRContentHoldingUIView alloc]
                                             initWithFrame:CGRectMake(0,0,
                                                                      adcView.frame.size.width +
                                                                      padding +
                                                                      padding,
                                                                      adcView.frame.size.height +
                                                                      padding +
                                                                      padding)];
    [wrappingView addSubview:adcView];
    NSString *horString = [[NSString alloc] initWithFormat:@"H:|-%u-[adcView]-%u-|",
                           padding,
                           padding];
    NSString *verString = [[NSString alloc] initWithFormat:@"V:|-%u-[adcView]-%u-|",
                           padding,
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
    [wrappingView setAlignmentForSubview:AdaptiveCards::HorizontalAlignment::Center];
    [_superview addArrangedSubview:_adcView];
}

- (IBAction)toggleVisibilityOfShowCard
{
    // if there is no ShowCard UIView, create one
    if(!_adcView)
    {
        [self createShowCard];
        return;
    }
    // Toggle the visibility of a ShowCard UIView
    _adcView.hidden = (_adcView.hidden == YES)? NO: YES;
}

- (void)doSelectAction
{
    [self toggleVisibilityOfShowCard];
}

@end
