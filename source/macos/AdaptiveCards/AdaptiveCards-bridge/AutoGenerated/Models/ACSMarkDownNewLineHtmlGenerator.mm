// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSMarkDownNewLineHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownNewLineHtmlGenerator {
    std::shared_ptr<MarkDownNewLineHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownNewLineHtmlGenerator:(const std::shared_ptr<MarkDownNewLineHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownStringHtmlGenerator: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (bool)isNewLine
{
 
    auto isNewLineCpp = mCppObj->IsNewLine();
    return isNewLineCpp;

}


@end
