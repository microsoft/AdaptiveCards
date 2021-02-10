// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSParseContext.h"
// #import "ACSValue.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/json/json.h"
#import "../../../../../shared/cpp/ObjectModel/ParseContext.h"


#import "ACSRichTextElementProperties.h"
#import "../../../../../shared/cpp/ObjectModel/RichTextElementProperties.h"


@implementation  ACSRichTextElementProperties {
    std::shared_ptr<RichTextElementProperties> mCppObj;
}

- (instancetype _Nonnull)initWithRichTextElementProperties:(const std::shared_ptr<RichTextElementProperties>)cppObj
{
    if (self = [super initWithTextElementProperties: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (bool)getItalic
{
 
    auto getItalicCpp = mCppObj->GetItalic();
    return getItalicCpp;

}

- (void)setItalic:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetItalic(valueCpp);
    
}

- (bool)getStrikethrough
{
 
    auto getStrikethroughCpp = mCppObj->GetStrikethrough();
    return getStrikethroughCpp;

}

- (void)setStrikethrough:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetStrikethrough(valueCpp);
    
}

- (bool)getUnderline
{
 
    auto getUnderlineCpp = mCppObj->GetUnderline();
    return getUnderlineCpp;

}

- (void)setUnderline:(bool)value
{
    auto valueCpp = value;
 
    mCppObj->SetUnderline(valueCpp);
    
}


@end
