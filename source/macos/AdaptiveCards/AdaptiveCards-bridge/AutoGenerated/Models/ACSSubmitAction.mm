// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSAssociatedInputsConvertor.h"
// #import "ACSValue.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
#import "../../../../../shared/cpp/ObjectModel/json/json.h"


#import "ACSSubmitAction.h"
#import "../../../../../shared/cpp/ObjectModel/SubmitAction.h"


@implementation  ACSSubmitAction {
    std::shared_ptr<SubmitAction> mCppObj;
}

- (instancetype _Nonnull)initWithSubmitAction:(const std::shared_ptr<SubmitAction>)cppObj
{
    if (self = [super initWithBaseActionElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getDataJson
{
 
    auto getDataJsonCpp = mCppObj->GetDataJson();
    return [NSString stringWithUTF8String:getDataJsonCpp.c_str()];

}

- (void)setDataJson:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetDataJson(valueCpp);
    
}

- (ACSAssociatedInputs)getAssociatedInputs
{
 
    auto getAssociatedInputsCpp = mCppObj->GetAssociatedInputs();
    return [ACSAssociatedInputsConvertor convertCpp:getAssociatedInputsCpp];

}

- (void)setAssociatedInputs:(enum ACSAssociatedInputs)value
{
    auto valueCpp = [ACSAssociatedInputsConvertor convertObj:value];
 
    mCppObj->SetAssociatedInputs(valueCpp);
    
}




@end
