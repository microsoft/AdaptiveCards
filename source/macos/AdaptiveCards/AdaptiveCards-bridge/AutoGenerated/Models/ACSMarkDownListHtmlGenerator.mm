// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMarkDownBlockTypeConvertor.h"

//cpp includes


#import "ACSMarkDownListHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownListHtmlGenerator {
    std::shared_ptr<MarkDownListHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownListHtmlGenerator:(const std::shared_ptr<MarkDownListHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownStringHtmlGenerator: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (NSString * _Nullable)generateHtmlString
{
 
    auto generateHtmlStringCpp = mCppObj->GenerateHtmlString();
    return [NSString stringWithUTF8String:generateHtmlStringCpp.c_str()];

}

- (ACSMarkDownBlockType)getBlockType
{
 
    auto getBlockTypeCpp = mCppObj->GetBlockType();
    return [ACSMarkDownBlockTypeConvertor convertCpp:getBlockTypeCpp];

}


@end
