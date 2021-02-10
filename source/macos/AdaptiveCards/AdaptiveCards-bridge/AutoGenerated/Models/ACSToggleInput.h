// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSToggleInput_IMPORTED
#define ACSToggleInput_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ToggleInput.h"
using namespace AdaptiveCards;
#endif




#import "ACSBaseInputElement.h"
  




@interface ACSToggleInput : ACSBaseInputElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithToggleInput:(const std::shared_ptr<ToggleInput>)cppObj;
#endif

- (NSString * _Nullable)getTitle;
- (void)setTitle:(NSString * _Nonnull)value;
- (NSString * _Nullable)getValue;
- (void)setValue:(NSString * _Nonnull)value;
- (NSString * _Nullable)getValueOff;
- (void)setValueOff:(NSString * _Nonnull)value;
- (NSString * _Nullable)getValueOn;
- (void)setValueOn:(NSString * _Nonnull)value;
- (bool)getWrap;
- (void)setWrap:(bool)value;



@end
#endif
