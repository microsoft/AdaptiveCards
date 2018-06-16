//
//  ACRColumnRenderer
//  ACRColumnRenderer.h
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRBaseCardElementRenderer.h"

@interface ACRColumnRenderer:ACRBaseCardElementRenderer

@property BOOL containerHasFillAlignment;

+ (ACRColumnRenderer *)getInstance;

- (void)setFillAlignment;
- (void)resetFillAlignment;

@end
