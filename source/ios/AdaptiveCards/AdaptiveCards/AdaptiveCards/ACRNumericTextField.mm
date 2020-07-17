//
//  ACRNumericTextFiled
//  ACRNumericTextFiled.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRNumericTextField.h"

@implementation ACRNumericTextField

- (BOOL)validate:(NSError **)error
{
    BOOL isValidated = YES;
    isValidated = [super validate:error];
    if (isValidated == YES) {
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
    dictionary[self.id] = self.text;
}

@end
