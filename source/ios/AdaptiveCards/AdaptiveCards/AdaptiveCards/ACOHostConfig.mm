//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AdaptiveCardParseException.h"
#import "ACOHostConfigPrivate.h"
#import "ACRErrors.h"
#import "TextBlock.h"
#import "ACOBaseCardElement.h"
#import "Enums.h"

using namespace AdaptiveCards;

@implementation ACOHostConfig
{
    std::shared_ptr<HostConfig> _config;
    NSMutableDictionary<NSString *, NSString *> *_fontFamilyNames;
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
        _fontFamilyNames = [NSMutableDictionary dictionary];
        
        // check if requested font family name is supported by iOS, if so save it for future uses
        [self importFontFamily: AdaptiveCards::FontStyle::Default];
        [self importFontFamily: AdaptiveCards::FontStyle::Display];
        [self importFontFamily: AdaptiveCards::FontStyle::Monospace];
        
        
        _allActionsHaveIcons = YES;
        _buttonPadding = 5;
        if(!_config->GetImageBaseUrl().empty()) {
            NSString *tmpURLString = [NSString stringWithCString:_config->GetImageBaseUrl().c_str() encoding:NSUTF8StringEncoding];
            _baseURL = [NSURL URLWithString:tmpURLString];
        }
    }
    return self;
}

