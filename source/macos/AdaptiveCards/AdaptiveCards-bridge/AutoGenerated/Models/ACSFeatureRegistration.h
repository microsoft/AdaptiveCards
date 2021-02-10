// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSFeatureRegistration_IMPORTED
#define ACSFeatureRegistration_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "FeatureRegistration.h"
using namespace AdaptiveCards;
#endif

#import "ACSSemanticVersion.h"



  

@class ACSSemanticVersion;



@interface ACSFeatureRegistration : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithFeatureRegistration:(const std::shared_ptr<FeatureRegistration>)cppObj;
#endif

- (void)addFeature:(NSString * _Nonnull)featureName featureVersion:(NSString * _Nonnull)featureVersion;
- (void)removeFeature:(NSString * _Nonnull)featureName;
- (ACSSemanticVersion * _Nullable)getAdaptiveCardsVersion;
- (NSString * _Nullable)getFeatureVersion:(NSString * _Nonnull)featureName;


@end
#endif
