// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSIsVisibleConvertor.h"

//cpp includes


#import "ACSToggleVisibilityTarget.h"
#import "ToggleVisibilityTarget.h"


@implementation  ACSToggleVisibilityTarget {
    std::shared_ptr<ToggleVisibilityTarget> mCppObj;
}

- (instancetype _Nonnull)initWithToggleVisibilityTarget:(const std::shared_ptr<ToggleVisibilityTarget>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getElementId
{
 
    auto getElementIdCpp = mCppObj->GetElementId();
    return [NSString stringWithUTF8String:getElementIdCpp.c_str()];

}

- (void)setElementId:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetElementId(valueCpp);
    
}

- (ACSIsVisible)getIsVisible
{
 
    auto getIsVisibleCpp = mCppObj->GetIsVisible();
    return [ACSIsVisibleConvertor convertCpp:getIsVisibleCpp];

}

- (void)setIsVisible:(enum ACSIsVisible)value
{
    auto valueCpp = [ACSIsVisibleConvertor convertObj:value];
 
    mCppObj->SetIsVisible(valueCpp);
    
}


@end
