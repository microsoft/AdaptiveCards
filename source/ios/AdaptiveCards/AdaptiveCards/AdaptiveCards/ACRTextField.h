//
//  ACRTextField
//  ACRTextField.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACRIBaseInputHandler.h"
#import <UIKit/UIKit.h>

@interface ACRTextField : UITextField <ACRIBaseInputHandler, UITextFieldDelegate>
@property NSString *id;
@property bool isRequired;
@property NSPredicate *regexPredicate;

@property NSUInteger maxLength;

- (void)dismissNumPad;
@end

@interface ACRTextEmailField : ACRTextField
@end

@interface ACRTextTelelphoneField : ACRTextField
@end

@interface ACRTextUrlField : ACRTextField
@end
