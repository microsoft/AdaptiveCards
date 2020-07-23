//
//  ACRTextInputHandler
//  ACRTextInputHandler.mm
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRTextInputHandler.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRInputLabelView.h"
#import "NumberInput.h"
#import "TextInput.h"


@implementation ACRTextInputHandler

- (instancetype)init:(ACOBaseCardElement *)acoElem
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<TextInput> inputBlock = std::dynamic_pointer_cast<TextInput>(elem);
        self.id = [NSString stringWithCString:inputBlock->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.maxLength = inputBlock->GetMaxLength();
        self.isRequired = inputBlock->GetIsRequired();
        std::string cpattern = inputBlock->GetRegex();
        if (!cpattern.empty()) {
            NSString *pattern = [NSString stringWithCString:cpattern.c_str() encoding:NSUTF8StringEncoding];
            self.regexPredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", pattern];
        }
        self.hasValidationProperties = self.isRequired || self.maxLength || self.regexPredicate;
        self.text = [NSString stringWithCString:inputBlock->GetValue().c_str() encoding:NSUTF8StringEncoding];
        if (self.text && self.text.length) {
            self.hasText = YES;
        }
    }
    return self;
}

- (BOOL)validate:(NSError **)error
{
    return [ACRInputLabelView commonTextUIValidate:self.isRequired hasText:self.hasText predicate:self.regexPredicate text:self.text error:error];
}

- (BOOL)textFieldShouldEndEditing:(UITextField *)textField
{
    self.text = textField.text;
    self.hasText = textField.hasText;
    return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = self.text;
}

- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view
{
    [ACRInputLabelView commonSetFocus:shouldBecomeFirstResponder view:view];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if (!_maxLength) {
        return YES;
    }

    if (range.length + range.location > textField.text.length) {
        return NO;
    }

    NSUInteger newLength = [textField.text length] + [string length] - range.length;
    return newLength <= _maxLength;
}


@synthesize isRequired;
@synthesize hasValidationProperties;
@synthesize id;

@end

@implementation ACRNumberInputHandler {
    NSCharacterSet *_notDigits;
}

- (instancetype)init:(ACOBaseCardElement *)acoElem
{
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<NumberInput> numberInputBlock = std::dynamic_pointer_cast<NumberInput>(elem);
    self = [super init];
    if (self) {
        self.isRequired = numberInputBlock->GetIsRequired();
        self.text = [NSString stringWithFormat:@"%d", numberInputBlock->GetValue()];
        self.id = [NSString stringWithCString:numberInputBlock->GetId().c_str()
        encoding:NSUTF8StringEncoding];
        if (self.text && self.text.length) {
            self.hasText = YES;
        }
        NSMutableCharacterSet *characterSets = [NSMutableCharacterSet characterSetWithCharactersInString:@"-."];
        [characterSets formUnionWithCharacterSet:[NSCharacterSet decimalDigitCharacterSet]];
        _notDigits = [characterSets invertedSet];
        self.id = [NSString stringWithCString:numberInputBlock->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.min = numberInputBlock->GetMin();
        self.max = numberInputBlock->GetMax();
        self.hasValidationProperties = self.isRequired || self.min || self.max;
    }
    return self;
}

- (BOOL)validate:(NSError **)error
{
    BOOL isValidated = YES;
    isValidated = [super validate:error];
    if (isValidated == YES) {
        if ([self.text rangeOfCharacterFromSet:_notDigits].location != NSNotFound) {
            return NO;
        }
        int val = [self.text intValue];
        if (val < self.min) {
            if (error) {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorLessThanMin userInfo:nil];
            }
            return NO;
        }
        if (val > self.max) {
            if (error) {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorGreaterThanMax userInfo:nil];
            }
            return NO;
        }
        return YES;
    }
    return isValidated;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    NSError *error;
    [self validate:&error];
    dictionary[self.id] = self.text;
}
@end
