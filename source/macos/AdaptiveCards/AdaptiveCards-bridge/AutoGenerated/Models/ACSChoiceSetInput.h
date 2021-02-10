// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSChoiceSetInput_IMPORTED
#define ACSChoiceSetInput_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ChoiceSetInput.h"
using namespace AdaptiveCards;
#endif

#import "ACSChoiceInput.h"
#import "ACSChoiceSetStyle.h"



#import "ACSBaseInputElement.h"
  

@class ACSChoiceInput;

enum ACSChoiceSetStyle: NSUInteger;


@interface ACSChoiceSetInput : ACSBaseInputElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithChoiceSetInput:(const std::shared_ptr<ChoiceSetInput>)cppObj;
#endif

- (bool)getIsMultiSelect;
- (void)setIsMultiSelect:(bool)isMultiSelect;
- (ACSChoiceSetStyle)getChoiceSetStyle;
- (void)setChoiceSetStyle:(enum ACSChoiceSetStyle)choiceSetStyle;
- (NSArray<ACSChoiceInput *> * _Nonnull)getChoices;
- (NSArray<ACSChoiceInput *> * _Nonnull)getChoices;
- (NSString * _Nullable)getValue;
- (void)setValue:(NSString * _Nonnull)value;
- (bool)getWrap;
- (void)setWrap:(bool)value;
- (NSString * _Nullable)getPlaceholder;
- (void)setPlaceholder:(NSString * _Nonnull)value;



@end
#endif
