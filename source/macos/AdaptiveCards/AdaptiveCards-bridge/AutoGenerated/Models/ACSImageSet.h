// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSImageSet_IMPORTED
#define ACSImageSet_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ImageSet.h"
using namespace AdaptiveCards;
#endif

#import "ACSImage.h"
#import "ACSImageSize.h"



#import "ACSBaseCardElement.h"
  

@class ACSImage;
@class ACSRemoteResourceInformation;

enum ACSImageSize: NSUInteger;


@interface ACSImageSet : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithImageSet:(const std::shared_ptr<ImageSet>)cppObj;
#endif

- (ACSImageSize)getImageSize;
- (void)setImageSize:(enum ACSImageSize)value;
- (NSArray<ACSImage *> * _Nonnull)getImages;
- (void)getResourceInformation:(NSArray<ACSRemoteResourceInformation *>* _Nonnull)resourceInfo;



@end
#endif
