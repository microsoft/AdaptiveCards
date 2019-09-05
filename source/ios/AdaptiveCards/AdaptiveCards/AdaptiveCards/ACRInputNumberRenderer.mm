//
//  ACRInputNumberRenderer
//  ACRInputNumberRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputNumberRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRNumericTextField.h"
#import "NumberInput.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "UtiliOS.h"

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
    ACRNumericTextField *numInput = [[ACRNumericTextField alloc] init];
    numInput.id = [NSString stringWithCString:numInputBlck->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
    numInput.placeholder = [NSString stringWithCString:numInputBlck->GetPlaceholder().c_str() encoding:NSUTF8StringEncoding];
    numInput.text = [NSString stringWithFormat: @"%d", numInputBlck->GetValue()];
    numInput.allowsEditingTextAttributes = YES;
    numInput.borderStyle = UITextBorderStyleRoundedRect;
    numInput.keyboardType = UIKeyboardTypeNumberPad;
    numInput.min = numInputBlck->GetMin();
    numInput.max = numInputBlck->GetMax();
    CGRect frame = CGRectMake(0, 0, viewGroup.frame.size.width, 30);
    UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:frame];
    UIBarButtonItem *flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
    UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:numInput action:@selector(dismissNumPad)];
    [toolBar setItems:@[doneButton, flexSpace] animated:NO];
    [toolBar sizeToFit];
    numInput.inputAccessoryView = toolBar;

    if(elem->GetHeight() == HeightType::Stretch){
        ACRColumnView *inputContainer = [[ACRColumnView alloc] init];
        [inputContainer addArrangedSubview: numInput];

        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [inputContainer addArrangedSubview:blankTrailingSpace];
        [inputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview: inputContainer];
    } else {
        [viewGroup addArrangedSubview: numInput];
    }

    numInput.translatesAutoresizingMaskIntoConstraints = NO;

    NSString *format = [[NSString alloc]initWithFormat:@"H:|-[%%@]-|"];

    NSDictionary *viewsMap = NSDictionaryOfVariableBindings(numInput);

    [ACRBaseCardElementRenderer applyLayoutStyle:format viewsMap:viewsMap];

    [inputs addObject:numInput];

    configVisibility(numInput, elem);

    return numInput;
}

@end
