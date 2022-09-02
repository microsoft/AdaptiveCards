//
//  ACRTextField
//  ACRTextField.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACRTextField.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>
#import <AdaptiveCards/ACRInputLabelView.h>
#import <AdaptiveCards/TextInput.h>


@implementation ACRTextField

- (instancetype)initWithCoder:(NSCoder *)coder
{
    return [super initWithCoder:coder];
}

- (void)dismissNumPad
{
    [self resignFirstResponder];
}

@end

@implementation ACRTextEmailField : ACRTextField
@end

@implementation ACRTextTelelphoneField : ACRTextField
@end

@implementation ACRTextUrlField : ACRTextField
@end
