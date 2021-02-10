// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSDateTimePreparsedToken_IMPORTED
#define ACSDateTimePreparsedToken_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "DateTimePreparsedToken.h"
using namespace AdaptiveCards;
#endif

#import "ACSDateTimePreparsedTokenFormat.h"



  


enum ACSDateTimePreparsedTokenFormat: NSUInteger;


@interface ACSDateTimePreparsedToken : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithDateTimePreparsedToken:(const std::shared_ptr<DateTimePreparsedToken>)cppObj;
#endif

- (NSString * _Nullable)getText;
- (ACSDateTimePreparsedTokenFormat)getFormat;
- (NSNumber * _Nullable)getDay;
- (NSNumber * _Nullable)getMonth;
- (NSNumber * _Nullable)getYear;


@end
#endif
