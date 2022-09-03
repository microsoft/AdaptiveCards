//
//  ACRTextField
//  ACRTextField.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseCardElement.h"
#import "ACRIBaseInputHandler.h"
#else
#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRTextField : UITextField <UITextFieldDelegate>

- (void)dismissNumPad;
@end

@interface ACRTextEmailField : ACRTextField
@end

@interface ACRTextTelelphoneField : ACRTextField
@end

@interface ACRTextUrlField : ACRTextField
@end
