// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSNumberInput.h"
#import "../../../../../shared/cpp/ObjectModel/NumberInput.h"


@implementation  ACSNumberInput {
    std::shared_ptr<NumberInput> mCppObj;
}

- (instancetype _Nonnull)initWithNumberInput:(const std::shared_ptr<NumberInput>)cppObj
{
    if (self = [super initWithBaseInputElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
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

- (NSNumber * _Nullable)getValue
{
 
    auto getValueCpp = mCppObj->GetValue();
    return getValueCpp.has_value() ? [NSNumber numberWithInt:getValueCpp.value_or(0)] : NULL;

}

- (void)setValue:(NSNumber * _Nullable)value
{
    auto valueCpp = [value intValue];
 
    mCppObj->SetValue(valueCpp);
    
}

- (NSNumber * _Nullable)getMax
{
 
    auto getMaxCpp = mCppObj->GetMax();
    return getMaxCpp.has_value() ? [NSNumber numberWithInt:getMaxCpp.value_or(0)] : NULL;

}

- (void)setMax:(NSNumber * _Nullable)value
{
    auto valueCpp = [value intValue];
 
    mCppObj->SetMax(valueCpp);
    
}

- (NSNumber * _Nullable)getMin
{
 
    auto getMinCpp = mCppObj->GetMin();
    return getMinCpp.has_value() ? [NSNumber numberWithInt:getMinCpp.value_or(0)] : NULL;

}

- (void)setMin:(NSNumber * _Nullable)value
{
    auto valueCpp = [value intValue];
 
    mCppObj->SetMin(valueCpp);
    
}




@end
