//
//  ACRInputLabelView
//  ACRInputLabelView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACOBundle.h"
#import "ACOHostConfigPrivate.h"
#import "ACRIContentHoldingView.h"
#import "ACRInputLabelViewPrivate.h"
#import "UtiliOS.h"

@implementation ACRInputLabelView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    [self commonInit];
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)aDecoder
{
    self = [super initWithCoder:aDecoder];
    [self commonInit];
    return self;
}

- (void)commonInit
{
    UIView *contentView = [[[ACOBundle getInstance] getBundle] loadNibNamed:@"ACRInputLabelView" owner:self options:nil][0];
    [self addSubview:contentView];
    self.layoutMargins = UIEdgeInsetsMake(0, 0, 0, 0);
    [self.layoutMarginsGuide.leadingAnchor constraintEqualToAnchor:contentView.leadingAnchor].active = YES;
    [self.layoutMarginsGuide.trailingAnchor constraintEqualToAnchor:contentView.trailingAnchor].active = YES;
    [self.layoutMarginsGuide.topAnchor constraintEqualToAnchor:contentView.topAnchor].active = YES;
    [self.layoutMarginsGuide.bottomAnchor constraintEqualToAnchor:contentView.bottomAnchor].active = YES;
}

- (instancetype)initInputLabelView:(ACRView *)rootView acoConfig:(ACOHostConfig *)acoConfig adptiveInputElement:(const std::shared_ptr<BaseInputElement> &)inputBlck inputView:(UIView *)inputView accessibilityItem:(UIView *)accessibilityItem viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup dataSource:(NSObject<ACRIBaseInputHandler> *)dataSource
{
    self = [self initWithFrame:CGRectMake(0, 0, viewGroup.frame.size.width, 0)];
    if (self) {
        const std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
        AdaptiveCards::InputsConfig inputConfig = config->GetInputs();
        self.stack.spacing = getSpacing(inputConfig.label.inputSpacing, config);
        NSAttributedString *attributedSuffix = nil;
        RichTextElementProperties textElementProperties;
        AdaptiveCards::InputLabelConfig *pLabelConfig = &inputConfig.label.requiredInputs;
        NSMutableAttributedString *attributedLabel = nil;
        self.dataSource = dataSource;

        if (dataSource) {
            dataSource.isRequired = inputBlck->GetIsRequired();
        }

        if (inputBlck->GetIsRequired()) {
            self.isRequired = YES;
            textElementProperties.SetTextSize(pLabelConfig->size);
            textElementProperties.SetTextWeight(pLabelConfig->weight);
            textElementProperties.SetIsSubtle(pLabelConfig->isSubtle);
            textElementProperties.SetTextColor(ForegroundColor::Attention);
            std::string suffix = inputConfig.label.requiredInputs.suffix;
            if (suffix.empty()) {
                suffix = " *";
            }
            attributedSuffix = initAttributedText(acoConfig, suffix, textElementProperties, viewGroup.style);
            self.label.hidden = NO;
        }

        std::string labelstring = inputBlck->GetLabel();
        if (!labelstring.empty()) {
            pLabelConfig = (inputBlck->GetIsRequired()) ? &inputConfig.label.requiredInputs : &inputConfig.label.optionalInputs;
            textElementProperties.SetTextSize(pLabelConfig->size);
            textElementProperties.SetTextWeight(pLabelConfig->weight);
            textElementProperties.SetIsSubtle(pLabelConfig->isSubtle);
            textElementProperties.SetTextColor(pLabelConfig->color);

            attributedLabel = initAttributedText(acoConfig, labelstring, textElementProperties, viewGroup.style);
            if (attributedSuffix) {
                [attributedLabel appendAttributedString:attributedSuffix];
            }
            self.label.hidden = NO;
        } else if (!inputBlck->GetIsRequired()) {
            self.label.hidden = YES;
        }

        self.label.attributedText = attributedLabel;

        std::string errorMessage = inputBlck->GetErrorMessage();
        if (!errorMessage.empty()) {
            AdaptiveCards::ErrorMessageConfig *pLabelConfig = &inputConfig.errorMessage;
            RichTextElementProperties textElementProperties;
            textElementProperties.SetTextSize(pLabelConfig->size);
            textElementProperties.SetTextWeight(pLabelConfig->weight);
            textElementProperties.SetTextColor(ForegroundColor::Attention);
            self.errorMessage.attributedText = initAttributedText(acoConfig, errorMessage, textElementProperties, viewGroup.style);
            self.errorMessage.isAccessibilityElement = NO;
            self.hasErrorMessage = YES;
        }
        self.errorMessage.hidden = YES;

        [self.stack insertArrangedSubview:inputView atIndex:1];
        self.validationSuccessBorderColor = inputView.layer.borderColor;
        self.validationSuccessBorderRadius = inputView.layer.cornerRadius;
        self.validationSuccessBorderWidth = inputView.layer.borderWidth;

        self.inputView = inputView;
        self.label.isAccessibilityElement = NO;
        self.isAccessibilityElement = NO;
        inputView.accessibilityLabel = self.label.text;
        self.inputAccessibilityItem = inputView;
        self.inputAccessibilityItem.accessibilityIdentifier = [NSString stringWithUTF8String:inputBlck->GetId().c_str()];
        if (inputView != accessibilityItem) {
            self.inputAccessibilityItem = accessibilityItem;
            self.inputAccessibilityItem.accessibilityLabel = inputView.accessibilityLabel;
        }

        self.inputAccessibilityItem.isAccessibilityElement = YES;
        self.labelText = self.inputAccessibilityItem.accessibilityLabel;

        self.shouldGroupAccessibilityChildren = NO;

        NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
        inputHandler.isRequired = self.isRequired;
        inputHandler.hasValidationProperties |= inputHandler.isRequired;
        if (inputHandler.hasValidationProperties && errorMessage.empty()) {
            [rootView addWarnings:ACRMissingInputErrorMessage mesage:@"The input has validation, but there is no associated error message, consider adding error message to the input"];
        }

        if (self.isRequired && (!self.label || !self.label.text.length)) {
            [rootView addWarnings:ACRMissingInputErrorMessage mesage:@"There exist required input, but there is no associated label with it, consider adding label to the input"];
        }
    }
    [self setRtl:rootView.context.rtl];
    return self;
}

