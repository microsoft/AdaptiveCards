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
#import "ACRAggregateTarget.h"
#import "ACRErrors.h"
#import "ACRShowCardTarget.h"
#import "ACRToggleVisibilityTarget.h"

// protocol all TargetBuild should implement
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

@implementation ACRTargetBuilder

+ (ACRTargetBuilder *)getInstance {
    static ACRTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director {
    return nil;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button {
    return nil;
}

@end

// build target for submit and openUrl actions
@interface ACRAggregateTargetBuilder : ACRTargetBuilder
@end

@implementation ACRAggregateTargetBuilder

+ (ACRAggregateTargetBuilder *)getInstance {
    static ACRAggregateTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director {
    ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] initWithBaseActionElement:action];

    return [[ACRAggregateTarget alloc] initWithActionElement:acoElem rootView:director.rootView];
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button {
    NSObject *target = [self build:action director:director];
    if (target) {
        [button addTarget:target
                      action:@selector(send:)
            forControlEvents:UIControlEventTouchUpInside];
    }
    return target;
}

@end

@interface ACRShowCardTargetBuilder : ACRTargetBuilder
@end

@implementation ACRShowCardTargetBuilder

+ (ACRShowCardTargetBuilder *)getInstance {
    static ACRShowCardTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

// currently not needed
- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director {
    return nil;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button {
    std::shared_ptr<ShowCardAction> showCardAction =
        std::dynamic_pointer_cast<ShowCardAction>(action);

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

@interface ACRToggleVisibilityTargetBuilder : ACRTargetBuilder
@end

@implementation ACRToggleVisibilityTargetBuilder

+ (ACRToggleVisibilityTargetBuilder *)getInstance {
    static ACRToggleVisibilityTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director {
    std::shared_ptr<ToggleVisibilityAction> toggleVisibilityAction =
        std::dynamic_pointer_cast<ToggleVisibilityAction>(action);

    if (toggleVisibilityAction && director.adaptiveHostConfig && director.rootView) {
        return [[ACRToggleVisibilityTarget alloc] initWithActionElement:toggleVisibilityAction
                                                                 config:director.adaptiveHostConfig
                                                               rootView:director.rootView];
    }
    return nil;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
           director:(ACRTargetBuilderDirector *)director
          ForButton:(UIButton *)button {
    NSObject *target = [self build:action director:director];
    if (target) {
        [button addTarget:target
                      action:@selector(doSelectAction)
            forControlEvents:UIControlEventTouchUpInside];
    }
    return target;
}

@end

@implementation ACRTargetBuilderDirector {
    NSDictionary<NSNumber *, ACRTargetBuilder *> *_builders;
}

- (instancetype)init {
    self = [self init:nil capability:ACRAction adaptiveHostConfig:nil];
    return self;
}

- (instancetype)init:(ACRView *)rootView
            capability:(ACRTargetCapability)capability
    adaptiveHostConfig:(ACOHostConfig *)adaptiveHostConfig {
    self = [super init];
    if (self) {
        self.rootView = rootView;
        self.adaptiveHostConfig = adaptiveHostConfig;
        NSNumber *openUrl = [NSNumber numberWithInt:static_cast<int>(ActionType::OpenUrl)];
        NSNumber *submit = [NSNumber numberWithInt:static_cast<int>(ActionType::Submit)];
        NSNumber *showcard = [NSNumber numberWithInt:static_cast<int>(ActionType::ShowCard)];
        NSNumber *toggle = [NSNumber numberWithInt:static_cast<int>(ActionType::ToggleVisibility)];

        // target capability lists supported events and corresponding target builders
        switch (capability) {
            case ACRAction:
                _builders = @{
                    openUrl : [ACRAggregateTargetBuilder getInstance],
                    submit : [ACRAggregateTargetBuilder getInstance],
                    showcard : [ACRShowCardTargetBuilder getInstance],
                    toggle : [ACRToggleVisibilityTargetBuilder getInstance]
                };
                break;
            case ACRSelectAction:
                _builders = @{
                    openUrl : [ACRAggregateTargetBuilder getInstance],
                    submit : [ACRAggregateTargetBuilder getInstance],
                    toggle : [ACRToggleVisibilityTargetBuilder getInstance]
                };
                break;
            case ACRQuickReply:
                _builders = @{
                    openUrl : [ACRAggregateTargetBuilder getInstance],
                    submit : [ACRAggregateTargetBuilder getInstance],
                    toggle : [ACRToggleVisibilityTargetBuilder getInstance]
                };
                break;
        }
    }
    return self;
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action {
    if ([self checkAgainstMyCapability:action]) {
        // check fail, stop and return
        return nil;
    }

    ACRTargetBuilder *builder = [self getBuilder:action];
    return [builder build:action director:self];
}

- (NSObject *)build:(std::shared_ptr<BaseActionElement> const &)action
          forButton:(UIButton *)button {
    if (ACRRenderingStatus::ACROk == [self checkAgainstMyCapability:action]) {
        ACRTargetBuilder *builder = [self getBuilder:action];
        return [builder build:action director:self ForButton:button];
    }
    return nil;
}

- (ACRRenderingStatus)checkAgainstMyCapability:(std::shared_ptr<BaseActionElement> const &)action {
    return ([_builders
               objectForKey:[NSNumber numberWithInt:static_cast<int>(action->GetElementType())]])
               ? ACRRenderingStatus::ACROk
               : ACRRenderingStatus::ACRUnsupported;
}

- (ACRTargetBuilder *)getBuilder:(std::shared_ptr<BaseActionElement> const &)action {
    NSNumber *key = [NSNumber numberWithInt:static_cast<int>(action->GetElementType())];
    return _builders[key];
}

@end

