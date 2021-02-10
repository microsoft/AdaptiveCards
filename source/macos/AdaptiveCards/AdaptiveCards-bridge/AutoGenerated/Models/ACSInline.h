// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSInline_IMPORTED
#define ACSInline_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "Inline.h"
using namespace AdaptiveCards;
#endif

#import "ACSInlineElementType.h"
// #import "ACSValue.h"



  



enum ACSInlineElementType: NSUInteger;


@interface ACSInline : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithInline:(const std::shared_ptr<Inline>)cppObj;
#endif

- (ACSInlineElementType)getInlineType;
- (NSString * _Nullable)getInlineTypeString;


@end
#endif
