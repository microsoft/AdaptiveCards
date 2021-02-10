// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSContainer_IMPORTED
#define ACSContainer_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "Container.h"
using namespace AdaptiveCards;
#endif

#import "ACSParseContext.h"
#import "ACSBaseCardElement.h"
// #import "ACSRemoteResourceInformation.h"
// #import "ACSValue.h"



#import "ACSCollectionTypeElement.h"
  

@class ACSParseContext;
@class ACSRemoteResourceInformation;




@interface ACSContainer : ACSCollectionTypeElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithContainer:(const std::shared_ptr<Container>)cppObj;
#endif

- (NSArray<ACSBaseCardElement *> * _Nonnull)getItems;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;



@end
#endif
