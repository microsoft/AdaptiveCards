//
//  ACRInputDateRenderer
//  ACRInputDateRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputDateRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRDateTextField.h"
#import "ACRInputLabelViewPrivate.h"
#import "UtiliOS.h"

@implementation ACRInputDateRenderer

+ (ACRInputDateRenderer *)getInstance
{
    static ACRInputDateRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRDateInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<BaseInputElement> dateInput = std::dynamic_pointer_cast<BaseInputElement>(elem);
    ACRDateTextField *dateField = [[ACRDateTextField alloc] initWithTimeDateInput:dateInput dateStyle:NSDateFormatterShortStyle];

    ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:dateInput inputView:dateField accessibilityItem:dateField.inputView viewGroup:viewGroup dataSource:nil];
    dateField.accessibilityTraits = UIAccessibilityTraitButton | UIAccessibilityTraitStaticText;

    if (elem->GetHeight() == HeightType::Stretch) {
        ACRColumnView *inputContainer = [[ACRColumnView alloc] init];
        [inputContainer addArrangedSubview:inputLabelView];

        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [inputContainer addArrangedSubview:blankTrailingSpace];
        [inputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview:inputContainer];
    } else {
        [viewGroup addArrangedSubview:inputLabelView];
    }

    [inputs addObject:inputLabelView];

    configVisibility(inputLabelView, elem);

    return inputLabelView;
}

@end
