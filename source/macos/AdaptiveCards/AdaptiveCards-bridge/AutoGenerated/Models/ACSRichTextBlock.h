// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSRichTextBlock_IMPORTED
#define ACSRichTextBlock_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "RichTextBlock.h"
using namespace AdaptiveCards;
#endif

#import "ACSHorizontalAlignment.h"
#import "ACSInline.h"



#import "ACSBaseCardElement.h"
  

@class ACSInline;

enum ACSHorizontalAlignment: NSUInteger;


@interface ACSRichTextBlock : ACSBaseCardElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithRichTextBlock:(const std::shared_ptr<RichTextBlock>)cppObj;
#endif

- (ACSHorizontalAlignment)getHorizontalAlignment;
- (void)setHorizontalAlignment:(enum ACSHorizontalAlignment)value;
- (NSArray<ACSInline *> * _Nonnull)getInlines;



@end
#endif
