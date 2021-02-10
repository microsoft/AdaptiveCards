// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSBaseInputElement_IMPORTED
#define ACSBaseInputElement_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "BaseInputElement.h"
using namespace AdaptiveCards;
#endif




#import "ACSBaseCardElement.h"
  




@interface ACSBaseInputElement : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithBaseInputElement:(const std::shared_ptr<BaseInputElement>)cppObj;
#endif

- (NSString * _Nullable)getLabel;
- (void)setLabel:(NSString * _Nonnull)label;
- (bool)getIsRequired;
- (void)setIsRequired:(bool)isRequired;
- (NSString * _Nullable)getErrorMessage;
- (void)setErrorMessage:(NSString * _Nonnull)errorMessage;


@end
#endif
