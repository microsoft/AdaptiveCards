// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSFontSizesConfig_IMPORTED
#define ACSFontSizesConfig_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
//#import "HostConfig.h"
using namespace AdaptiveCards;
#endif

#import "ACSTextSize.h"



  


enum ACSTextSize: NSUInteger;


@interface ACSFontSizesConfig : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithFontSizesConfig:(const std::shared_ptr<FontSizesConfig>)cppObj;
#endif

- (NSNumber * _Nullable)getFontSize:(enum ACSTextSize)size;
- (void)setFontSize:(enum ACSTextSize)size value:(NSNumber * _Nonnull)value;


@end
#endif
