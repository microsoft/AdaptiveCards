//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#ifdef SWIFT_PACKAGE
#import "ACRIBaseCardElementRenderer.h"
#else
#import <AdaptiveCards/ACRIBaseCardElementRenderer.h>
#endif
#import <Foundation/Foundation.h>
@interface ACRBaseCardElementRenderer : NSObject <ACRIBaseCardElementRenderer>
- (void)setSeparationConfig:(UIView *)viewGroup;

+ (void)applyLayoutStyle:(NSString *)styleFormat viewsMap:(NSDictionary *)viewsMap;

@end
