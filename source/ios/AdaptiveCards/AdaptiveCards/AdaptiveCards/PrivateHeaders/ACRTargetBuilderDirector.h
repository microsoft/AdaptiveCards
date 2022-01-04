//
//  ACRTargetBuilderDirector.h
//  AdaptiveCards
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import <AdaptiveCards/ACOBaseActionElementPrivate.h>
#import <AdaptiveCards/ACRView.h>
#import <Foundation/Foundation.h>
#import <AdaptiveCards/ACRTargetBuilder.h>

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
