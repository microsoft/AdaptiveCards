//
//  ACRBaseTarget
//  ACRBaseTarget.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseActionElement.h"
#import "ACRTapGestureRecognizerEventHandler.h"
#import <UIKit/UIKit.h>

@interface ACRBaseTarget : NSObject <ACRSelectActionDelegate>

- (void)addGestureRecognizer:(UIView *)view tooTipText:(NSString *)toolTipText;

- (void)setTooltip:(UIView *)view tooTipText:(NSString *)toolTipText;

- (void)showToolTip:(UILongPressGestureRecognizer *)gesture;

@end
