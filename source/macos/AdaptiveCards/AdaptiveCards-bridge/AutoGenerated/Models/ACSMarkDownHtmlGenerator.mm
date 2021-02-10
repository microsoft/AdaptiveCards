// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMarkDownBlockTypeConvertor.h"

//cpp includes


#import "ACSMarkDownHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownHtmlGenerator {
    std::shared_ptr<MarkDownHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownHtmlGenerator:(const std::shared_ptr<MarkDownHtmlGenerator>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (void)makeItHead
{
 
    mCppObj->MakeItHead();
    
}

- (void)makeItTail
{
 
    mCppObj->MakeItTail();
    
}

- (bool)isNewLine
{
 
    auto isNewLineCpp = mCppObj->IsNewLine();
    return isNewLineCpp;

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
