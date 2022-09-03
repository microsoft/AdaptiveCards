//
//  ACRNumericTextFiled
//  ACRNumericTextFiled.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACRNumericTextField.h"
#else
#import <AdaptiveCards/ACRNumericTextField.h>
#endif


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
