//
//  ACRTextField
//  ACRTextField.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRIBaseInputHandler.h"

@interface ACRTextField:UITextField<ACRIBaseInputHandler, UITextFieldDelegate>
@property NSString* id;
@property bool isRequired;
- (void) dismissNumPad;
@end
