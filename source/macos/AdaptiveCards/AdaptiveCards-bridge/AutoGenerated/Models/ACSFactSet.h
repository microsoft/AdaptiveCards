// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSFactSet_IMPORTED
#define ACSFactSet_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "FactSet.h"
using namespace AdaptiveCards;
#endif

#import "ACSFact.h"



#import "ACSBaseCardElement.h"
  

@class ACSFact;



@interface ACSFactSet : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithFactSet:(const std::shared_ptr<FactSet>)cppObj;
#endif

- (NSArray<ACSFact *> * _Nonnull)getFacts;
- (NSArray<ACSFact *> * _Nonnull)getFacts;



@end
#endif
