// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSActionSet_IMPORTED
#define ACSActionSet_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ActionSet.h"
using namespace AdaptiveCards;
#endif




#import "ACSBaseCardElement.h"
#import "ACSBaseActionElement.h"
  




@interface ACSActionSet : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithActionSet:(const std::shared_ptr<ActionSet>)cppObj;
#endif

- (NSArray<ACSBaseActionElement *> * _Nonnull)getActions;



@end
#endif
