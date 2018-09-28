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
- (std::shared_ptr<HostConfig>)getHostConfig;
- (void)setHostConfig:(std::shared_ptr<HostConfig> const &)config;

+ (NSNumber *)getTextStrokeWidthForWeight:(TextWeight)weight;
- (int)getTextBlockFontWeight:(TextWeight)weight;
- (int)getTextBlockTextSize:(TextSize)txtSz;
+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle;
+ (NSTextAlignment)getTextBlockAlignment:(HorizontalAlignment)alignment;
- (CGSize)getImageSize:(ImageSize)imageSize;
+ (NSArray *)getConstraintsForImageAlignment:(HorizontalAlignment)alignment
                               withSuperview:(UIView *)superview
                                      toView:(UIView *)view;
// find date and time string, and replace them in NSDateFormatterCompactStyle, NSDateFormatterMediumStyle or
// NSDateFormatterLongStyle of local language
+ (std::string) getLocalizedDate:(std::string const &)text language:(std::string const &)language;

+ (UIColor *)convertHexColorCodeToUIColor:(std::string const &)hexColorCode;

- (UIColor *)getBackgroundColorForContainerStyle:(ACRContainerStyle)style;

+ (ACRContainerStyle)getPlatformContainerStyle:(ContainerStyle)style;

@end
