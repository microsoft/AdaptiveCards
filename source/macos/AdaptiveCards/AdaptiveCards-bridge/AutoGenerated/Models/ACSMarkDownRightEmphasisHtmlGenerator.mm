// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMarkDownEmphasisHtmlGenerator.h"

//cpp includes


#import "ACSMarkDownRightEmphasisHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownRightEmphasisHtmlGenerator {
    std::shared_ptr<MarkDownRightEmphasisHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownRightEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownRightEmphasisHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownEmphasisHtmlGenerator: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (void)generateTags:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token
{
//    auto tokenCpp = // NEED TO INSERT CODE //;
// 
//    mCppObj->GenerateTags(tokenCpp);
    
}

- (bool)isRightEmphasis
{
 
    auto isRightEmphasisCpp = mCppObj->IsRightEmphasis();
    return isRightEmphasisCpp;

}

- (NSString * _Nullable)generateHtmlString
{
 
    auto generateHtmlStringCpp = mCppObj->GenerateHtmlString();
    return [NSString stringWithUTF8String:generateHtmlStringCpp.c_str()];

}

- (void)pushItalicTag
{
 
    mCppObj->PushItalicTag();
    
}

- (void)pushBoldTag
{
 
    mCppObj->PushBoldTag();
    
}


@end
