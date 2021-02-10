// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSBaseElement.h"
#import "ACSFallbackTypeConvertor.h"
#import "ACSFeatureRegistration.h"
#import "ACSInternalId.h"
#import "ACSParseContext.h"
#import "ACSRemoteResourceInformationConvertor.h"
// #import "ACSValue.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
#import "../../../../../shared/cpp/ObjectModel/FeatureRegistration.h"
#import "../../../../../shared/cpp/ObjectModel/json/json.h"
#import "../../../../../shared/cpp/ObjectModel/ParseContext.h"
#import "../../../../../shared/cpp/ObjectModel/RemoteResourceInformation.h"


#import "ACSBaseElement.h"
#import "../../../../../shared/cpp/ObjectModel/BaseElement.h"


@implementation  ACSBaseElement {
    std::shared_ptr<BaseElement> mCppObj;
}

- (instancetype _Nonnull)initWithBaseElement:(const std::shared_ptr<BaseElement>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getElementTypeString
{
 
    auto getElementTypeStringCpp = mCppObj->GetElementTypeString();
    return [NSString stringWithUTF8String:getElementTypeStringCpp.c_str()];

}

- (void)setElementTypeString:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetElementTypeString(valueCpp);
    
}

- (NSString * _Nullable)getId
{
 
    auto getIdCpp = mCppObj->GetId();
    return [NSString stringWithUTF8String:getIdCpp.c_str()];

}

- (void)setId:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetId(valueCpp);
    
}

- (ACSInternalId * _Nullable)getInternalId
{
 
//    auto getInternalIdCpp = mCppObj->GetInternalId();
    return [[ACSInternalId alloc] init];

}

- (ACSFallbackType)getFallbackType
{
 
    auto getFallbackTypeCpp = mCppObj->GetFallbackType();
    return [ACSFallbackTypeConvertor convertCpp:getFallbackTypeCpp];

}

- (ACSBaseElement * _Nullable)getFallbackContent
{
 
    auto getFallbackContentCpp = mCppObj->GetFallbackContent();
    return [BridgeConverter convertFromBaseElement:getFallbackContentCpp];

}

- (bool)canFallbackToAncestor
{
 
    auto canFallbackToAncestorCpp = mCppObj->CanFallbackToAncestor();
    return canFallbackToAncestorCpp;

}

- (void)setFallbackType:(enum ACSFallbackType)type
{
    auto typeCpp = [ACSFallbackTypeConvertor convertObj:type];
 
    mCppObj->SetFallbackType(typeCpp);
    
}

- (void)setFallbackContent:(ACSBaseElement * _Nonnull)element
{
//    auto elementCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->SetFallbackContent(elementCpp);
    
}

- (bool)meetsRequirements:(ACSFeatureRegistration * _Nonnull)hostProvides
{
//    auto hostProvidesCpp = // NEED TO INSERT CODE //;
//
//    auto meetsRequirementsCpp = mCppObj->MeetsRequirements(hostProvidesCpp);
//    return meetsRequirementsCpp;
    return true;

}

- (NSString * _Nullable)getRequirements
{
 
    auto getRequirementsCpp = mCppObj->GetRequirements();
//    return [NSString stringWithUTF8String:getRequirementsCpp.c_str()];
    return @"Hello"; // Need to check

}


- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceUris
{
    std::vector<AdaptiveCards::RemoteResourceInformation> resourceUrisVector;
    for (id resourceUrisObj in resourceUris)
    {
        resourceUrisVector.push_back([ACSRemoteResourceInformationConvertor convertObj:resourceUrisObj]);
    }

 
    mCppObj->GetResourceInformation(resourceUrisVector);
    
}





@end
