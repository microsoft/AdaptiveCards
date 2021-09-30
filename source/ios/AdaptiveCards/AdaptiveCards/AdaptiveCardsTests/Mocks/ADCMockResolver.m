//
//  ADCMockResolver.m
//  ADCIOSVisualizer
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ADCMockResolver.h"

@implementation ADCMockResolver


- (UIImageView *)resolveImageViewResource:(NSURL *)url
{
    return [[UIImageView alloc] init];
}

@end
