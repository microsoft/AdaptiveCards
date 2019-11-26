//
//  CustomProgressBarRenderer
//  CustomProgressBarRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "CustomProgressBarRenderer.h"

@implementation CACProgressBar

- (instancetype)init:(NSNumber *)red green:(NSNumber *)green blue:(NSNumber *)blue
               alpha:(NSNumber *)alpha
            progress:(NSNumber *)progress
           thickness:(NSNumber *)thickness
{
    self = [super init];
    if (self) {
        _red = red;
        _green = green;
        _blue = blue;
        _alpha = alpha;
        _progress = progress;
        _thickness = thickness;
    }

    return self;
}

- (ACOBaseCardElement *)deserialize:(NSData *)json parseContext:(ACOParseContext *)parseContext
{
    if (json) {
        NSDictionary *data = [NSJSONSerialization JSONObjectWithData:json options:NSJSONReadingMutableLeaves error:nil];
        NSDictionary<NSString *, NSNumber *> *myval = data[@"payload"][0];
        UIProgressView *progressView;
        progressView = [[UIProgressView alloc] initWithProgressViewStyle:UIProgressViewStyleBar];
        NSNumber *red = myval[@"red"];
        NSNumber *green = myval[@"green"];
        NSNumber *blue = myval[@"blue"];
        NSNumber *alpha = myval[@"alpha"];
        NSNumber *progress = myval[@"progress"];
        NSNumber *thickness = myval[@"thickness"];

        CACProgressBar *progressBarData = [[CACProgressBar alloc] init:red green:green blue:blue alpha:alpha progress:progress thickness:thickness];
        return progressBarData;
    }
    return nil;
}

@end

@implementation CustomProgressBarRenderer
+ (CustomProgressBarRenderer *)getInstance
{
    static CustomProgressBarRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig
{
    CACProgressBar *progressBarData = (CACProgressBar *)acoElem;
    UIProgressView *progressView = [[UIProgressView alloc] initWithProgressViewStyle:UIProgressViewStyleBar];
    progressView.translatesAutoresizingMaskIntoConstraints = NO;

    progressView.progressTintColor = [UIColor colorWithRed:[progressBarData.red doubleValue] / 255.0f
                                                     green:[progressBarData.green doubleValue] / 255.0f
                                                      blue:[progressBarData.blue doubleValue] / 255.0f
                                                     alpha:[progressBarData.alpha doubleValue]];
    progressView.trackTintColor = [UIColor clearColor];
    [progressView setProgress:[progressBarData.progress doubleValue] animated:YES];
    [[progressView layer] setBorderWidth:[progressBarData.thickness doubleValue]];
    progressView.clipsToBounds = NO;

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] init];
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;

    [viewGroup addArrangedSubview:wrappingview];

    [wrappingview addSubview:progressView];
    [progressView.widthAnchor constraintEqualToAnchor:wrappingview.widthAnchor multiplier:0.8].active = YES;
    [progressView.centerXAnchor constraintEqualToAnchor:wrappingview.centerXAnchor].active = YES;
    [progressView.heightAnchor constraintEqualToConstant:50].active = YES;
    [wrappingview.heightAnchor constraintEqualToConstant:55].active = YES;

    return progressView;
}

@end
