//
//  MockRenderer.h
//  ADCIOSVisualizer
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <AdaptiveCards/AdaptiveCards.h>

@interface MockRenderer : ACRBaseCardElementRenderer

+ (MockRenderer *)getInstance;

@end
