//
//  ACRTextInputHandler
//  ACRTextInputHandler.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACRIBaseInputHandler.h"
#import <UIKit/UIKit.h>

@interface ACRTextInputHandler : NSObject <ACRIBaseInputHandler, UITextFieldDelegate>

@property NSPredicate *regexPredicate;
@property NSUInteger maxLength;
@property NSString *text;
@property BOOL hasText;

- (instancetype)init:(ACOBaseCardElement *)acoElem;

@end

@interface ACRNumberInputHandler : ACRTextInputHandler

@property double min;
@property bool hasMin;
@property double max;
@property bool hasMax;

@end

@interface ACRDateInputHandler : ACRTextInputHandler
@end
