// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSBaseActionElement.h"
#import "ACSTextInputStyleConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/BaseActionElement.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"


#import "ACSTextInput.h"
#import "../../../../../shared/cpp/ObjectModel/TextInput.h"


@implementation  ACSTextInput {
    std::shared_ptr<TextInput> mCppObj;
}

- (instancetype _Nonnull)initWithTextInput:(const std::shared_ptr<TextInput>)cppObj
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

- (bool)getIsMultiline
{
 
    auto getIsMultilineCpp = mCppObj->GetIsMultiline();
    return getIsMultilineCpp;

}

- (void)setIsMultiline:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetIsMultiline(valueCpp);
    
}

- (NSNumber * _Nullable)getMaxLength
{
 
    auto getMaxLengthCpp = mCppObj->GetMaxLength();
    return [NSNumber numberWithUnsignedInt:getMaxLengthCpp];

}

- (void)setMaxLength:(NSNumber * _Nonnull)value
{
    auto valueCpp = [value unsignedIntValue];
 
    mCppObj->SetMaxLength(valueCpp);
    
}

- (ACSTextInputStyle)getTextInputStyle
{
 
    auto getTextInputStyleCpp = mCppObj->GetTextInputStyle();
    return [ACSTextInputStyleConvertor convertCpp:getTextInputStyleCpp];

}

- (void)setTextInputStyle:(enum ACSTextInputStyle)value
{
    auto valueCpp = [ACSTextInputStyleConvertor convertObj:value];
 
    mCppObj->SetTextInputStyle(valueCpp);
    
}

- (ACSBaseActionElement * _Nullable)getInlineAction
{
 
    auto getInlineActionCpp = mCppObj->GetInlineAction();
    return [BridgeConverter convertFromBaseActionElement:getInlineActionCpp];

}

- (void)setInlineAction:(ACSBaseActionElement * _Nonnull)action
{
//    auto actionCpp = // NEED TO INSERT CODE //;
// 
//    mCppObj->SetInlineAction(actionCpp);
    
}

- (NSString * _Nullable)getRegex
{
 
    auto getRegexCpp = mCppObj->GetRegex();
    return [NSString stringWithUTF8String:getRegexCpp.c_str()];

}

- (void)setRegex:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetRegex(valueCpp);
    
}




@end
