// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSDateTimePreparser.h"
#import "ACSFontTypeConvertor.h"
#import "ACSForegroundColorConvertor.h"
#import "ACSHorizontalAlignmentConvertor.h"
#import "ACSTextSizeConvertor.h"
#import "ACSTextWeightConvertor.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/DateTimePreparser.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"


#import "ACSTextBlock.h"
#import "../../../../../shared/cpp/ObjectModel/TextBlock.h"


@implementation  ACSTextBlock {
    std::shared_ptr<TextBlock> mCppObj;
}

- (instancetype _Nonnull)initWithTextBlock:(const std::shared_ptr<TextBlock>)cppObj
{
    if (self = [super initWithBaseCardElement: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)getText
{
 
    auto getTextCpp = mCppObj->GetText();
    return [NSString stringWithUTF8String:getTextCpp.c_str()];

}

- (void)setText:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetText(valueCpp);
    
}

- (ACSDateTimePreparser * _Nullable)getTextForDateParsing
{
 
    auto getTextForDateParsingCpp = mCppObj->GetTextForDateParsing();
    return [[ACSDateTimePreparser alloc] init];

}

- (ACSTextSize)getTextSize
{
 
    auto getTextSizeCpp = mCppObj->GetTextSize();
    return [ACSTextSizeConvertor convertCpp:getTextSizeCpp];

}

- (void)setTextSize:(enum ACSTextSize)value
{
    auto valueCpp = [ACSTextSizeConvertor convertObj:value];
 
    mCppObj->SetTextSize(valueCpp);
    
}

- (ACSTextWeight)getTextWeight
{
 
    auto getTextWeightCpp = mCppObj->GetTextWeight();
    return [ACSTextWeightConvertor convertCpp:getTextWeightCpp];

}

- (void)setTextWeight:(enum ACSTextWeight)value
{
    auto valueCpp = [ACSTextWeightConvertor convertObj:value];
 
    mCppObj->SetTextWeight(valueCpp);
    
}

- (ACSFontType)getFontType
{
 
    auto getFontTypeCpp = mCppObj->GetFontType();
    return [ACSFontTypeConvertor convertCpp:getFontTypeCpp];

}

- (void)setFontType:(enum ACSFontType)value
{
    auto valueCpp = [ACSFontTypeConvertor convertObj:value];
 
    mCppObj->SetFontType(valueCpp);
    
}

- (ACSForegroundColor)getTextColor
{
 
    auto getTextColorCpp = mCppObj->GetTextColor();
    return [ACSForegroundColorConvertor convertCpp:getTextColorCpp];

}

- (void)setTextColor:(enum ACSForegroundColor)value
{
    auto valueCpp = [ACSForegroundColorConvertor convertObj:value];
 
    mCppObj->SetTextColor(valueCpp);
    
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

- (bool)getIsSubtle
{
 
    auto getIsSubtleCpp = mCppObj->GetIsSubtle();
    return getIsSubtleCpp;

}

- (void)setIsSubtle:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetIsSubtle(valueCpp);
    
}

- (NSNumber * _Nullable)getMaxLines
{
 
    auto getMaxLinesCpp = mCppObj->GetMaxLines();
    return [NSNumber numberWithUnsignedInt:getMaxLinesCpp];

}

- (void)setMaxLines:(NSNumber * _Nonnull)value
{
    auto valueCpp = [value unsignedIntValue];
 
    mCppObj->SetMaxLines(valueCpp);
    
}

- (ACSHorizontalAlignment)getHorizontalAlignment
{
 
    auto getHorizontalAlignmentCpp = mCppObj->GetHorizontalAlignment();
    return [ACSHorizontalAlignmentConvertor convertCpp:getHorizontalAlignmentCpp];

}

- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value
{
    auto valueCpp = [ACSHorizontalAlignmentConvertor convertObj:value];
 
    mCppObj->SetHorizontalAlignment(valueCpp);
    
}

- (void)setLanguage:(NSString * _Nonnull)value
{
    auto valueCpp = std::string([value UTF8String]);
 
    mCppObj->SetLanguage(valueCpp);
    
}

- (NSString * _Nullable)getLanguage
{
 
    auto getLanguageCpp = mCppObj->GetLanguage();
    return [NSString stringWithUTF8String:getLanguageCpp.c_str()];

}




@end
