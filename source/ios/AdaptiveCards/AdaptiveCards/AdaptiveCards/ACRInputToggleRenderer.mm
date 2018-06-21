//
//  ACRInputToggleRenderer
//  ACRInputToggleRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputToggleRenderer.h"
#import "ACRInputTableView.h"
#import "ACRContentHoldingUIView.h"
#import "ACRSeparator.h"
#import "ToggleInput.h"
#import "ACRColumnSetView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRToggleInputView.h"

@implementation ACRInputToggleRenderer

+ (ACRInputToggleRenderer *)getInstance
{
    static ACRInputToggleRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRToggleInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<ToggleInput> toggleBlck = std::dynamic_pointer_cast<ToggleInput>(elem);
    
    ACRToggleInputView *inputView = [[ACRToggleInputView alloc] initWithInputToggle:toggleBlck WithHostConfig:config];
    [inputs addObject:inputView];

    if(elem->GetHeight() == HeightType::Stretch){
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:inputView];
        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [textInputContainer addArrangedSubview:blankTrailingSpace];
        [textInputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview: textInputContainer];
    } else {
        [viewGroup addArrangedSubview:inputView];
    }
    [NSLayoutConstraint constraintWithItem:inputView
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0].active = YES;
    [NSLayoutConstraint constraintWithItem:inputView
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:viewGroup
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0].active = YES;
    return inputView;
}

@end
