// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownListHtmlGenerator_IMPORTED
#define ACSMarkDownListHtmlGenerator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownHtmlGenerator.h"
using namespace AdaptiveCards;
#endif

#import "ACSMarkDownBlockType.h"



#import "ACSMarkDownStringHtmlGenerator.h"
  


enum ACSMarkDownBlockType: NSUInteger;


@interface ACSMarkDownListHtmlGenerator : ACSMarkDownStringHtmlGenerator

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownListHtmlGenerator:(const std::shared_ptr<MarkDownListHtmlGenerator>)cppObj;
#endif

- (NSString * _Nullable)generateHtmlString;
- (ACSMarkDownBlockType)getBlockType;


@end
#endif
