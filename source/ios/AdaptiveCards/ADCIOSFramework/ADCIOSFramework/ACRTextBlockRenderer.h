//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRTextBlockRenderer:ACRBaseCardElementRenderer

+ (ACRTextBlockRenderer *)getInstance;

+ (NSNumber *)getTextBlockTextWeight:(TextWeight)weight
                      withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (int)getTextBlockTextSize:(TextSize)txtSz
             withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (UIColor *)getTextBlockColor:(TextColor)txtClr
                withHostConfig:(std::shared_ptr<HostConfig> const &)config
               andSubtleOption:(bool)IsSubtle;

@end
