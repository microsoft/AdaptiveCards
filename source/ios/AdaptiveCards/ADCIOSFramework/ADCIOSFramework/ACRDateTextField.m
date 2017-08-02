//
//  ACRDateTextField
//  ACRDateTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRDateTextField.h"

@implementation ACRDateTextField

- (IBAction)dismiss
{
    [self endEditing:YES];
}

- (IBAction)update:(UIDatePicker *)picker
{
    self.text = [self.formatter stringFromDate:picker.date];
}

- (BOOL)validate:(NSError **)error
{
    BOOL isValidated = YES;
    isValidated = [super validate:error];
    if(isValidated == YES)
    {
        NSDate *date = [self.formatter dateFromString:self.text];
        if(date < self.min)
        {
            if(error)
            {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorLessThanMinDate userInfo:nil];
            }
            return NO;
        }
        if(date > self.max)
        {
            if(error)
            {
                *error = [NSError errorWithDomain:ACRInputErrorDomain code:ACRInputErrorGreaterThanMaxDate userInfo:nil];
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
