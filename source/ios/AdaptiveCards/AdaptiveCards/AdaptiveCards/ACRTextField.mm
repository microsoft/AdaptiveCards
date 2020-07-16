//
//  ACRTextField
//  ACRTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextField.h"
#import "ACOBaseCardElementPrivate.h"
#import "TextInput.h"


@implementation ACRTextField

- (instancetype)initWithCoder:(NSCoder *)coder
{
    return [super initWithCoder:coder];
}

- (BOOL)validate:(NSError **)error
{
    if (self.isRequired && !self.hasText) {
        if (error) {
            *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorValueMissing userInfo:nil];
        }
        return NO;
    } else
        if (_regexPredicate) {
            return [_regexPredicate evaluateWithObject:self.text];
        }
        return YES;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = self.text;
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

@end

@implementation ACRTextEmailField : ACRTextField
@end

@implementation ACRTextTelelphoneField : ACRTextField
@end

@implementation ACRTextUrlField : ACRTextField
@end
