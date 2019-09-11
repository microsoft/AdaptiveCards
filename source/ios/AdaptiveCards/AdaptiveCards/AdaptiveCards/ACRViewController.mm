//
//  ACRViewController.m
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ACOAdaptiveCardPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRView.h"

using namespace AdaptiveCards;

@implementation ACRViewController {
    ACOAdaptiveCard *_adaptiveCard;
    ACOHostConfig *_hostConfig;
    CGRect _guideFrame;
    __weak id<ACRActionDelegate> _delegate;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (instancetype)init:(ACOAdaptiveCard *)card hostconfig:(ACOHostConfig *)config frame:(CGRect)frame delegate:(id<ACRActionDelegate>)acrActionDelegate
{
    self = [self initWithNibName:nil bundle:nil];
    if (self) {
        _guideFrame = frame;
        _adaptiveCard = card;
        if (config) {
            _hostConfig = config;
        } else {
            std::shared_ptr<HostConfig> cHostConfig = std::make_shared<HostConfig>();
            _hostConfig = [[ACOHostConfig alloc] initWithConfig:cHostConfig];
        }
        _delegate = acrActionDelegate;
    }
    return self;
}
- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view = [[ACRView alloc] init:_adaptiveCard hostconfig:_hostConfig widthConstraint:_guideFrame.size.width];
    ((ACRView *)self.view).acrActionDelegate = _delegate;
}

@end
