//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"
#import "TextBlock.h"

@interface ACRTextBlockRenderer:ACRBaseCardElementRenderer

+ (ACRTextBlockRenderer *)getInstance;

+ (NSNumber *)getTextBlockTextWeight:(TextWeight)weight
                      withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (int)getTextBlockTextSize:(TextSize)txtSz
             withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle;

+ (NSTextAlignment)getTextBlockAlignment:(std::shared_ptr<TextBlock> const &)txtBlock
                          withHostConfig:(std::shared_ptr<HostConfig> const &)config;

@end
