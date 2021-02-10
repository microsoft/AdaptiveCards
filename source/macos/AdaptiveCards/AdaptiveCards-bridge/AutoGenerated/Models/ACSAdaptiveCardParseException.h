// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSAdaptiveCardParseException_IMPORTED
#define ACSAdaptiveCardParseException_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "AdaptiveCardParseException.h"
using namespace AdaptiveCards;
#endif

#import "ACSErrorStatusCode.h"



  


enum ACSErrorStatusCode: NSUInteger;


@interface ACSAdaptiveCardParseException : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithAdaptiveCardParseException:(const std::shared_ptr<AdaptiveCardParseException>)cppObj;
#endif

- (NSString * _Nullable)what;
- (ACSErrorStatusCode)getStatusCode;
- (NSString * _Nullable)getReason;


@end
#endif
