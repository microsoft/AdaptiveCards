//
//  ACRTextView
//  ACRTextView.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseCardElement.h"
#import "ACRIBaseInputHandler.h"
#else
#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACRIBaseInputHandler.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRTextView : UITextView <ACRIBaseInputHandler, UITextViewDelegate>
@property NSString *placeholderText;
@property NSUInteger maxLength;
@property IBInspectable UIColor *borderColor;
@property IBInspectable UIColor *placeholderColor;
@property NSPredicate *regexPredicate;

- (instancetype)initWithFrame:(CGRect)frame element:(ACOBaseCardElement *)element;
- (void)configWithSharedModel:(ACOBaseCardElement *)element;

@end
