// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSMediaSource_IMPORTED
#define ACSMediaSource_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "MediaSource.h"
using namespace AdaptiveCards;
#endif

// #import "ACSRemoteResourceInformation.h"



  

@class ACSRemoteResourceInformation;



@interface ACSMediaSource : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithMediaSource:(const std::shared_ptr<MediaSource>)cppObj;
#endif

- (NSString * _Nullable)getMimeType;
- (void)setMimeType:(NSString * _Nonnull)value;
- (NSString * _Nullable)getUrl;
- (void)setUrl:(NSString * _Nonnull)value;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;


@end
#endif
