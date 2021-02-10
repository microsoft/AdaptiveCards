// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSDateInput_IMPORTED
#define ACSDateInput_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "DateInput.h"
using namespace AdaptiveCards;
#endif




#import "ACSBaseInputElement.h"
  




@interface ACSDateInput : ACSBaseInputElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithDateInput:(const std::shared_ptr<DateInput>)cppObj;
#endif

- (NSString * _Nullable)getMax;
- (void)setMax:(NSString * _Nonnull)value;
- (NSString * _Nullable)getMin;
- (void)setMin:(NSString * _Nonnull)value;
- (NSString * _Nullable)getPlaceholder;
- (void)setPlaceholder:(NSString * _Nonnull)value;
- (NSString * _Nullable)getValue;
- (void)setValue:(NSString * _Nonnull)value;



@end
#endif
