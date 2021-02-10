// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownLeftAndRightEmphasisHtmlGenerator_IMPORTED
#define ACSMarkDownLeftAndRightEmphasisHtmlGenerator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownHtmlGenerator.h"
using namespace AdaptiveCards;
#endif




#import "ACSMarkDownRightEmphasisHtmlGenerator.h"
  




@interface ACSMarkDownLeftAndRightEmphasisHtmlGenerator : ACSMarkDownRightEmphasisHtmlGenerator

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownLeftAndRightEmphasisHtmlGenerator:(const std::shared_ptr<MarkDownLeftAndRightEmphasisHtmlGenerator>)cppObj;
#endif

- (bool)isRightEmphasis;
- (bool)isLeftEmphasis;
- (bool)isLeftAndRightEmphasis;
- (void)pushItalicTag;
- (void)pushBoldTag;


@end
#endif
