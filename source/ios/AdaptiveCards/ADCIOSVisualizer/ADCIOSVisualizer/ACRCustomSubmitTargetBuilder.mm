//
//  ACRCustomSubmitTargetBuilder.mm
//  AdaptiveCards
//
//  Copyright © 2020 Microsoft. All rights reserved.

#import "ACRCustomSubmitTargetBuilder.h"
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/ACRTargetBuilderDirector.h>
#import <AdaptiveCards/ACRViewPrivate.h>

@interface ACRCustomSubmitTarget : ACRAggregateTarget
@end

@implementation ACRCustomSubmitTarget
- (IBAction)send:(UIButton *)sender
{
}
@end

@implementation ACRCustomSubmitTargetBuilder

+ (ACRCustomSubmitTargetBuilder *)getInstance
{
    static ACRCustomSubmitTargetBuilder *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (NSObject *)build:(ACOBaseActionElement *)action
           director:(ACRTargetBuilderDirector *)director
{
    return [[ACRCustomSubmitTarget alloc] initWithActionElement:action rootView:director.rootView];
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
