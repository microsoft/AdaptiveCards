//
//  ACRTextField
//  ACRTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextField.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRInputLabelView.h"
#import "TextInput.h"


@implementation ACRTextField

- (instancetype)initWithCoder:(NSCoder *)coder
{
    return [super initWithCoder:coder];
}

- (BOOL)validate:(NSError **)error
{
    return [ACRInputLabelView commonTextUIValidate:self.isRequired hasText:self.hasText predicate:self.regexPredicate text:self.text error:error];
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
    [self resignFirstResponder];
    return YES;
}

- (void)dismissNumPad
{
    [self resignFirstResponder];
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

@end

@implementation ACRTextEmailField : ACRTextField
@end

@implementation ACRTextTelelphoneField : ACRTextField
@end

@implementation ACRTextUrlField : ACRTextField
@end
