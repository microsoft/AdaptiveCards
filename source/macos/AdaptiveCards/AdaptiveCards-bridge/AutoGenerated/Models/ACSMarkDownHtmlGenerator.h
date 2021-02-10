// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMarkDownHtmlGenerator_IMPORTED
#define ACSMarkDownHtmlGenerator_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MarkDownHtmlGenerator.h"
using namespace AdaptiveCards;
#endif

#import "ACSMarkDownBlockType.h"



  


enum ACSMarkDownBlockType: NSUInteger;


@interface ACSMarkDownHtmlGenerator : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMarkDownHtmlGenerator:(const std::shared_ptr<MarkDownHtmlGenerator>)cppObj;
#endif

- (void)makeItHead;
- (void)makeItTail;
- (bool)isNewLine;
- (NSString * _Nullable)generateHtmlString;
- (ACSMarkDownBlockType)getBlockType;


@end
#endif
