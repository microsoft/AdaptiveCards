// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSChoiceInput.h"
#import "ACSChoiceSetStyleConvertor.h"

//cpp includes
#import "ChoiceInput.h"
#import "Enums.h"


#import "ACSChoiceSetInput.h"
#import "ChoiceSetInput.h"


@implementation  ACSChoiceSetInput {
    std::shared_ptr<ChoiceSetInput> mCppObj;
}

- (instancetype _Nonnull)initWithChoiceSetInput:(const std::shared_ptr<ChoiceSetInput>)cppObj
{
    if (self = [super initWithBaseInputElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (bool)getIsMultiSelect
{
 
    auto getIsMultiSelectCpp = mCppObj->GetIsMultiSelect();
    return getIsMultiSelectCpp;

}

- (void)setIsMultiSelect:(bool)isMultiSelect
{
    auto isMultiSelectCpp = isMultiSelect;
 
    mCppObj->SetIsMultiSelect(isMultiSelectCpp);
    
}

- (ACSChoiceSetStyle)getChoiceSetStyle
{
 
    auto getChoiceSetStyleCpp = mCppObj->GetChoiceSetStyle();
    return [ACSChoiceSetStyleConvertor convertCpp:getChoiceSetStyleCpp];

}

- (void)setChoiceSetStyle:(enum ACSChoiceSetStyle)choiceSetStyle
{
    auto choiceSetStyleCpp = [ACSChoiceSetStyleConvertor convertObj:choiceSetStyle];
 
    mCppObj->SetChoiceSetStyle(choiceSetStyleCpp);
    
}

- (NSArray<ACSChoiceInput *> * _Nonnull)getChoices
{
 
    auto getChoicesCpp = mCppObj->GetChoices();
    NSMutableArray*  objList = [NSMutableArray new];
    for (const auto& item: getChoicesCpp)
    {
        [objList addObject: [[ACSChoiceInput alloc] initWithChoiceInput:item]];
    }
    return objList;


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




@end
