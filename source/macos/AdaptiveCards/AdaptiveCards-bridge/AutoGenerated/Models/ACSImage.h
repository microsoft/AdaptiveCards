// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSImage_IMPORTED
#define ACSImage_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "Image.h"
using namespace AdaptiveCards;
#endif

#import "ACSBaseActionElement.h"
#import "ACSHorizontalAlignment.h"
#import "ACSImageSize.h"
#import "ACSImageStyle.h"
// #import "ACSRemoteResourceInformation.h"



#import "ACSBaseCardElement.h"
  

@class ACSBaseActionElement;
@class ACSRemoteResourceInformation;

enum ACSHorizontalAlignment: NSUInteger;
enum ACSImageSize: NSUInteger;
enum ACSImageStyle: NSUInteger;


@interface ACSImage : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithImage:(const std::shared_ptr<Image>)cppObj;
#endif

- (NSString * _Nullable)getUrl;
- (void)setUrl:(NSString * _Nonnull)value;
- (NSString * _Nullable)getBackgroundColor;
- (void)setBackgroundColor:(NSString * _Nonnull)value;
- (ACSImageStyle)getImageStyle;
- (void)setImageStyle:(enum ACSImageStyle)value;
- (ACSImageSize)getImageSize;
- (void)setImageSize:(enum ACSImageSize)value;
- (NSString * _Nullable)getAltText;
- (void)setAltText:(NSString * _Nonnull)value;
- (ACSHorizontalAlignment)getHorizontalAlignment;
- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value;
- (ACSBaseActionElement * _Nullable)getSelectAction;
- (void)setSelectAction:(ACSBaseActionElement * _Nonnull)action;
- (NSNumber * _Nullable)getPixelWidth;
- (void)setPixelWidth:(NSNumber * _Nonnull)value;
- (NSNumber * _Nullable)getPixelHeight;
- (void)setPixelHeight:(NSNumber * _Nonnull)value;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;



@end
#endif
