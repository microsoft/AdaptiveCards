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

@implementation ACRInputNumberRenderer

+ (ACRInputNumberRenderer *)getInstance
{
    static ACRInputNumberRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::NumberInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<NumberInput> numInputBlck = std::dynamic_pointer_cast<NumberInput>(elem);
    ACRNumericTextField *numInput = [[ACRNumericTextField alloc] init];
    numInput.id = [NSString stringWithCString:numInputBlck->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
    numInput.placeholder = [NSString stringWithCString:numInputBlck->GetPlaceholder().c_str() encoding:NSUTF8StringEncoding];
    numInput.text = [NSString stringWithFormat: @"%d", numInputBlck->GetValue()];
    numInput.allowsEditingTextAttributes = YES;
    numInput.borderStyle = UITextBorderStyleLine;
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

    [viewGroup addArrangedSubview: numInput];

    numInput.translatesAutoresizingMaskIntoConstraints = NO;

    NSString *format = [[NSString alloc]initWithFormat:@"H:|-[%%@]-|"];

    NSDictionary *viewsMap = NSDictionaryOfVariableBindings(numInput);

    [ACRBaseCardElementRenderer applyLayoutStyle:format viewsMap:viewsMap];

    [inputs addObject:numInput];

    return numInput;
}

@end
