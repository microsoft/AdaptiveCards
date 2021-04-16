// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSActionTypeConvertor.h"
#import "ACSRemoteResourceInformationConvertor.h"

//cpp includes
#import "Enums.h"
#import "RemoteResourceInformation.h"


#import "ACSBaseActionElement.h"
#import "BaseActionElement.h"


@implementation  ACSBaseActionElement {
    std::shared_ptr<BaseActionElement> mCppObj;
}

- (instancetype _Nonnull)initWithBaseActionElement:(const std::shared_ptr<BaseActionElement>)cppObj
{
    if (self = [super initWithBaseElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getTitle
{
 
    auto getTitleCpp = mCppObj->GetTitle();
    return [NSString stringWithUTF8String:getTitleCpp.c_str()];

}

- (void)setTitle:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetTitle(valueCpp);
    
}

- (NSString * _Nullable)getIconUrl
{
 
    auto getIconUrlCpp = mCppObj->GetIconUrl();
    return [NSString stringWithUTF8String:getIconUrlCpp.c_str()];

}

- (void)setIconUrl:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetIconUrl(valueCpp);
    
}

- (NSString * _Nullable)getStyle
{
 
    auto getStyleCpp = mCppObj->GetStyle();
    return [NSString stringWithUTF8String:getStyleCpp.c_str()];

}

- (void)setStyle:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetStyle(valueCpp);
    
}

- (ACSActionType)getElementType
{
 
    auto getElementTypeCpp = mCppObj->GetElementType();
    return [ACSActionTypeConvertor convertCpp:getElementTypeCpp];

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
