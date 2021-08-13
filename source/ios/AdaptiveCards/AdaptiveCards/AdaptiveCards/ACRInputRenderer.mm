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
#import "ACOBundle.h"
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
#import "ACRTextInputHandler.h"
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

+ (ACRTextField *)configTextFiled:(std::shared_ptr<TextInput> const &)inputBlock renderAction:(BOOL)renderAction rootView:(ACRView *)rootView viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup
{
    ACRTextField *txtInput = nil;
    NSBundle *bundle = [[ACOBundle getInstance] getBundle];
    switch (inputBlock->GetTextInputStyle()) {
        case TextInputStyle::Email: {
            txtInput = [bundle loadNibNamed:@"ACRTextEmailField" owner:rootView options:nil][0];
            break;
        }
        case TextInputStyle::Tel: {
            txtInput = [bundle loadNibNamed:@"ACRTextTelelphoneField" owner:rootView options:nil][0];
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
            txtInput = [bundle loadNibNamed:@"ACRTextUrlField" owner:rootView options:nil][0];
            break;
        }
        case TextInputStyle::Text:
        default: {
            txtInput = [bundle loadNibNamed:@"ACRTextField" owner:rootView options:nil][0];
            break;
        }
    }
    txtInput.placeholder = [NSString stringWithCString:inputBlock->GetPlaceholder().c_str()
                                              encoding:NSUTF8StringEncoding];
    txtInput.text = [NSString stringWithCString:inputBlock->GetValue().c_str() encoding:NSUTF8StringEncoding];
    txtInput.allowsEditingTextAttributes = YES;
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
    if (action != nullptr && [acoConfig getHostConfig]->GetSupportsInteractivity()) {
        if (action->GetElementType() == ActionType::ShowCard) {
            if ([acoConfig getHostConfig]->GetActions().showCard.actionMode != ActionMode::Inline) {
                renderAction = YES;
            }
        } else {
            renderAction = YES;
        }
    }

    ACRTextInputHandler *textInputHandler = [[ACRTextInputHandler alloc] init:acoElem];
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
            configRtl(multilineview.contentView, rootView.context);
            configRtl(txtview, rootView.context);
            configRtl(button, rootView.context);
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
        ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:inputBlck inputView:inputview accessibilityItem:inputview viewGroup:viewGroup dataSource:nil];
        inputview = inputLabelView;
    } else {
        if (renderAction) {
            // if action is defined, load ACRQuickReplyView nib for customizable UI
            quickReplyView = [[ACRQuickReplyView alloc] initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
            button = quickReplyView.button;
            txtInput = [ACRInputRenderer configTextFiled:inputBlck renderAction:renderAction rootView:rootView viewGroup:viewGroup];
            [quickReplyView addTextField:txtInput];
            ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:inputBlck inputView:quickReplyView accessibilityItem:quickReplyView viewGroup:viewGroup dataSource:textInputHandler];
            inputview = inputLabelView;
            configRtl(quickReplyView.stack, rootView.context);
            configRtl(txtInput, rootView.context);
            configRtl(button, rootView.context);
        } else {
            txtInput = [ACRInputRenderer configTextFiled:inputBlck renderAction:renderAction rootView:rootView viewGroup:viewGroup];
            ACRInputLabelView *inputLabelView = [[ACRInputLabelView alloc] initInputLabelView:rootView acoConfig:acoConfig adptiveInputElement:inputBlck inputView:txtInput accessibilityItem:txtInput viewGroup:viewGroup dataSource:textInputHandler];
            inputview = inputLabelView;
        }
        txtInput.delegate = textInputHandler;

        [inputview setContentCompressionResistancePriority:UILayoutPriorityRequired forAxis:UILayoutConstraintAxisVertical];
    }

    if (elem->GetHeight() == HeightType::Stretch && !inputBlck->GetIsMultiline()) {
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

        ACOBaseActionElement *acoSelectAction = [ACOBaseActionElement getACOActionElementFromAdaptiveElement:action];

        NSObject *target;
        if (ACRRenderingStatus::ACROk == buildTargetForButton([rootView getQuickReplyTargetBuilderDirector], acoSelectAction, button, &target)) {
            if (action->GetElementType() == ActionType::Submit) {
                quickReplyView.target = (ACRAggregateTarget *)target;
                quickReplyView.userInteractionEnabled = [acoSelectAction isEnabled];
                if (![acoSelectAction isEnabled]) {
                    quickReplyView.accessibilityTraits |= UIAccessibilityTraitNotEnabled;
                }
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
