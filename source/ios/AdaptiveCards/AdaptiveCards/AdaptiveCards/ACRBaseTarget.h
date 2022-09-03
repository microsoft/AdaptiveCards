//
//  ACRBaseTarget
//  ACRBaseTarget.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
#import "ACOBaseActionElement.h"
#import "ACRTapGestureRecognizerEventHandler.h"
#else
#import <AdaptiveCards/ACOBaseActionElement.h>
#import <AdaptiveCards/ACRTapGestureRecognizerEventHandler.h>
#endif
#import <UIKit/UIKit.h>

@interface ACRBaseTarget : NSObject <ACRSelectActionDelegate>

- (void)addGestureRecognizer:(UIView *)view toolTipText:(NSString *)toolTipText;

- (void)setTooltip:(UIView *)view toolTipText:(NSString *)toolTipText;

- (void)showToolTip:(UILongPressGestureRecognizer *)gesture;

@end
