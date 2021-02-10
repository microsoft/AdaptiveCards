// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSSubmitAction_IMPORTED
#define ACSSubmitAction_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "SubmitAction.h"
using namespace AdaptiveCards;
#endif

#import "ACSAssociatedInputs.h"
// #import "ACSValue.h"



#import "ACSBaseActionElement.h"
  


enum ACSAssociatedInputs: NSUInteger;


@interface ACSSubmitAction : ACSBaseActionElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithSubmitAction:(const std::shared_ptr<SubmitAction>)cppObj;
#endif

- (NSString * _Nullable)getDataJson;
- (void)setDataJson:(NSString * _Nonnull)value;
- (ACSAssociatedInputs)getAssociatedInputs;
- (void)setAssociatedInputs:(enum ACSAssociatedInputs)value;



@end
#endif
