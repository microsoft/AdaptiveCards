//
//  ACRTargetBuilderDirector.h
//  AdaptiveCards
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOBaseActionElementPrivate.h"
#import "ACRTargetBuilder.h"
#import "ACRView.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACRTargetBuilder.h>
#import <AdaptiveCards/ACRView.h>
#endif
#import <Foundation/Foundation.h>

// protocol all TargetBuild should implement
@interface ACRTargetBuilderDirector : NSObject
// indicates types of target director is allowed to build
@property __weak ACRView *rootView;
@property __weak ACOHostConfig *adaptiveHostConfig;
@property (readonly) ACRTargetCapability capability;

- (instancetype)init:(ACRView *)rootView capability:(ACRTargetCapability)capability adaptiveHostConfig:(ACOHostConfig *)adaptiveHostConfig;
- (NSObject *)build:(ACOBaseActionElement *)action;
- (NSObject *)build:(ACOBaseActionElement *)action forButton:(UIButton *)button;

@end
