//
//  ACRInputRenderer
//  ACRInputRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRTextField.h"
#import "TextInput.h"

@implementation ACRInputRenderer

+ (ACRInputRenderer *)getInstance
{
    static ACRInputRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::TextInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<TextInput> inputBlck = std::dynamic_pointer_cast<TextInput>(elem);
    ACRTextField *txtInput = [[ACRTextField alloc] init];
    NSString *placeHolderStr = [NSString stringWithCString:inputBlck->GetPlaceholder().c_str()
                                                encoding:NSUTF8StringEncoding];
    txtInput.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
    txtInput.placeholder = placeHolderStr;
    txtInput.text = [NSString stringWithCString:inputBlck->GetValue().c_str() encoding:NSUTF8StringEncoding];
    txtInput.allowsEditingTextAttributes = YES;
    txtInput.borderStyle = UITextBorderStyleLine;
    txtInput.isRequired  = inputBlck->GetIsRequired();
    txtInput.delegate = txtInput;

    switch(inputBlck->GetTextInputStyle())
    {
        case TextInputStyle::Text:
        {
            txtInput.keyboardType = UIKeyboardTypeAlphabet;
            break;
        }
        case TextInputStyle::Email:
        {
            txtInput.keyboardType = UIKeyboardTypeEmailAddress;
            break;
        }
        case TextInputStyle::Tel:
        {
            txtInput.keyboardType = UIKeyboardTypePhonePad;
            CGRect frame = CGRectMake(0, 0, viewGroup.frame.size.width, 30);
            UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:frame];
            UIBarButtonItem *flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
            UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:txtInput action:@selector(dismissNumPad)];
            [toolBar setItems:@[doneButton, flexSpace] animated:NO];
            [toolBar sizeToFit];
            txtInput.inputAccessoryView = toolBar;
            break;
        }
        case TextInputStyle::Url:
        {
            txtInput.keyboardType = UIKeyboardTypeURL;
            break;
        }
        default:
        {
            txtInput.keyboardType = UIKeyboardTypeAlphabet;
            break;
        }
    }

    [viewGroup addArrangedSubview: txtInput];

    txtInput.translatesAutoresizingMaskIntoConstraints = false;

    NSString *format = [[NSString alloc]initWithFormat:@"H:|-[%%@]-|"];

    NSDictionary *viewsMap = NSDictionaryOfVariableBindings(txtInput);

    [ACRBaseCardElementRenderer applyLayoutStyle:format viewsMap:viewsMap];

    [inputs addObject:txtInput];

    return txtInput;
}

@end
