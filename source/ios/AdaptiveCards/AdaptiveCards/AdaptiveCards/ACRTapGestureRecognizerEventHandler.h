//
//  ACRTapGestureRecognizerEventHandler
//  ACRTapGestureRecognizerEventHandler.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol ACRSelectActionDelegate
- (void)doSelectAction;
@end

@interface ACRTapGestureRecognizerEventHandler : NSObject <UIGestureRecognizerDelegate>

@property (weak) id<ACRSelectActionDelegate> delegate;

// this method should be assigned when LongPressGesture is intiated with this object as target
// this method will be called when LongPressGesture is recognized
// 1. it provides users with cue that select action is about to be initiated
// 2. execute select action by calling its delegate
- (IBAction)processTapGesture:(UITapGestureRecognizer *)recognizer;

@end
