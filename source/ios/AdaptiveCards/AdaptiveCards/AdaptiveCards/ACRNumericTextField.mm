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



@end