- (void) importFontFamily:(AdaptiveCards::FontStyle)style
{
    NSString *requestedFontFamilyName = [NSString stringWithCString:_config->GetFontFamily(style).c_str() encoding:NSUTF8StringEncoding];
    if([UIFont.familyNames containsObject:requestedFontFamilyName]){
        NSString *key = [NSString stringWithCString:FontStyleToString(style).c_str() encoding:NSUTF8StringEncoding];
        _fontFamilyNames[key] = requestedFontFamilyName;
    }
}

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload resourceResolvers:(ACOResourceResolvers *)resolvers
{
    ACOHostConfigParseResult *result = nil;
    if(payload) {
        try {
            std::shared_ptr<HostConfig> cHostConfig = std::make_shared<HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String])));
            ACOHostConfig *config= [[ACOHostConfig alloc] initWithConfig:cHostConfig];
            result = [[ACOHostConfigParseResult alloc] init:config errors:nil];
            config->_resolvers = resolvers;
        } catch(const AdaptiveCardParseException& e) {
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

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload;
{
    ACOHostConfigParseResult *result = nil;

    if(payload) {
        result = [ACOHostConfig fromJson:payload resourceResolvers:nil];
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

- (NSObject<ACOIResourceResolver> *)getResourceResolverForScheme:(NSString *)scheme
{
    if(!scheme) {
        return nil;
    }

    return [_resolvers getResourceResolverForScheme:scheme];
}

+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle
{
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

    return [ACOHostConfig convertHexColorCodeToUIColor:*str];
}

- (int)getTextBlockTextSize:(FontStyle)style
                   textSize:(TextSize)txtSz
{
    return _config->GetFontSize(style, txtSz);
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

- (int)getTextBlockFontWeight:(FontStyle) style
                   textWeight:(TextWeight)weight
{
    return _config->GetFontWeight(style, weight);
}

- (CGSize)getImageSize:(ImageSize)imageSize
{
    float sz;
    switch (imageSize)
    {
        case ImageSize::Large:{
            sz = _config->GetImageSizes().largeSize;
            break;
        }
        case ImageSize::Medium:{
            sz = _config->GetImageSizes().mediumSize;
            break;
        }

        case ImageSize::Small:{
            sz = _config->GetImageSizes().smallSize;
            break;
        }

        default:{
            sz = _config->GetImageSizes().largeSize;
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}

+ (NSArray *)getConstraintsForImageAlignment:(HorizontalAlignment)alignment
                               withSuperview:(UIView *)superview
                                      toView:(UIView *)view
{
    NSMutableArray *constraints = [[NSMutableArray alloc] init];
    [constraints addObject:
        [NSLayoutConstraint constraintWithItem:superview
                                     attribute:NSLayoutAttributeCenterY
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:view
                                     attribute:NSLayoutAttributeCenterY
                                    multiplier:1
                                      constant:0]];

    switch (alignment)
    {
        case HorizontalAlignment::Center:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeCenterX
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeCenterX
                                            multiplier:1
                                              constant:0]];
                return constraints;
        }
        case HorizontalAlignment::Left:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeLeading
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeLeading
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
        case HorizontalAlignment::Right:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeTrailing
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeTrailing
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
        default:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeLeading
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeLeading
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
    }
    return constraints;
}
// find date and time string, and replace them in NSDateFormatterCompactStyle, NSDateFormatterMediumStyle or
// NSDateFormatterLongStyle of local language
+ (std::string) getLocalizedDate:(std::string const) text language:(std::string const) language
{
    std::string dateParsedString;
    std::vector<std::shared_ptr<DateTimePreparsedToken>> DateTimePreparsedTokens =  DateTimePreparser(text).GetTextTokens();
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

            NSString *languageType= [NSString stringWithCString:language.c_str() encoding:NSUTF8StringEncoding];
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

+ (UIColor *)convertHexColorCodeToUIColor:(const std::string&)hexColorCode
{
    if((hexColorCode.length() < 2) || (hexColorCode.at(0) != '#') || !isxdigit(hexColorCode.at(1)) ||
       ((hexColorCode.length() != 7) && hexColorCode.length() != 9)) {
        NSLog(@"invalid hexcolor code is given for background color: %@",
            [NSString stringWithCString:hexColorCode.c_str() encoding:NSUTF8StringEncoding]);
        return UIColor.clearColor;
    }

    UIColor *color = UIColor.clearColor;

    try {
        size_t idx = 0;
        long num = std::stoul(hexColorCode.substr(1), &idx, 16), alpha = 0xFF;
        if(hexColorCode.length() == 9) {
            alpha = (num & 0xFF000000) >> 24;
        }

        if(idx != hexColorCode.length() - 1) {
            NSLog(@"invalid hexcolor code is given: %@",
                  [NSString stringWithCString:hexColorCode.c_str() encoding:NSUTF8StringEncoding]);
            color = UIColor.clearColor;
        } else {
            color = [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                                    green:((num & 0x0000FF00) >>  8) / 255.0
                                     blue:((num & 0x000000FF)) / 255.0
                                    alpha:alpha / 255.0];
        }
    } catch (...) {
        color = UIColor.clearColor;
        NSLog(@"invalid hexcolor code is given: %@",
            [NSString stringWithCString:hexColorCode.c_str() encoding:NSUTF8StringEncoding]);
    }

    return color;
}

- (UIColor *)getBackgroundColorForContainerStyle:(ACRContainerStyle)style
{
    const std::string &hexColorCode = (style == ACREmphasis)?
        _config->GetContainerStyles().emphasisPalette.backgroundColor :
        _config->GetContainerStyles().defaultPalette.backgroundColor;

    return [ACOHostConfig convertHexColorCodeToUIColor:hexColorCode];
}

+ (ACRContainerStyle)getPlatformContainerStyle:(ContainerStyle)style
{
    ACRContainerStyle containerStyle = ACRDefault;
    switch (style) {
        case ContainerStyle::None:
            containerStyle = ACRNone;
            break;
        case ContainerStyle::Default:
            containerStyle = ACRDefault;
            break;
        case ContainerStyle::Emphasis:
            containerStyle = ACREmphasis;
            break;
        default:
            containerStyle = ACRDefault;
            break;
    }
    return containerStyle;
}

- (NSString *)getFontFamily:(AdaptiveCards::FontStyle)style
{
    NSString *key = [NSString stringWithCString:FontStyleToString(style).c_str() encoding:NSUTF8StringEncoding];
    return _fontFamilyNames[key];
}

- (ACRIconPlacement)getIconPlacement
{
    if(IconPlacement::AboveTitle == _config->GetActions().iconPlacement) {
        return ACRAboveTitle;
    }
    return ACRLeftOfTitle;
}
@end
