// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSNumberInput_IMPORTED
#define ACSNumberInput_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "NumberInput.h"
using namespace AdaptiveCards;
#endif




#import "ACSBaseInputElement.h"
  




@interface ACSNumberInput : ACSBaseInputElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithNumberInput:(const std::shared_ptr<NumberInput>)cppObj;
#endif

- (NSString * _Nullable)getPlaceholder;
- (void)setPlaceholder:(NSString * _Nonnull)value;
- (NSNumber * _Nullable)getValue;
- (void)setValue:(NSNumber * _Nullable)value;
- (NSNumber * _Nullable)getMax;
- (void)setMax:(NSNumber * _Nullable)value;
- (NSNumber * _Nullable)getMin;
- (void)setMin:(NSNumber * _Nullable)value;



@end
#endif
