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
#import "TextBlock.h"

using namespace AdaptiveCards;

@implementation ACOHostConfig
{
    std::shared_ptr<HostConfig> _config;
}

- (instancetype)init
{
    self = [self initWithConfig:nullptr];
    _config = std::make_shared<HostConfig>();
    return self;
}

- (instancetype)initWithConfig:(std::shared_ptr<HostConfig> const &)config
{
    self = [super init];
    if(self && config){
        _config = config;
        // check if requested font family name is supported by iOS, if so save it for future uses
        NSString *requestedFontFamilyName = [NSString stringWithCString:_config->fontFamily.c_str() encoding:NSUTF8StringEncoding];
        if([UIFont.familyNames containsObject:requestedFontFamilyName]){
            _fontFamilyNames = @[requestedFontFamilyName];
        }
        // if the requested font family name is not supported, use system font instead
        if(!_fontFamilyNames){
            _fontFamilyNames = @[@"-apple-system", @"HelveticaNeue"];
        }
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
            std::shared_ptr<HostConfig> cHostConfig = std::make_shared<HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String])));
            ACOHostConfig *config= [[ACOHostConfig alloc] initWithConfig:cHostConfig];
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

- (std::shared_ptr<HostConfig>)getHostConfig
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

// find date and time string, and replace them in NSDateFormatterCompactStyle, NSDateFormatterMediumStyle or
// NSDateFormatterLongStyle of local language
+ (std::string) getLocalizedDate:(std::shared_ptr<TextBlock> const &)txtBlck
{
    std::string dateParsedString;
    std::vector<std::shared_ptr<DateTimePreparsedToken>> DateTimePreparsedTokens =  DateTimePreparser(txtBlck->GetText()).GetTextTokens();
    for(auto section : DateTimePreparsedTokens){
        if(section->GetFormat() != DateTimePreparsedTokenFormat::RegularString) {
            NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
            [formatter setDateFormat:@"MM/dd/yyyy"];
            /// date format has been already verified by preparsed token
            std::string givenDate = std::to_string(section->GetMonth() + 1) + "/" +  std::to_string(section->GetDay()) + "/" +  std::to_string(section->GetYear());
            NSString *nsString = [NSString stringWithCString:givenDate.c_str() encoding:NSUTF8StringEncoding];
            NSDate *date = [formatter dateFromString:nsString];
            // specify output date format
            NSDateFormatter *outputFormatter = [[NSDateFormatter alloc] init];
            outputFormatter.timeStyle = NSDateFormatterNoStyle;
            if(section->GetFormat() == DateTimePreparsedTokenFormat::DateCompact){
                outputFormatter.dateStyle = NSDateFormatterShortStyle;
            } else if(section->GetFormat() == DateTimePreparsedTokenFormat::DateShort){
                outputFormatter.dateStyle = NSDateFormatterMediumStyle;
            } else{
                outputFormatter.dateStyle = NSDateFormatterLongStyle;
            }

            NSString *languageType= [NSString stringWithCString:txtBlck->GetLanguage().c_str() encoding:NSUTF8StringEncoding];
            if(languageType.length > 0){
                outputFormatter.locale = [[NSLocale alloc] initWithLocaleIdentifier:languageType];
            }
            NSString *dateInLocalLanguage = [outputFormatter stringFromDate:date];
            dateParsedString += [dateInLocalLanguage UTF8String];
        } else {
            dateParsedString += section->GetText();
        }
    }
    return dateParsedString;
}

@end
