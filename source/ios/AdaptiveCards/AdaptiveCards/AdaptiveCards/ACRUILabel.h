//
//  ACRUILable.h
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseCardElement.h"
#else
#import <AdaptiveCards/ACOBaseCardElement.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRUILabel : UITextView <UITextViewDelegate>
@property ACRContainerStyle style;
@property CGFloat area;

- (void)handleInlineAction:(UIGestureRecognizer *)gestureRecognizer;

@end