- (void)setRtl:(ACRRtl)rtl
{
    if (rtl == ACRRtlNone) {
        return;
    }
    UISemanticContentAttribute semanticAttribute = (rtl == ACRRtlRTL) ? UISemanticContentAttributeForceRightToLeft : UISemanticContentAttributeForceLeftToRight;

    if (self.errorMessage) {
        self.errorMessage.semanticContentAttribute = semanticAttribute;
    }

    if (self.label) {
        self.label.semanticContentAttribute = semanticAttribute;
    }

    if (self.stack) {
        self.stack.semanticContentAttribute = semanticAttribute;
    }

    if (self.inputView) {
        self.inputView.semanticContentAttribute = semanticAttribute;
    }
}

- (BOOL)validate:(NSError **)error
{
    NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
    UIView *inputView = [self getInputView];
    if (inputView) {
        [inputView resignFirstResponder];
    }
    if (inputHandler) {
        NSError *error = nil;
        if (NO == [inputHandler validate:&error]) {
            if (self.hasErrorMessage) {
                self.hasVisibilityChanged = self.errorMessage.hidden == YES;
                self.errorMessage.hidden = NO;
                self.errorMessage.isAccessibilityElement = NO;
                self.inputAccessibilityItem.accessibilityLabel = [NSString stringWithFormat:@"%@, %@,", self.labelText, self.errorMessage.text];
                self.inputAccessibilityItem.accessibilityIdentifier = self.id;
            }
        } else {
            if (self.hasErrorMessage) {
                self.hasVisibilityChanged = self.errorMessage.hidden == NO;
                self.errorMessage.hidden = YES;
                self.inputAccessibilityItem.accessibilityLabel = self.labelText;
            }

            self.stack.arrangedSubviews[1].layer.borderColor = self.validationSuccessBorderColor;
            self.stack.arrangedSubviews[1].layer.cornerRadius = self.validationSuccessBorderRadius;
            self.stack.arrangedSubviews[1].layer.borderWidth = self.validationSuccessBorderWidth;

            return YES;
        }
    }

    self.stack.arrangedSubviews[1].layer.borderWidth = self.validationFailBorderWidth;
    self.stack.arrangedSubviews[1].layer.cornerRadius = self.validationFailBorderRadius;
    self.stack.arrangedSubviews[1].layer.borderColor = self.validationFailBorderColor.CGColor;
    return NO;
}

- (NSObject<ACRIBaseInputHandler> *_Nullable)getInputHandler
{
    NSObject<ACRIBaseInputHandler> *inputHandler = nil;
    if (self.dataSource && [self.dataSource conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
        inputHandler = self.dataSource;
    } else {
        UIView *inputView = [self getInputView];
        if ([inputView conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
            inputHandler = (NSObject<ACRIBaseInputHandler> *)inputView;
        }
    }

    return inputHandler;
}

- (UIView *)getInputView
{
    if ((_stack.arrangedSubviews.count) == 3) {
        return self.stack.arrangedSubviews[1];
    }
    return nil;
}

- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view
{
    NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
    UIView *viewToFocus = [self getInputView];
    if (!inputHandler || !viewToFocus) {
        return;
    }

    [inputHandler setFocus:shouldBecomeFirstResponder view:self.inputAccessibilityItem];
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
    if (inputHandler) {
        [inputHandler getInput:dictionary];
    }
}

+ (void)commonSetFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view
{
    if (shouldBecomeFirstResponder) {
        [view becomeFirstResponder];
    } else {
        [view resignFirstResponder];
    }
}

+ (BOOL)commonTextUIValidate:(BOOL)isRequired hasText:(BOOL)hasText predicate:(NSPredicate *)predicate text:(NSString *)text error:(NSError *__autoreleasing *)error
{
    if (isRequired && !hasText) {
        if (error) {
            *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorValueMissing userInfo:nil];
        }
        return NO;
    } else if (hasText && predicate) {
        return [predicate evaluateWithObject:text];
    }
    return YES;
}

// returns intrinsic content size for inputs
- (CGSize)intrinsicContentSize
{
    CGFloat width = 0.0f, height = 0.0f;
    for (UIView *view in self.stack.arrangedSubviews) {
        if (!view.hidden) {
            CGSize size = [view intrinsicContentSize];
            width = MAX(size.width, width);
            height += size.height;
        }
    }

    return CGSizeMake(width, height);
}

@synthesize hasValidationProperties;

@synthesize id;

@synthesize hasVisibilityChanged;

@end
