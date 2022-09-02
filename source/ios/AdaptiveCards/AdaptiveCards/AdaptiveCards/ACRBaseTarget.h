//
//  ACRBaseTarget
//  ACRBaseTarget.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseActionElement.h>
#import <AdaptiveCards/ACRTapGestureRecognizerEventHandler.h>
#import <UIKit/UIKit.h>

@interface ACRBaseTarget : NSObject <ACRSelectActionDelegate>

- (void)addGestureRecognizer:(UIView *)view toolTipText:(NSString *)toolTipText;

- (void)setTooltip:(UIView *)view toolTipText:(NSString *)toolTipText;

- (void)showToolTip:(UILongPressGestureRecognizer *)gesture;

@end
