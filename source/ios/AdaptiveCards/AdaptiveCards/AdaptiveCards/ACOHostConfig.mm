//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACOHostConfig.h"
#import "HostConfig.h"
#import "AdaptiveCardParseException.h"
#import "ACRErrors.h"

using namespace AdaptiveCards;

@implementation ACOHostConfig
{
    std::shared_ptr<HostConfig> _config;
}

- (instancetype)init
{
    self = [self initWithConfig:nil];
    _config = std::make_shared<HostConfig>();
    return self;
}

- (instancetype)initWithConfig:(std::shared_ptr<HostConfig> const &)config
{
    self = [super init];
    if(self && config){
        _config = config;
    }
    return self;
}

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload;
{
    ACOHostConfigParseResult *result = nil;

    if(payload)
    {
        try
        {
            ACOHostConfig *config= [[ACOHostConfig alloc] init];
            *config->_config.get() = AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String]));
            result = [[ACOHostConfigParseResult alloc] init:config errors:nil];
        }
        catch(const AdaptiveCardParseException& e)
        {
            // converts AdaptiveCardParseException to NSError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;
            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:nil];
            NSArray<NSError *> *errors = @[parseError];
            result = [[ACOHostConfigParseResult alloc] init:nil errors:errors];
        }
    }
    return result;
}

- (std::shared_ptr<HostConfig> const &)getHostConfig
{
    return _config;
}

- (void)setHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    _config = config;
}

+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle
{
    long num = 0;
    const std::string *str;
    switch (txtClr) {
        case ForegroundColor::Dark:{
            str = (isSubtle) ?
                &config.dark.subtleColor: &config.dark.defaultColor;
            break;
        }
        case ForegroundColor::Light:{
            str = (isSubtle) ?
                &config.light.subtleColor: &config.light.defaultColor;
            break;
        }
        case ForegroundColor::Accent:{
            str = (isSubtle) ?
                &config.accent.subtleColor: &config.accent.defaultColor;
            break;
        }
        case ForegroundColor::Good:{
            str = (isSubtle) ?
                &config.good.subtleColor: &config.good.defaultColor;
            break;
        }
        case ForegroundColor::Warning:{
            str = (isSubtle) ?
                &config.warning.subtleColor: &config.warning.defaultColor;
            break;
        }
        case ForegroundColor::Attention:{
            str = (isSubtle) ?
                &config.attention.subtleColor: &config.attention.defaultColor;
            break;
        }
        default:{
            str = (isSubtle) ?
                &config.dark.subtleColor: &config.dark.defaultColor;
            break;
        }
    }

    num = std::stoul(str->substr(1), nullptr, 16);

    return [UIColor colorWithRed:((num & 0x00FF0000)>> 16)/ 255.0
                           green:((num & 0x0000FF00)>> 8)/ 255.0
                            blue:((num & 0x000000FF))/ 255.0
                           alpha:((num & 0xFF000000)>> 24)/ 255.0];

}

- (int)getTextBlockTextSize:(TextSize)txtSz
{
    switch (txtSz){
        case TextSize::Small:
            return _config->fontSizes.smallFontSize;
        case TextSize::Default:
            return _config->fontSizes.defaultFontSize;
        case TextSize::Medium:
            return _config->fontSizes.mediumFontSize;
        case TextSize::Large:
            return _config->fontSizes.largeFontSize;
        case TextSize::ExtraLarge:
            return _config->fontSizes.extraLargeFontSize;
        default:
            return _config->fontSizes.defaultFontSize;
    }
}

+ (NSTextAlignment)getTextBlockAlignment:(HorizontalAlignment) alignment
{
    switch (alignment){
        case HorizontalAlignment::Center:
            return NSTextAlignmentCenter;
        case HorizontalAlignment::Left:
            return NSTextAlignmentLeft;
        case HorizontalAlignment::Right:
            return NSTextAlignmentRight;
        default:
            return NSTextAlignmentLeft;
    }
}

+ (NSNumber *)getTextStrokeWidthForWeight:(TextWeight)weight
{
    switch (weight) {
        case TextWeight::Default:
            return @0;
        case TextWeight::Lighter:
            return @1;
        case TextWeight::Bolder:
            return @-2;
    }
}

- (int)getTextBlockFontWeight:(TextWeight)weight
{
    switch (weight) {
        default:
        case TextWeight::Default:
            return _config->fontWeights.defaultWeight;
        case TextWeight::Lighter:
            return _config->fontWeights.lighterWeight;
        case TextWeight::Bolder:
            return _config->fontWeights.bolderWeight;
    }
}

- (CGSize)getImageSize:(ImageSize)imageSize
{
    float sz = _config->imageSizes.smallSize;
    switch (imageSize)
    {
        case ImageSize::Large:{
            sz = _config->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium:{
            sz = _config->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small:{
            sz = _config->imageSizes.smallSize;
            break;
        }

        default:{
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}
@end
