//
//  ACRTextView
//  ACRTextView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import "ACRIBaseInputHandler.h"
#import <UIKit/UIKit.h>

@interface ACRTextView : UITextView <ACRIBaseInputHandler, UITextViewDelegate>
@property NSString *placeholderText;
@property NSUInteger maxLength;
@property IBInspectable UIColor *borderColor;
@property NSPredicate *regexPredicate;

- (instancetype)initWithFrame:(CGRect)frame element:(ACOBaseCardElement *)element;
- (void)configWithSharedModel:(ACOBaseCardElement *)element;

@end
