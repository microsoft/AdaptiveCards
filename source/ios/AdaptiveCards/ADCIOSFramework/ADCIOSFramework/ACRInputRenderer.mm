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

- (UIView *)render:(UIView *)viewGroup
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
    txtInput.allowsEditingTextAttributes = YES;
    txtInput.borderStyle = UITextBorderStyleLine;
    txtInput.isRequired  = inputBlck->GetIsRequired();
    
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
    
    CGSize intrinsicSz = [txtInput intrinsicContentSize];
    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:CGRectMake(0, 0, intrinsicSz.width, intrinsicSz.height)];
    [wrappingview addSubview: txtInput];
    [wrappingview setAlignmentForSubview: HorizontalAlignment::Left];
    
    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview: wrappingview];
    }
    
    wrappingview.translatesAutoresizingMaskIntoConstraints = false;
    
    txtInput.translatesAutoresizingMaskIntoConstraints = false;
    
    [inputs addObject:txtInput];
    
    return wrappingview;
}

@end
