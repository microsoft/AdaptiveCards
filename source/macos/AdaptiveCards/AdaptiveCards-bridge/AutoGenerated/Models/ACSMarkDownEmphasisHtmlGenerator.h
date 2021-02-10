// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownEmphasisHtmlGenerator_IMPORTED
#define ACSMarkDownEmphasisHtmlGenerator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownHtmlGenerator.h"
using namespace AdaptiveCards;
#endif

#import "ACSMarkDownEmphasisHtmlGenerator.h"



#import "ACSMarkDownHtmlGenerator.h"
  

@class ACSMarkDownEmphasisHtmlGenerator;



@interface ACSMarkDownEmphasisHtmlGenerator : ACSMarkDownHtmlGenerator

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownEmphasisHtmlGenerator>)cppObj;
#endif

- (bool)isRightEmphasis;
- (bool)isLeftEmphasis;
- (bool)isLeftAndRightEmphasis;
- (void)pushItalicTag;
- (void)pushBoldTag;
- (bool)isMatch:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token;
- (bool)isSameType:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token;
- (bool)isDone;
- (NSNumber * _Nullable)getNumberOfUnusedDelimiters;
- (bool)generateTags:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token;
- (void)reverseDirectionType;
- (NSNumber * _Nullable)adjustEmphasisCounts:(NSNumber * _Nonnull)leftOver rightToken:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)rightToken;


@end
#endif
