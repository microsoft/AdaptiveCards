//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputToggleRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ToggleInput.h"

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
    title.text = desc;
    
    UIStackView* contentView = [[UIStackView alloc] init];
  
    contentView.axis = UILayoutConstraintAxisHorizontal;
    contentView.distribution = UIStackViewDistributionFill;
    [contentView addArrangedSubview:title];
    [contentView addArrangedSubview:toggle];
    
    if(viewGroup)[(UIStackView*)viewGroup addArrangedSubview: contentView];
    
    return contentView;
}

@end
