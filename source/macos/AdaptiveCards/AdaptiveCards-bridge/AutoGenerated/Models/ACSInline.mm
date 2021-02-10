// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSInlineElementTypeConvertor.h"
// #import "ACSValue.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/Enums.h"
#import "../../../../../shared/cpp/ObjectModel/json/json.h"


#import "ACSInline.h"
#import "../../../../../shared/cpp/ObjectModel/Inline.h"


@implementation  ACSInline {
    std::shared_ptr<Inline> mCppObj;
}

- (instancetype _Nonnull)initWithInline:(const std::shared_ptr<Inline>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (ACSInlineElementType)getInlineType
{
 
    auto getInlineTypeCpp = mCppObj->GetInlineType();
    return [ACSInlineElementTypeConvertor convertCpp:getInlineTypeCpp];

}

- (NSString * _Nullable)getInlineTypeString
{
 
    auto getInlineTypeStringCpp = mCppObj->GetInlineTypeString();
    return [NSString stringWithUTF8String:getInlineTypeStringCpp.c_str()];

}




@end
