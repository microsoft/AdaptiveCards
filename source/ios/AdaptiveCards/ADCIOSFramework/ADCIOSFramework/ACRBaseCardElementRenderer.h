//
//  ACRBaseCardElementRenderer
//  ACRBaseCardElementRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <Foundation/Foundation.h>
#import "ACRIBaseCardElementRenderer.h"
@interface ACRBaseCardElementRenderer :NSObject <ACRIBaseCardElementRenderer>
- (void) setSeparationConfig: (UIView* ) viewGroup;
            //SeparationStyle separationStyle,
            //SeparationConfig defaultSeparationConfig,
            //SeparationConfig strongSeparationConfig,
            //(Boolean) horizontalLine)

@end
