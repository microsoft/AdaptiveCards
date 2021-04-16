// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSBackgroundImage.h"
#import "ACSBaseActionElement.h"
#import "ACSCardElementTypeConvertor.h"
#import "ACSContainerStyleConvertor.h"
#import "ACSFontTypesDefinitionConvertor.h"
#import "ACSHeightTypeConvertor.h"
#import "ACSInternalId.h"
#import "ACSRemoteResourceInformationConvertor.h"
#import "ACSVerticalContentAlignmentConvertor.h"

//cpp includes
#import "BackgroundImage.h"
#import "BaseActionElement.h"
#import "BaseElement.h"
#import "Enums.h"
#import "HostConfig.h"
#import "RemoteResourceInformation.h"


#import "ACSAdaptiveCard.h"
#import "SharedAdaptiveCard.h"


@implementation  ACSAdaptiveCard {
    std::shared_ptr<AdaptiveCard> mCppObj;
}

- (instancetype _Nonnull)initWithAdaptiveCard:(const std::shared_ptr<AdaptiveCard>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getVersion
{
 
    auto getVersionCpp = mCppObj->GetVersion();
    return [NSString stringWithUTF8String:getVersionCpp.c_str()];

}

- (void)setVersion:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetVersion(valueCpp);
    
}

- (NSString * _Nullable)getFallbackText
{
 
    auto getFallbackTextCpp = mCppObj->GetFallbackText();
    return [NSString stringWithUTF8String:getFallbackTextCpp.c_str()];

}

- (void)setFallbackText:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetFallbackText(valueCpp);
    
}

- (ACSBackgroundImage * _Nullable)getBackgroundImage
{
 
    auto getBackgroundImageCpp = mCppObj->GetBackgroundImage();
    if (getBackgroundImageCpp)
        return [[ACSBackgroundImage alloc] initWithBackgroundImage:getBackgroundImageCpp];
    return NULL;
}

- (void)setBackgroundImage:(ACSBackgroundImage * _Nonnull)value
{
//    auto valueCpp = // NEED TO INSERT CODE //;
// 
//    mCppObj->SetBackgroundImage(valueCpp);
    
}

- (NSString * _Nullable)getSpeak
{
 
    auto getSpeakCpp = mCppObj->GetSpeak();
    return [NSString stringWithUTF8String:getSpeakCpp.c_str()];

}

- (void)setSpeak:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetSpeak(valueCpp);
    
}

- (ACSContainerStyle)getStyle
{
 
    auto getStyleCpp = mCppObj->GetStyle();
    return [ACSContainerStyleConvertor convertCpp:getStyleCpp];

}

- (void)setStyle:(enum ACSContainerStyle)value
{
    auto valueCpp = [ACSContainerStyleConvertor convertObj:value];
 
    mCppObj->SetStyle(valueCpp);
    
}

- (NSString * _Nullable)getLanguage
{
 
    auto getLanguageCpp = mCppObj->GetLanguage();
    return [NSString stringWithUTF8String:getLanguageCpp.c_str()];

}

- (void)setLanguage:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetLanguage(valueCpp);
    
}

- (ACSVerticalContentAlignment)getVerticalContentAlignment
{
 
    auto getVerticalContentAlignmentCpp = mCppObj->GetVerticalContentAlignment();
    return [ACSVerticalContentAlignmentConvertor convertCpp:getVerticalContentAlignmentCpp];

}

- (void)setVerticalContentAlignment:(enum ACSVerticalContentAlignment)value
{
    auto valueCpp = [ACSVerticalContentAlignmentConvertor convertObj:value];
 
    mCppObj->SetVerticalContentAlignment(valueCpp);
    
}

- (ACSHeightType)getHeight
{
 
    auto getHeightCpp = mCppObj->GetHeight();
    return [ACSHeightTypeConvertor convertCpp:getHeightCpp];

}

- (void)setHeight:(enum ACSHeightType)value
{
    auto valueCpp = [ACSHeightTypeConvertor convertObj:value];
 
    mCppObj->SetHeight(valueCpp);
    
}

- (NSNumber * _Nullable)getMinHeight
{
 
    auto getMinHeightCpp = mCppObj->GetMinHeight();
    return [NSNumber numberWithUnsignedInt:getMinHeightCpp];

}

- (void)setMinHeight:(NSNumber * _Nonnull)value
{
    auto valueCpp = [value unsignedIntValue];
 
    mCppObj->SetMinHeight(valueCpp);
    
}

//- (ACSFontTypesDefinition * _Nullable)getFontTypes
//{
// 
//    auto getFontTypesCpp = mCppObj->GetFontTypes();
//    return [ACSFontTypesDefinitionConvertor convertCpp:getFontTypesCpp];
//
//}
//
//- (void)setFontTypes:(ACSFontTypesDefinition * _Nonnull)value
//{
//    auto valueCpp = [ACSFontTypesDefinitionConvertor convertObj:value];
// 
//    mCppObj->SetFontTypes(valueCpp);
//    
//}

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

- (NSArray<ACSBaseCardElement *> * _Nonnull)getBody
{
 
    auto getBodyCpp = mCppObj->GetBody();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getBodyCpp)
    {
        [objList addObject: [BridgeConverter convertFromBaseCardElement:item]];
    }
    return objList;


}


- (NSArray<ACSBaseActionElement *> * _Nonnull)getActions
{
 
    auto getActionsCpp = mCppObj->GetActions();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getActionsCpp)
    {
        [objList addObject: [BridgeConverter convertFromBaseActionElement:item]];
    }
    return objList;


}

- (NSArray<ACSRemoteResourceInformation *> * _Nonnull)getResourceInformation
{
 
    auto getResourceInformationCpp = mCppObj->GetResourceInformation();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getResourceInformationCpp)
    {
        [objList addObject: [ACSRemoteResourceInformationConvertor convertCpp:item]];
    }
    return objList;


}

- (ACSCardElementType)getElementType
{
 
    auto getElementTypeCpp = mCppObj->GetElementType();
    return [ACSCardElementTypeConvertor convertCpp:getElementTypeCpp];

}

- (ACSInternalId * _Nullable)getInternalId
{
 
    auto getInternalIdCpp = mCppObj->GetInternalId();
    return [[ACSInternalId alloc] initWithInternalId:std::make_shared<InternalId>(getInternalIdCpp)];

}


@end
