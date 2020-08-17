//
//  ACRInputNumberRenderer
//  ACRInputNumberRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputNumberRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRInputLabelViewPrivate.h"
#import "ACRNumericTextField.h"
#import "NumberInput.h"
#import "UtiliOS.h"
#import "ACRTextInputHandler.h"

@implementation ACRInputNumberRenderer

+ (ACRInputNumberRenderer *)getInstance
{
    static ACRInputNumberRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRNumberInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<NumberInput> numInputBlck = std::dynamic_pointer_cast<NumberInput>(elem);
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    ACRNumericTextField *numInput = [bundle loadNibNamed:@"ACRTextNumberField" owner:rootView options:nil][0];
    numInput.placeholder = [NSString stringWithCString:numInputBlck->GetPlaceholder().c_str() encoding:NSUTF8StringEncoding];
    
    ACRNumberInputHandler *numberInputHandler = [[ACRNumberInputHandler alloc] init:acoElem];
    
    numInput.delegate = numberInputHandler;
    numInput.text = numberInputHandler.text;
    
    ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:numInputBlck inputView:numInput viewGroup:viewGroup dataSource:numberInputHandler];

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
