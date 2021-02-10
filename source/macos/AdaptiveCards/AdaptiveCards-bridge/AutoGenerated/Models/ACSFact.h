// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSFact_IMPORTED
#define ACSFact_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "Fact.h"
using namespace AdaptiveCards;
#endif

#import "ACSDateTimePreparser.h"



  

@class ACSDateTimePreparser;



@interface ACSFact : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithFact:(const std::shared_ptr<Fact>)cppObj;
#endif

- (NSString * _Nullable)getTitle;
- (void)setTitle:(NSString * _Nonnull)value;
- (NSString * _Nullable)getValue;
- (void)setValue:(NSString * _Nonnull)value;
- (ACSDateTimePreparser * _Nullable)getTitleForDateParsing;
- (ACSDateTimePreparser * _Nullable)getValueForDateParsing;
- (void)setLanguage:(NSString * _Nonnull)value;
- (NSString * _Nullable)getLanguage;


@end
#endif
