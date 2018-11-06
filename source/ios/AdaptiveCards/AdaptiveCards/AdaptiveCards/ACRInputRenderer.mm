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
#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseActionElement.h"
#import "ACRQuickReplyView.h"
#import "ACRQuickReplyMultilineView.h"
#import "ACRSeparator.h"
#import "ACRButton.h"
#import "ACRAggregateTarget.h"
#import "ACRShowCardTarget.h"
#import "ACRActionOpenURLRenderer.h"

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
    std::shared_ptr<BaseActionElement> action = inputBlck->GetInlineAction();
    UIView *inputview = nil;
    ACRTextField *txtInput = nil;
    ACRTextView *txtview = nil;
    UIButton *button = nil;
    
    if(inputBlck->GetIsMultiline()) {
        ACRQuickReplyMultilineView *multilineview;
        if(action == nullptr) {
            txtview = [[ACRTextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) element:acoElem];
            txtview.allowsEditingTextAttributes = YES;
            txtview.layer.borderWidth = 0.5;
            txtview.layer.borderColor = [[UIColor grayColor] CGColor];
            txtview.font = [UIFont preferredFontForTextStyle:UIFontTextStyleBody];
            txtview.scrollEnabled = NO;
            txtview.keyboardType = UIKeyboardTypeDefault;
        } else {
            multilineview = [[ACRQuickReplyMultilineView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
            txtview = multilineview.textView;
            button = multilineview.button;
        }
        BOOL bRemove = NO;
        if(![txtview.text length]) {
            txtview.text = @"placeholder text";
            bRemove = YES;
        }
        txtview.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                         encoding:NSUTF8StringEncoding];
        txtview.isRequired  = inputBlck->GetIsRequired();
        txtview.delegate = txtview;

        CGRect boundingrect = [txtview.layoutManager lineFragmentRectForGlyphAtIndex:0 effectiveRange:nil];
        boundingrect.size.height *= 4;
        boundingrect.size.width = viewGroup.frame.size.width;
        txtview.frame = boundingrect;

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
        
        if (action == nullptr) {
            inputview = txtview;
        } else {
            inputview = multilineview;
        }
    } else {
        ACRQuickReplyView *quickReplyView;
        if(action != nullptr) {
            quickReplyView = [[ACRQuickReplyView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
            txtInput = quickReplyView.textFileld;
            button = quickReplyView.button;

        } else {
            NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
            txtInput = [bundle loadNibNamed:@"ACRTextField" owner:rootView options:nil][0];
        }

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
        if(action != nullptr) {
            inputview = quickReplyView;
        } else {
            inputview = txtInput;
        }
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

    if(action != nullptr) {
        if(inputBlck->GetIsMultiline()) {
            [inputs addObject:txtview];
        } else {
            [inputs addObject:txtInput];
        }
        NSString *title = [NSString stringWithCString:action->GetTitle().c_str() encoding:NSUTF8StringEncoding];
        
        NSDictionary *imageViewMap = [rootView getImageMap];
        NSString *key = [NSString stringWithCString:action->GetIconUrl().c_str() encoding:[NSString defaultCStringEncoding]];
        UIImage *img = imageViewMap[key];
        if(img){
            CGSize contentSize = [button.titleLabel intrinsicContentSize];
            [UIButton setImageView:img inButton:button withConfig:acoConfig contentSize:contentSize inconPlacement:ACRLeftOfTitle];
        } else {
            [button setTitle:title forState:UIControlStateNormal];
        }
        ACOBaseActionElement *acoAction = [[ACOBaseActionElement alloc] init];
        [acoAction setElem:action];
        ACRAggregateTarget *target = [[ACRAggregateTarget alloc] initWithActionElement:acoAction rootView:rootView];
        
        switch (action->GetElementType()) {
            case ActionType::ShowCard:
                [button addTarget:target action:@selector(toggleVisibilityOfShowCard) forControlEvents:UIControlEventTouchUpInside];
                break;
            case ActionType::Submit:
            case ActionType::OpenUrl:
                [button addTarget:target action:@selector(send:) forControlEvents:UIControlEventTouchUpInside];
                break;
            default:
                break;
        }
        
        [viewGroup addTarget:target];
    } else {
        [inputs addObject:inputview];
    }

    return inputview;
}

@end
