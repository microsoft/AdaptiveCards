//
//  ACRInputLabelView
//  ACRInputLabelView.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

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
    NSBundle *bundle = [NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"];
    UIView *contentView = [bundle loadNibNamed:@"ACRInputLabelView" owner:self options:nil][0];
    [self addSubview:contentView];
    self.layoutMargins = UIEdgeInsetsMake(0, 0, 0, 0);
    [self.layoutMarginsGuide.leadingAnchor constraintEqualToAnchor:contentView.leadingAnchor].active = YES;
    [self.layoutMarginsGuide.trailingAnchor constraintEqualToAnchor:contentView.trailingAnchor].active = YES;
    [self.layoutMarginsGuide.topAnchor constraintEqualToAnchor:contentView.topAnchor].active = YES;
    [self.layoutMarginsGuide.bottomAnchor constraintEqualToAnchor:contentView.bottomAnchor].active = YES;
}

- (instancetype)initInputLabelView:(ACRView *)rootView acoConfig:(ACOHostConfig *)acoConfig adptiveInputElement:(const std::shared_ptr<BaseInputElement> &)inputBlck inputView:(UIView *)inputView viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup dataSource:(NSObject<ACRIBaseInputHandler> *)dataSource
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
            self.hasErrorMessage = YES;
        }
        self.errorMessage.hidden = YES;

        [self.stack insertArrangedSubview:inputView atIndex:1];
        NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
        inputHandler.isRequired = self.isRequired;
        inputHandler.hasValidationProperties |= inputHandler.isRequired;
        if (inputHandler.hasValidationProperties && errorMessage.empty()) {
            [rootView addWarnings:ACRMissingInputErrorMessage mesage:@"The input has validation, but there is no associated error message, consider adding error message to the input"];
        }
    }
    return self;
}

- (BOOL)validate:(NSError **)error
{
    NSObject<ACRIBaseInputHandler> *inputHandler = [self getInputHandler];
    if (inputHandler) {
        NSError *error = nil;
        if (NO == [inputHandler validate:&error]) {
            if (self.hasErrorMessage) {
                self.errorMessage.hidden = NO;
            }
        } else {
            if (self.hasErrorMessage) {
                self.errorMessage.hidden = YES;
            }
            self.stack.arrangedSubviews[1].layer.borderWidth = 0;
            return YES;
        }
    }
    self.stack.arrangedSubviews[1].layer.borderWidth = 1;
    self.stack.arrangedSubviews[1].layer.cornerRadius = 6.0f;
    self.stack.arrangedSubviews[1].layer.borderColor = UIColor.systemRedColor.CGColor;
    return NO;
}

- (NSObject<ACRIBaseInputHandler> *_Nullable)getInputHandler
{
    NSObject<ACRIBaseInputHandler> *inputHandler = nil;
    if (self.dataSource && [self.dataSource conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
        inputHandler = self.dataSource;
    }
    else {
        id inputView = [self getInputView];
        if ([inputView conformsToProtocol:@protocol(ACRIBaseInputHandler)]) {
            inputHandler = inputView;
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
    id inputHandler = [self getInputHandler];
    UIView *viewToFocus = [self getInputView];
    if (!inputHandler || !viewToFocus) {
        return;
    }

    [inputHandler setFocus:shouldBecomeFirstResponder view:viewToFocus];
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    id<ACRIBaseInputHandler> inputHandler = [self getInputHandler];
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
    } else if (predicate) {
        return [predicate evaluateWithObject:text];
    }
    return YES;
}

@synthesize hasValidationProperties;

@end
