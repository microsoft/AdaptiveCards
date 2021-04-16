// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSChoiceInput.h"
#import "ChoiceInput.h"


@implementation  ACSChoiceInput {
    std::shared_ptr<ChoiceInput> mCppObj;
}

- (instancetype _Nonnull)initWithChoiceInput:(const std::shared_ptr<ChoiceInput>)cppObj
{
    if (self = [super init])
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


@end
