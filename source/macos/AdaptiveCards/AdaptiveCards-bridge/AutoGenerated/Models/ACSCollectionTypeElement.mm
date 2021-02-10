// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSBackgroundImage.h"
#import "ACSBaseActionElement.h"
#import "ACSContainerBleedDirectionConvertor.h"
#import "ACSContainerStyleConvertor.h"
#import "ACSInternalId.h"
#import "ACSParseContext.h"
// #import "ACSValue.h"
#import "ACSVerticalContentAlignmentConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/BackgroundImage.h"
#import "../../../../../shared/cpp/ObjectModel/BaseActionElement.h"
#import "../../../../../shared/cpp/ObjectModel/BaseElement.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
#import "../../../../../shared/cpp/ObjectModel/json/json.h"
#import "../../../../../shared/cpp/ObjectModel/ParseContext.h"


#import "ACSCollectionTypeElement.h"
#import "../../../../../shared/cpp/ObjectModel/CollectionTypeElement.h"


@implementation  ACSCollectionTypeElement {
    std::shared_ptr<CollectionTypeElement> mCppObj;
}

- (instancetype _Nonnull)initWithCollectionTypeElement:(const std::shared_ptr<CollectionTypeElement>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
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

- (bool)getPadding
{
 
    auto getPaddingCpp = mCppObj->GetPadding();
    return getPaddingCpp;

}

- (void)setPadding:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetPadding(valueCpp);
    
}

- (bool)getBleed
{
 
    auto getBleedCpp = mCppObj->GetBleed();
    return getBleedCpp;

}

- (void)setBleed:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetBleed(valueCpp);
    
}

- (bool)getCanBleed
{
 
    auto getCanBleedCpp = mCppObj->GetCanBleed();
    return getCanBleedCpp;

}

- (ACSContainerBleedDirection)getBleedDirection
{
 
    auto getBleedDirectionCpp = mCppObj->GetBleedDirection();
    return [ACSContainerBleedDirectionConvertor convertCpp:getBleedDirectionCpp];

}

- (void)configForContainerStyle:(ACSParseContext * _Nonnull)context
{
//    auto contextCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->ConfigForContainerStyle(contextCpp);
    
}

- (void)setParentalId:(ACSInternalId * _Nonnull)id
{
//    auto idCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->SetParentalId(idCpp);
//
}

- (ACSInternalId * _Nullable)getParentalId
{
 
//    auto getParentalIdCpp = mCppObj->GetParentalId();
//    return [[ACSInternalId alloc] initWithInternalId:getParentalIdCpp];
    return [[ACSInternalId alloc] init];
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

- (ACSBackgroundImage * _Nullable)getBackgroundImage
{
 
    auto getBackgroundImageCpp = mCppObj->GetBackgroundImage();
    return [[ACSBackgroundImage alloc] initWithBackgroundImage:getBackgroundImageCpp];

}

- (void)setBackgroundImage:(ACSBackgroundImage * _Nonnull)value
{
//    auto valueCpp = // NEED TO INSERT CODE //;
//
//    mCppObj->SetBackgroundImage(valueCpp);
//
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


@end
