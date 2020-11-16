//
//  ACRTextField
//  ACRTextField.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACRIBaseInputHandler.h"
#import <UIKit/UIKit.h>

@interface ACRTextField : UITextField <UITextFieldDelegate>
@property IBInspectable UIColor *borderColor;
@property IBInspectable CGFloat borderWidth;

- (void)dismissNumPad;
@end

@interface ACRTextEmailField : ACRTextField
@end

@interface ACRTextTelelphoneField : ACRTextField
@end

@interface ACRTextUrlField : ACRTextField
@end
