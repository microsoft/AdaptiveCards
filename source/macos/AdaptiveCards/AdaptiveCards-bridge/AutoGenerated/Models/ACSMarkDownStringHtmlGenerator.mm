// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSMarkDownStringHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownStringHtmlGenerator {
    std::shared_ptr<MarkDownStringHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownStringHtmlGenerator:(const std::shared_ptr<MarkDownStringHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownHtmlGenerator: cppObj])
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


@end
