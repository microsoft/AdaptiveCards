//
//  ACRCustomSubmitTargetBuilder.mm
//  AdaptiveCards
//
//  Copyright © 2020 Microsoft. All rights reserved.

#import "ACRCustomSubmitTargetBuilder.h"
#import <AdaptiveCards/ACRTargetBuilderDirector.h>
#import <AdaptiveCards/ACRAggregateTarget.h>
#import <AdaptiveCards/ACRViewPrivate.h>

@interface ACRCustomSubmitTarget : ACRAggregateTarget
@end

@implementation ACRCustomSubmitTarget
- (IBAction)send:(UIButton *)sender
{
    BOOL hasValidationPassed = YES;
    BOOL hasViewChangedForAnyViews = NO;
    NSError *error = nil;
    NSMutableArray<ACRIBaseInputHandler> *gatheredInputs = [[NSMutableArray<ACRIBaseInputHandler> alloc] init];

    ACRColumnView *parent = self.currentShowcard;

    while (parent) {
        NSMutableArray<ACRIBaseInputHandler> *inputs = parent.inputHandlers;
        for (id<ACRIBaseInputHandler> input in inputs) {
            BOOL validationResult = [input validate:&error];
            [gatheredInputs addObject:input];
            if (hasValidationPassed && !validationResult) {
                [input setFocus:YES view:nil];
            } else {
                [input setFocus:NO view:nil];
            }
            hasValidationPassed &= validationResult;
            hasViewChangedForAnyViews |= input.hasVisibilityChanged;
        }
        parent = [self.view getParent:parent];
    }

    if (hasValidationPassed) {
        sender.backgroundColor = UIColor.greenColor;
        [[self.view card] setInputs:gatheredInputs];
        [self.view.acrActionDelegate didFetchUserResponses:[self.view card] action:self.actionElement];
    } else if (hasViewChangedForAnyViews && [self.view.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
        [self.view.acrActionDelegate didChangeViewLayout:CGRectNull newFrame:CGRectNull];
    }
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
