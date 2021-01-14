//
//  ACRHostConfig.mm
//  ACRHostConfig.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import "ACOBaseCardElement.h"
#import "ACOHostConfigPrivate.h"
#import "ACRErrors.h"
#import "AdaptiveCardParseException.h"
#import "Enums.h"
#import "TextBlock.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

using namespace AdaptiveCards;

@implementation ACOHostConfig {
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
    if (self && config) {
        _config = config;
        _fontFamilyNames = [NSMutableDictionary dictionary];

        // check if requested font family name is supported by iOS, if so save it for future uses
        [self importFontFamily:AdaptiveCards::FontType::Default];
        [self importFontFamily:AdaptiveCards::FontType::Monospace];

        _allActionsHaveIcons = YES;
        _buttonPadding = 5;
        if (!_config->GetImageBaseUrl().empty()) {
            NSString *tmpURLString = [NSString stringWithCString:_config->GetImageBaseUrl().c_str() encoding:NSUTF8StringEncoding];
            _baseURL = [NSURL URLWithString:tmpURLString];
        }
    }
    return self;
}

- (void)importFontFamily:(AdaptiveCards::FontType)type
{
    NSString *requestedFontFamilyName = [NSString stringWithCString:_config->GetFontFamily(type).c_str() encoding:NSUTF8StringEncoding];
    if ([UIFont.familyNames containsObject:requestedFontFamilyName]) {
        NSString *key = [NSString stringWithCString:FontTypeToString(type).c_str() encoding:NSUTF8StringEncoding];
        _fontFamilyNames[key] = requestedFontFamilyName;
    }
}

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload resourceResolvers:(ACOResourceResolvers *)resolvers
{
    ACOHostConfigParseResult *result = nil;
    if (payload) {
        try {
            std::shared_ptr<HostConfig> cHostConfig = std::make_shared<HostConfig>(AdaptiveCards::HostConfig::DeserializeFromString(std::string([payload UTF8String])));
            ACOHostConfig *config = [[ACOHostConfig alloc] initWithConfig:cHostConfig];
            result = [[ACOHostConfigParseResult alloc] init:config errors:nil];
            config->_resolvers = resolvers;
        } catch (const AdaptiveCardParseException &e) {
            // converts AdaptiveCardParseException to NSError
            ErrorStatusCode errorStatusCode = e.GetStatusCode();
            NSInteger errorCode = (long)errorStatusCode;
            NSError *parseError = [NSError errorWithDomain:ACRParseErrorDomain
                                                      code:errorCode
                                                  userInfo:nil];
            NSArray<NSError *> *errors = @[ parseError ];
            result = [[ACOHostConfigParseResult alloc] init:nil errors:errors];
        }
    }
    return result;
}

