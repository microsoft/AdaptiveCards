//
//  ACRRegistartion
//  ACRRegistartion.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
//
@class ACRBaseCardElementRenderer;

#import "ACRBaseActionElementRenderer.h"
#import "ACOBaseCardElement.h"

@interface ACRRegistration:NSObject

+ (ACRRegistration *)getInstance;

- (ACRBaseCardElementRenderer *)getRenderer:(NSNumber *) cardElementType;

- (ACRBaseActionElementRenderer *)getActionRenderer:(NSNumber *) cardElementType;

- (id<ACRIBaseActionSetRenderer>)getActionSetRenderer;

- (void) setActionRenderer:(ACRBaseActionElementRenderer *)renderer cardElementType:(NSNumber *)cardElementType;

- (void) setBaseCardElementRenderer:(ACRBaseCardElementRenderer *)renderer cardElementType:(ACRCardElementType)cardElementType;

- (void) setActionSetRenderer:(id<ACRIBaseActionSetRenderer>)actionsetRenderer;

- (void) setCustomElementParser:(NSObject<ACOIBaseCardElementParser> *)customElementParser;

- (BOOL) isElementRendererOverriden:(ACRCardElementType)cardElementType;

- (BOOL) isActionRendererOverriden:(NSNumber *)cardElementType;

@end

@interface ACOFeatureRegistration:NSObject
+ (ACOFeatureRegistration *)getInstance;
- (void)addFeature:(nullable NSString *)featureName featureVersion:(nullable NSString *)version;
- (void)removeFeature:(nullable NSString *)featureName;
- (nonnull NSString *)getFeatureVersion:(nullable NSString *)featureName;
@end
