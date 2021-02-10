// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSParseContext_IMPORTED
#define ACSParseContext_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ParseContext.h"
using namespace AdaptiveCards;
#endif

#import "ACSCollectionTypeElement.h"
#import "ACSContainerBleedDirection.h"
#import "ACSContainerStyle.h"
#import "ACSInternalId.h"



  

@class ACSCollectionTypeElement;
@class ACSInternalId;

enum ACSContainerBleedDirection: NSUInteger;
enum ACSContainerStyle: NSUInteger;


@interface ACSParseContext : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithParseContext:(const std::shared_ptr<ParseContext>)cppObj;
#endif

- (void)pushElement:(NSString * _Nonnull)idJsonProperty internalId:(ACSInternalId * _Nonnull)internalId isFallback:(bool)isFallback;
- (void)popElement;
- (bool)getCanFallbackToAncestor;
- (void)setCanFallbackToAncestor:(bool)value;
- (void)setLanguage:(NSString * _Nonnull)value;
- (NSString * _Nullable)getLanguage;
- (ACSContainerStyle)getParentalContainerStyle;
- (void)setParentalContainerStyle:(enum ACSContainerStyle)style;
- (ACSInternalId * _Nullable)paddingParentInternalId;
- (void)saveContextForCollectionTypeElement:(ACSCollectionTypeElement * _Nonnull)current;
- (void)restoreContextForCollectionTypeElement:(ACSCollectionTypeElement * _Nonnull)current;
- (ACSContainerBleedDirection)getBleedDirection;
- (void)pushBleedDirection:(enum ACSContainerBleedDirection)direction;
- (void)popBleedDirection;
- (ACSInternalId * _Nullable)getNearestFallbackId:(ACSInternalId * _Nonnull)skipId;


@end
#endif
