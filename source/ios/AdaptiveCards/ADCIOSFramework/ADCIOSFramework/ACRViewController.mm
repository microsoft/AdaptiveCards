//
//  ACRViewController.m
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ACRHostConfig.h"
#import "SharedAdaptiveCard.h"
#import "ACRRegistration.h"
#import <AVFoundation/AVFoundation.h>

using namespace AdaptiveCards;

@implementation ACRViewController
{
    std::shared_ptr<AdaptiveCard> adaptiveCard;
    std::shared_ptr<HostConfig> config;
}

-(instancetype) initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self){
        self.jsonString = nil;
        config = std::make_shared<HostConfig>();
    }
    return self;
}

-(instancetype) init: (NSString*) str {
    self = [self initWithNibName:nil bundle:nil];
    if(self) {
        self.jsonString = str;
    }
    
    return self;
}

-(void) viewDidLoad {
    [super viewDidLoad];
    [self buildViewFromADC: self.jsonString];
}

-(void) buildViewFromADC:(NSString*) str
{
    adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([str UTF8String]));

    std::vector<std::shared_ptr<BaseCardElement>> body = adaptiveCard->GetBody();
    
    UIView* childView = nil;
    
    if(!body.empty())
    { 
        ACRRegistration* reg = [ACRRegistration getInstance];
        childView = [reg render:self.view withCardElems:body andHostConfig:config];
        
        [NSLayoutConstraint activateConstraints:
         @[[childView.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],
           [childView.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
    }
}

@end
