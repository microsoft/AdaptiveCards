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

@implementation ACRButtonTarget
{
    __weak UIViewController *_vc;
    NSURL *_url;
    std::shared_ptr<AdaptiveCards::AdaptiveCard> _adaptiveCard;
    std::shared_ptr<AdaptiveCards::HostConfig> _config; 
    UIView<ACRIContentHoldingView> *_superview;
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

- (IBAction)showCard
{
    UIView* adcView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                            viewController:_vc
                                                guideFrame:_superview.frame
                                                hostconfig:_config];
    [_superview addArrangedSubview:adcView];
}
@end
