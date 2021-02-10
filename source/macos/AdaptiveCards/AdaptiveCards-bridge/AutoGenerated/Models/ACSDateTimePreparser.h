// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSDateTimePreparser_IMPORTED
#define ACSDateTimePreparser_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "DateTimePreparser.h"
using namespace AdaptiveCards;
#endif

#import "ACSDateTimePreparsedToken.h"
#import "ACSDateTimePreparsedTokenFormat.h"



  

@class ACSDateTimePreparsedToken;
@class ACStm;

enum ACSDateTimePreparsedTokenFormat: NSUInteger;


@interface ACSDateTimePreparser : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithDateTimePreparser:(const std::shared_ptr<DateTimePreparser>)cppObj;
#endif

- (NSArray<ACSDateTimePreparsedToken *> * _Nonnull)getTextTokens;
- (bool)hasDateTokens;


@end
#endif
