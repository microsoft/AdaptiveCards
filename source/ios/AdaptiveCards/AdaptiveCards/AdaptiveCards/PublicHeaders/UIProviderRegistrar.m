//
//  UIProviderRegistrar.m
//  AdaptiveCards
//
//  Created by Janus Balatbat on 12/8/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "UIProviderRegistrar.h"

@implementation UIProviderRegistrar

+ (instancetype)sharedInstance {
    static UIProviderRegistrar *sharedInstance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[UIProviderRegistrar alloc] init];
    });
    return sharedInstance;
}

- (void)registerTooltipProvider:(id<TooltipProviderProtocol>)provider {
    self.tooltipProvider = provider;
}

@end
