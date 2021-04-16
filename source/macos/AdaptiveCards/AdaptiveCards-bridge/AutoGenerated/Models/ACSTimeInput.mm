// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSTimeInput.h"
#import "TimeInput.h"


@implementation  ACSTimeInput {
    std::shared_ptr<TimeInput> mCppObj;
}

- (instancetype _Nonnull)initWithTimeInput:(const std::shared_ptr<TimeInput>)cppObj
{
    if (self = [super initWithBaseInputElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getMax
{
 
    auto getMaxCpp = mCppObj->GetMax();
    return [NSString stringWithUTF8String:getMaxCpp.c_str()];

}

- (void)setMax:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetMax(valueCpp);
    
}

- (NSString * _Nullable)getMin
{
 
    auto getMinCpp = mCppObj->GetMin();
    return [NSString stringWithUTF8String:getMinCpp.c_str()];

}

- (void)setMin:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetMin(valueCpp);
    
}

- (NSString * _Nullable)getPlaceholder
{
 
    auto getPlaceholderCpp = mCppObj->GetPlaceholder();
    return [NSString stringWithUTF8String:getPlaceholderCpp.c_str()];

}

- (void)setPlaceholder:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetPlaceholder(valueCpp);
    
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




@end
