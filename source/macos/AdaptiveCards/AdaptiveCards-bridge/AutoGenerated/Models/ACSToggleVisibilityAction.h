// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSToggleVisibilityAction_IMPORTED
#define ACSToggleVisibilityAction_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ToggleVisibilityAction.h"
using namespace AdaptiveCards;
#endif

#import "ACSToggleVisibilityTarget.h"



#import "ACSBaseActionElement.h"
  

@class ACSToggleVisibilityTarget;



@interface ACSToggleVisibilityAction : ACSBaseActionElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithToggleVisibilityAction:(const std::shared_ptr<ToggleVisibilityAction>)cppObj;
#endif

- (NSArray<ACSToggleVisibilityTarget *> * _Nonnull)getTargetElements;
- (NSArray<ACSToggleVisibilityTarget *> * _Nonnull)getTargetElements;



@end
#endif
