// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSAdaptiveCardParseWarning_IMPORTED
#define ACSAdaptiveCardParseWarning_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "AdaptiveCardParseWarning.h"
using namespace AdaptiveCards;
#endif

#import "ACSWarningStatusCode.h"



  


enum ACSWarningStatusCode: NSUInteger;


@interface ACSAdaptiveCardParseWarning : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithAdaptiveCardParseWarning:(const std::shared_ptr<AdaptiveCardParseWarning>)cppObj;
#endif

- (ACSWarningStatusCode)getStatusCode;
- (NSString * _Nullable)getReason;


@end
#endif
