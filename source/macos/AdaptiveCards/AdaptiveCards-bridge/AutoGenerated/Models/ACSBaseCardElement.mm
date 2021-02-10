// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSCardElementTypeConvertor.h"
#import "ACSHeightTypeConvertor.h"
#import "ACSSpacingConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"


#import "ACSBaseCardElement.h"
#import "../../../../../shared/cpp/ObjectModel/BaseCardElement.h"


@implementation  ACSBaseCardElement {
    std::shared_ptr<BaseCardElement> mCppObj;
}

- (instancetype _Nonnull)initWithBaseCardElement:(const std::shared_ptr<BaseCardElement>)cppObj
{
    if (self = [super initWithBaseElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (bool)getSeparator
{
 
    auto getSeparatorCpp = mCppObj->GetSeparator();
    return getSeparatorCpp;

}

- (void)setSeparator:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetSeparator(valueCpp);
    
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

- (ACSSpacing)getSpacing
{
 
    auto getSpacingCpp = mCppObj->GetSpacing();
    return [ACSSpacingConvertor convertCpp:getSpacingCpp];

}

- (void)setSpacing:(enum ACSSpacing)value
{
    auto valueCpp = [ACSSpacingConvertor convertObj:value];
 
    mCppObj->SetSpacing(valueCpp);
    
}

- (bool)getIsVisible
{
 
    auto getIsVisibleCpp = mCppObj->GetIsVisible();
    return getIsVisibleCpp;

}

- (void)setIsVisible:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetIsVisible(valueCpp);
    
}

- (ACSCardElementType)getElementType
{
 
    auto getElementTypeCpp = mCppObj->GetElementType();
    return [ACSCardElementTypeConvertor convertCpp:getElementTypeCpp];

}




@end
