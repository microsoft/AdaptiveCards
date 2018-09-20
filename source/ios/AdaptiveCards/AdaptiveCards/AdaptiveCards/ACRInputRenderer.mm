//
//  ACRInputRenderer
//  ACRInputRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRTextField.h"
#import "ACRTextView.h"
#import "TextInput.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"

@implementation ACRInputRenderer

+ (ACRInputRenderer *)getInstance
{
    static ACRInputRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTextInput;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
          rootView:(ACRView *)rootView
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<TextInput> inputBlck = std::dynamic_pointer_cast<TextInput>(elem);
    UIView *inputview = nil;

    if(inputBlck->GetIsMultiline()) {
        ACRTextView *txtview = [[ACRTextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) element:acoElem];
        BOOL bRemove = NO;
        if(![txtview.text length]) {
            txtview.text = @"placeholder text";
            bRemove = YES;
        }
        txtview.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                         encoding:NSUTF8StringEncoding];
        txtview.font = [UIFont preferredFontForTextStyle:UIFontTextStyleBody];
        txtview.allowsEditingTextAttributes = YES;
        txtview.isRequired  = inputBlck->GetIsRequired();
        txtview.delegate = txtview;

        txtview.layer.borderWidth = 0.5;
        txtview.layer.borderColor = [[UIColor grayColor] CGColor];
        CGRect boundingrect = [txtview.layoutManager lineFragmentRectForGlyphAtIndex:0 effectiveRange:nil];
        boundingrect.size.height *= 4;
        boundingrect.size.width = viewGroup.frame.size.width;
        txtview.frame = boundingrect;
        txtview.keyboardType = UIKeyboardTypeDefault;
        txtview.scrollEnabled = NO;

        if(bRemove){
            txtview.text = @"";
        }

        CGRect frame = CGRectMake(0, 0, viewGroup.frame.size.width, 30);
        UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:frame];
        UIBarButtonItem *flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
        UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:txtview action:@selector(dismissKeyboard)];
        [toolBar setItems:@[doneButton, flexSpace] animated:NO];
        [toolBar sizeToFit];
        txtview.inputAccessoryView = toolBar;
        inputview = txtview;
    } else {
        NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
        ACRTextField *txtInput = [bundle loadNibNamed:@"ACRTextField" owner:rootView options:nil][0];
        NSString *placeHolderStr = [NSString stringWithCString:inputBlck->GetPlaceholder().c_str()
                                                    encoding:NSUTF8StringEncoding];
        txtInput.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                         encoding:NSUTF8StringEncoding];
        txtInput.maxLength = inputBlck->GetMaxLength();
        txtInput.placeholder = placeHolderStr;
        txtInput.text = [NSString stringWithCString:inputBlck->GetValue().c_str() encoding:NSUTF8StringEncoding];
        txtInput.allowsEditingTextAttributes = YES;
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
        inputview = txtInput;
    }
    [inputview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];

    if(elem->GetHeight() == HeightType::Stretch){
        ACRColumnView *textInputContainer = [[ACRColumnView alloc] init];
        [textInputContainer addArrangedSubview:inputview];

        // Add a blank view so the input field doesnt grow as large as it can and so it keeps the same behavior as Android and UWP
        UIView *blankTrailingSpace = [[UIView alloc] init];
        [textInputContainer addArrangedSubview:blankTrailingSpace];
        [textInputContainer adjustHuggingForLastElement];

        [viewGroup addArrangedSubview:textInputContainer];
    } else {
        [viewGroup addArrangedSubview:inputview];
    }

    inputview.translatesAutoresizingMaskIntoConstraints = false;
    NSString *format = [[NSString alloc]initWithFormat:@"H:|-[%%@]-|"];
    NSDictionary *viewsMap = NSDictionaryOfVariableBindings(inputview);
    [ACRBaseCardElementRenderer applyLayoutStyle:format viewsMap:viewsMap];

    [inputs addObject:inputview];

    return inputview;
}

@end
