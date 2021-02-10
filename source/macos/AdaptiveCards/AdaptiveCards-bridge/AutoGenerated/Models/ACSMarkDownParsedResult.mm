// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel.j2

#import "SwiftInterfaceHeader.h"

#import "ACSMarkDownEmphasisHtmlGenerator.h"
#import "ACSMarkDownHtmlGenerator.h"
#import "ACSMarkDownParsedResult.h"
#import "ACSchar.h"

//cpp includes
#import "../../../../../shared/cpp/ObjectModel/MarkDownHtmlGenerator.h"


#import "ACSMarkDownParsedResult.h"
#import "../../../../../shared/cpp/ObjectModel/MarkDownParsedResult.h"


@implementation  ACSMarkDownParsedResult {
    std::shared_ptr<MarkDownParsedResult> mCppObj;
}

- (instancetype _Nonnull)initWithMarkDownParsedResult:(const std::shared_ptr<MarkDownParsedResult>)cppObj
{
    if (self = [super init])
    {
        mCppObj = cppObj;
    }
    return self;
}

- (void)translate
{
 
    mCppObj->Translate();
    
}

- (void)addBlockTags
{
 
    mCppObj->AddBlockTags();
    
}

- (NSString * _Nullable)generateHtmlString
{
 
    auto generateHtmlStringCpp = mCppObj->GenerateHtmlString();
    return [NSString stringWithUTF8String:generateHtmlStringCpp.c_str()];

}

- (void)appendParseResult:(ACSMarkDownParsedResult * _Nonnull)
{
//    auto Cpp = // NEED TO INSERT CODE //;
//
//    mCppObj->AppendParseResult(Cpp);
    
}

- (void)appendToTokens:(ACSMarkDownHtmlGenerator * _Nonnull)
{
//    auto Cpp = // NEED TO INSERT CODE //;
//
//    mCppObj->AppendToTokens(Cpp);
    
}

- (void)appendToLookUpTable:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)
{
//    auto Cpp = // NEED TO INSERT CODE //;
//
//    mCppObj->AppendToLookUpTable(Cpp);
    
}

- (void)addNewTokenToParsedResult:(NSNumber * _Nonnull)ch
{
    auto chCpp = [ch intValue];
 
    mCppObj->AddNewTokenToParsedResult(chCpp);
    
}

- (void)addNewTokenToParsedResult:(NSString * _Nonnull)word
{
    auto wordCpp = std::string([word UTF8String]);
 
    mCppObj->AddNewTokenToParsedResult(wordCpp);
    
}

- (void)addNewLineTokenToParsedResult:(ACSchar * _Nonnull)ch
{
    auto chCpp = std::string([ch UTF8String]);
 
    mCppObj->AddNewLineTokenToParsedResult(chCpp);
    
}

- (void)popFront
{
 
    mCppObj->PopFront();
    
}

- (void)popBack
{
 
    mCppObj->PopBack();
    
}

- (void)clear
{
 
    mCppObj->Clear();
    
}

- (bool)hasHtmlTags
{
 
    auto hasHtmlTagsCpp = mCppObj->HasHtmlTags();
    return hasHtmlTagsCpp;

}

- (void)foundHtmlTags
{
 
    mCppObj->FoundHtmlTags();
    
}

- (bool)getIsCaptured
{
 
    auto getIsCapturedCpp = mCppObj->GetIsCaptured();
    return getIsCapturedCpp;

}

- (void)setIsCaptured:(bool)val
{
    auto valCpp = val;
 
    mCppObj->SetIsCaptured(valCpp);
    
}

- (void)markTags:(ACSMarkDownHtmlGenerator * _Nonnull)
{
    auto Cpp = // NEED TO INSERT CODE //;
 
    mCppObj->MarkTags(Cpp);
    
}

- (void)matchLeftAndRightEmphasises
{
 
    mCppObj->MatchLeftAndRightEmphasises();
    
}


@end
