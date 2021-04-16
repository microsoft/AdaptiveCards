#import <Foundation/Foundation.h>

#import "SwiftInterfaceHeader.h"
#import <AdaptiveCards_bridge/BridgeTextUtils.h>
#import "MarkDownParser.h"
#import "DateTimePreparsedToken.h"
#import "Enums.h"

@implementation BridgeTextUtils

+ (ACSMarkdownParserResult * _Nonnull)processTextFromTextBlock:(ACSTextBlock * _Nonnull)textBlock hostConfig:(ACSHostConfig * _Nonnull)config
{
    auto text = [BridgeConverter getStringCpp:[textBlock getText]];
    auto language = [BridgeConverter getStringCpp:[textBlock getLanguage]];
    auto textProperties = [BridgeTextUtils convertTextBlockToRichTextElementProperties:textBlock];
    std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>([BridgeTextUtils getLocalizedDate:text language:language]);

    // MarkDownParser transforms text with MarkDown to a html string
    NSString *parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];

    // use Apple's html rendering only if the string has markdowns
    NSString *fontFamilyName = nil;

    if ([config getFontFamily:[textBlock getFontType]]) {
        if ([textBlock getFontType] == ACSFontTypeMonospace) {
            fontFamilyName = @"'Courier New'";
        } else {
            fontFamilyName = @"'-apple-system',  'San Francisco'";
        }
    } else {
        fontFamilyName = [config getFontFamily:[textBlock getFontType]];
    }

    NSString *font_style = [textProperties getItalic] ? @"italic" : @"normal";
    // Font and text size are applied as CSS style by appending it to the html string
    parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%@px; font-weight: %@; font-style: %@;}</style>", fontFamilyName, [config getFontSize:[textBlock getFontType] size:[textBlock getTextSize]], [config getFontWeight:[textBlock getFontType] weight:[textBlock getTextWeight]], font_style]];

    NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];
    return [[ACSMarkdownParserResult alloc] initWithParsedString:parsedString htmlData:htmlData];
}

+ (ACSMarkdownParserResult * _Nonnull)processTextFromRichTextBlock:(ACSTextRun * _Nullable)textRun hostConfig:(ACSHostConfig * _Nonnull)config
{
    auto text = [BridgeConverter getStringCpp:[textRun getText]];
    auto language = [BridgeConverter getStringCpp:[textRun getLanguage]];
    auto textProperties = [BridgeTextUtils convertTextRunToRichTextElementProperties:textRun];
    std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>([BridgeTextUtils getLocalizedDate:text language:language]);

    // MarkDownParser transforms text with MarkDown to a html string
    NSString *parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];

    NSString *fontFamilyName = nil;
    if (![config getFontFamily:[textRun getFontType]]) {
        if ([textRun getFontType] == ACSFontTypeMonospace) {
            fontFamilyName = @"'Courier New'";
        } else {
            fontFamilyName = @"'-apple-system',  'San Francisco'";
        }
    } else {
        fontFamilyName = [config getFontFamily:[textRun getFontType]];
    }

    NSString *font_style = [textProperties getItalic] ? @"italic" : @"normal";
    // Font and text size are applied as CSS style by appending it to the html string
    parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%@px; font-weight: %@; font-style: %@;}</style>", fontFamilyName, [config getFontSize:[textRun getFontType] size:[textRun getTextSize]], [config getFontWeight:[textRun getFontType] weight:[textRun getTextWeight]], font_style]];

    NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];

    return [[ACSMarkdownParserResult alloc] initWithParsedString:parsedString htmlData:htmlData];
}

 + (ACSMarkdownParserResult * _Nonnull)processTextFromFact:(ACSFact * _Nullable)fact hostConfig:(ACSHostConfig * _Nonnull)config
{
    auto text = [BridgeConverter getStringCpp:[fact getValue]];
    auto language = [BridgeConverter getStringCpp:[fact getLanguage]];
    std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>([BridgeTextUtils getLocalizedDate:text language:language]);
    
    NSString *parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];
    if (markDownParser->HasHtmlTags() || markDownParser->IsEscaped()) {
        NSString *fontFamilyName = nil;
        fontFamilyName = [config getFontFamily: ACSFontTypeDefault];
        parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%@px; font-weight: %@;}</style>", fontFamilyName, [config getFontSize:ACSFontTypeDefault size:ACSTextSizeDefault], [config getFontWeight:ACSFontTypeDefault weight:ACSTextWeightDefault]]];
        NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];
        return [[ACSMarkdownParserResult alloc] initWithParsedString:parsedString htmlData:htmlData];
    }
    return [[ACSMarkdownParserResult alloc] initWithParsedString:parsedString htmlData:nil];
}

+ (ACSRichTextElementProperties * _Nonnull)convertTextRunToRichTextElementProperties:(ACSTextRun * _Nonnull)textRun
{
    ACSRichTextElementProperties* textProp = [[ACSRichTextElementProperties alloc] initWithRichTextElementProperties:std::make_shared<RichTextElementProperties>()];
    [textProp setLanguage:[textRun getLanguage]];
    [textProp setText:[textRun getText]];
    [textProp setTextSize:[textRun getTextSize]];
    [textProp setTextWeight:[textRun getTextWeight]];
    [textProp setFontType:[textRun getFontType]];
    [textProp setTextColor:[textRun getTextColor]];
    [textProp setIsSubtle:[textRun getIsSubtle]];
    [textProp setLanguage:[textRun getLanguage]];
    [textProp setItalic:[textRun getItalic]];
    return textProp;
}

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

+ (ACSRichTextElementProperties * _Nonnull)convertTextBlockToRichTextElementProperties:(ACSTextBlock * _Nonnull)textBlock
{
    ACSRichTextElementProperties* textProp = [[ACSRichTextElementProperties alloc] initWithRichTextElementProperties:std::make_shared<RichTextElementProperties>()];
    [textProp setText:[textBlock getText]];
    [textProp setTextSize:[textBlock getTextSize]];
    [textProp setTextWeight:[textBlock getTextWeight]];
    [textProp setFontType:[textBlock getFontType]];
    [textProp setTextColor:[textBlock getTextColor]];
    [textProp setIsSubtle:[textBlock getIsSubtle]];
    [textProp setLanguage:[textBlock getLanguage]];
    return textProp;
}
@end
