//
//  ACRShowCardTarget
//  ACRShowCardTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SafariServices/SafariServices.h>
#import "ACRShowCardTarget.h"
#import "ACRRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRViewController.h"

@implementation ACRShowCardTarget
{
    std::shared_ptr<AdaptiveCards::AdaptiveCard> _adaptiveCard;
    std::shared_ptr<AdaptiveCards::HostConfig> _config;
    __weak UIView<ACRIContentHoldingView> *_superview;
    __weak UIViewController *_vc;
    __weak UIView *_adcView;
}

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard
                              config:(std::shared_ptr<AdaptiveCards::HostConfig> const&)config
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

- (IBAction)showCard:(UIButton *)sender
{
    if(YES == [sender isSelected])
    {
        _adcView.hidden = YES;
        sender.selected = NO;
    }
    else
    {
        if(_adcView)
        {
            _adcView.hidden = NO;
        }
        else
        {
            NSMutableArray *inputs = [[NSMutableArray alloc] init];
            UIView *adcView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                                            inputs:inputs
                                                    viewController:_vc
                                                        guideFrame:_superview.frame

                                                        hostconfig:_config];
            unsigned int padding = 0;

            switch (_config->actions.spacing)
            {
                case Spacing::ExtraLarge:
                    padding = _config->spacing.extraLargeSpacing;
                    break;
                case Spacing::Large:
                    padding = _config->spacing.largeSpacing;
                    break;
                case Spacing::Medium:
                    padding = _config->spacing.mediumSpacing;
                    break;
                case Spacing::Small:
                    padding = _config->spacing.smallSpacing;
                    break;
                case Spacing::Default:
                    padding =  _config->spacing.defaultSpacing;
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

            ContainerStyle style = (_config->adaptiveCard.allowCustomStyle)? _adaptiveCard->GetStyle() : _config->actions.showCard.style;

            long num = 0;

            if(style == ContainerStyle::None)
            {
                style = [_superview getStyle];
            }

            if(style == ContainerStyle::Emphasis)
            {
                num = std::stoul(_config->containerStyles.emphasisPalette.backgroundColor.substr(1), nullptr, 16);
            }
            else
            {
                num = std::stoul(_config->containerStyles.defaultPalette.backgroundColor.substr(1), nullptr, 16);
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
        sender.selected = YES;
    }
}
@end
