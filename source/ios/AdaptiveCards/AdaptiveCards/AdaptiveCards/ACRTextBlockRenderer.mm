//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRTextBlockRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "TextBlock.h"
#import "MarkDownParser.h"

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
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<TextBlock> txtBlck = std::dynamic_pointer_cast<TextBlock>(elem);
    UILabel *lab = [[UILabel alloc] init];

    // MarkDownParser transforms text with MarkDown to a html string
    std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>(txtBlck->GetText().c_str());
    NSString *parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];

    // Font and text size are applied as CSS style by appending it to the html string -- font is hard coded for now
    parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: '%@'; font-size:%dpx;}</style>",
                                                          @"verdana", [ACRTextBlockRenderer getTextBlockTextSize:txtBlck->GetTextSize() withHostConfig:config]]];
    // Convert html string to NSMutableAttributedString, NSAttributedString knows how to apply html tags
    NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];
    NSDictionary *options = @{NSDocumentTypeDocumentAttribute: NSHTMLTextDocumentType};
    NSMutableAttributedString *content = [[NSMutableAttributedString alloc] initWithData:htmlData options:options documentAttributes:nil error:nil];

    // Set paragraph style such as line break mode and alignment
    NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
    paragraphStyle.lineBreakMode = txtBlck->GetWrap() ? NSLineBreakByWordWrapping:NSLineBreakByTruncatingTail;
    paragraphStyle.alignment = [self getTextBlockAlignment:txtBlck withHostConfig:config];

    // Obtain text color to apply to the attributed string
    ContainerStyle style = [viewGroup getStyle];
    ColorsConfig &colorConfig = (style == ContainerStyle::Emphasis)? config->containerStyles.emphasisPalette.foregroundColors:
                                                                     config->containerStyles.defaultPalette.foregroundColors;

    // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
    [content addAttributes:@{NSParagraphStyleAttributeName:paragraphStyle, NSForegroundColorAttributeName:[ACRTextBlockRenderer getTextBlockColor:txtBlck->GetTextColor() colorsConfig:colorConfig subtleOption:txtBlck->GetIsSubtle()], NSStrokeWidthAttributeName:[ACRTextBlockRenderer getTextBlockTextWeight:txtBlck->GetTextWeight() withHostConfig:config]} range:NSMakeRange(0, content.length - 1)];
        lab.attributedText = content;

    lab.numberOfLines = int(txtBlck->GetMaxLines());
    if(!lab.numberOfLines and !txtBlck->GetWrap())
    {
        lab.numberOfLines = 1;
    }

    CGSize intrinsicSz = [lab intrinsicContentSize];

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:CGRectMake(0, 0, intrinsicSz.width, intrinsicSz.height)];

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

- (NSTextAlignment)getTextBlockAlignment:(std::shared_ptr<TextBlock> const &)txtBlock
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

+ (NSNumber *)getTextBlockTextWeight:(TextWeight)weight
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

@end
