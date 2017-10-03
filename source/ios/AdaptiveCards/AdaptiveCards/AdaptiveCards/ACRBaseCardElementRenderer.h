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
            //SeparationStyle separationStyle,
            //SeparationConfig defaultSeparationConfig,
            //SeparationConfig strongSeparationConfig,
            //(Boolean) horizontalLine)

+ (void)applyLayoutStyle:(NSString *)styleFormat view1:(UIView *)view1 view2:(UIView *)view2;
@end
