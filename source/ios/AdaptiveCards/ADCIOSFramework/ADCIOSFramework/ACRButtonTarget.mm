//
//  ACRButtonTarget
//  ACRButtonTarget.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SafariServices/SafariServices.h>
#import "ACRButtonTarget.h"
#import "ACRRenderer.h"
#import "ACRContentHoldingUIView.h"

@implementation ACRButtonTarget
{
    __weak UIViewController *_vc;
    NSURL *_url;
    std::shared_ptr<AdaptiveCards::AdaptiveCard> _adaptiveCard;
    std::shared_ptr<AdaptiveCards::HostConfig> _config; 
    __weak UIView<ACRIContentHoldingView> *_superview;
    UIView* _adcView;
}

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard 
                              config:(std::shared_ptr<AdaptiveCards::HostConfig> const&)config
                           superview:(UIView<ACRIContentHoldingView> *)superview
{
    self = [super init];
    if(self)
    {
        _adaptiveCard = adaptiveCard;
        _config = config;
        _superview = superview;
        _adcView = nil;
    }
    return self;
}

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *)vc
{
    self = [super init];
    if(self)
    {
        _vc = vc;
        _url = url;
    }
    return self;
}

- (IBAction)openURL
{ 
    SFSafariViewController* svc = [[SFSafariViewController alloc] initWithURL:_url];
    [_vc presentViewController:svc animated:YES completion:nil];
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
            NSMutableArray* inputs = [[NSMutableArray alloc] init];
            UIView* adcView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                                            inputs:inputs
                                                    viewController:_vc
                                                        guideFrame:_superview.frame
            
                                                        hostconfig:_config];
            ACRContentHoldingUIView* wrappingView = [[ACRContentHoldingUIView alloc]
                                                     initWithFrame:CGRectMake(0,0,
                                                                              adcView.frame.size.width +
                                                                              _config->actions.showCard.padding.left +
                                                                              _config->actions.showCard.padding.right,
                                                                              adcView.frame.size.height +
                                                                              _config->actions.showCard.padding.top +
                                                                              _config->actions.showCard.padding.bottom)];
            [wrappingView addSubview:adcView];
            NSString *horString = [[NSString alloc] initWithFormat:@"H:|-%u-[adcView]-%u-|",
                                   _config->actions.showCard.padding.left,
                                   _config->actions.showCard.padding.right];
            NSString *verString = [[NSString alloc] initWithFormat:@"V:|-%u-[adcView]-%u-|",
                                   _config->actions.showCard.padding.top,
                                   _config->actions.showCard.padding.bottom];
            NSDictionary* dictionary = NSDictionaryOfVariableBindings(wrappingView, adcView);
            NSArray* horzConst = [NSLayoutConstraint constraintsWithVisualFormat:horString
                                                                         options:0
                                                                         metrics:nil
                                                                           views:dictionary];
            NSArray* vertConst = [NSLayoutConstraint constraintsWithVisualFormat:verString
                                                                         options:0
                                                                         metrics:nil
                                                                           views:dictionary];
            [wrappingView addConstraints:horzConst];
            [wrappingView addConstraints:vertConst];
            _adcView = wrappingView;
            
            long num = std::stoul(_config->actions.showCard.backgroundColor.substr(1), nullptr, 16);
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
