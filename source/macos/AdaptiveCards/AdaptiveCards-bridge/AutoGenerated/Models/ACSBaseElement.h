// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSBaseElement_IMPORTED
#define ACSBaseElement_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "BaseElement.h"
using namespace AdaptiveCards;
#endif

#import "ACSBaseElement.h"
#import "ACSFallbackType.h"
#import "ACSFeatureRegistration.h"
#import "ACSInternalId.h"



  

@class ACSBaseElement;
@class ACSFeatureRegistration;
@class ACSInternalId;
@class ACSParseContext;
@class ACSRemoteResourceInformation;

enum ACSFallbackType: NSUInteger;


@interface ACSBaseElement : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithBaseElement:(const std::shared_ptr<BaseElement>)cppObj;
#endif

- (NSString * _Nullable)getElementTypeString;
- (void)setElementTypeString:(NSString * _Nonnull)value;
- (NSString * _Nullable)getId;
- (void)setId:(NSString * _Nonnull)value;
- (ACSInternalId * _Nullable)getInternalId;
- (ACSFallbackType)getFallbackType;
- (ACSBaseElement * _Nullable)getFallbackContent;
- (bool)canFallbackToAncestor;
- (void)setFallbackType:(enum ACSFallbackType)type;
- (void)setFallbackContent:(ACSBaseElement * _Nonnull)element;
- (bool)meetsRequirements:(ACSFeatureRegistration * _Nonnull)hostProvides;
- (NSString * _Nullable)getRequirements;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceUris;


@end
#endif
