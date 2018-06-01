//
//  CustomInputNumberRenderer
//  CustomInputNumberRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "CustomInputNumberRenderer.h"
#import <AdaptiveCards/ACFramework.h>
#import <AdaptiveCards/ACOHostConfigPrivate.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>
#import <AdaptiveCards/ACRNumericTextField.h>
#import <AdaptiveCards/HostConfig.h>
#import <AdaptiveCards/NumberInput.h>

@implementation CustomInputNumberRenderer

+ (CustomInputNumberRenderer *)getInstance
{
    static CustomInputNumberRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig
{
    std::shared_ptr<AdaptiveCards::HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<AdaptiveCards::BaseCardElement> elem = [acoElem element];
    std::shared_ptr<AdaptiveCards::NumberInput> numInputBlck = std::dynamic_pointer_cast<NumberInput>(elem);
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
    
    [numInput setBackgroundColor: [UIColor colorWithRed:1.0
                                               green:59.0/255.0
                                                blue:48.0/255.0
                                               alpha:1.0]];
    return numInput;
}
@end
