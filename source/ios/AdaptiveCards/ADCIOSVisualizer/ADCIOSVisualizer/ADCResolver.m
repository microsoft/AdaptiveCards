//
//  ADCResolver.m
//  ADCIOSVisualizer
//
//  Created by Inyoung Woo on 7/11/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ADCResolver.h"

@implementation ADCResolver

- (UIImage *)resolveImageResource:(NSString *)url { 
    NSURL *nsurl = [NSURL URLWithString:url];
    // download image
    UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:nsurl]];
    return img;
}

@end

