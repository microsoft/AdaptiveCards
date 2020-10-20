//
//  ACRTargetBuilderDirector.h
//  AdaptiveCards
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "ACOBaseActionElementPrivate.h"
#import "ACRView.h"
#import <Foundation/Foundation.h>

// protocol all TargetBuild should implement
@interface ACRTargetBuilderDirector : NSObject
// indicates types of target director is allowed to build
@property __weak ACRView *rootView;
@property __weak ACOHostConfig *adaptiveHostConfig;

typedef NS_ENUM(NSInteger, ACRTargetCapability) {
    ACRAction = 0,
    ACRSelectAction,
    ACRQuickReply,
};

- (instancetype)init:(ACRView *)rootView capability:(ACRTargetCapability)capability adaptiveHostConfig:(ACOHostConfig *)adaptiveHostConfig;
- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action;
- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action forButton:(UIButton *)button;

@end

@protocol ACRITargetBuilder

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director;
- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button;

@end

// provides singleton interface
@interface ACRTargetBuilder : NSObject <ACRITargetBuilder>

+ (ACRTargetBuilder *)getInstance;

@end

// build target for submit and openUrl actions
@interface ACRAggregateTargetBuilder : ACRTargetBuilder
@end

@interface ACRShowCardTargetBuilder : ACRTargetBuilder
@end

@interface ACRToggleVisibilityTargetBuilder : ACRTargetBuilder
@end

// build target for unknown actions
@interface ACRUnknownActionTargetBuilder : ACRTargetBuilder
@end


