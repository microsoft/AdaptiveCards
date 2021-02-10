// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSSemanticVersion.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/SemanticVersion.h"


#import "ACSFeatureRegistration.h"
#import "../../../../../shared/cpp/ObjectModel/FeatureRegistration.h"


@implementation  ACSFeatureRegistration {
    std::shared_ptr<FeatureRegistration> mCppObj;
}

- (instancetype _Nonnull)initWithFeatureRegistration:(const std::shared_ptr<FeatureRegistration>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (void)addFeature:(NSString * _Nonnull)featureName featureVersion:(NSString * _Nonnull)featureVersion
{
    auto featureNameCpp = std::string([featureName UTF8String]);
    auto featureVersionCpp = std::string([featureVersion UTF8String]);
 
    mCppObj->AddFeature(featureNameCpp,featureVersionCpp);
    
}

- (void)removeFeature:(NSString * _Nonnull)featureName
{
    auto featureNameCpp = std::string([featureName UTF8String]);
 
    mCppObj->RemoveFeature(featureNameCpp);
    
}

- (ACSSemanticVersion * _Nullable)getAdaptiveCardsVersion
{
 
    auto getAdaptiveCardsVersionCpp = mCppObj->GetAdaptiveCardsVersion();
    return [[ACSSemanticVersion alloc] initWithSemanticVersion:std::make_shared<SemanticVersion>(getAdaptiveCardsVersionCpp)];

}

- (NSString * _Nullable)getFeatureVersion:(NSString * _Nonnull)featureName
{
    auto featureNameCpp = std::string([featureName UTF8String]);
 
    auto getFeatureVersionCpp = mCppObj->GetFeatureVersion(featureNameCpp);
    return [NSString stringWithUTF8String:getFeatureVersionCpp.c_str()];

}


@end
