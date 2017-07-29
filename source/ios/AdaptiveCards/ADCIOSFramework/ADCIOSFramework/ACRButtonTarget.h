//
//  ACRButtonTarget
//  ACRButtonTarget.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIContentHoldingView.h"
#import "SharedAdaptiveCard.h"
#import "HostConfig.h"

@interface ACRButtonTarget:NSObject

- (instancetype)initWithURL:(NSURL *)url viewController:(UIViewController *) vc;

- (IBAction)openURL;

- (instancetype)initWithAdaptiveCard:(std::shared_ptr<AdaptiveCards::AdaptiveCard> const &)adaptiveCard 
                              config:(std::shared_ptr<AdaptiveCards::HostConfig> const&)config
                           superview:(UIView<ACRIContentHoldingView> *)superview;
- (IBAction)showCard;
@end
