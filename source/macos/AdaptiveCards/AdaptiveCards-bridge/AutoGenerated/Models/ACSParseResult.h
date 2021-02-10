// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSParseResult_IMPORTED
#define ACSParseResult_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ParseResult.h"
using namespace AdaptiveCards;
#endif

#import "ACSAdaptiveCard.h"
#import "ACSAdaptiveCardParseWarning.h"



  

@class ACSAdaptiveCard;
@class ACSAdaptiveCardParseWarning;



@interface ACSParseResult : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithParseResult:(const std::shared_ptr<ParseResult>)cppObj;
#endif

- (ACSAdaptiveCard * _Nullable)getAdaptiveCard;
- (NSArray<ACSAdaptiveCardParseWarning *> * _Nonnull)getWarnings;


@end
#endif
