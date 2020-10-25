//
//  ACRAggregateTarget
//  ACRAggregateTarget.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRAggregateTarget.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseInputHandler.h"
#import "ACRViewController.h"
#import "ACRViewPrivate.h"
#import <UIKit/UIKit.h>

@implementation ACRAggregateTarget

- (instancetype)initWithActionElement:(ACOBaseActionElement *)actionElement rootView:(ACRView *)rootView;
{
    self = [super init];
    if (self) {
        _actionElement = actionElement;
        _view = rootView;
        _currentShowcard = [rootView peekCurrentShowCard];
    }
    return self;
}

- (IBAction)send:(UIButton *)sender
{
    [self validateInput];
    [self updateUI];
    [self dispatchUserInput];
    [self dispatchUserInput];
}

- (NSMutableArray *)validateInput
{
    BOOL hasValidationPassed = YES;
    BOOL hasViewChangedForAnyViews = NO;
    NSError *error = nil;
    NSMutableArray<ACRIBaseInputHandler> *gatheredInputs = [[NSMutableArray<ACRIBaseInputHandler> alloc] init];

    ACRColumnView *parent = _currentShowcard;

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
        parent = [_view getParent:parent];
    }
    return gatheredInputs;
}

//    if (hasValidationPassed) {
//        [[_view card] setInputs:gatheredInputs];
//        [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
//    } else if (hasViewChangedForAnyViews && [_view.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
//        [_view.acrActionDelegate didChangeViewLayout:CGRectNull newFrame:CGRectNull];
//    }

- (void)updateUI
{
}

- (void)dispatchUserInput
{
    [[_view card] setInputs:gatheredInputs];
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

- (void)notifyLayoutChage
{
    if (hasViewChangedForAnyViews && [_view.acrActionDelegate respondsToSelector:@selector(didChangeViewLayout:newFrame:)]) {
        [_view.acrActionDelegate didChangeViewLayout:CGRectNull newFrame:CGRectNull];
    }
}

- (void)doSelectAction
{
    [_view.acrActionDelegate didFetchUserResponses:[_view card] action:_actionElement];
}

@end
