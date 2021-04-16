// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSToggleInput.h"
#import "ToggleInput.h"


@implementation  ACSToggleInput {
    std::shared_ptr<ToggleInput> mCppObj;
}

- (instancetype _Nonnull)initWithToggleInput:(const std::shared_ptr<ToggleInput>)cppObj
{
    if (self = [super initWithBaseInputElement: cppObj])
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

- (NSString * _Nullable)getValue
{
 
    auto getValueCpp = mCppObj->GetValue();
    return [NSString stringWithUTF8String:getValueCpp.c_str()];

}

- (void)setValue:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetValue(valueCpp);
    
}

- (NSString * _Nullable)getValueOff
{
 
    auto getValueOffCpp = mCppObj->GetValueOff();
    return [NSString stringWithUTF8String:getValueOffCpp.c_str()];

}

- (void)setValueOff:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetValueOff(valueCpp);
    
}

- (NSString * _Nullable)getValueOn
{
 
    auto getValueOnCpp = mCppObj->GetValueOn();
    return [NSString stringWithUTF8String:getValueOnCpp.c_str()];

}

- (void)setValueOn:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetValueOn(valueCpp);
    
}

- (bool)getWrap
{
 
    auto getWrapCpp = mCppObj->GetWrap();
    return getWrapCpp;

}

- (void)setWrap:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetWrap(valueCpp);
    
}




@end
