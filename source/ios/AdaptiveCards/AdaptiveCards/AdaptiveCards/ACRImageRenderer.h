//
//  ACRImageRenderer
//  ACRImageRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"
#import "Image.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@interface ACRImageRenderer:ACRBaseCardElementRenderer

+ (ACRImageRenderer *)getInstance;

+ (CGSize)getImageSize:(ImageSize)imageSize withHostConfig:(std::shared_ptr<HostConfig> const &)hostConfig;
@end
