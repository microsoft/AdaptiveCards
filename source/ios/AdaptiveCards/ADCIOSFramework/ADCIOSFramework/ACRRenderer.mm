//
//  ACRRenderer
//  ACRRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRRenderer.h"
#import "ACRRegistration.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRIContentHoldingView.h"
#import "ACRColumnView.h"


using namespace AdaptiveCards;

@implementation ACRRenderer

+ (UIView *)renderWithAdaptiveCards:(std::shared_ptr<AdaptiveCard> const &)adaptiveCard
                     viewController:(UIViewController *)vc
                         guideFrame:(CGRect)guideFrame
                         hostconfig:(std::shared_ptr<HostConfig> const &)config
{
    std::vector<std::shared_ptr<BaseCardElement>> body = adaptiveCard->GetBody();
    
    ACRColumnView *verticalView = nil;
    
    if(!body.empty())
    {
         verticalView = [[ACRColumnView alloc] initWithFrame:CGRectMake(0, 0, guideFrame.size.width, guideFrame.size.height)];

        ACRRegistration *reg = [ACRRegistration getInstance];
        [reg render:verticalView withCardElems:body andHostConfig:config];

        std::vector<std::shared_ptr<BaseActionElement>> actions = adaptiveCard->GetActions();
        UIView<ACRIContentHoldingView> *actionChildView = [reg renderButton:vc superview:verticalView actionElems:actions hostConfig:config];
        [verticalView addArrangedSubview:actionChildView];
    }
    return verticalView;
}

+ (UIView *)renderWithJson:(NSString *)str
            viewController:(UIViewController *)vc
                guideFrame:(CGRect)guideFrame
                hostconfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<AdaptiveCard> adaptiveCard = AdaptiveCard::DeserializeFromString(std::string([str UTF8String]));
    return [ACRRenderer renderWithAdaptiveCards:adaptiveCard
                                 viewController:vc
                                     guideFrame:guideFrame
                                     hostconfig:config];
}
@end
