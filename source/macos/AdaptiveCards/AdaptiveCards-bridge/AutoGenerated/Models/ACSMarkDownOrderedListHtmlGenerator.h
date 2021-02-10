// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownOrderedListHtmlGenerator_IMPORTED
#define ACSMarkDownOrderedListHtmlGenerator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownHtmlGenerator.h"
using namespace AdaptiveCards;
#endif

#import "ACSMarkDownBlockType.h"



#import "ACSMarkDownStringHtmlGenerator.h"
  


enum ACSMarkDownBlockType: NSUInteger;


@interface ACSMarkDownOrderedListHtmlGenerator : ACSMarkDownStringHtmlGenerator

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownOrderedListHtmlGenerator:(const std::shared_ptr<MarkDownOrderedListHtmlGenerator>)cppObj;
#endif

- (NSString * _Nullable)generateHtmlString;
- (ACSMarkDownBlockType)getBlockType;


@end
#endif
