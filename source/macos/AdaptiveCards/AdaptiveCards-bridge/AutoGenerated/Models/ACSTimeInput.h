// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSTimeInput_IMPORTED
#define ACSTimeInput_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "TimeInput.h"
using namespace AdaptiveCards;
#endif




#import "ACSBaseInputElement.h"
  




@interface ACSTimeInput : ACSBaseInputElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithTimeInput:(const std::shared_ptr<TimeInput>)cppObj;
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
