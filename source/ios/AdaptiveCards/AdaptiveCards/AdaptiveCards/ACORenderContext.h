//
//  ACORenderContext
//  ACORenderContext.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACOBaseActionElement.h"
#import "ACOBaseCardElement.h"
#import "ACOHostConfig.h"
#import "ACOVisibilityManager.h"
#import <Foundation/Foundation.h>

@class ACOAdaptiveCard;

@interface ACORenderContext : NSObject

@property (readonly) BOOL childHasSelectAction;
@property (readonly) ACRRtl rtl;
@property (readonly) BOOL hasSelectAction;
@property (readonly) BOOL allHasActionIcons;
@property (readonly) BOOL isFirstRowAsHeaders;
@property (readonly) ACRVerticalContentAlignment verticalContentAlignment;
@property (readonly) ACRHorizontalAlignment horizontalContentAlignment;
@property (readonly) ACRContainerStyle style;

@property (weak) ACOHostConfig *_Nullable hostConfig;

- (instancetype _Nullable)init:(ACOHostConfig *_Nonnull)config;

- (void)pushBaseCardElementContext:(ACOBaseCardElement *_Nullable)acoElement additionalProperty:(NSDictionary *_Nullable (^_Nullable)(void))additionalProperty;
- (void)pushBaseCardElementContext:(ACOBaseCardElement *_Nullable)element;
- (void)popBaseCardElementContext:(ACOBaseCardElement *_Nullable)element;

- (void)pushBaseActionElementContext:(ACOBaseActionElement *_Nullable)element;
- (void)popBaseActionElementContext:(ACOBaseActionElement *_Nullable)element;

- (void)pushCardContext:(ACOAdaptiveCard *_Nullable)card;
- (void)popCardContext:(ACOAdaptiveCard *_Nullable)card;

- (void)registerVisibilityManager:(NSObject<ACOIVisibilityManagerFacade> *_Nullable)manager targetViewTag:(NSUInteger)viewTag;
- (NSObject<ACOIVisibilityManagerFacade> *_Nullable)retrieveVisiblityManagerWithTag:(NSUInteger)viewTag;

@end
