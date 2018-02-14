//
//  ACRTextBlockRenderer
//  ACRTextBlockRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"
#import "TextBlock.h"

@interface ACRTextBlockRenderer:ACRBaseCardElementRenderer

+ (ACRTextBlockRenderer *)getInstance;

+ (NSNumber *)getTextStrokeWidthForWeight:(TextWeight)weight
                      withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (int)getTextBlockFontWeight:(TextWeight)weight
               withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (int)getTextBlockTextSize:(TextSize)txtSz
             withHostConfig:(std::shared_ptr<HostConfig> const &)config;
+ (UIColor *)getTextBlockColor:(ForegroundColor)txtClr
                  colorsConfig:(ColorsConfig const &)config
                  subtleOption:(bool)isSubtle;
+ (NSTextAlignment)getTextBlockAlignment:(std::shared_ptr<TextBlock> const &)txtBlock
                          withHostConfig:(std::shared_ptr<HostConfig> const &)config;
// given string with short form of date (MM/dd/yyyy), convert it to 
// NSDateFormatterMediumStyle or NSDateFormatterLongStyle in local language
+ (void) getLocalizedDate:(std::shared_ptr<TextBlock> const &)txtBlck 
           stringWithDate:(std::string &)dateParsedString;
@end
