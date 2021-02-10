// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSTextBlock_IMPORTED
#define ACSTextBlock_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "TextBlock.h"
using namespace AdaptiveCards;
#endif

#import "ACSDateTimePreparser.h"
#import "ACSFontType.h"
#import "ACSForegroundColor.h"
#import "ACSHorizontalAlignment.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"



#import "ACSBaseCardElement.h"
  

@class ACSDateTimePreparser;

enum ACSFontType: NSUInteger;
enum ACSForegroundColor: NSUInteger;
enum ACSHorizontalAlignment: NSUInteger;
enum ACSTextSize: NSUInteger;
enum ACSTextWeight: NSUInteger;


@interface ACSTextBlock : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithTextBlock:(const std::shared_ptr<TextBlock>)cppObj;
#endif

- (NSString * _Nullable)getText;
- (void)setText:(NSString * _Nonnull)value;
- (ACSDateTimePreparser * _Nullable)getTextForDateParsing;
- (ACSTextSize)getTextSize;
- (void)setTextSize:(enum ACSTextSize)value;
- (ACSTextWeight)getTextWeight;
- (void)setTextWeight:(enum ACSTextWeight)value;
- (ACSFontType)getFontType;
- (void)setFontType:(enum ACSFontType)value;
- (ACSForegroundColor)getTextColor;
- (void)setTextColor:(enum ACSForegroundColor)value;
- (bool)getWrap;
- (void)setWrap:(bool)value;
- (bool)getIsSubtle;
- (void)setIsSubtle:(bool)value;
- (NSNumber * _Nullable)getMaxLines;
- (void)setMaxLines:(NSNumber * _Nonnull)value;
- (ACSHorizontalAlignment)getHorizontalAlignment;
- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value;
- (void)setLanguage:(NSString * _Nonnull)value;
- (NSString * _Nullable)getLanguage;



@end
#endif
