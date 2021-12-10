//
//  FluentTooltipProvider.m
//  AdaptiveCards
//
//  Created by Janus Balatbat on 12/8/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "FluentTooltipProvider.h"
#import <AdaptiveCards/UIProviderRegistrar.h>
#import <FluentUI/FluentUI-Swift.h>

@interface FluentTooltipProvider()<TooltipProviderProtocol>
@end

@implementation FluentTooltipProvider

+ (void)load
{
    FluentTooltipProvider *selfProvider = [[FluentTooltipProvider alloc] init];
    [[UIProviderRegistrar sharedInstance] setTooltipProvider:selfProvider];
}

- (void)showToolTipWithMessage:(NSString * _Nullable)message recognizer:(UILongPressGestureRecognizer * _Nullable)recognizer
{
    [MSFTooltip.shared showWith:message for:recognizer.view preferredArrowDirection:MSFTooltipArrowDirectionUp offset:CGPointZero screenMargins:MSFTooltip.defaultScreenMargins dismissOn:MSFTooltipDismissModeTapAnywhere onTap:nil];
}

@end
