// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMarkDownEmphasisHtmlGenerator.h"

//cpp includes


#import "ACSMarkDownEmphasisHtmlGenerator.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


@implementation  ACSMarkDownEmphasisHtmlGenerator {
    std::shared_ptr<MarkDownEmphasisHtmlGenerator> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownEmphasisHtmlGenerator>)cppObj
{
    if (self = [super initWithMarkDownHtmlGenerator: cppObj])
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

- (bool)isMatch:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token
{
    auto tokenCpp = // NEED TO INSERT CODE //;
 
    auto isMatchCpp = mCppObj->IsMatch(tokenCpp);
    return isMatchCpp;

}

- (bool)isSameType:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token
{
    auto tokenCpp = // NEED TO INSERT CODE //;
 
    auto isSameTypeCpp = mCppObj->IsSameType(tokenCpp);
    return isSameTypeCpp;

}

- (bool)isDone
{
 
    auto isDoneCpp = mCppObj->IsDone();
    return isDoneCpp;

}

- (NSNumber * _Nullable)getNumberOfUnusedDelimiters
{
 
    auto getNumberOfUnusedDelimitersCpp = mCppObj->GetNumberOfUnusedDelimiters();
    return [NSNumber numberWithInt:getNumberOfUnusedDelimitersCpp];

}

- (bool)generateTags:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token
{
    auto tokenCpp = // NEED TO INSERT CODE //;
 
    auto generateTagsCpp = mCppObj->GenerateTags(tokenCpp);
    return generateTagsCpp;

}

- (void)reverseDirectionType
{
 
    mCppObj->ReverseDirectionType();
    
}

- (NSNumber * _Nullable)adjustEmphasisCounts:(NSNumber * _Nonnull)leftOver rightToken:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)rightToken
{
    auto leftOverCpp = [leftOver intValue];
    auto rightTokenCpp = // NEED TO INSERT CODE //;
 
    auto adjustEmphasisCountsCpp = mCppObj->AdjustEmphasisCounts(leftOverCpp,rightTokenCpp);
    return [NSNumber numberWithInt:adjustEmphasisCountsCpp];

}


@end
