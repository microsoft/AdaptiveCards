#import <Foundation/Foundation.h>

@class ACSMarkdownParserResult;
@class ACSTextBlock;
@class ACSHostConfig;
@class ACSRichTextElementProperties;

@interface BridgeTextUtils : NSObject

+ (ACSMarkdownParserResult * _Nonnull)processTextFromTextBlock:(ACSTextBlock * _Nonnull)textBlock hostConfig:(ACSHostConfig * _Nonnull)config;
+ (ACSMarkdownParserResult * _Nonnull)processTextFromRichTextBlock:(ACSTextRun * _Nullable)textBlock hostConfig:(ACSHostConfig * _Nonnull)config;
+ (ACSRichTextElementProperties * _Nonnull)convertTextBlockToRichTextElementProperties:(ACSTextBlock * _Nonnull)textBlock;
+ (ACSRichTextElementProperties * _Nonnull)convertTextRunToRichTextElementProperties:(ACSTextRun * _Nonnull)textRun;
+ (ACSRichTextElementProperties * _Nonnull)convertFactToRichTextElementProperties:(ACSFact * _Nonnull)fact;
+ (ACSMarkdownParserResult * _Nonnull)processTextFromFact:(ACSFact * _Nullable)fact hostConfig:(ACSHostConfig * _Nonnull)config;

@end
