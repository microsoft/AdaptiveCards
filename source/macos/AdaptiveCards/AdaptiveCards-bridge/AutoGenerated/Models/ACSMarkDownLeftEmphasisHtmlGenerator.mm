// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSMarkDownLeftEmphasisHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownLeftEmphasisHtmlGenerator {
    std::shared_ptr<MarkDownLeftEmphasisHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownLeftEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownLeftEmphasisHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownEmphasisHtmlGenerator: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (bool)isLeftEmphasis
{
 
    auto isLeftEmphasisCpp = mCppObj->IsLeftEmphasis();
    return isLeftEmphasisCpp;

}

- (NSString * _Nullable)generateHtmlString
{
 
    auto generateHtmlStringCpp = mCppObj->GenerateHtmlString();
    return [NSString stringWithUTF8String:generateHtmlStringCpp.c_str()];

}


@end
