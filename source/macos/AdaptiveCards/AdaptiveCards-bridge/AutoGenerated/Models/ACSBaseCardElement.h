// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSBaseCardElement_IMPORTED
#define ACSBaseCardElement_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "BaseCardElement.h"
using namespace AdaptiveCards;
#endif

#import "ACSCardElementType.h"
#import "ACSHeightType.h"
#import "ACSSpacing.h"



#import "ACSBaseElement.h"
  


enum ACSCardElementType: NSUInteger;
enum ACSHeightType: NSUInteger;
enum ACSSpacing: NSUInteger;


@interface ACSBaseCardElement : ACSBaseElement

#ifdef __cplusplus
- (instancetype _Nonnull)initWithBaseCardElement:(const std::shared_ptr<BaseCardElement>)cppObj;
#endif

- (bool)getSeparator;
- (void)setSeparator:(bool)value;
- (ACSHeightType)getHeight;
- (void)setHeight:(enum ACSHeightType)value;
- (ACSSpacing)getSpacing;
- (void)setSpacing:(enum ACSSpacing)value;
- (bool)getIsVisible;
- (void)setIsVisible:(bool)value;
- (ACSCardElementType)getElementType;



@end
#endif
