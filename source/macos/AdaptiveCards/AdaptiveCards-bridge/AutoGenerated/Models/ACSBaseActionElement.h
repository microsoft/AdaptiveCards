// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSBaseActionElement_IMPORTED
#define ACSBaseActionElement_IMPORTED
#import <Foundation/Foundation.h>

//#import "ACSBaseElement.h"
#import "ACSActionType.h"

#ifdef __cplusplus
#import "BaseActionElement.h"
using namespace AdaptiveCards;
#endif

@class ACSRemoteResourceInformation;

enum ACSActionType: NSUInteger;

@interface ACSBaseActionElement : ACSBaseElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithBaseActionElement:(const std::shared_ptr<BaseActionElement>)cppObj;
#endif

- (NSString * _Nullable)getTitle;
- (void)setTitle:(NSString * _Nonnull)value;
- (void)setTitle:(NSString * _Nonnull)value;
- (NSString * _Nullable)getIconUrl;
- (void)setIconUrl:(NSString * _Nonnull)value;
- (void)setIconUrl:(NSString * _Nonnull)value;
- (NSString * _Nullable)getStyle;
- (void)setStyle:(NSString * _Nonnull)value;
- (void)setStyle:(NSString * _Nonnull)value;
- (ACSActionType)getElementType;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceUris;



@end
#endif
