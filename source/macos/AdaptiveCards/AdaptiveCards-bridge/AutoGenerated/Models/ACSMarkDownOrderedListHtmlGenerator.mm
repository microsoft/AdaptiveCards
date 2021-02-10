// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMarkDownBlockTypeConvertor.h"

//cpp includes


#import "ACSMarkDownOrderedListHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownOrderedListHtmlGenerator {
    std::shared_ptr<MarkDownOrderedListHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownOrderedListHtmlGenerator:(const std::shared_ptr<MarkDownOrderedListHtmlGenerator>)cppObj
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
