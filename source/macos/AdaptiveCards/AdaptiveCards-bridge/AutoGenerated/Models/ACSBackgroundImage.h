// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSBackgroundImage_IMPORTED
#define ACSBackgroundImage_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "BackgroundImage.h"
using namespace AdaptiveCards;
#endif

#import "ACSHorizontalAlignment.h"
#import "ACSImageFillMode.h"
#import "ACSVerticalAlignment.h"



  


enum ACSHorizontalAlignment: NSUInteger;
enum ACSImageFillMode: NSUInteger;
enum ACSVerticalAlignment: NSUInteger;


@interface ACSBackgroundImage : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithBackgroundImage:(const std::shared_ptr<BackgroundImage>)cppObj;
#endif

- (NSString * _Nullable)getUrl;
- (void)setUrl:(NSString * _Nonnull)value;
- (ACSImageFillMode)getFillMode;
- (void)setFillMode:(enum ACSImageFillMode)value;
- (ACSHorizontalAlignment)getHorizontalAlignment;
- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value;
- (ACSVerticalAlignment)getVerticalAlignment;
- (void)setVerticalAlignment:(enum ACSVerticalAlignment)value;


@end
#endif
