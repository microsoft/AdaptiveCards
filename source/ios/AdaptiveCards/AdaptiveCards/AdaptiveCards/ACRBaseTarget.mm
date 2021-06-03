//
//  ACRBaseTarget
//  ACRBaseTarget.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRBaseTarget.h"
#import <FluentUI/FluentUI-Swift.h>
#import <UIKit/UIKit.h>

@implementation ACRBaseTarget

- (void)doSelectAction
{
}

- (void)showToolTip:(UIView *)anchorView
{
    [MSFTooltip.shared showWith:@"Hello World!" for:anchorView preferredArrowDirection:MSFTooltipArrowDirectionDown offset:CGPointMake(0.0, 0.0) screenMargins:MSFTooltip.defaultScreenMargins dismissOn:MSFTooltipDismissModeTapAnywhere onTap:nil];
}


@end
