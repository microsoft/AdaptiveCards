#import <Foundation/Foundation.h>

@class ACSMarkdownParserResult;
@class ACSTextBlock;
@class ACSHostConfig;
@class ACSRichTextElementProperties;

@interface BridgeTextUtils : NSObject

+ (ACSMarkdownParserResult * _Nonnull)processTextFromTextBlock:(ACSTextBlock * _Nonnull)textBlock hostConfig:(ACSHostConfig * _Nonnull)config;
+ (ACSRichTextElementProperties * _Nonnull)convertTextBlockToRichTextElementProperties:(ACSTextBlock * _Nonnull)textBlock;

@end
