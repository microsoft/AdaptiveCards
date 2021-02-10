// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownRightEmphasisHtmlGenerator_IMPORTED
#define ACSMarkDownRightEmphasisHtmlGenerator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownHtmlGenerator.h"
using namespace AdaptiveCards;
#endif

#import "ACSMarkDownEmphasisHtmlGenerator.h"



#import "ACSMarkDownEmphasisHtmlGenerator.h"
  

@class ACSMarkDownEmphasisHtmlGenerator;



@interface ACSMarkDownRightEmphasisHtmlGenerator : ACSMarkDownEmphasisHtmlGenerator

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownRightEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownRightEmphasisHtmlGenerator>)cppObj;
#endif

- (void)generateTags:(ACSMarkDownEmphasisHtmlGenerator * _Nonnull)token;
- (bool)isRightEmphasis;
- (NSString * _Nullable)generateHtmlString;
- (void)pushItalicTag;
- (void)pushBoldTag;


@end
#endif
