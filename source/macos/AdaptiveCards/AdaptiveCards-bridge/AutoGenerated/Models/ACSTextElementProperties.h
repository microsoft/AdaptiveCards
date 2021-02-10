// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSTextElementProperties_IMPORTED
#define ACSTextElementProperties_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "TextElementProperties.h"
using namespace AdaptiveCards;
#endif

#import "ACSDateTimePreparser.h"
#import "ACSFontType.h"
#import "ACSForegroundColor.h"
#import "ACSParseContext.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"
// #import "ACSValue.h"



  

@class ACSDateTimePreparser;
@class ACSParseContext;

enum ACSFontType: NSUInteger;
enum ACSForegroundColor: NSUInteger;
enum ACSTextSize: NSUInteger;
enum ACSTextWeight: NSUInteger;


@interface ACSTextElementProperties : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithTextElementProperties:(const std::shared_ptr<TextElementProperties>)cppObj;
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
- (bool)getIsSubtle;
- (void)setIsSubtle:(bool)value;
- (void)setLanguage:(NSString * _Nonnull)value;
- (NSString * _Nullable)getLanguage;


@end
#endif
