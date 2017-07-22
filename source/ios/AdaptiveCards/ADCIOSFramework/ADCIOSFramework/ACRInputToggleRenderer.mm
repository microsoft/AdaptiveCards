//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputToggleRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRSeparator.h"
#import "ToggleInput.h"
#import "ACRColumnSetView.h"

@implementation ACRInputToggleRenderer

+ (ACRInputToggleRenderer* ) getInstance
{
    static ACRInputToggleRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType) elemType
{
    return CardElementType::ToggleInput;
}

- (UIView* ) render: (UIView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
      andHostConfig: (std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<ToggleInput> toggleBlck = std::dynamic_pointer_cast<ToggleInput>(elem);
    UISwitch * toggle = [[UISwitch alloc] init];
    NSString* desc = [NSString stringWithCString:toggleBlck->GetTitle().c_str()
                                                encoding:NSUTF8StringEncoding];
    UILabel* title = [[UILabel alloc] init];
    [title setContentHuggingPriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisHorizontal];
    title.text = desc;
    
    ACRColumnSetView* contentView = [[ACRColumnSetView alloc] init];

    [contentView addArrangedSubview:title];

    ACRSeparator* separation = [[ACRSeparator alloc]initWithFrame:CGRectMake(0,0,10,toggle.frame.size.height)
                                             withSuperview:contentView toAxis:UILayoutConstraintAxisHorizontal];
    [contentView addArrangedSubview:toggle];

    separation = [[ACRSeparator alloc]initWithFrame:CGRectMake(0,0,10,toggle.frame.size.height)
                                      withSuperview:contentView toAxis:UILayoutConstraintAxisHorizontal];
    
    [contentView adjustHuggingForLastElement];
    
    if(viewGroup)[(UIStackView*)viewGroup addArrangedSubview: contentView];
    
    return contentView;
}

@end
