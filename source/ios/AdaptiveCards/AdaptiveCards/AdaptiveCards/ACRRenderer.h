//
//  ACRRenderer.h
//  ACRRenderer
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACRRenderResult.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACRRenderResult.h>
#endif
#import "ACOAdaptiveCard.h"
#import "ACOHostConfig.h"
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface ACRRenderer : NSObject

- (instancetype)init;
+ (ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width;
+ (ACRRenderResult *)render:(ACOAdaptiveCard *)card config:(ACOHostConfig *)config widthConstraint:(float)width delegate:(id<ACRActionDelegate>)acrActionDelegate;
+ (ACRRenderResult *)renderAsViewController:(ACOAdaptiveCard *)card
                                     config:(ACOHostConfig *)config
                                      frame:(CGRect)frame
                                   delegate:(id<ACRActionDelegate>)acrActionDelegate;

@end
