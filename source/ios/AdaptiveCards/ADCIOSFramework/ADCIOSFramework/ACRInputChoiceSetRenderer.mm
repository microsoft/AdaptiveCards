//
//  ACRInputChoiceSetRenderer
//  ACRInputChoiceSetRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputChoiceSetRenderer.h"
#import "ACRInputControlTableView.h"
#import "ACRInputControlPickerView.h"
#import "ChoiceSetInput.h"

@implementation ACRInputChoiceSetRenderer

+ (ACRInputChoiceSetRenderer *)getInstance
{
    static ACRInputChoiceSetRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::ChoiceSetInput;
}

- (UIView *)render:(UIView *)viewGroup
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    UIView *inputView = nil;
    
    if(choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Compact &&
       !choiceSet->GetIsMultiSelect())
    {
        inputView = [[ACRInputControlPickerView alloc] initWithInputChoiceSet:choiceSet
                                                                   hostConfig:config
                                                                    superview:viewGroup];

        [(ACRInputControlPickerView *)inputView setDefaultView];
    }
    else
    {
        
        inputView = [[ACRInputControlTableView alloc] initWithInputChoiceSet:choiceSet WithHostConfig:config WithSuperview:viewGroup];
        [(UITableView *)inputView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"tabCellId"];
    }
    
    if(viewGroup)[(UIStackView *)viewGroup addArrangedSubview:inputView];
   
    [viewGroup addConstraint:
     [NSLayoutConstraint constraintWithItem:inputView
                                  attribute:NSLayoutAttributeLeading
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeLeading
                                 multiplier:1.0
                                   constant:0]];
    [viewGroup addConstraint:
     [NSLayoutConstraint constraintWithItem:inputView
                                  attribute:NSLayoutAttributeTrailing
                                  relatedBy:NSLayoutRelationLessThanOrEqual
                                     toItem:viewGroup
                                  attribute:NSLayoutAttributeTrailing
                                 multiplier:1.0
                                   constant:0]];
    
    return inputView;
}

@end
