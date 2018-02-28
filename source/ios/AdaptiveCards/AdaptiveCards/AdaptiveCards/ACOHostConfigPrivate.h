//
//  ACRHostConfigPrivate.h
//  ACRHostConfigPrivate
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOHostConfig.h"
#import "HostConfig.h"
#import "TextBlock.h"
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@interface ACOHostConfig()

- (instancetype)initWithConfig:(std::shared_ptr<HostConfig> const &)config;
- (std::shared_ptr<HostConfig> const &)getHostConfig;
- (void)setHostConfig:(std::shared_ptr<HostConfig> const &)config;

+ (NSNumber *)getTextStrokeWidthForWeight:(TextWeight)weight;
- (int)getTextBlockFontWeight:(TextWeight)weight;
- (int)getTextBlockTextSize:(TextSize)txtSz;
+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle;
+ (NSTextAlignment)getTextBlockAlignment:(HorizontalAlignment)alignment;
- (CGSize)getImageSize:(ImageSize)imageSize;

@end    
