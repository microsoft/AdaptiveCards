// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSTextInput_IMPORTED
#define ACSTextInput_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "TextInput.h"
using namespace AdaptiveCards;
#endif

#import "ACSBaseActionElement.h"
#import "ACSTextInputStyle.h"



#import "ACSBaseInputElement.h"
  

@class ACSBaseActionElement;

enum ACSTextInputStyle: NSUInteger;


@interface ACSTextInput : ACSBaseInputElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithTextInput:(const std::shared_ptr<TextInput>)cppObj;
#endif

- (NSString * _Nullable)getPlaceholder;
- (void)setPlaceholder:(NSString * _Nonnull)value;
- (NSString * _Nullable)getValue;
- (void)setValue:(NSString * _Nonnull)value;
- (bool)getIsMultiline;
- (void)setIsMultiline:(bool)value;
- (NSNumber * _Nullable)getMaxLength;
- (void)setMaxLength:(NSNumber * _Nonnull)value;
- (ACSTextInputStyle)getTextInputStyle;
- (void)setTextInputStyle:(enum ACSTextInputStyle)value;
- (ACSBaseActionElement * _Nullable)getInlineAction;
- (void)setInlineAction:(ACSBaseActionElement * _Nonnull)action;
- (NSString * _Nullable)getRegex;
- (void)setRegex:(NSString * _Nonnull)value;



@end
#endif
