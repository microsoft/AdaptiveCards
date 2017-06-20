//
//  ACRViewController.m
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ACRHostConfig.h"
#import "AdaptiveCard.h"
#import "TextBlock.h"
#import "Image.h"
#import "ACRImageRenderer.h"
#import "ACRTextBlockRenderer.h"
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

-(void) buildViewFromADC:(NSString*) str{
    adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([str UTF8String]));

    UIStackView* mainView = [[UIStackView alloc] init];
    mainView.axis = UILayoutConstraintAxisVertical;
    mainView.distribution = UIStackViewDistributionEqualSpacing;
    mainView.translatesAutoresizingMaskIntoConstraints = false;
    
    std::vector<std::shared_ptr<BaseCardElement>> body = adaptiveCard->GetBody();
    
    // work in progress; simplified version to verify TextBlock and Image
    // to-do add support for container / column set / columns 
    for(auto elem: body)
    {
        switch(elem->GetElementType()){
            case CardElementType::TextBlock:
            {
                ACRTextBlockRenderer* textRenderer = [ACRTextBlockRenderer getInstance];
                [mainView addArrangedSubview:[textRenderer render:nil withCardElem:elem andHostCofig:config]];
                break;
            }
            case CardElementType::Image:
            {
                ACRImageRenderer* imageRenderer = [ACRImageRenderer getInstance];
                [mainView addArrangedSubview:[imageRenderer render:nil withCardElem:elem andHostCofig:config]];
                break;
            }
            default:;
        }
    }

    [self.view addSubview: mainView];

    [NSLayoutConstraint activateConstraints:@[[mainView.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], 
                                              [mainView.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
}

@end
