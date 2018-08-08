//
//  ADCResolver.m
//  ADCIOSVisualizer
//
//  Created by Inyoung Woo on 7/11/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ADCResolver.h"

@implementation ADCResolver

- (UIImage *)resolveImageResource:(NSURL *)url { 
    // download image
    UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
    return img;
}

@end

