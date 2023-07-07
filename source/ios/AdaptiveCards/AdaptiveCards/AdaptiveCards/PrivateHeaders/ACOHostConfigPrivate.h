//
//  ACRHostConfigPrivate.h
//  ACRHostConfigPrivate
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOBaseActionElement.h"
#import "ACOBaseCardElement.h"
#import "ACOHostConfig.h"
#import "ACORenderContext.h"
#import "ACREnums.h"
#import "HostConfig.h"
#import "TextBlock.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOBaseActionElement.h>
#import <AdaptiveCards/ACOBaseCardElement.h>
#import <AdaptiveCards/ACOHostConfig.h>
#import <AdaptiveCards/ACORenderContext.h>
#import <AdaptiveCards/ACREnums.h>
#import <AdaptiveCards/HostConfig.h>
#import <AdaptiveCards/TextBlock.h>
#endif
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@interface ACOHostConfig ()

- (instancetype)initWithConfig:(std::shared_ptr<HostConfig> const &)config;
- (std::shared_ptr<HostConfig>)getHostConfig;
- (void)setHostConfig:(std::shared_ptr<HostConfig> const &)config;

+ (NSNumber *)getTextStrokeWidthForWeight:(TextWeight)weight;

- (int)getTextBlockFontWeight:(FontType)type
                   textWeight:(TextWeight)weight;

- (int)getTextBlockTextSize:(FontType)type
                   textSize:(TextSize)txtSz;

- (NSString *)getFontFamily:(AdaptiveCards::FontType)type;

- (UIColor *)getTextBlockColor:(ACRContainerStyle)style
                     textColor:(ForegroundColor)txtClr
                  subtleOption:(bool)isSubtle;

- (UIColor *)getHighlightColor:(ACRContainerStyle)style
               foregroundColor:(ForegroundColor)color
                  subtleOption:(bool)isSubtle;

+ (NSTextAlignment)getTextBlockAlignment:(HorizontalAlignment)alignment context:(ACORenderContext *)context;

- (CGSize)getImageSizeAsCGSize:(ACRImageSize)imageSize width:(CGFloat)width height:(CGFloat)height;

+ (NSArray *)getConstraintsForImageAlignment:(HorizontalAlignment)alignment
                               withSuperview:(UIView *)superview
                                      toView:(UIView *)view;
// find date and time string, and replace them in NSDateFormatterCompactStyle, NSDateFormatterMediumStyle or
// NSDateFormatterLongStyle of local language
+ (std::string)getLocalizedDate:(std::string const &)text language:(std::string const &)language;

+ (UIColor *)convertHexColorCodeToUIColor:(std::string const &)hexColorCode;

- (UIColor *)getBackgroundColorForContainerStyle:(ACRContainerStyle)style;

+ (ACRContainerStyle)getPlatformContainerStyle:(ContainerStyle)style;

+ (ContainerStyle)getSharedContainerStyle:(ACRContainerStyle)style;

- (ACRIconPlacement)getIconPlacement;

- (void)setIconPlacement:(NSNumber *)internalId placement:(BOOL)placement;

@end
