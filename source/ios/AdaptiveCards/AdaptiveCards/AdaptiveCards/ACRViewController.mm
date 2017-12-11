//
//  ACRViewController.m
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ACOHostConfigPrivate.h"
#import "ACOAdaptiveCardPrivate.h"
#import "SharedAdaptiveCard.h"
#import "ACRRendererPrivate.h"
#import <AVFoundation/AVFoundation.h>

using namespace AdaptiveCards;

@implementation ACRViewController
{
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
    std::shared_ptr<HostConfig> _hostConfig;
    CGRect _guideFrame;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self){
        _guideFrame = CGRectMake(0, 0, 0, 0);
        _hostConfig = std::make_shared<HostConfig>();
    }
    return self;
}

- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
               frame:(CGRect)frame
{
    self = [self initWithNibName:nil bundle:nil];
    if(self)
    {
        _adaptiveCard = [card getCard];
        if(config)
        {
            _hostConfig = [config getHostConfig];
        }
        _guideFrame = frame;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self render];
}

- (void)render
{
    UIView *view = self.view;
    view.frame = _guideFrame;
    NSMutableArray *inputs = [[NSMutableArray alloc] init];

    std::string backgroundImage = _adaptiveCard->GetBackgroundImage();
    NSString* imgUrl = nil;
    if(!backgroundImage.empty())
        imgUrl = [[NSString alloc] initWithCString:backgroundImage.c_str() encoding:NSUTF8StringEncoding];
    if (imgUrl)
    {
        NSURL *url = [NSURL URLWithString:imgUrl];
        UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
        UIImageView *imgView = [[UIImageView alloc] initWithImage:img];
        [view addSubview:imgView];
        [view sendSubviewToBack:imgView];
        [NSLayoutConstraint activateConstraints:
         @[[imgView.trailingAnchor constraintEqualToAnchor:view.trailingAnchor],
           [imgView.topAnchor constraintEqualToAnchor:view.topAnchor],
           [imgView.trailingAnchor constraintEqualToAnchor:view.trailingAnchor],
           ]];
    }
    ContainerStyle style = (_hostConfig->adaptiveCard.allowCustomStyle)? _adaptiveCard->GetStyle() : _hostConfig->actions.showCard.style;
    if(style != ContainerStyle::None)
    {
        unsigned long num = 0;
        if(style == ContainerStyle::Emphasis)
        {
            num = std::stoul(_hostConfig->containerStyles.emphasisPalette.backgroundColor.substr(1), nullptr, 16);
        }
        else
        {
            num = std::stoul(_hostConfig->containerStyles.defaultPalette.backgroundColor.substr(1), nullptr, 16);
        }
        view.backgroundColor =
        [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                        green:((num & 0x0000FF00) >>  8) / 255.0
                         blue:((num & 0x000000FF)) / 255.0
                        alpha:((num & 0xFF000000) >> 24) / 255.0];
    }
    UIView *newView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                                             inputs:inputs
                                                     viewController:self
                                                         guideFrame:_guideFrame
                                                         hostconfig:_hostConfig];

    [view addSubview:newView];

    NSLayoutConstraint *constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeTop
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeTop
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeBottom
                                 relatedBy:NSLayoutRelationGreaterThanOrEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeBottom
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    [NSLayoutConstraint activateConstraints:
     @[[newView.leadingAnchor constraintEqualToAnchor:view.leadingAnchor],
       [newView.topAnchor constraintEqualToAnchor:view.topAnchor]]];
}

@end
