// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownParsedResult_IMPORTED
#define ACSMarkDownParsedResult_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownParsedResult.h"
using namespace AdaptiveCards;
#endif

#import "ACSMarkDownEmphasisHtmlGenerator.h"
#import "ACSMarkDownHtmlGenerator.h"
#import "ACSMarkDownParsedResult.h"



  

@class ACSMarkDownEmphasisHtmlGenerator;
@class ACSMarkDownHtmlGenerator;
@class ACSMarkDownParsedResult;
@class ACSchar;



@interface ACSMarkDownParsedResult : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownParsedResult:(const std::shared_ptr<MarkDownParsedResult>)cppObj;
#endif

- (void)translate;
- (void)addBlockTags;
- (NSString * _Nullable)generateHtmlString;
- (void)appendParseResult:(ACSMarkDownParsedResult * _Nonnull) mdParsedResult;
- (void)appendToTokens:(ACSMarkDownHtmlGenerator * _Nonnull) mdHtmlGenerator;
- (void)appendToLookUpTable:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull) mdEmphasisHtmlGenerator;
- (void)addNewTokenToParsedResult:(NSNumber * _Nonnull)ch;
- (void)addNewTokenToParsedResultString:(NSString * _Nonnull)word;
- (void)addNewLineTokenToParsedResult:(NSString * _Nonnull)ch;
- (void)popFront;
- (void)popBack;
- (void)clear;
- (bool)hasHtmlTags;
- (void)foundHtmlTags;
- (bool)getIsCaptured;
- (void)setIsCaptured:(bool)val;
- (void)markTags:(ACSMarkDownHtmlGenerator * _Nonnull)mdHtmlGenerator;
- (void)matchLeftAndRightEmphasises;


@end
#endif
