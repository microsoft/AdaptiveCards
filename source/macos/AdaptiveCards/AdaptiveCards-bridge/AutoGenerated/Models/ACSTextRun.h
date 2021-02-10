// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSTextRun_IMPORTED
#define ACSTextRun_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "TextRun.h"
using namespace AdaptiveCards;
#endif

#import "ACSBaseActionElement.h"
#import "ACSDateTimePreparser.h"
#import "ACSFontType.h"
#import "ACSForegroundColor.h"
#import "ACSTextSize.h"
#import "ACSTextWeight.h"



#import "ACSInline.h"
  

@class ACSBaseActionElement;
@class ACSDateTimePreparser;

enum ACSFontType: NSUInteger;
enum ACSForegroundColor: NSUInteger;
enum ACSTextSize: NSUInteger;
enum ACSTextWeight: NSUInteger;


@interface ACSTextRun : ACSInline

#ifdef __cplusplus
- (instancetype _Nonnull)initWithTextRun:(const std::shared_ptr<TextRun>)cppObj;
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
- (bool)getItalic;
- (void)setItalic:(bool)value;
- (bool)getStrikethrough;
- (void)setStrikethrough:(bool)value;
- (bool)getHighlight;
- (void)setHighlight:(bool)value;
- (void)setLanguage:(NSString * _Nonnull)value;
- (NSString * _Nullable)getLanguage;
- (bool)getUnderline;
- (void)setUnderline:(bool)value;
- (ACSBaseActionElement * _Nullable)getSelectAction;
- (void)setSelectAction:(ACSBaseActionElement * _Nonnull)action;



@end
#endif
