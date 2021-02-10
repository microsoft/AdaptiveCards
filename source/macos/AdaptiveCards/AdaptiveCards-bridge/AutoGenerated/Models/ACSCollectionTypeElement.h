// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSCollectionTypeElement_IMPORTED
#define ACSCollectionTypeElement_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "CollectionTypeElement.h"
using namespace AdaptiveCards;
#endif

#import "ACSBaseCardElement.h"

#import "ACSBackgroundImage.h"
#import "ACSBaseActionElement.h"
#import "ACSContainerBleedDirection.h"
#import "ACSContainerStyle.h"
#import "ACSInternalId.h"
#import "ACSParseContext.h"
#import "ACSVerticalContentAlignment.h"
  

@class ACSBackgroundImage;
@class ACSBaseActionElement;
@class ACSInternalId;
@class ACSParseContext;

enum ACSContainerBleedDirection: NSUInteger;
enum ACSContainerStyle: NSUInteger;
enum ACSVerticalContentAlignment: NSUInteger;


@interface ACSCollectionTypeElement : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithCollectionTypeElement:(const std::shared_ptr<CollectionTypeElement>)cppObj;
#endif

- (ACSContainerStyle)getStyle;
- (void)setStyle:(enum ACSContainerStyle)value;
- (ACSVerticalContentAlignment)getVerticalContentAlignment;
- (void)setVerticalContentAlignment:(enum ACSVerticalContentAlignment)value;
- (bool)getPadding;
- (void)setPadding:(bool)value;
- (bool)getBleed;
- (void)setBleed:(bool)value;
- (bool)getCanBleed;
- (ACSContainerBleedDirection)getBleedDirection;
- (void)configForContainerStyle:(ACSParseContext * _Nonnull)context;
- (void)setParentalId:(ACSInternalId * _Nonnull)id;
- (ACSInternalId * _Nullable)getParentalId;
- (ACSBaseActionElement * _Nullable)getSelectAction;
- (void)setSelectAction:(ACSBaseActionElement * _Nonnull)action;
- (ACSBackgroundImage * _Nullable)getBackgroundImage;
- (void)setBackgroundImage:(ACSBackgroundImage * _Nonnull)value;
- (NSNumber * _Nullable)getMinHeight;
- (void)setMinHeight:(NSNumber * _Nonnull)value;
- (void)configPadding:(ACSParseContext * _Nonnull)context;
- (void)configBleed:(ACSParseContext * _Nonnull)context;
- (void)setBleedDirection:(enum ACSContainerBleedDirection)bleedDirection;


@end
#endif
