//
//  ACRBaseTarget
//  ACRBaseTarget.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRBaseTarget.h"
#import <FluentUI/FluentUI-Swift.h>
#import <UIKit/UIKit.h>

@implementation ACRBaseTarget {
    NSString *_toolTip;
}

- (void)doSelectAction
{
}

- (void)addGestureRecognizer:(UIView *)view toolTipText:(NSString *)toolTipText
{
    if (view && toolTipText && toolTipText.length) {
        [self setTooltip:view toolTipText:toolTipText];
        UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(showToolTip:)];
        [view addGestureRecognizer:longPress];
    }
}

- (void)setTooltip:(UIView *)view toolTipText:(NSString *)toolTipText
{
    if (view && toolTipText) {
        _toolTip = toolTipText;
    }
}

- (void)showToolTip:(UILongPressGestureRecognizer *)recognizer
{
    if (recognizer.state == UIGestureRecognizerStateBegan && _toolTip && recognizer.view) {
        [MSFTooltip.shared showWith:_toolTip for:recognizer.view preferredArrowDirection:MSFTooltipArrowDirectionUp offset:CGPointZero screenMargins:MSFTooltip.defaultScreenMargins dismissOn:MSFTooltipDismissModeTapAnywhere onTap:nil];
    }
}

@end
