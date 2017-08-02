//
//  ACRTextField
//  ACRTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextField.h"

@implementation ACRTextField

- (bool)validate
{
    if(self.isRequired && !self.hasText)
        return false;
    else
        return true;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = self.text;
}
@end
