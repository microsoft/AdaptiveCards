//
//  UIProviderRegistrar.h
//  AdaptiveCards
//
//  Created by Janus Balatbat on 12/8/21.
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
@protocol TooltipProviderProtocol <NSObject>

- (void)showToolTipWithMessage:(NSString *_Nullable)message
                    recognizer:(UILongPressGestureRecognizer *_Nullable)recognizer;

@end

NS_ASSUME_NONNULL_BEGIN

@interface UIProviderRegistrar : NSObject

+ (instancetype)sharedInstance;

@property(nonatomic, strong) id<TooltipProviderProtocol> tooltipProvider;

@end

NS_ASSUME_NONNULL_END
