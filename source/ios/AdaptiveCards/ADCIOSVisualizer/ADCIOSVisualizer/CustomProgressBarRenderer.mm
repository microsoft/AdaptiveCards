//
//  CustomProgressBarRenderer
//  CustomProgressBarRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "CustomProgressBarRenderer.h"

@implementation CustomProgressBarRenderer

- (UIView *)deserializeToCustomUIElement:(NSData* )json
{
        if(json) {
            NSDictionary *data = [NSJSONSerialization JSONObjectWithData:json options:NSJSONReadingMutableLeaves error:nil];
            NSDictionary<NSString *, NSNumber *> *myval = data[@"payload"][0];
            UIProgressView *progressView;
            progressView = [[UIProgressView alloc] initWithProgressViewStyle:UIProgressViewStyleBar];
            NSNumber *red = myval[@"red"];
            NSNumber *green = myval[@"green"];
            NSNumber *blue = myval[@"blue"];
            NSNumber *alpha = myval[@"alpha"];

            progressView.progressTintColor =  [UIColor colorWithRed:[red doubleValue] / 255 green:[green doubleValue] /255 blue:[blue doubleValue] /255 alpha:[alpha doubleValue]];
            [[progressView layer]setFrame:CGRectMake(20, 50, 200, 50)];
            progressView.trackTintColor = [UIColor clearColor];
            [progressView setProgress:0.8 animated:YES];
            [[progressView layer]setBorderWidth:3];
            progressView.clipsToBounds = YES;
            return progressView;
        }
        return nil;
}

@end
