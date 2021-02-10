// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSShowCardAction_IMPORTED
#define ACSShowCardAction_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ShowCardAction.h"
using namespace AdaptiveCards;
#endif

#import "ACSAdaptiveCard.h"
// #import "ACSRemoteResourceInformation.h"



#import "ACSBaseActionElement.h"
  

@class ACSAdaptiveCard;
@class ACSRemoteResourceInformation;



@interface ACSShowCardAction : ACSBaseActionElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithShowCardAction:(const std::shared_ptr<ShowCardAction>)cppObj;
#endif

- (ACSAdaptiveCard * _Nullable)getCard;
- (void)setCard:(ACSAdaptiveCard * _Nonnull)card;
- (void)setLanguage:(NSString * _Nonnull)value;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;


@end
#endif
