// DO NOT EDIT - Auto generated

// Generated with objc_viewmodel_header.j2


#ifndef ACSFontWeightsConfig_IMPORTED
#define ACSFontWeightsConfig_IMPORTED
#import <Foundation/Foundation.h>

#ifdef __cplusplus
using namespace AdaptiveCards;
#endif

#import "ACSTextWeight.h"



  


enum ACSTextWeight: NSUInteger;


@interface ACSFontWeightsConfig : NSObject

#ifdef __cplusplus
- (instancetype _Nonnull)initWithFontWeightsConfig:(const std::shared_ptr<FontWeightsConfig>)cppObj;
#endif

- (NSNumber * _Nullable)getFontWeight:(enum ACSTextWeight)weight;
- (void)setFontWeight:(enum ACSTextWeight)weight value:(NSNumber * _Nonnull)value;


@end
#endif
