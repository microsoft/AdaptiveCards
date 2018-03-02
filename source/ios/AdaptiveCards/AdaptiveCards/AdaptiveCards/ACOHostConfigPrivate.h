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
- (std::shared_ptr<HostConfig>) getHostConfig;
- (void)setHostConfig:(std::shared_ptr<HostConfig> const &)config;

+ (NSNumber *)getTextStrokeWidthForWeight:(TextWeight)weight;
- (int)getTextBlockFontWeight:(TextWeight)weight;
- (int)getTextBlockTextSize:(TextSize)txtSz;
+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle;
+ (NSTextAlignment)getTextBlockAlignment:(HorizontalAlignment)alignment;
- (CGSize)getImageSize:(ImageSize)imageSize;
// find date and time string, and replace them in NSDateFormatterCompactStyle, NSDateFormatterMediumStyle or
// NSDateFormatterLongStyle of local language
+ (std::string) getLocalizedDate:(std::shared_ptr<TextBlock> const &)txtBlck;

@end    
