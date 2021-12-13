//
//  ACRToolTip
//  ACRToolTip.m
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRToolTip.h"
#import <UIKit/UIKit.h>

#ifdef USEFLUENTUI
#import <FluentUI/FluentUI-Swift.h>
#endif

@implementation ACRToolTip

+ (void)showToolTip:(UILongPressGestureRecognizer *)recognizer toolTip:(NSString *)toolTip
{
#ifdef USEFLUENTUI
    if (recognizer.state == UIGestureRecognizerStateBegan && toolTip && recognizer.view) {
        [MSFTooltip.shared showWith:toolTip for:recognizer.view preferredArrowDirection:MSFTooltipArrowDirectionUp offset:CGPointZero screenMargins:MSFTooltip.defaultScreenMargins dismissOn:MSFTooltipDismissModeTapAnywhere onTap:nil];
    }
#endif
}

@end
