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
    CACProgressBar *progressBarData = (CACProgressBar *)acoElem;
    UIProgressView *progressView = [[UIProgressView alloc] initWithProgressViewStyle:UIProgressViewStyleBar];
    progressView.translatesAutoresizingMaskIntoConstraints = NO;

    progressView.progressTintColor =  [UIColor colorWithRed:[progressBarData.red doubleValue] / 255.0f
        green:[progressBarData.green doubleValue] / 255.0f blue:[progressBarData.blue doubleValue] / 255.0f
        alpha:[progressBarData.alpha doubleValue]];
    progressView.trackTintColor = [UIColor clearColor];
    [progressView setProgress:[progressBarData.progress doubleValue] animated:YES];
    [[progressView layer] setBorderWidth:[progressBarData.thickness doubleValue]];
    progressView.clipsToBounds = NO;

    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] init];
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    
    [viewGroup addArrangedSubview:wrappingview];

    [wrappingview addSubview:progressView];
    [progressView.widthAnchor constraintEqualToAnchor:wrappingview.widthAnchor multiplier:0.8].active =  YES;
    [progressView.centerXAnchor constraintEqualToAnchor:wrappingview.centerXAnchor].active = YES;
    [progressView.heightAnchor constraintEqualToConstant:50].active = YES;
    [wrappingview.heightAnchor constraintEqualToConstant:55].active = YES;

    return progressView;
}

@end
