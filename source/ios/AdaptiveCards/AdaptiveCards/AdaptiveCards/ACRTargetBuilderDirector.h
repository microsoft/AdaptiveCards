//
//  ACRTargetBuilderDirector.h
//  AdaptiveCards
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACOBaseActionElementPrivate.h"
#import "Util.h"

@interface ACRTargetBuilderDirector:NSObject
// indicates types of target director is allowed to build
@property ACRTargetCapability builderCapability;
@property __weak ACRView *rootView;
@property __weak ACOHostConfig *adaptiveHostConfig;

- (instancetype)init:(ACRView *)rootView capability:(ACRTargetCapability)capability adaptiveHostConfig:(ACOHostConfig *)adaptiveHostConfig;

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action;
- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action forButton:(UIButton *)button;

@end
