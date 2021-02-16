//
//  ACRInputTimeRenderer
//  ACRInputTimeRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputTimeRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRDateTextField.h"
#import "ACRInputLabelViewPrivate.h"
#import "UtiliOS.h"

@implementation ACRInputTimeRenderer

+ (ACRInputTimeRenderer *)getInstance
{
    static ACRInputTimeRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTimeInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<BaseInputElement> timeInput = std::dynamic_pointer_cast<BaseInputElement>(elem);
    ACRDateTextField *field = [[ACRDateTextField alloc] initWithTimeDateInput:timeInput dateStyle:NSDateFormatterNoStyle];

    ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:timeInput inputView:field accessibilityItem:field.inputView viewGroup:viewGroup dataSource:nil];
    field.accessibilityTraits = UIAccessibilityTraitButton | UIAccessibilityTraitStaticText;    
    UIView *renderedview = inputLabelView;

    if (viewGroup) {
        if (elem->GetHeight() == HeightType::Stretch) {
            ACRColumnView *inputContainer = [[ACRColumnView alloc] init];
            [inputContainer addArrangedSubview:renderedview];

            // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
            UIView *blankTrailingSpace = [[UIView alloc] init];
            [inputContainer addArrangedSubview:blankTrailingSpace];
            [inputContainer adjustHuggingForLastElement];
            [viewGroup addArrangedSubview:inputContainer];
            renderedview = inputContainer;
        } else {
            [viewGroup addArrangedSubview:renderedview];
        }
    }

    [inputs addObject:renderedview];

    configVisibility(renderedview, elem);

    return renderedview;
}

@end
