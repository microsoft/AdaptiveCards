//
//  ACRLongPressGestureRecognizerEventHandler
//  ACRLongPressGestureRecognizerEventHandler.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRLongPressGestureRecognizerEventHandler.h"

@implementation ACRLongPressGestureRecognizerEventHandler

// this method does the followings
// 1. it provides users with cue that select action is about to be initiated
// 2. execute select action by calling its delegate
- (IBAction)processLongPressGesture:(UILongPressGestureRecognizer *)recognizer;
{
    // activate it when fingers lifts off
    if (recognizer.state == UIGestureRecognizerStateBegan) {
        UIColor *backgroundColor = recognizer.view.backgroundColor;
        // set up animation as visual cue
        UIViewPropertyAnimator *animation = [UIViewPropertyAnimator runningPropertyAnimatorWithDuration:0.25
            delay:0
            options:UIViewAnimationCurveEaseOut
            animations:^{
                recognizer.view.backgroundColor =
                    [UIColor colorWithRed:0xD4 / 255.0
                                    green:0xD4 / 255.0
                                     blue:0xD4 / 255.0
                                    alpha:0x1];
            }
            completion:^(UIViewAnimatingPosition finalPosition) {
                recognizer.view.backgroundColor = backgroundColor;
            }];
        [animation startAnimation];
    }

    if (recognizer.state == UIGestureRecognizerStateEnded) {
        if (_delegate) {
            [_delegate doSelectAction];
        }
    }
}
// a delegate methods that set dependency of gesture recognizers.
- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRequireFailureOfGestureRecognizer:(nonnull UIGestureRecognizer *)otherGestureRecognizer
{
    // only execute longPressGesture when all other gesture recognizer fails
    return YES;
}
@end
