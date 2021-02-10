// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSBaseActionElement.h"
#import "ACSHorizontalAlignmentConvertor.h"
#import "ACSImageSizeConvertor.h"
#import "ACSImageStyleConvertor.h"
#import "ACSRemoteResourceInformationConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/BaseActionElement.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
#import "../../../../../shared/cpp/ObjectModel/RemoteResourceInformation.h"


#import "ACSImage.h"
#import "../../../../../shared/cpp/ObjectModel/Image.h"


@implementation  ACSImage {
    std::shared_ptr<Image> mCppObj;
}

- (instancetype _Nonnull)initWithImage:(const std::shared_ptr<Image>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getUrl
{
 
    auto getUrlCpp = mCppObj->GetUrl();
    return [NSString stringWithUTF8String:getUrlCpp.c_str()];

}

- (void)setUrl:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetUrl(valueCpp);
    
}

- (NSString * _Nullable)getBackgroundColor
{
 
    auto getBackgroundColorCpp = mCppObj->GetBackgroundColor();
    return [NSString stringWithUTF8String:getBackgroundColorCpp.c_str()];

}

- (void)setBackgroundColor:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetBackgroundColor(valueCpp);
    
}

- (ACSImageStyle)getImageStyle
{
 
    auto getImageStyleCpp = mCppObj->GetImageStyle();
    return [ACSImageStyleConvertor convertCpp:getImageStyleCpp];

}

- (void)setImageStyle:(enum ACSImageStyle)value
{
    auto valueCpp = [ACSImageStyleConvertor convertObj:value];
 
    mCppObj->SetImageStyle(valueCpp);
    
}

- (ACSImageSize)getImageSize
{
 
    auto getImageSizeCpp = mCppObj->GetImageSize();
    return [ACSImageSizeConvertor convertCpp:getImageSizeCpp];

}

- (void)setImageSize:(enum ACSImageSize)value
{
    auto valueCpp = [ACSImageSizeConvertor convertObj:value];
 
    mCppObj->SetImageSize(valueCpp);
    
}

- (NSString * _Nullable)getAltText
{
 
    auto getAltTextCpp = mCppObj->GetAltText();
    return [NSString stringWithUTF8String:getAltTextCpp.c_str()];

}

- (void)setAltText:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetAltText(valueCpp);
    
}

- (ACSHorizontalAlignment)getHorizontalAlignment
{
 
    auto getHorizontalAlignmentCpp = mCppObj->GetHorizontalAlignment();
    return [ACSHorizontalAlignmentConvertor convertCpp:getHorizontalAlignmentCpp];

}

- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value
{
    auto valueCpp = [ACSHorizontalAlignmentConvertor convertObj:value];
 
    mCppObj->SetHorizontalAlignment(valueCpp);
    
}

- (ACSBaseActionElement * _Nullable)getSelectAction
{
 
    auto getSelectActionCpp = mCppObj->GetSelectAction();
    return [BridgeConverter convertFromBaseActionElement:getSelectActionCpp];

}

- (void)setSelectAction:(ACSBaseActionElement * _Nonnull)action
{
//    auto actionCpp = // NEED TO INSERT CODE //;
// 
//    mCppObj->SetSelectAction(actionCpp);
    
}

- (NSNumber * _Nullable)getPixelWidth
{
 
    auto getPixelWidthCpp = mCppObj->GetPixelWidth();
    return [NSNumber numberWithUnsignedInt:getPixelWidthCpp];

}

- (void)setPixelWidth:(NSNumber * _Nonnull)value
{
    auto valueCpp = [value unsignedIntValue];
 
    mCppObj->SetPixelWidth(valueCpp);
    
}

- (NSNumber * _Nullable)getPixelHeight
{
 
    auto getPixelHeightCpp = mCppObj->GetPixelHeight();
    return [NSNumber numberWithUnsignedInt:getPixelHeightCpp];

}

- (void)setPixelHeight:(NSNumber * _Nonnull)value
{
    auto valueCpp = [value unsignedIntValue];
 
    mCppObj->SetPixelHeight(valueCpp);
    
}

- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo
{
    std::vector<AdaptiveCards::RemoteResourceInformation> resourceInfoVector;
    for (id resourceInfoObj in resourceInfo)
    {
        resourceInfoVector.push_back([ACSRemoteResourceInformationConvertor convertObj:resourceInfoObj]);
    }

 
    mCppObj->GetResourceInformation(resourceInfoVector);
    
}




@end
