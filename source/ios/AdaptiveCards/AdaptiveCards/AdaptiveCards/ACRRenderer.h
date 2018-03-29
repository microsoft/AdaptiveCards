//
//  ACRRenderer.h
//  ACRRenderer
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ACRRenderResult.h"
#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"

@interface ACRRenderer:NSObject

- (instancetype)init;
+ (ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width;
+ (ACRRenderResult *)renderAsViewController:(ACOAdaptiveCard *)card
                                     config:(ACOHostConfig *)config
                                      frame:(CGRect)frame
                                   delegate:(id<ACRActionDelegate>)acrActionDelegate;
;

@end    
