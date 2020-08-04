//
//  ACRTextInputHandler
//  ACRTextInputHandler.h
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ACOBaseCardElement.h"
#import <UIKit/UIKit.h>

@interface ACRTextInputHandler : NSObject<ACRIBaseInputHandler, UITextFieldDelegate>

@property NSPredicate *regexPredicate;
@property NSUInteger maxLength;
@property NSString *text;
@property BOOL hasText;

- (instancetype)init:(ACOBaseCardElement *)acoElem;

@end

@interface ACRNumberInputHandler : ACRTextInputHandler

@property NSInteger min;
@property bool hasMin;
@property NSInteger max;
@property bool hasMax;

@end

@interface ACRDateInputHandler : ACRTextInputHandler
@end
