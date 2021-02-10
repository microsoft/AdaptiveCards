// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSRichTextElementProperties_IMPORTED
#define ACSRichTextElementProperties_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "RichTextElementProperties.h"
using namespace AdaptiveCards;
#endif

#import "ACSParseContext.h"
// #import "ACSValue.h"



#import "ACSTextElementProperties.h"
  

@class ACSParseContext;



@interface ACSRichTextElementProperties : ACSTextElementProperties

#ifdef __cplusplus
- (instancetype _Nonnull)initWithRichTextElementProperties:(const std::shared_ptr<RichTextElementProperties>)cppObj;
#endif

- (bool)getItalic;
- (void)setItalic:(bool)value;
- (bool)getStrikethrough;
- (void)setStrikethrough:(bool)value;
- (bool)getUnderline;
- (void)setUnderline:(bool)value;


@end
#endif
