//
//  ACRNumericTextFiled
//  ACRNumericTextFiled.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRNumericTextField.h"

@implementation ACRNumericTextField {
    NSCharacterSet *_notDigits;
}

- (instancetype)init
{
    self = [super init];
    NSMutableCharacterSet *characterSets = [NSMutableCharacterSet characterSetWithCharactersInString:@"-."];
    [characterSets formUnionWithCharacterSet:[NSCharacterSet decimalDigitCharacterSet]];
    _notDigits = [characterSets invertedSet];
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
