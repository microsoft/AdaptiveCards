//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "MarkDownParser.h"
#import "ACRViewController.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRUILabel.h"
#import "DateTimePreparsedToken.h"
#import "DateTimePreparser.h"

@implementation ACRTextBlockRenderer

+ (ACRTextBlockRenderer *)getInstance
{
    static ACRTextBlockRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::TextBlock;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
rootViewController:(UIViewController *)vc
            inputs:(NSMutableArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig;
{
    std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<TextBlock> txtBlck = std::dynamic_pointer_cast<TextBlock>(elem);
    ACRUILabel *lab = [[ACRUILabel alloc] init];
    lab.style = [viewGroup style];
    __block NSMutableAttributedString *content = nil;
    if(vc)
    {
        NSMutableDictionary *textMap = [(ACRViewController *)vc getTextMap];
        // Generate key for ImageViewMap
        NSString *key = [NSString stringWithCString:elem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
        // Syncronize access to imageViewMap
        dispatch_sync([(ACRViewController *)vc getSerialTextQueue], ^{
            if(textMap[key]) { // if content is available, get it, otherwise cache label, so it can be used used later
                content = textMap[key];
            } else {
                textMap[key] = lab;
            }
        });
    }

    if(content)
    {
        // Set paragraph style such as line break mode and alignment
        NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
        paragraphStyle.lineBreakMode = txtBlck->GetWrap() ? NSLineBreakByWordWrapping:NSLineBreakByTruncatingTail;
        paragraphStyle.alignment = [ACRTextBlockRenderer getTextBlockAlignment:txtBlck withHostConfig:config];

        // Obtain text color to apply to the attributed string
        ContainerStyle style = lab.style;
        ColorsConfig &colorConfig = (style == ContainerStyle::Emphasis)? config->containerStyles.emphasisPalette.foregroundColors:
                                                                         config->containerStyles.defaultPalette.foregroundColors;

        // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
        [content addAttributes:@{NSParagraphStyleAttributeName:paragraphStyle, NSForegroundColorAttributeName:[ACRTextBlockRenderer getTextBlockColor:txtBlck->GetTextColor() colorsConfig:colorConfig subtleOption:txtBlck->GetIsSubtle()], NSStrokeWidthAttributeName:[ACRTextBlockRenderer getTextStrokeWidthForWeight:txtBlck->GetTextWeight() withHostConfig:config]} range:NSMakeRange(0, content.length - 1)];
        lab.attributedText = content;

        std::string id = txtBlck->GetId();
        std::size_t idx = id.find_last_of('_');
        txtBlck->SetId(id.substr(0, idx));
    }

    lab.numberOfLines = int(txtBlck->GetMaxLines());
    if(!lab.numberOfLines and !txtBlck->GetWrap())
    {
        lab.numberOfLines = 1;
    }

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] init];

    [wrappingview addSubview:lab];

    [wrappingview setAlignmentForSubview:txtBlck->GetHorizontalAlignment()];

    [viewGroup addArrangedSubview:wrappingview];

    wrappingview.translatesAutoresizingMaskIntoConstraints = false;

    lab.translatesAutoresizingMaskIntoConstraints = false;

    return wrappingview;
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

+ (int)getTextBlockTextSize:(TextSize)txtSz
              withHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    switch (txtSz){
        case TextSize::Small:
            return config->fontSizes.smallFontSize;
        case TextSize::Default:
            return config->fontSizes.defaultFontSize;
        case TextSize::Medium:
            return config->fontSizes.mediumFontSize;
        case TextSize::Large:
            return config->fontSizes.largeFontSize;
        case TextSize::ExtraLarge:
            return config->fontSizes.extraLargeFontSize;
        default:
            return config->fontSizes.defaultFontSize;
    }
}

+ (NSTextAlignment)getTextBlockAlignment:(std::shared_ptr<TextBlock> const &)txtBlock
                          withHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    switch (txtBlock->GetHorizontalAlignment()){
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
                      withHostConfig:(std::shared_ptr<HostConfig> const &)config
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

+ (int)getTextBlockFontWeight:(TextWeight)weight
               withHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    switch (weight) {
        default:
        case TextWeight::Default:
            return config->fontWeights.defaultWeight;
        case TextWeight::Lighter:
            return config->fontWeights.lighterWeight;
        case TextWeight::Bolder:
            return config->fontWeights.bolderWeight;
    }
}

@end
