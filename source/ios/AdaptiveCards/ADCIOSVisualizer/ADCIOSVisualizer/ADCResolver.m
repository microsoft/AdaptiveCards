//
//  ADCResolver.m
//  ADCIOSVisualizer
//
//  Created by Inyoung Woo on 7/11/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ADCResolver.h"

@implementation ADCResolver


- (UIImageView *)resolveImageViewResource:(NSURL *)url {
    __block UIImageView *imageView = [[UIImageView alloc] init];
    NSURLSessionDownloadTask *downloadPhotoTask = [[NSURLSession sharedSession]
                                                   downloadTaskWithURL:url completionHandler:^(NSURL *location, NSURLResponse *response, NSError *error) {
                                                       UIImage *image = [UIImage imageWithData: [NSData dataWithContentsOfURL:location]];
                                                       dispatch_async(dispatch_get_main_queue(), ^{
                                                           imageView.image = image;
                                                       });
                                                   }];
    [downloadPhotoTask resume];
    return imageView;
}


@end

