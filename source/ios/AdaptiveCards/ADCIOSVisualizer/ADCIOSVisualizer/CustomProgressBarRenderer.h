//
//  CustomProgressBarRenderer.h
//  ADCIOSVisualizer
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AdaptiveCards/ACFramework.h>

@interface CustomProgressBarRenderer:NSObject<ACOIBaseCardElementParser>

- (UIView *)deserializeToCustomUIElement:(NSData* )json;
@end
