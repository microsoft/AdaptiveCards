// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSBaseInputElement.h"
#import "BaseInputElement.h"


@implementation  ACSBaseInputElement {
    std::shared_ptr<BaseInputElement> mCppObj;
}

- (instancetype _Nonnull)initWithBaseInputElement:(const std::shared_ptr<BaseInputElement>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getLabel
{
 
    auto getLabelCpp = mCppObj->GetLabel();
    return [NSString stringWithUTF8String:getLabelCpp.c_str()];

}

- (void)setLabel:(NSString * _Nonnull)label
{
    auto labelCpp = std::string([label UTF8String]);
 
    mCppObj->SetLabel(labelCpp);
    
}

- (bool)getIsRequired
{
 
    auto getIsRequiredCpp = mCppObj->GetIsRequired();
    return getIsRequiredCpp;

}

- (void)setIsRequired:(bool)isRequired
{
    auto isRequiredCpp = isRequired;
 
    mCppObj->SetIsRequired(isRequiredCpp);
    
}

- (NSString * _Nullable)getErrorMessage
{
 
    auto getErrorMessageCpp = mCppObj->GetErrorMessage();
    return [NSString stringWithUTF8String:getErrorMessageCpp.c_str()];

}

- (void)setErrorMessage:(NSString * _Nonnull)errorMessage
{
    auto errorMessageCpp = std::string([errorMessage UTF8String]);
 
    mCppObj->SetErrorMessage(errorMessageCpp);
    
}




@end
