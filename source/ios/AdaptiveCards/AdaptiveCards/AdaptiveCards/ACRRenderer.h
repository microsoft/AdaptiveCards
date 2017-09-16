//
//  ACRRenderer.h
//  ACRRenderer
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRRenderResult.h"
#import "ACOAdaptiveCards.h"
#import "ACOHostConfig.h"

@interface ACRRenderer:NSObject

- (instancetype)init;
+ (ACRRenderResult *)render:(ACOAdaptiveCards *)card config:(ACOHostConfig *)config frame:(CGRect) frame;

@end    
