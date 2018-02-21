//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACRIBaseCardElementRenderer.h"
@interface ACRBaseCardElementRenderer:NSObject<ACRIBaseCardElementRenderer>
- (void)setSeparationConfig:(UIView *)viewGroup;

+ (void)applyLayoutStyle:(NSString *)styleFormat viewsMap:(NSDictionary *)viewsMap;

@end
