//
//  ACRImageRenderer
//  ACRImageRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"
#import "Image.h"

@interface ACRImageRenderer:ACRBaseCardElementRenderer

+ (ACRImageRenderer *)getInstance;

+ (CGSize)getImageSize:(std::shared_ptr<Image> const &)imgElem
        withHostConfig:(std::shared_ptr<HostConfig> const &)hostConfig;
@end