+ (ACOHostConfigParseResult *)fromJson:(NSString *)payload;
{
    ACOHostConfigParseResult *result = nil;

    if (payload) {
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
    return [_resolvers getResourceResolverForScheme:scheme];
}

- (ACOResolverIFType)getResolverIFType:(NSString *)scheme;
{
    return [_resolvers getResolverIFType:scheme];
}

- (UIColor *)getHighlightColor:(ACRContainerStyle)style
               foregroundColor:(ForegroundColor)color
                  subtleOption:(bool)isSubtle
{
    const std::string str = _config->GetHighlightColor([ACOHostConfig getSharedContainerStyle:style], color, isSubtle);
    return [ACOHostConfig convertHexColorCodeToUIColor:str];
}

- (UIColor *)getTextBlockColor:(ACRContainerStyle)style
                     textColor:(ForegroundColor)txtClr
                  subtleOption:(bool)isSubtle
{
    const std::string str = _config->GetForegroundColor([ACOHostConfig getSharedContainerStyle:style], txtClr, isSubtle);
    return [ACOHostConfig convertHexColorCodeToUIColor:str];
}

- (int)getTextBlockTextSize:(FontType)type
                   textSize:(TextSize)txtSz
{
    return _config->GetFontSize(type, txtSz);
}

+ (NSTextAlignment)getTextBlockAlignment:(HorizontalAlignment)alignment
{
    switch (alignment) {
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

- (int)getTextBlockFontWeight:(FontType)type
                   textWeight:(TextWeight)weight
{
    return _config->GetFontWeight(type, weight);
}

- (CGSize)getImageSizeAsCGSize:(ACRImageSize)imageSize width:(CGFloat)width height:(CGFloat)height
{
    float sz = 0.0f;
    switch (imageSize) {
        case ACRImageSizeLarge:
            sz = _config->GetImageSizes().largeSize;
            break;

        case ACRImageSizeMedium:
            sz = _config->GetImageSizes().mediumSize;
            break;

        case ACRImageSizeStretch:
        case ACRImageSizeSmall:
            sz = _config->GetImageSizes().smallSize;
            break;

        case ACRImageSizeExplicit:
            BOOL isAspectRatioNeeded = !(width && height);
            CGSize imageSizeAsCGSize = CGSizeZero;
            if (width) {
                intrinsicContentSize.width = width;
                if (isAspectRatioNeeded) {
                    intrinsicContentSize.height = width;
                }
            }

            if (height) {
                intrinsicContentSize.height = height;
                if (isAspectRatioNeeded) {
                    intrinsicContentSize.width = height;
                }
            }
            break;
        case ACRImageSizeNone:
        case ACRImageSizeAuto:
        defalt:
            return CGSizeZero;
    }

    return CGSizeMake(sz, sz);
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

    switch (alignment) {
        case HorizontalAlignment::Center: {
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
        case HorizontalAlignment::Left: {
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
        case HorizontalAlignment::Right: {
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
        default: {
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
+ (std::string)getLocalizedDate:(std::string const &)text language:(std::string const &)language
{
    std::string dateParsedString;
    std::vector<std::shared_ptr<DateTimePreparsedToken>> DateTimePreparsedTokens = DateTimePreparser(text).GetTextTokens();
    for (auto section : DateTimePreparsedTokens) {
        if (section->GetFormat() != DateTimePreparsedTokenFormat::RegularString) {
            NSDateFormatter *formatter = [[NSDateFormatter alloc] init];
            [formatter setDateFormat:@"MM/dd/yyyy"];
            /// date format has been already verified by preparsed token
            std::string givenDate = std::to_string(section->GetMonth() + 1) + "/" + std::to_string(section->GetDay()) + "/" + std::to_string(section->GetYear());
            NSString *nsString = [NSString stringWithCString:givenDate.c_str() encoding:NSUTF8StringEncoding];
            NSDate *date = [formatter dateFromString:nsString];
            // specify output date format
            NSDateFormatter *outputFormatter = [[NSDateFormatter alloc] init];
            outputFormatter.timeStyle = NSDateFormatterNoStyle;
            if (section->GetFormat() == DateTimePreparsedTokenFormat::DateCompact) {
                outputFormatter.dateStyle = NSDateFormatterShortStyle;
            } else if (section->GetFormat() == DateTimePreparsedTokenFormat::DateShort) {
                outputFormatter.dateStyle = NSDateFormatterMediumStyle;
            } else {
                outputFormatter.dateStyle = NSDateFormatterLongStyle;
            }

            NSString *languageType = [NSString stringWithCString:language.c_str() encoding:NSUTF8StringEncoding];
            if (languageType.length > 0) {
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

+ (UIColor *)convertHexColorCodeToUIColor:(const std::string &)hexColorCode
{
    if ((hexColorCode.length() < 2) || (hexColorCode.at(0) != '#') || !isxdigit(hexColorCode.at(1)) ||
        ((hexColorCode.length() != 7) && hexColorCode.length() != 9)) {
        NSLog(@"invalid hexcolor code is given: %@",
              [NSString stringWithCString:hexColorCode.c_str()
                                 encoding:NSUTF8StringEncoding]);
        return UIColor.clearColor;
    }

    UIColor *color = UIColor.clearColor;

    try {
        size_t idx = 0;
        long num = std::stoul(hexColorCode.substr(1), &idx, 16), alpha = 0xFF;
        if (hexColorCode.length() == 9) {
            alpha = (num & 0xFF000000) >> 24;
        }

        if (idx != hexColorCode.length() - 1) {
            NSLog(@"invalid hexcolor code is given: %@",
                  [NSString stringWithCString:hexColorCode.c_str()
                                     encoding:NSUTF8StringEncoding]);
            color = UIColor.clearColor;
        } else {
            color = [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                                    green:((num & 0x0000FF00) >> 8) / 255.0
                                     blue:((num & 0x000000FF)) / 255.0
                                    alpha:alpha / 255.0];
        }
    } catch (...) {
        color = UIColor.clearColor;
        NSLog(@"invalid hexcolor code is given: %@",
              [NSString stringWithCString:hexColorCode.c_str()
                                 encoding:NSUTF8StringEncoding]);
    }

    return color;
}

- (UIColor *)getBackgroundColorForContainerStyle:(ACRContainerStyle)style
{
    std::string hexColorCode = _config->GetBackgroundColor([ACOHostConfig getSharedContainerStyle:style]);
    return [ACOHostConfig convertHexColorCodeToUIColor:hexColorCode];
}

+ (ACRContainerStyle)getPlatformContainerStyle:(ContainerStyle)style
{
    ACRContainerStyle containerStyle = ACRDefault;
    switch (style) {
        case ContainerStyle::None:
            containerStyle = ACRNone;
            break;
        case ContainerStyle::Accent:
            containerStyle = ACRAccent;
            break;
        case ContainerStyle::Attention:
            containerStyle = ACRAttention;
            break;
        case ContainerStyle::Emphasis:
            containerStyle = ACREmphasis;
            break;
        case ContainerStyle::Good:
            containerStyle = ACRGood;
            break;
        case ContainerStyle::Warning:
            containerStyle = ACRWarning;
            break;
        case ContainerStyle::Default:
        default:
            containerStyle = ACRDefault;
            break;
    }
    return containerStyle;
}

+ (ContainerStyle)getSharedContainerStyle:(ACRContainerStyle)style
{
    ContainerStyle containerStyle = ContainerStyle::Default;
    switch (style) {
        case ACRContainerStyle::ACRNone:
            containerStyle = ContainerStyle::None;
            break;
        case ACRContainerStyle::ACRAccent:
            containerStyle = ContainerStyle::Accent;
            break;
        case ACRContainerStyle::ACRAttention:
            containerStyle = ContainerStyle::Attention;
            break;
        case ACRContainerStyle::ACREmphasis:
            containerStyle = ContainerStyle::Emphasis;
            break;
        case ACRContainerStyle::ACRGood:
            containerStyle = ContainerStyle::Good;
            break;
        case ACRContainerStyle::ACRWarning:
            containerStyle = ContainerStyle::Warning;
            break;
        case ACRContainerStyle::ACRDefault:
        default:
            containerStyle = ContainerStyle::Default;
            break;
    }
    return containerStyle;
}

- (NSString *)getFontFamily:(AdaptiveCards::FontType)type
{
    NSString *key = [NSString stringWithCString:FontTypeToString(type).c_str() encoding:NSUTF8StringEncoding];
    return _fontFamilyNames[key];
}

- (ACRIconPlacement)getIconPlacement
{
    if (IconPlacement::AboveTitle == _config->GetActions().iconPlacement) {
        return ACRAboveTitle;
    }
    return ACRLeftOfTitle;
}
@end
