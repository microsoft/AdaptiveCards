//
//  ACRInputRenderer
//  ACRInputRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputRenderer.h"
#import "ACOBaseActionElement.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRActionOpenURLRenderer.h"
#import "ACRAggregateTarget.h"
#import "ACRButton.h"
#import "ACRContentHoldingUIView.h"
#import "ACRInputLabelViewPrivate.h"
#import "ACRQuickReplyMultilineView.h"
#import "ACRQuickReplyView.h"
#import "ACRSeparator.h"
#import "ACRShowCardTarget.h"
#import "ACRTextField.h"
#import "ACRTextView.h"
#import "ACRToggleVisibilityTarget.h"
#import "ACRUIImageView.h"
#import "TextInput.h"
#import "UtiliOS.h"

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

+ (ACRTextField *)configTextFiled:(const std::shared_ptr<TextInput> &)inputBlck renderAction:(BOOL)renderAction rootView:(ACRView *)rootView txtInput:(ACRTextField *)txtInput viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup
{
    switch (inputBlck->GetTextInputStyle()) {
        case TextInputStyle::Text: {
            txtInput.keyboardType = UIKeyboardTypeDefault;
            break;
        }
        case TextInputStyle::Email: {
            if (renderAction) {
                txtInput.keyboardType = UIKeyboardTypeEmailAddress;
            } else {
                NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
                txtInput = [bundle loadNibNamed:@"ACRTextEmailField" owner:rootView options:nil][0];
                txtInput.delegate = txtInput;
            }

            break;
        }
        case TextInputStyle::Tel: {
            txtInput.keyboardType = UIKeyboardTypePhonePad;
            CGRect frame = CGRectMake(0, 0, viewGroup.frame.size.width, 30);
            UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:frame];
            UIBarButtonItem *flexSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
            UIBarButtonItem *doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:txtInput action:@selector(dismissNumPad)];
            [toolBar setItems:@[ doneButton, flexSpace ] animated:NO];
            [toolBar sizeToFit];
            txtInput.inputAccessoryView = toolBar;
            break;
        }
        case TextInputStyle::Url: {
            txtInput.keyboardType = UIKeyboardTypeURL;
            break;
        }
        default: {
            txtInput.keyboardType = UIKeyboardTypeAlphabet;
            break;
        }
    }

    NSString *placeHolderStr = [NSString stringWithCString:inputBlck->GetPlaceholder().c_str()
                                                  encoding:NSUTF8StringEncoding];
    txtInput.id = [NSString stringWithCString:inputBlck->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
    txtInput.maxLength = inputBlck->GetMaxLength();
    txtInput.placeholder = placeHolderStr;
    txtInput.text = [NSString stringWithCString:inputBlck->GetValue().c_str() encoding:NSUTF8StringEncoding];
    txtInput.allowsEditingTextAttributes = YES;
    txtInput.isRequired = inputBlck->GetIsRequired();
    std::string cpattern = inputBlck->GetRegex();
    if (!cpattern.empty()) {
        NSString *pattern = [NSString stringWithCString:cpattern.c_str() encoding:NSUTF8StringEncoding];
        txtInput.regexPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", pattern];
    }
    txtInput.hasValidationProperties = txtInput.isRequired || txtInput.maxLength || txtInput.regexPredicate;
    return txtInput;
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
    ACRButton *button = nil;
    ACRQuickReplyMultilineView *multilineview = nil;
    ACRQuickReplyView *quickReplyView = nil;

    BOOL renderAction = NO;
    if (action != nullptr && [acoConfig getHostConfig] -> GetSupportsInteractivity()) {
        if (action->GetElementType() == ActionType::ShowCard) {
            if ([acoConfig getHostConfig] -> GetActions().showCard.actionMode != ActionMode::Inline) {
                renderAction = YES;
            }
        } else {
            renderAction = YES;
        }
    }

    if (inputBlck->GetIsMultiline()) {
        if (renderAction) {
            // if action is defined, load ACRQuickReplyMultilineView nib for customizable UI
            multilineview = [[ACRQuickReplyMultilineView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
            txtview = multilineview.textView;
            // configure it with basecard element since init with decoder can't pass in input param
            [txtview configWithSharedModel:acoElem];
            button = multilineview.button;
            // borderColor is user defined runtime attribute
            if (txtview.borderColor) {
                txtview.layer.borderColor = txtview.borderColor.CGColor;
            }
            [NSLayoutConstraint constraintWithItem:multilineview
                                         attribute:NSLayoutAttributeWidth
                                         relatedBy:NSLayoutRelationGreaterThanOrEqual
                                            toItem:txtview
                                         attribute:NSLayoutAttributeWidth
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            inputview = multilineview;

        } else {
            txtview = [[ACRTextView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0) element:acoElem];
            txtview.allowsEditingTextAttributes = YES;
            txtview.layer.borderWidth = 0.5;
            txtview.layer.borderColor = [[UIColor grayColor] CGColor];
            txtview.scrollEnabled = NO;
            txtview.keyboardType = UIKeyboardTypeDefault;
            [txtview.layer setCornerRadius:5.0f];
            inputview = txtview;
        }
        ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:inputBlck inputView:inputview viewGroup:viewGroup dataSource:nil];
        inputview = inputLabelView;
    } else {
        if (renderAction) {
            // if action is defined, load ACRQuickReplyView nib for customizable UI
            quickReplyView = [[ACRQuickReplyView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
            txtInput = quickReplyView.textField;
            button = quickReplyView.button;
            txtInput.delegate = quickReplyView;
            inputview = quickReplyView;
            txtInput = [ACRInputRenderer configTextFiled:inputBlck renderAction:renderAction rootView:rootView txtInput:txtInput viewGroup:viewGroup];
            ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:inputBlck inputView:inputview viewGroup:viewGroup dataSource:txtInput];
            inputview = inputLabelView;

        } else {
            NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
            txtInput = [bundle loadNibNamed:@"ACRTextField" owner:rootView options:nil][0];
            txtInput.delegate = txtInput;
            inputview = txtInput;
            txtInput = [ACRInputRenderer configTextFiled:inputBlck renderAction:renderAction rootView:rootView txtInput:txtInput viewGroup:viewGroup];
            ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:inputBlck inputView:txtInput viewGroup:viewGroup dataSource:nil];
            inputview = inputLabelView;
        }

        [inputview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }

    if (elem->GetHeight() == HeightType::Stretch) {
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

    // configures for action
    if (renderAction) {
        if (inputBlck->GetIsMultiline()) {
            [inputs addObject:txtview];
        } else {
            [inputs addObject:inputview];
        }
        NSString *title = [NSString stringWithCString:action->GetTitle().c_str() encoding:NSUTF8StringEncoding];
        NSDictionary *imageViewMap = [rootView getImageMap];
        NSString *key = [NSString stringWithCString:action->GetIconUrl().c_str() encoding:[NSString defaultCStringEncoding]];
        UIImage *img = imageViewMap[key];
        button.iconPlacement = ACRNoTitle;

        if (img) {
            UIImageView *iconView = [[ACRUIImageView alloc] init];
            iconView.image = img;
            [button addSubview:iconView];
            button.iconView = iconView;
            [button setImageView:img withConfig:acoConfig];
        } else if (key.length) {
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)action.get()];
            NSString *key = [number stringValue];
            UIImageView *view = [rootView getImageView:key];
            if (view && view.image) {
                button.iconView = view;
                [button addSubview:view];
                [button setImageView:view.image withConfig:acoConfig];
            } else {
                button.iconView = view;
                [button addSubview:view];
                [rootView setImageView:key view:button];
            }
            [NSLayoutConstraint constraintWithItem:button
                                         attribute:NSLayoutAttributeWidth
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:view
                                         attribute:NSLayoutAttributeWidth
                                        multiplier:1.0
                                          constant:0]
                .active = YES;

        } else {
            [button setTitle:title forState:UIControlStateNormal];
        }
        ACOBaseActionElement *acoAction = [[ACOBaseActionElement alloc] init];
        [acoAction setElem:action];

        NSObject *target;
        if (ACRRenderingStatus::ACROk == buildTargetForButton([rootView getQuickReplyTargetBuilderDirector], action, button, &target)) {
            if (action->GetElementType() == ActionType::Submit) {
                quickReplyView.target = (ACRAggregateTarget *)target;
            }
            [viewGroup addTarget:target];
        }
    } else {
        [inputs addObject:inputview];
    }

    configVisibility(inputview, elem);

    return inputview;
}

@end
