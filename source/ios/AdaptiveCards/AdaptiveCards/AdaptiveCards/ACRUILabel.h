//
//  ACRUILable.h
//  AdaptiveCards
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOBaseCardElement.h"
#import <UIKit/UIKit.h>

@interface ACRUILabel : UITextView
@property ACRContainerStyle style;
@property CGFloat area;

- (void)handleInlineAction:(UIGestureRecognizer *)gestureRecognizer;

@end
