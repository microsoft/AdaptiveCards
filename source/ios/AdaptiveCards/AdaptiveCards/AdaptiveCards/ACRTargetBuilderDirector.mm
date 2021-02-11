//
//  ACRTargetBuilderDirector.mm
//  AdaptiveCards
//
//  Copyright © 2019 Microsoft. All rights reserved.

//  This module manages building and configuring targets for buttons and gesture handler.
//  as new kind of target will be added and existing targets become more complicated to build,
//  this module will help ease the burden of maintaining and implementing new targets.
//  To add a new target, the class for the target with an initializer should be added
//  then target builder for the new target should be added. target builder should inherit
//  ACRTargetBuilder which has two methods, build and build: forButton
//      they both build targets, but build: forButton designed to provide place to add target to
//      button, and configure the button
//  then the new builder is added to _builders; _builders is an array of dictionary
//  each entry in the array is a capability
//  a capability indicates available targets for each entry.
//  ACRAction is associated with actions in adaptive card
//  ACRSelectAction is associated with select action in adaptive card
//  ACRQuickReply is associated with input.inline
//
//  if more arguments are needed for building target than provided by the ACRITargetBuilder
//  protocol, parameters should be added via this module, director, to maintain clean and unified
//  interface.
//
//  target builders are singletons since they do exactly same works regardless of renderer
//  instances. however builders' director can have different configuration per rendering, and having
//  single instance per renderer is preferred. for these reasons, ACRView owns the director, and
//  clients who wish to use the director's service should access the service through two functions
//  in UtiliOS.h, buildTarget and buildTargetForButton

#import "ACRTargetBuilderDirector.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRAggregateTarget.h"
#import "ACRErrors.h"
#import "ACRRegistration.h"
#import "ACRShowCardTarget.h"
#import "ACRToggleVisibilityTarget.h"
#import "UtiliOS.h"

@implementation ACRTargetBuilder

+ (ACRTargetBuilder *)getInstance
{
    static ACRTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
{
    return nil;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button
{
    NSObject *target = [self build:action director:director];
    if (target) {
        [button addTarget:target
                      action:@selector(send:)
            forControlEvents:UIControlEventTouchUpInside];
    }
    return target;
}

@end

@implementation ACRAggregateTargetBuilder

+ (ACRAggregateTargetBuilder *)getInstance
{
    static ACRAggregateTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
{
    return [[ACRAggregateTarget alloc] initWithActionElement:action rootView:director.rootView];
}

@end

@implementation ACRShowCardTargetBuilder

+ (ACRShowCardTargetBuilder *)getInstance
{
    static ACRShowCardTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button
{
    std::shared_ptr<ShowCardAction> showCardAction =
        std::dynamic_pointer_cast<ShowCardAction>(action.element);

    if (director.rootView && director.adaptiveHostConfig) {
        NSObject *target =
            [[ACRShowCardTarget alloc] initWithActionElement:showCardAction
                                                      config:director.adaptiveHostConfig
                                                    rootView:director.rootView
                                                      button:button];
        [button addTarget:target
                      action:@selector(toggleVisibilityOfShowCard)
            forControlEvents:UIControlEventTouchUpInside];
        return target;
    }
    return nil;
}

@end

@implementation ACRToggleVisibilityTargetBuilder

+ (ACRToggleVisibilityTargetBuilder *)getInstance
{
    static ACRToggleVisibilityTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
{
    std::shared_ptr<ToggleVisibilityAction> toggleVisibilityAction =
        std::dynamic_pointer_cast<ToggleVisibilityAction>(action.element);

    if (toggleVisibilityAction && director.adaptiveHostConfig && director.rootView) {
        return [[ACRToggleVisibilityTarget alloc] initWithActionElement:toggleVisibilityAction
                                                                 config:director.adaptiveHostConfig
                                                               rootView:director.rootView];
    }
    return nil;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button
{
    NSObject *target = [self build:action director:director];
    if (target) {
        [button addTarget:target
                      action:@selector(doSelectAction)
            forControlEvents:UIControlEventTouchUpInside];
    }
    return target;
}

@end

@implementation ACRUnknownActionTargetBuilder

+ (ACRUnknownActionTargetBuilder *)getInstance
{
    static ACRUnknownActionTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
{
    if (action) {
        return [[ACRAggregateTarget alloc] initWithActionElement:action rootView:director.rootView];
    }

    return nil;
}

@end

@implementation ACRTargetBuilderDirector

- (instancetype)init
{
    self = [self init:nil capability:ACRAction adaptiveHostConfig:nil];
    return self;
}

- (instancetype)init:(ACRView *)rootView
            capability:(ACRTargetCapability)capability
    adaptiveHostConfig:(ACOHostConfig *)adaptiveHostConfig
{
    self = [super init];
    if (self) {
        self.rootView = rootView;
        self.adaptiveHostConfig = adaptiveHostConfig;
        _capability = capability;
    }
    return self;
}

- (NSObject *)build:(ACOBaseActionElement *)adaptiveAction
{
    ACRTargetBuilder *builder = [self getBuilder:adaptiveAction];

    if (builder) {
        return [builder build:adaptiveAction director:self];
    }
    return nil;
}

- (NSObject *)build:(ACOBaseActionElement *)adaptiveAction
          forButton:(UIButton *)button
{
    ACRTargetBuilder *builder = [self getBuilder:adaptiveAction];
    if (builder) {
        return [builder build:adaptiveAction director:self ForButton:button];
    }

    return nil;
}

- (ACRTargetBuilder *)getBuilder:(ACOBaseActionElement *)action
{
    return [[ACRTargetBuilderRegistration getInstance] getTargetBuilder:action.type capability:self.capability];
}

@end
