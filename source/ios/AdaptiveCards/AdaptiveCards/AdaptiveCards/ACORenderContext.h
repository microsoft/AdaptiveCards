//
//  ACORenderContext
//  ACORenderContext.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOBaseActionElement.h"
#import "ACOBaseCardElement.h"
#import "ACOHostConfig.h"

@class ACOAdaptiveCard;

@interface ACORenderContext : NSObject

@property (readonly) ACRRtl rtl;
@property (readonly) BOOL hasSelectAction;
@property (readonly) BOOL allHasActionIcons;

@property (weak) ACOHostConfig *hostConfig;

- (instancetype)init:(ACOHostConfig *)config;

- (void)pushBaseCardElementContext:(ACOBaseCardElement *)element;
- (void)popBaseCardElementContext:(ACOBaseCardElement *)element;

- (void)pushBaseActionElementContext:(ACOBaseActionElement *)element;
- (void)popBaseActionElementContext:(ACOBaseActionElement *)element;

- (void)pushCardContext:(ACOAdaptiveCard *)card;
- (void)popCardContext:(ACOAdaptiveCard *)card;

@end
