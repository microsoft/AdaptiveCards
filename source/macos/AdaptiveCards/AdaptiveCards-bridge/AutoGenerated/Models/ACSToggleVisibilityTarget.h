// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSToggleVisibilityTarget_IMPORTED
#define ACSToggleVisibilityTarget_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
#import "ToggleVisibilityTarget.h"
using namespace AdaptiveCards;
#endif

#import "ACSIsVisible.h"



  


enum ACSIsVisible: NSUInteger;


@interface ACSToggleVisibilityTarget : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithToggleVisibilityTarget:(const std::shared_ptr<ToggleVisibilityTarget>)cppObj;
#endif

- (NSString * _Nullable)getElementId;
- (void)setElementId:(NSString * _Nonnull)value;
- (ACSIsVisible)getIsVisible;
- (void)setIsVisible:(enum ACSIsVisible)value;


@end
#endif
