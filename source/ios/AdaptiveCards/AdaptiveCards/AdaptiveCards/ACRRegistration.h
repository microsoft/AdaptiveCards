//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//
@class ACRBaseCardElementRenderer;

#import "ACOBaseCardElement.h"
#import "ACRBaseActionElementRenderer.h"

@interface ACRRegistration : NSObject

+ (ACRRegistration *_Nonnull)getInstance;

- (ACRBaseCardElementRenderer *_Nullable)getRenderer:(NSNumber *_Nonnull)cardElementType;

- (ACRBaseActionElementRenderer *_Nullable)getActionRenderer:(NSNumber *_Nonnull)cardElementType;

- (id<ACRIBaseActionSetRenderer>_Nullable)getActionSetRenderer;

- (void)setActionRenderer:(ACRBaseActionElementRenderer *_Nullable)renderer cardElementType:(NSNumber *_Nonnull)cardElementType;

- (void)setBaseCardElementRenderer:(ACRBaseCardElementRenderer *_Nullable)renderer cardElementType:(ACRCardElementType)cardElementType;

- (void)setActionSetRenderer:(id<ACRIBaseActionSetRenderer>_Nullable)actionsetRenderer;

- (void)setCustomElementParser:(NSObject<ACOIBaseCardElementParser> *_Nonnull)customElementPars_Nonnuller key:(NSString *_Nonnull)key;
;

- (NSObject<ACOIBaseCardElementParser> *_Nullable)getCustomElementParser:(NSString *_Nonnull)key;

- (void)setCustomElementRenderer:(ACRBaseCardElementRenderer *_Nonnull)renderer key:(NSString *_Nonnull)key;

- (BOOL)isElementRendererOverridden:(ACRCardElementType)cardElementType;

- (BOOL)isActionRendererOverridden:(NSNumber *_Nonnull)cardElementType;

- (void)setCustomActionElementParser:(NSObject<ACOIBaseActionElementParser> *_Nonnull)parser key:(NSString *_Nonnull)key;

- (NSObject<ACOIBaseActionElementParser> *_Nullable)getCustomActionElementParser:(NSString *_Nonnull)key;

- (void)setCustomActionRenderer:(ACRBaseActionElementRenderer *_Nonnull)renderer key:(NSString *_Nonnull)key;

- (ACOParseContext *_Nonnull)getParseContext;

@end

@interface ACOFeatureRegistration : NSObject
+ (ACOFeatureRegistration *_Nonnull)getInstance;
- (void)addFeature:(nullable NSString *)featureName featureVersion:(nullable NSString *)version;
- (void)removeFeature:(nullable NSString *)featureName;
- (nonnull NSString *)getFeatureVersion:(nullable NSString *)featureName;
@end
