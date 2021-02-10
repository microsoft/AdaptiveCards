// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"


//cpp includes


#import "ACSMarkDownLeftAndRightEmphasisHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownLeftAndRightEmphasisHtmlGenerator {
    std::shared_ptr<MarkDownLeftAndRightEmphasisHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownLeftAndRightEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownLeftAndRightEmphasisHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownRightEmphasisHtmlGenerator: cppObj])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (bool)isRightEmphasis
{
 
    auto isRightEmphasisCpp = mCppObj->IsRightEmphasis();
    return isRightEmphasisCpp;

}

- (bool)isLeftEmphasis
{
 
    auto isLeftEmphasisCpp = mCppObj->IsLeftEmphasis();
    return isLeftEmphasisCpp;

}

- (bool)isLeftAndRightEmphasis
{
 
    auto isLeftAndRightEmphasisCpp = mCppObj->IsLeftAndRightEmphasis();
    return isLeftAndRightEmphasisCpp;

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
